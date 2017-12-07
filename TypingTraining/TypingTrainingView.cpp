
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTypingTrainingView

IMPLEMENT_DYNCREATE(CTypingTrainingView, CFormView)

BEGIN_MESSAGE_MAP(CTypingTrainingView, CFormView)
END_MESSAGE_MAP()

// CTypingTrainingView ����/�Ҹ�

CTypingTrainingView::CTypingTrainingView()
	: CFormView(IDD_TYPINGTRAINING_FORM)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CTypingTrainingView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

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
