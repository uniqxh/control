// controlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "controlDlg.h"
#include "connection.h"
#include "sockdata.h"
#include "minilzo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IN_LEN      (128*1024ul)
#define OUT_LEN     (IN_LEN + IN_LEN / 16 + 64 + 3)

static unsigned char __LZO_MMODEL in  [ IN_LEN ];
static unsigned char __LZO_MMODEL out [ OUT_LEN ];

#define HEAP_ALLOC(var,size) \
    lzo_align_t __LZO_MMODEL var [ ((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t) ]

static HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

BMP_SEND_LEN	bmpSendLen,rec;

int ctlcnt,ctldcnt;  
bool flag; //数据头是否接收

unsigned char *pBMP = NULL;
unsigned char *pBMP2 = NULL;
LPRECT lprect;
HBITMAP hTempBitmap;
HBITMAP GetHBmp(HDC hDC, unsigned char *pBuf);
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlDlg dialog

CControlDlg::CControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CControlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CControlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControlDlg)
	DDX_Control(pDX, IDC_PIC, m_pic);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CControlDlg, CDialog)
	//{{AFX_MSG_MAP(CControlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_exit, Onexit)
	ON_COMMAND(ID_connect, Onconnect)
	ON_WM_TIMER()
	ON_COMMAND(ID_min, Onmin)
	ON_COMMAND(ID_max, Onmax)
	ON_COMMAND(ID_restore, Onrestore)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlDlg message handlers

BOOL CControlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	lzo_init();

	flag = 0;
	ctlcnt = 0;
	ctldcnt = 0;

	pBMP = (unsigned char *)malloc(5*1024*1024);
	pBMP2 = (unsigned char *)malloc(5*1024*1024);
	if ((pBMP == NULL) ||(pBMP2 == NULL))
	{
		AfxMessageBox("内存分配失败");
	}
	//要截取位图的大小
	lprect = new RECT();
	GetDesktopWindow()->GetWindowRect(lprect);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CControlDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CControlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//退出程序
void CControlDlg::Onexit() 
{
	OnOK();
}
//接收消息响应，并处理
BOOL CControlDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_ESCAPE)     
	{
		CWnd::ShowWindow(SW_RESTORE);	//SW_SHOWMINIMIZED  	 SW_RESTORE
		ModifyStyle( 0, WS_CAPTION );
		return   TRUE;  //按Esc键，使其退出全屏
	}
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_RETURN)     return   TRUE;  //屏蔽Enter键

	if( m_set_dlg.m_IsControl )  //处理主控端的消息
	{
		msg_data _msg;
		_msg.point = pt;

		if (pMsg->message==WM_KEYDOWN)//模拟键盘事件
		{
			if(pMsg->wParam!=16 && pMsg->wParam!=17)//过滤组合键的第一个键
			{
				if (::GetKeyState(VK_CONTROL)<0)//检取指定虚拟键的状态
				{
					_msg.flag=16;
				}
				else if(::GetKeyState(VK_SHIFT)<0)
				{
					_msg.flag=17;
				}
				else
				{
					_msg.flag=-1;
				}
				_msg.ch=pMsg->wParam;

				send(&_msg);
			}
		}
		else if(pMsg->message == WM_LBUTTONDBLCLK) //左键双击
		{
			_msg.flag=1;
			send(&_msg);
			//MessageBox("doubleclick");
		}
		else if(pMsg->message == WM_LBUTTONDOWN) //左键单击
		{
			_msg.flag=2;
			send(&_msg);
			//MessageBox("leftclick");
		}
		else if(pMsg->message == WM_RBUTTONDOWN) //右键单击
		{
			_msg.flag=3;
			send(&_msg);
			//MessageBox("rightclick");
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
//准备连接
void CControlDlg::Onconnect() 
{
	if( IDOK == m_set_dlg.DoModal() )
	{
		start_connection( m_set_dlg.m_IsControl );
	}
}
//开始连接
void CControlDlg::start_connection(bool iscontrol)
{
	if( iscontrol ) //主控端
	{
		SetPos();
		m_con.Create( atoi( m_set_dlg.m_port ) );
		m_con.Listen();
	}
	else   //被控端
	{
		CWnd::ShowWindow(SW_SHOWMINIMIZED);
		m_sock.Create();
		m_sock.Connect( m_set_dlg.m_ControlIP, atoi( m_set_dlg.m_port ) );
		SetTimer(1,200,0); //设置定时器
	}
}
//主控端连接成功
void CControlDlg::accept()
{
	m_con.Accept(m_sock);
	m_is_con = 1;
	SetWindowText("Control");
}
//被控端连接成功
void CControlDlg::connection()
{
	m_is_con = 1;
	SetWindowText("Controlled");
}

//接收数据
DWORD nDataReceived;
void CControlDlg::receive()
{
	int ret;
	//MessageBox("receive");
	if( m_set_dlg.m_IsControl ) //主控端接收位图信息
	{
		//收取连接来的原始何压缩后数据的大小
		if( !flag )
		{
			//MessageBox("kaishi");

			ret = m_sock.Receive((char *)pBMP, sizeof(BMP_SEND_LEN));
			if (ret == sizeof(BMP_SEND_LEN))
			{
				memcpy(&bmpSendLen, pBMP, sizeof(BMP_SEND_LEN));
				flag = 1;
			}
			nDataReceived = 0;
			return ;
		}

		//开始接收压缩位图的数据

		if (nDataReceived < bmpSendLen.newlen)
		{
			if((ctlcnt = m_sock.Receive((char *)(pBMP + nDataReceived), 
				bmpSendLen.newlen - nDataReceived))==SOCKET_ERROR)
			{
				return ;
			}
			else nDataReceived += ctlcnt;
		}
		CString str;
		str.Format("%d %d",nDataReceived,bmpSendLen.newlen);
		//MessageBox(str);

		if( nDataReceived == bmpSendLen.newlen )
		{
			flag = 0;
			//解压缩位图数据
			int ret2 = lzo1x_decompress(pBMP, bmpSendLen.newlen, pBMP2, 
				&bmpSendLen.oldlen, NULL);
			if (ret2 != LZO_E_OK)
			{
				AfxMessageBox("解压缩错误");
				return ;
			}
			//MessageBox("接收完成");
			//显示到界面上
			CDC *pDC = GetDC();
			HBITMAP hBMP = GetHBmp( pDC->m_hDC, pBMP2);
			m_pic.SetBitmap(hBMP);
			DeleteObject(hBMP);
			ReleaseDC(pDC);
			//m_sock.OnReceive(0);
		}
	}
	else   //被控端接收消息响应
	{
		msg_data _msg;
		if(m_sock.Receive((LPVOID)&_msg,sizeof(msg_data)) == SOCKET_ERROR)
		{
			MessageBox(_T("接收数据时发生错误，请检查网络连接。"),_T("错误"),MB_ICONSTOP);
			return ;
		}
		//MessageBox( msg.str );
		SetCursorPos( _msg.point.x, _msg.point.y );
		if( _msg.ch > 0 ) //处理键盘响应
		{
			if( _msg.flag < 0 )  //单个键盘按键
			{
				keybd_event(_msg.ch,0,0,0);
				keybd_event(_msg.ch,0,KEYEVENTF_KEYUP,0);
			}
			else if( _msg.flag == MSG_CTRL ) //组合键ctr
			{
				keybd_event(16,0,0,0);
				keybd_event(_msg.ch,0,0,0);
				keybd_event(_msg.ch,0,KEYEVENTF_KEYUP,0);
				keybd_event(16,0,KEYEVENTF_KEYUP,0);
			}
			else if( _msg.flag == MSG_SHIFT ) //组合键shift
			{
				keybd_event(17,0,0,0);
				keybd_event(_msg.ch,0,0,0);
				keybd_event(_msg.ch,0,KEYEVENTF_KEYUP,0);
				keybd_event(17,0,KEYEVENTF_KEYUP,0);
			}
		}
		else  //处理鼠标响应
		{
			if( _msg.flag == MSG_LBUTTONDOWN ) mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP,0,0,0,0);
			else if( _msg.flag == MSG_LBUTTONDBLCLK ) 
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP,0,0,0,0);
				mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP,0,0,0,0);
			}
			else if( _msg.flag == MSG_RBUTTONDOWN ) mouse_event(MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP,0,0,0,0);//*/
		}
	}
}
//设置定时器
void CControlDlg::OnTimer(UINT nIDEvent) 
{
	screen();
	CDialog::OnTimer(nIDEvent);
}
//发送消息
void CControlDlg::send(msg_data *m_msg_data)
{
	m_sock.Send((LPVOID)m_msg_data,sizeof(msg_data));
}
//位图数据处理
int ToMemory(HBITMAP hbitmap , unsigned char *pBuf, int ibits)
{
	int ret = 0;
	HDC hdc;			//设备描述表
	WORD wbitcount; 	//当前显示分辨率下每个像素所占字节数
	
	//位图中每个像素所占字节数，定义调色板大小，位图中像素字节大小，位图文件大小 ，写入文件字节数
	DWORD dwpalettesize=0, dwbmbitssize, dwdibsize;

	BITMAP bitmap;				//位图属性结构
	BITMAPFILEHEADER bmfhdr;	//位图文件头结构
	BITMAPINFOHEADER bi;		//位图信息头结构
	LPBITMAPINFOHEADER lpbi;	//指向位图信息头结构
	
	//定义文件，分配内存句柄，调色板句柄
	HANDLE hdib, hpal, holdpal=NULL;

	if (ibits <= 1)
			wbitcount = 1;
	else if (ibits <= 4)
			wbitcount = 4;
	else if (ibits <= 8)
			wbitcount = 8;
	else if (ibits <= 16)
			wbitcount = 16;
	else if (ibits <= 24)
			wbitcount = 24;
	else 
			wbitcount = 32;

	//计算调色板大小
	if (wbitcount <= 8)
		dwpalettesize = (1 << wbitcount) * sizeof(RGBQUAD);

	//设置位图信息头结构
	GetObject(hbitmap, sizeof(BITMAP), (LPSTR)&bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bitmap.bmWidth;
	bi.biHeight = bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wbitcount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	dwbmbitssize = ((bitmap.bmWidth * wbitcount+31)/32)* 4 * bitmap.bmHeight ;
	//为位图内容分配内存
	hdib = GlobalAlloc(GHND, dwbmbitssize + dwpalettesize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hdib);
	*lpbi = bi;
	
	// 处理调色板 
	hpal = GetStockObject(DEFAULT_PALETTE);
	if (hpal)
	{
		hdc = ::GetDC(NULL);
		holdpal = SelectPalette(hdc, (HPALETTE)hpal, false);
		RealizePalette(hdc);
	}
	
	// 获取该调色板下新的像素值
	GetDIBits(hdc, hbitmap, 0, (UINT) bitmap.bmHeight,(LPSTR)lpbi + 
				sizeof(BITMAPINFOHEADER)+dwpalettesize,(BITMAPINFO*)lpbi, DIB_RGB_COLORS);
	
	//恢复调色板 
	if (holdpal)
	{
		SelectPalette(hdc, (HPALETTE)holdpal, true);
		RealizePalette(hdc);
		::ReleaseDC(NULL, hdc);
	}

	
	// 设置位图文件头
	bmfhdr.bfType = 0x4d42; // "BM"
	dwdibsize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+ dwpalettesize + dwbmbitssize; 
	bmfhdr.bfSize = dwdibsize;	//整个BMP文件的大小
	bmfhdr.bfReserved1 = 0;
	bmfhdr.bfReserved2 = 0;
	bmfhdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + 
		(DWORD)sizeof(BITMAPINFOHEADER)+ dwpalettesize; //位图数据的位置

	// 写入位图文件头
	memcpy(pBuf, (LPSTR)&bmfhdr, sizeof(BITMAPFILEHEADER));
	ret += sizeof(BITMAPFILEHEADER);

	// 写入位图文件其余内容
	memcpy(pBuf+ret, (LPSTR)lpbi, dwdibsize);
	ret += dwdibsize;

	//清除 
	GlobalUnlock(hdib);
	GlobalFree(hdib);
	return ret;
}

//客户端截屏并发送数据给主控端
void CControlDlg::screen()
{
	if( !m_is_con )
	{
		KillTimer(1);
		return ;
	}
	if( !flag )
	{
		flag = 1;
		unsigned long l = 0;

		hTempBitmap = getbitmap();

		int ret;
		ret= ToMemory(hTempBitmap, pBMP, 8);

		//压缩
		int r = lzo1x_1_compress(pBMP, ret, pBMP2, &l, wrkmem);
		if (r != LZO_E_OK)
		{
			AfxMessageBox("压缩错误");
			return;
		}

		bmpSendLen.oldlen = ret;
		bmpSendLen.newlen = l;

		//先发位图压缩前后的数据的大小
		m_sock.Send((const char *)&bmpSendLen, sizeof(bmpSendLen));

		ret = l;
		unsigned long nPos = 0;
		int cnt,i=0;
		while ( nPos < bmpSendLen.newlen )
		{
			i++;
			if((cnt = m_sock.Send((const char *)(pBMP2 + nPos),bmpSendLen.newlen-nPos))==SOCKET_ERROR)
			{
				if(GetLastError() == WSAEWOULDBLOCK) break;
			}
			else nPos += cnt;
		}

		DeleteObject(hTempBitmap);

		flag = 0;
	}
}

//客户端截屏
HBITMAP CControlDlg::getbitmap()
{
	HDC hscrdc, hmemdc; 
	// 屏幕和内存设备描述表
	HBITMAP hbitmap, holdbitmap; 
	// 位图句柄
	int nx, ny, nx2, ny2; 
	// 选定区域坐标
	int nwidth, nheight; 
	// 位图宽度和高度
	int xscrn, yscrn; 
	// 屏幕分辨率

	// 确保选定区域不为空矩形
	if (IsRectEmpty(lprect))
		return NULL;

	//为屏幕创建设备描述表
	hscrdc = CreateDC("display", NULL, NULL, NULL);
	//为屏幕设备描述表创建兼容的内存设备描述表
	hmemdc = CreateCompatibleDC(hscrdc);
	// 获得选定区域坐标
	nx = lprect->left;
	ny = lprect->top;
	nx2 = lprect->right;
	ny2 = lprect->bottom;
	// 获得屏幕分辨率
	xscrn = GetDeviceCaps(hscrdc, HORZRES);
	yscrn = GetDeviceCaps(hscrdc, VERTRES);
	//确保选定区域是可见的
	if (nx < 0)
		nx = 0;
	if (ny < 0)
		ny = 0;
	if (nx2 > xscrn)
		nx2 = xscrn;
	if (ny2 > yscrn)
		ny2 = yscrn;

	nwidth = nx2 - nx;
	nheight = ny2 - ny;

	// 创建一个与屏幕设备描述表兼容的位图
	hbitmap = CreateCompatibleBitmap(hscrdc, nwidth, nheight);

	// 把新位图选到内存设备描述表中
	holdbitmap = (HBITMAP)SelectObject(hmemdc, hbitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中
	BitBlt(hmemdc, 0, 0, nwidth, nheight,hscrdc, nx, ny, SRCCOPY);
	//得到屏幕位图的句柄
	hbitmap = (HBITMAP)SelectObject(hmemdc, holdbitmap);
	
	//清除 
	DeleteDC(hscrdc);
	DeleteDC(hmemdc);
	
	// 返回位图句柄
	return hbitmap;
}
//主控端处理位图数据
HBITMAP GetHBmp(HDC hDC, unsigned char *pBuf)
{
	BITMAPINFO *pBmpInfo = NULL;
	unsigned char *pBits = NULL;
	BITMAPFILEHEADER *pBmpFileHeader = NULL;
	pBmpFileHeader = (BITMAPFILEHEADER *)pBuf;
	
	//读出bmp位图信息，BITMAPINFO
	pBmpInfo = (BITMAPINFO *)(pBuf + sizeof(BITMAPFILEHEADER));
	
	//一个扫描行所占用的字节数
	int DataSizePerLine= (pBmpInfo->bmiHeader.biWidth * 
		pBmpInfo->bmiHeader.biBitCount+31)/8; 
	DataSizePerLine= DataSizePerLine/4*4;	//调整
	
	//位图数据大小
	int DataSize= DataSizePerLine * pBmpInfo->bmiHeader.biHeight;
	
	//指向实际的数据区
	pBits = pBuf+pBmpFileHeader->bfOffBits;
	
	//得到一个 HBITMAP，并使用一个图片控件显示在界面上
	HBITMAP hBmp = ::CreateDIBitmap(hDC, 
		&(pBmpInfo->bmiHeader), 
		CBM_INIT, 		
		pBuf+pBmpFileHeader->bfOffBits, 
		pBmpInfo, 
		DIB_RGB_COLORS);
	
	return hBmp;
} 

void CControlDlg::SetPos() //设置对话框大小
{
	ModifyStyle(WS_CAPTION, 0); // 去掉标题栏  
	ModifyStyleEx(WS_EX_DLGMODALFRAME, 0); // 去掉边框
	CWnd::ShowWindow(SW_SHOWMAXIMIZED );
}

void CControlDlg::Onmin() 
{
	CWnd::ShowWindow(SW_SHOWMINIMIZED ); //最小化
}

void CControlDlg::Onmax() 
{
	ModifyStyle(WS_CAPTION, 0); // 去掉标题栏
	CWnd::ShowWindow(SW_SHOWMAXIMIZED ); //最大化
}

void CControlDlg::Onrestore() 
{	 
	CWnd::ShowWindow(SW_RESTORE );  //还原
	ModifyStyle( 0, WS_CAPTION );   //显示标题栏
}

void CControlDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CControlDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CControlDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CControlDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CControlDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonUp(nFlags, point);
}

void CControlDlg::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnRButtonDblClk(nFlags, point);
}

void CControlDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CControlDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnRButtonUp(nFlags, point);
}


void CControlDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	pt = point;
	CDialog::OnMouseMove(nFlags, point);
}
