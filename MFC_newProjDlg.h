
// MFC_newProjDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "vector"

using namespace std;

// CMFC_newProjDlg dialog
class CMFC_newProjDlg : public CDialogEx
{
// Construction
public:
	CMFC_newProjDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_NEWPROJ_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	void parser_file(CString filepath, CString brcode,
		vector<CString>& filename, vector<CString>& wholepath);

	CEdit brcode_in;
	CString g_brcode;
	CEdit info_edit;
};
