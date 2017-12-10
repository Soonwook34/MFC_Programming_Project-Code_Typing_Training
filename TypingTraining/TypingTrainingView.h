
// TypingTrainingView.h : CTypingTrainingView 클래스의 인터페이스
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
class CTypingTrainingDoc;
class CLogin;
class CShort;
class CLong;
class CGame;
class CInfo;

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
	int mode;
	CLogin* m_pLogin;
	CShort* m_pShort;
	CLong* m_pLong;
	CGame* m_pGame;
	CInfo* m_pInfo;
	
	CString str_userid;
	int m_game_sum, m_game_rsum;
	CArray <int, int> m_typenum;
	int m_letter_sum;
	int m_letter_rsum;

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
	virtual void OnDraw(CDC* /*pDC*/);
public:
	CButton m_goShort;
	CButton m_goLong;
	CButton m_goGame;
	CButton m_goStatic;
	afx_msg void OnBnClickedGoShort();
	afx_msg void OnBnClickedGoLong();
	afx_msg void OnBnClickedGoGame();
	afx_msg void OnBnClickedGoStatic();
	CTabCtrl m_tab;
	CEdit m_explain;
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_user;
	CStatic m_imgcanvas;
};

#ifndef _DEBUG  // TypingTrainingView.cpp의 디버그 버전
inline CTypingTrainingDoc* CTypingTrainingView::GetDocument() const
   { return reinterpret_cast<CTypingTrainingDoc*>(m_pDocument); }
#endif

