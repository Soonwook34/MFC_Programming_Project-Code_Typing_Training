#pragma once
#include "afxwin.h"


// CLogin ��ȭ �����Դϴ�.
class CTypingTrainingView;

class CLogin : public CDialog
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLogin();
	CString str_id, str_pw;
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
