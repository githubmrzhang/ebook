
// E_bookDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "E_book.h"
#include "E_bookDlg.h"
#include "afxdialogex.h"
#include "New_logMessage.h"
#include "Book_material.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CE_bookDlg �Ի���

void CE_bookDlg::OnRead_infor()
{
	CFile f;
	f.Open(L"data.hxq",CFile::modeCreate|CFile::modeNoTruncate |
		CFile::modeRead);
	CArchive ar(&f,CArchive::load);
	ar>>Log_name_real>>Log_code_real;
	ar.Close();
}


CE_bookDlg::CE_bookDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CE_bookDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Log_name=_T("");
	Log_code=_T("");
	//Log_name_real="admin";
	//Log_code_real="123456";
	OnRead_infor();
	
}

void CE_bookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CE_bookDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_QUIT, &CE_bookDlg::OnBnClickedQuit)
	ON_BN_CLICKED(ID_CHANGE, &CE_bookDlg::OnBnClickedChange)
	ON_BN_CLICKED(ID_LOGON, &CE_bookDlg::OnBnClickedLogon)
END_MESSAGE_MAP()


// CE_bookDlg ��Ϣ�������

BOOL CE_bookDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CE_bookDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CE_bookDlg::OnPaint()
{
	/*if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}*/
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CFont font;//����
	font.CreatePointFont(225,_T("�����п�"));
	CFont *pOldFont;//ԭDC�е�����
	pOldFont=dc.SelectObject(&font);

	CString strTemp;
	strTemp="��ӭʹ�õ��������ϵͳ";
	dc.SetBkMode(TRANSPARENT);//����Ϊ͸��
	dc.TextOutW((rect.Width()*1)/5,rect.Height()*1/15,strTemp);

	dc.SelectObject(pOldFont);//�ָ�����
	font.DeleteObject();//�ͷ�����
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CE_bookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CE_bookDlg::OnBnClickedQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (IDYES==MessageBox(L"ȷ���˳���ϵͳ��",L"��Ϣ��ʾ",MB_YESNO))
	{
		OnOK();
	}
}


void CE_bookDlg::OnBnClickedChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	New_logMessage dlg;    //�µ��û���Ϣ����
	dlg.Corre_name=Log_name_real;
	dlg.Corre_code=Log_code_real;
	if (IDOK==dlg.DoModal())
	{
		Log_name_real=dlg.New_name;         //��ֵ�����Ի���
		Log_code_real=dlg.New_code;
		CFile f;
		f.Open(L"data.hxq",CFile::modeCreate|CFile::modeWrite);//��
		CArchive ar(&f,CArchive::store);
		ar<<Log_name_real<<Log_code_real;//д��
		ar.Close();
	}

}


void CE_bookDlg::OnBnClickedLogon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(Log_name);
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(Log_code);
	if (Log_name!=Log_name_real)
	
		MessageBox(L"�û�����������������",L"������ʾ",MB_OK);
	
	else if ((Log_name==Log_name_real) && (Log_code!=Log_code_real))
	{
		MessageBox(L"�û������������������",L"������ʾ",MB_OK);
	} 
	else
	{
		Book_material dlg;
		dlg.DoModal();
	}

}
