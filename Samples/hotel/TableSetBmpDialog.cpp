// TableSetBmpDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "TableSetBmpDialog.h"
#include ".\tablesetbmpdialog.h"
#include "KProfile.h"

// CTableSetBmpDialog 对话框

IMPLEMENT_DYNAMIC(CTableSetBmpDialog, CDialog)
CTableSetBmpDialog::CTableSetBmpDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTableSetBmpDialog::IDD, pParent)
{
	m_nPos = -1;
}

CTableSetBmpDialog::~CTableSetBmpDialog()
{
}

void CTableSetBmpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EMPTY_TABLE_LIST, m_GuiTableImageList);

	DDX_Control(pDX, IDOK, m_GuiOkButton);
}


BEGIN_MESSAGE_MAP(CTableSetBmpDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_EMPTY_TABLE_LIST, OnNMClickEmptyTableList)
END_MESSAGE_MAP()


// CTableSetBmpDialog 消息处理程序

BOOL CTableSetBmpDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_GuiOkButton.EnableWindow(false);
	Init();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTableSetBmpDialog::OnBnClickedOk()
{	
	OnOK();
}

void CTableSetBmpDialog::Init()
{
	hotelMIS::KProfile file("set.ini");
	CString t;
	t.Format("%s",file.GetProfile("SYS_SET","imagenum","12").c_str());
		
	HBITMAP hbitmap = (HBITMAP)LoadImage(NULL,"res/table.bmp",IMAGE_BITMAP,0,0,
    /*LR_CREATEDIBSECTION|*/LR_DEFAULTSIZE|LR_LOADFROMFILE);
	m_bitmap.Attach(hbitmap);

	int num = static_cast<int>(atoi(t));
	m_ImageList.Create(64, 64, TRUE | ILC_COLOR24, num, 0); 
	m_ImageList.Add(&m_bitmap,RGB(255,255,255));
	
	m_GuiTableImageList.SetImageList(&m_ImageList,LVSIL_NORMAL);
	m_GuiTableImageList.ModifyStyle(LVS_TYPEMASK,LVS_ICON);
	
	

	LV_ITEM lvi;
	
	for ( int i = 0; i < num; i+=2)
	{
		lvi.iItem = i;
		lvi.iSubItem = 0;
		//szText.Format("%d号",it->table_id);
		lvi.iImage = i;
		lvi.pszText = "";	//根据当前就餐状态设置不同文字
		lvi.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
		m_GuiTableImageList.InsertItem(&lvi);
	}
}
void CTableSetBmpDialog::OnNMClickEmptyTableList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	DWORD dwPos = ::GetMessagePos();
	CPoint point((int)LOWORD(dwPos),(int)HIWORD(dwPos));
	m_GuiTableImageList.ScreenToClient(&point);

	if (( m_nPos= m_GuiTableImageList.HitTest(point)) != -1 ) {
		m_GuiOkButton.EnableWindow(true);	
	}
	else{
		m_GuiOkButton.EnableWindow(false);	
	}

	
}
