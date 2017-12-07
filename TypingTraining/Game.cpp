// Game.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TypingTraining.h"
#include "Game.h"
#include "afxdialogex.h"
#include "TypingTrainingDoc.h"
#include "TypingTrainingView.h"


// CGame ��ȭ �����Դϴ�.

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


// CGame �޽��� ó�����Դϴ�.


void CGame::OnBnClickedGoBack()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	DestroyWindow();
}


void CGame::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pMain->ShowWindow(SW_SHOW);
	m_pMain->mode = IDD_TYPINGTRAINING_FORM;
	m_pMain->m_pGame = NULL;
	delete this;
	CDialog::PostNcDestroy();
}
