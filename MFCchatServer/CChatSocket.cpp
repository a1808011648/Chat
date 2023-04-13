#include "pch.h"
#include "CChatSocket.h"
#include "MFCchatServer.h"
#include "MFCchatServerDlg.h"


CChatSocket::CChatSocket() {

}

CChatSocket::~CChatSocket() {

}

void CChatSocket::OnReceive(int nErrorCode) {

	TRACE("#####Server OnReceive");
	CMFCchatServerDlg* dlg = (CMFCchatServerDlg*)AfxGetApp()->GetMainWnd();

	//接收数据到BUF
	char szRecvBuf[200] = { 0 };
	this->Receive(szRecvBuf, 200);
	TRACE("#####Server szRecvBuf:%s",szRecvBuf);

	//更新界面
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	dlg->updataListBox(strRecvMsg, _T("客户端："));


	CAsyncSocket::OnReceive(nErrorCode);

	 

}