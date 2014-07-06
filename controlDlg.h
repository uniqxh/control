// controlDlg.h : header file
//

#if !defined(AFX_CONTROLDLG_H__212077D3_EAF7_48A0_8D61_76674B3AF8FA__INCLUDED_)
#define AFX_CONTROLDLG_H__212077D3_EAF7_48A0_8D61_76674B3AF8FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "connection.h"
#include "Set_Dlg.h"	// Added by ClassView
#include "sockdata.h"
/////////////////////////////////////////////////////////////////////////////
// CControlDlg dialog

class CControlDlg : public CDialog
{
// Construction
public:
	CPoint pt;
	void SetPos();
	HBITMAP getbitmap();
	void screen();
	void send(msg_data *m_msg_data);
	void receive();
	void connection();
	bool m_is_con;
	void accept();
	void start_connection(bool iscontrol);
	Set_Dlg m_set_dlg;
	Cconnection m_sock;
	Cconnection m_con;
	CControlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CControlDlg)
	enum { IDD = IDD_CONTROL_DIALOG };
	CStatic	m_pic;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CControlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void Onexit();
	afx_msg void Onconnect();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void Onmin();
	afx_msg void Onmax();
	afx_msg void Onrestore();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLDLG_H__212077D3_EAF7_48A0_8D61_76674B3AF8FA__INCLUDED_)
