#pragma once
#include "afxwin.h"


// CLogin 대화 상자입니다.
class CTypingTrainingView;

class CLogin : public CDialog
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLogin();
	CString str_id, str_pw;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTypingTrainingView* m_pMain;
	CButton m_goMain;
	afx_msg void OnBnClickedGoMain();
	virtual void PostNcDestroy();
	CEdit m_edit_id;
	CEdit m_edit_pw;
	CButton m_join;
	afx_msg void OnBnClickedJoin();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CStatic m_name;
	CStatic m_id;
	CStatic m_pw;
	virtual BOOL OnInitDialog();
};
