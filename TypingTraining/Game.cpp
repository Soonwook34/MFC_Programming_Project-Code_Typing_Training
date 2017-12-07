// Game.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TypingTraining.h"
#include "Game.h"
#include "afxdialogex.h"
#include "TypingTrainingDoc.h"
#include "TypingTrainingView.h"


// CGame 대화 상자입니다.

IMPLEMENT_DYNAMIC(CGame, CDialog)

CGame::CGame(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_GAME, pParent)
{
	m_pMain = (CTypingTrainingView*)pParent;
}

CGame::~CGame()
{
}

void CGame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GO_BACK, m_goBack);
}


BEGIN_MESSAGE_MAP(CGame, CDialog)
	ON_BN_CLICKED(IDC_GO_BACK, &CGame::OnBnClickedGoBack)
END_MESSAGE_MAP()


// CGame 메시지 처리기입니다.


void CGame::OnBnClickedGoBack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DestroyWindow();
}


void CGame::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pMain->ShowWindow(SW_SHOW);
	m_pMain->mode = IDD_TYPINGTRAINING_FORM;
	m_pMain->m_pGame = NULL;
	delete this;
	CDialog::PostNcDestroy();
}
