
// TypingTrainingView.h : CTypingTrainingView Ŭ������ �������̽�
//

#pragma once


class CTypingTrainingView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CTypingTrainingView();
	DECLARE_DYNCREATE(CTypingTrainingView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_TYPINGTRAINING_FORM };
#endif

// Ư���Դϴ�.
public:
	CTypingTrainingDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CTypingTrainingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // TypingTrainingView.cpp�� ����� ����
inline CTypingTrainingDoc* CTypingTrainingView::GetDocument() const
   { return reinterpret_cast<CTypingTrainingDoc*>(m_pDocument); }
#endif

