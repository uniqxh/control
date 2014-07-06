// Set_Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "Set_Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Set_Dlg dialog


Set_Dlg::Set_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Set_Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Set_Dlg)
	m_port = _T("");
	//}}AFX_DATA_INIT
}


void Set_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Set_Dlg)
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
	DDX_Text(pDX, IDC_PORT, m_port);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Set_Dlg, CDialog)
	//{{AFX_MSG_MAP(Set_Dlg)
	ON_BN_CLICKED(IDC_control, Oncontrol)
	ON_BN_CLICKED(IDC_controlled, Oncontrolled)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Set_Dlg message handlers

void Set_Dlg::Oncontrol() 
{
	// TODO: Add your control notification handler code here
	m_IsControl = 1;
	m_ip.SetWindowText( "127.0.0.1" );
	m_port = "2014";
	UpdateData(false);
}

void Set_Dlg::Oncontrolled() 
{
	// TODO: Add your control notification handler code here
	m_IsControl = 0;
	m_ip.SetWindowText( "192.168.1.109" );
	m_port = "2014";
	UpdateData(false);
}

BOOL Set_Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CButton*)GetDlgItem(IDC_control))->SetCheck(1);
	Oncontrol();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Set_Dlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(1);
	m_ip.GetWindowText( m_ControlIP );
	CDialog::OnOK();
}
