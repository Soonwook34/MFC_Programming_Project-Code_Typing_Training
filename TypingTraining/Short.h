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
	CEdit m_copy1;
	CStatic m_str2;
	CStatic m_str3;
	CStatic m_str4;
	CStatic m_str5;
	CString str1;
	int same = 2;		//m_str1 m_copy1 ���ڿ� �� (2:black, 1:blue, 0:red)
	int str_num = 0;	//���ڿ� �� �� �Է��ߴ°�
	int str_allnum = 15;		//���ڿ� �� �� �� �Է� ���� ���ΰ�
	int ch_num = 0;				//�� ���� m_str(static) ���� ����
	int ch_num2 = 0;			//�� ���� m_copy(edit) ���� ����
	int ch_allnum = 0;			//��ü�� static ���� ����
	int ch_allnum2 = 0;			//��ü�� edit ���� ����
	bool bspace = FALSE;		//backspace �Է� ����
	bool first;
	int times = 0;				//�ð� ����
	int alltime = 0;
	int best = 0;				//�ְ� Ÿ��
	int besttemp;				//���� Ÿ��
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
