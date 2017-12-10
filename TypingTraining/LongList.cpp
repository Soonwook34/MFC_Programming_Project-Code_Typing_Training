// LongList.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TypingTraining.h"
#include "LongList.h"
#include "afxdialogex.h"
#include "Long.h"


// CLongList ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CLongList, CDialog)

CLongList::CLongList(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LONGLIST, pParent)
{
	m_pLong = (CLong *)pParent;
}

CLongList::~CLongList()
{
}

void CLongList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDSTART, m_start);
	DDX_Control(pDX, IDADD, m_add);
}


BEGIN_MESSAGE_MAP(CLongList, CDialog)
	ON_BN_CLICKED(IDSTART, &CLongList::OnBnClickedStart)
	ON_BN_CLICKED(IDADD, &CLongList::OnBnClickedAdd)
END_MESSAGE_MAP()


// CLongList �޽��� ó�����Դϴ�.


BOOL CLongList::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CFileFind longCodeFinder;

	CString directory = _T(".\\LongCode\\");
	CString strFile = _T("*.*");
	BOOL IsExist = longCodeFinder.FindFile(directory + strFile);

	if (!IsExist) {
		IsExist = CreateDirectory(directory, NULL);
	}
	else {
		IsExist = longCodeFinder.FindFile(directory + strFile);
		while (IsExist) {
			IsExist = longCodeFinder.FindNextFile();
			if (!longCodeFinder.IsDirectory()) {
				m_list.AddString(longCodeFinder.GetFileName());
			}
		}
		if (m_list.GetCount() > 0) {
			m_list.SetCurSel(0);
		}
	}
	longCodeFinder.Close();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CLongList::OnBnClickedStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_list.GetCount() > 0) {
		int index = m_list.GetCurSel();
		CString fileName;
		m_list.GetText(index, fileName);
		m_pLong->fileName = fileName;
		EndDialog(IDSTART);
	}
	else {
		AfxMessageBox(_T("������ �߰��ϰų� ������ �ּ���!"));
	}
}


void CLongList::OnBnClickedAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	TCHAR BASED_CODE szFilter[] = _T("C ����(*.c, *.cpp) |*.c;*.cpp|JAVA ����(*.java) |*.java||");
	CFileDialog dlg(TRUE, _T("*.c"), _T("cCode"), OFN_HIDEREADONLY, szFilter);

	if (dlg.DoModal() == IDOK) {
		CString filePath = dlg.GetPathName(), fileName = dlg.GetFileName();
		CFileFind longCodeFinder;
		FILE *fOpenStream, *fSaveStream;
		errno_t e;

		e = _tfopen_s(&fOpenStream, filePath, _T("rt,ccs=UTF-8"));
		if (e != 0) {
			AfxMessageBox(_T("���� ���� ����!"));
			return;
		}
		CStdioFile openFile(fOpenStream);

		e = _tfopen_s(&fSaveStream, _T(".\\LongCode\\" + fileName), _T("wt,ccs=UTF-8"));
		if (e != 0) {
			AfxMessageBox(_T("���� �߰� ����!"));
			return;
		}
		CStdioFile saveFile(fSaveStream);

		CString str;
		while (openFile.ReadString(str)) {
			str.Remove('\t');
			if (!(str == _T(""))) {
				saveFile.WriteString(str + _T("\n"));
			}
		}
		openFile.Close();
		saveFile.Close();

		BOOL add = true;
		int index = 0;
		CString compareStr;
		while (add && m_list.GetCount() > index) {
			m_list.GetText(index, compareStr);
			if (compareStr == fileName) {
				add = false;
			}
			index++;
		}
		if (add) {
			m_list.AddString(fileName);
		}
	}
}
