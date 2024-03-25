//==========================================================
//
// 太陽タスク [sun.cpp]
// Author : Riku Nakamura
//
//==========================================================
#include "sun.h"
#include "enemy.h"
#include "manager.h"
#include "time.h"
#include "object2D.h"
#include "flower.h"

// マクロ定義
#define SUN_SPEED (0.000872f)	//太陽の回転速度
#define SUN_ANGLE (1.44f)	//太陽の軸に対する角度

//==========================================================
// コンストラクタ
//==========================================================
CSunTask::CSunTask()
{
	// 値のクリア
	Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	SunObject = CObjectX::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data/MODEL/sun.x", 4);

	Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	D3DXVECTOR3 SunPos;
	SunPos = PosRelativeMtx(D3DXVECTOR3(0.0f, 0.0f, 0.0f), Rot, D3DXVECTOR3(8000.0f, 0.0f, 0.0f));
	SunPos.y += 1400.0f;
	float rotOld = Rot.z;

	// 回転させる
	Rot.x = SUN_ANGLE;
	Rot.z += SUN_SPEED;

	// 回転補正
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

	// 位置代入
	SunObject->SetPosition(SunPos);
	SunObject->SetRotation(D3DXVECTOR3(0.0f, -Rot.z + (D3DX_PI * -0.5f), -Rot.z * 4.0f));
}

//==========================================================
// 生成
//==========================================================
CSunTask *CSunTask::Create(void)
{
	CSunTask *pSunTask = nullptr;

	pSunTask = new CSunTask;

	if (pSunTask != nullptr)
	{
		// 初期化処理
		pSunTask->Init();
	}

	return pSunTask;
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
