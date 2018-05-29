
// ReTRPatchMDlg.h : header file
//

#pragma once


// CReTRPatchMDlg dialog
class CReTRPatchMDlg : public CDialogEx
{
// Construction
public:
	CReTRPatchMDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RETRPATCHM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSelectfile();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedBackuppatch();
	afx_msg void OnBnClickedVtr2();
	afx_msg void OnBnClickedVtr3();
	afx_msg void OnBnClickedVtr4();
	afx_msg void OnBnClickedVtr5();
};
