// New_logMessage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "E_book.h"
#include "New_logMessage.h"
#include "afxdialogex.h"


// New_logMessage �Ի���

IMPLEMENT_DYNAMIC(New_logMessage, CDialogEx)

New_logMessage::New_logMessage(CWnd* pParent /*=NULL*/)
	: CDialogEx(New_logMessage::IDD, pParent)
{
	Corre_name=_T("");
	Corre_code=_T("");
	Old_name=_T("");;
	New_name=_T("");
	New_code=_T("");
	Old_code=_T("");;
}

New_logMessage::~New_logMessage()
{
}

void New_logMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(New_logMessage, CDialogEx)
	ON_BN_CLICKED(IDOK, &New_logMessage::OnBnClickedSure)
END_MESSAGE_MAP()


// New_logMessage ��Ϣ�������


void New_logMessage::OnBnClickedSure()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(Old_name);
	if (Old_name!=Corre_name)
	{
		MessageBox(L"������û���",L"����",MB_OK);
	}
	else
	{
		GetDlgItem(IDC_EDIT2)->GetWindowTextW(New_name);
		GetDlgItem(IDC_EDIT3)->GetWindowTextW(Old_code);
		if (Old_code!=Corre_code)
		{
			MessageBox(L"�û��������",L"����",MB_OK);
		} 
		else
		{
			GetDlgItem(IDC_EDIT4)->GetWindowTextW(New_code);
			AfxMessageBox(L"�û���Ϣ�޸ĳɹ�");
			OnOK();
		}
	}
}
