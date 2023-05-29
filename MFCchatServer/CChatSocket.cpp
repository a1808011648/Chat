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

	//�������ݵ�BUF
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	this->Receive(szRecvBuf, SEND_MAX_BUF);
	TRACE("#####Server szRecvBuf:%s",szRecvBuf);

	//���½���
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	dlg->updataListBox(strRecvMsg, _T(""));
	CAsyncSocket::OnReceive(nErrorCode);


}

void CChatSocket::OnClose(int nErrorCode)
{
	CAsyncSocket::OnClose(nErrorCode);
}
