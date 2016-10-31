#pragma once


// Book_material 对话框

class Book_material : public CDialogEx
{
	DECLARE_DYNAMIC(Book_material)

public:
	Book_material(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Book_material();

public:
	afx_msg void OnPaint();          //绘制文本
public:
	virtual BOOL OnInitDialog();         //绘制对话框
public:
	_ConnectionPtr   m_pConnection;     //连接
	_CommandPtr      m_pCommand;        //命令
	_RecordsetPtr    m_pRecordset;      //记录


	CListCtrl        m_ListCtrl;        //显示数据库内容控件
	CString          fileDBName;        //路径名
public:
	CString    m_Name;                  //书名
	CString    m_Author;                //作者
	CString    m_Publisher;             //出版社
	CString    m_ISDN;                  //
	CString    m_Year;                   //出版日期
	CString    m_Price;                 //价格
	CString    m_Size;                  //开本
	CString    m_Genre;                 //类名
	CString    m_Websit;                //网址
public:
	BOOL Link;                          //数据库连接成功标识


// 对话框数据
	enum { IDD = IDD_MATERIAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLinkKu();
	afx_msg void OnBnClickedQuery();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedOk();
};
