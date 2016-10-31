// Book_Modify.cpp : 实现文件
//

#include "stdafx.h"
#include "E_book.h"
#include "Book_Modify.h"
#include "afxdialogex.h"


// Book_Modify 对话框

IMPLEMENT_DYNAMIC(Book_Modify, CDialogEx)

Book_Modify::Book_Modify(CWnd* pParent /*=NULL*/)
	: CDialogEx(Book_Modify::IDD, pParent)
{
	m_Publisher=_T("");
	m_ISDN=_T("");
	m_Year=_T("");
	m_Price=_T("");
	m_Size=_T("");
	m_Genre=_T("");
	m_Websit=_T("");
}

Book_Modify::~Book_Modify()
{
}

void Book_Modify::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Book_Modify, CDialogEx)
	ON_BN_CLICKED(IDOK, &Book_Modify::OnBnClickedOk)
END_MESSAGE_MAP()


// Book_Modify 消息处理程序


void Book_Modify::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(m_Genre);
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(m_Publisher);
	GetDlgItem(IDC_EDIT3)->GetWindowTextW(m_ISDN);
	GetDlgItem(IDC_EDIT4)->GetWindowTextW(m_Year);
	GetDlgItem(IDC_EDIT5)->GetWindowTextW(m_Price);
	GetDlgItem(IDC_EDIT6)->GetWindowTextW(m_Size);
	GetDlgItem(IDC_EDIT7)->GetWindowTextW(m_Websit);
	OnOK();
}
