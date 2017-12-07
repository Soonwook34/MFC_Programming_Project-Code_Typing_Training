#pragma once
#include "afxwin.h"


// CShort 대화 상자입니다.
class CTypingTrainingView;

class CShort : public CDialog
{
	DECLARE_DYNAMIC(CShort)

public:
	CShort(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CShort();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTypingTrainingView* m_pMain;
	CButton m_goBack;
	afx_msg void OnBnClickedGoBack();
	virtual void PostNcDestroy();
};
