// Login.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TypingTraining.h"
#include "Login.h"
#include "afxdialogex.h"
#include "TypingTrainingDoc.h"
#include "TypingTrainingView.h"
#include "Join.h"


// CLogin ��ȭ �����Դϴ�.

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


// CLogin �޽��� ó�����Դϴ�.


void CLogin::OnBnClickedGoMain()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		MessageBox(_T("�α��� ����"));
	else if (n >= 0) {
		MessageBox(_T("�α��� ����"));
		infofile.Close();
		//����ȭ�鿡 ���̵� �Ѱ��ֱ�
		m_pMain->str_userid = str_id;
		DestroyWindow();
	}
	else
		MessageBox(_T("�α��� ����"));
}


void CLogin::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
