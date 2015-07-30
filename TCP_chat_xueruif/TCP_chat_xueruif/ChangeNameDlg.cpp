// ChangeNameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TCP_chat_xueruif.h"
#include "ChangeNameDlg.h"
#include "afxdialogex.h"


// CChangeNameDlg 对话框

IMPLEMENT_DYNAMIC(CChangeNameDlg, CDialog)

CChangeNameDlg::CChangeNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeNameDlg::IDD, pParent)
{

	m_sName = _T("");
}

CChangeNameDlg::~CChangeNameDlg()
{
}

void CChangeNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, m_sName);
	DDV_MaxChars(pDX, m_sName, 100);/////
}


BEGIN_MESSAGE_MAP(CChangeNameDlg, CDialog)
END_MESSAGE_MAP()


// CChangeNameDlg 消息处理程序
