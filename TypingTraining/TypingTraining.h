
// TypingTraining.h : TypingTraining ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CTypingTrainingApp:
// �� Ŭ������ ������ ���ؼ��� TypingTraining.cpp�� �����Ͻʽÿ�.
//

class CTypingTrainingApp : public CWinApp
{
public:
	CTypingTrainingApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTypingTrainingApp theApp;
