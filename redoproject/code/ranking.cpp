//===============================================
//
// �����L���O��ʂ̊Ǘ����� [ranking.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "ranking.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"
#include "result.h"
#include "time.h"
#include "camera.h"
#include "meshdome.h"
#include "fileload.h"
#include "score.h"

// �}�N����`
#define RANKING_FILE	"data\\FILE\\ranking.bin"	// �����L���O�t�@�C��
#define MOVE_TIMER	(660)

namespace
{
	const char* FILEPASS = "data\\TXT\\player";	// �t�@�C���̃p�X
	const char* FILEEXT = ".txt";				// �t�@�C���̊g���q
	const int FILEPASS_SIZE = (200);			// �t�@�C���̃p�X�T�C�Y
}

int CRanking::m_nScore = 0;

//===============================================
// �R���X�g���N�^
//===============================================
CRanking::CRanking()
{
	m_pMeshSky = NULL;
	m_nTimer = 0;
}

//===============================================
// �f�X�g���N�^
//===============================================
CRanking::~CRanking()
{

}

//===============================================
// ����������
//===============================================
HRESULT CRanking::Init(void)
{
	int aScore[NUM_RANK] = {};	// �X�R�A�i�[�p
	m_nRank = -1;	//�����N�C�����ĂȂ����

	// �O���t�@�C���ǂݍ��݂̐���
	CFileLoad::GetInstance()->OpenFile("data\\TXT\\model.txt");

	// �f�[�^�̓ǂݍ���
	Load(&aScore[0]);

	// �f�[�^�̃\�[�g
	Sort(&aScore[0]);

	// �����N�C���m�F
	RankIn(&aScore[0], m_nScore);

	// ���S�̐���
	CObject2D* p = CObject2D::Create(7);
	p->BindTexture(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\ranking_logo.png"));
	p->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.125f, 0.0f));
	p->SetSize(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.11f);

	// ���ʕ��X�R�A�̐���
	for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
	{
		if (m_apScore[nCntRank] == NULL)
		{
			m_apScore[nCntRank] = CScore::Create(D3DXVECTOR3(350.0f, 250.0f + nCntRank * 100.0f, 0.0f), 8, 1.0f, 40.0f, 80.0f);
			m_apScore[nCntRank]->SetScore(aScore[nCntRank]);

			if (m_nRank == nCntRank)
			{
				m_apScore[nCntRank]->SetClo(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));
			}
		}
	}

	CMeshDome::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15000.0f, 3000.0f, 3, 8, 8);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CRanking::Uninit(void)
{
	for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
	{
		if (m_apScore[nCntRank] != NULL)
		{
			m_apScore[nCntRank]->Uninit();
			delete m_apScore[nCntRank];	// �������̊J��
			m_apScore[nCntRank] = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
		}
	}

	CFileLoad::Release();
	CManager::GetInstance()->GetSound()->Stop();
	CManager::GetInstance()->GetCamera()->SetActive(true);
	m_nScore = 0;
}

//===============================================
// �X�V����
//===============================================
void CRanking::Update(void)
{
	m_nTimer++;

	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) || m_nTimer > MOVE_TIMER
		|| CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_A, 0) || CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_START, 0))
	{
		CManager::GetInstance()->GetFade()->Set(CScene::MODE_TITLE);
	}

	CScene::Update();
}

//===============================================
// �`�揈��
//===============================================
void CRanking::Draw(void)
{
	CScene::Draw();
}

//===============================================
// �����L���O�f�[�^�ۑ�
//===============================================
void CRanking::Save(int* pScore)
{
	FILE* pFile;

	pFile = fopen(RANKING_FILE, "wb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 //�f�[�^��ǂݍ���
		fwrite(pScore, sizeof(int), NUM_RANK, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
}

//===============================================
// �����L���O�f�[�^�ǂݍ���
//===============================================
void CRanking::Load(int* pScore)
{
	FILE* pFile;

	pFile = fopen(RANKING_FILE, "rb");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 //�f�[�^��ǂݍ���
		fread(pScore, sizeof(int), NUM_RANK, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
	 //�v�f�����Ă���
		for (int nCntRanking = 0; nCntRanking < NUM_RANK; nCntRanking++)
		{
			pScore[nCntRanking] = 1000 + (1000 * nCntRanking);
		}
	}
}

//===============================================
// �����L���O�f�[�^�\�[�g
//===============================================
void CRanking::Sort(int* pScore)
{
	// �~���\�[�g
	for (int nCntFst = 0; nCntFst < NUM_RANK - 1; nCntFst++)
	{
		int nTempNum = nCntFst;	// ���̈�ԑ傫���ԍ�

		for (int nCntSec = nCntFst + 1; nCntSec < NUM_RANK; nCntSec++)
		{
			if (pScore[nCntSec] > pScore[nTempNum])
			{// �l���傫���ꍇ
				nTempNum = nCntSec;	// �傫���ԍ���ύX
			}
		}

		if (nTempNum != nCntFst)
		{// �ύX����ꍇ
			int nTemp = pScore[nCntFst];
			pScore[nCntFst] = pScore[nTempNum];
			pScore[nTempNum] = nTemp;
		}
	}
}

//===============================================
// �����L���O�C���m�F
//===============================================
void CRanking::RankIn(int* pScore, int nRanking)
{
	if (nRanking > pScore[NUM_RANK - 1] && nRanking != 0)
	{
		pScore[NUM_RANK - 1] = nRanking;

		// �\�[�g����
		Sort(pScore);

		// �ۑ�����
		Save(pScore);

		//�����N�C���������ʂ��m�F����
		for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
		{
			if (pScore[nCntRank] == nRanking)
			{
				m_nRank = nCntRank;	// �����N�C���������ʂ�ۑ�			
				break;
			}
		}
	}
}