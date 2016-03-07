// SafetyScan.h : main header file for the SafetyScan application
//

#if !defined(AFX_SAFETYSCAN_H__22D417F0_5640_47E8_AFD6_C6AF5E49D4A7__INCLUDED_)
#define AFX_SAFETYSCAN_H__22D417F0_5640_47E8_AFD6_C6AF5E49D4A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "vector"
using namespace std;
using std::vector;
/////////////////////////////////////////////////////////////////////////////
// CSafetyScanApp:
// See SafetyScan.cpp for the implementation of this class
//

class CSafetyScanApp : public CWinApp
{
public:
	CSafetyScanApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSafetyScanApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

		
// Implementation

	//{{AFX_MSG(CSafetyScanApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAFETYSCAN_H__22D417F0_5640_47E8_AFD6_C6AF5E49D4A7__INCLUDED_)
