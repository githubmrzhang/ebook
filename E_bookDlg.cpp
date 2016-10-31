
// E_bookDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "E_book.h"
#include "E_bookDlg.h"
#include "afxdialogex.h"
#include "New_logMessage.h"
#include "Book_material.h"

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


// CE_bookDlg 对话框

void CE_bookDlg::OnRead_infor()
{
	CFile f;
	f.Open(L"data.hxq",CFile::modeCreate|CFile::modeNoTruncate |
		CFile::modeRead);
	CArchive ar(&f,CArchive::load);
	ar>>Log_name_real>>Log_code_real;
	ar.Close();
}


CE_bookDlg::CE_bookDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CE_bookDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Log_name=_T("");
	Log_code=_T("");
	//Log_name_real="admin";
	//Log_code_real="123456";
	OnRead_infor();
	
}

void CE_bookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CE_bookDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_QUIT, &CE_bookDlg::OnBnClickedQuit)
	ON_BN_CLICKED(ID_CHANGE, &CE_bookDlg::OnBnClickedChange)
	ON_BN_CLICKED(ID_LOGON, &CE_bookDlg::OnBnClickedLogon)
END_MESSAGE_MAP()


// CE_bookDlg 消息处理程序

BOOL CE_bookDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CE_bookDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CE_bookDlg::OnPaint()
{
	/*if (IsIconic())
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
	}*/
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CFont font;//字体
	font.CreatePointFont(225,_T("华文行楷"));
	CFont *pOldFont;//原DC中的字体
	pOldFont=dc.SelectObject(&font);

	CString strTemp;
	strTemp="欢迎使用电子书管理系统";
	dc.SetBkMode(TRANSPARENT);//背景为透明
	dc.TextOutW((rect.Width()*1)/5,rect.Height()*1/15,strTemp);

	dc.SelectObject(pOldFont);//恢复自体
	font.DeleteObject();//释放字体
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CE_bookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CE_bookDlg::OnBnClickedQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IDYES==MessageBox(L"确定退出本系统吗？",L"信息提示",MB_YESNO))
	{
		OnOK();
	}
}


void CE_bookDlg::OnBnClickedChange()
{
	// TODO: 在此添加控件通知处理程序代码
	New_logMessage dlg;    //新的用户信息例子
	dlg.Corre_name=Log_name_real;
	dlg.Corre_code=Log_code_real;
	if (IDOK==dlg.DoModal())
	{
		Log_name_real=dlg.New_name;         //传值到主对话框
		Log_code_real=dlg.New_code;
		CFile f;
		f.Open(L"data.hxq",CFile::modeCreate|CFile::modeWrite);//打开
		CArchive ar(&f,CArchive::store);
		ar<<Log_name_real<<Log_code_real;//写出
		ar.Close();
	}

}


void CE_bookDlg::OnBnClickedLogon()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(Log_name);
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(Log_code);
	if (Log_name!=Log_name_real)
	
		MessageBox(L"用户名错误，请重新输入",L"错误提示",MB_OK);
	
	else if ((Log_name==Log_name_real) && (Log_code!=Log_code_real))
	{
		MessageBox(L"用户密码错误，请重新输入",L"错误提示",MB_OK);
	} 
	else
	{
		Book_material dlg;
		dlg.DoModal();
	}

}
