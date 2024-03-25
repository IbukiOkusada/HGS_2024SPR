//===============================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "texture.h"
#include "slow.h"
#include "game.h"
#include "meshfield.h"
#include "billboard.h"

//===============================================
// �������O���
//===============================================
namespace {
	const float LIFE = (30.0f); // ����
	const float GUNCHARGE = (0.1f);

	const D3DXCOLOR COLINFO[CEffect::TYPE_MAX] = {	// ��ޕʏ����F�̐ݒ�
		{1.0f, 1.0f, 1.0f, 1.0f},
		{ 1.0f, 1.0f, 0.0f, 1.0f },
	};

	const float RADIUSINFO[CEffect::TYPE_MAX] = {	// ��ޕʔ��a�̐ݒ�
		100.0f,
		100.0f,
	};
}

//===============================================
// �R���X�g���N�^
//===============================================
CEffect::CEffect()
{
	// �l�̃N���A
	m_Info.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Info.fLife = 0;
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.fRadius = 0.0f;
	m_Info.Type = TYPE_NONE;
}

//===============================================
// �f�X�g���N�^
//===============================================
CEffect::~CEffect()
{

}

//===============================================
// ����������
//===============================================
HRESULT CEffect::Init(void)
{
	// �I�u�W�F�N�g�̏���������
	m_pObjectBilBoard = CObjectBillboard::Create(m_Info.pos, 6);
	m_pObjectBilBoard->BindTexture(CManager::GetInstance()->GetTexture()->Regist(CManager::GetInstance()->GetTexture()->GetFileName(SetTex(m_Info.Type))));
	m_pObjectBilBoard->SetAlphaText(true);
	m_pObjectBilBoard->SetZTest(true);
	m_pObjectBilBoard->SetLighting(true);
	m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_ADD);

	m_Info.fLife = LIFE;	// �̗͂̏�����

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CEffect::Uninit(void)
{
	// �I�u�W�F�N�g�̏I������
	if (m_pObjectBilBoard != nullptr) {
		m_pObjectBilBoard->Uninit();
		m_pObjectBilBoard = nullptr;
	}

	Release();
}

//===============================================
// �X�V����
//===============================================
void CEffect::Update(void)
{
	m_Info.fLife -= CManager::GetInstance()->GetSlow()->Get();
	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posOld = m_Info.pos;
	float fHeight = CMeshField::GetHeight(m_Info.pos, posOld);

	if (m_Info.fLife < 0)
	{// �������Ȃ��Ȃ����ꍇ

		// �I������
		Uninit();
		return;
	}

	D3DXVECTOR3 pos = GetPosition();	// ���W

	pos += m_Info.move * CManager::GetInstance()->GetSlow()->Get();

	// ���W
	SetPosition(pos);

	switch (m_Info.Type)
	{
	case TYPE_NONE:
		m_Info.col.a -= 0.05f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius += 0.1f * CManager::GetInstance()->GetSlow()->Get();
		break;

	case TYPE_SMAKE:	// ��

		m_Info.col.a -= 0.05f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius += 0.1f * CManager::GetInstance()->GetSlow()->Get();

		break;

	case TYPE_FLOWERING:	// ��

		m_Info.move.x -= m_Info.move.x * 0.025f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.y -= m_Info.move.y * 0.01f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.move.z -= m_Info.move.z * 0.025f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.fRadius -= 0.5f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.col.a -= 0.05f * CManager::GetInstance()->GetSlow()->Get();

		{
			D3DXVECTOR3 rot = m_pObjectBilBoard->GetRotation();
			rot.z += D3DX_PI * (rand() % 50 * 0.001f);
			m_pObjectBilBoard->SetRotation(rot);
		}

		break;
	case TYPE_SPEEDUP:	// ��

		m_Info.fRadius -= 0.5f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.col.a -= 0.05f * CManager::GetInstance()->GetSlow()->Get();

		{
			D3DXVECTOR3 rot = m_pObjectBilBoard->GetRotation();
			rot.z += D3DX_PI * (rand() % 50 * 0.001f);
			m_pObjectBilBoard->SetRotation(rot);
		}

		break;

	case TYPE_SCOREUP:	// ��

		m_Info.fRadius -= 0.75f * CManager::GetInstance()->GetSlow()->Get();
		m_Info.col.a -= 0.05f * CManager::GetInstance()->GetSlow()->Get();

		{
			D3DXVECTOR3 rot = m_pObjectBilBoard->GetRotation();
			rot.z += D3DX_PI * (rand() % 50 * 0.001f);
			m_pObjectBilBoard->SetRotation(rot);
		}

		break;
	}

	if (m_Info.col.a < 0.0f || m_Info.fRadius < 0.0f)
	{// �l���Ђ�����Ԃ���

		
		Uninit();
		return;
	}

	InfoSet();
}

//===============================================
// ����
//===============================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, TYPE type)
{
	CEffect *pEffect = NULL;
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �G�t�F�N�g�̐���
	pEffect = new CEffect;

	if (pEffect != NULL)
	{// �����ł����ꍇ

		// ���W�ݒ�
		pEffect->SetPosition(pos);

		// ��ނ̐ݒ�
		pEffect->SetType(type);

		// ���a�ݒ�
		pEffect->RadiusSet();

		// �F�̐ݒ�
		pEffect->ColorSet();

		pEffect->InfoSet();

		// ����������
		pEffect->Init();

		// �e�N�X�`���̊��蓖��
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pEffect;
}

//===============================================
// ����
//===============================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fRadius, float fLife, TYPE type)
{
	CEffect *pEffect = NULL;
	CTexture *pTexture = CManager::GetInstance()->GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �G�t�F�N�g�̐���
	pEffect = new CEffect();

	if (pEffect != NULL)
	{// �����ł����ꍇ

		// ���W�ݒ�
		pEffect->SetPosition(pos);

		// �G�t�F�N�g�̐ݒ�
		pEffect->SetType(type);

		// ���a�ݒ�
		pEffect->m_Info.fRadius = fRadius;

		// �ړ��ʐݒ�
		pEffect->SetMove(move);

		// �T�C�Y�̐ݒ�
		//pEffect->SetSize(pEffect->m_Info.fRadius, pEffect->m_Info.fRadius);

		// �F�̐ݒ�
		pEffect->m_Info.col = col;

		// ����������
		pEffect->Init();

		// �����ݒ�
		pEffect->m_Info.fLife = fLife;

		pEffect->InfoSet();

		// �`����@�ݒ�
		pEffect->DrawSet();
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pEffect;
}

//===============================================
// �F�ݒ�
//===============================================
void CEffect::ColorSet(void)
{
	// ��ނ��ƂɐF�̐ݒ�
	m_Info.col = COLINFO[m_Info.Type];
	

	if (m_pObjectBilBoard == nullptr) {
		return;
	}

	m_pObjectBilBoard->SetCol(m_Info.col);
}

//===============================================
// �T�C�Y�̐ݒ�
//===============================================
void CEffect::RadiusSet(void)
{
	// ���a�̐ݒ�
	m_Info.fRadius = RADIUSINFO[m_Info.Type];

	if (m_pObjectBilBoard == nullptr) {
		return;
	}

	m_pObjectBilBoard->SetSize(m_Info.fRadius, m_Info.fRadius);
}

//===============================================
// �ړ��ʂ̐ݒ�
//===============================================
void CEffect::SetMove(D3DXVECTOR3 move)
{
	m_Info.move = move;
}

//===============================================
// ����{�ݒ�
//===============================================
void CEffect::InfoSet(void)
{
	if (m_pObjectBilBoard == nullptr) {
		return;
	}

	m_pObjectBilBoard->SetPosition(m_Info.pos);
	m_pObjectBilBoard->SetCol(m_Info.col);
	m_pObjectBilBoard->SetSize(m_Info.fRadius, m_Info.fRadius);
}

//===============================================
// �^�C�v�ʃe�N�X�`��
//===============================================
CTexture::TYPE CEffect::SetTex(TYPE type)
{
	switch (type)
	{
	case TYPE_NONE:
	{

	}
	break;

	case TYPE_SMAKE:
	{
		return CTexture::TYPE_EFFECT;

	}
	break;

	case TYPE_FLOWERING:
	{
		return CTexture::TYPE_STAR;

	}
	break;

	case TYPE_SPEEDUP:
	{
		return CTexture::TYPE_SPEED;

	}
	break;

	case TYPE_SCOREUP:
	{
		return CTexture::TYPE_SCORE;

	}
	break;
	}

	return CTexture::TYPE();
}

//===============================================
// �`��ݒ�
//===============================================
void CEffect::DrawSet(void)
{
	if (m_pObjectBilBoard == nullptr) {
		return;
	}

	switch (m_Info.Type)
	{
	case TYPE_NONE:
	{

	}
	break;

	case TYPE_SMAKE:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(true);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_ADD);
	}
	break;

	case TYPE_FLOWERING:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(true);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_ADD);
	}
	break;

	case TYPE_SPEEDUP:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(true);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_ADD);
	}
	break;

	case TYPE_SCOREUP:
	{
		m_pObjectBilBoard->SetAlphaText(true);
		m_pObjectBilBoard->SetZTest(true);
		m_pObjectBilBoard->SetLighting(true);
		m_pObjectBilBoard->SetFusion(CObjectBillboard::FUSION_ADD);
	}
	break;

	}
}

//===============================================
// ���a�擾
//===============================================
float CEffect::GetRange(void) const
{
	if (m_pObjectBilBoard == nullptr) {
		return 0.0f;
	}

	return m_pObjectBilBoard->GetWidth();
}

//===============================================
// �F�擾
//===============================================
D3DXCOLOR CEffect::GetCol(void) const
{
	if (m_pObjectBilBoard == nullptr) {
		return D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	return m_pObjectBilBoard->GetCol();
}