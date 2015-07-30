
// TCP_chat_xueruifDlg.h : 头文件
//

#pragma once
#include "Server.h"
#include "Client.h"
#include <afxtempl.h>

#define SER_MESSAGE WM_USER + 100
#define CLI_MESSAGE WM_USER + 101

typedef CList <SOCKET,SOCKET&> SOCKET_ARRAY;
// CTCP_chat_xueruifDlg 对话框
class CTCP_chat_xueruifDlg : public CDialogEx
{
// 构造
public:
	CTCP_chat_xueruifDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TCP_CHAT_XUERUIF_DIALOG };
public:										////////////////
	CServer m_server;
	CClient m_client;
	BOOL m_bInit;
	BOOL m_bClient;
	SOCKET_ARRAY m_connectionList;

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
	afx_msg LRESULT OnServerMessage(WPARAM wParam, LPARAM lParam);///////////
	afx_msg LRESULT OnClientMessage(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedConnect();
	afx_msg void OnUpdateInputtext();
	afx_msg void OnClickedSetserver();
	CString m_sInputText;
	CIPAddressCtrl m_ServerIp;
	CString m_sShowText;
	UINT m_uPort;
};
