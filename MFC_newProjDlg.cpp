
// MFC_newProjDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFC_newProj.h"
#include "MFC_newProjDlg.h"
#include "afxdialogex.h"
#include "stdlib.h"
#include "iostream"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_newProjDlg dialog



CMFC_newProjDlg::CMFC_newProjDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_NEWPROJ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_newProjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_barcode, brcode_in);
	DDX_Control(pDX, IDC_infoarea, info_edit);
}

BEGIN_MESSAGE_MAP(CMFC_newProjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMFC_newProjDlg message handlers

BOOL CMFC_newProjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFC_newProjDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFC_newProjDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFC_newProjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_newProjDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	brcode_in.GetWindowText(g_brcode);
	if (g_brcode.GetLength() < 6)
	{
		info_edit.SetWindowText(L"No valid barcode readin.");
		brcode_in.SetWindowText(L"");
		return;
	}
	info_edit.SetWindowText(L"Read in barcode.\r\n");
	CString workingdir = L"E:\\temp\\";
	vector<CString> filename;
	vector<CString> wholepath;
	parser_file(workingdir, g_brcode, filename, wholepath);



	//CDialogEx::OnOK();
}

void CMFC_newProjDlg::parser_file(CString filepath, CString brcode, 
	vector<CString>& filename, vector<CString>& wholepath)
{
	CStdioFile filereader;
	bool op_sign = filereader.Open(filepath + brcode + L".txt", CFile::modeRead);
	if (op_sign)
	{
	//	info_edit.ReplaceSel(L"Open target file.\r\nParsering...\r\n");
		CString completecontent;
		filereader.ReadString(completecontent);
		vector<CString> info_parts;
		int nCnt = 0;
		nCnt = completecontent.Find(' ');
		while (nCnt !=  -1)
		{
			info_parts.push_back(completecontent.Left(nCnt));
			completecontent = completecontent.Mid(nCnt + 1);
			nCnt = completecontent.Find(' ');
		}
		info_parts.push_back(completecontent);

		for (int i = 0; i < info_parts.size(); i++)
		{
			CString temp_cont;
			if ((nCnt = info_parts[i].Find('/')) != -1)//layer
			{
				temp_cont = info_parts[i].Mid(nCnt + 1);
				((CEdit*)GetDlgItem(IDC_EDIT3))->SetWindowText(temp_cont);
				temp_cont = info_parts[i].Mid(info_parts[i].Find('=') + 1,
					info_parts[i].GetLength() - info_parts[i].Find('=') - temp_cont.GetLength() - 2);
				((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText(temp_cont);
			}
			else if ((nCnt = info_parts[i].Find(',')) != -1)
			{
				CString temporary;
				temp_cont = info_parts[i].Mid(nCnt + 1);
				double scale_index = 100 + _ttof(temp_cont);
				temporary.Format(L"%.3f", scale_index);
				((CEdit*)GetDlgItem(IDC_EDIT5))->SetWindowText(temporary);
				temp_cont = info_parts[i].Mid(info_parts[i].Find('=') + 1,
					info_parts[i].GetLength() - info_parts[i].Find('=') - temp_cont.GetLength() - 2);
				scale_index = 100 + _ttof(temp_cont);
				temporary.Format(L"%.3f", scale_index);
				((CEdit*)GetDlgItem(IDC_EDIT4))->SetWindowText(temporary);
			}
			else
			{

			}


		}
	}
	else
	{
		info_edit.SetWindowText(L"No such file.");
	}



	filereader.Close();
}
