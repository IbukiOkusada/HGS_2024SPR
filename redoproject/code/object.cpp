//===============================================
//
// �I�u�W�F�N�g�̏��� [object.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "object.h"
#include "manager.h"
#include "renderer.h"
#include "object_manager.h"

// �}�N����`

//===============================================
// �ÓI�����o�ϐ��錾
//===============================================

//===============================================
// �R���X�g���N�^
//===============================================
//CObject::CObject()
//{
//}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CObject::CObject(int nPriority)
{
	// �l�̃N���A
	m_pNext = NULL;
	m_pPrev = NULL;
	m_bDeath = false;
	m_bDraw = true;

	// �D�揇�ʂ̊m�F
	if (nPriority < 0)
	{
		nPriority = 0;
	}
	else if (nPriority >= NUM_PRIORITY)
	{
		nPriority = NUM_PRIORITY - 1;
	}

	m_nPriority = nPriority;	// �ݒ�

	// ���X�g�ɑ}��
	CObjectManager::GetInstance()->ListIn(this);
}

//===============================================
// �f�X�g���N�^
//===============================================
CObject::~CObject()
{
	
}

#if 0	// �������z�֐��Ȃ̂Œʂ�Ȃ�
//===============================================
// ����������
//===============================================
HRESULT CObject::Init(void)
{

}
#endif

#if 0	// �������z�֐��Ȃ̂Œʂ�Ȃ�
//===============================================
// �I������
//===============================================
void CObject::Uninit(void)
{
	
}
#endif

#if 0	// �������z�֐��Ȃ̂Œʂ�Ȃ�
//===============================================
// �X�V����
//===============================================
void CObject::Update(void)
{

}
#endif

#if 0	// �������z�֐��Ȃ̂Œʂ�Ȃ�
//===============================================
// �`�揈��
//===============================================
void CObject::Draw(void)
{

}
#endif

//===============================================
// �I�u�W�F�N�g�̔p��
//===============================================
void CObject::Release(void)
{
	// ���S��Ԃɂ���
	m_bDeath = true;
}

//===============================================
// �^�C�v�̐ݒ�
//===============================================
void CObject::SetType(const TYPE type)
{
	m_type = type;	// ��ނ�ݒ�
}