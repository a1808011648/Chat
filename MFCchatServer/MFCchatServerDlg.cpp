
// MFCchatServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCchatServer.h"
#include "MFCchatServerDlg.h"
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


// CMFCchatServerDlg 对话框



CMFCchatServerDlg::CMFCchatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCchatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CMFCchatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CMFCchatServerDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCchatServerDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_CLEARMSG_BTN, &CMFCchatServerDlg::OnBnClickedClearmsgBtn)
END_MESSAGE_MAP()


// CMFCchatServerDlg 消息处理程序

BOOL CMFCchatServerDlg::OnInitDialog()
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
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5038"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCchatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCchatServerDlg::OnPaint()
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
HCURSOR CMFCchatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCchatServerDlg::OnBnClickedStartBtn()
{
	// TODO: 在此添加控件通知处理程序代码

	if (m_startServer) {
		return;
	}


	//获取控件内容：端口
	CString strPort;
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);

	//CSstring转char*
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(strPort);

	//判断端口是否占用了系统端口
	int iPort = atoi(szPort);
	if (iPort <= 1024 || iPort > 65535) {
		MessageBox(_T("端口号必须大于1024小于65535"));
		return;
	}


	//准备服务器套接字
	if (m_server == NULL) {
		m_server = new CServerSocket;
	}

	//创建服务器套接字
	if (!m_server->Create(iPort)) {

		TRACE("m_server Create error: %d", GetLastError());
		return;
	}
	else {
		TRACE("m_server Create Success");
	}

	//开启监听
	if (!m_server->Listen()) {
		TRACE("m_server Listen error: %d", GetLastError());
		return;
	}
	else {
		TRACE("m_server Listen Success");
	}

	CString str;
	m_time = CTime::GetCurrentTime();
	str = m_time.Format("%X ");
	str += _T("服务器启动成功...");
	m_list.AddString(str);

	m_startServer = true;
	

}


void CMFCchatServerDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_startServer == false) {
		MessageBox(_T("服务器还未启动"), _T("提示:"), MB_ICONINFORMATION);
		return;
	}

	if (m_chat == NULL) {
		MessageBox(_T("没有客户端连接"), _T("提示:"), MB_ICONINFORMATION);
		return;
	}
	CString strTmpMsg;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowText(strTmpMsg);
	USES_CONVERSION;
	char* szSendBuf = (char*)T2A(strTmpMsg);

	m_chat->Send(szSendBuf, SEND_MAX_BUF);
	TRACE("m_server Send error:%d", GetLastError());

	//数据更新到界面
	updataListBox(strTmpMsg, _T("服务器："));
}

int CMFCchatServerDlg::updataListBox(const CString& strSendMsg, const CString& strNameUser)
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


void CMFCchatServerDlg::OnBnClickedClearmsgBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}
