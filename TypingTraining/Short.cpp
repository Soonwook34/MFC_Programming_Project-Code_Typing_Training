// Short.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TypingTraining.h"
#include "Short.h"
#include "afxdialogex.h"
#include "TypingTrainingDoc.h"
#include "TypingTrainingView.h"
#include "Info.h"

class CInfo;

//abcdefghijklmn
//hi
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
	DDX_Control(pDX, IDC_COPY1, m_copy1);
	DDX_Control(pDX, IDC_STR2, m_str2);
	DDX_Control(pDX, IDC_STR3, m_str3);
	DDX_Control(pDX, IDC_STR4, m_str4);
	DDX_Control(pDX, IDC_STR5, m_str5);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Control(pDX, IDC_PRESENT, m_present);
	DDX_Control(pDX, IDC_BEST, m_best);
	DDX_Control(pDX, IDC_ACCURACY, m_accuracy);
}


BEGIN_MESSAGE_MAP(CShort, CDialog)
	ON_BN_CLICKED(IDC_GO_BACK, &CShort::OnBnClickedGoBack)
	ON_EN_MAXTEXT(IDC_COPY1, &CShort::OnEnMaxtextCopy1)
	ON_EN_CHANGE(IDC_COPY1, &CShort::OnEnChangeCopy1)
	ON_WM_TIMER()
	ON_WM_PAINT()
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


BOOL CShort::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CStdioFile file;
	CFileException e;
	CString temp;
	CString str[5];
	int a[5];
	int num = 0;		//���Ͽ� ����ִ� ���ڿ� ����

	if (!file.Open(_T("a.txt"), CFile::modeRead, &e)) {
		e.ReportError();
		return TRUE;
	}

	while (file.ReadString(temp)) {			//�� �پ� �о����
		num++;
	}

	//file ó������ �̵�
	file.SeekToBegin();

	//�ؽ�Ʈ���Ͽ� �ִ� ���ڿ��� tempstr�迭�� �����ϱ�
	CString *tempstr = new CString[num];

	for (int i = 0; i < num; i++) {
		file.ReadString(tempstr[i]);
		tempstr[i] = tempstr[i].Trim(_T("\t"));
	}

	srand((unsigned)time(NULL));

	//���� 5���� ���� ���� a�迭�� ����
	for (int i = 0; i < 5; i++) {
		a[i] = rand() % num;
		while (true) {
			int ch = 1;
			for (int j = 0; j < i; j++) {
				if (tempstr[a[i]].GetLength() < 10 || tempstr[a[i]].GetLength() > 30 || a[i] == a[j]) {
					ch = 0;
					a[i] = rand() % num;
					break;
				}
			}
			if (ch == 1)
				break;
		}

	}

	for (int i = 0; i < 5; i++) {
		int t = a[i];
		str[i] = tempstr[t];
	}

	str1 = str[0];
	m_str2.SetWindowText(str[1]);
	m_str3.SetWindowText(str[2]);
	m_str4.SetWindowText(str[3]);
	m_str5.SetWindowText(str[4]);

	m_copy1.SetLimitText(str1.GetLength());


	ch_num = str1.GetLength();


	col = new int[str1.GetLength()];

	CString progress;
	progress.Format(_T("%d%%"), str_num * 100 / str_allnum);
	m_progress.SetWindowText(progress);
	same = 2;
	first = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CShort::OnEnMaxtextCopy1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	str_num++;
	CString temp;
	CString tmp;
	CString *str = new CString[4];
	m_str2.GetWindowText(tmp);
	str1 = tmp;

	m_str3.GetWindowText(temp);
	m_str2.SetWindowText(temp);
	m_str4.GetWindowText(temp);
	m_str3.SetWindowText(temp);
	m_str5.GetWindowText(temp);
	m_str4.SetWindowText(temp);

	str[0] = str1;
	m_str2.GetWindowText(str[1]);
	m_str3.GetWindowText(str[2]);
	m_str4.GetWindowText(str[3]);

	CStdioFile file;
	CFileException e;


	int num = 0;		//���Ͽ� ����ִ� ���ڿ� ����
	int i = 0;
	if (!file.Open(_T("a.txt"), CFile::modeRead, &e)) {
		e.ReportError();
		return;
	}

	while (file.ReadString(temp)) {			//�� �پ� �о����
		num++;
	}

	//file ó������ �̵�
	file.SeekToBegin();

	//�ؽ�Ʈ���Ͽ� �ִ� ���ڿ��� tempstr�迭�� �����ϱ�
	CString *tempstr = new CString[num];

	for (int i = 0; i < num; i++) {
		file.ReadString(tempstr[i]);
		tempstr[i] = tempstr[i].Trim(_T("\t"));
	}

	int t;
	t = rand() % num;
	while (true) {
		int ch = 1;
		for (int i = 0; i < 4; i++) {
			if (tempstr[t].GetLength() < 10 || tempstr[t].Compare(str[i]) == 0) {
				ch = 0;
				t = rand() % num;
				break;
			}
		}
		if (ch == 1)
			break;
	}


	m_str5.SetWindowText(tempstr[t]);


	m_copy1.SetLimitText(str1.GetLength());

	m_copy1.SetWindowText(_T(""));
	same = 2;



	ch_allnum += ch_num;
	ch_allnum2 += ch_num2;

	CString progress;
	progress.Format(_T("%d%%"), str_num * 100 / str_allnum);
	m_progress.SetWindowText(progress);

	CString accuracy;
	accuracy.Format(_T("%d%%"), ch_allnum2 * 100 / ch_allnum);
	m_accuracy.SetWindowText(accuracy);


	ch_num = str1.GetLength();

	col = new int[str1.GetLength()];

	ch_num2 = 0;
	KillTimer(1);
	times = 0;
	first = TRUE;

	if (besttemp > best) {
		best = besttemp;
		CString temp;
		temp.Format(_T("%d"), best);
		m_best.SetWindowText(temp);
	}

	avgtyping += besttemp;

	if (str_num >= str_allnum - 4)
		m_str5.SetWindowText(_T(""));

	if (str_num == str_allnum) {
		CString end;
		avgtyping = avgtyping / str_num;
		alltime = alltime / 10;
		endTime = clock();
		totalTime = (endTime - startTime) / 1000;
		if (totalTime / 60 >= 1)
			end.Format(_T("������: %d\n��Ȯ��: %d\n�����ð�: %d�� %d��\n"), avgtyping, ch_allnum2 * 100 / ch_allnum, totalTime / 60, totalTime % 60);
		else
			end.Format(_T("������: %d\n��Ȯ��: %d\n�����ð�:%d��\n"), avgtyping, ch_allnum2 * 100 / ch_allnum, totalTime);
		
		MessageBox(end, _T("ª�� �� ����"));
		DestroyWindow();
		//exit(0);
	}
}


BOOL CShort::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_RETURN && (m_copy1.GetWindowTextLength() == str1.GetLength()))
		{
			str_num++;
			CString temp;
			CString tmp;
			CString *str = new CString[4];
			m_str2.GetWindowText(tmp);
			str1 = tmp;

			m_str3.GetWindowText(temp);
			m_str2.SetWindowText(temp);
			m_str4.GetWindowText(temp);
			m_str3.SetWindowText(temp);
			m_str5.GetWindowText(temp);
			m_str4.SetWindowText(temp);


			str[0] = str1;
			m_str2.GetWindowText(str[1]);
			m_str3.GetWindowText(str[2]);
			m_str4.GetWindowText(str[3]);

			CStdioFile file;
			CFileException e;


			int num = 0;		//���Ͽ� ����ִ� ���ڿ� ����
			int i = 0;
			if (!file.Open(_T("a.txt"), CFile::modeRead, &e)) {
				e.ReportError();
				return FALSE;
			}

			while (file.ReadString(temp)) {			//�� �پ� �о����
				num++;
			}

			//file ó������ �̵�
			file.SeekToBegin();

			//�ؽ�Ʈ���Ͽ� �ִ� ���ڿ��� tempstr�迭�� �����ϱ�
			CString *tempstr = new CString[num];

			for (int i = 0; i < num; i++) {
				file.ReadString(tempstr[i]);
				tempstr[i] = tempstr[i].Trim(_T("\t"));
			}

			int t;
			t = rand() % num;
			while (true) {
				int ch = 1;
				for (int i = 0; i < 4; i++) {
					if (tempstr[t].GetLength() < 10 || tempstr[t].Compare(str[i]) == 0) {
						ch = 0;
						t = rand() % num;
						break;
					}
				}
				if (ch == 1)
					break;
			}


			m_str5.SetWindowText(tempstr[t]);

			m_copy1.SetLimitText(str1.GetLength());
			m_copy1.SetWindowText(_T(""));
			same = 2;

			ch_allnum += ch_num;
			ch_allnum2 += ch_num2;

			CString progress;
			progress.Format(_T("%d%%"), str_num * 100 / str_allnum);
			m_progress.SetWindowText(progress);


			CString accuracy;
			accuracy.Format(_T("%d%%"), ch_allnum2 * 100 / ch_allnum);
			m_accuracy.SetWindowText(accuracy);


			ch_num = str1.GetLength();

			col = new int[str1.GetLength()];

			ch_num2 = 0;
			KillTimer(1);
			times = 0;
			first = TRUE;
			if (besttemp > best) {
				best = besttemp;
				CString temp;
				temp.Format(_T("%d"), best);
				m_best.SetWindowText(temp);
			}
			avgtyping += besttemp;
		}

		else if (pMsg->wParam == VK_BACK) {
			bspace = TRUE;
			if (same == 1 && ch_num2 != 0)
				ch_num2--;

		}

		//����Ű ��ȿȭ
		else if (pMsg->wParam == VK_LEFT)
			return TRUE;
		else if (pMsg->wParam == VK_RIGHT)
			return TRUE;
		else if (pMsg->wParam == VK_ESCAPE) {
			OnBnClickedGoBack();
			return TRUE;
		}
		else if (pMsg->wParam==VK_TAB)
			return TRUE;
	}

	if (str_num >= str_allnum - 4)
		m_str5.SetWindowText(_T(""));
	if (str_num == str_allnum) {
		CString end;
		alltime = alltime / 10;
		avgtyping = avgtyping / str_num;
		endTime = clock();
		totalTime = (endTime - startTime) / 1000;
		if (totalTime / 60 >= 1)
			end.Format(_T("������: %d\n��Ȯ��: %d\n�����ð�: %d�� %d��\n"), avgtyping, ch_allnum2 * 100 / ch_allnum, totalTime / 60, totalTime % 60);
		else
			end.Format(_T("������: %d\n��Ȯ��: %d\n�����ð�:%d��\n"), avgtyping, ch_allnum2 * 100 / ch_allnum, totalTime);
		MessageBox(end, _T("ª�� �� ����"));
		DestroyWindow();
		return TRUE;
		//exit(0);
	}

	//���콺 Ŭ�� ��ȿȭ
	if (GetDlgItem(IDC_COPY1)->m_hWnd == pMsg->hwnd && pMsg->message == WM_LBUTTONDOWN)
		return TRUE;
	else if (GetDlgItem(IDC_COPY1)->m_hWnd == pMsg->hwnd && pMsg->message == WM_LBUTTONDBLCLK)
		return TRUE;
	else if (GetDlgItem(IDC_COPY1)->m_hWnd == pMsg->hwnd && pMsg->message == WM_MBUTTONDOWN)
		return TRUE;
	else if (GetDlgItem(IDC_COPY1)->m_hWnd == pMsg->hwnd && pMsg->message == WM_MBUTTONDBLCLK)
		return TRUE;
	else if (GetDlgItem(IDC_COPY1)->m_hWnd == pMsg->hwnd && pMsg->message == WM_RBUTTONDOWN)
		return TRUE;
	else if (GetDlgItem(IDC_COPY1)->m_hWnd == pMsg->hwnd && pMsg->message == WM_RBUTTONDBLCLK)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}


void CShort::OnEnChangeCopy1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (first == TRUE)
		SetTimer(1, 100, NULL);

	if (str_num == 1)
		startTime = clock();

	CString stat, edit;
	int n = m_copy1.GetWindowTextLength();

	CString tmp;
	tmp = str1.Left(str1.GetLength());
	stat = tmp;

	stat = stat.Left(n);
	m_copy1.GetWindowText(edit);



	if (n != 0 && stat[n - 1] == edit[n - 1]) {
		if (bspace == FALSE) {
			ch_num2++;
		}
		same = 1;
		col[n - 1] = 1;
	}
	else if (n != 0) {
		same = 0;
		col[n - 1] = 0;
	}

	if (n == 0) {
		same = 2;
		for (int i = 0; i < ch_num; i++)
			col[i] = 2;
	}

	if (bspace == TRUE && n != 0)
		col[n] = 2;

	CString accuracy;
	if (n != 0) {
		accuracy.Format(_T("%d%%"), ch_num2 * 100 / n);
		m_accuracy.SetWindowText(accuracy);
	}



	bspace = FALSE;
	first = FALSE;

	Invalidate();
}


void CShort::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	times++;
	alltime++;


	CString present;
	if (times != 0) {
		present.Format(_T("%d"), ch_num2 * 600 / times);
		m_present.SetWindowText(present);
		besttemp = ch_num2 * 600 / times;
	}
	CDialog::OnTimer(nIDEvent);
}


void CShort::OnPaint()
{
	/*
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	CDC* pDC = GetDC();
	COLORREF red = RGB(255, 50, 25), blue = RGB(50, 25, 255), black = RGB(0, 0, 0);
	CPoint point = CPoint(35, 150);
	CFont font;
	font.CreatePointFont(120, _T("Consolas"));

	CString tmp;

	pDC->SelectObject(&font);

	for (int i = 0; i < str1.GetLength(); i++) {
		tmp.Format(_T("%c"), str1[i]);
		if (col[i] == 1)
			pDC->SetTextColor(blue);
		else if (col[i] == 0)
			pDC->SetTextColor(red);
		else
			pDC->SetTextColor(black);
		pDC->TextOut(point.x, point.y, tmp);
		point.x += 11;
	}
	*/

	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
	CDC* pDC = GetDC();
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(752, 480);
	pDC->SetViewportExt(rect.Width(), rect.Height());
	COLORREF red = RGB(255, 50, 25), blue = RGB(50, 25, 255), black = RGB(0, 0, 0);
	CPoint point = CPoint(31, 135);
	CFont font;
	//font.CreatePointFont(120, _T("Consolas"));
	font.CreateFont(19, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Consolas"));

	CString tmp;

	pDC->SelectObject(&font);

	for (int i = 0; i < str1.GetLength(); i++) {
		tmp.Format(_T("%c"), str1[i]);
		if (col[i] == 1)
			pDC->SetTextColor(blue);
		else if (col[i] == 0)
			pDC->SetTextColor(red);
		else
			pDC->SetTextColor(black);
		pDC->TextOut(point.x, point.y, tmp);
		point.x += 9;
	}
}
