
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
	DDX_Control(pDX, IDC_AUTOSEND_RADIO, m_autoSendRadio);
	DDX_Control(pDX, IDC_COLOR_COMBO, m_CwordColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCchatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CMFCchatClientDlg::OnBnClickedConnectBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCchatClientDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_SAVENAME_BTN, &CMFCchatClientDlg::OnBnClickedSavenameBtn)
	ON_BN_CLICKED(IDC_AUTOSEND_RADIO, &CMFCchatClientDlg::OnBnClickedAutosendRadio)
	ON_BN_CLICKED(IDC_CLEARMSG_BTN, &CMFCchatClientDlg::OnBnClickedClearmsgBtn)
	ON_BN_CLICKED(IDC_DISCONNECT_BTN, &CMFCchatClientDlg::OnBnClickedDisconnectBtn)
	ON_WM_CTLCOLOR()
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

	//获取当前目录路径
	WCHAR wSzPath[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, wSzPath);

	//设置即将读取的文件名以及路径
	CString strFilePath;
	strFilePath.Format(_T("%ls//Test.ini"), wSzPath);
	CString strName;
	TCHAR wSzName[256] = {_T("客户端")};
	if (GetPrivateProfileString(_T("CLIENT"), _T("NAME"), NULL, wSzName, 256, strFilePath) <= 0) {
		m_name = _T("客户端：");
		SetDlgItemText(IDC_NAME_EDIT, _T("客户端"));
	}
	else {
		m_name.Format(_T("%s："), wSzName);
		SetDlgItemText(IDC_NAME_EDIT, wSzName);
	}

	m_CwordColorCombo.AddString(_T("黑色"));
	m_CwordColorCombo.AddString(_T("红色"));
	m_CwordColorCombo.AddString(_T("蓝色"));
	m_CwordColorCombo.AddString(_T("绿色"));
	m_CwordColorCombo.SetCurSel(0);
	SetDlgItemText(IDC_COLOR_COMBO, _T("黑色"));

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
	char* szSendBuf = (char*)T2A((m_name + strTmpMsg));

	//发送数据
	m_client->Send(szSendBuf, SEND_MAX_BUF);

	/*CString strTmpMsg;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowText(strTmpMsg);

	m_client->Send(strTmpMsg.GetBuffer(), strTmpMsg.GetLength());*/
	
	//更新界面
	updataListBox(strTmpMsg, m_name);

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


void CMFCchatClientDlg::OnBnClickedSavenameBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IDCANCEL == AfxMessageBox(_T("是否要修改名称吗？"), MB_OKCANCEL)) {
		return;
	}

	
	//得到昵称控件中的内容
	CString strName;
	GetDlgItemText(IDC_NAME_EDIT, strName);

	//判断昵称是否为空
	if (strName.GetLength() <= 0) {
		MessageBox(_T("昵称不能为空！"), _T("提示："), MB_ICONINFORMATION);
		return;
	}

	//获取路径，写入配置文件，保存昵称
	//获取当前路径
	TCHAR wSzPath[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, wSzPath);
	TRACE("#####wSzPath = %ls", wSzPath);


	//设置文件名字和路径
	CString strFilePath;
	strFilePath.Format(_T("%ls//Test.ini"), wSzPath);

	//保存到配置文件
	if (WritePrivateProfileString(_T("CLIENT"), _T("NAME"), strName, strFilePath) != 0) {
		MessageBox(_T("保存成功！"), _T("提示："), MB_ICONINFORMATION);
		m_name = strName + _T("：");
	}
	else {
		MessageBox(_T("保存失败！"), _T("提示："), MB_ICONWARNING);
	}
	


}

//自动回复消息
int CMFCchatClientDlg::autoSendMsg()
{
	// TODO: 在此处添加实现代码.

	//自动回复是否开启
	if (m_autoSendRadio.GetCheck() == false) {
	
		return -1;
	}
	//获取自动回复的内容
	CString strAutoMsg;
	GetDlgItemText(IDC_AUTOMSG_EDIT, strAutoMsg);

	//如果为空 返回
	if (strAutoMsg.GetLength() <= 0) {
		return -1;
	}
	USES_CONVERSION;
	char* szAutoBuf = (char*)T2A((m_name + strAutoMsg));
	m_client->Send(szAutoBuf, SEND_MAX_BUF);

	//更新界面
	updataListBox(strAutoMsg, m_name);

	return 0;
}


void CMFCchatClientDlg::OnBnClickedAutosendRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_autoSendRadio.GetCheck()) {
		m_autoSendRadio.SetCheck(false);
	}
	else {
		m_autoSendRadio.SetCheck(true);
	}
}


void CMFCchatClientDlg::OnBnClickedClearmsgBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CMFCchatClientDlg::OnBnClickedDisconnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_client == NULL) {

		return;
	}
	m_client->Close();
	delete m_client;
	m_client = NULL;
	m_isConnect = false;
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(true);
	updataListBox(_T("服务器已断开..."), _T(""));
}


HBRUSH CMFCchatClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	CString strColor;
	m_CwordColorCombo.GetWindowText(strColor);

	if (IDC_SENDMSG_EDIT == pWnd->GetDlgCtrlID() || IDC_BEFOREMSG_LIST == pWnd->GetDlgCtrlID()) {

		if (strColor == _T("黑色")) {
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		else if (strColor == _T("红色")) {
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		else if (strColor == _T("绿色")) {
			pDC->SetTextColor(RGB(0, 255, 0));
		}
		else if (strColor == _T("蓝色")) {
			pDC->SetTextColor(RGB(0, 0, 255));
		}

	}

	return hbr;
}


BOOL CMFCchatClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	//如果消息等于键盘某键被按下，并且，是回车键那么不做处理
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {

		TRACE(_T("chat---回车"));
		return true;
	}

	//添加快捷键按下CTRL+X退出程序
	if (pMsg->message == WM_KEYDOWN) {

		if (GetKeyState(VK_CONTROL) < 0) {
			TRACE(_T("chat---CTRL"));

			if (pMsg->wParam == 'X') {

				TRACE(_T("chat---X"));
				CDialogEx::OnOK();
			}

		}

	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
