// New_Book.cpp : 实现文件
//

#include "stdafx.h"
#include "E_book.h"
#include "New_Book.h"
#include "afxdialogex.h"


// New_Book 对话框

IMPLEMENT_DYNAMIC(New_Book, CDialogEx)

New_Book::New_Book(CWnd* pParent /*=NULL*/)
	: CDialogEx(New_Book::IDD, pParent)
{
	    m_Name=_T("");
		m_Author=_T("");
		m_Publisher=_T("");
		m_ISDN=_T("");
		m_Year=_T("");
		m_Price=_T("");
		m_Size=_T("");
		m_Genre=_T("");
		m_Websit=_T("");
}

New_Book::~New_Book()
{
}

void New_Book::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*DDX_Control(pDX, IDC_EDIT2, editName);
	DDX_Control(pDX, IDC_EDIT3, editAuthor);*/
}


BEGIN_MESSAGE_MAP(New_Book, CDialogEx)
	ON_BN_CLICKED(IDOK, &New_Book::OnBnClickedOk)
END_MESSAGE_MAP()


// New_Book 消息处理程序


void New_Book::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(m_Genre);
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(m_Name);
	GetDlgItem(IDC_EDIT3)->GetWindowTextW(m_Author);
	GetDlgItem(IDC_EDIT4)->GetWindowTextW(m_Publisher);
	GetDlgItem(IDC_EDIT5)->GetWindowTextW(m_ISDN);
	GetDlgItem(IDC_EDIT6)->GetWindowTextW(m_Year);
	GetDlgItem(IDC_EDIT7)->GetWindowTextW(m_Price);
	GetDlgItem(IDC_EDIT8)->GetWindowTextW(m_Size);
	GetDlgItem(IDC_EDIT9)->GetWindowTextW(m_Websit);
	OnOK();
}
