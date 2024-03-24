//==========================================================
//
// �G�}�l�[�W���[ [Player_manager.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "player_manager.h"
#include "player.h"

// �ÓI�����o�ϐ��錾
CPlayerManager* CPlayerManager::m_pInstance = nullptr;	// �C���X�^���X

//==========================================================
// �R���X�g���N�^
//==========================================================
CPlayerManager::CPlayerManager()
{
	// �l�̃N���A
	m_pCur = nullptr;
	m_pTop = nullptr;
	m_nNum = 0;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CPlayerManager::~CPlayerManager()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CPlayerManager::Init(void)
{
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CPlayerManager::Uninit(void)
{

}

//==========================================================
// �X�V����
//==========================================================
void CPlayerManager::Update(void)
{

}

//==========================================================
// �C���X�^���X���m��
//==========================================================
CPlayerManager* CPlayerManager::GetInstance(void)
{
	if (m_pInstance == nullptr) {	// �g���Ă��Ȃ�
		m_pInstance = new CPlayerManager;
	}

	return m_pInstance;
}

//==========================================================
// �C���X�^���X�������[�X
//==========================================================
void CPlayerManager::Release(void)
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
void CPlayerManager::ListIn(CPlayer* pPlayer)
{
	if (m_pTop != nullptr)
	{// �擪�����݂��Ă���ꍇ
		m_pCur->SetNext(pPlayer);	// ���ݍŌ���̃I�u�W�F�N�g�̃|�C���^�ɂȂ���
		pPlayer->SetPrev(m_pCur);
		m_pCur = pPlayer;	// �������g���Ō���ɂȂ�
	}
	else
	{// ���݂��Ȃ��ꍇ
		m_pTop = pPlayer;	// �������g���擪�ɂȂ�
		m_pCur = pPlayer;	// �������g���Ō���ɂȂ�
	}

	m_nNum++;
}

//==========================================================
// ���X�g����O��
//==========================================================
void CPlayerManager::ListOut(CPlayer* pPlayer)
{
	// ���X�g���玩�����g���폜����
	if (m_pTop == pPlayer)
	{// ���g���擪
		if (pPlayer->GetNext() != nullptr)
		{// �������݂��Ă���
			m_pTop = pPlayer->GetNext();	// ����擪�ɂ���
			m_pTop->SetPrev(nullptr);	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_pTop = nullptr;	// �擪���Ȃ���Ԃɂ���
			m_pCur = nullptr;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else if (m_pCur == pPlayer)
	{// ���g���Ō��
		if (pPlayer->GetPrev() != nullptr)
		{// �������݂��Ă���
			m_pCur = pPlayer->GetPrev();		// �O���Ō���ɂ���
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
		if (pPlayer->GetNext() != nullptr)
		{
			pPlayer->GetNext()->SetPrev(pPlayer->GetPrev());	// ���g�̎��ɑO�̃|�C���^���o��������
		}
		if (pPlayer->GetPrev() != nullptr)
		{
			pPlayer->GetPrev()->SetNext(pPlayer->GetNext());	// ���g�̑O�Ɏ��̃|�C���^���o��������
		}
	}

	m_nNum--;
}

//==========================================================
// �U���q�b�g�m�F
//==========================================================
bool CPlayerManager::Hit(D3DXVECTOR3& pos, const float fRange, const float fHeight, const int nDamage)
{
	CPlayer* pPlayer = m_pTop;
	bool bUse = false;

	//�ʔ���
	while (pPlayer != nullptr) {
		CPlayer* pPlayerNext = pPlayer->GetNext();
		//if (pPlayer->HitCheck(pos, fRange, fHeight, nDamage)) {
			//bUse = true;
		//}
		pPlayer = pPlayerNext;
	}

	return bUse;
}