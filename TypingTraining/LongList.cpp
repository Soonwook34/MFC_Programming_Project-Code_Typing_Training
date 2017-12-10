// LongList.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TypingTraining.h"
#include "LongList.h"
#include "afxdialogex.h"
#include "Long.h"


// CLongList 대화 상자입니다.

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


// CLongList 메시지 처리기입니다.


BOOL CLongList::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
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
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CLongList::OnBnClickedStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_list.GetCount() > 0) {
		int index = m_list.GetCurSel();
		CString fileName;
		m_list.GetText(index, fileName);
		m_pLong->fileName = fileName;
		EndDialog(IDSTART);
	}
	else {
		AfxMessageBox(_T("파일을 추가하거나 선택해 주세요!"));
	}
}


void CLongList::OnBnClickedAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TCHAR BASED_CODE szFilter[] = _T("C 파일(*.c, *.cpp) |*.c;*.cpp|JAVA 파일(*.java) |*.java||");
	CFileDialog dlg(TRUE, _T("*.c"), _T("cCode"), OFN_HIDEREADONLY, szFilter);

	if (dlg.DoModal() == IDOK) {
		CString filePath = dlg.GetPathName(), fileName = dlg.GetFileName();
		CFileFind longCodeFinder;
		FILE *fOpenStream, *fSaveStream;
		errno_t e;

		e = _tfopen_s(&fOpenStream, filePath, _T("rt,ccs=UTF-8"));
		if (e != 0) {
			AfxMessageBox(_T("파일 열기 오류!"));
			return;
		}
		CStdioFile openFile(fOpenStream);

		e = _tfopen_s(&fSaveStream, _T(".\\LongCode\\" + fileName), _T("wt,ccs=UTF-8"));
		if (e != 0) {
			AfxMessageBox(_T("파일 추가 오류!"));
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
