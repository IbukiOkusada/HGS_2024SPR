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


	// �A�N�V�����񋓌^
	enum ACTION
	{
		ACTION_NEUTRAL = 0,		// �ҋ@
		ACTION_WALK,			// ���s
		ACTION_JUMP,			// �W�����v
		ACTION_SLIDING,			// �X���C�f�B���O
		ACTION_WALLSTAND,		// �ǂ���
		ACTION_WALLKICK,		// �ǃL�b�N
		ACTION_SLIDEJUMP,		// ���Ⴊ�݃W�����v
		ACTION_NORMALATK,		// �U��
		ACTION_WALLDUSH,		// �Ǒ���
		ACTION_CEILINGDUSH,		// �V�䑖��
		ACTION_KICKUP,			// �R�肠����
		ACTION_AXEKICK,			// �����Ɨ��Ƃ�
		ACTION_RIDERKICK,		// ���C�_�[�L�b�N
		ACTION_TITLENEUTRAL,	// �^�C�g���ҋ@
		ACTION_DAMAGE,			// �_���[�W
		ACTION_DEATH,			// �_�E��
		ACTION_MAX
	};

	// �U�����
	enum ATK
	{
		ATK_NORMAL = 0,	// �ʏ�
		ATK_AXEKICK,	// �����Ɨ��Ƃ�
		ATK_RIDERKICK,	// ���C�_�[�L�b�N
		ATK_SLOWKICK,	// �X���[���C�_�[�L�b�N
		ATK_MAX
	};

private:	// �����������A�N�Z�X�\�Ȓ�`

	// ��ԗ񋓌^
	enum STATE
	{
		STATE_APPEAR = 0,	// �o�����
		STATE_NORMAL,		// �ʏ���
		STATE_DAMAGE,		// �_���[�W���
		STATE_DEATH,		// ���S���
		STATE_SPAWN,		// ���������
		STATE_MAX
	};

	// ���\����
	struct SInfo
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 move;		// �ړ���
		float fSlideMove;		// �X���C�f�B���O�J�n�ړ���
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
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move,
		const char *pBodyName, const char *pLegName);

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

	// �����o�ϐ�
	CPlayer *m_pPrev;			// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CPlayer *m_pNext;			// ���̃I�u�W�F�N�g�ւ̃|�C���^
	SInfo m_Info;				// �������g�̏��
	float m_fRotMove;			// ���݂̊p�x
	float m_fRotDiff;			// �ړI�̊p�x
	float m_fRotDest;			// �p�x�v�Z
	int m_nId;					// ID
	TYPE m_type;
};

#endif