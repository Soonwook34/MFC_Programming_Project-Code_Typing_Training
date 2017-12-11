// Login.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TypingTraining.h"
#include "Login.h"
#include "afxdialogex.h"
#include "TypingTrainingDoc.h"
#include "TypingTrainingView.h"
#include "Join.h"


// CLogin 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLogin, CDialog)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LOGIN, pParent)
{
	m_pMain = (CTypingTrainingView *)pParent;
}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GO_MAIN, m_goMain);
	DDX_Control(pDX, IDC_ID, m_edit_id);
	DDX_Control(pDX, IDC_PW, m_edit_pw);
	DDX_Control(pDX, IDC_JOIN, m_join);
}


BEGIN_MESSAGE_MAP(CLogin, CDialog)
	ON_BN_CLICKED(IDC_GO_MAIN, &CLogin::OnBnClickedGoMain)
	ON_BN_CLICKED(IDC_JOIN, &CLogin::OnBnClickedJoin)
END_MESSAGE_MAP()


// CLogin 메시지 처리기입니다.


void CLogin::OnBnClickedGoMain()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString input_str;
	m_edit_id.GetWindowText(str_id);
	input_str += str_id;
	input_str += _T(".");
	m_edit_pw.GetWindowText(str_pw);
	input_str += str_pw;

	CStdioFile infofile;
	CString written_str, str;
	if (infofile.Open(_T("typinguserinfo.txt"), CFile::modeRead | CFile::typeText)) {
		while (infofile.ReadString(str)) {
			written_str += str;
		}
	}
	//written_str.Replace(_T("\r\n"), _T(" "));
	int n = written_str.Find(input_str);
	if (input_str == _T("."))
		MessageBox(_T("로그인 실패"));
	else if (n >= 0) {
		MessageBox(_T("로그인 성공"));
		infofile.Close();
		//메인화면에 아이디 넘겨주기
		m_pMain->str_userid = str_id;
		DestroyWindow();
	}
	else
		MessageBox(_T("로그인 실패"));
}


void CLogin::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pMain->ShowWindow(SW_SHOW);
	m_pMain->mode = IDD_TYPINGTRAINING_FORM;
	m_pMain->m_pLogin = NULL;
	m_pMain->str_userid = str_id;
	m_pMain->str_userpw = str_pw;
	delete this;
	CDialog::PostNcDestroy();
}


void CLogin::OnBnClickedJoin()
{
	CJoin join;
	join.DoModal();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
