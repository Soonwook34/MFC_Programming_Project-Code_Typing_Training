#pragma once
#include "afxwin.h"


// CInfo ��ȭ �����Դϴ�.
class CTypingTrainingView;


class CInfo : public CDialog
{
	DECLARE_DYNAMIC(CInfo)

public:
	CInfo(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CInfo();
	CString userid, userpw;
	int game_sum=0, game_rsum=0;
	CArray <int, int> typenum;
	int letter_sum=0;
	int letter_rsum=0;

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STATIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
};
