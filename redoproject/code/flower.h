//==========================================================
//
// �Ԃ̏��� [flower.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _SAMPLETASK_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _SAMPLETASK_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"	// ����Ńt�@�C���C���N���[�h�ł��܂�

// �O���錾
class CModel;

//==========================================================
// �T���v���̃N���X��`
//==========================================================
class CFlower : public CTask
{
public:

	// ���
	enum TYPE {
		TYPE_SPEED = 0,	// ���x
		TYPE_GROWSPEED,	// �������x
		TYPE_SLEEP,		// ����
		TYPE_MAX
	};
public:	// �N�ł��A�N�Z�X�\

	CFlower();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CFlower();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CFlower *Create(const D3DXVECTOR3& pos,const D3DXVECTOR3& rot);

	// �����o�֐�(�擾)

	// �����o�֐�(�ݒ�)

private:	// �����������A�N�Z�X�\

	// �����o�֐�

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	CModel* m_pModel;
	int m_nType;
	bool m_bHit;
	static const char* m_apModelType[TYPE_MAX];	// ���f���t�@�C��
};

#endif
