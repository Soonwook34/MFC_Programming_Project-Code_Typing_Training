// Long.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TypingTraining.h"
#include "Long.h"
#include "afxdialogex.h"
#include "TypingTrainingDoc.h"
#include "TypingTrainingView.h"


// CLong ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CLong, CDialog)

CLong::CLong(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LONG, pParent)
{
	m_pMain = (CTypingTrainingView*)pParent;
}

CLong::~CLong()
{
}

void CLong::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GO_BACK, m_goBack);
}


BEGIN_MESSAGE_MAP(CLong, CDialog)
	ON_BN_CLICKED(IDC_GO_BACK, &CLong::OnBnClickedGoBack)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CLong �޽��� ó�����Դϴ�.


void CLong::OnBnClickedGoBack()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	DestroyWindow();
}


void CLong::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pMain->ShowWindow(SW_SHOW);
	m_pMain->mode = IDD_TYPINGTRAINING_FORM;
	m_pMain->m_pLong = NULL;
	delete this;
	CDialog::PostNcDestroy();
}


void CLong::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
}
