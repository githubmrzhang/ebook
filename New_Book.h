#pragma once
#include "afxwin.h"


// New_Book �Ի���

class New_Book : public CDialogEx
{
	DECLARE_DYNAMIC(New_Book)

public:
	New_Book(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~New_Book();

public:
	//������Ϣ����
	CString    m_Name;                  //����
	CString    m_Author;                //����
	CString    m_Publisher;             //������
	CString    m_ISDN;                  //
	CString    m_Year;                   //��������
	CString    m_Price;                 //�۸�
	CString    m_Size;                  //����
	CString    m_Genre;                 //����
	CString    m_Websit;                //��ַ

// �Ի�������
	enum { IDD = IDD_NEW_BOOK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

};

