#pragma once


// New_logMessage �Ի���

class New_logMessage : public CDialogEx
{
	DECLARE_DYNAMIC(New_logMessage)

public:
	New_logMessage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~New_logMessage();
	//test TOOD
	CString Corre_name;    //��ȷ���û���
	CString Corre_code;    //��ȷ������
	CString Old_name;      //ԭ�û���
	CString New_name;      //���û���
	CString Old_code;      //ԭ����
	CString New_code;      //������

// �Ի�������
	enum { IDD = IDD_INFORMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSure();
};
