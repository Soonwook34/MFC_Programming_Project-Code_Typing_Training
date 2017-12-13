#pragma once
#include "afxwin.h"
#include "Info.h"


// CGame ��ȭ �����Դϴ�.
class CTypingTrainingView;

class CGame : public CDialog
{
	DECLARE_DYNAMIC(CGame)

public:
	CGame(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGame();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CTypingTrainingView* m_pMain;
	CButton m_goBack;
	afx_msg void OnBnClickedGoBack();
	virtual void PostNcDestroy();
	CStatic m_prob;
	CStatic m_rate;
	CStatic m_num;
	CString str;
	CStringArray ansArr;
	CStringArray probArr;
	CStringArray numberArr;
	CStringArray rateArr;
	CBrush m_brush;
	CStringArray answer;
	CStringArray problem;
//	CString m_str;
	int count;
	int rate;
	int n;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedEnter();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_str;
	CButton m_enter;
	CInfo info;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
