//===============================================
//
// エネミーの処理 [enemy.cpp]
// Author : Riku Nakamura
//
//===============================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "camera.h"
#include "Xfile.h"
#include "slow.h"
#include "texture.h"
#include "meshfield.h"
#include "Xfile.h"
#include "meshorbit.h"
#include "game.h"
#include "filter.h"
#include "object2D.h"
#include "meshwall.h"
#include "objectX.h"
#include "sound.h"
#include <assert.h>
#include "billboard.h"
#include "character.h"
#include "motion.h"
#include "waist.h"
#include "sound.h"
#include "model.h"
#include "particle.h"
#include "effect.h"
#include <math.h>
#include "meshwall.h"
#include "enemy_manager.h"
#include "fade.h"
#include "camera_manager.h"
#include "camera.h"
#include "score.h"
#include "sun.h"
#include "player.h"
#include "player_manager.h"

//===============================================
// 無名名前空間
//===============================================
namespace {
	const float MOVE = (1.0f);	// 移動量
	const float ROT_MULTI = (0.1f);	// 向き補正倍率
	const float INER = (0.3f);		// 慣性
	const float DAMAGE_APPEAR = (40.0f);
	const int SETLIFE = (4);
	const int ADDSCORE = (3);
}

namespace ENEMY
{
	const D3DXVECTOR3 COLLIMAX = { 20.0f, 70.0f, 20.0f };	// 最大当たり判定
	const D3DXVECTOR3 COLLIMIN = { -20.0f, 0.0f, -20.0f };	// 最小当たり判定
}

// 前方宣言

//===============================================
// コンストラクタ
//===============================================
//CEnemy::CEnemy()
//{
//	// 値をクリアする
//	m_nCounterAnim = 0;
//	m_nPatternAnim = 0;
//}

//===============================================
// コンストラクタ(オーバーロード)
//===============================================
CEnemy::CEnemy()
{
	// 値をクリアする
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	m_type = TYPE_NONE;
	m_nId = -1;
	m_bMove = false;
	m_pScore = nullptr;
	m_nLife = 0;
	m_headState = HEADSTATE_NORMAL;

	CEnemyManager::GetInstance()->ListIn(this);
}

//===============================================
// デストラクタ
//===============================================
CEnemy::~CEnemy()
{
	
}

//===============================================
// 初期化処理
//===============================================
HRESULT CEnemy::Init(void)
{
	// 下半身の設定
	m_pLeg = CCharacter::Create("data\\TXT\\motion_playerbody.txt");
	m_pLeg->SetParent(&m_Info.mtxWorld);

	if (m_pLeg->GetMotion() != nullptr)
	{
		// 初期モーションの設定
		m_pLeg->GetMotion()->InitSet(m_nMotion);
	}

	// 胴体の設定
	m_pBody = CCharacter::Create("data\\TXT\\motion_bee.txt");
	m_pBody->SetParent(m_pLeg->GetParts(2)->GetMtx());

	if (m_pBody->GetMotion() != nullptr)
	{
		// 初期モーションの設定
		m_pBody->GetMotion()->InitSet(m_nMotion);
		m_pBody->GetParts(0)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// パラメータの設定
	m_Info.state = STATE_APPEAR;
	m_type = TYPE_NONE;
	m_headState = HEADSTATE_NORMAL;
	m_nLife = SETLIFE;

	return S_OK;
}

//===============================================
// 初期化処理(オーバーロード)
//===============================================
HRESULT CEnemy::Init(const char *pBodyName, const char *pLegName)
{
	SetMatrix();

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CEnemy::Uninit(void)
{
	CEnemyManager::GetInstance()->ListOut(this);

	// 胴体の終了
	if (m_pBody != nullptr) {
		m_pBody->Uninit();
		delete m_pBody;
		m_pBody = nullptr;
	}

	// 下半身の終了
	if (m_pLeg != nullptr) {
		m_pLeg->Uninit();
		delete m_pLeg;
		m_pLeg = nullptr;
	}

	// 廃棄
	Release();
}

//===============================================
// 更新処理
//===============================================
void CEnemy::Update(void)
{	
	// 前回の座標を取得
	m_Info.posOld = GetPosition();

	StateSet();	

	{
		
		// エネミー操作
		Controller();

		// オンライン送信
		//CManager::GetInstance()->GetScene()->SendPosition(m_Info.pos);
		//CManager::GetInstance()->GetScene()->SendRotation(m_Info.rot);
	}
	
	SetMatrix();
	BodySet();
}

//===============================================
// 生成
//===============================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pEnemy = nullptr;

	// オブジェクト2Dの生成
	pEnemy = new CEnemy();

	if (nullptr != pEnemy)
	{// 生成できた場合
		// 初期化処理
		pEnemy->Init();

		// 座標設定
		pEnemy->SetPosition(pos);

		// 向き設定
		pEnemy->SetRotation(rot);

		pEnemy->m_fRotDest = rot.y;
	}
	else
	{// 生成に失敗した場合
		return nullptr;
	}

	return pEnemy;
}

//===============================================
// 操作処理
//===============================================
void CEnemy::Controller(void)
{
	D3DXVECTOR3 pos = GetPosition();	// 座標を取得
	D3DXVECTOR3 rot = GetRotation();	// 向きを取得
	float fSlow = CManager::GetInstance()->GetSlow()->Get();
	float fIner = INER;
	m_fRotMove = rot.y;	//現在の向きを取得

	{
		Move();
	}

	// 向き設定
	Adjust();

	m_Info.move.x += (0.0f - m_Info.move.x) * 0.12f;	//x座標
	m_Info.move.z += (0.0f - m_Info.move.z) * 0.12f;	//x座標

	pos.x += m_Info.move.x * fSlow;
	pos.z += m_Info.move.z * fSlow;

	// 当たり判定
	{
		D3DXVECTOR3 vtxMax = ENEMY::COLLIMAX;
		D3DXVECTOR3 vtxMin = ENEMY::COLLIMIN;
		D3DXVECTOR3 vtxMaxOld = vtxMax;
		D3DXVECTOR3 vtxMinOld = vtxMin;
		CObjectX::COLLISION_AXIS ColiAxis = CObjectX::TYPE_MAX;	// 当たっている方向をリセット
		CObjectX::Collision(pos, m_Info.posOld, m_Info.move, vtxMin, vtxMax, vtxMinOld, vtxMaxOld, ColiAxis);
	}

	SetPosition(pos);
	SetRotation(m_Info.rot);
}

//===============================================
// 移動
//===============================================
void CEnemy::Move(void)
{
	float fSpeed = MOVE;	// 移動量

	//エネミーの更新

	if (CPlayerManager::GetInstance()->GetTop())
	{
		D3DXVECTOR3 posPlayer = CPlayerManager::GetInstance()->GetTop()->GetPosition();
		D3DXVECTOR3 posEnemy = GetPosition();
		float rotDef, rotPlayer;

		rotPlayer = atan2f(posEnemy.x - posPlayer.x, posEnemy.z - posPlayer.z);

		// 回転補正
		if (rotPlayer > D3DX_PI)
		{
			rotPlayer -= D3DX_PI * 2.0f;
		}

		if (rotPlayer < -D3DX_PI)
		{
			rotPlayer += D3DX_PI * 2.0f;
		}

		m_fRotDest = rotPlayer;

		m_Info.move.x += -sinf(GetRotation().y + (D3DX_PI * 0.0f)) * fSpeed;
		m_Info.move.z += -cosf(GetRotation().y + (D3DX_PI * 0.0f)) * fSpeed;
	}
}

//===============================================
// 状態管理
//===============================================
void CEnemy::StateSet(void)
{
	float fSlawMul = CManager::GetInstance()->GetSlow()->Get();
	switch (m_Info.state)
	{
	case STATE_APPEAR:
	{
		m_Info.fStateCounter -= fSlawMul;

		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = 0.0f;
			m_Info.state = STATE_NORMAL;
		}
	}
		break;

	case STATE_NORMAL:
	{

	}
		break;

	case STATE_DAMAGE:
	{
		m_Info.fStateCounter -= fSlawMul;

		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = DAMAGE_APPEAR;
			m_Info.state = STATE_APPEAR;
		}
	}
		break;

	case STATE_DEATH:
	{
		m_Info.fStateCounter -= fSlawMul;

		if (m_Info.fStateCounter <= 0.0f)
		{
			m_Info.fStateCounter = DAMAGE_APPEAR;
		}
	}
		break;

	}
}

//===============================================
// 体力設定
//===============================================
void CEnemy::SetType(TYPE type)
{
	m_type = type;
}

//===============================================
// マトリックス設定
//===============================================
void CEnemy::SetMatrix(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスへのポインタを取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);
}

//===============================================
// 指定モーションに設定
//===============================================
void CEnemy::SetMotion(int nMotion) {	
	
}

//===============================================
// エネミーの描画設定
//===============================================
void CEnemy::SetDraw(bool bDraw)
{
	
}

//===============================================
// 調整
//===============================================
void CEnemy::Adjust(void)
{
	while (1)
	{
		if (m_fRotDest > D3DX_PI || m_fRotDest < -D3DX_PI)
		{//-3.14～3.14の範囲外の場合
			if (m_fRotDest > D3DX_PI)
			{
				m_fRotDest += (-D3DX_PI * 2);
			}
			else if (m_fRotDest < -D3DX_PI)
			{
				m_fRotDest += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}

	m_fRotDiff = m_fRotDest - m_fRotMove;	//目標までの移動方向の差分

	while (1)
	{
		if (m_fRotDiff > D3DX_PI || m_fRotDiff < -D3DX_PI)
		{//-3.14～3.14の範囲外の場合
			if (m_fRotDiff > D3DX_PI)
			{
				m_fRotDiff += (-D3DX_PI * 2);
			}
			else if (m_fRotDiff < -D3DX_PI)
			{
				m_fRotDiff += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}

	m_Info.rot.y += m_fRotDiff * ROT_MULTI;

	while (1)
	{
		if (m_Info.rot.y > D3DX_PI || m_Info.rot.y < -D3DX_PI)
		{//-3.14～3.14の範囲外の場合
			if (m_Info.rot.y > D3DX_PI)
			{
				m_Info.rot.y += (-D3DX_PI * 2);
			}
			else if (m_Info.rot.y < -D3DX_PI)
			{
				m_Info.rot.y += (D3DX_PI * 2);
			}
		}
		else
		{
			break;
		}
	}
}

//===============================================
// 使用階層構造の設定
//===============================================
void CEnemy::BodySet(void)
{
	// 下半身更新
	if (BodyCheck(m_pLeg))
	{// 使用されている場合
		m_pLeg->Update();
	}

	// 胴体更新
	if (BodyCheck(m_pBody))
	{// 使用されている場合
		m_pBody->Update();
	}
}

//===============================================
// 体使用確認
//===============================================
bool CEnemy::BodyCheck(CCharacter* pBody)
{
	if (pBody == nullptr) {	// 使用されている
		return false;
	}

	if (pBody->GetMotion() == nullptr) {	// モーションも使用されている
		return false;
	}

	return true;
}

//===============================================
// ダメージ
//===============================================
void CEnemy::Damage(void)
{
	if (m_Info.state != STATE_NORMAL) {
		return;
	}

	m_Info.state = STATE_DAMAGE;
	m_Info.fStateCounter = DAMAGE_APPEAR;
	m_headState = HEADSTATE_DAMAGE;
	m_nLife--;

	if (m_nLife <= 0) {
		m_Info.state = STATE_DEATH;
	}
}