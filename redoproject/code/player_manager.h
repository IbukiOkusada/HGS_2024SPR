//==========================================================
//
// �v���C���[�}�l�[�W���[ [player_manager.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _PLAYERMANAGER_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _PLAYERMANAGER_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

// �O���錾
class CPlayer;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CPlayerManager
{
private:

	CPlayerManager();		// �R���X�g���N�^
	~CPlayerManager();	// �f�X�g���N�^

public:	// �N�ł��A�N�Z�X�\

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CPlayerManager* GetInstance(void);
	static void Release(void);
	CPlayer* GetTop(void) { return m_pTop; }
	CPlayer* GetCur(void) { return m_pCur; }
	void ListIn(CPlayer* pPlayer);
	void ListOut(CPlayer* pPlayer);
	int GetNum(void) { return m_nNum; }
	bool Hit(D3DXVECTOR3& pos, const float fRange, const float fHeight, const int nDamage);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	// 
	// �����o�ϐ�
	CPlayer* m_pTop;	// �擪
	CPlayer* m_pCur;	// �Ō��
	int m_nNum;
	static CPlayerManager* m_pInstance;	// �C���X�^���X
};

#endif
