#pragma once


// Book_Modify 对话框

class Book_Modify : public CDialogEx
{
	DECLARE_DYNAMIC(Book_Modify)

public:
	Book_Modify(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Book_Modify();

	CString    m_Publisher;             //出版社
	CString    m_ISDN;                  //
	CString    m_Year;                   //出版日期
	CString    m_Price;                 //价格
	CString    m_Size;                  //开本
	CString    m_Genre;                 //类名
	CString    m_Websit;                //网址

// 对话框数据
	enum { IDD = IDD_BOOK_MODIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
