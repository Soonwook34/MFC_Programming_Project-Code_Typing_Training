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
	average = 0;
	
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
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
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
	
	CStdioFile infofile;
	CString written_str, str;
	CString forid, forpw, fora, forls, forlrs, forgs, forgrs;
	if (infofile.Open(_T("typinguserinfo.txt"), CFile::modeRead | CFile::typeText))
	{
		while (infofile.ReadString(str)) {
			written_str += str;
			int len = userid.GetLength();
			//written_str.Replace(_T("\r\n"), _T(" "))
			CString find_id;
			find_id = written_str.Left(len + 1);
			int n = find_id.Find(userid);
			if (n < 0)
				written_str.Empty();
			else {
				//int ls, lrs, gs, grs;
				//CString forid, forpw, fora, forls, forlrs, forgs, forgrs;
				AfxExtractSubString(forid, str, 0, '.');
				AfxExtractSubString(forpw, str, 1, '.');
				AfxExtractSubString(fora, str, 2, '.');
				AfxExtractSubString(forls, str, 3, '.');
				AfxExtractSubString(forlrs, str, 4, '.');
				AfxExtractSubString(forgs, str, 5, '.');
				AfxExtractSubString(forgrs, str, 6, '.');
				ls = _wtoi(forls);
				lrs = _wtoi(forlrs);
				if (ls != 0) {
					f_accuracy = (lrs * 100) / ls;
				}
				else {
					f_accuracy = 0;
				}
				//f_accuracy = (lrs * 100) / ls;
				//CString a;
				//a.Format(_T("%d"), ls);
				//MessageBox(a);
				gs = _wtoi(forgs);
				grs = _wtoi(forgrs);
				if (gs != 0) {
					f_exact = (grs * 100) / gs;
				}
				else {
					f_exact = 0;
				}
				//ils = ls;
				//ilrs = lrs;
				//igs = gs;
				//igrs = grs;
				//CString a;
				//a.Format(_T("%d"), ls);
				//MessageBox(a);
				infofile.Close();
				break;
			}
		}
	}
	//f_accuracy=(lrs * 100) / ls;
	//f_exact = (grs * 100) / gs;
	count = typenum.GetCount();
	
	if (static_count==0) {
		CString str_average;
		str_average += fora;
		str_average += _T("Ÿ");
		CString str_accuracy, str_exact;
		str_accuracy.Format(_T("%d�ۼ�Ʈ"), f_accuracy);
		str_exact.Format(_T("%d�ۼ�Ʈ"), f_exact);
		m_edit_average.SetWindowText(str_average);
		m_edit_accuracy.SetWindowText(str_accuracy);
		m_edit_exact.SetWindowText(str_exact);
		average = f_average;
		

	}
	
	else {
		if (game_count==0 && practice_count>0) {
			int typenum_sum = 0;
			int i;
			//count = typenum.GetCount();
			if (count <= 10) {
				for (i = 0; i < count; i++)
					typenum_sum += typenum.GetAt(i);
			}
			else {
				for (i = count - 10; i < count; i++)
					typenum_sum += typenum.GetAt(i);
			}

			if (count <= 10)
				average = typenum_sum / count;
			else
				average = typenum_sum / 10;
			CString str_average;
			str_average.Format(_T("%dŸ"), average);
			m_edit_average.SetWindowText(str_average);

			int accuracy = (letter_rsum * 100) / letter_sum;
			CString str_accuracy;
			str_accuracy.Format(_T("%d�ۼ�Ʈ"), accuracy);
			m_edit_accuracy.SetWindowText(str_accuracy);

			CString str_exact;
			str_exact.Format(_T("%d�ۼ�Ʈ"), f_exact);
			m_edit_exact.SetWindowText(str_exact);
		
		}
		
		if (game_count>0 && practice_count==0) {
			int exact = (game_rsum * 100) / game_sum;
			CString str_exact;
			str_exact.Format(_T("%d�ۼ�Ʈ"), exact);
			m_edit_exact.SetWindowText(str_exact);
			
			CString str_average;
			str_average += fora;
			str_average += _T("Ÿ");
			CString str_accuracy;
			str_accuracy.Format(_T("%d�ۼ�Ʈ"), f_accuracy);
			m_edit_average.SetWindowText(str_average);
			m_edit_accuracy.SetWindowText(str_accuracy);
		}
		if(practice_count>0 && game_count>0) {
			int typenum_sum = 0;
			int i;
			count = typenum.GetCount();
			if (count <= 10) {
				for (i = 0; i < count; i++)
					typenum_sum += typenum.GetAt(i);
			}
			else {
				for (i = count - 10; i < count; i++)
					typenum_sum += typenum.GetAt(i);
			}

			if (count <= 10)
				average = typenum_sum / count;
			else
				average = typenum_sum / 10;
			CString str_average;
			str_average.Format(_T("%dŸ"), average);
			m_edit_average.SetWindowText(str_average);

			int accuracy = (letter_rsum * 100) / letter_sum;
			CString str_accuracy;
			str_accuracy.Format(_T("%d�ۼ�Ʈ"), accuracy);
			m_edit_accuracy.SetWindowText(str_accuracy);

			CString please;
			please.Format(_T("%d"), game_rsum);
			MessageBox(please);
			int exact = (game_rsum * 100) / game_sum;
			CString str_exact;
			str_exact.Format(_T("%d�ۼ�Ʈ"), exact);
			m_edit_exact.SetWindowText(str_exact);
		}
		
		LONGLONG pos;
		CStdioFile infofile;
		CString written_str, str;
		if (infofile.Open(_T("typinguserinfo.txt"), CFile::modeReadWrite | CFile::typeText))
		{
			while (infofile.ReadString(str)) {
				written_str += str;
				written_str.Replace(_T("\r\n"), _T(" "));
				//int n = written_str.Find(userid);
				int lenid = userid.GetLength();
				CString find_id;
				find_id = written_str.Left(lenid + 1);
				int n = find_id.Find(userid);
				if (n < 0) {
					written_str.Empty();
					pos = infofile.GetPosition();
				}
				else {
					infofile.Seek(pos, CFile::begin);
					//int len = written_str.GetLength();
					//infofile.WriteString(_T("0123456789"));
					CString str_average, str_lettersum, str_letter_rsum, str_gamesum, str_game_rsum;
					str_average.Format(_T("%d"), average);
					str_lettersum.Format(_T("%d"), letter_sum);
					str_letter_rsum.Format(_T("%d"), letter_rsum);
					str_gamesum.Format(_T("%d"), game_sum);
					str_game_rsum.Format(_T("%d"), game_rsum);
					//infofile.WriteString(_T("\n"));
					//infofile.WriteString(_T("\n"));
					CString tmp;
					for (int i = 0; i < written_str.GetLength(); i++)
						tmp += _T("");
					infofile.WriteString(tmp);
					infofile.WriteString(_T("\n"));
					infofile.WriteString(_T("*") + userid + _T(".") + userpw + _T(".") + str_average + _T(".") + str_lettersum + _T(".") + str_letter_rsum + _T(".") + str_gamesum + _T(".") + str_game_rsum);

					break;
					infofile.Close();
				}
			}
		}
		
	}
	
		/*
		int typenum_sum = 0;
		int i;
		int ncount = typenum.GetCount();
		if (ncount <= 10) {
			for (i = 0; i < ncount; i++)
				typenum_sum += typenum.GetAt(i);
		}
		else {
			for (i = ncount - 10; i < count; i++)
				typenum_sum += typenum.GetAt(i);
		}

		if (ncount <= 10)
			average = typenum_sum / ncount;
		else
			average = typenum_sum / 10;
		CString str_average;
		str_average.Format(_T("%dŸ"), average);
		m_edit_average.SetWindowText(str_average);

		int accuracy = (letter_rsum * 100) / letter_sum;
		CString str_accuracy;
		str_accuracy.Format(_T("%d�ۼ�Ʈ"), accuracy);
		m_edit_accuracy.SetWindowTextW(str_accuracy);

		int exact = (game_rsum * 100) / game_sum;
		CString str_exact;
		str_exact.Format(_T("%d�ۼ�Ʈ"), exact);
		m_edit_exact.SetWindowTextW(str_exact);

		LONGLONG pos;
		CStdioFile infofile;
		CString written_str, str;
		if (infofile.Open(_T("typinguserinfo.txt"), CFile::modeReadWrite | CFile::typeText))
		{
			while (infofile.ReadString(str)) {
				written_str += str;
				written_str.Replace(_T("\r\n"), _T(" "));
				//int n = written_str.Find(userid);
				int len = userid.GetLength();
				CString find_id;
				find_id = written_str.Left(len + 1);
				int n = find_id.Find(userid);
				if (n < 0) {
					written_str.Empty();
					pos = infofile.GetPosition();
				}
				else {
					infofile.Seek(pos, CFile::begin);
					//int len = written_str.GetLength();
					//infofile.WriteString(_T("0123456789"));
					CString str_average, str_lettersum, str_letter_rsum, str_gamesum, str_game_rsum;
					str_average.Format(_T("%d"), average);
					str_lettersum.Format(_T("%d"), letter_sum);
					str_letter_rsum.Format(_T("%d"), letter_rsum);
					str_gamesum.Format(_T("%d"), game_sum);
					str_game_rsum.Format(_T("%d"), game_rsum);
					infofile.WriteString(_T("*") + userid + _T(".") + userpw + _T(".") + str_average + _T(".") + str_lettersum + _T(".") + str_letter_rsum + _T(".") + str_gamesum + _T(".") + str_game_rsum);
				}
			}
		}
	}
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
	dc.FillSolidRect(m_rect, RGB(0, 0, 0));
	CRect m_graph_rect(m_rect.left + 50, m_rect.top, m_rect.right, m_rect.bottom - 40);
	dc.FillSolidRect(m_graph_rect, RGB(250, 244, 192));


	//��Ʈ����,���� �׸��� ����� ����
	CFont font;
	font.CreatePointFont(100, _T("Consolas"));
	dc.SelectObject(&font);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.SetBkColor(RGB(0, 0, 0));
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
	dc.SelectStockObject(BLACK_BRUSH);
	//������ �׷��� �׸���
	dc.SelectObject(&line_pen);
	for (i = 0; i < m_value_count; i++) {
		// x��ǥ�� ����
		x_pos = m_graph_rect.left + h_step*(i + 1);
		y_pos = y_start + (y_end - y_start)*(600 - typenum.GetAt(i)) / 600;

		dc.Ellipse(x_pos - 3, y_pos - 3, x_pos + 3, y_pos + 3);
		// ù��° �������� ��� MoveTo�� �ϰ�
		if (i == 0)
			dc.MoveTo(int(x_pos), int(y_pos));
		// ������ �����ʹ� LineTo�� �׸���.
		else
			dc.LineTo(int(x_pos), int(y_pos));
	}
	/*
	if (static_count == 0|game_count>0) {
		CRect rect;
		GetClientRect(rect);
		CRect m_rect(rect.left + 20, (rect.top + 1)*((rect.bottom - rect.top) / 2) - 50, rect.right - 20, rect.bottom - 20);
		dc.FillSolidRect(m_rect, RGB(255, 255, 255));
		CRect m_graph_rect(m_rect.left + 50, m_rect.top, m_rect.right, m_rect.bottom - 40);
		dc.FillSolidRect(m_graph_rect, RGB(250, 244, 192));

	}

	else if(practice_count>0) {
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


BOOL CInfo::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(255, 255, 255));
	return TRUE;
	return CDialog::OnEraseBkgnd(pDC);
}


HBRUSH CInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	switch (nCtlColor) {
	case CTLCOLOR_DLG:
		return (HBRUSH)GetStockObject(BLACK_BRUSH);
		break;
	case CTLCOLOR_BTN:
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);
		break;
	case CTLCOLOR_STATIC:
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);
		break;
	case CTLCOLOR_EDIT:
		pDC->SetTextColor(RGB(225, 225, 225));
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}
