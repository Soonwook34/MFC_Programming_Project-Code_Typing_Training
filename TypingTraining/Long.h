#pragma once
#include "afxwin.h"


// CLong ��ȭ �����Դϴ�.
class CTypingTrainingView;

class CLong : public CDialog
{
	DECLARE_DYNAMIC(CLong)

public:
	CLong(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLong();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LONG };
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
