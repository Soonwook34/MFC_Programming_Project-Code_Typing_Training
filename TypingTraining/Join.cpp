// Join.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TypingTraining.h"
#include "Join.h"
#include "afxdialogex.h"


// CJoin ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CJoin, CDialog)

CJoin::CJoin(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_JOIN, pParent)
	, str_newid(_T(""))
	, str_newpw(_T(""))
	, str_cfpw(_T(""))
{
	str_newid = _T("");
	str_newpw = _T("");
	str_cfpw = _T("");
}

CJoin::~CJoin()
{
}

void CJoin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NewID, m_edit_newid);
	DDX_Control(pDX, IDC_NewPW, m_edit_newpw);
	DDX_Control(pDX, IDC_ConfirmPW, m_edit_cfpw);
	DDX_Text(pDX, IDC_NewID, str_newid);
	DDX_Text(pDX, IDC_NewPW, str_newpw);
	DDX_Text(pDX, IDC_ConfirmPW, str_cfpw);
}


BEGIN_MESSAGE_MAP(CJoin, CDialog)
END_MESSAGE_MAP()


// CJoin �޽��� ó�����Դϴ�.


void CJoin::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_edit_newid.GetWindowText(str_newid);
	if (str_newid.IsEmpty() == TRUE) {
		MessageBox(_T("���̵� �Է��ϼ���."));
		m_edit_newid.SetFocus();
		return;
	}
	m_edit_newpw.GetWindowText(str_newpw);
	if (str_newpw.IsEmpty() == TRUE) {
		MessageBox(_T("��й�ȣ�� �Է��ϼ���."));
		m_edit_newpw.SetFocus();
		return;
	}
	m_edit_cfpw.GetWindowText(str_cfpw);
	if (str_cfpw != str_newpw) {
		MessageBox(_T("��й�ȣ�� ��ġ���� �ʽ��ϴ�."));
		m_edit_newpw.SetFocus();
		return;
	}
	else {
		CStdioFile infofile;
		if (infofile.Open(_T("typinguserinfo.txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::typeText))
		{
			infofile.SeekToEnd();
			infofile.WriteString(_T("\n"));
			infofile.WriteString(str_newid + _T(".")+str_newpw);
		}
		MessageBox(_T("ȸ������ �Ϸ�"));
		
	}

	CDialog::OnOK();
}
