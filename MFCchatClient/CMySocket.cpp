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
	//�õ�������
	CMFCchatClientDlg* dlg = (CMFCchatClientDlg*)AfxGetApp()->GetMainWnd();

	
	//�ж��Ƿ����ӳɹ�
	if (nErrorCode != 0) {
		dlg->updataListBox(_T("���ӷ�����ʧ��"), _T(""));
		dlg->m_isConnect = false;
	}
	else {
		dlg->updataListBox(_T("���ӷ������ɹ�"), _T(""));
		dlg->m_isConnect = true;
	}
	
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	CMFCchatClientDlg* dlg = (CMFCchatClientDlg*)AfxGetApp()->GetMainWnd();

	//��������
	char szRecvBuf[200] = { 0 };
	Receive(szRecvBuf, 200);

	//��������ת��
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);

	//��ʾ������
	//��ʾ������
	dlg->updataListBox(strRecvMsg, _T("��������"));
}

void CMySocket::OnSend(int nErrorCode)
{
}
