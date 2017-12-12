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
	DDX_Control(pDX, IDC_ISEXIST, m_isexist);
}


BEGIN_MESSAGE_MAP(CJoin, CDialog)
	ON_BN_CLICKED(IDC_ISEXIST, &CJoin::OnBnClickedIsexist)
	ON_EN_UPDATE(IDC_NewID, &CJoin::OnEnUpdateNewid)
	ON_EN_UPDATE(IDC_NewPW, &CJoin::OnEnUpdateNewpw)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
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
	
	if (isexist_click == FALSE) {
		MessageBox(_T("���̵� �ߺ�Ȯ���� �ϼ���."));
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
			MessageBox(_T("ȸ������ �Ϸ�"));
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
			MessageBox(_T("��밡���� ���̵��Դϴ�."));
			//m_edit_newpw.SetFocus();
		}
		else
			MessageBox(_T("���Ұ����� ���̵��Դϴ�. �ٽ� �Է����ּ���."));
	}
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CJoin::OnEnUpdateNewid()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�Ͽ�, IParam ����ũ�� OR �����Ͽ� ������ ENM_SCROLL �÷��׸� �����Ͽ� ��Ʈ�ѿ� EM_SETEVENTMASK �޽����� ������ ������
	// ���� ��Ʈ���� �ٲ� �ؽ�Ʈ�� ǥ���Ϸ��� ���� ��Ÿ���ϴ�.
	UpdateData(TRUE);
	
	TCHAR* tchr;
	CString forid = _T("");
	int i;

	for (i = 0; i < str_newid.GetLength(); i++) {
		forid = str_newid.Mid(i, 1);
		//���ڿ��� ���ڷ� ��ȯ
		tchr = (TCHAR*)(LPCTSTR)forid;

		if (!IsCharAlphaNumericA(*tchr)) {
			MessageBox(_T("���ڳ� ���ĺ��� �Է��ؾ� �մϴ�."));
			str_newid.Remove(*tchr);
		}
	}
	UpdateData(FALSE);
	m_edit_newid.SetSel(0, -1);
	m_edit_newid.SetSel(-1, -1);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CJoin::OnEnUpdateNewpw()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�Ͽ�, IParam ����ũ�� OR �����Ͽ� ������ ENM_SCROLL �÷��׸� �����Ͽ� ��Ʈ�ѿ� EM_SETEVENTMASK �޽����� ������ ������
	// ���� ��Ʈ���� �ٲ� �ؽ�Ʈ�� ǥ���Ϸ��� ���� ��Ÿ���ϴ�.
	UpdateData(TRUE);

	TCHAR* tchr;
	CString forpw = _T("");
	int i;

	for (i = 0; i < str_newpw.GetLength(); i++) {
		forpw = str_newpw.Mid(i, 1);
		//���ڿ��� ���ڷ� ��ȯ
		tchr = (TCHAR*)(LPCTSTR)forpw;

		int asc = 0;
		asc = __toascii(*tchr);

		if ((asc==46)|(asc==42)) {
			MessageBox(_T("�Է��� �� ���� �����Դϴ�."));
			str_newpw.Remove(*tchr);
		}
	}
	UpdateData(FALSE);
	m_edit_newid.SetSel(0, -1);
	m_edit_newid.SetSel(-1, -1);
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


HBRUSH CJoin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
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
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}


BOOL CJoin::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(0, 0, 0));
	return CDialog::OnEraseBkgnd(pDC);
}
