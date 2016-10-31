#pragma once


// New_logMessage 对话框

class New_logMessage : public CDialogEx
{
	DECLARE_DYNAMIC(New_logMessage)

public:
	New_logMessage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~New_logMessage();
	//test TOOD
	CString Corre_name;    //正确的用户名
	CString Corre_code;    //正确的密码
	CString Old_name;      //原用户名
	CString New_name;      //新用户名
	CString Old_code;      //原密码
	CString New_code;      //新密码

// 对话框数据
	enum { IDD = IDD_INFORMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSure();
};
