// Book_material.cpp : 实现文件
//

#include "stdafx.h"
#include "E_book.h"
#include "Book_material.h"
#include "afxdialogex.h"
#include "New_Book.h"
#include "Book_Modify.h"


// Book_material 对话框

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
	CoInitialize(NULL);                  //初始化
}

Book_material::~Book_material()
{
	CoUninitialize();                    //卸载COM库
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


// Book_material 消息处理程序

void Book_material::OnPaint()
{
	CPaintDC   dc(this);

	CRect rect;
	GetClientRect(&rect);
	CFont font;
	font.CreatePointFont(500,_T("华文行楷"));
	CFont *pOldFont;
	pOldFont=dc.SelectObject(&font);

	CString strTemp;
	strTemp ="电子书管理系统";
	dc.SetBkMode(TRANSPARENT);
	dc.TextOutW((rect.Width()*1)/5,rect.Height()*1/14,strTemp);

	dc.SelectObject(pOldFont);//恢复自体
	font.DeleteObject();//释放字体
}


BOOL Book_material::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;
	GetClientRect(&rect);                //获取对话框大小
	CRect rectLeft;
	CRect rectRight;

	GetDlgItem(ID_LINK_KU)->GetWindowRect(&rectLeft);

	GetDlgItem(IDCANCEL)->GetWindowRect(&rectRight);

	ScreenToClient(&rectLeft);
	ScreenToClient(&rectRight);

	//设置clistctrl控件位置
	rect.left=rectLeft.left-50;
	rect.top+=rect.Height()/4;
	rect.right=rectRight.right+50;
	rect.bottom=rectLeft.top-10;
	BOOL bl=m_ListCtrl.Create(WS_BORDER | WS_VISIBLE | LVS_REPORT,
		rect,this,IDC_LIST_DB);
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_ListCtrl.InsertColumn(0,L"分类",LVCFMT_LEFT,50);
	m_ListCtrl.InsertColumn(1,L"书名",LVCFMT_LEFT,50);
	m_ListCtrl.InsertColumn(2,L"作者",LVCFMT_LEFT,50);
	m_ListCtrl.InsertColumn(3,L"出版社",LVCFMT_LEFT,80);
	m_ListCtrl.InsertColumn(4,L"ISDN",LVCFMT_LEFT,50);
	m_ListCtrl.InsertColumn(5,L"出版日期",LVCFMT_LEFT,100);
	m_ListCtrl.InsertColumn(6,L"价格￥",LVCFMT_LEFT,50);
	m_ListCtrl.InsertColumn(7,L"开本",LVCFMT_LEFT,50);
	m_ListCtrl.InsertColumn(8,L"网址",LVCFMT_LEFT,150);
	return TRUE;

}

void Book_material::OnBnClickedLinkKu()
{
	// TODO: 在此添加控件通知处理程序代码
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
		errorMessage.Format(L"连接数据库失败！\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errorMessage);
	}
	if (m_pConnection->State)
	{
		AfxMessageBox(L"已经成功连接数据库");
		Link=TRUE;
	}
}


void Book_material::OnBnClickedQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	if (Link)
	{
		CString strSQL=L"";
		int nFieldsCount=0;
		long i=0;
		CString strFieldName=L"";
		m_pRecordset.CreateInstance("ADODB.Recordset");
		strSQL="SELECT 分类,书名,作者,出版社,ISDN,出版日期,价格￥,开本,网址 FROM eBook";
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
		m_ListCtrl.DeleteAllItems();                            //清空列标题
		for (i=nListColCount-1;i>=0;i--)
		{
			m_ListCtrl.DeleteColumn(i);                         //清空列
		}
		for (i=0;i<nFieldsCount;i++)
		{
			//获取列标题
			strFieldName=LPCTSTR(m_pRecordset->GetFields()->GetItem(_variant_t(i))->Name);
			//插入列标题
			m_ListCtrl.InsertColumn(i,strFieldName,LVCFMT_LEFT,50,50);
		}

		_variant_t var;                  //
		CString strItemValue;            //当前字段的值
		int nItem=0;                     //插入记录的行数
		long nFirstCol=0;                //第一列的索引
		int nIndex=0;                    //标记当前记录索引

		while (!m_pRecordset->adoEOF)
		{
			var=m_pRecordset->GetCollect(_variant_t(nFirstCol));

			if (var.vt!=VT_NULL)
			{
				strItemValue=LPCTSTR(_bstr_t(var));    //类型转换
			}
			nItem=m_ListCtrl.InsertItem(nIndex,strItemValue);

			for (i=1;i<nFieldsCount;i++)               //填入列表控件
			{
				var=m_pRecordset->GetCollect(_variant_t(i));
				if (var.vt!=VT_NULL)
				{
					strItemValue=LPCTSTR(_bstr_t(var));
					m_ListCtrl.SetItemText(nItem,i,strItemValue);
				}
			}
			m_pRecordset->MoveNext();              //插入下一条记录
			nIndex++;
		}

			m_ListCtrl.ShowWindow(SW_HIDE);            //隐藏窗口
			for (i=0;i<nFieldsCount;i++)
			{
				m_ListCtrl.SetColumnWidth(i,LVSCW_AUTOSIZE_USEHEADER);       //调整列宽

			}

			m_ListCtrl.ShowWindow(SW_SHOW);	
	}
	else
		AfxMessageBox(L"未连接到数据库，请先连接数据库");
}


void Book_material::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	if (Link)
	{
		New_Book dlg;
		if (dlg.DoModal()==IDOK)
		{
			if (IDYES==MessageBox(L"确定添加这组记录吗？",L"提示",MB_YESNO))
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
				
				
				strSQL="SELECT 分类,书名,作者,出版社,ISDN,出版日期,价格￥,开本,网址 FROM eBook";
				try
				{
					_variant_t ra;
				CString str;
				str.Format(_T("SELECT COUNT(*)  FROM eBook WHERE 书名='%s'  AND 作者='%s'"),m_Name,m_Author);
				if (m_pConnection->State)
				{
					m_pRecordset=m_pConnection->Execute((LPCTSTR)str,&ra,adCmdText);
				_variant_t vCount = m_pRecordset->GetCollect((_variant_t)(long)(0)); //取得第一个字段的值放入vCount变量

				//m_pRecordset->Close();
				//CString message;
				if (vCount.lVal>0)
				{
					AfxMessageBox(_T("主键冲突,即将返回主界面"));
					return ;
				}
				//message.Format(_T("共有%d条记录"),vCount.lVal);
				//AfxMessageBox(message); 
				}
				else
				{
					AfxMessageBox((_T("数据库链接错误")));
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
					m_pRecordset->PutCollect("分类",(_variant_t)m_Genre);
					m_pRecordset->PutCollect("书名",(_variant_t)m_Name);
					m_pRecordset->PutCollect("作者",(_variant_t)m_Author);
					m_pRecordset->PutCollect("出版社",(_variant_t)m_Publisher);
					m_pRecordset->PutCollect("ISDN",(_variant_t)m_ISDN);
					m_pRecordset->PutCollect("出版日期",(_variant_t)m_Year);
					m_pRecordset->PutCollect("价格￥",(_variant_t)m_Price);
					m_pRecordset->PutCollect("开本",(_variant_t)m_Size);
					m_pRecordset->PutCollect("网址",(_variant_t)m_Websit);
					m_pRecordset->Update();
					m_pRecordset->GetFields();
					AfxMessageBox(L"该记录被成功加入表中");
				}
				catch (_com_error* e)
				{
					AfxMessageBox(e->ErrorMessage());
				}
			}
		}
	}
	else
		AfxMessageBox(L"未连接到目标数据库，请连接数据库");
}


void Book_material::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if (Link)
	{
		UpdateData();
		CString str,str1;
		int nItemSel=m_ListCtrl.GetSelectionMark();
		//没有选择要删除的图书信息
		if (nItemSel<0)
		{
			AfxMessageBox(_T("请选择一条有效数据"));
			return;
		}
		else
		{
			str=m_ListCtrl.GetItemText(nItemSel,1);
			str1=m_ListCtrl.GetItemText(nItemSel,2);
			CString strSQL;
			strSQL.Format(_T("DELETE FROM eBook WHERE 书名='%s'  AND 作者='%s'"),str,str1);
			_variant_t ra;
			if (IDYES==MessageBoxW(L"确定这组记录吗？",L"提示",MB_YESNO))
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
		AfxMessageBox(L"未连接到目标数据库，请连接数据库");
}


void Book_material::OnBnClickedModify()
{
	// TODO: 在此添加控件通知处理程序代码
	if (Link)
	{
		UpdateData();
		CString str,str1;
		int nItemSel=m_ListCtrl.GetSelectionMark();
		//没有选择要删除的图书信息
		if (nItemSel<0)
		{
			AfxMessageBox(_T("请选择一条有效数据"));
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
					strSql.Format(_T("UPDATE eBook SET 分类='%s' WHERE 书名='%s' AND 作者='%s'"),dlg.m_Genre,str,str1);
					_variant_t ra;
					if (m_pConnection->Execute((LPCTSTR)strSql,&ra,adCmdText))
					{
						m_ListCtrl.SetItemText(nItemSel,0,dlg.m_Genre);
					}
				}
				if (dlg.m_Publisher!=L"")
				{
					CString strSql;
					strSql.Format(_T("UPDATE eBook SET 出版社='%s' WHERE 书名='%s' AND 作者='%s'"),dlg.m_Publisher,str,str1);
					_variant_t ra;
					if (m_pConnection->Execute((LPCTSTR)strSql,&ra,adCmdText))
					{
						m_ListCtrl.SetItemText(nItemSel,1,dlg.m_Publisher);
					}
				}
				if (dlg.m_ISDN!=L"")
				{
					CString strSql;
					strSql.Format(_T("UPDATE eBook SET ISDN='%s' WHERE 书名='%s' AND 作者='%s'"),dlg.m_ISDN,str,str1);
					_variant_t ra;
					if (m_pConnection->Execute((LPCTSTR)strSql,&ra,adCmdText))
					{
						m_ListCtrl.SetItemText(nItemSel,2,dlg.m_ISDN);
					}
				}
				if (dlg.m_Year!=L"")
				{
					CString strSql;
					strSql.Format(_T("UPDATE eBook SET 出版日期='%s' WHERE 书名='%s' AND 作者='%s'"),dlg.m_Year,str,str1);
					_variant_t ra;
					if (m_pConnection->Execute((LPCTSTR)strSql,&ra,adCmdText))
					{
						m_ListCtrl.SetItemText(nItemSel,3,dlg.m_Year);
					}
				}
				if (dlg.m_Price!=L"")
				{
					CString strSql;
					strSql.Format(_T("UPDATE eBook SET 价格￥='%s' WHERE 书名='%s' AND 作者='%s'"),dlg.m_Price,str,str1);
					_variant_t ra;
					if (m_pConnection->Execute((LPCTSTR)strSql,&ra,adCmdText))
					{
						m_ListCtrl.SetItemText(nItemSel,4,dlg.m_Price);
					}
				}
				if (dlg.m_Size!=L"")
				{
					CString strSql;
					strSql.Format(_T("UPDATE eBook SET 开本='%s' WHERE 书名='%s' AND 作者='%s'"),dlg.m_Size,str,str1);
					_variant_t ra;
					if (m_pConnection->Execute((LPCTSTR)strSql,&ra,adCmdText))
					{
						m_ListCtrl.SetItemText(nItemSel,5,dlg.m_Size);
					}
				}
				if (dlg.m_Websit!=L"")
				{
					CString strSql;
					strSql.Format(_T("UPDATE eBook SET 网址='%s' WHERE 书名='%s' AND 作者='%s'"),dlg.m_Websit,str,str1);
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
		AfxMessageBox(L"未连接到目标数据库，请连接数据库");
}


void Book_material::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (Link)
	{
		UpdateData();
		CString str,str1;
		int nItemSel=m_ListCtrl.GetSelectionMark();
		//没有选择要删除的图书信息
		if (nItemSel<0)
		{
			AfxMessageBox(_T("请选择一条有效数据"));
			return;
		}
		else
		{
			str=m_ListCtrl.GetItemText(nItemSel,1);
			str1=m_ListCtrl.GetItemText(nItemSel,2);
			_variant_t websit;
			m_pRecordset.CreateInstance("ADODB.Recordset");
			CString strSQL;
			strSQL.Format(_T("SELECT * FROM eBook WHERE 书名='%s' AND 作者='%s'"),str,str1);
			m_pRecordset->Open((LPCTSTR)strSQL,_variant_t((IDispatch*)m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);
			websit=m_pRecordset->GetCollect("网址");
			if (((LPCTSTR)(_bstr_t)websit)==NULL)
			{
				AfxMessageBox(L"您没有收藏它的阅读网址");
				if (IDYES==MessageBox(L"是否继续进行其余操作？",L"提示",MB_YESNO))
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
		AfxMessageBox(L"未连接到目标数据库，请连接数据库");
	}
}
