// Join.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TypingTraining.h"
#include "Join.h"
#include "afxdialogex.h"


// CJoin 대화 상자입니다.

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


// CJoin 메시지 처리기입니다.


void CJoin::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_edit_newid.GetWindowText(str_newid);
	if (str_newid.IsEmpty() == TRUE) {
		MessageBox(_T("아이디를 입력하세요."));
		m_edit_newid.SetFocus();
		return;
	}
	m_edit_newpw.GetWindowText(str_newpw);
	if (str_newpw.IsEmpty() == TRUE) {
		MessageBox(_T("비밀번호를 입력하세요."));
		m_edit_newpw.SetFocus();
		return;
	}
	m_edit_cfpw.GetWindowText(str_cfpw);
	if (str_cfpw != str_newpw) {
		MessageBox(_T("비밀번호가 일치하지 않습니다."));
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
		MessageBox(_T("회원가입 완료"));
		
	}

	CDialog::OnOK();
}
