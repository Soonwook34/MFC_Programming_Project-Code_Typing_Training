
// TypingTrainingView.cpp : CTypingTrainingView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "TypingTraining.h"
#endif

#include "TypingTrainingDoc.h"
#include "TypingTrainingView.h"
#include "Login.h"
#include "Short.h"
#include "Long.h"
#include "Game.h"
#include "Info.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTypingTrainingView

IMPLEMENT_DYNCREATE(CTypingTrainingView, CFormView)

BEGIN_MESSAGE_MAP(CTypingTrainingView, CFormView)
	ON_BN_CLICKED(IDC_GO_SHORT, &CTypingTrainingView::OnBnClickedGoShort)
	ON_BN_CLICKED(IDC_GO_LONG, &CTypingTrainingView::OnBnClickedGoLong)
	ON_BN_CLICKED(IDC_GO_GAME, &CTypingTrainingView::OnBnClickedGoGame)
	ON_BN_CLICKED(IDC_GO_STATIC, &CTypingTrainingView::OnBnClickedGoStatic)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CTypingTrainingView::OnTcnSelchangeTab)
END_MESSAGE_MAP()

// CTypingTrainingView ����/�Ҹ�

CTypingTrainingView::CTypingTrainingView()
	: CFormView(IDD_TYPINGTRAINING_FORM)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	mode = IDD_LOGIN;
	m_pLogin = NULL;
	m_pShort = NULL;
	m_pLong = NULL;
	m_pGame = NULL;
	m_pInfo = NULL;
}

CTypingTrainingView::~CTypingTrainingView()
{
}

void CTypingTrainingView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GO_SHORT, m_goShort);
	DDX_Control(pDX, IDC_GO_LONG, m_goLong);
	DDX_Control(pDX, IDC_GO_GAME, m_goGame);
	DDX_Control(pDX, IDC_GO_STATIC, m_goStatic);
	DDX_Control(pDX, IDC_TAB, m_tab);
	DDX_Control(pDX, IDC_EXPLAIN, m_explain);
	DDX_Control(pDX, IDC_USER, m_user);
	DDX_Control(pDX, IDC_IMAGE, m_imgcanvas);
}

BOOL CTypingTrainingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CTypingTrainingView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	m_tab.InsertItem(0, _T("short"), 0);
	m_tab.InsertItem(1, _T("long"), 0);
	m_tab.InsertItem(2, _T("game"), 0);
	m_tab.InsertItem(3, _T("static"), 0);

	m_tab.SetCurSel(0);
	m_explain.SetWindowTextW(_T("ª�� �ڵ� ����\r\n�ڵ� ������ �Է��ϴ� �����⿡ ����\r\n���� Ÿ���� �ְ� Ÿ���� �ǽð����� ��Ÿ���ϴ�."));

	//m_pLogin = new CLogin();
	//str_userid = m_pLogin->str_id;
}


// CTypingTrainingView ����

#ifdef _DEBUG
void CTypingTrainingView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTypingTrainingView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTypingTrainingDoc* CTypingTrainingView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTypingTrainingDoc)));
	return (CTypingTrainingDoc*)m_pDocument;
}
#endif //_DEBUG


// CTypingTrainingView �޽��� ó����


void CTypingTrainingView::OnDraw(CDC* pDC)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (mode != IDD_TYPINGTRAINING_FORM) {
		m_goShort.ShowWindow(SW_HIDE);
		m_goLong.ShowWindow(SW_HIDE);
		m_goGame.ShowWindow(SW_HIDE);
		m_goStatic.ShowWindow(SW_HIDE);
		m_tab.ShowWindow(SW_HIDE);
		m_explain.ShowWindow(SW_HIDE);
		m_imgcanvas.ShowWindow(SW_HIDE);
		//m_user.ShowWindow(SW_HIDE);
	}
	else {
		m_goShort.ShowWindow(SW_SHOW);
		m_goLong.ShowWindow(SW_SHOW);
		m_goGame.ShowWindow(SW_SHOW);
		m_goStatic.ShowWindow(SW_SHOW);
		m_tab.ShowWindow(SW_SHOW);
		m_explain.ShowWindow(SW_SHOW);
		m_imgcanvas.ShowWindow(SW_SHOW);
		//��Ʈ�� �̹��� �ֱ�
		CBitmap bitmap;
		bitmap.LoadBitmapW(IDB_BITMAP1);
		BITMAP bmpinfo;
		bitmap.GetBitmap(&bmpinfo);

		CDC memDC;
		memDC.CreateCompatibleDC(m_imgcanvas.GetDC());
		memDC.SelectObject(&bitmap);

		CStatic *staticSize = (CStatic*)GetDlgItem(IDC_IMAGE);
		CRect rect;
		staticSize->GetClientRect(rect);
		int iWidth = rect.Width();
		int iHeight = rect.Height();
		m_imgcanvas.GetDC()->StretchBlt(0, 0, iWidth, iHeight, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
		
		//m_user.ShowWindow(SW_SHOW);
		//m_pLogin = new CLogin();
		//str_userid = m_pLogin->str_id;
		//SetDlgItemText(IDC_USER, str_userid);
		

	}
	
	switch (mode) {
	case IDD_TYPINGTRAINING_FORM:
		break;
	case IDD_LOGIN:
		if(m_pLogin == NULL) {
			m_pLogin = new CLogin(this);
			m_pLogin->Create(IDD_LOGIN, this);
			m_pLogin->ShowWindow(SW_SHOW);
		}
		break;
	case IDD_SHORT:
		if (m_pShort == NULL) {
			m_pShort = new CShort(this);
			m_pShort->Create(IDD_SHORT, this);
			m_pShort->ShowWindow(SW_SHOW);
		}
		break;
	case IDD_LONG:
		if (m_pLong == NULL) {
			m_pLong = new CLong(this);
			m_pLong->Create(IDD_LONG, this);
			m_pLong->ShowWindow(SW_SHOW);
		}
		break;
	case IDD_GAME:
		if (m_pGame == NULL) {
			m_pGame = new CGame(this);
			m_pGame->Create(IDD_GAME, this);
			m_pGame->ShowWindow(SW_SHOW);
		}
		break;
	case IDD_STATIC:
		if (m_pInfo == NULL) {
			m_pInfo = new CInfo(this);
			m_pInfo->Create(IDD_STATIC, this);
			m_pInfo->ShowWindow(SW_SHOW);
		}
		break;
	}
}


void CTypingTrainingView::OnBnClickedGoShort()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	mode = IDD_SHORT;
	Invalidate();
}


void CTypingTrainingView::OnBnClickedGoLong()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	mode = IDD_LONG;
	Invalidate();
}


void CTypingTrainingView::OnBnClickedGoGame()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	mode = IDD_GAME;
	Invalidate();
}


void CTypingTrainingView::OnBnClickedGoStatic()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	mode = IDD_STATIC;
	Invalidate();
}


void CTypingTrainingView::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nIndex = m_tab.GetCurSel();
	CString str;
	if (nIndex == 0) {
		str.Format(_T("ª�� �ڵ� ����\r\n�ڵ� ������ �Է��ϴ� �����⿡ ����\r\n ���� Ÿ���� �ְ� Ÿ���� �ǽð����� ��Ÿ���ϴ�."));
		m_explain.SetWindowText(str);
	}
	else if (nIndex == 1) {
		str.Format(_T("�� �ڵ� ����\r\n�ڵ� ������ �Է��ϴ� �����⿡ ����\r\n ���� Ÿ���� �ְ� Ÿ���� �ǽð����� ��Ÿ���ϴ�."));
		m_explain.SetWindowText(str);
	}
	else if (nIndex == 2) {
		str.Format(_T("����\r\n�־��� ������ ���߸� ���� ������\r\n���� ��Ÿ���ϴ�."));
		m_explain.SetWindowText(str);
	}
	else if(nIndex == 3){
		str.Format(_T("���\r\n���Ÿ���� ��Ÿ���ϴ�."));
		m_explain.SetWindowText(str);
	}
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}
