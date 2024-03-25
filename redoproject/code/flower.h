//==========================================================
//
// 花の処理 [flower.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _SAMPLETASK_H_		// このマクロが定義されていない場合
#define _SAMPLETASK_H_		// 二重インクルード防止用マクロを定義

#include "task.h"	// これでファイルインクルードできます

// 前方宣言
class CModel;

//==========================================================
// サンプルのクラス定義
//==========================================================
class CFlower : public CTask
{
public:

	// 種類
	enum TYPE {
		TYPE_SPEED = 0,	// 速度
		TYPE_GROWSPEED,	// 成長速度
		TYPE_SLEEP,		// 睡眠
		TYPE_MAX
	};
public:	// 誰でもアクセス可能

	CFlower();	// コンストラクタ(オーバーロード)
	~CFlower();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CFlower *Create(const D3DXVECTOR3& pos,const D3DXVECTOR3& rot);

	// メンバ関数(取得)

	// メンバ関数(設定)

private:	// 自分だけがアクセス可能

	// メンバ関数

	// メンバ変数
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	CModel* m_pModel;
	int m_nType;
	bool m_bHit;
	static const char* m_apModelType[TYPE_MAX];	// モデルファイル
};

#endif
