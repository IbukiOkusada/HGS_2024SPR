//==========================================================
//
// �v���C���[�̏��� [player.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _PLAYER_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _PLAYER_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "object.h"
#include "objectX.h"
#include "task.h"

// �O���錾
class CWaist;
class CCharacter;
class CScore;

// �}�N����`
#define MAX_ITEM  (1280)  // �����ł���A�C�e���̍ő吔

//==========================================================
// �v���C���[�̃N���X��`(�h���N���X)
//==========================================================
class CPlayer : public CTask
{
public:

	// �����ޗ񋓌^
	enum TYPE
	{
		TYPE_NONE,	// ����s�\
		TYPE_SEND,	// �f�[�^���M
		TYPE_ACTIVE,	// ����\
		TYPE_MAX
	};

private:	// �����������A�N�Z�X�\�Ȓ�`

	// ��ԗ񋓌^
	enum STATE
	{
		STATE_APPEAR = 0,	// �o�����
		STATE_NORMAL,		// �ʏ���
		STATE_OPEN,			// �J�ԏ��
		STATE_DAMAGE,		// �_���[�W���
		STATE_DEATH,		// ���S���
		STATE_MAX
	};

	// �������
	enum HEADSTATE
	{
		HEADSTATE_NORMAL = 0,	// �ڂ�
		HEADSTATE_FLOWERING,	// �J��
		HEADSTATE_DAMAGE,		// �_���[�W
		HEADSTATE_MAX
	};

	// ���\����
	struct SInfo
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 posOld;		// �ݒ�ʒu
		D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
		STATE state;			// ���
		float fStateCounter;	// ��ԊǗ��J�E���^�[
	};

public:	// �N�ł��A�N�Z�X�\

	CPlayer();	// �R���X�g���N�^
	~CPlayer();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	HRESULT Init(const char *pBodyName, const char *pLegName);	// �I�[�o�[���[�h
	void Uninit(void);
	void Update(void);
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	// �����o�֐�(�ݒ�)
	void SetMove(const D3DXVECTOR3 move) { m_Info.move = move; }
	void SetPosition(const D3DXVECTOR3 pos) { m_Info.pos = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	void SetType(TYPE type);
	void BindId(int nId) { m_nId = nId; }
	void SetMotion(int nMotion);
	void SetDraw(bool bDraw);
	void SetNext(CPlayer* pNext) { m_pNext = pNext; }
	void SetPrev(CPlayer* pPrev) { m_pPrev = pPrev; }
	void SetScore(CScore* pScore) { m_pScore = pScore; }
	void SetRotDiff(float fDiff) { m_fRotDest = fDiff; }

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }
	D3DXVECTOR3 GetRotation(void) { return m_Info.rot; }
	D3DXVECTOR3 GetOldPosition(void) { return m_Info.posOld; }
	CPlayer* GetNext(void) { return m_pNext; }
	CPlayer* GetPrev(void) { return m_pPrev; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void SetMatrix(void);
	void StateSet(void);
	void Controller(void);
	void Move(void);
	void Adjust(void);
	void BodySet(void);
	bool BodyCheck(CCharacter* pBody);
	void AddScore(void);
	void Damage(void);

	// �����o�ϐ�
	CPlayer *m_pPrev;			// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CPlayer *m_pNext;			// ���̃I�u�W�F�N�g�ւ̃|�C���^
	CCharacter* m_pBody;		// �㔼�g
	CCharacter* m_pLeg;			// �����g
	SInfo m_Info;				// �������g�̏��
	CScore* m_pScore;			// ���g�̃X�R�A
	float m_fRotMove;			// ���݂̊p�x
	float m_fRotDiff;			// �ړI�̊p�x
	float m_fRotDest;			// �p�x�v�Z
	bool m_bMove;				// �ړ��������ۂ�
	int m_nLife;				// �̗�
	int m_nId;					// ID
	int m_nMotion;
	TYPE m_type;
	HEADSTATE m_headState;
};

#endif
