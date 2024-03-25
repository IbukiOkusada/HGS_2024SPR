//==========================================================
//
// �G�l�~�[�}�l�[�W���[ [enemy_manager.cpp]
// Author : Riku Nakamura
//
//==========================================================
#include "enemy_manager.h"
#include "enemy.h"

// �ÓI�����o�ϐ��錾
CEnemyManager* CEnemyManager::m_pInstance = nullptr;	// �C���X�^���X

//==========================================================
// �R���X�g���N�^
//==========================================================
CEnemyManager::CEnemyManager()
{
	// �l�̃N���A
	m_pCur = nullptr;
	m_pTop = nullptr;
	m_nNum = 0;
	m_nCntSleep = 0;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CEnemyManager::~CEnemyManager()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CEnemyManager::Init(void)
{
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CEnemyManager::Uninit(void)
{

}

//==========================================================
// �X�V����
//==========================================================
void CEnemyManager::Update(void)
{
	m_nCntSleep--;

	if (m_nCntSleep < 0)
	{
		m_nCntSleep = 0;
	}
}

//==========================================================
// �C���X�^���X���m��
//==========================================================
CEnemyManager* CEnemyManager::GetInstance(void)
{
	if (m_pInstance == nullptr) {	// �g���Ă��Ȃ�
		m_pInstance = new CEnemyManager;
	}

	return m_pInstance;
}

//==========================================================
// �C���X�^���X�������[�X
//==========================================================
void CEnemyManager::Release(void)
{
	if (m_pInstance != nullptr) {	// �C���X�^���X���m�ۂ���Ă���
		m_pInstance->Uninit();
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

//==========================================================
// ���X�g�ɑ}��
//==========================================================
void CEnemyManager::ListIn(CEnemy* pEnemy)
{
	if (m_pTop != nullptr)
	{// �擪�����݂��Ă���ꍇ
		m_pCur->SetNext(pEnemy);	// ���ݍŌ���̃I�u�W�F�N�g�̃|�C���^�ɂȂ���
		pEnemy->SetPrev(m_pCur);
		m_pCur = pEnemy;	// �������g���Ō���ɂȂ�
	}
	else
	{// ���݂��Ȃ��ꍇ
		m_pTop = pEnemy;	// �������g���擪�ɂȂ�
		m_pCur = pEnemy;	// �������g���Ō���ɂȂ�
	}

	m_nNum++;
}

//==========================================================
// ���X�g����O��
//==========================================================
void CEnemyManager::ListOut(CEnemy* pEnemy)
{
	// ���X�g���玩�����g���폜����
	if (m_pTop == pEnemy)
	{// ���g���擪
		if (pEnemy->GetNext() != nullptr)
		{// �������݂��Ă���
			m_pTop = pEnemy->GetNext();	// ����擪�ɂ���
			m_pTop->SetPrev(nullptr);	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = nullptr;	// �擪���Ȃ���Ԃɂ���
			m_pCur = nullptr;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else if (m_pCur == pEnemy)
	{// ���g���Ō��
		if (pEnemy->GetPrev() != nullptr)
		{// �������݂��Ă���
			m_pCur = pEnemy->GetPrev();		// �O���Ō���ɂ���
			m_pCur->SetNext(nullptr);			// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = nullptr;	// �擪���Ȃ���Ԃɂ���
			m_pCur = nullptr;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else
	{
		if (pEnemy->GetNext() != nullptr)
		{
			pEnemy->GetNext()->SetPrev(pEnemy->GetPrev());	// ���g�̎��ɑO�̃|�C���^���o��������
		}
		if (pEnemy->GetPrev() != nullptr)
		{
			pEnemy->GetPrev()->SetNext(pEnemy->GetNext());	// ���g�̑O�Ɏ��̃|�C���^���o��������
		}
	}

	m_nNum--;
}

//==========================================================
// �U���q�b�g�m�F
//==========================================================
bool CEnemyManager::Hit(D3DXVECTOR3& pos, const float fRange, const float fHeight, const int nDamage)
{
	CEnemy* pEnemy = m_pTop;
	bool bUse = false;

	//�ʔ���
	while (pEnemy != nullptr) {
		CEnemy* pEnemyNext = pEnemy->GetNext();
		//if (pEnemy->HitCheck(pos, fRange, fHeight, nDamage)) {
			//bUse = true;
		//}
		pEnemy = pEnemyNext;
	}

	return bUse;
}