#pragma once
#include <afxsock.h>

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

