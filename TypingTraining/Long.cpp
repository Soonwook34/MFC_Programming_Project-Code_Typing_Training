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
	red = RGB(225, 100, 100);
	blue = RGB(150, 175, 100);
	black = RGB(255, 225, 200);
	speedCnt = 0;
	speedSum = 0;
	correctChar = 0;
	totalChar = 0;
	curPage = 0;
	start = FALSE;
	time = 0;
	tempTotal = 0;
	tempCorrect = 0;
	bestSpeed = 0;
	typeIndex = 0;
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
	DDX_Control(pDX, IDC_BESTSPEED, m_bestSpeed);
}


BEGIN_MESSAGE_MAP(CLong, CDialog)
	ON_BN_CLICKED(IDC_GO_BACK, &CLong::OnBnClickedGoBack)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT1, &CLong::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CLong::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CLong::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CLong::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CLong::OnEnChangeEdit5)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
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
	CRect rect;
	GetClientRect(&rect);
	dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetWindowExt(752, 480);
	dc.SetViewportExt(rect.Width(), rect.Height());
	
	CFont font, font2;
	CString c, cc;
	int i, j, k, strNum;

	font.CreateFont(18, 9, 0, 0, 0/*FW_BOLD*/, 0, 0, 0, 0, 0, 0, 0, 0, _T("Consolas"));
	font2.CreateFont(18, 6, 0, 0, 0/*FW_BOLD*/, 0, 0, 0, 0, 0, 0, 0, 0, _T("Consolas"));
	dc.SelectObject(&font);
	dc.SetBkColor(RGB(0, 0, 0));
	CPoint point(31, 135);
	dc.TextOut(point.x, point.y, _T("asdf"));
	strNum = (curPage - 1) * 5;
	for (i = 0; i < 5; i++) {
		if ((curPage - 1) * 5 + i - 1 > fileStr.GetCount()) {
			break;
		}
		for (k = 0; k < check[i].GetLength(); k++) {
			c = fileStr[strNum + i].GetAt(k);
			cc = check[i].GetAt(k);
			if (cc == _T('0')) dc.SetTextColor(blue);
			else if (cc == _T('1')) dc.SetTextColor(red);
			if (0 >= c.GetAt(0) || 127 < c.GetAt(0)) {
				dc.SelectObject(&font2);
				dc.TextOut(point.x, point.y, c);
				point.x += 12;
			}
			else {
				dc.SelectObject(&font);
				dc.TextOut(point.x, point.y, c);
				point.x += 9;
			}
		}
		dc.SetTextColor(black);
		for (k; k < fileStr[strNum + i].GetLength(); k++) {
			c = fileStr[strNum + i].GetAt(k);
			if (0 >= c.GetAt(0) || 127 < c.GetAt(0)) {
				dc.SelectObject(&font2);
				dc.TextOut(point.x, point.y, c);
				point.x += 12;
			}
			else {
				dc.SelectObject(&font);
				dc.TextOut(point.x, point.y, c);
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
			int tempPage = fileStr.GetCount() % 5;
			for (; tempPage < 5; tempPage++) {
				fileStr.Add(_T(""));
			}
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
		m_edit1.SetWindowText(_T(""));
		m_edit2.SetWindowText(_T(""));
		m_edit3.SetWindowText(_T(""));
		m_edit4.SetWindowText(_T(""));
		m_edit5.SetWindowText(_T(""));
		m_edit1.EnableWindow(TRUE);
		m_edit1.SetFocus();
		m_edit2.EnableWindow(FALSE);
		m_edit3.EnableWindow(FALSE);
		m_edit4.EnableWindow(FALSE);
		m_edit5.EnableWindow(FALSE);
		IsTyping = 1;
		Invalidate(0);
	}


	void CLong::OnTyping(CString type, int index, int strNum)
	{
		CString right = _T("0"), wrong = _T("1"), accuracy;
		int currentPos = type.GetLength() - 1, curCorrect = 0, curTotal = 0;
		if (check[index].GetLength() < type.GetLength()) {
			if(type.GetAt(currentPos) == fileStr[strNum].GetAt(currentPos))
				speedCnt++;
		}
		check[index].Empty();
		for (int i = 0; i < type.GetLength(); i++) {
			if (fileStr[strNum][i] == type[i]) {
				check[index].Append(right);
				curCorrect++;
			}
			else {
				check[index].Append(wrong);
			}
			curTotal++;
		}
		if (type.GetLength() != 0) {
			tempTotal = totalChar + curTotal;
			tempCorrect = correctChar + curCorrect;
		}
		if (tempTotal != 0) {
			accuracy.Format(_T("%d%%"), (int)((float)tempCorrect / (float)tempTotal * 100));
			m_accuracy.SetWindowText(accuracy);
		}
		Invalidate(0);
	}


	void CLong::OnEnChangeEdit1()
	{
		// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
		// CDialog::OnInitDialog() �Լ��� ������ 
		//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
		// �� �˸� �޽����� ������ �ʽ��ϴ�.

		// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		CString type;
		m_edit1.GetWindowText(type);
		if (!start && type.GetLength()) {
			SetTimer(1210, 200, NULL);
			start = TRUE;
		}
		int strNum = (curPage - 1) * 5;
		OnTyping(type, 0, strNum);
	}


	void CLong::OnEnChangeEdit2()
	{
		// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
		// CDialog::OnInitDialog() �Լ��� ������ 
		//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
		// �� �˸� �޽����� ������ �ʽ��ϴ�.

		// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		int strNum = (curPage - 1) * 5 + 1;
		CString type;
		m_edit2.GetWindowText(type);
		OnTyping(type, 1, strNum);
	}


	void CLong::OnEnChangeEdit3()
	{
		// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
		// CDialog::OnInitDialog() �Լ��� ������ 
		//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
		// �� �˸� �޽����� ������ �ʽ��ϴ�.

		// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		int strNum = (curPage - 1) * 5 + 2;
		CString type;
		m_edit3.GetWindowText(type);
		OnTyping(type, 2, strNum);
	}


	void CLong::OnEnChangeEdit4()
	{
		// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
		// CDialog::OnInitDialog() �Լ��� ������ 
		//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
		// �� �˸� �޽����� ������ �ʽ��ϴ�.

		// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		int strNum = (curPage - 1) * 5 + 3;
		CString type;
		m_edit4.GetWindowText(type);
		OnTyping(type, 3, strNum);
	}


	void CLong::OnEnChangeEdit5()
	{
		// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
		// CDialog::OnInitDialog() �Լ��� ������ 
		//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
		// �� �˸� �޽����� ������ �ʽ��ϴ�.

		// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		int strNum = (curPage - 1) * 5 + 4;
		CString type;
		m_edit5.GetWindowText(type);
		OnTyping(type, 4, strNum);
	}


	BOOL CLong::PreTranslateMessage(MSG* pMsg)
	{
		// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 53) {
			if (GetKeyState(VK_SHIFT) < 0) {
				CString str, percent = _T("%");
				switch (IsTyping) {
				case 1:
					m_edit1.GetWindowText(str);
					str.Append(percent);
					m_edit1.SetSel(0, -1);
					m_edit1.ReplaceSel(str);
					m_edit1.SetFocus();
					break;
				case 2:
					m_edit2.GetWindowText(str);
					str.Append(percent);
					m_edit2.SetSel(0, -1);
					m_edit2.ReplaceSel(str);
					m_edit2.SetFocus();
					break;
				case 3:
					m_edit3.GetWindowText(str);
					str.Append(percent);
					m_edit3.SetSel(0, -1);
					m_edit3.ReplaceSel(str);
					m_edit3.SetFocus();
					break;
				case 4:
					m_edit4.GetWindowText(str);
					str.Append(percent);
					m_edit4.SetSel(0, -1);
					m_edit4.ReplaceSel(str);
					m_edit4.SetFocus();
					break;
				case 5:
					m_edit5.GetWindowText(str);
					str.Append(percent);
					m_edit5.SetSel(0, -1);
					m_edit5.ReplaceSel(str);
					m_edit5.SetFocus();
					break;
				}
				return true;
			}
		}
		switch (pMsg->wParam) {
		case VK_ESCAPE:
		case VK_LEFT:
		case VK_RIGHT:
		case VK_TAB:
			return true;
		case VK_RETURN:
			switch (IsTyping) {
			case 1:
				if (check[0].GetLength() == fileStr[(curPage - 1) * 5].GetLength()) {
					totalChar = tempTotal;
					correctChar = tempCorrect;
					tempTotal = 0;
					tempCorrect = 0;
					if (fileStr[(curPage - 1) * 5 + 1].GetLength() == 0) {
						ShowFinalResult();
						return true;
					}
					m_edit1.EnableWindow(FALSE);
					m_edit2.EnableWindow(TRUE);
					m_edit2.SetFocus();
					IsTyping = 2;
				}
				break;
			case 2:
				if (check[1].GetLength() == fileStr[(curPage - 1) * 5 + 1].GetLength()) {
					totalChar = tempTotal;
					correctChar = tempCorrect;
					tempTotal = 0;
					tempCorrect = 0;
					if (fileStr[(curPage - 1) * 5 + 2].GetLength() == 0) {
						ShowFinalResult();
						return true;
					}
					m_edit2.EnableWindow(FALSE);
					m_edit3.EnableWindow(TRUE);
					m_edit3.SetFocus();
					IsTyping = 3;
				}
				break;
			case 3:
				if (check[2].GetLength() == fileStr[(curPage - 1) * 5 + 2].GetLength()) {
					totalChar = tempTotal;
					correctChar = tempCorrect;
					tempTotal = 0;
					tempCorrect = 0;
					if (fileStr[(curPage - 1) * 5 + 3].GetLength() == 0) {
						ShowFinalResult();
						return true;
					}
					m_edit3.EnableWindow(FALSE);
					m_edit4.EnableWindow(TRUE);
					m_edit4.SetFocus();
					IsTyping = 4;
				}
				break;
			case 4:
				if (check[3].GetLength() == fileStr[(curPage - 1) * 5 + 3].GetLength()) {
					totalChar = tempTotal;
					correctChar = tempCorrect;
					tempTotal = 0;
					tempCorrect = 0;
					if (fileStr[(curPage - 1) * 5 + 4].GetLength() == 0) {
						ShowFinalResult();
						return true;
					}
					m_edit4.EnableWindow(FALSE);
					m_edit5.EnableWindow(TRUE);
					m_edit5.SetFocus();
					IsTyping = 5;
				}
				break;
			case 5:
				if (check[4].GetLength() == fileStr[(curPage - 1) * 5 + 4].GetLength()) {
					totalChar = tempTotal;
					correctChar = tempCorrect;
					tempTotal = 0;
					tempCorrect = 0;
					if (curPage == totalPage) {
						ShowFinalResult();
						return true;
					}
					InitLongCode();
				}
				break;
			default:
				return true;
			}
			return true;
		}
		if (GetDlgItem(IDC_EDIT1)->m_hWnd == pMsg->hwnd && pMsg->message == WM_LBUTTONDOWN)
			return TRUE;
		else if (GetDlgItem(IDC_EDIT1)->m_hWnd == pMsg->hwnd && pMsg->message == WM_MBUTTONDOWN)
			return TRUE;
		else if (GetDlgItem(IDC_EDIT1)->m_hWnd == pMsg->hwnd && pMsg->message == WM_RBUTTONDOWN)
			return TRUE;
		else if (GetDlgItem(IDC_EDIT2)->m_hWnd == pMsg->hwnd && pMsg->message == WM_LBUTTONDOWN)
			return TRUE;
		else if (GetDlgItem(IDC_EDIT2)->m_hWnd == pMsg->hwnd && pMsg->message == WM_MBUTTONDOWN)
			return TRUE;
		else if (GetDlgItem(IDC_EDIT2)->m_hWnd == pMsg->hwnd && pMsg->message == WM_RBUTTONDOWN)
			return TRUE;
		else if (GetDlgItem(IDC_EDIT3)->m_hWnd == pMsg->hwnd && pMsg->message == WM_LBUTTONDOWN)
			return TRUE;
		else if (GetDlgItem(IDC_EDIT3)->m_hWnd == pMsg->hwnd && pMsg->message == WM_MBUTTONDOWN)
			return TRUE;
		else if (GetDlgItem(IDC_EDIT3)->m_hWnd == pMsg->hwnd && pMsg->message == WM_RBUTTONDOWN)
			return TRUE;
		else if (GetDlgItem(IDC_EDIT4)->m_hWnd == pMsg->hwnd && pMsg->message == WM_LBUTTONDOWN)
			return TRUE;
		else if (GetDlgItem(IDC_EDIT4)->m_hWnd == pMsg->hwnd && pMsg->message == WM_MBUTTONDOWN)
			return TRUE;
		else if (GetDlgItem(IDC_EDIT4)->m_hWnd == pMsg->hwnd && pMsg->message == WM_RBUTTONDOWN)
			return TRUE;
		else if (GetDlgItem(IDC_EDIT5)->m_hWnd == pMsg->hwnd && pMsg->message == WM_LBUTTONDOWN)
			return TRUE;
		else if (GetDlgItem(IDC_EDIT5)->m_hWnd == pMsg->hwnd && pMsg->message == WM_MBUTTONDOWN)
			return TRUE;
		else if (GetDlgItem(IDC_EDIT5)->m_hWnd == pMsg->hwnd && pMsg->message == WM_RBUTTONDOWN)
			return TRUE;
		return CDialog::PreTranslateMessage(pMsg);
	}


	void CLong::ShowFinalResult()
	{
		CString timer;
		KillTimer(1210);
		int totalSpeed = (int)((float)correctChar / (float)time * 600);
		timer.Format(_T("�ɸ� �ð� > %d : %d\n��� Ÿ�� > %dŸ/min\n�ְ� Ÿ�� > %dŸ/min\n��Ȯ�� > %d%%"), time / 600, (time % 600) / 10, totalSpeed, bestSpeed, (int)((float)correctChar / (float)totalChar * 100));
		AfxMessageBox(timer);
		m_pMain->m_letter_rsum += correctChar;
		m_pMain->m_letter_sum += totalChar;
		m_pMain->m_typenum.Add(totalSpeed);
		DestroyWindow();
		return;
	}


	void CLong::OnTimer(UINT_PTR nIDEvent)
	{
		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
		switch (nIDEvent) {
		case 1210:
			time += 2;
			if (time % 10 == 0) {
				CString timer;
				timer.Format(_T("%d : %d"), time/600, (time%600)/10);
				m_time.SetWindowText(timer);
			}
			if (typeIndex < 300) {
				speed.Add(speedCnt);
				speedSum += speedCnt;
			}
			else {
				speedSum -= speed[typeIndex % 300];
				speed[typeIndex % 300] = speedCnt;
				speedSum += speedCnt;
			}
			speedCnt = 0;
			typeIndex++;
			int curSpeed;
			if (typeIndex > 300) {
				curSpeed = speedSum;
			}
			else {
				curSpeed = speedSum * 300 / typeIndex;
			}
			CString strSpeed;
			strSpeed.Format(_T("%dŸ"), curSpeed);
			if (curSpeed > bestSpeed) {
				bestSpeed = curSpeed;
				m_bestSpeed.SetWindowText(strSpeed);
			}
			m_speed.SetWindowText(strSpeed);
		}
		CDialog::OnTimer(nIDEvent);
	}


	HBRUSH CLong::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
			pDC->SetTextColor(RGB(255, 225, 200));
			pDC->SetBkMode(BLACK_BRUSH);
			return (HBRUSH)GetStockObject(BLACK_BRUSH);
			break;
		}
		// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
		return hbr;
	}
