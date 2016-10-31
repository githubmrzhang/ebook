
// E_bookDlg.h : 头文件
//

#pragma once


// CE_bookDlg 对话框
class CE_bookDlg : public CDialogEx
{
// 构造
public:
	CE_bookDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_E_BOOK_DIALOG };

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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQuit();
	afx_msg void OnBnClickedChange();
	void OnRead_infor();
	

	CString Log_name_real;   //当前正确的用户名
	CString Log_code_real;   //当前正确的用户密码
	CString Log_name;
	CString Log_code;
	afx_msg void OnBnClickedLogon();
};
