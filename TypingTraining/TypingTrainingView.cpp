
// TypingTrainingView.cpp : CTypingTrainingView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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

// CTypingTrainingView 생성/소멸

CTypingTrainingView::CTypingTrainingView()
	: CFormView(IDD_TYPINGTRAINING_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.
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
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

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
	m_explain.SetWindowTextW(_T("짧은 코드 연습\r\n코드 연습은 입력하는 빠르기에 따라\r\n현재 타수와 최고 타수가 실시간으로 나타납니다."));

	//m_pLogin = new CLogin();
	//str_userid = m_pLogin->str_id;
}


// CTypingTrainingView 진단

#ifdef _DEBUG
void CTypingTrainingView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTypingTrainingView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTypingTrainingDoc* CTypingTrainingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTypingTrainingDoc)));
	return (CTypingTrainingDoc*)m_pDocument;
}
#endif //_DEBUG


// CTypingTrainingView 메시지 처리기


void CTypingTrainingView::OnDraw(CDC* pDC)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
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
		//비트맵 이미지 넣기
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mode = IDD_SHORT;
	Invalidate();
}


void CTypingTrainingView::OnBnClickedGoLong()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mode = IDD_LONG;
	Invalidate();
}


void CTypingTrainingView::OnBnClickedGoGame()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mode = IDD_GAME;
	Invalidate();
}


void CTypingTrainingView::OnBnClickedGoStatic()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mode = IDD_STATIC;
	Invalidate();
}


void CTypingTrainingView::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nIndex = m_tab.GetCurSel();
	CString str;
	if (nIndex == 0) {
		str.Format(_T("짧은 코드 연습\r\n코드 연습은 입력하는 빠르기에 따라\r\n 현재 타수와 최고 타수가 실시간으로 나타납니다."));
		m_explain.SetWindowText(str);
	}
	else if (nIndex == 1) {
		str.Format(_T("긴 코드 연습\r\n코드 연습은 입력하는 빠르기에 따라\r\n 현재 타수와 최고 타수가 실시간으로 나타납니다."));
		m_explain.SetWindowText(str);
	}
	else if (nIndex == 2) {
		str.Format(_T("게임\r\n주어진 문제를 맞추면 맞은 개수가\r\n왼편에 나타납니다."));
		m_explain.SetWindowText(str);
	}
	else if(nIndex == 3){
		str.Format(_T("통계\r\n평균타수가 나타납니다."));
		m_explain.SetWindowText(str);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
