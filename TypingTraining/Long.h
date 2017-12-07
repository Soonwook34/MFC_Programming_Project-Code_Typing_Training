#pragma once
#include "afxwin.h"


// CLong 대화 상자입니다.
class CTypingTrainingView;

class CLong : public CDialog
{
	DECLARE_DYNAMIC(CLong)

public:
	CLong(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLong();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LONG };
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
