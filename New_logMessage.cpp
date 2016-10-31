// New_logMessage.cpp : 实现文件
//

#include "stdafx.h"
#include "E_book.h"
#include "New_logMessage.h"
#include "afxdialogex.h"


// New_logMessage 对话框

IMPLEMENT_DYNAMIC(New_logMessage, CDialogEx)

New_logMessage::New_logMessage(CWnd* pParent /*=NULL*/)
	: CDialogEx(New_logMessage::IDD, pParent)
{
	Corre_name=_T("");
	Corre_code=_T("");
	Old_name=_T("");;
	New_name=_T("");
	New_code=_T("");
	Old_code=_T("");;
}

New_logMessage::~New_logMessage()
{
}

void New_logMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(New_logMessage, CDialogEx)
	ON_BN_CLICKED(IDOK, &New_logMessage::OnBnClickedSure)
END_MESSAGE_MAP()


// New_logMessage 消息处理程序


void New_logMessage::OnBnClickedSure()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(Old_name);
	if (Old_name!=Corre_name)
	{
		MessageBox(L"错误的用户名",L"警告",MB_OK);
	}
	else
	{
		GetDlgItem(IDC_EDIT2)->GetWindowTextW(New_name);
		GetDlgItem(IDC_EDIT3)->GetWindowTextW(Old_code);
		if (Old_code!=Corre_code)
		{
			MessageBox(L"用户密码错误",L"警告",MB_OK);
		} 
		else
		{
			GetDlgItem(IDC_EDIT4)->GetWindowTextW(New_code);
			AfxMessageBox(L"用户信息修改成功");
			OnOK();
		}
	}
}
