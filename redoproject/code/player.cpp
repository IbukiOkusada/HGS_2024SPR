//===============================================
//
// プレイヤーの処理 [player.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "player.h"
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
#include "player_manager.h"
#include "fade.h"
#include "camera_manager.h"
#include "camera.h"
#include "score.h"
#include "sun.h"
#include "result.h"

//===============================================
// 無名名前空間
//===============================================
namespace {
	const float MOVE = (1.5f);	// 移動量
	const float ROT_MULTI = (0.1f);	// 向き補正倍率
	const float INER = (0.3f);		// 慣性
	const float DAMAGE_APPEAR = (40.0f);
	const int SETLIFE = (4);
	const int ADDSCORE = (3);
	const int SCOREBOOSTTIME = (300);
	const int SPEEDBOOSTTIME = (300);
}

namespace PLAYER
{
	const D3DXVECTOR3 COLLIMAX = { 20.0f, 70.0f, 20.0f };	// 最大当たり判定
	const D3DXVECTOR3 COLLIMIN = { -20.0f, 0.0f, -20.0f };	// 最小当たり判定
}

// 前方宣言

//===============================================
// コンストラクタ
//===============================================
//CPlayer::CPlayer()
//{
//	// 値をクリアする
//	m_nCounterAnim = 0;
//	m_nPatternAnim = 0;
//}

//===============================================
// コンストラクタ(オーバーロード)
//===============================================
CPlayer::CPlayer()
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
	m_nSpeedUpCounter = 0;
	m_fSpeedBoost = 0;
	m_nScoreBoost = 0;
	m_nScoreUpCounter = 0;
	m_pArrow = nullptr;

	CPlayerManager::GetInstance()->ListIn(this);
}

//===============================================
// デストラクタ
//===============================================
CPlayer::~CPlayer()
{
	
}

//===============================================
// 初期化処理
//===============================================
HRESULT CPlayer::Init(void)
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
	m_pBody = CCharacter::Create("data\\TXT\\motion_sunflowerman.txt");
	m_pBody->SetParent(m_pLeg->GetParts(2)->GetMtx());

	if (m_pBody->GetMotion() != nullptr)
	{
		// 初期モーションの設定
		m_pBody->GetMotion()->InitSet(m_nMotion);
		m_pBody->GetParts(0)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	m_pArrow = CModel::Create("data\\MODEL\\arrow000.x");
	m_pArrow->SetParent(&m_Info.mtxWorld);
	m_pArrow->SetCurrentPosition(D3DXVECTOR3(0.0f, 0.0f, 50.0f));

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
HRESULT CPlayer::Init(const char *pBodyName, const char *pLegName)
{
	SetMatrix();

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CPlayer::Uninit(void)
{
	CPlayerManager::GetInstance()->ListOut(this);

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
void CPlayer::Update(void)
{	
	// 前回の座標を取得
	m_Info.posOld = GetPosition();

	StateSet();	

	{
		
		// プレイヤー操作
		Controller();

		// オンライン送信
		//CManager::GetInstance()->GetScene()->SendPosition(m_Info.pos);
		//CManager::GetInstance()->GetScene()->SendRotation(m_Info.rot);
	}
	
	// カメラの追従
	CManager::GetInstance()->GetCamera()->Update();
	D3DXVECTOR3 pos = GetPosition();
	pos.y += 70.0f;
	CManager::GetInstance()->GetCamera()->Pursue(pos, GetRotation(), 600.0f);

	// ブースト処理
	if(m_nScoreUpCounter > 0){
		m_nScoreUpCounter--;
		if (m_nScoreUpCounter <= 0) {
			m_nScoreUpCounter = 0;
			m_nScoreBoost = 0;
		}
	}
	if (m_nSpeedUpCounter > 0) {
		m_nSpeedUpCounter--;
		if (m_nSpeedUpCounter <= 0) {
			m_nSpeedUpCounter = 0;
			m_fSpeedBoost = 0.0f;
		}
	}

	SetMatrix();
	BodySet();

	// 開花状態設定
	HeadSun();

	// スコア設定
	AddScore();
}

//===============================================
// 生成
//===============================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = nullptr;

	// オブジェクト2Dの生成
	pPlayer = new CPlayer();

	if (nullptr != pPlayer)
	{// 生成できた場合
		// 初期化処理
		pPlayer->Init();

		// 座標設定
		pPlayer->SetPosition(pos);

		// 向き設定
		pPlayer->SetRotation(rot);

		pPlayer->m_fRotDest = rot.y;
	}
	else
	{// 生成に失敗した場合
		return nullptr;
	}

	return pPlayer;
}

//===============================================
// 操作処理
//===============================================
void CPlayer::Controller(void)
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
		D3DXVECTOR3 vtxMax = PLAYER::COLLIMAX;
		D3DXVECTOR3 vtxMin = PLAYER::COLLIMIN;
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
void CPlayer::Move(void)
{
	CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();	// キーボードのポインタ
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();
	CCamera* pCamera = CManager::GetInstance()->GetCamera();		// カメラのポインタ
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// カメラの角度
	float fSpeed = MOVE + m_fSpeedBoost;	// 移動量

	// 入力装置確認
	if (nullptr == pInputKey){
		return;
	}

	//プレイヤーの更新
	if (pInputKey->GetPress(DIK_A) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_X, 0.5f, CInputPad::STICK_MINUS) == true)
	{
		if (pInputKey->GetPress(DIK_W) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_PLUS))
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 0.25f);
		}
		else if (pInputKey->GetPress(DIK_S) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_MINUS))
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.25f);
		}
		else
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = -CamRot.y;
		}

		// 移動した状態にする
		m_bMove = true;
	}
	else if (pInputKey->GetPress(DIK_D) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_X, 0.5f, CInputPad::STICK_PLUS) == true)
	{
		if (pInputKey->GetPress(DIK_W) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_PLUS))
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed;

			m_fRotDest = (-CamRot.y + D3DX_PI * 0.75f);
		}
		else if (pInputKey->GetPress(DIK_S) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_MINUS))
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed;

			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.75f);
		}
		else
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 1.0f);
		}

		// 移動した状態にする
		m_bMove = true;
	}
	else if (pInputKey->GetPress(DIK_W) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_PLUS))
	{
		m_Info.move.x += -cosf(CamRot.y) * fSpeed;
		m_Info.move.z += -sinf(CamRot.y) * fSpeed;
		m_fRotDest = (-CamRot.y + D3DX_PI * 0.5f);

		// 移動した状態にする
		m_bMove = true;

	}
	else if (pInputKey->GetPress(DIK_S) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_MINUS))
	{
		m_Info.move.x += cosf(CamRot.y) * fSpeed;
		m_Info.move.z += sinf(CamRot.y) * fSpeed;
		m_fRotDest = (-CamRot.y + -D3DX_PI * 0.5f);

		// 移動した状態にする
		m_bMove = true;
	}
}

//===============================================
// 状態管理
//===============================================
void CPlayer::StateSet(void)
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
			CResult::SetScore(m_pScore->GetScore());
		}
	}
		break;

	}

	switch (m_headState)
	{
	case CPlayer::HEADSTATE_NORMAL:		// つぼみ
		if (m_pBody->GetMotion() != nullptr)
		{
			m_pBody->GetMotion()->BlendSet(0);
		}
		break;

	case CPlayer::HEADSTATE_FLOWERING:	// 開花
		if (m_pBody->GetMotion() != nullptr)
		{
			m_pBody->GetMotion()->BlendSet(1);
		}
		break;

	case CPlayer::HEADSTATE_DAMAGE:		// ダメージ
		if (m_pBody->GetMotion() != nullptr)
		{
			m_pBody->GetMotion()->BlendSet(2);
		}
		break;
	}
}

//===============================================
// 体力設定
//===============================================
void CPlayer::SetType(TYPE type)
{
	m_type = type;
}

//===============================================
// マトリックス設定
//===============================================
void CPlayer::SetMatrix(void)
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
void CPlayer::SetMotion(int nMotion) {	
	
}

//===============================================
// プレイヤーの描画設定
//===============================================
void CPlayer::SetDraw(bool bDraw)
{
	
}

//===============================================
// 調整
//===============================================
void CPlayer::Adjust(void)
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
void CPlayer::BodySet(void)
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
bool CPlayer::BodyCheck(CCharacter* pBody)
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
// スコア加算
//===============================================
void CPlayer::AddScore(void){

	if (m_pScore == nullptr) {	// スコアがない
		return;
	}

	if (m_headState != HEADSTATE_FLOWERING) {	// 開花していない
		return;
	}

	// 加算
	m_pScore->AddScore(ADDSCORE + m_nScoreBoost);
}
//===============================================
// 開花状態設定
//===============================================
void CPlayer::HeadSun(void)
{
	// 各変数
	D3DXVECTOR3 posSun = CManager::GetInstance()->GetScene()->GetSun()->GetSunObject()->GetPosition();
	D3DXVECTOR3 posPlayer = GetPosition();
	float rotSunPlayer = atan2f(posPlayer.x - posSun.x, posPlayer.z - posSun.z);
	float rotSunPlayerDef = rotSunPlayer - GetRotation().y;

	if (m_pArrow != nullptr) {
		D3DXVECTOR3 ArrowRot = m_Info.rot;
		ArrowRot.y = rotSunPlayer - ArrowRot.y + -D3DX_PI * 0.5f;

		// 回転補正
		if (ArrowRot.y > D3DX_PI)
		{
			ArrowRot.y -= D3DX_PI * 2.0f;
		}

		if (ArrowRot.y < -D3DX_PI)
		{
			ArrowRot.y += D3DX_PI * 2.0f;
		}
		m_pArrow->SetRotation(ArrowRot);
	}

	// 回転補正
	if (rotSunPlayerDef > D3DX_PI)
	{
		rotSunPlayerDef -= D3DX_PI * 2.0f;
	}

	if (rotSunPlayerDef < -D3DX_PI)
	{
		rotSunPlayerDef += D3DX_PI * 2.0f;
	}

	CManager::GetInstance()->GetDebugProc()->Print("太陽との角度[%f]\n", rotSunPlayer);
	CManager::GetInstance()->GetDebugProc()->Print("プレイヤーの角度[%f, %f, %f]\n", GetRotation().x, GetRotation().y, GetRotation().z);
	CManager::GetInstance()->GetDebugProc()->Print("太陽との角度差[%f]\n", rotSunPlayerDef);

	// 角度の差が一定値以内で開花状態に
	if (rotSunPlayerDef < 0.7f && rotSunPlayerDef > -0.7f)
	{
		m_headState = HEADSTATE_FLOWERING;
		CManager::GetInstance()->GetDebugProc()->Print("プレイヤーの状態[開花]\n");
	}
	else
	{
		m_headState = HEADSTATE_NORMAL;
		CManager::GetInstance()->GetDebugProc()->Print("プレイヤーの状態[通常]\n");
	}
}

//===============================================
// ダメージ
//===============================================
void CPlayer::Damage(void)
{
	if (m_nScoreUpCounter) {

	}

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

//===============================================
// 速度増加
//===============================================
void CPlayer::SpeedBoost(void)
{
	m_fSpeedBoost = MOVE * 0.5f;
	m_nSpeedUpCounter = SPEEDBOOSTTIME;
}

//===============================================
// スコア増加
//===============================================
void CPlayer::ScoreBoost(void)
{
	m_nScoreBoost += ADDSCORE;
	m_nScoreUpCounter = SCOREBOOSTTIME;
}