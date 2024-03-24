//===============================================
//
// �^�C�g����ʂ̊Ǘ����� [title.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "title.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"

//===============================================
// �������O���
//===============================================
namespace {
	const D3DXVECTOR3 ENTERPOS = { 0.0f, 0.0f, 0.0f };	// ENTER ���W
	const D3DXVECTOR3 ENTERROT = { 0.0f, 0.0f, 0.0f };	// ENTER ����
	const int AUTOMOVE_RANKING = 640;	// �����L���O�����J�ڎ���
	const int MOVE_TUTORIAL = 120;		// �`���[�g���A���ɑJ�ڂ���܂ł̎���
	const int PLAYER_WALLKICKTIMER = 40;
	const int ENEMY_NUM = 3;			//���o�p�G�o����
	const char* FILEPASS = "data\\TXT\\player";	// �t�@�C���̃p�X
	const char* FILEEXT = ".txt";				// �t�@�C���̊g���q
	const int FILEPASS_SIZE = (200);			// �t�@�C���̃p�X�T�C�Y
}

//===============================================
// �R���X�g���N�^
//===============================================
CTitle::CTitle()
{
	m_nCounterRanking = 0;
	m_nCounterTutorial = 0;
	m_nCounterRanking = 0;
	m_bPush = false;
	m_pFileLoad = nullptr;
	m_pEnter = nullptr;
}

//===============================================
// �f�X�g���N�^
//===============================================
CTitle::~CTitle()
{

}

//===============================================
// ����������
//===============================================
HRESULT CTitle::Init(void)
{

	// �J�����̏����ʒu�ݒ�
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->SetPositionV(D3DXVECTOR3(-874.3f, 1124.15f, 1717.2f));
	pCamera->SetPositionR(D3DXVECTOR3(80.0f, 95.0f, 220.0f));
	pCamera->SetLength(350.0f);
	pCamera->SetRotation(D3DXVECTOR3(0.0f, -2.1f, 1.79f));
	pCamera->SetActive(false);

	// �J�ڃ^�C�}�[�ݒ�
	m_nCounterTutorial = MOVE_TUTORIAL;
	m_nCounterRanking = AUTOMOVE_RANKING;

	// �T�E���h�Đ�
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_TITLE);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CTitle::Uninit(void)
{
	CManager::GetInstance()->GetSound()->Stop();
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->SetActive(true);
}

//===============================================
// �X�V����
//===============================================
void CTitle::Update(void)
{
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();

	if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_START, 0)) {
		m_bPush = true;
	}

	if (m_bPush) {
		m_nCounterTutorial--;
		if (m_nCounterTutorial <= 0) {
			CManager::GetInstance()->GetFade()->Set(CScene::MODE_GAME);
		}
	}
	else {
		m_nCounterRanking--;
		if (m_nCounterRanking <= 0) {
			CManager::GetInstance()->GetFade()->Set(CScene::MODE_RANKING);
		}
	}

	CScene::Update();
}

//===============================================
// �`�揈��
//===============================================
void CTitle::Draw(void)
{
	CScene::Draw();
}
