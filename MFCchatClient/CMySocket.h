#pragma once
#include <afxsock.h>
#define SEND_MAX_BUF 1024

class CMySocket :
    public CAsyncSocket
{
public:
    CMySocket();
    ~CMySocket();

    virtual void OnConnect(int nErrorCode);
    virtual void OnReceive(int nErrorCode);
    virtual void OnSend(int nErrorCode);

};

