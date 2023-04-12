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

	//得到时间
	CString str;
	dlg->m_time = CTime::GetCurrentTime();
	str = dlg->m_time.Format("%X ");
	
	//判断是否链接成功
	if (nErrorCode != 0) {
		str += _T("连接服务器失败");
		dlg->m_list.AddString(str);
		
	}
	else {
		str += _T("连接服务器成功");
		dlg->m_list.AddString(str);
	}
	
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
}

void CMySocket::OnSend(int nErrorCode)
{
}
