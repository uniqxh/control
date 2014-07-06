// control.h : main header file for the CONTROL application
//

#if !defined(AFX_CONTROL_H__05341F0A_9FE9_4C21_B9E5_B540AB59FB94__INCLUDED_)
#define AFX_CONTROL_H__05341F0A_9FE9_4C21_B9E5_B540AB59FB94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CControlApp:
// See control.cpp for the implementation of this class
//

class CControlApp : public CWinApp
{
public:
	CControlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CControlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROL_H__05341F0A_9FE9_4C21_B9E5_B540AB59FB94__INCLUDED_)
