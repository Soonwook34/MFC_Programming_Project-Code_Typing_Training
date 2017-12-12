
// TypingTrainingView.h : CTypingTrainingView Ŭ������ �������̽�
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
protected: // serialization������ ��������ϴ�.
	CTypingTrainingView();
	DECLARE_DYNCREATE(CTypingTrainingView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_TYPINGTRAINING_FORM };
#endif

// Ư���Դϴ�.
public:
	CTypingTrainingDoc* GetDocument() const;
	int mode;
	CLogin* m_pLogin;
	CShort* m_pShort;
	CLong* m_pLong;
	CGame* m_pGame;
	CInfo* m_pInfo;
	
	CString str_userid, str_userpw;
	int m_game_sum, m_game_rsum;
	CArray <int, int> m_typenum;
	int m_letter_sum ;
	int m_letter_rsum ;
	
	int m_static_count;
	int m_game_count;
	int m_practice_count;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CTypingTrainingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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
	CStatic m_main;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // TypingTrainingView.cpp�� ����� ����
inline CTypingTrainingDoc* CTypingTrainingView::GetDocument() const
   { return reinterpret_cast<CTypingTrainingDoc*>(m_pDocument); }
#endif

