// Book_material.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "E_book.h"
#include "Book_material.h"
#include "afxdialogex.h"
#include "New_Book.h"
#include "Book_Modify.h"


// Book_material �Ի���

IMPLEMENT_DYNAMIC(Book_material, CDialogEx)

Book_material::Book_material(CWnd* pParent /*=NULL*/)
	: CDialogEx(Book_material::IDD, pParent)
	,m_Name(_T(""))
	,m_Author(_T(""))
	,m_Publisher(_T(""))
	,m_ISDN(_T(""))
	,m_Year(_T(""))
	,m_Price(_T(""))
	,m_Size(_T(""))
	,m_Genre(_T(""))
	,m_Websit(_T(""))
{
	Link=FALSE;
	CoInitialize(NULL);                  //��ʼ��
}

Book_material::~Book_material()
{
	CoUninitialize();                    //ж��COM��
}

void Book_material::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Book_material, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_LINK_KU, &Book_material::OnBnClickedLinkKu)
	ON_BN_CLICKED(ID_QUERY, &Book_material::OnBnClickedQuery)
	ON_BN_CLICKED(ID_ADD, &Book_material::OnBnClickedAdd)
	ON_BN_CLICKED(ID_DELETE, &Book_material::OnBnClickedDelete)
	ON_BN_CLICKED(ID_MODIFY, &Book_material::OnBnClickedModify)
	ON_BN_CLICKED(IDOK, &Book_material::OnBnClickedOk)
END_MESSAGE_MAP()


// Book_material ��Ϣ�������

void Book_material::OnPaint()
{
	CPaintDC   dc(this);

	CRect rect;
	GetClientRect(&rect);
	CFont font;
	font.CreatePointFont(500,_T("�����п�"));
	CFont *pOldFont;
	pOldFont=dc.SelectObject(&font);

	CString strTemp;
	strTemp ="���������ϵͳ";
	dc.SetBkMode(TRANSPARENT);
	dc.TextOutW((rect.Width()*1)/5,rect.Height()*1/14,strTemp);

	dc.SelectObject(pOldFont);//�ָ�����
	font.DeleteObject();//�ͷ�����
}


BOOL Book_material::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;
	GetClientRect(&rect);                //��ȡ�Ի����С
	CRect rectLeft;
	CRect rectRight;

	GetDlgItem(ID_LINK_KU)->GetWindowRect(&rectLeft);

	GetDlgItem(IDCANCEL)->GetWindowRect(&rectRight);

	ScreenToClient(&rectLeft);
	ScreenToClient(&rectRight);

	//����clistctrl�ؼ�λ��
	rect.left=rectLeft.left-50;
	rect.top+=rect.Height()/4;
	rect.right=rectRight.right+50;
	rect.bottom=rectLeft.top-10;
	BOOL bl=m_ListCtrl.Create(WS_BORDER | WS_VISIBLE | LVS_REPORT,
		rect,this,IDC_LIST_DB);
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_ListCtrl.InsertColumn(0,L"����",LVCFMT_LEFT,50);
	m_ListCtrl.InsertColumn(1,L"����",LVCFMT_LEFT,50);
	m_ListCtrl.InsertColumn(2,L"����",LVCFMT_LEFT,50);
	m_ListCtrl.InsertColumn(3,L"������",LVCFMT_LEFT,80);
	m_ListCtrl.InsertColumn(4,L"ISDN",LVCFMT_LEFT,50);
	m_ListCtrl.InsertColumn(5,L"��������",LVCFMT_LEFT,100);
	m_ListCtrl.InsertColumn(6,L"�۸�",LVCFMT_LEFT,50);
	m_ListCtrl.InsertColumn(7,L"����",LVCFMT_LEFT,50);
	m_ListCtrl.InsertColumn(8,L"��ַ",LVCFMT_LEFT,150);
	return TRUE;

}

void Book_material::OnBnClickedLinkKu()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CFileDialog dlg(TRUE,_T("*mdb"),NULL,OFN_PATHMUSTEXIST
	//	| OFN_OVERWRITEPROMPT
	//	| OFN_HIDEREADONLY,
	//	_T("*mdb|*mdb||"),this);
	//if (dlg.DoModal()!=IDOK)
	//{
	//	return;
	//}
	//fileDBName=dlg.GetPathName();
	CString strConn;
	strConn=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=D:\\zyx.mdb");
	/*strConn+=fileDBName;*/
	

	try
	{
		{
			
			HRESULT hr=m_pConnection.CreateInstance(L"ADODB.Connection");
			
			if (SUCCEEDED(hr))
			{
				hr=m_pConnection->Open((LPCTSTR)strConn,"","",adModeUnknown);
			}
			
		}
		
	}

	catch (_com_error e)
	{
		CString errorMessage;
		errorMessage.Format(L"�������ݿ�ʧ�ܣ�\r\n������Ϣ:%s",e.ErrorMessage());
		AfxMessageBox(errorMessage);
	}
	if (m_pConnection->State)
	{
		AfxMessageBox(L"�Ѿ��ɹ��������ݿ�");
		Link=TRUE;
	}
}


void Book_material::OnBnClickedQuery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Link)
	{
		CString strSQL=L"";
		int nFieldsCount=0;
		long i=0;
		CString strFieldName=L"";
		m_pRecordset.CreateInstance("ADODB.Recordset");
		strSQL="SELECT ����,����,����,������,ISDN,��������,�۸�,����,��ַ FROM eBook";
		try
		{
			m_pRecordset->Open((_variant_t)strSQL,(IDispatch*)m_pConnection,
				adOpenDynamic,adLockOptimistic,adCmdText);

		}
		catch (_com_error* e)
		{
			AfxMessageBox(e->ErrorMessage());
		}
		try
		{
			nFieldsCount=m_pRecordset->GetFields()->Count;

		}
		catch (_com_error* e)
		{
			AfxMessageBox(e->ErrorMessage());
		}

		int nListColCount=0;
		nListColCount=m_ListCtrl.GetHeaderCtrl()->GetItemCount();
		m_ListCtrl.DeleteAllItems();                            //����б���
		for (i=nListColCount-1;i>=0;i--)
		{
			m_ListCtrl.DeleteColumn(i);                         //�����
		}
		for (i=0;i<nFieldsCount;i++)
		{
			//��ȡ�б���
			strFieldName=LPCTSTR(m_pRecordset->GetFields()->GetItem(_variant_t(i))->Name);
			//�����б���
			m_ListCtrl.InsertColumn(i,strFieldName,LVCFMT_LEFT,50,50);
		}

		_variant_t var;                  //
		CString strItemValue;            //��ǰ�ֶε�ֵ
		int nItem=0;                     //�����¼������
		long nFirstCol=0;                //��һ�е�����
		int nIndex=0;                    //��ǵ�ǰ��¼����

		while (!m_pRecordset->adoEOF)
		{
			var=m_pRecordset->GetCollect(_variant_t(nFirstCol));

			if (var.vt!=VT_NULL)
			{
				strItemValue=LPCTSTR(_bstr_t(var));    //����ת��
			}
			nItem=m_ListCtrl.InsertItem(nIndex,strItemValue);

			for (i=1;i<nFieldsCount;i++)               //�����б�ؼ�
			{
				var=m_pRecordset->GetCollect(_variant_t(i));
				if (var.vt!=VT_NULL)
				{
					strItemValue=LPCTSTR(_bstr_t(var));
					m_ListCtrl.SetItemText(nItem,i,strItemValue);
				}
			}
			m_pRecordset->MoveNext();              //������һ����¼
			nIndex++;
		}

			m_ListCtrl.ShowWindow(SW_HIDE);            //���ش���
			for (i=0;i<nFieldsCount;i++)
			{
				m_ListCtrl.SetColumnWidth(i,LVSCW_AUTOSIZE_USEHEADER);       //�����п�

			}

			m_ListCtrl.ShowWindow(SW_SHOW);	
	}
	else
		AfxMessageBox(L"δ���ӵ����ݿ⣬�����������ݿ�");
}


void Book_material::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Link)
	{
		New_Book dlg;
		if (dlg.DoModal()==IDOK)
		{
			if (IDYES==MessageBox(L"ȷ����������¼��",L"��ʾ",MB_YESNO))
			{
				m_Genre=dlg.m_Genre;
				m_Name=dlg.m_Name;
				m_Author=dlg.m_Author;
				m_Publisher=dlg.m_Publisher;
				m_ISDN=dlg.m_ISDN;
				m_Year=dlg.m_Year;
				m_Price=dlg.m_Price;
				m_Size=dlg.m_Size;
				m_Websit=dlg.m_Websit;


				CString strSQL=L"";
				int nFieldsCount=0;
				long i=0;
				CString strFieldName=L"";
				m_pRecordset.CreateInstance("ADODB.Recordset");
				//top
				
				
				strSQL="SELECT ����,����,����,������,ISDN,��������,�۸�,����,��ַ FROM eBook";
				try
				{
					_variant_t ra;
				CString str;
				str.Format(_T("SELECT COUNT(*)  FROM eBook WHERE ����='%s'  AND ����='%s'"),m_Name,m_Author);
				if (m_pConnection->State)
				{
					m_pRecordset=m_pConnection->Execute((LPCTSTR)str,&ra,adCmdText);
				_variant_t vCount = m_pRecordset->GetCollect((_variant_t)(long)(0)); //ȡ�õ�һ���ֶε�ֵ����vCount����

				//m_pRecordset->Close();
				//CString message;
				if (vCount.lVal>0)
				{
					AfxMessageBox(_T("������ͻ,��������������"));
					return ;
				}
				//message.Format(_T("����%d����¼"),vCount.lVal);
				//AfxMessageBox(message); 
				}
				else
				{
					AfxMessageBox((_T("���ݿ����Ӵ���")));
				}
				
				}
				catch (_com_error* e)
				{
					AfxMessageBox(e->ErrorMessage());
				}
			
				m_pRecordset->Close();
				m_pRecordset.CreateInstance("ADODB.Recordset");
			
				
				//int count=Execute();
				try
				{
					

					m_pRecordset->Open((_variant_t)strSQL,(IDispatch*)m_pConnection,
						adOpenDynamic,adLockOptimistic,adCmdText);
					m_pRecordset->AddNew();
					m_pRecordset->PutCollect("����",(_variant_t)m_Genre);
					m_pRecordset->PutCollect("����",(_variant_t)m_Name);
					m_pRecordset->PutCollect("����",(_variant_t)m_Author);
					m_pRecordset->PutCollect("������",(_variant_t)m_Publisher);
					m_pRecordset->PutCollect("ISDN",(_variant_t)m_ISDN);
					m_pRecordset->PutCollect("��������",(_variant_t)m_Year);
					m_pRecordset->PutCollect("�۸�",(_variant_t)m_Price);
					m_pRecordset->PutCollect("����",(_variant_t)m_Size);
					m_pRecordset->PutCollect("��ַ",(_variant_t)m_Websit);
					m_pRecordset->Update();
					m_pRecordset->GetFields();
					AfxMessageBox(L"�ü�¼���ɹ��������");
				}
				catch (_com_error* e)
				{
					AfxMessageBox(e->ErrorMessage());
				}
			}
		}
	}
	else
		AfxMessageBox(L"δ���ӵ�Ŀ�����ݿ⣬���������ݿ�");
}


void Book_material::OnBnClickedDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Link)
	{
		UpdateData();
		CString str,str1;
		int nItemSel=m_ListCtrl.GetSelectionMark();
		//û��ѡ��Ҫɾ����ͼ����Ϣ
		if (nItemSel<0)
		{
			AfxMessageBox(_T("��ѡ��һ����Ч����"));
			return;
		}
		else
		{
			str=m_ListCtrl.GetItemText(nItemSel,1);
			str1=m_ListCtrl.GetItemText(nItemSel,2);
			CString strSQL;
			strSQL.Format(_T("DELETE FROM eBook WHERE ����='%s'  AND ����='%s'"),str,str1);
			_variant_t ra;
			if (IDYES==MessageBoxW(L"ȷ�������¼��",L"��ʾ",MB_YESNO))
			{
				if (m_pConnection->Execute((LPCTSTR)strSQL,&ra,adCmdText))
				{
					m_ListCtrl.DeleteItem(nItemSel);
					OnBnClickedQuery();
				}
			}
		}
	}
	else
		AfxMessageBox(L"δ���ӵ�Ŀ�����ݿ⣬���������ݿ�");
}


void Book_material::OnBnClickedModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Link)
	{
		UpdateData();
		CString str,str1;
		int nItemSel=m_ListCtrl.GetSelectionMark();
		//û��ѡ��Ҫɾ����ͼ����Ϣ
		if (nItemSel<0)
		{
			AfxMessageBox(_T("��ѡ��һ����Ч����"));
			return;
		}
		else
		{
			
			str=m_ListCtrl.GetItemText(nItemSel,1);
			str1=m_ListCtrl.GetItemText(nItemSel,2);
			
			Book_Modify dlg;
			if (IDOK==dlg.DoModal())
			{
			    /* ((CEdit*)GetDlgItem(IDC_EDIT2))->SetReadOnly(TRUE);
				 ((CEdit*)GetDlgItem(IDC_EDIT3))->SetReadOnly(TRUE);*/
				if (dlg.m_Genre!=L"")
				{
					CString strSql;
					strSql.Format(_T("UPDATE eBook SET ����='%s' WHERE ����='%s' AND ����='%s'"),dlg.m_Genre,str,str1);
					_variant_t ra;
					if (m_pConnection->Execute((LPCTSTR)strSql,&ra,adCmdText))
					{
						m_ListCtrl.SetItemText(nItemSel,0,dlg.m_Genre);
					}
				}
				if (dlg.m_Publisher!=L"")
				{
					CString strSql;
					strSql.Format(_T("UPDATE eBook SET ������='%s' WHERE ����='%s' AND ����='%s'"),dlg.m_Publisher,str,str1);
					_variant_t ra;
					if (m_pConnection->Execute((LPCTSTR)strSql,&ra,adCmdText))
					{
						m_ListCtrl.SetItemText(nItemSel,1,dlg.m_Publisher);
					}
				}
				if (dlg.m_ISDN!=L"")
				{
					CString strSql;
					strSql.Format(_T("UPDATE eBook SET ISDN='%s' WHERE ����='%s' AND ����='%s'"),dlg.m_ISDN,str,str1);
					_variant_t ra;
					if (m_pConnection->Execute((LPCTSTR)strSql,&ra,adCmdText))
					{
						m_ListCtrl.SetItemText(nItemSel,2,dlg.m_ISDN);
					}
				}
				if (dlg.m_Year!=L"")
				{
					CString strSql;
					strSql.Format(_T("UPDATE eBook SET ��������='%s' WHERE ����='%s' AND ����='%s'"),dlg.m_Year,str,str1);
					_variant_t ra;
					if (m_pConnection->Execute((LPCTSTR)strSql,&ra,adCmdText))
					{
						m_ListCtrl.SetItemText(nItemSel,3,dlg.m_Year);
					}
				}
				if (dlg.m_Price!=L"")
				{
					CString strSql;
					strSql.Format(_T("UPDATE eBook SET �۸�='%s' WHERE ����='%s' AND ����='%s'"),dlg.m_Price,str,str1);
					_variant_t ra;
					if (m_pConnection->Execute((LPCTSTR)strSql,&ra,adCmdText))
					{
						m_ListCtrl.SetItemText(nItemSel,4,dlg.m_Price);
					}
				}
				if (dlg.m_Size!=L"")
				{
					CString strSql;
					strSql.Format(_T("UPDATE eBook SET ����='%s' WHERE ����='%s' AND ����='%s'"),dlg.m_Size,str,str1);
					_variant_t ra;
					if (m_pConnection->Execute((LPCTSTR)strSql,&ra,adCmdText))
					{
						m_ListCtrl.SetItemText(nItemSel,5,dlg.m_Size);
					}
				}
				if (dlg.m_Websit!=L"")
				{
					CString strSql;
					strSql.Format(_T("UPDATE eBook SET ��ַ='%s' WHERE ����='%s' AND ����='%s'"),dlg.m_Websit,str,str1);
					_variant_t ra;
					if (m_pConnection->Execute((LPCTSTR)strSql,&ra,adCmdText))
					{
						m_ListCtrl.SetItemText(nItemSel,6,dlg.m_Websit);
					}
				}
			}
			///////////////////////////////////////
			OnBnClickedQuery();
		}
	}
	else
		AfxMessageBox(L"δ���ӵ�Ŀ�����ݿ⣬���������ݿ�");
}


void Book_material::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (Link)
	{
		UpdateData();
		CString str,str1;
		int nItemSel=m_ListCtrl.GetSelectionMark();
		//û��ѡ��Ҫɾ����ͼ����Ϣ
		if (nItemSel<0)
		{
			AfxMessageBox(_T("��ѡ��һ����Ч����"));
			return;
		}
		else
		{
			str=m_ListCtrl.GetItemText(nItemSel,1);
			str1=m_ListCtrl.GetItemText(nItemSel,2);
			_variant_t websit;
			m_pRecordset.CreateInstance("ADODB.Recordset");
			CString strSQL;
			strSQL.Format(_T("SELECT * FROM eBook WHERE ����='%s' AND ����='%s'"),str,str1);
			m_pRecordset->Open((LPCTSTR)strSQL,_variant_t((IDispatch*)m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
			websit=m_pRecordset->GetCollect("��ַ");
			if (((LPCTSTR)(_bstr_t)websit)==NULL)
			{
				AfxMessageBox(L"��û���ղ������Ķ���ַ");
				if (IDYES==MessageBox(L"�Ƿ�����������������",L"��ʾ",MB_YESNO))
				{
					return;
				}
				else
				{
					OnOK();
				}
			}
			ShellExecute(AfxGetMainWnd()->m_hWnd,_T("open"),(LPCTSTR)(_bstr_t)websit,_T(""),NULL,0);

		}
		//OnOK();
	}
	else
	{
		AfxMessageBox(L"δ���ӵ�Ŀ�����ݿ⣬���������ݿ�");
	}
}
