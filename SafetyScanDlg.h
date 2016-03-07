// SafetyScanDlg.h : header file
//

#if !defined(AFX_SAFETYSCANDLG_H__434FDC3B_FF29_429F_8BFF_12446A07EF74__INCLUDED_)
#define AFX_SAFETYSCANDLG_H__434FDC3B_FF29_429F_8BFF_12446A07EF74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SafeConfigMng.h"
/////////////////////////////////////////////////////////////////////////////
// CSafetyScanDlg dialog

class CSafetyScanDlg : public CDialog
{
// Construction
public:
	CSafetyScanDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSafetyScanDlg)
	enum { IDD = IDD_SAFETYSCAN_DIALOG };
	CListBox	m_ListInfo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSafetyScanDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	void process();
	// Generated message map functions
	//{{AFX_MSG(CSafetyScanDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	SafeConfigMng g_pconfigmng;
	vector<CString> m_vsoftinfo;//存放软件信息
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAFETYSCANDLG_H__434FDC3B_FF29_429F_8BFF_12446A07EF74__INCLUDED_)
