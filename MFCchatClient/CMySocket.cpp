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

	//�õ�ʱ��
	CString str;
	dlg->m_time = CTime::GetCurrentTime();
	str = dlg->m_time.Format("%X ");
	
	//�ж��Ƿ����ӳɹ�
	if (nErrorCode != 0) {
		str += _T("���ӷ�����ʧ��");
		dlg->m_list.AddString(str);
		
	}
	else {
		str += _T("���ӷ������ɹ�");
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
