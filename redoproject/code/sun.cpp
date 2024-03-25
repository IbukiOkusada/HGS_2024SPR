//==========================================================
//
// 太陽タスク [sun.cpp]
// Author : Riku Nakamura
//
//==========================================================
#include "sun.h"

// マクロ定義

//==========================================================
// コンストラクタ
//==========================================================
CSunTask::CSunTask()
{
	// 値のクリア
}

//==========================================================
// デストラクタ
//==========================================================
CSunTask::~CSunTask()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CSunTask::Init(void)
{
	SunObject = CObjectX::Create(D3DXVECTOR3(150.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data/MODEL/30msphere", 4);

	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CSunTask::Uninit(void)
{
	Release();
}

//==========================================================
// 更新処理
//==========================================================
void CSunTask::Update(void)
{
	// 太陽の位置決定
	D3DXVECTOR3 PosSun;
	PosSun = PosRelativeMtx(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SunObject->GetPosition());

	// 位置代入
	SunObject->SetPosition(PosSun);
}

//==========================================================
// 生成
//==========================================================
CSunTask *CSunTask::Create(void)
{
	CSunTask *pSampleTask = nullptr;

	pSampleTask = new CSunTask;

	if (pSampleTask != nullptr)
	{
		// 初期化処理
		pSampleTask->Init();
	}

	return pSampleTask;
}

//========================================
// 3次元空間での行列による回転座標変換関数
// (任意の点からのオフセット位置を角度と距離で変換)
//========================================
D3DXVECTOR3 CSunTask::PosRelativeMtx(D3DXVECTOR3 posO, D3DXVECTOR3 rotO, D3DXVECTOR3 offset)
{
	D3DXVECTOR3 posAnswer;
	D3DXMATRIX mtxO, mtxAnswer;
	D3DXMATRIX mtxRot, mtxTrans;		// 計算用マトリックス
	D3DXMATRIX mtxRotModel, mtxTransModel, mtxPalent;		// 計算用マトリックス

	// パーツのワールドマトリックス初期化
	D3DXMatrixIdentity(&mtxO);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		rotO.y, rotO.x, rotO.z);
	D3DXMatrixMultiply(&mtxO, &mtxO, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTransModel,
		posO.x, posO.y, posO.z);
	D3DXMatrixMultiply(&mtxO, &mtxO, &mtxTransModel);

	// 親に設定
	mtxPalent = mtxO;

	// パーツのワールドマトリックス初期化
	D3DXMatrixIdentity(&mtxAnswer);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		3.14f, 3.14f, 3.14f);
	D3DXMatrixMultiply(&mtxO, &mtxO, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTransModel,
		offset.x, offset.y, offset.z);
	D3DXMatrixMultiply(&mtxAnswer, &mtxAnswer, &mtxTransModel);

	// 算出したパーツのワールドマトリックスと親のマトリックスをかけ合わせる
	D3DXMatrixMultiply(&mtxAnswer,
		&mtxAnswer,
		&mtxPalent);

	// 返り値に代入
	posAnswer.x = mtxAnswer._41;
	posAnswer.y = mtxAnswer._42;
	posAnswer.z = mtxAnswer._43;

	return posAnswer;
}
