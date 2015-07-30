
// TCP_chat_xueruifDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TCP_chat_xueruif.h"
#include "TCP_chat_xueruifDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTCP_chat_xueruifDlg 对话框




CTCP_chat_xueruifDlg::CTCP_chat_xueruifDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCP_chat_xueruifDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_sInputText = _T("");
	m_sShowText = _T("");
	m_uPort = 4000;/////初始设置默认为4000端口
}

void CTCP_chat_xueruifDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUTTEXT, m_sInputText);
	DDX_Control(pDX, IDC_SERVERIP, m_ServerIp);
	DDX_Text(pDX, IDC_SHOWTEXT, m_sShowText);
	DDX_Text(pDX, IDC_PORT, m_uPort);
	DDV_MinMaxUInt(pDX, m_uPort, 1024, 100000);//////
}

BEGIN_MESSAGE_MAP(CTCP_chat_xueruifDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CTCP_chat_xueruifDlg::OnClickedConnect)
	ON_EN_UPDATE(IDC_INPUTTEXT, &CTCP_chat_xueruifDlg::OnUpdateInputtext)
	ON_BN_CLICKED(IDC_SETSERVER, &CTCP_chat_xueruifDlg::OnClickedSetserver)
	ON_MESSAGE(SER_MESSAGE,OnServerMessage)//////////
	ON_MESSAGE(CLI_MESSAGE,OnClientMessage)
END_MESSAGE_MAP()


// CTCP_chat_xueruifDlg 消息处理程序

BOOL CTCP_chat_xueruifDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	WSADATA wsaData;				////////////////
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);
	if(ret != 0)
	{
		TRACE("Initilize Error!\n");  //初始化失败
		AfxMessageBox("Failed in initial socket");
	}
//	m_connectionList.AssertValid();
	m_connectionList.RemoveAll();
	ASSERT(m_connectionList.GetCount()==0);
	m_bInit=FALSE;
	m_bClient=FALSE;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTCP_chat_xueruifDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTCP_chat_xueruifDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTCP_chat_xueruifDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTCP_chat_xueruifDlg::OnClickedConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	BYTE  f0,f1,f2,f3;				////////////////
	m_ServerIp.GetAddress(f0,f1,f2,f3);
	CString add;
	add.Format("%d.%d.%d.%d",f0,f1,f2,f3);
	
	if(m_client.InitAndConnet(m_hWnd,m_uPort,add)==FALSE)
		return;
}


void CTCP_chat_xueruifDlg::OnUpdateInputtext()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(!m_bInit)
	{
		AfxMessageBox("The session has not been set correctly");
		return;
	}
	CString in;
	GetDlgItem(IDC_INPUTTEXT)->GetWindowText(in);
	//输入框中只有回车键被按下，所以不发送回车键字符
	if(in.GetLength()<1)
	{
		return;
	}

	if(in.GetAt(in.GetLength()-1)=='\n')
	{
		//in.TrimRight(" ")用来消去无用的空格键字符
		in.TrimRight(" ");
		//将输入框中的字符清空,表示字符已经被发送
		GetDlgItem(IDC_INPUTTEXT)->SetWindowText("");
		if(in.GetLength()>2)
		{
			m_sShowText+=in;
			//将输入的话显示到显示窗口中
			GetDlgItem(IDC_SHOWTEXT)->SetWindowText(m_sShowText);		
			CEdit * output=(CEdit *)GetDlgItem(IDC_SHOWTEXT);
			//随时跟踪滚动条的位置
			output->LineScroll(output->GetLineCount());

			//服务器端
			if(!m_bClient)
			{
				int length=m_connectionList.GetCount();
				SOCKET  socket;
				for(int i=0;i<length;i++)
				{
					socket=m_connectionList.GetAt(m_connectionList.FindIndex(i));
					send(socket,in.GetBuffer(0),in.GetLength(),0);
				}
			}
			//客户端
			else
			{
				m_client.SendString(in);
			}
		}
	}
	
}


void CTCP_chat_xueruifDlg::OnClickedSetserver()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_server.InitAndListen(this->m_hWnd,m_uPort)==FALSE)
	{					/////////
		return;
	}
	else
	{
		m_bInit=TRUE;
		m_bClient=FALSE;
		m_sShowText="Server has been set ok!\n";
		GetDlgItem(IDC_SHOWTEXT)->SetWindowText(m_sShowText);
	}
}

//Server消息相应函数
LRESULT CTCP_chat_xueruifDlg::OnServerMessage(WPARAM wParam, LPARAM lParam)
{

	SOCKET socket,ts;
	int length,i;
	int j;
	CString str="";
	CEdit * output=NULL;
	char s[1024];
	int len;
	switch(lParam)
	{
		case FD_ACCEPT:
			socket= accept(m_server.m_hSocket,NULL,NULL);
			length=m_connectionList.GetCount();
			for(i=0;i<length;i++)
			{
				ts=m_connectionList.GetAt(m_connectionList.FindIndex(i));
				s[0]=NULL;
				strcat(s,"一个游客进入了聊天室");
				send(ts,s,strlen(s),0);
			}
			m_sShowText+="\n";
			m_sShowText+="一个游客进入了聊天室了";
			GetDlgItem(IDC_SHOWTEXT)->SetWindowText(m_sShowText);
			output=(CEdit *)GetDlgItem(IDC_SHOWTEXT);
			//随时跟踪滚动条的位置
			output->LineScroll(output->GetLineCount());
			m_connectionList.AddHead(socket);
			return 0;

		case FD_READ:
			length=m_connectionList.GetCount();
			for(i=0;i<length;i++)
			{
				socket=m_connectionList.GetAt(m_connectionList.FindIndex(i));
				if(socket==wParam)
				{
					len=recv(socket,s,1024,0);
					s[len]=NULL;
					//将一个客户端发送的消息传递到其他客户端去
					for(j=0;j<length;j++)
					{
						socket=m_connectionList.GetAt(m_connectionList.FindIndex(j));
						if(socket!=wParam)
						{
							send(socket,s,strlen(s),0);
						}
					}
					m_sShowText=m_sShowText+s;
					GetDlgItem(IDC_SHOWTEXT)->SetWindowText(m_sShowText);
					CEdit * output=(CEdit *)GetDlgItem(IDC_SHOWTEXT);
					//随时跟踪滚动条的位置
					output->LineScroll(output->GetLineCount());
					return 0;
				}
			}
			return 0;

		case FD_WRITE:
			return 0;

		case FD_CLOSE:
			return 0;

		default:
			m_sShowText=m_sShowText+"An networking error has occured with a client";
			GetDlgItem(IDC_SHOWTEXT)->SetWindowText(m_sShowText);
			CEdit * output=(CEdit *)GetDlgItem(IDC_SHOWTEXT);
			//随时跟踪滚动条的位置
			output->LineScroll(output->GetLineCount());
			return 0;
	}
}

LRESULT CTCP_chat_xueruifDlg::OnClientMessage(WPARAM wParam, LPARAM lParam)
{
	CEdit * output=NULL;
	char s[1024];
	int len;
	switch(lParam)
	{
		case FD_CONNECT:
			len=GetLastError();
			if(len!=0)
			{
				AfxMessageBox("Error in Connecting");
			}
			else
			{
				m_bInit=TRUE;
				m_bClient=TRUE;
				m_sShowText="Having connected to server!\n";
				GetDlgItem(IDC_SHOWTEXT)->SetWindowText(m_sShowText);
			}
			return 0;
		case FD_READ:
			len=recv(m_client.m_hSocket,s,1024,0);
			s[len]=NULL;
			m_sShowText+=s;
			//随时跟踪滚动条的位置 
			output=(CEdit *)GetDlgItem(IDC_SHOWTEXT);
			output->SetWindowText(m_sShowText);
			output->LineScroll(output->GetLineCount());
			return 0;
		case FD_WRITE:
			return 0;
		case FD_CLOSE:
			return 0;
		default:
			output=(CEdit *)GetDlgItem(IDC_SHOWTEXT);
			output->SetWindowText("An network error has occured,the connection is dropped");
			closesocket(m_client.m_hSocket);
			m_bInit=false;
			return 0;
	}
}
