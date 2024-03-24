//===============================================
//
// �`���[�g���A����ʂ̊Ǘ����� [tutorial.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "time.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "Xfile.h"
#include "input.h"
#include "fade.h"
#include "result.h"
#include "debugproc.h"
#include "game.h"

// �������O���
namespace
{
	const char* FILEPASS = "data\\TXT\\player";	// �t�@�C���̃p�X
	const char* FILEEXT = ".txt";				// �t�@�C���̊g���q
	const int FILEPASS_SIZE = (200);	// �t�@�C���̃p�X�T�C�Y
	const D3DXVECTOR2 PORISIZE = D3DXVECTOR2(200.0f, 50.0f);
}

//===============================================
// �}�N����`
//===============================================

//===============================================
// �ÓI�����o�ϐ�
//===============================================

//===============================================
// �R���X�g���N�^
//===============================================
CTutorial::CTutorial()
{
	// �l�̃N���A
	m_pFileLoad = NULL;

	for (int i = 0; i < NUM_PLAYER; i++)
	{
		m_apObject[i] = nullptr;
	}

	for (int i = 0; i < NUM_PORI; i++)
	{
		m_pObject3D[i] = nullptr;
	}

	for (int i = 0; i < NUM_ENEMY; i++)
	{
		m_apEnemy[i] = nullptr;
	}
	
	m_nCntRespawn = 0;
	m_nEnemyId = 0;
	m_bEnd = false;
}

//===============================================
// �f�X�g���N�^
//===============================================
CTutorial::~CTutorial()
{

}

//===============================================
// ����������
//===============================================
HRESULT CTutorial::Init(void)
{
	return S_OK;
}

//===============================================
// �I������
//===============================================
void CTutorial::Uninit(void)
{
	CManager::GetInstance()->GetSound()->Stop();
	CManager::GetInstance()->GetCamera()->SetActive(true);
}

//===============================================
// �X�V����
//===============================================
void CTutorial::Update(void)
{
	if (CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_START, 0) || CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->GetFade()->Set(CScene::MODE_GAME);
	}

	bool bCreate = false;

	// �X�V����
	CScene::Update();
}

//===============================================
// �`�揈��
//===============================================
void CTutorial::Draw(void)
{
	// �`�揈��
	CScene::Draw();
}

//===================================================
// �t�@�C���ǂݍ��݂̎擾
//===================================================
CFileLoad *CTutorial::GetFileLoad(void)
{
	return m_pFileLoad;
}