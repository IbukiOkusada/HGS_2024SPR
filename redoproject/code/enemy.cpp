//===============================================
//
// �G�l�~�[�̏��� [enemy.cpp]
// Author : Riku Nakamura
//
//===============================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "camera.h"
#include "Xfile.h"
#include "slow.h"
#include "texture.h"
#include "meshfield.h"
#include "Xfile.h"
#include "meshorbit.h"
#include "game.h"
#include "filter.h"
#include "object2D.h"
#include "meshwall.h"
#include "objectX.h"
#include "sound.h"
#include <assert.h>
#include "billboard.h"
#include "character.h"
#include "motion.h"
#include "waist.h"
#include "sound.h"
#include "model.h"
#include "particle.h"
#include "effect.h"
#include <math.h>
#include "meshwall.h"
#include "enemy_manager.h"
#include "fade.h"
#include "camera_manager.h"
#include "camera.h"
#include "score.h"
#include "sun.h"
#include "player.h"
#include "player_manager.h"

//===============================================
// �������O���
//===============================================
namespace {
	const float MOVE = (1.0f);	// �ړ���
	const float ROT_MULTI = (0.1f);	// �����␳�{��
	const float INER = (0.3f);		// ����
	const float DAMAGE_APPEAR = (40.0f);
	const int SETLIFE = (4);
	const int ADDSCORE = (3);
}

namespace ENEMY
{
	const D3DXVECTOR3 COLLIMAX = { 20.0f, 70.0f, 20.0f };	// �ő哖���蔻��
	const D3DXVECTOR3 COLLIMIN = { -20.0f, 0.0f, -20.0f };	// �ŏ������蔻��
}

// �O���錾

//===============================================
// �R���X�g���N�^
//===============================================
//CEnemy::CEnemy()
//{
//	// �l���N���A����
//	m_nCounterAnim = 0;
//	m_nPatternAnim = 0;
//}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CEnemy::CEnemy()
{
	// �l���N���A����
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	m_type = TYPE_NONE;
	m_nId = -1;
	m_bMove = false;
	m_pScore = nullptr;
	m_nLife = 0;
	m_headState = HEADSTATE_NORMAL;

	CEnemyManager::GetInstance()->ListIn(this);
}

//===============================================
// �f�X�g���N�^
//===============================================
CEnemy::~CEnemy()
{
	
}

//===============================================
// ����������
//===============================================
HRESULT CEnemy::Init(void)
{
	// �����g�̐ݒ�
	m_pLeg = CCharacter::Create("data\\TXT\\motion_playerbody.txt");
	m_pLeg->SetParent(&m_Info.mtxWorld);

	if (m_pLeg->GetMotion() != nullptr)
	{
		// �������[�V�����̐ݒ�
		m_pLeg->GetMotion()->InitSet(m_nMotion);
	}

	// ���̂̐ݒ�
	m_pBody = CCharacter::Create("data\\TXT\\motion_bee.txt");
	m_pBody->SetParent(m_pLeg->GetParts(2)->GetMtx());

	if (m_pBody->GetMotion() != nullptr)
	{
		// �������[�V�����̐ݒ�
		m_pBody->GetMotion()->InitSet(m_nMotion);
		m_pBody->GetParts(0)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// �p�����[�^�̐ݒ�
	m_Info.state = STATE_APPEAR;
	m_type = TYPE_NONE;
	m_headState = HEADSTATE_NORMAL;
	m_nLife = SETLIFE;

	return S_OK;
}

//===============================================
// ����������(�I�[�o�[���[�h)
//===============================================
HRESULT CEnemy::Init(const char *pBodyName, const char *pLegName)
{
	SetMatrix();

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CEnemy::Uninit(void)
{
	CEnemyManager::GetInstance()->ListOut(this);

	// ���̂̏I��
	if (m_pBody != nullptr) {
		m_pBody->Uninit();
		delete m_pBody;
		m_pBody = nullptr;
	}

	// �����g�̏I��
	if (m_pLeg != nullptr) {
		m_pLeg->Uninit();
		delete m_pLeg;
		m_pLeg = nullptr;
	}

	// �p��
	Release();
}

//===============================================
// �X�V����
//===============================================
void CEnemy::Update(void)
{	
	// �O��̍��W���擾
	m_Info.posOld = GetPosition();

	StateSet();	

	{
		
		// �G�l�~�[����
		Controller();

		// �I�����C�����M
		//CManager::GetInstance()->GetScene()->SendPosition(m_Info.pos);
		//CManager::GetInstance()->GetScene()->SendRotation(m_Info.rot);
	}
	
	SetMatrix();
	BodySet();
}

//===============================================
// ����
//===============================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pEnemy = nullptr;

	// �I�u�W�F�N�g2D�̐���
	pEnemy = new CEnemy();

	if (nullptr != pEnemy)
	{// �����ł����ꍇ
		// ����������
		pEnemy->Init();

		// ���W�ݒ�
		pEnemy->SetPosition(pos);

		// �����ݒ�
		pEnemy->SetRotation(rot);

		pEnemy->m_fRotDest = rot.y;
	}
	else
	{// �����Ɏ��s�����ꍇ
		return nullptr;
	}

	return pEnemy;
}

//===============================================
// ���쏈��
//===============================================
void CEnemy::Controller(void)
{
	D3DXVECTOR3 pos = GetPosition();	// ���W���擾
	D3DXVECTOR3 rot = GetRotation();	// �������擾
	float fSlow = CManager::GetInstance()->GetSlow()->Get();
	float fIner = INER;
	m_fRotMove = rot.y;	//���݂̌������擾

	{
		Move();
	}

	// �����ݒ�
	Adjust();

	m_Info.move.x += (0.0f - m_Info.move.x) * 0.12f;	//x���W
	m_Info.move.z += (0.0f - m_Info.move.z) * 0.12f;	//x���W

	pos.x += m_Info.move.x * fSlow;
	pos.z += m_Info.move.z * fSlow;

	// �����蔻��
	{
		D3DXVECTOR3 vtxMax = ENEMY::COLLIMAX;
		D3DXVECTOR3 vtxMin = ENEMY::COLLIMIN;
		D3DXVECTOR3 vtxMaxOld = vtxMax;
		D3DXVECTOR3 vtxMinOld = vtxMin;
		CObjectX::COLLISION_AXIS ColiAxis = CObjectX::TYPE_MAX;	// �������Ă�����������Z�b�g
		CObjectX::Collision(pos, m_Info.posOld, m_Info.move, vtxMin, vtxMax, vtxMinOld, vtxMaxOld, ColiAxis);
	}

	SetPosition(pos);
	SetRotation(m_Info.rot);
}

//===============================================
// �ړ�
//===============================================
void CEnemy::Move(void)
{
	float fSpeed = MOVE;	// �ړ���

	//�G�l�~�[�̍X�V

	if (CPlayerManager::GetInstance()->GetTop())
	{
		D3DXVECTOR3 posPlayer = CPlayerManager::GetInstance()->GetTop()->GetPosition();
		D3DXVECTOR3 posEnemy = GetPosition();
		float rotDef, rotPlayer;

		rotPlayer = atan2f(posEnemy.x - posPlayer.x, posEnemy.z - posPlayer.z);

		// ��]�␳
		if (rotPlayer > D3DX_PI)
		{
			rotPlayer -= D3DX_PI * 2.0f;
		}

		if (rotPlayer < -D3DX_PI)
		{
			rotPlayer += D3DX_PI * 2.0f;
		}

		m_fRotDest = rotPlayer;

		m_Info.move.x += -sinf(GetRotation().y + (D3DX_PI * 0.0f)) * fSpeed;
		m_Info.move.z += -cosf(GetRotation().y + (D3DX_PI * 0.0f)) * fSpeed;
	}
}

//===============================================
// ��ԊǗ�
//===============================================
void CEnemy::StateSet(void)
{
	float fSlawMul = CManager::GetInstance()->GetSlow()->Get();
	switch (m_Info.state)
	{
	case STATE_APPEAR:
	{
		m_Info.fStateCounter -= fSlawMul;

		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = 0.0f;
			m_Info.state = STATE_NORMAL;
		}
	}
		break;

	case STATE_NORMAL:
	{

	}
		break;

	case STATE_DAMAGE:
	{
		m_Info.fStateCounter -= fSlawMul;

		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = DAMAGE_APPEAR;
			m_Info.state = STATE_APPEAR;
		}
	}
		break;

	case STATE_DEATH:
	{
		m_Info.fStateCounter -= fSlawMul;

		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = DAMAGE_APPEAR;
		}
	}
		break;

	}
}

//===============================================
// �̗͐ݒ�
//===============================================
void CEnemy::SetType(TYPE type)
{
	m_type = type;
}

//===============================================
// �}�g���b�N�X�ݒ�
//===============================================
void CEnemy::SetMatrix(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�ւ̃|�C���^���擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);
}

//===============================================
// �w�胂�[�V�����ɐݒ�
//===============================================
void CEnemy::SetMotion(int nMotion) {	
	
}

//===============================================
// �G�l�~�[�̕`��ݒ�
//===============================================
void CEnemy::SetDraw(bool bDraw)
{
	
}

//===============================================
// ����
//===============================================
void CEnemy::Adjust(void)
{
	while (1)
	{
		if (m_fRotDest > D3DX_PI || m_fRotDest < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (m_fRotDest > D3DX_PI)
			{
				m_fRotDest += (-D3DX_PI * 2);
			}
			else if (m_fRotDest < -D3DX_PI)
			{
				m_fRotDest += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}

	m_fRotDiff = m_fRotDest - m_fRotMove;	//�ڕW�܂ł̈ړ������̍���

	while (1)
	{
		if (m_fRotDiff > D3DX_PI || m_fRotDiff < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (m_fRotDiff > D3DX_PI)
			{
				m_fRotDiff += (-D3DX_PI * 2);
			}
			else if (m_fRotDiff < -D3DX_PI)
			{
				m_fRotDiff += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}

	m_Info.rot.y += m_fRotDiff * ROT_MULTI;

	while (1)
	{
		if (m_Info.rot.y > D3DX_PI || m_Info.rot.y < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (m_Info.rot.y > D3DX_PI)
			{
				m_Info.rot.y += (-D3DX_PI * 2);
			}
			else if (m_Info.rot.y < -D3DX_PI)
			{
				m_Info.rot.y += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}
}

//===============================================
// �g�p�K�w�\���̐ݒ�
//===============================================
void CEnemy::BodySet(void)
{
	// �����g�X�V
	if (BodyCheck(m_pLeg))
	{// �g�p����Ă���ꍇ
		m_pLeg->Update();
	}

	// ���̍X�V
	if (BodyCheck(m_pBody))
	{// �g�p����Ă���ꍇ
		m_pBody->Update();
	}
}

//===============================================
// �̎g�p�m�F
//===============================================
bool CEnemy::BodyCheck(CCharacter* pBody)
{
	if (pBody == nullptr) {	// �g�p����Ă���
		return false;
	}

	if (pBody->GetMotion() == nullptr) {	// ���[�V�������g�p����Ă���
		return false;
	}

	return true;
}

//===============================================
// �_���[�W
//===============================================
void CEnemy::Damage(void)
{
	if (m_Info.state != STATE_NORMAL) {
		return;
	}

	m_Info.state = STATE_DAMAGE;
	m_Info.fStateCounter = DAMAGE_APPEAR;
	m_headState = HEADSTATE_DAMAGE;
	m_nLife--;

	if (m_nLife <= 0) {
		m_Info.state = STATE_DEATH;
	}
}