#pragma once


// Book_Modify �Ի���

class Book_Modify : public CDialogEx
{
	DECLARE_DYNAMIC(Book_Modify)

public:
	Book_Modify(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Book_Modify();

	CString    m_Publisher;             //������
	CString    m_ISDN;                  //
	CString    m_Year;                   //��������
	CString    m_Price;                 //�۸�
	CString    m_Size;                  //����
	CString    m_Genre;                 //����
	CString    m_Websit;                //��ַ

// �Ի�������
	enum { IDD = IDD_BOOK_MODIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
