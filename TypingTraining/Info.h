#pragma once
#include "afxwin.h"


// CInfo 대화 상자입니다.
class CTypingTrainingView;


class CInfo : public CDialog
{
	DECLARE_DYNAMIC(CInfo)

public:
	CInfo(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInfo();
	CString userid, userpw;
	int game_sum, game_rsum;
	CArray <int, int> typenum;
	int letter_sum;
	int letter_rsum;
	
	int static_count;
	int practice_count;
	int game_count;
	
	int count;
	int average;
	int ls, lrs, gs, grs;
	int f_average;
	int f_accuracy;
	int f_exact;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STATIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTypingTrainingView* m_pMain;
	CButton m_goBack;
	afx_msg void OnBnClickedGoBack();
	virtual void PostNcDestroy();
	CEdit m_edit_userid;
	CEdit m_edit_average;
	CEdit m_edit_accuracy;
	CEdit m_edit_exact;
	CButton m_dropout;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedDropout();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
