#include "pch.h"
#include "CMySocket.h"
#include "MFCchatClient.h"
#include "MFCchatClientDlg.h"


CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}

void CMySocket::OnConnect(int nErrorCode)
{
	//得到主窗口
	CMFCchatClientDlg* dlg = (CMFCchatClientDlg*)AfxGetApp()->GetMainWnd();

	
	//判断是否链接成功
	if (nErrorCode != 0) {
		dlg->updataListBox(_T("连接服务器失败"), _T(""));
		dlg->m_isConnect = false;
	}
	else {
		dlg->updataListBox(_T("连接服务器成功"), _T(""));
		dlg->m_isConnect = true;
		dlg->GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(false);

	}
	
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	CMFCchatClientDlg* dlg = (CMFCchatClientDlg*)AfxGetApp()->GetMainWnd();

	//接收数据
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF);

	//数据类型转换
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);

	//显示到界面
	//显示到界面
	dlg->updataListBox(strRecvMsg, _T("服务器："));

	//自动回复
	dlg->autoSendMsg();
}

void CMySocket::OnSend(int nErrorCode)
{
}
