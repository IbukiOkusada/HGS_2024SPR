//===============================================
//
// リザルト画面の管理処理 [result.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "result.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"
#include "result.h"
#include "camera.h"
#include "ranking.h"
#include "object_manager.h"
#include "time.h"
#include "fileload.h"
#include "player.h"
#include "character.h"
#include "motion.h"
#include "model.h"
#include "score.h"

// 静的メンバ変数
int CResult::m_nScore = 0;
CResult::TYPE CResult::m_type = CResult::TYPE_MAX;

//===============================================
// コンストラクタ
//===============================================
CResult::CResult()
{
	m_pMeshSky = NULL;
	m_pTime = NULL;
	m_pObjClear = nullptr;
}

//===============================================
// デストラクタ
//===============================================
CResult::~CResult()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CResult::Init(void)
{
	//カメラ初期化
	{
		CManager::GetInstance()->GetCamera()->SetLength(300.0f);
		CManager::GetInstance()->GetCamera()->SetRotation(D3DXVECTOR3(1.0f, -1.5f, 1.5f));
		CManager::GetInstance()->GetCamera()->SetPositionR(D3DXVECTOR3(0.0f, 127.77f, -301.94f));
		CManager::GetInstance()->GetCamera()->SetPositionV(D3DXVECTOR3(0.0f, 107.77f, -601.94f));
		D3DVIEWPORT9 viewport;

		//プレイヤー追従カメラの画面位置設定
		viewport.X = 0;
		viewport.Y = 0;
		viewport.Width = (DWORD)(SCREEN_WIDTH * 1.0f);
		viewport.Height = (DWORD)(SCREEN_HEIGHT * 1.0f);
		viewport.MinZ = 0.0f;
		viewport.MaxZ = 1.0f;
		CManager::GetInstance()->GetCamera()->SetViewPort(viewport);
	}

	// 外部ファイル読み込みの生成
	CFileLoad::GetInstance()->OpenFile("data\\TXT\\model.txt");

	// 下半身の設定
	m_pLeg = CCharacter::Create("data\\TXT\\motion_playerbody.txt");
	m_pLeg->Init();
	m_pLeg->SetPosition({ 0.0f, 0.0f, 0.0f });

	if (m_pLeg->GetMotion() != nullptr)
	{
		m_pLeg->GetMotion()->InitSet(0);
	}

	// 胴体の設定
	m_pBody = CCharacter::Create("data\\TXT\\motion_sunflowerman.txt");
	m_pBody->SetParent(m_pLeg->GetParts(2)->GetMtx());

	if (m_pBody->GetMotion() != nullptr)
	{
		// 初期モーションの設定
		if (m_type == TYPE_MULTI_WIN)
		{
			m_pBody->GetMotion()->InitSet(1);
		}
		else
		{
			m_pBody->GetMotion()->InitSet(2);
		}
		m_pBody->GetParts(0)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RESULT);
	//CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RESULT);

	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.2f - 10.0f * 4, 300.0f, 0.0f), 8, 1.0f, 60.0f, 120.0f);
	m_pScore->AddScore(m_nScore);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CResult::Uninit(void)
{
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

	if (m_pScore != nullptr) {
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = nullptr;
	}

	CFileLoad::Release();
	CRanking::SetScore(m_nScore);
	m_nScore = 0;
	m_type = TYPE_MAX;
	CManager::GetInstance()->GetCamera()->SetActive(true);
	CManager::GetInstance()->GetSound()->Stop();
}

//===============================================
// 更新処理
//===============================================
void CResult::Update(void)
{

	if (CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_A, 0) ||
		CManager::GetInstance()->GetInputPad()->GetTrigger(CInputPad::BUTTON_START, 0) ||
		CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetInstance()->GetFade()->Set(CScene::MODE_RANKING);
	}

	// 下半身更新
	if (m_pLeg != nullptr)
	{// 使用されている場合
		m_pLeg->Update();
	}

	// 胴体更新
	if (m_pBody != nullptr)
	{// 使用されている場合
		m_pBody->Update();
	}

	CScene::Update();
}

//===============================================
// 描画処理
//===============================================
void CResult::Draw(void)
{
	CScene::Draw();
}
