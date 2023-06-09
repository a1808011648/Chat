﻿
// MFCchatServerDlg.h: 头文件
//

#pragma once
#include "CServerSocket.h"
#include "CChatSocket.h"
// CMFCchatServerDlg 对话框
#define SEND_MAX_BUF 1024
class CMFCchatServerDlg : public CDialogEx
{
// 构造
public:
	CMFCchatServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartBtn();
protected:
	
	
public:
	CListBox m_list;
	CTime m_time;
	CChatSocket* m_chat = NULL;
	CServerSocket* m_server = NULL;
	BOOL m_startServer =false;
	afx_msg void OnBnClickedSendBtn();
	int updataListBox(const CString& strSendMsg, const CString& strNameUser);
	afx_msg void OnBnClickedClearmsgBtn();
	afx_msg void OnBnClickedStopBtn();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CComboBox m_CwordColorCombo;
	afx_msg void OnBnClickedCalcBtn();
	afx_msg void OnBnClickedMailBtn();
	afx_msg void OnBnClickedQqBtn();
};
