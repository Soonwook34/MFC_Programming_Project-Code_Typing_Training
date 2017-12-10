#pragma once
#include "afxwin.h"


// CLongList 대화 상자입니다.
class CLong;

class CLongList : public CDialog
{
	DECLARE_DYNAMIC(CLongList)

public:
	CLongList(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLongList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LONGLIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CLong *m_pLong;
	CStdioFile listFile;
	CListBox m_list;
	CButton m_start;
	CButton m_add;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedAdd();
	virtual void OnCancel();
};