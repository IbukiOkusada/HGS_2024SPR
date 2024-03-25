//==========================================================
//
// ���z�^�X�N [sun.cpp]
// Author : Riku Nakamura
//
//==========================================================
#include "sun.h"
#include "enemy.h"
#include "manager.h"
#include "time.h"
#include "object2D.h"
#include "flower.h"

// �}�N����`
#define SUN_SPEED (0.000872f)	//���z�̉�]���x
#define SUN_ANGLE (1.44f)	//���z�̎��ɑ΂���p�x

//==========================================================
// �R���X�g���N�^
//==========================================================
CSunTask::CSunTask()
{
	// �l�̃N���A
	Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CSunTask::~CSunTask()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CSunTask::Init(void)
{
	SunObject = CObjectX::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data/MODEL/sun.x", 4);

	Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CSunTask::Uninit(void)
{
	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CSunTask::Update(void)
{
	// ���z�̈ʒu����
	D3DXVECTOR3 SunPos;
	SunPos = PosRelativeMtx(D3DXVECTOR3(0.0f, 0.0f, 0.0f), Rot, D3DXVECTOR3(8000.0f, 0.0f, 0.0f));
	SunPos.y += 1400.0f;
	float rotOld = Rot.z;

	// ��]������
	Rot.x = SUN_ANGLE;
	Rot.z += SUN_SPEED;

	// ��]�␳
	if (Rot.z > D3DX_PI)
	{
		Rot.z -= D3DX_PI * 2.0f;
	}

	int interbal = (int)(Rot.z * 1000000.0f) / 872;
	if (interbal % 360 == 0)
	{
		float posrandX = (float)(rand() % 4000 - 2000);
		float posrandZ = (float)(rand() % 4000 - 2000);
		CEnemy::Create(D3DXVECTOR3(posrandX, 0.0f, posrandZ), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		for (int nCnt = 0; nCnt < 7; nCnt++)
		{
			D3DXVECTOR3 pos = { 0.0f, -10.0f, 0.0f };
			D3DXVECTOR3 rot = { 0.0f, 0.0f, 0.0f };
			rot.y = static_cast<float>(rand() % 628 - 314) * 0.01f;
			pos.x = static_cast<float>(rand() % 5000 - 2500);
			pos.z = static_cast<float>(rand() % 5000 - 2500);
			CFlower::Create(pos, rot);
		}
	}

	// �ʒu���
	SunObject->SetPosition(SunPos);
	SunObject->SetRotation(D3DXVECTOR3(0.0f, -Rot.z + (D3DX_PI * -0.5f), -Rot.z * 4.0f));
}

//==========================================================
// ����
//==========================================================
CSunTask *CSunTask::Create(void)
{
	CSunTask *pSunTask = nullptr;

	pSunTask = new CSunTask;

	if (pSunTask != nullptr)
	{
		// ����������
		pSunTask->Init();
	}

	return pSunTask;
}

//========================================
// 3������Ԃł̍s��ɂ���]���W�ϊ��֐�
// (�C�ӂ̓_����̃I�t�Z�b�g�ʒu���p�x�Ƌ����ŕϊ�)
//========================================
D3DXVECTOR3 CSunTask::PosRelativeMtx(D3DXVECTOR3 posO, D3DXVECTOR3 rotO, D3DXVECTOR3 offset)
{
	D3DXVECTOR3 posAnswer;
	D3DXMATRIX mtxO, mtxAnswer;
	D3DXMATRIX mtxRot, mtxTrans;		// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRotModel, mtxTransModel, mtxPalent;		// �v�Z�p�}�g���b�N�X

	// �p�[�c�̃��[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&mtxO);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		rotO.y, rotO.x, rotO.z);
	D3DXMatrixMultiply(&mtxO, &mtxO, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTransModel,
		posO.x, posO.y, posO.z);
	D3DXMatrixMultiply(&mtxO, &mtxO, &mtxTransModel);

	// �e�ɐݒ�
	mtxPalent = mtxO;

	// �p�[�c�̃��[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&mtxAnswer);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		3.14f, 3.14f, 3.14f);
	D3DXMatrixMultiply(&mtxO, &mtxO, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTransModel,
		offset.x, offset.y, offset.z);
	D3DXMatrixMultiply(&mtxAnswer, &mtxAnswer, &mtxTransModel);

	// �Z�o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
	D3DXMatrixMultiply(&mtxAnswer,
		&mtxAnswer,
		&mtxPalent);

	// �Ԃ�l�ɑ��
	posAnswer.x = mtxAnswer._41;
	posAnswer.y = mtxAnswer._42;
	posAnswer.z = mtxAnswer._43;

	return posAnswer;
}
