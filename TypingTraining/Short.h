#pragma once
#include "afxwin.h"


// CShort ��ȭ �����Դϴ�.
class CTypingTrainingView;

class CShort : public CDialog
{
	DECLARE_DYNAMIC(CShort)

public:
	CShort(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CShort();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CTypingTrainingView* m_pMain;
	CButton m_goBack;
	afx_msg void OnBnClickedGoBack();
	virtual void PostNcDestroy();
};
