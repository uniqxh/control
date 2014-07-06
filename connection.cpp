// connection.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "connection.h"
#include "ControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cconnection

Cconnection::Cconnection()
{
}

Cconnection::~Cconnection()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(Cconnection, CAsyncSocket)
	//{{AFX_MSG_MAP(Cconnection)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// Cconnection member functions

void Cconnection::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CControlDlg *dlg = (CControlDlg*)AfxGetMainWnd();
	dlg->accept();
	CAsyncSocket::OnAccept(nErrorCode);
}

void Cconnection::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CControlDlg *dlg = (CControlDlg*)AfxGetMainWnd();
	dlg->m_con.Close();
	dlg->m_sock.Close();
	dlg->m_is_con = 0;
	dlg->KillTimer(1);
	dlg->MessageBox("对方断开连接！");
	dlg->m_pic.CloseWindow();
	CAsyncSocket::OnClose(nErrorCode);
}

void Cconnection::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CControlDlg *dlg = (CControlDlg*)AfxGetMainWnd();
	dlg->connection();
	CAsyncSocket::OnConnect(nErrorCode);
}

void Cconnection::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(nErrorCode==0)
	{
		CControlDlg *dlg = (CControlDlg*)AfxGetMainWnd();
		dlg->receive();
	}
	CAsyncSocket::OnReceive(nErrorCode);
}
