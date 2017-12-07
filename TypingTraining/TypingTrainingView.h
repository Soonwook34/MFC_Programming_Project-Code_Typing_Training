
// TypingTrainingView.h : CTypingTrainingView 클래스의 인터페이스
//

#pragma once


class CTypingTrainingView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CTypingTrainingView();
	DECLARE_DYNCREATE(CTypingTrainingView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_TYPINGTRAINING_FORM };
#endif

// 특성입니다.
public:
	CTypingTrainingDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CTypingTrainingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // TypingTrainingView.cpp의 디버그 버전
inline CTypingTrainingDoc* CTypingTrainingView::GetDocument() const
   { return reinterpret_cast<CTypingTrainingDoc*>(m_pDocument); }
#endif

