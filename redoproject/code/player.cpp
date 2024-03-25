//===============================================
//
// �v���C���[�̏��� [player.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "player.h"
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
#include "player_manager.h"
#include "fade.h"
#include "camera_manager.h"
#include "camera.h"
#include "score.h"
#include "sun.h"
#include "result.h"

//===============================================
// �������O���
//===============================================
namespace {
	const float MOVE = (1.5f);	// �ړ���
	const float ROT_MULTI = (0.1f);	// �����␳�{��
	const float INER = (0.3f);		// ����
	const float DAMAGE_APPEAR = (40.0f);
	const int SETLIFE = (4);
	const int ADDSCORE = (3);
	const int SCOREBOOSTTIME = (300);
	const int SPEEDBOOSTTIME = (300);
}

namespace PLAYER
{
	const D3DXVECTOR3 COLLIMAX = { 20.0f, 70.0f, 20.0f };	// �ő哖���蔻��
	const D3DXVECTOR3 COLLIMIN = { -20.0f, 0.0f, -20.0f };	// �ŏ������蔻��
}

// �O���錾

//===============================================
// �R���X�g���N�^
//===============================================
//CPlayer::CPlayer()
//{
//	// �l���N���A����
//	m_nCounterAnim = 0;
//	m_nPatternAnim = 0;
//}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CPlayer::CPlayer()
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
	m_nSpeedUpCounter = 0;
	m_fSpeedBoost = 0;
	m_nScoreBoost = 0;
	m_nScoreUpCounter = 0;
	m_pArrow = nullptr;

	CPlayerManager::GetInstance()->ListIn(this);
}

//===============================================
// �f�X�g���N�^
//===============================================
CPlayer::~CPlayer()
{
	
}

//===============================================
// ����������
//===============================================
HRESULT CPlayer::Init(void)
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
	m_pBody = CCharacter::Create("data\\TXT\\motion_sunflowerman.txt");
	m_pBody->SetParent(m_pLeg->GetParts(2)->GetMtx());

	if (m_pBody->GetMotion() != nullptr)
	{
		// �������[�V�����̐ݒ�
		m_pBody->GetMotion()->InitSet(m_nMotion);
		m_pBody->GetParts(0)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	m_pArrow = CModel::Create("data\\MODEL\\arrow000.x");
	m_pArrow->SetParent(&m_Info.mtxWorld);
	m_pArrow->SetCurrentPosition(D3DXVECTOR3(0.0f, 0.0f, 50.0f));

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
HRESULT CPlayer::Init(const char *pBodyName, const char *pLegName)
{
	SetMatrix();

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CPlayer::Uninit(void)
{
	CPlayerManager::GetInstance()->ListOut(this);

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
void CPlayer::Update(void)
{	
	// �O��̍��W���擾
	m_Info.posOld = GetPosition();

	StateSet();	

	{
		
		// �v���C���[����
		Controller();

		// �I�����C�����M
		//CManager::GetInstance()->GetScene()->SendPosition(m_Info.pos);
		//CManager::GetInstance()->GetScene()->SendRotation(m_Info.rot);
	}
	
	// �J�����̒Ǐ]
	CManager::GetInstance()->GetCamera()->Update();
	D3DXVECTOR3 pos = GetPosition();
	pos.y += 70.0f;
	CManager::GetInstance()->GetCamera()->Pursue(pos, GetRotation(), 600.0f);

	// �u�[�X�g����
	if(m_nScoreUpCounter > 0){
		m_nScoreUpCounter--;
		if (m_nScoreUpCounter <= 0) {
			m_nScoreUpCounter = 0;
			m_nScoreBoost = 0;
		}
	}
	if (m_nSpeedUpCounter > 0) {
		m_nSpeedUpCounter--;
		if (m_nSpeedUpCounter <= 0) {
			m_nSpeedUpCounter = 0;
			m_fSpeedBoost = 0.0f;
		}
	}

	SetMatrix();
	BodySet();

	// �J�ԏ�Ԑݒ�
	HeadSun();

	// �X�R�A�ݒ�
	AddScore();
}

//===============================================
// ����
//===============================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = nullptr;

	// �I�u�W�F�N�g2D�̐���
	pPlayer = new CPlayer();

	if (nullptr != pPlayer)
	{// �����ł����ꍇ
		// ����������
		pPlayer->Init();

		// ���W�ݒ�
		pPlayer->SetPosition(pos);

		// �����ݒ�
		pPlayer->SetRotation(rot);

		pPlayer->m_fRotDest = rot.y;
	}
	else
	{// �����Ɏ��s�����ꍇ
		return nullptr;
	}

	return pPlayer;
}

//===============================================
// ���쏈��
//===============================================
void CPlayer::Controller(void)
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
		D3DXVECTOR3 vtxMax = PLAYER::COLLIMAX;
		D3DXVECTOR3 vtxMin = PLAYER::COLLIMIN;
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
void CPlayer::Move(void)
{
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();
	CCamera* pCamera = CManager::GetInstance()->GetCamera();		// �J�����̃|�C���^
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x
	float fSpeed = MOVE + m_fSpeedBoost;	// �ړ���

	// ���͑��u�m�F
	if (nullptr == pInputKey){
		return;
	}

	//�v���C���[�̍X�V
	if (pInputKey->GetPress(DIK_A) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_X, 0.5f, CInputPad::STICK_MINUS) == true)
	{
		if (pInputKey->GetPress(DIK_W) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_PLUS))
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 0.25f);
		}
		else if (pInputKey->GetPress(DIK_S) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_MINUS))
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.25f);
		}
		else
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = -CamRot.y;
		}

		// �ړ�������Ԃɂ���
		m_bMove = true;
	}
	else if (pInputKey->GetPress(DIK_D) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_X, 0.5f, CInputPad::STICK_PLUS) == true)
	{
		if (pInputKey->GetPress(DIK_W) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_PLUS))
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed;

			m_fRotDest = (-CamRot.y + D3DX_PI * 0.75f);
		}
		else if (pInputKey->GetPress(DIK_S) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_MINUS))
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed;

			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.75f);
		}
		else
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 1.0f);
		}

		// �ړ�������Ԃɂ���
		m_bMove = true;
	}
	else if (pInputKey->GetPress(DIK_W) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_PLUS))
	{
		m_Info.move.x += -cosf(CamRot.y) * fSpeed;
		m_Info.move.z += -sinf(CamRot.y) * fSpeed;
		m_fRotDest = (-CamRot.y + D3DX_PI * 0.5f);

		// �ړ�������Ԃɂ���
		m_bMove = true;

	}
	else if (pInputKey->GetPress(DIK_S) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_MINUS))
	{
		m_Info.move.x += cosf(CamRot.y) * fSpeed;
		m_Info.move.z += sinf(CamRot.y) * fSpeed;
		m_fRotDest = (-CamRot.y + -D3DX_PI * 0.5f);

		// �ړ�������Ԃɂ���
		m_bMove = true;
	}
}

//===============================================
// ��ԊǗ�
//===============================================
void CPlayer::StateSet(void)
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
			CResult::SetScore(m_pScore->GetScore());
		}
	}
		break;

	}

	switch (m_headState)
	{
	case CPlayer::HEADSTATE_NORMAL:		// �ڂ�
		if (m_pBody->GetMotion() != nullptr)
		{
			m_pBody->GetMotion()->BlendSet(0);
		}
		break;

	case CPlayer::HEADSTATE_FLOWERING:	// �J��
		if (m_pBody->GetMotion() != nullptr)
		{
			m_pBody->GetMotion()->BlendSet(1);
		}
		break;

	case CPlayer::HEADSTATE_DAMAGE:		// �_���[�W
		if (m_pBody->GetMotion() != nullptr)
		{
			m_pBody->GetMotion()->BlendSet(2);
		}
		break;
	}
}

//===============================================
// �̗͐ݒ�
//===============================================
void CPlayer::SetType(TYPE type)
{
	m_type = type;
}

//===============================================
// �}�g���b�N�X�ݒ�
//===============================================
void CPlayer::SetMatrix(void)
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
void CPlayer::SetMotion(int nMotion) {	
	
}

//===============================================
// �v���C���[�̕`��ݒ�
//===============================================
void CPlayer::SetDraw(bool bDraw)
{
	
}

//===============================================
// ����
//===============================================
void CPlayer::Adjust(void)
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
void CPlayer::BodySet(void)
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
bool CPlayer::BodyCheck(CCharacter* pBody)
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
// �X�R�A���Z
//===============================================
void CPlayer::AddScore(void){

	if (m_pScore == nullptr) {	// �X�R�A���Ȃ�
		return;
	}

	if (m_headState != HEADSTATE_FLOWERING) {	// �J�Ԃ��Ă��Ȃ�
		return;
	}

	// ���Z
	m_pScore->AddScore(ADDSCORE + m_nScoreBoost);
}
//===============================================
// �J�ԏ�Ԑݒ�
//===============================================
void CPlayer::HeadSun(void)
{
	// �e�ϐ�
	D3DXVECTOR3 posSun = CManager::GetInstance()->GetScene()->GetSun()->GetSunObject()->GetPosition();
	D3DXVECTOR3 posPlayer = GetPosition();
	float rotSunPlayer = atan2f(posPlayer.x - posSun.x, posPlayer.z - posSun.z);
	float rotSunPlayerDef = rotSunPlayer - GetRotation().y;

	if (m_pArrow != nullptr) {
		D3DXVECTOR3 ArrowRot = m_Info.rot;
		ArrowRot.y = rotSunPlayer - ArrowRot.y + -D3DX_PI * 0.5f;

		// ��]�␳
		if (ArrowRot.y > D3DX_PI)
		{
			ArrowRot.y -= D3DX_PI * 2.0f;
		}

		if (ArrowRot.y < -D3DX_PI)
		{
			ArrowRot.y += D3DX_PI * 2.0f;
		}
		m_pArrow->SetRotation(ArrowRot);
	}

	// ��]�␳
	if (rotSunPlayerDef > D3DX_PI)
	{
		rotSunPlayerDef -= D3DX_PI * 2.0f;
	}

	if (rotSunPlayerDef < -D3DX_PI)
	{
		rotSunPlayerDef += D3DX_PI * 2.0f;
	}

	CManager::GetInstance()->GetDebugProc()->Print("���z�Ƃ̊p�x[%f]\n", rotSunPlayer);
	CManager::GetInstance()->GetDebugProc()->Print("�v���C���[�̊p�x[%f, %f, %f]\n", GetRotation().x, GetRotation().y, GetRotation().z);
	CManager::GetInstance()->GetDebugProc()->Print("���z�Ƃ̊p�x��[%f]\n", rotSunPlayerDef);

	// �p�x�̍������l�ȓ��ŊJ�ԏ�Ԃ�
	if (rotSunPlayerDef < 0.7f && rotSunPlayerDef > -0.7f)
	{
		m_headState = HEADSTATE_FLOWERING;
		CManager::GetInstance()->GetDebugProc()->Print("�v���C���[�̏��[�J��]\n");
	}
	else
	{
		m_headState = HEADSTATE_NORMAL;
		CManager::GetInstance()->GetDebugProc()->Print("�v���C���[�̏��[�ʏ�]\n");
	}
}

//===============================================
// �_���[�W
//===============================================
void CPlayer::Damage(void)
{
	if (m_nScoreUpCounter) {

	}

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

//===============================================
// ���x����
//===============================================
void CPlayer::SpeedBoost(void)
{
	m_fSpeedBoost = MOVE * 0.5f;
	m_nSpeedUpCounter = SPEEDBOOSTTIME;
}

//===============================================
// �X�R�A����
//===============================================
void CPlayer::ScoreBoost(void)
{
	m_nScoreBoost += ADDSCORE;
	m_nScoreUpCounter = SCOREBOOSTTIME;
}