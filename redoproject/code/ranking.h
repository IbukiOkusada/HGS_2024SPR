//===============================================
//
// �����L���O��ʂ̊Ǘ����� [ranking.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _RANKING_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _RANKING_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "manager.h"

class CScore;
class CFileLoad;
class CMeshDome;
class CTime;
class CCharacter;

#define NUM_RANK	(5)		// �����L���O�̏��ʐ�

//===============================================
// ���U���g�N���X�̒�`(�h���N���X)
//===============================================
class CRanking : public CScene
{
public:

	// �����o�֐�
	CRanking();	// �R���X�g���N�^
	~CRanking();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetScore(int nNum) { m_nScore = nNum; }

private:

	// �����o�֐�
	void Save(int* pScore);
	void Load(int* pScore);
	void Sort(int* pScore);
	void RankIn(int* pScore, int nRanking);

	// �����o�ϐ�
	CFileLoad* m_pFileLoad;	// �t�@�C���ǂݍ��݂̃|�C���^
	CMeshDome* m_pMeshSky;		// ��p
	CScore* m_apScore[NUM_RANK];	// �X�R�A�̃|�C���^(���ʕ�)
	int m_nRank;				// ����̃����N
	int m_nTimer;				// �J�ڃ^�C�}�[
	static int m_nScore;		// ����̃X�R�A
};

#endif