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
	char szRecvBuf[200] = { 0 };
	this->Receive(szRecvBuf, 200);
	TRACE("#####Server szRecvBuf:%s",szRecvBuf);

	//���½���
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	dlg->updataListBox(strRecvMsg, _T("�ͻ��ˣ�"));


	CAsyncSocket::OnReceive(nErrorCode);

	 

}