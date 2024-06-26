//==========================================================
//
// タイムの処理 [time.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _TIME_H_	// このマクロが定義されていない場合
#define _TIME_H_	// 二重インクルード防止用マクロを定義

#include "main.h"

// 前方宣言
class CNumber;
class CObject2D;

//==========================================================
// テクスチャスライドオブジェクト(2D)のクラス定義(派生クラス)
//==========================================================
class CTime
{
public:	// ここから関数(誰でもアクセス可能)

	CTime();	// コンストラクタ
	~CTime();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CTime *Create(D3DXVECTOR3 pos);

	// メンバ関数
	void Add(int nValue);
	void Set(int nValue);
	void SetMax(int nValue) { m_nMaxNum = nValue; }

	// メンバ関数(取得)
	int GetNum(void) { return m_nNum; }
	int GetStartNum(void) { return m_nSetNum; }
	float GetAnim(void) { return m_fAnimTimer; }
	float GetDiff(void) { return m_fDiff; }
	CObject2D *GetSun(void) { return m_pSun; }

private:	// 自分だけがアクセス可能

	// マクロ定義
	#define NUM_PLACE	(4)	// スコアの桁数

	// メンバ関数
	void SetValue(void);

	// メンバ変数
	CNumber *m_apNumber[NUM_PLACE];			// 数字のポインタ
	CObject2D *m_pSun;	// 太陽
	D3DXVECTOR3 m_pos;	// 座標
	int m_nNum;	// 現在の値
	int m_nSetNum;	// 設定値
	int m_nMaxNum;	// 最大値
	float m_fAnimTimer;	// 1秒カウント
	float m_fDiff;	// 現在と最大値の差分
	int m_nIdxTexture;	// テクスチャ番号
};

#endif
