#include "pch.h"
#include "CServerSocket.h"
#include "MFCchatServer.h"
#include "MFCchatServerDlg.h"



CServerSocket::CServerSocket() {

}
CServerSocket::~CServerSocket() {

}
void CServerSocket::OnAccept(int nErrorCode) {

	TRACE("[chat] Aceept，code：%d", nErrorCode);
	CMFCchatServerDlg* dlg = (CMFCchatServerDlg*)AfxGetApp()->GetMainWnd();
	dlg->m_chat = new CChatSocket;
	this->Accept(*(dlg->m_chat));

	dlg->updataListBox(_T("客户端连接成功"), _T(""));

	CAsyncSocket::OnAccept(nErrorCode);
}

void CServerSocket::OnClose(int nErrorCode)
{

	CAsyncSocket::OnClose(nErrorCode);
}
