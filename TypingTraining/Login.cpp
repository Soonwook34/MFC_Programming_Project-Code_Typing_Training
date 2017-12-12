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
	DDX_Control(pDX, IDC_NAME, m_name);
	DDX_Control(pDX, IDC_LOGIN1, m_id);
	DDX_Control(pDX, IDC_LOGIN2, m_pw);
}


BEGIN_MESSAGE_MAP(CLogin, CDialog)
	ON_BN_CLICKED(IDC_GO_MAIN, &CLogin::OnBnClickedGoMain)
	ON_BN_CLICKED(IDC_JOIN, &CLogin::OnBnClickedJoin)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
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
	//CString l;
	//l.Format(_T("%d"), n);
	//MessageBox(l);
	if (input_str == _T("."))
		MessageBox(_T("로그인 실패"));
	else if (str_pw == _T(""))
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


HBRUSH CLogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	switch (nCtlColor) {
	case CTLCOLOR_DLG:
		return (HBRUSH)GetStockObject(BLACK_BRUSH);
		break;
	case CTLCOLOR_BTN:
		pDC->SetBkMode(BLACK_BRUSH);
		return (HBRUSH)GetStockObject(BLACK_BRUSH);
		break;
	case CTLCOLOR_STATIC:
	case CTLCOLOR_EDIT:
		pDC->SetTextColor(RGB(255, 255, 200));
		pDC->SetBkColor(BLACK_BRUSH);
		return (HBRUSH)GetStockObject(BLACK_BRUSH);
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


BOOL CLogin::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(0, 0, 0));
	return CDialog::OnEraseBkgnd(pDC);
}

 
BOOL CLogin::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CFont font1, font2;
	font1.CreatePointFont(200, _T("Consolas"));
	font2.CreatePointFont(150, _T("Consolas"));
	m_name.SetFont(&font1);
	m_id.SetFont(&font2);
	m_pw.SetFont(&font2);
	font1.Detach();
	font2.Detach();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
