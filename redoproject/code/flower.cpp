//==========================================================
//
// �Ԃ̏��� [flower.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "flower.h"
#include "model.h"
#include "manager.h"
#include "Xfile.h"
#include "player.h"
#include "player_manager.h"

// �ÓI�����o�ϐ�
const char* CFlower::m_apModelType[CFlower::TYPE_MAX] = {
	"data\\MODEL\\flower000.x",
	"data\\MODEL\\flower001.x",
	"data\\MODEL\\flower002.x",
};

namespace {
	const float HITLENGTH = (200.0f);
	const D3DXCOLOR SETCOL = { 1.0f, 1.0f, 1.0f, 1.0f };
}

//==========================================================
// �R���X�g���N�^
//==========================================================
CFlower::CFlower()
{
	// �l�̃N���A
	m_pModel = nullptr;
	m_nType = TYPE_MAX;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CFlower::~CFlower()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CFlower::Init(void)
{
	int nRand = rand() % TYPE_MAX;
	m_nType = nRand;

	// ���f������
	m_pModel = CModel::Create(m_apModelType[nRand]);
	if (m_pModel != nullptr) {
		// �ύX�}�e���A���ݒ�
		D3DMATERIAL9 mat;
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		mat.Ambient = col;
		mat.Diffuse = col;
		mat.Emissive = col;
		mat.Power = col;
		mat.Specular = col;
		m_pModel->SetMaterial(mat);
		m_pModel->ChangeCol(true);
	}

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CFlower::Uninit(void)
{
	if (m_pModel != nullptr) {
		m_pModel->Uninit();
		m_pModel = nullptr;
	}

	Release();
}

//==========================================================
// �X�V����
//==========================================================
void CFlower::Update(void)
{
	if (m_bHit) {
		return;
	}

	CPlayer* pPlayer = CPlayerManager::GetInstance()->GetTop();

	if (pPlayer == nullptr) {
		return;
	}

	D3DXVECTOR3 pos = pPlayer->GetPosition();

	// �������擾
	float fLength = sqrtf((pos.x - m_pos.x) * (pos.x - m_pos.x)
		+ (pos.z - m_pos.z) * (pos.z - m_pos.z));

	// �ǐՊm�F
	if (fLength < HITLENGTH) {	// ���݌��Ă���v���C���[�̕����߂��ꍇ
		m_bHit = true;

		switch (m_nType) {
		case TYPE_SPEED:
			pPlayer->SpeedBoost();
			break;

		case TYPE_GROWSPEED:
			pPlayer->ScoreBoost();
			break;

		case TYPE_SLEEP:

			break;
		}

		if (m_pModel != nullptr) {
			m_pModel->ChangeCol(false);
		}
	}
}

//==========================================================
// ����
//==========================================================
CFlower *CFlower::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	CFlower *pFlower = nullptr;

	pFlower = new CFlower;

	if (pFlower != nullptr)
	{
		// ����������
		pFlower->Init();

		pFlower->m_pos = pos;
		pFlower->m_rot = rot;

		if (pFlower->m_pModel != nullptr) {
			pFlower->m_pModel->SetPosition(pos);
			pFlower->m_pModel->SetRotation(rot);
		}
	}

	return pFlower;
}
