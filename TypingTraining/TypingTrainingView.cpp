
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTypingTrainingView

IMPLEMENT_DYNCREATE(CTypingTrainingView, CFormView)

BEGIN_MESSAGE_MAP(CTypingTrainingView, CFormView)
END_MESSAGE_MAP()

// CTypingTrainingView 생성/소멸

CTypingTrainingView::CTypingTrainingView()
	: CFormView(IDD_TYPINGTRAINING_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CTypingTrainingView::~CTypingTrainingView()
{
}

void CTypingTrainingView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
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
