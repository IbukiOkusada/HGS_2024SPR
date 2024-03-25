//===============================================
//
// �Q�[����ʂ̊Ǘ����� [game.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "Xfile.h"
#include "input.h"
#include "fade.h"
#include "result.h"
#include "debugproc.h"
#include "time.h"
#include "tcp_client.h"
#include <thread>
#include "protocol_online.h"
#include "object2D.h"
#include <assert.h>
#include "ranking.h"
#include "meshdome.h"
#include "player.h"
#include "fileload.h"
#include "score.h"
#include "sun.h"
#include "time.h"
#include "flower.h"

// �������O��Ԃ��`
namespace {
    
    const int MAX_TIME = (60 * 2);	// �ő厞��
    const int MAX_STRING = (2048);
    const int DEF_PORT = (22333);
    const char* ADDRESSFILE	= "data\\TXT\\address.txt";
}

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CGame::STATE CGame::m_state = CGame::STATE_LOCAL;	// ���
int CGame::m_nNumPlayer = 0;

//===============================================
// �R���X�g���N�^
//===============================================
CGame::CGame()
{
    // �l�̃N���A
    m_ppCamera = nullptr;
    m_ppPlayer = nullptr;
    m_pFileLoad = nullptr;
    m_pMeshDome = nullptr;
    m_pClient = nullptr;
    m_pTimer = nullptr;
    m_pScore = nullptr;
    m_pSun = nullptr;
    m_nSledCnt = 0;
    m_bEnd = false;
    m_fOpenDoorUISin = 0.0f;
    m_bPause = false;
    m_pPause = nullptr;
}

//===============================================
// �R���X�g���N�^(�l���ݒ�)
//===============================================
CGame::CGame(int nNumPlayer)
{
    // �l�̃N���A
    m_ppCamera = nullptr;
    m_ppPlayer = nullptr;
    m_pFileLoad = nullptr;
    m_pMeshDome = nullptr;
    m_pClient = nullptr;
    m_pTimer = nullptr;
    m_nSledCnt = 0;
    m_bEnd = false;
    m_fOpenDoorUISin = 0.0f;
    m_bPause = false;
    m_pPause = nullptr;

    // �l���ݒ�
    m_nNumPlayer = nNumPlayer;
}

//===============================================
// �f�X�g���N�^
//===============================================
CGame::~CGame()
{
   
}

//===============================================
// ����������
//===============================================
HRESULT CGame::Init(void)
{
    memset(&m_aAddress[0], '\0', sizeof(m_aAddress));
    int nErr = WSAStartup(WINSOCK_VERSION, &m_wsaData);	// winsock�̏������֐�

    if (nErr != 0)
    {// �������Ɏ��s�����ꍇ
        m_state = STATE_LOCAL;
    }

    // �O���t�@�C���ǂݍ��݂̐���
    CFileLoad::GetInstance()->OpenFile("data\\TXT\\model.txt");

    switch (m_state)
    {
    case STATE_LOCAL:
    {// ���[�J���̏ꍇ
        if (m_nNumPlayer <= 0)
        {// �l�����w�肳��Ă��Ȃ�
            m_nNumPlayer = 1;
        }

        CPlayer *pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

        m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.2f - 40.0f * 4, 30.0f, 0.0f), 8, 1.0f, 20.0f, 60.0f);
        pPlayer->SetScore(m_pScore);
    }
        break;

    case STATE_ONLINE:
    {// �I�����C���ʐM�̏ꍇ
        m_pClient = new CClient;
        AddressLoad(&m_aAddress[0]);

        if (m_pClient->Init(&m_aAddress[0], DEF_PORT))
        {// �����ڑ�����
            // �I�����C���֐����}���`�X���b�h
            std::thread th(&CGame::Online, this);
            th.detach();
        }
    }
        break;

    default:

        break;
    }


    //CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_GAME);
    CMeshDome::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15000.0f, 3000.0f, 3, 8, 8);
    CFlower::Create(D3DXVECTOR3(400.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

    m_pSun = CSunTask::Create();
    m_pTimer = CTime::Create(D3DXVECTOR3(550.0f, 100.0f, 0.0f));
    m_pTimer->Set(0);
    m_pTimer->SetMax(MAX_TIME * 2);

    return S_OK;
}

//===============================================
// �I������
//===============================================
void CGame::Uninit(void)
{
   CManager::GetInstance()->GetSound()->Stop();

    m_bEnd = true;

    while (1)
    {
        OnlineEnd();
        if (m_nSledCnt <= 0)
        {
            break;
        }
    }

    // �N���C�A���g
    if (m_pClient != nullptr)
    {
        m_pClient->Uninit();
        delete m_pClient;
        m_pClient = nullptr;
    }

    if (m_pScore != nullptr) {
        m_pScore->Uninit();
        delete m_pScore;
        m_pScore = nullptr;
    }

    if (m_pTimer != nullptr) {
        m_pTimer->Uninit();
        delete m_pTimer;
        m_pTimer = nullptr;
    }

    CFileLoad::Release();

    // default�J�����I��
    CManager::GetInstance()->GetCamera()->SetDraw(true);

    //Winsock�I������
    WSACleanup();	// WSACleanup�֐� : winsock�̏I������

    m_state = STATE_LOCAL;
}

//===============================================
// �X�V����
//===============================================
void CGame::Update(void)
{
    CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();
    CInputKeyboard *pInputKey = CManager::GetInstance()->GetInputKeyboard();

    if (pInputKey->GetTrigger(DIK_P) == true || pInputPad->GetTrigger(CInputPad::BUTTON_START, 0))
    {//�|�[�Y�L�[(P�L�[)�������ꂽ
        m_bPause = m_bPause ? false : true;
    }

    if (m_pTimer != nullptr) {
        m_pTimer->Update();

        if (m_pTimer->GetNum() >= MAX_TIME) {
            CManager::GetInstance()->GetFade()->Set(CScene::MODE_RESULT);
        }
    }

    CScene::Update();
}

//===============================================
// �`�揈��
//===============================================
void CGame::Draw(void)
{
    CScene::Draw();
}

//===================================================
// �v���C���[�̎擾
//===================================================
CPlayer *CGame::GetPlayer(void)
{
    return *m_ppPlayer;
}

//===================================================
// �t�@�C���ǂݍ��݂̎擾
//===================================================
CFileLoad *CGame::GetFileLoad(void)
{
    return m_pFileLoad;
}

//===================================================
// �I�����C���ʐM
//===================================================
void CGame::Online(void)
{
    m_nSledCnt = 1;

    while (1)
    {
        if (m_ppPlayer == NULL || m_bEnd == true)
        {
            break;
        }

        char aRecvData[MAX_STRING] = {};	// ��M�p

        // ��M
        int nRecvByte = m_pClient->Recv(&aRecvData[0], MAX_STRING);

        // �}���`�X���b�h
        std::thread th(&CGame::ByteCheck, this, &aRecvData[0], nRecvByte);
        th.detach();
    }

    m_nSledCnt--;
}

//===================================================
// ��M�m�F
//===================================================
void CGame::ByteCheck(char *pRecvData, int nRecvByte)
{
    m_mutex.lock();

    //m_nSledCnt++;
    //D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    //D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    //int nType = COMMAND_TYPE_NONE;	// �R�}���h�ԍ�
    //int nId = -1;		// ID
    //int nByte = 0;	// �o�C�g��
    //int nDamage = 0;	// �_���[�W��
    //CPlayer *pPlayer = NULL;		// �擪���擾
    //CPlayer *pPlayerNext = NULL;	// ����ێ�

    //if (nRecvByte <= 0)
    //{
    //    m_nSledCnt--;
    //    m_mutex.unlock();
    //    return;
    //}

    //pPlayer = CPlayerManager::GetInstance()->GetTop();	// �擪���擾

    //// �I�[�����܂Ŋm�F����
    //while (nByte < nRecvByte)
    //{
    //    bool bIn = false;	// ���ɂ��邩�ǂ���
    //    memcpy(&nId, &pRecvData[nByte], sizeof(int));
    //    nByte += sizeof(int);

    //    // �R�}���h�擾
    //    memcpy(&nType, &pRecvData[nByte], sizeof(int));
    //    nByte += sizeof(int);

    //    if (nId != -1)
    //    {
    //        // �R�}���h���Ƃɕ�����
    //        switch (nType)
    //        {

    //        case COMMAND_TYPE_SETPOSITION:

    //            memcpy(&pos, &pRecvData[nByte], sizeof(D3DXVECTOR3));
    //            nByte += sizeof(D3DXVECTOR3);
    //            break;

    //        case COMMAND_TYPE_SETROTATION:

    //            memcpy(&pos, &pRecvData[nByte], sizeof(D3DXVECTOR3));
    //            nByte += sizeof(D3DXVECTOR3);
    //            break;

    //        case COMMAND_TYPE_SETLIFE:

    //            memcpy(&nDamage, &pRecvData[nByte], sizeof(int));
    //            nByte += sizeof(int);
    //            break;

    //        case COMMAND_TYPE_START_OK:

    //            break;

    //        case COMMAND_TYPE_CREATE:
    //            break;

    //        case COMMAND_TYPE_DAMAGE:

    //            memcpy(&nDamage, &pRecvData[nByte], sizeof(int));
    //            nByte += sizeof(int);
    //            break;

    //        case COMMAND_TYPE_DELETE:
    //            break;

    //        case COMMAND_TYPE_GETID:
    //            break;
    //        }
    //    }

    //    if (m_ppPlayer == NULL)
    //    {
    //        m_nSledCnt--;
    //        m_mutex.unlock();
    //        return;
    //    }

    //    if (nId != -1 && (*m_ppPlayer)->GetId() != -1)
    //    {// ID����M�ł���

    //        pPlayer = CPlayerManager::GetInstance()->GetTop();	// �擪���擾

    //        while (pPlayer != NULL)
    //        {// �g�p����Ă���ԌJ��Ԃ�
    //            pPlayerNext = pPlayer->GetNext();	// ����ێ�

    //            if (nId == pPlayer->GetId() && (*m_ppPlayer)->GetId() != nId)
    //            {// �����ȊO�����삵�Ă��Ȃ�

    //             // �R�}���h���Ƃɕ�����
    //                switch (nType)
    //                {
    //                case COMMAND_TYPE_SETPOSITION:

    //                    pPlayer->SetPosition(pos);
    //                    break;

    //                case COMMAND_TYPE_SETROTATION:

    //                    pPlayer->SetRotation(pos);
    //                    break;

    //                case COMMAND_TYPE_SETLIFE:

    //                    pPlayer->SetLife(nDamage);
    //                    break;

    //                case COMMAND_TYPE_START_OK:

    //                    break;

    //                case COMMAND_TYPE_CREATE:

    //                    break;

    //                case COMMAND_TYPE_DAMAGE:

    //                    pPlayer->Damage(nDamage);
    //                    break;

    //                case COMMAND_TYPE_GOAL:

    //                    break;

    //                case COMMAND_TYPE_DELETE:

    //                    pPlayer->Uninit();
    //                    break;

    //                case COMMAND_TYPE_GETID:

    //                    break;
    //                }

    //                bIn = true;	// �����Ԃɂ���
    //                break;
    //            }
    //            else if (nId == pPlayer->GetId() && (*m_ppPlayer)->GetId() == nId)
    //            {// �����ȊO������L����

    //                bIn = true;	// �����Ԃɂ���
    //                break;
    //            }

    //            pPlayer = pPlayerNext;	// ���Ɉړ�
    //        }

    //        if (bIn == false && (*m_ppPlayer)->GetId() != -1 && nType > COMMAND_TYPE_NONE && nType < COMMAND_TYPE_MAX)
    //        {// �܂����݂��Ă��Ȃ��ꍇ
    //            pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), NULL, NULL);
    //            pPlayer->BindId(nId);
    //            pPlayer->SetType(CPlayer::TYPE_NONE);
    //        }
    //    }
    //    else if (nId == -1 && (*m_ppPlayer)->GetId() == -1)
    //    {// ID����M�ł��Ă��Ȃ����������g��ID�����݂��Ă��Ȃ�
    //        nId = nType;

    //        // ������ID��ݒ�
    //        (*m_ppPlayer)->BindId(nId);

    //        break;
    //    }
    //}

    //m_nSledCnt--;
    m_mutex.unlock();
}

//===================================================
// ���W���M
//===================================================
void CGame::SendPosition(D3DXVECTOR3& pos)
{
    if (m_pClient != nullptr)
    {
        char aSendData[MAX_STRING] = {};	// ���M�p
        int nProt = COMMAND_TYPE_SETPOSITION;

        // protocol��}��
        memcpy(&aSendData[0], &nProt, sizeof(int));

        // ���W��}��
        memcpy(&aSendData[sizeof(int)], &pos, sizeof(D3DXVECTOR3));

        // ���M
        m_pClient->Send(&aSendData[0], sizeof(int) + sizeof(D3DXVECTOR3));
    }
}

//===================================================
// �������M
//===================================================
void CGame::SendRotation(D3DXVECTOR3& rot)
{
    if (m_pClient != nullptr)
    {
        char aSendData[MAX_STRING] = {};	// ���M�p
        int nProt = COMMAND_TYPE_SETROTATION;

        // protocol��}��
        memcpy(&aSendData[0], &nProt, sizeof(int));

        // ���W��}��
        memcpy(&aSendData[sizeof(int)], &rot, sizeof(D3DXVECTOR3));

        // ���M
        m_pClient->Send(&aSendData[0], sizeof(int) + sizeof(D3DXVECTOR3));
    }
}

//===================================================
// �_���[�W���M
//===================================================
void CGame::SendDamage(int nDamage)
{
    if (m_pClient != nullptr)
    {
        char aSendData[MAX_STRING] = {};	// ���M�p
        int nProt = COMMAND_TYPE_DAMAGE;

        // protocol��}��
        memcpy(&aSendData[0], &nProt, sizeof(int));

        // �_���[�W��}��
        memcpy(&aSendData[sizeof(int)], &nDamage, sizeof(int));

        // ���M
        m_pClient->Send(&aSendData[0], sizeof(int) + sizeof(int));
    }
}

//===================================================
// �̗͑��M
//===================================================
void CGame::SendLife(int nLife)
{
    if (m_pClient != nullptr)
    {
        char aSendData[MAX_STRING] = {};	// ���M�p
        int nProt = COMMAND_TYPE_SETLIFE;

        // protocol��}��
        memcpy(&aSendData[0], &nProt, sizeof(int));

        // �_���[�W��}��
        memcpy(&aSendData[sizeof(int)], &nLife, sizeof(int));

        // ���M
        m_pClient->Send(&aSendData[0], sizeof(int) + sizeof(int));
    }
}

//===================================================
// �I�����M
//===================================================
void CGame::OnlineEnd(void)
{
    if (m_pClient != nullptr)
    {
        char aSendData[MAX_STRING] = {};	// ���M�p
        int nProt = COMMAND_TYPE_DELETE;

        // protocol��}��
        memcpy(&aSendData[0], &nProt, sizeof(int));

        // ���M
        m_pClient->Send(&aSendData[0], sizeof(int));
    }
}

//===============================================
// �̗͐ݒ�
//===============================================
void CGame::SendSetUp(void)
{
    if (m_pClient != nullptr)
    {
        char aSendData[MAX_STRING] = {};	// ���M�p
        int nProt = COMMAND_TYPE_START_OK;

        // protocol��}��
        memcpy(&aSendData[0], &nProt, sizeof(int));

        // ���M
        m_pClient->Send(&aSendData[0], sizeof(int));
    }
}

//===============================================
// �S�[�����M
//===============================================
void CGame::SendGoal(void)
{
    if (m_pClient != nullptr)
    {
        char aSendData[MAX_STRING] = {};	// ���M�p
        int nProt = COMMAND_TYPE_GOAL;

        // protocol��}��
        memcpy(&aSendData[0], &nProt, sizeof(int));


        // ���M
        m_pClient->Send(&aSendData[0], sizeof(int));
    }
}

//===================================================
// �A�h���X�ǂݍ���
//===================================================
void CGame::AddressLoad(char *pAddrss)
{
    FILE *pFile;	// �t�@�C���ւ̃|�C���^

    pFile = fopen(ADDRESSFILE, "r");

    if (pFile != NULL)
    {//�t�@�C�����J�����ꍇ
        
        //�e�L�X�g�ǂݍ���
        fscanf(pFile, "%s", pAddrss);

        //�t�@�C�������
        fclose(pFile);
    }
    else
    {//�t�@�C�����J���Ȃ������ꍇ
        return;
    }
}

//===================================================
// �J�n���o
//===================================================
bool CGame::StartDirection(void)
{
    return false;
}