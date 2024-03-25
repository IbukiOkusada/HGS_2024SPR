//==========================================================
//
// ���z�^�X�N [sun.h]
// Author : Riku Nakamura
//
//==========================================================
#ifndef _SUN_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _SUN_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "task.h"
#include "objectX.h"
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
	CObjectX* GetSunObject(void) { return SunObject; }
	D3DXVECTOR3 GetSunRot(void) { return Rot; }

	// �����o�֐�(�ݒ�)

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	D3DXVECTOR3 PosRelativeMtx(D3DXVECTOR3 posO, D3DXVECTOR3 rotO, D3DXVECTOR3 offset);

	// �����o�ϐ�
	CObjectX *SunObject;
	D3DXVECTOR3 Rot;
};

#endif
