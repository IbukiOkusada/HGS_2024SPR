//==========================================================
//
// ���z�^�X�N [sun.cpp]
// Author : Riku Nakamura
//
//==========================================================
#include "sun.h"

// �}�N����`

//==========================================================
// �R���X�g���N�^
//==========================================================
CSunTask::CSunTask()
{
	// �l�̃N���A
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
	SunObject = CObjectX::Create(D3DXVECTOR3(150.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data/MODEL/30msphere", 4);

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
	D3DXVECTOR3 PosSun;
	PosSun = PosRelativeMtx(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SunObject->GetPosition());

	// �ʒu���
	SunObject->SetPosition(PosSun);
}

//==========================================================
// ����
//==========================================================
CSunTask *CSunTask::Create(void)
{
	CSunTask *pSampleTask = nullptr;

	pSampleTask = new CSunTask;

	if (pSampleTask != nullptr)
	{
		// ����������
		pSampleTask->Init();
	}

	return pSampleTask;
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
