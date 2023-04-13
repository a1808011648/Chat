
// MFCchatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCchatClient.h"
#include "MFCchatClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCchatClientDlg 对话框



CMFCchatClientDlg::CMFCchatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCchatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BEFOREMSG_LIST, m_list);
	DDX_Control(pDX, IDC_SENDMSG_EDIT, m_input);
}

BEGIN_MESSAGE_MAP(CMFCchatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CMFCchatClientDlg::OnBnClickedConnectBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCchatClientDlg::OnBnClickedSendBtn)
END_MESSAGE_MAP()


// CMFCchatClientDlg 消息处理程序

BOOL CMFCchatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//初始化端口控件为62023,并且设置风格为只能输入数字
	HWND hEdit = GetDlgItem(IDC_PORT_EDIT)->GetSafeHwnd(); //得到句柄

	//得到Edit控件当前的风格
	LONG sytle = GetWindowLong(hEdit, GWL_STYLE);

	//在之前的风格上加入新的风格
	SetWindowLong(hEdit, GWL_STYLE, sytle | ES_NUMBER);

	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5038"));
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCchatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCchatClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCchatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCchatClientDlg::OnBnClickedConnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//关闭之前的连接
	if (m_isConnect) {
		return;
	}

	//获取控件里面的IP以及端口
	CString strPort, strIP;
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIP);

	//CString 转char*
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	LPCSTR szIP = (LPCSTR)T2A(strIP);

	//端口号是否占用了系统端口
	int iPort = atoi(szPort);
	if (iPort <= 1024 || iPort > 65535) {
		MessageBox(_T("端口号必须大于1024小于65535"));
		return;
	}

	//打印调试
	TRACE("[chat]--szPort = %s szIP = %s", szPort, szIP);

	//分配一个套接字内存
	if (m_client == NULL) {
		m_client = new CMySocket;
		//创建套接字
		if (!m_client->Create()) {

			TRACE("m_client Create error: %d", GetLastError());
		}
		else {
			TRACE("m_client Create Success");
		}

	}

	

	//链接服务器
	if (m_client->Connect(strIP, iPort) == SOCKET_ERROR) {
		TRACE("m_client Connect error:%d", GetLastError());
		return;
	}

	
}


void CMFCchatClientDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//判断是否连接上了服务器
	if (m_isConnect == false) {
		MessageBox(_T("没有与服务器连接，无法发送！"),_T("提示:"), MB_ICONINFORMATION);
		return;
	}
	//获取发送控件的内容
	CString strTmpMsg;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowText(strTmpMsg);

	//转换为char*
	USES_CONVERSION;
	char* szSendBuf = (char*)T2A(strTmpMsg);

	//发送数据
	m_client->Send(szSendBuf, 200);

	/*CString strTmpMsg;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowText(strTmpMsg);

	m_client->Send(strTmpMsg.GetBuffer(), strTmpMsg.GetLength());*/
	
	//更新界面
	updataListBox(strTmpMsg, _T("我："));

}


int CMFCchatClientDlg::updataListBox(const CString& strSendMsg,const CString& strNameUser)
{
	// TODO: 在此处添加实现代码.

	//数据更新到界面
	m_time = CTime::GetCurrentTime();
	CString strShow = m_time.Format("%X ");
	strShow += strNameUser + strSendMsg;
	m_list.AddString(strShow);
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowText(_T(""));
	GetDlgItem(IDC_SENDMSG_EDIT)->SetFocus();
	return 0;
}
