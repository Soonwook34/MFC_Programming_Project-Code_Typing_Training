// Game.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TypingTraining.h"
#include "Game.h"
#include "afxdialogex.h"
#include "TypingTrainingDoc.h"
#include "TypingTrainingView.h"
#include "locale.h"


// CGame ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CGame, CDialog)

CGame::CGame(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_GAME, pParent)
	, m_str(_T(""))
{
	m_pMain = (CTypingTrainingView*)pParent;
	ansArr.SetSize(100);
	probArr.SetSize(100);
	answer.SetSize(10);
	problem.SetSize(10);
	numberArr.SetSize(10);
	rateArr.SetSize(10);


	n = 0;

	for (int i = 0; i < 10; i++) {
		numberArr[i].Format(_T("%d"), i + 1);
	}

	for (int i = 0; i < 10; i++) {
		rateArr[i].Format(_T("%d"), i);
	}

	count = 0;
}

CGame::~CGame()
{
}

void CGame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GO_BACK, m_goBack);
	DDX_Control(pDX, IDC_QUESTION, m_prob);
	DDX_Control(pDX, IDC_RATE, m_rate);
	DDX_Control(pDX, IDC_NUM, m_num);
	//	DDX_Control(pDX, IDC_STR, m_str);
	DDX_Text(pDX, IDC_STR, m_str);
}


BEGIN_MESSAGE_MAP(CGame, CDialog)
	ON_BN_CLICKED(IDC_GO_BACK, &CGame::OnBnClickedGoBack)
	ON_BN_CLICKED(IDC_ENTER, &CGame::OnBnClickedEnter)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CGame �޽��� ó�����Դϴ�.


void CGame::OnBnClickedGoBack()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	DestroyWindow();
}


void CGame::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pMain->ShowWindow(SW_SHOW);
	m_pMain->mode = IDD_TYPINGTRAINING_FORM;
	m_pMain->m_pGame = NULL;
	delete this;
	CDialog::PostNcDestroy();
}


BOOL CGame::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	int a[10];
	int num1 = 0;
	int num2 = 0;
	CString tmp1, tmp2;

	FILE *fStream1, *fStream2;
	setlocale(LC_ALL, "korean");
	errno_t e1 = _tfopen_s(&fStream1, _T("������.txt"), _T("rt,ccs=UNICODE"));
//	if (e1 != 0) // return FALSE;
	CStdioFile file1(fStream1);
	//	file1.ReadString(tmp1);

	errno_t e2 = _tfopen_s(&fStream2, _T("�����.txt"), _T("rt,ccs=UNICODE"));
//	if (e2 != 0) return FALSE;
	CStdioFile file2(fStream2);
	//	file2.ReadString(tmp2);


	//������ ���� ���� ���پ� �о� �迭�� �ֱ�
	//	if (!file1.Open(_T("������.txt"), CFile::modeRead, &e)) {		//������
	//		e.ReportError();
	//		return;
	//	}
	for (int i = 0; file1.ReadString(tmp1); i++) {
		probArr[i] = tmp1;
		num1++;
	}
	//	if (!file2.Open(_T("�����.txt"), CFile::modeRead, &e)) {		//�����
	//		e.ReportError();
	//		return;
	//	}
	for (int i = 0; file2.ReadString(tmp2); i++) {
		ansArr[i] = tmp2;
		num2++;
	}



	//���� ���� & ���� �̱�
	srand((unsigned)time(NULL));

	for (int i = 0; i < 10; i++) {
		int aa = rand() % probArr.GetSize();
		problem[i] = probArr[aa];
		answer[i] = ansArr[aa];
		a[i] = rand() % 10;
		while (true) {
			int ch = 1;
			for (int j = 0; j < i; j++) {
				if (a[i] == a[j]) {
					ch = 0;
					a[i] = rand() % num1;
					break;
				}
			}
			if (ch == 1)
				break;
		}
	}
	for (int i = 0; i < 10; i++) {
		int t = a[i];
		problem[i] = probArr[t];
		answer[i] = ansArr[t];

	}

	//�ʱⰪ
	rate = 0;

	m_prob.SetWindowText(problem[0]);
	m_num.SetWindowText(numberArr[0]);
	m_rate.SetWindowText(_T(""));
	m_brush.CreateSolidBrush(RGB(255, 255, 255));

	m_prob.ShowWindow(SW_SHOW);
	m_num.ShowWindow(SW_SHOW);
	m_rate.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CGame::OnBnClickedEnter()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CString correct, wrong;
	correct = _T("�����Դϴ�!");
	wrong = _T("�ٽ� �����غ�����~");
	//	CString wrong2;
	//������ ���߾��� ��
	if (m_str == answer[count]) {
		AfxMessageBox(correct);
		n = 0;
		m_str = _T("");
		UpdateData(FALSE);
		count++;
		rate++;
		Invalidate();

	}

	//1ȸ Ʋ���� ��
	else {
		if (n == 1)				//2ȸ Ʋ���� ��
		{

			AfxMessageBox(answer[count]);
			count++;
			n = 0;
			m_str = _T("");
			UpdateData(FALSE);
			Invalidate();

			return;
		}
		AfxMessageBox(wrong);
		n++;
		m_str = _T("");
		UpdateData(FALSE);
	}
}


void CGame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
//	CDC* pDC = GetDC();
// �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
	int i = count;
	int j = rate;
	CString finalrate;
	if (count == 10) {
		finalrate.Format(_T("�����մϴ�! �� %d ������ ������ϴ�!"), j);
		AfxMessageBox(finalrate);
	}
	m_prob.SetWindowText(problem[i]);
	m_num.SetWindowText(numberArr[i]);
	m_rate.SetWindowText(rateArr[j]);
}


BOOL CGame::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(255, 255, 255));

	return TRUE;
}


HBRUSH CGame::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	if (pWnd->GetDlgCtrlID() == IDC_RATE)
	{
		pDC->SetBkColor(RGB(255, 255, 255));
		return m_brush;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC1)
	{
		pDC->SetBkColor(RGB(255, 255, 255));
		return m_brush;
	}
	if (pWnd->GetDlgCtrlID() == IDC_QUESTION)
	{
		pDC->SetBkColor(RGB(255, 255, 255));
		return m_brush;
	}
	if (pWnd->GetDlgCtrlID() == IDC_NUM)
	{
		pDC->SetBkColor(RGB(255, 255, 255));
		return m_brush;
	}
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}
