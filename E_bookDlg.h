
// E_bookDlg.h : ͷ�ļ�
//

#pragma once


// CE_bookDlg �Ի���
class CE_bookDlg : public CDialogEx
{
// ����
public:
	CE_bookDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_E_BOOK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQuit();
	afx_msg void OnBnClickedChange();
	void OnRead_infor();
	

	CString Log_name_real;   //��ǰ��ȷ���û���
	CString Log_code_real;   //��ǰ��ȷ���û�����
	CString Log_name;
	CString Log_code;
	afx_msg void OnBnClickedLogon();
};
