//==========================================================
//
// 太陽タスク [sun.h]
// Author : Riku Nakamura
//
//==========================================================
#ifndef _SUN_H_		// このマクロが定義されていない場合
#define _SUN_H_		// 二重インクルード防止用マクロを定義

#include "task.h"
#include "objectX.h"
//#include "task.h"	// これでファイルインクルードできます

//==========================================================
// 太陽のクラス定義
//==========================================================
class CSunTask : public CTask
{

public:	// 誰でもアクセス可能

	CSunTask();	// コンストラクタ(オーバーロード)
	~CSunTask();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CSunTask *Create(void);

	// メンバ関数(取得)
	CObjectX* GetSunObject(void) { return SunObject; }
	D3DXVECTOR3 GetSunRot(void) { return Rot; }

	// メンバ関数(設定)

private:	// 自分だけがアクセス可能

	// メンバ関数
	D3DXVECTOR3 PosRelativeMtx(D3DXVECTOR3 posO, D3DXVECTOR3 rotO, D3DXVECTOR3 offset);

	// メンバ変数
	CObjectX *SunObject;
	D3DXVECTOR3 Rot;
};

#endif
