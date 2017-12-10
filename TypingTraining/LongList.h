#pragma once
#include "afxwin.h"


// CLongList ��ȭ �����Դϴ�.
class CLong;

class CLongList : public CDialog
{
	DECLARE_DYNAMIC(CLongList)

public:
	CLongList(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLongList();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LONGLIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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