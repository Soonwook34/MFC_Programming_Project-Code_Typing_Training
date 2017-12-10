// Info.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TypingTraining.h"
#include "Info.h"
#include "afxdialogex.h"
#include "TypingTrainingDoc.h"
#include "TypingTrainingView.h"



// CInfo ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CInfo, CDialog)

CInfo::CInfo(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_STATIC, pParent)
{
	m_pMain = (CTypingTrainingView*)pParent;
}

CInfo::~CInfo()
{
}

void CInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GO_BACK, m_goBack);
	DDX_Control(pDX, IDC_USERID, m_edit_userid);
	DDX_Control(pDX, IDC_AVERAGE, m_edit_average);
	DDX_Control(pDX, IDC_ACCURACY, m_edit_accuracy);
	DDX_Control(pDX, IDC_EXACT, m_edit_exact);
	DDX_Control(pDX, IDC_DROPOUT, m_dropout);
}


BEGIN_MESSAGE_MAP(CInfo, CDialog)
	ON_BN_CLICKED(IDC_GO_BACK, &CInfo::OnBnClickedGoBack)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_DROPOUT, &CInfo::OnBnClickedDropout)
END_MESSAGE_MAP()


// CInfo �޽��� ó�����Դϴ�.


void CInfo::OnBnClickedGoBack()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	DestroyWindow();
}


void CInfo::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pMain->ShowWindow(SW_SHOW);
	m_pMain->mode = IDD_TYPINGTRAINING_FORM;
	m_pMain->m_pInfo = NULL;
	delete this;
	CDialog::PostNcDestroy();
}


BOOL CInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	m_edit_userid.SetWindowText(userid);
	
	int typenum_sum = 0;
	int i;
	int count = typenum.GetCount();
	if (count <= 10) {
		for (i = 0; i < count; i++)
			typenum_sum += typenum.GetAt(i);
	}
	else{
		for (i = count - 10; i < count; i++) 
			typenum_sum += typenum.GetAt(i);
	}
	int average = 0;
	if (count <= 10)
		average = typenum_sum / count;
	else
		average = typenum_sum / 10;
	CString str_average;
	str_average.Format(_T("%dŸ"), average);
	m_edit_average.SetWindowText(str_average);
	
	int accuracy = (letter_rsum*100 )/ letter_sum;
	CString str_accuracy;
	str_accuracy.Format(_T("%d�ۼ�Ʈ"), accuracy);
	m_edit_accuracy.SetWindowTextW(str_accuracy);
	/*
	double exact = (game_rsum / game_sum) * 100;
	CString str_exact;
	str_exact.Format(_T("%.2lf%"), exact);
	m_edit_exact.SetWindowTextW(str_exact);
	*/

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CInfo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   
	//�׷��� �׸� ���� �� ����
	CRect rect;
	GetClientRect(rect);
	CRect m_rect(rect.left + 20, (rect.top + 1)*((rect.bottom - rect.top) / 2) - 50, rect.right - 20, rect.bottom - 20);
	dc.FillSolidRect(m_rect, RGB(255, 255, 255));
	CRect m_graph_rect(m_rect.left + 50, m_rect.top, m_rect.right, m_rect.bottom - 40);
	dc.FillSolidRect(m_graph_rect, RGB(250, 244, 192));

	
	//��Ʈ����,���� �׸��� ����� ����
	CFont font;
	font.CreatePointFont(100, _T("Consolas"));
	dc.SelectObject(&font);
	dc.SetTextColor(RGB(0, 0, 0));
	dc.SetBkColor(RGB(255, 255, 255));
	CPen line_pen(PS_SOLID, 2, RGB(0, 0, 0));

	int m_v_count = 6;
	int m_value_count = 10;
	int count = typenum.GetCount();
	if (count <= 10)
		m_value_count = count;
	else
		m_value_count = 10;
	//y�� �����̶� ���ݼ��� ǥ��
	int v_step = m_graph_rect.Height() / (m_v_count + 1); //y��ǥ ���ݴ� ��ǥ ����
	int y_pos = 0;
	int v_scale_value = 600 / (m_v_count - 1); //y��ǥ ���ݴ� ��ġ��
	int i;
	for (i = 0; i < 6; i++) {
		dc.SelectObject(&line_pen);
		y_pos = m_graph_rect.top + v_step*(i + 1);
		//y�� ���� �׸���
		dc.MoveTo(m_graph_rect.left - 1, y_pos);
		dc.LineTo(m_graph_rect.left - 6, y_pos);
		CString str;
		str.Format(_T("%d"), 600 - v_scale_value*i);
		CRect r;
		r.SetRect(m_graph_rect.left - 45, int(y_pos - 8), m_graph_rect.left - 8, int(y_pos + 10));
		dc.DrawText(str, r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	//y��ǥ ���۰� ��
	int y_start = m_graph_rect.top + v_step;
	int y_end = m_graph_rect.top + v_step * m_v_count;

	int h_step = m_graph_rect.Width() / (m_value_count + 1); // x��ǥ ���ݴ� ��ǥ ����
	int x_pos = 0;
	for (i = 0; i < m_value_count; i++) {
		dc.SelectObject(&line_pen);
		x_pos = m_graph_rect.left + h_step*(i + 1);
		//x�� ���� �׸���
		dc.MoveTo(x_pos, m_graph_rect.bottom + 1);
		dc.LineTo(x_pos, m_graph_rect.bottom + 6);
		CString str;
		str.Format(_T("%d"), i + 1);
		CRect r;
		r.SetRect(int(x_pos - 40), m_graph_rect.bottom + 8, int(x_pos + 40), m_graph_rect.bottom + 26);
		dc.DrawText(str, r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

	//������ �׷��� �׸���
	dc.SelectObject(&line_pen);
	for (i = 0; i < m_value_count; i++) {
		// x��ǥ�� ����
		x_pos = m_graph_rect.left + h_step*(i + 1);
		y_pos = y_start + (y_end - y_start)*(600 - typenum.GetAt(i)) / 600;


		// ù��° �������� ��� MoveTo�� �ϰ�
		if (i == 0) 
			dc.MoveTo(int(x_pos), int(y_pos));
		// ������ �����ʹ� LineTo�� �׸���.
		else 
			dc.LineTo(int(x_pos), int(y_pos));
	}
	/*
	//������ �� �׸��� �ڵ�
	CBrush brush(RGB(0, 0, 255));
	for (i = 0; i<10; i++) {
		x_pos = m_graph_rect.left + h_step*(i + 1);
		y_pos = y_start + (y_end - y_start)*(600 - typenum.GetAt(i)) / 600;
		dc.Ellipse(CRect(int(x_pos - 3), int(y_pos - 3), int(x_pos + 3), int(y_pos + 3)));
	}
	*/
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
}


void CInfo::OnBnClickedDropout()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	LONGLONG pos;
	CStdioFile infofile;
	CString userid_forfile = userid;
	if (infofile.Open(_T("typinguserinfo.txt"), CFile::modeReadWrite | CFile::typeText)) {
		CString str, written_str;
		while (infofile.ReadString(str)) {
			written_str += str;
			written_str.Replace(_T("\r\n"), _T(" "));
			int n = written_str.Find(userid_forfile);
			if (n < 0) {
				written_str.Empty();
				pos = infofile.GetPosition();
			}
			else {
				infofile.Seek(pos, CFile::begin);
				int len = written_str.GetLength();
				CString fix_str;
				int i;
				for (i = 0; i < len; i++)
					fix_str += _T(" ");
				infofile.WriteString(fix_str);
				MessageBox(_T("Ż��Ϸ�"));
				SetDlgItemText(IDC_USERID, _T(""));
				SetDlgItemText(IDC_AVERAGE, _T(""));
				SetDlgItemText(IDC_ACCURACY, _T(""));
				SetDlgItemText(IDC_EXACT, _T(""));
				infofile.Close();
				break;
			}
		}
	}
}
