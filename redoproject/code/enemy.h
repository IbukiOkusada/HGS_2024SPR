//==========================================================
//
// エネミーの処理 [enemy.h]
// Author : Riku Nakamura
//
//==========================================================
#ifndef _ENEMY_H_		// このマクロが定義されていない場合
#define _ENEMY_H_		// 二重インクルード防止用マクロを定義

#include "main.h"
#include "object.h"
#include "objectX.h"
#include "task.h"

// 前方宣言
class CWaist;
class CCharacter;
class CScore;

// マクロ定義
#define MAX_ITEM  (1280)  // 所持できるアイテムの最大数

//==========================================================
// エネミーのクラス定義(派生クラス)
//==========================================================
class CEnemy : public CTask
{
public:

	// 操作種類列挙型
	enum TYPE
	{
		TYPE_NONE,	// 操作不可能
		TYPE_SEND,	// データ送信
		TYPE_ACTIVE,	// 操作可能
		TYPE_MAX
	};

private:	// 自分だけがアクセス可能な定義

	// 状態列挙型
	enum STATE
	{
		STATE_APPEAR = 0,	// 出現状態
		STATE_NORMAL,		// 通常状態
		STATE_DAMAGE,		// ダメージ状態
		STATE_DEATH,		// 死亡状態
		STATE_MAX
	};

	// 頭部状態
	enum HEADSTATE
	{
		HEADSTATE_NORMAL = 0,	// つぼみ
		HEADSTATE_FLOWERING,	// 開花
		HEADSTATE_DAMAGE,		// ダメージ
		HEADSTATE_MAX
	};

	// 情報構造体
	struct SInfo
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 rot;		// 向き
		D3DXVECTOR3 move;		// 移動量
		D3DXVECTOR3 posOld;		// 設定位置
		D3DXMATRIX mtxWorld;	// ワールドマトリックス
		STATE state;			// 状態
		float fStateCounter;	// 状態管理カウンター
	};

public:	// 誰でもアクセス可能

	CEnemy();	// コンストラクタ
	~CEnemy();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	HRESULT Init(const char *pBodyName, const char *pLegName);	// オーバーロード
	void Uninit(void);
	void Update(void);
	static CEnemy *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	// メンバ関数(設定)
	void SetMove(const D3DXVECTOR3 move) { m_Info.move = move; }
	void SetPosition(const D3DXVECTOR3 pos) { m_Info.pos = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	void SetType(TYPE type);
	void BindId(int nId) { m_nId = nId; }
	void SetMotion(int nMotion);
	void SetDraw(bool bDraw);
	void SetNext(CEnemy* pNext) { m_pNext = pNext; }
	void SetPrev(CEnemy* pPrev) { m_pPrev = pPrev; }
	void SetScore(CScore* pScore) { m_pScore = pScore; }
	void SetRotDiff(float fDiff) { m_fRotDest = fDiff; }

	// メンバ関数(取得)
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }
	D3DXVECTOR3 GetRotation(void) { return m_Info.rot; }
	D3DXVECTOR3 GetOldPosition(void) { return m_Info.posOld; }
	CEnemy* GetNext(void) { return m_pNext; }
	CEnemy* GetPrev(void) { return m_pPrev; }
	int GetId(void) { return m_nId; }

private:	// 自分だけがアクセス可能

	// メンバ関数
	void SetMatrix(void);
	void StateSet(void);
	void Controller(void);
	void Move(void);
	void Adjust(void);
	void BodySet(void);
	bool BodyCheck(CCharacter* pBody);
	void Damage(void);
	void Collision(void);

	// メンバ変数
	CEnemy *m_pPrev;			// 前のオブジェクトへのポインタ
	CEnemy *m_pNext;			// 次のオブジェクトへのポインタ
	CCharacter* m_pBody;		// 上半身
	CCharacter* m_pLeg;			// 下半身
	SInfo m_Info;				// 自分自身の情報
	CScore* m_pScore;			// 自身のスコア
	float m_fRotMove;			// 現在の角度
	float m_fRotDiff;			// 目的の角度
	float m_fRotDest;			// 角度計算
	bool m_bMove;				// 移動したか否か
	int m_nLife;				// 体力
	int m_nId;					// ID
	int m_nMotion;
	TYPE m_type;
	HEADSTATE m_headState;
};

#endif
