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
	CStatic m_accuracy;
	CStatic m_speed;
	CStatic m_page;
	CStatic m_time;
	CStatic m_fileName;
	CEdit m_edit1;
	CEdit m_edit2;
	CEdit m_edit3;
	CEdit m_edit4;
	CEdit m_edit5;
	CString fileName;
	CArray<CString, CString> fileStr;
	int speedCnt, correctChar, totalChar, speedSum, bestSpeed;
	int tempTotal, tempCorrect;
	int typeIndex;
	BOOL start;
	CArray<int, int> speed;
	CString check[5];
	COLORREF red, blue, black;
	int IsTyping;
	int curPage, totalPage;
	int time;
	afx_msg void OnBnClickedGoBack();
	virtual void PostNcDestroy();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	void InitLongCode();
	void OnTyping(CString type, int index, int strNum);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void ShowFinalResult();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_bestSpeed;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
