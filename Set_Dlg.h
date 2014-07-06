#if !defined(AFX_SET_DLG_H__D82EFC51_01B5_4103_822C_B53B368A236D__INCLUDED_)
#define AFX_SET_DLG_H__D82EFC51_01B5_4103_822C_B53B368A236D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Set_Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Set_Dlg dialog

class Set_Dlg : public CDialog
{
// Construction
public:
	CString m_ControlIP;
	bool m_IsControl;
	Set_Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Set_Dlg)
	enum { IDD = IDD_Set_Dlg };
	CIPAddressCtrl	m_ip;
	CString	m_port;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Set_Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Set_Dlg)
	afx_msg void Oncontrol();
	afx_msg void Oncontrolled();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SET_DLG_H__D82EFC51_01B5_4103_822C_B53B368A236D__INCLUDED_)
