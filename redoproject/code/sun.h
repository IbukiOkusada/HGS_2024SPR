//==========================================================
//
// ���z�^�X�N [sun.h]
// Author : Riku Nakamura
//
//==========================================================
#ifndef _SUN_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _SUN_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"
//#include "task.h"	// ����Ńt�@�C���C���N���[�h�ł��܂�

//==========================================================
// ���z�̃N���X��`
//==========================================================
class CSunTask : public CTask
{

public:	// �N�ł��A�N�Z�X�\

	CSunTask();	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CSunTask();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CSunTask *Create(void);

	// �����o�֐�(�擾)

	// �����o�֐�(�ݒ�)

private:	// �����������A�N�Z�X�\

	// �����o�֐�

	// �����o�ϐ�
};

#endif
