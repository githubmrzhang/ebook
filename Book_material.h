#pragma once


// Book_material �Ի���

class Book_material : public CDialogEx
{
	DECLARE_DYNAMIC(Book_material)

public:
	Book_material(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Book_material();

public:
	afx_msg void OnPaint();          //�����ı�
public:
	virtual BOOL OnInitDialog();         //���ƶԻ���
public:
	_ConnectionPtr   m_pConnection;     //����
	_CommandPtr      m_pCommand;        //����
	_RecordsetPtr    m_pRecordset;      //��¼


	CListCtrl        m_ListCtrl;        //��ʾ���ݿ����ݿؼ�
	CString          fileDBName;        //·����
public:
	CString    m_Name;                  //����
	CString    m_Author;                //����
	CString    m_Publisher;             //������
	CString    m_ISDN;                  //
	CString    m_Year;                   //��������
	CString    m_Price;                 //�۸�
	CString    m_Size;                  //����
	CString    m_Genre;                 //����
	CString    m_Websit;                //��ַ
public:
	BOOL Link;                          //���ݿ����ӳɹ���ʶ


// �Ի�������
	enum { IDD = IDD_MATERIAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLinkKu();
	afx_msg void OnBnClickedQuery();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedOk();
};
