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
#include "sound.h"
#include "model.h"
#include "particle.h"
#include "effect.h"
#include <math.h>
#include "meshwall.h"
#include "player_manager.h"
#include "fade.h"

//===============================================
// �}�N����`
//===============================================
#define MOVE	(3.5f)		// �ړ���
#define GRAVITY	(-0.6f)		//�v���C���[�d��
#define ROT_MULTI	(0.1f)	// �����␳�{��
#define WIDTH	(20.0f)		// ��
#define HEIGHT	(80.0f)		// ����
#define INER	(0.3f)		// ����
#define JUMP	(16.0f)

namespace {
	const int HEADPARTS_IDX = (1);	// ���̃p�[�c�C���f�b�N�X
	const float DAMAGE_INTERVAL = (10.0f);	// �_���[�W�C���^�[�o��
	const float DAMAGE_APPEAR = (110.0f);	// ���G���ԃC���^�[�o��
	const float DEATH_INTERVAL = (120.0f);	// ���S�C���^�[�o��
	const float SPAWN_INTERVAL = (60.0f);	// �����C���^�[�o��
	const float SLIDING_INER = (0.015f);	// �X���C�f�B���O����
	const float SLIDING_MINMOVE = (1.0f);	// �X���C�f�B���O�\�Œ�ړ���
	const float SLIDING_STARTMOVE = (6.0f);	// �X���C�f�B���O�J�n�\�ړ���
	const float SLIDING_SPEED = (0.5f);
	const float WALLKICK_MOVE = (45.0f);	// �ǃL�b�N�ړ���
	const float WALLKICK_INER = (0.1f);		// �ǃL�b�N������
	const float WALLKICK_SPEED = (1.0f);	// �ǃL�b�N���ړ����x
	const float WALLSLIDE_GRAVITY = (-1.5f);	// �ǂ��蒆�������x
	const float WALLDUSH_GRAVITY = (-0.75f);
	const float SLIDEJUMP_INER = (0.02f);		// �X���C�f�B���O����
	const float SLIDEJUMP_GRAVITY = (-0.25f);	// �X���C�f�B���O�W�����v�d��
	const float SLIDEJUMP = (7.0f);				// �X���C�f�B���O�W�����v�W�����v��
	const float SLIDEJUMP_SPEED = (1.75f);		// �X���C�f�B���O�W�����v�ړ���
	const float WALLSLIDE_MOVE = (0.05f);		// �ǂ��肢�ǂ���傤
	const float WALLDUSH_MOVE = (5.0f);			// �Ǒ���ړ���
	const float CAMROT_INER = (0.2f);			// �J��������
	const float SLIDINNG_ROTZ = (D3DX_PI * 0.51f);	// �X���C�f�B���O�J�����p�x
	const float SLIDING_LENGTH = (200.0f);			//�X���C�f�B���O�J��������
	const float KICKUP_SPEED = (1.5f);			// �R�肠����ړ����x
	const float KICKUP_JUMP = (18.0f);			// �R�肠����W�����v��
	const float KICKUP_QUICKJUMP = (13.0f);		// ���C�_�[�L�b�N����̃W�����v��
	const float AXEKICK_ROTZ = (D3DX_PI * 0.21f);	// �����Ɨ��Ƃ��J����
	const float RIDERKICK_ROTZ = (D3DX_PI * 0.31f);	// ���C�_�[�L�b�N�J��������
	const float AXEKICK_CAMERALENGTH = (400.0f);	// �����Ɨ��Ƃ��J��������
	const float SLOW_KICKCHARGE = (15.0f);			// �X���[�܂ł̃`���[�W����
	const float KICK_LENGTH = (1000.0f);	// �U���͈�
	const float RIDERKICK_SPEED = (24.0f);	// ���C�_�[�L�b�N���x
	const float RIDERKICK_HIGHSPEED = (60.0f);	// ���C�_�[�L�b�N�ő�
	const float RIDERKICK_CAMERALENGTH = (600.0f);	// ���C�_�[�L�b�N�J��������
	const float WALLKICK_GRAVITY = (-0.4f);
	const float WALLKICK_JUMP = (11.0f);
	const float AXEKICK_GRAVITY = (-2.5f);
	const float AXEKICK_MOVE = (0.75f);
	const int LIFE = (10);
	const float KICK_STEPMOVE = (45.0f);
	const float ATK_INTERVAL = (5.0f);
	const float CEILING_ROTZ = (D3DX_PI * 0.65f);
	const float CEILING_MOVE = (MOVE * 0.5f);
	const float CEILING_CAMLENGTH = (300.0f);
	const D3DXVECTOR3 LIFEUI_POS = { SCREEN_WIDTH * 0.175f, SCREEN_HEIGHT * 0.9f, 0.0f };
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
	m_Info.fSlideMove = 0.0f;

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
	// ���̐���

	m_Info.state = STATE_APPEAR;
	m_type = TYPE_NONE;
	

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

	if (m_type == TYPE_ACTIVE)
	{
		
		// �v���C���[����
		Controller();

		// �I�����C�����M
		CManager::GetInstance()->GetScene()->SendPosition(m_Info.pos);
		CManager::GetInstance()->GetScene()->SendRotation(m_Info.rot);
	}
	else {

	}
	
	SetMatrix();
}

//===============================================
// ����
//===============================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, const char *pBodyName, const char *pLegName)
{
	CPlayer *pPlayer = nullptr;

	// �I�u�W�F�N�g2D�̐���
	pPlayer = new CPlayer();

	if (nullptr != pPlayer)
	{// �����ł����ꍇ
		// ����������
		pPlayer->Init(pBodyName, pLegName);

		// ���W�ݒ�
		pPlayer->SetPosition(pos);

		// �����ݒ�
		pPlayer->SetRotation(rot);

		pPlayer->m_fRotDest = rot.y;

		// �ړ��ʐݒ�
		pPlayer->SetMove(move);
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
	float fIner = INER;
	m_fRotMove = rot.y;	//���݂̌������擾
}

//===============================================
// �ړ�
//===============================================
void CPlayer::Move(void)
{
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	// ���͑��u�m�F
	if (nullptr == pInputKey){
		return;
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
		}
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
