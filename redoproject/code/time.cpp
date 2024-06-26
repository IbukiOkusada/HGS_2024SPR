//===============================================
//
// タイムの処理 [time.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "time.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "number.h"
#include "object2D.h"
#include "slow.h"
#include "debugproc.h"

// マクロ定義
#define WIDTH	(60)	// 幅
#define X_SPACE	(50)	// 横の移動量
#define HEIGHT	(80)	// 高さ
#define NUM_WIDTH	(20)
#define NUM_HEIGHT	(40)

//===============================================
// コンストラクタ
//===============================================
CTime::CTime()
{
	// 値をクリア
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

	m_pSun = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNum = 0;
	m_fAnimTimer = 0.0f;
	m_nIdxTexture = -1;
	m_nMaxNum = 0;
	m_fDiff = 0.0f;
}

//===============================================
// デストラクタ
//===============================================
CTime::~CTime()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CTime::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	m_pSun = CObject2D::Create(5);
	m_pSun->BindTexture(pTexture->Regist("data\\TEXTURE\\timer000.png"));
	m_pSun->SetLength((HEIGHT + WIDTH) * 2, (HEIGHT + WIDTH) * 2);
	m_pSun->SetPosition(D3DXVECTOR3(m_pos.x + X_SPACE * 1.05f + NUM_WIDTH, m_pos.y - HEIGHT * 1.25f, 0.0f));
	m_pSun->SetVtx();
	
	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// 使用していない場合
			m_apNumber[nCnt]->Uninit();

			delete m_apNumber[nCnt];

			m_apNumber[nCnt] = NULL;
		}
	}
}

//===============================================
// 更新処理
//===============================================
void CTime::Update(void)
{
	m_fAnimTimer += CManager::GetInstance()->GetSlow()->Get();

	if (m_fAnimTimer >= 60)
	{// 12フレーム立った
		m_fAnimTimer = 0;	// カウンターリセット
		Add(1);
	}
}

//===============================================
// 生成
//===============================================
CTime *CTime::Create(D3DXVECTOR3 pos)
{
	CTime *pBg = NULL;

	// オブジェクト2Dの生成
	pBg = new CTime;

	if (pBg != NULL)
	{// 生成できた場合

		pBg->m_pos = pos;

		// 初期化処理
		pBg->Init();
	}
	else
	{// 生成に失敗した場合
		return NULL;
	}

	return pBg;
}

//===============================================
// 加算
//===============================================
void CTime::Add(int nValue)
{
	// 代入
	m_nNum += nValue;

	if (m_nNum % 10 == 0)
	{
		// 数値設定
		SetValue();
	}

	// 角度変更
	float fRot = m_pSun->GetRotation().y;
	m_fDiff = (float)(m_nNum - m_nSetNum) / (float)(m_nMaxNum - m_nSetNum);

	fRot = m_fDiff * (-D3DX_PI * 2);

	if (fRot < -D3DX_PI)
	{
		fRot += D3DX_PI * 2;
	}
	m_pSun->SetRotation(D3DXVECTOR3(0.0f, 0.0f, fRot));
	m_pSun->SetVtx();
}

//===============================================
// 設定
//===============================================
void CTime::Set(int nValue)
{
	// 代入
	m_nNum = nValue;
	m_nSetNum = nValue;

	// 数値設定
	SetValue();
}

//===============================================
// 桁ごとの値設定
//===============================================
void CTime::SetValue(void)
{
	int aTexU[NUM_PLACE] = {};	// 計算格納用

	if (m_nNum < 0)
	{// 0以下の場合
		m_nNum = 0;
	}
	else if (m_nNum >= 60 * 100)
	{
		m_nNum = 60 * 100 - 1;
	}

	//タイムを各配列に格納
	aTexU[0] = m_nNum / 60 / 10;
	aTexU[1] = m_nNum / 60 - aTexU[0] * 10;
	aTexU[2] = m_nNum % 60 / 10;
	aTexU[3] = m_nNum % 60 - aTexU[2] * 10;

	//スコアを各配列に格納
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// 使用されている場合
			// 値を設定
			m_apNumber[nCnt]->SetIdx(aTexU[nCnt]);
		}
	}
}
