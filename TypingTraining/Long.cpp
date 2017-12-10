// Long.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TypingTraining.h"
#include "Long.h"
#include "afxdialogex.h"
#include "TypingTrainingDoc.h"
#include "TypingTrainingView.h"
#include "LongList.h"


// CLong ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CLong, CDialog)

CLong::CLong(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LONG, pParent)
{
	m_pMain = (CTypingTrainingView*)pParent;
	fileName = _T("");
	CLongList listDlg(this);
	red = RGB(225, 50, 25);
	blue = RGB(50, 25, 225);
	black = RGB(0, 0, 0);
	speedCnt = 0;
	correctChar = 0;
	totalChar = 0;
	curPage = 0;
}

CLong::~CLong()
{
}

void CLong::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GO_BACK, m_goBack);
	DDX_Control(pDX, IDC_ACCURACY, m_accuracy);
	DDX_Control(pDX, IDC_SPEED, m_speed);
	DDX_Control(pDX, IDC_PAGE, m_page);
	DDX_Control(pDX, IDC_TIME, m_time);
	DDX_Control(pDX, IDC_FILENAME, m_fileName);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_EDIT4, m_edit4);
	DDX_Control(pDX, IDC_EDIT5, m_edit5);
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
	CFont font;
	CString c, cc;
	int i, j, k, strNum;

	font.CreatePointFont(120, _T("Consolas"));
	dc.SelectObject(&font);
	dc.SetBkColor(RGB(240, 240, 240));
	CPoint point(31, 135);
	dc.TextOut(point.x, point.y, _T("asdf"));
	strNum = (curPage - 1) * 5;
	for (i = 0; i < 5; i++) {
		for (k = 0; k < check[i].GetLength(); k++) {
			c = fileStr[strNum + i].GetAt(k);
			cc = check[i].GetAt(k);
			if (cc == _T('0')) dc.SetTextColor(blue);
			else if (cc == _T('1')) dc.SetTextColor(red);
			dc.TextOut(point.x, point.y, c);
			if (0 >= c.GetAt(0) || 127 < c.GetAt(0)) {
				point.x += 12;
			}
			else {
				point.x += 9;
			}
		}
		dc.SetTextColor(black);
		for (k; k < fileStr[strNum + i].GetLength(); k++) {
			c = fileStr[strNum + i].GetAt(k);
			dc.TextOut(point.x, point.y, c);
			if (0 >= c.GetAt(0) || 127 < c.GetAt(0)) {
				point.x += 12;
			}
			else {
				point.x += 9;
			}
		}
		point.x = 31;
		point.y += 57;
	}
}


BOOL CLong::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CLongList listDlg(this);
	if (listDlg.DoModal() == IDSTART) {
		FILE *fLoadStream;
		errno_t e = _tfopen_s(&fLoadStream, _T(".\\LongCode\\" + fileName), _T("rt,ccs=UTF-8"));

		if (e != 0) {
			AfxMessageBox(_T("���� ���� ����!"));
			return FALSE;
		}
		CStdioFile loadFile(fLoadStream);

		CString str;
		while (loadFile.ReadString(str)) {
			fileStr.Add(str);
		}
		loadFile.Close();

		if (fileStr.GetCount() % 5 == 0) {
			totalPage = fileStr.GetCount() / 5;
		}
		else {
			totalPage = fileStr.GetCount() / 5 + 1;
		}
		m_fileName.SetWindowText(fileName);
		InitLongCode();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


	void CLong::InitLongCode()
	{
		m_edit1.SetLimitText(fileStr[curPage * 5].GetLength());
		m_edit2.SetLimitText(fileStr[curPage * 5 + 1].GetLength());
		m_edit3.SetLimitText(fileStr[curPage * 5 + 2].GetLength());
		m_edit4.SetLimitText(fileStr[curPage * 5 + 3].GetLength());
		m_edit5.SetLimitText(fileStr[curPage * 5 + 4].GetLength());
		curPage++;
		CString page;
		page.Format(_T("%d / %d��"), curPage, totalPage);
		m_page.SetWindowText(page);
		for (int i = 0; i < 5; i++) {
			check[i].Empty();
		}
		Invalidate(0);
	}


	void CLong::OnTyping(CString type, int index, int strNum)
	{
		CString now;
		int currentPos = type.GetLength() - 1;
		if (type.GetLength() < check[index].GetLength()) {
			check[index].Delete(currentPos + 1, 1);
		}
		else {
			now = type.GetAt(currentPos);
			if (now == fileStr[strNum].GetAt(currentPos)) {
				speedCnt++;
				check[index].Format(_T("%s%c"), check[index], _T('0'));
			}
			else {
				check[index].Format(_T("%s%c"), check[index], _T('1'));
			}
		}
		Invalidate(0);
	}
