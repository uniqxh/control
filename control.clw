; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CControlDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "control.h"

ClassCount=5
Class1=CControlApp
Class2=CControlDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_Set_Dlg
Resource2=IDR_MAINFRAME
Class4=Cconnection
Resource3=IDD_CONTROL_DIALOG
Resource4=IDD_ABOUTBOX
Class5=Set_Dlg
Resource5=IDR_MAIN_MENU

[CLS:CControlApp]
Type=0
HeaderFile=control.h
ImplementationFile=control.cpp
Filter=N

[CLS:CControlDlg]
Type=0
HeaderFile=controlDlg.h
ImplementationFile=controlDlg.cpp
Filter=D
LastObject=CControlDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=controlDlg.h
ImplementationFile=controlDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CONTROL_DIALOG]
Type=1
Class=CControlDlg
ControlCount=1
Control1=IDC_PIC,static,1342177294

[CLS:Cconnection]
Type=0
HeaderFile=connection.h
ImplementationFile=connection.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q
LastObject=Cconnection

[MNU:IDR_MAIN_MENU]
Type=1
Class=?
Command1=ID_connect
Command2=ID_exit
Command3=ID_min
Command4=ID_max
Command5=ID_restore
CommandCount=5

[CLS:Set_Dlg]
Type=0
HeaderFile=Set_Dlg.h
ImplementationFile=Set_Dlg.cpp
BaseClass=CDialog
Filter=D
LastObject=Set_Dlg
VirtualFilter=dWC

[DLG:IDD_Set_Dlg]
Type=1
Class=Set_Dlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308866
Control4=IDC_IPADDRESS1,SysIPAddress32,1342242816
Control5=IDC_STATIC,static,1342308866
Control6=IDC_PORT,edit,1350631552
Control7=IDC_control,button,1342177289
Control8=IDC_controlled,button,1342177289

