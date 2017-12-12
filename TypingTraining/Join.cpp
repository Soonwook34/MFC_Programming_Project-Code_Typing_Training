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
	DDX_Control(pDX, IDC_ISEXIST, m_isexist);
}


BEGIN_MESSAGE_MAP(CJoin, CDialog)
	ON_BN_CLICKED(IDC_ISEXIST, &CJoin::OnBnClickedIsexist)
	ON_EN_UPDATE(IDC_NewID, &CJoin::OnEnUpdateNewid)
	ON_EN_UPDATE(IDC_NewPW, &CJoin::OnEnUpdateNewpw)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
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
	
	if (isexist_click == FALSE) {
		MessageBox(_T("아이디 중복확인을 하세요."));
	}
	else {
		
		CStdioFile infofile;
		if (infofile.Open(_T("typinguserinfo.txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::typeText))
		{
			infofile.SeekToEnd();
			infofile.WriteString(_T("\n"));
			CString strnum;
			int num = 0;
			strnum.Format(_T("%d"), num);
			//CString blank;
			//blank = _T("    ");
			infofile.WriteString(_T("*")+str_newid + _T(".")+str_newpw+_T(".")+strnum+_T(".")+ strnum + _T(".") + strnum + _T(".")+strnum + _T(".") + strnum);
			MessageBox(_T("회원가입 완료"));
			infofile.Close();
		}
		
	}

	CDialog::OnOK();
}


void CJoin::OnBnClickedIsexist()
{
	isexist_click = TRUE;
	
	CStdioFile infofile;
	CString written_str, str;
	if (infofile.Open(_T("typinguserinfo.txt"), CFile::modeRead | CFile::typeText)){
		while (infofile.ReadString(str))
			written_str += str;
		CString checkid;
		checkid += _T("*");
		checkid += str_newid;
		checkid +=_T(".");
		//MessageBox(checkid);
		int n = written_str.Find(checkid);
		if (n < 0 || str==_T("")) {
			MessageBox(_T("사용가능한 아이디입니다."));
			//m_edit_newpw.SetFocus();
		}
		else
			MessageBox(_T("사용불가능한 아이디입니다. 다시 입력해주세요."));
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CJoin::OnEnUpdateNewid()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하여, IParam 마스크에 OR 연산하여 설정된 ENM_SCROLL 플래그를 지정하여 컨트롤에 EM_SETEVENTMASK 메시지를 보내지 않으면
	// 편집 컨트롤이 바뀐 텍스트를 표시하려고 함을 나타냅니다.
	UpdateData(TRUE);
	
	TCHAR* tchr;
	CString forid = _T("");
	int i;

	for (i = 0; i < str_newid.GetLength(); i++) {
		forid = str_newid.Mid(i, 1);
		//문자열을 문자로 변환
		tchr = (TCHAR*)(LPCTSTR)forid;

		if (!IsCharAlphaNumericA(*tchr)) {
			MessageBox(_T("숫자나 알파벳을 입력해야 합니다."));
			str_newid.Remove(*tchr);
		}
	}
	UpdateData(FALSE);
	m_edit_newid.SetSel(0, -1);
	m_edit_newid.SetSel(-1, -1);

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CJoin::OnEnUpdateNewpw()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하여, IParam 마스크에 OR 연산하여 설정된 ENM_SCROLL 플래그를 지정하여 컨트롤에 EM_SETEVENTMASK 메시지를 보내지 않으면
	// 편집 컨트롤이 바뀐 텍스트를 표시하려고 함을 나타냅니다.
	UpdateData(TRUE);

	TCHAR* tchr;
	CString forpw = _T("");
	int i;

	for (i = 0; i < str_newpw.GetLength(); i++) {
		forpw = str_newpw.Mid(i, 1);
		//문자열을 문자로 변환
		tchr = (TCHAR*)(LPCTSTR)forpw;

		int asc = 0;
		asc = __toascii(*tchr);

		if ((asc==46)|(asc==42)) {
			MessageBox(_T("입력할 수 없는 문자입니다."));
			str_newpw.Remove(*tchr);
		}
	}
	UpdateData(FALSE);
	m_edit_newid.SetSel(0, -1);
	m_edit_newid.SetSel(-1, -1);
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


HBRUSH CJoin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CJoin::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(0, 0, 0));
	return CDialog::OnEraseBkgnd(pDC);
}
