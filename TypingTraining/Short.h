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
	CEdit m_copy1;
	CStatic m_str2;
	CStatic m_str3;
	CStatic m_str4;
	CStatic m_str5;
	CString str1;
	int same = 2;		//m_str1 m_copy1 문자열 비교 (2:black, 1:blue, 0:red)
	int str_num = 0;	//문자열 몇 줄 입력했는가
	int str_allnum = 15;		//문자열 총 몇 줄 입력 받을 것인가
	int ch_num = 0;				//한 줄의 m_str(static) 문자 개수
	int ch_num2 = 0;			//한 줄의 m_copy(edit) 문자 개수
	int ch_allnum = 0;			//전체의 static 문자 개수
	int ch_allnum2 = 0;			//전체의 edit 문자 개수
	bool bspace = FALSE;		//backspace 입력 여부
	bool first;
	int times = 0;				//시간 측정
	int alltime = 0;
	int best = 0;				//최고 타수
	int besttemp;				//현재 타수
	int avgtyping = 0;
	int* col;
	clock_t startTime, endTime;
	clock_t totalTime;
	virtual BOOL OnInitDialog();
	CStatic m_progress;
	CStatic m_present;
	CStatic m_best;
	CStatic m_accuracy;
	afx_msg void OnEnMaxtextCopy1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeCopy1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
};
