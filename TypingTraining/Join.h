#pragma once
#include "afxwin.h"


// CJoin ��ȭ �����Դϴ�.

class CJoin : public CDialog
{
	DECLARE_DYNAMIC(CJoin)

public:
	CJoin(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CJoin();
	BOOL isexist_click = FALSE;
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JOIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
