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
	int speedCnt, correctChar, totalChar;
	CArray<int, int> speed;
	CString check[5];
	COLORREF red, blue, black;
	int curPage, totalPage;
	int time;
	afx_msg void OnBnClickedGoBack();
	virtual void PostNcDestroy();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	void InitLongCode();
	void OnTyping(CString type, int index, int strNum);
};
