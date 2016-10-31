#pragma once
#include "afxwin.h"


// New_Book 对话框

class New_Book : public CDialogEx
{
	DECLARE_DYNAMIC(New_Book)

public:
	New_Book(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~New_Book();

public:
	//新书信息变量
	CString    m_Name;                  //书名
	CString    m_Author;                //作者
	CString    m_Publisher;             //出版社
	CString    m_ISDN;                  //
	CString    m_Year;                   //出版日期
	CString    m_Price;                 //价格
	CString    m_Size;                  //开本
	CString    m_Genre;                 //类名
	CString    m_Websit;                //网址

// 对话框数据
	enum { IDD = IDD_NEW_BOOK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

};

