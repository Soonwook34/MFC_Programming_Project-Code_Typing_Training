#pragma once
#include "afxwin.h"


// CJoin 대화 상자입니다.

class CJoin : public CDialog
{
	DECLARE_DYNAMIC(CJoin)

public:
	CJoin(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CJoin();
	BOOL isexist_click = FALSE;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JOIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_newid;
	CEdit m_edit_newpw;
	CEdit m_edit_cfpw;
	CString str_newid;
	CString str_newpw;
	CString str_cfpw;
	virtual void OnOK();
	CButton m_isexist;
	afx_msg void OnBnClickedIsexist();
	afx_msg void OnEnUpdateNewid();
	afx_msg void OnEnUpdateNewpw();
};
