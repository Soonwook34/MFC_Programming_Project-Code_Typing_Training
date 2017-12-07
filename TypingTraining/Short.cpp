// Short.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TypingTraining.h"
#include "Short.h"
#include "afxdialogex.h"
#include "TypingTrainingDoc.h"
#include "TypingTrainingView.h"


// CShort ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CShort, CDialog)

CShort::CShort(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SHORT, pParent)
{
	m_pMain = (CTypingTrainingView*)pParent;
}

CShort::~CShort()
{
}

void CShort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GO_BACK, m_goBack);
}


BEGIN_MESSAGE_MAP(CShort, CDialog)
	ON_BN_CLICKED(IDC_GO_BACK, &CShort::OnBnClickedGoBack)
END_MESSAGE_MAP()


// CShort �޽��� ó�����Դϴ�.


void CShort::OnBnClickedGoBack()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	DestroyWindow();
}


void CShort::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pMain->ShowWindow(SW_SHOW);
	m_pMain->mode = IDD_TYPINGTRAINING_FORM;
	m_pMain->m_pShort = NULL;
	delete this;
	CDialog::PostNcDestroy();
}
