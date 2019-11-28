// XFDetailsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "XFDetailsDlg.h"

using namespace std;
// CXFDetailsDlg �Ի���

IMPLEMENT_DYNAMIC(CXFDetailsDlg, CDialog)
CXFDetailsDlg::CXFDetailsDlg(CWnd* pParent,CString accountId)
	: CDialog(CXFDetailsDlg::IDD, pParent)
{
	m_accountId = accountId;
}

CXFDetailsDlg::~CXFDetailsDlg()
{
}

void CXFDetailsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_xfDetailsList);
}


BEGIN_MESSAGE_MAP(CXFDetailsDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnBnClickedButtonPrint)
END_MESSAGE_MAP()


// CXFDetailsDlg ��Ϣ�������

BOOL CXFDetailsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString t;
	t.Format(_T("�ʵ���: %s"),m_accountId);
    SetWindowText(t);
	int i = 0;
	m_xfDetailsList.InsertColumn(i,_T("���"),LVCFMT_LEFT,50);
	m_xfDetailsList.InsertColumn(++i,_T("����"),LVCFMT_LEFT,140);
	m_xfDetailsList.InsertColumn(++i,_T("�۸�"),LVCFMT_RIGHT,70);
	m_xfDetailsList.InsertColumn(++i,_T("����"),LVCFMT_LEFT,40);
	m_xfDetailsList.InsertColumn(++i,_T("��λ"),LVCFMT_LEFT,40);
	m_xfDetailsList.InsertColumn(++i,_T("����"),LVCFMT_LEFT,40);
	m_xfDetailsList.InsertColumn(++i,_T("�ۺ��"),LVCFMT_RIGHT,70);

	m_xfDetailsList.InsertColumn(++i,_T("��ʦ"),LVCFMT_LEFT,70);
	ListView_SetExtendedListViewStyleEx(m_xfDetailsList.GetSafeHwnd(), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES , LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	Init();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CXFDetailsDlg::Init()
{
	
	int nPos = -1;
	
		hotelMIS::HAccSearchBdy accSearchBdy;
		hotelMIS::HAccDetailsVec vec = accSearchBdy.searchDetails(m_accountId.GetBuffer());
		hotelMIS::HAccDetailsVec::iterator it ;
		int i = 0,j;
		float p=0.0f,zkprice=0.0f;
		CString t;
		
		for ( it = vec.begin(); it != vec.end(); it++)
		{
			j = 1;
			t.Format("%d",i+1);m_xfDetailsList.InsertItem(i,t);
			m_xfDetailsList.SetItemText(i,j++,it->food_name.c_str());
			t.Format("%.2f",it->food_price);m_xfDetailsList.SetItemText(i,j++,t);
			t.Format("%d",it->food_num);m_xfDetailsList.SetItemText(i,j++,t);
			m_xfDetailsList.SetItemText(i,j++,it->food_unit.c_str());

			t.Format("%.2f",it->zk_num);
			m_xfDetailsList.SetItemText(i,j++,t); //����
			zkprice += it->food_price * it->food_num * it->zk_num;
			t.Format("%.2f", it->food_price * it->food_num * it->zk_num);
			m_xfDetailsList.SetItemText(i,j++,t); //�ۺ��

			m_xfDetailsList.SetItemText(i,j++,it->ck_name.c_str());
			i++;
			p = p+(it->food_price*it->food_num);
		}
		m_xfDetailsList.InsertItem(i,_T("�ϼ�:"));
		//float ys = repDetailsCtrl.getAllPrice(accid);
		t.Format("%.2f",p);
		m_xfDetailsList.SetItemText(i,2,t);
		t.Format("%.2f",zkprice);
		m_xfDetailsList.SetItemText(i,6,t);
	
}



void CXFDetailsDlg::OnBnClickedButtonPrint()
{
	// TODO: ���´�ӡСƱ
	int nPos = -1;
	if ( !m_accountId.IsEmpty()  )
	{
		

		int r = MessageBox(_T("ȷ��Ҫ��ʼ��ӡ?"),_T("����"),MB_ICONWARNING|MB_YESNO);
		if ( r != IDYES)
			return;

		CWinApp* pApp = AfxGetApp();
		CString sPrint = pApp->GetProfileString("Print","PrintBefore");
		HDC hdc = CreateDC(NULL, sPrint, NULL, NULL) ; //������ӡ���
		if ( hdc != NULL){
			CDC dc;
			dc.Attach(hdc);
			DOCINFO di;
			::ZeroMemory(&di,sizeof(DOCINFO));
			di.cbSize = sizeof(DOCINFO);
			di.lpszDocName= _T("�����˵�");

			dc.StartDoc(&di);
			dc.StartPage();
			PrintReport(&dc,m_accountId.GetBuffer());
			dc.EndPage();
			dc.EndDoc();
		}
		else{
			MessageBox(_T("��ӡ������ʧ��!"));
		}
	}
}

void CXFDetailsDlg::PrintReport(CDC *dc,CString accountId)
{
	hotelMIS::HAccSearchBdy m_accSearchBdy;
	hotelMIS::HAccDetailsVec vec = m_accSearchBdy.searchDetails(accountId.GetBuffer());
	hotelMIS::HAccDetailsVec::iterator it ;

	hotelMIS::HAccountCtrl accountCtrl(m_con.get_con());
	hotelMIS::HAccount account = accountCtrl.getAccount(accountId.GetBuffer());

	hotelMIS::HSetHotelPrintMsg s(m_con.get_con());
	hotelMIS::HotelMsg hotelMsg = s.getHotelMsg();

	dc->SetMapMode(MM_LOMETRIC); //����Ϊ���׵�λ
	dc->SetTextAlign(TA_LEFT);

	CWinApp* pApp = AfxGetApp();
	int fontSize = pApp->GetProfileInt("Settings", "PrintFontSize",26);
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	CFont font,*pOldFont;
	font.CreatePointFont(fontSize*10,_T("����"));
	dc->SetTextColor(RGB(0,0,0));
	pOldFont = dc->SelectObject(&font);

	int xPos = pApp->GetProfileInt("Settings", "PrintLeftxPos",30);
	int yPos = pApp->GetProfileInt("Settings", "PrintLeftyPos",15);
	yPos = -yPos;
	int col_2_w = pApp->GetProfileInt("Settings", "PrintCol2w",19);
	int col_3_w = pApp->GetProfileInt("Settings", "PrintCol3w",25);
	int col_4_w = pApp->GetProfileInt("Settings", "PrintCol4w",32);
	int lineHeight = pApp->GetProfileInt("Settings", "PrintLineHeight",8);
	int restline = pApp->GetProfileInt("Settings","PrintRestLine",6);

	CString acc;
	CTime t1=CTime::GetCurrentTime();

	TEXTMETRIC lpMetrics;

	dc->GetTextMetrics(&lpMetrics);
	int fHeight = lpMetrics.tmHeight + lineHeight;
	int n = 2;
	acc.Format("%s",hotelMsg.hotelname.c_str());
	dc->TextOut(xPos,yPos,acc);
	dc->TextOut(xPos,yPos-fHeight,_T("--------------����СƱ----------------"));

	hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
	acc.Format("%s-%d��",roomCtrl.getRoomName(account.room_id).c_str(),account.table_id);
	dc->TextOut(xPos,yPos-fHeight*n++,acc);

	acc.Format("�˵���: %s ",accountId);
	dc->TextOut(xPos,yPos-fHeight*n++,acc);
	acc.Format("����: %d/%d/%d",t1.GetYear(),t1.GetMonth(),t1.GetDay());
	dc->TextOut(xPos,yPos-fHeight*n++,acc);
	dc->TextOut(xPos,yPos-fHeight*5,_T("����"));
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_2_w ,yPos-fHeight*n,_T("����"));
	//dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_3_w,yPos-fHeight*n,_T("����"));
	//dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos + lpMetrics.tmAveCharWidth*col_4_w ,yPos-fHeight*n++,_T("�ܼ�"));

	CString cnt;
	int len = 0;
	for ( it = vec.begin(); it != vec.end(); it++)
	{
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight * n,it->food_name.c_str());			//����

		cnt.Format("%.2f",it->food_price);

		len = it->food_name.length();

		if ( (xPos + len*lpMetrics.tmAveCharWidth) >( xPos+ lpMetrics.tmAveCharWidth*col_2_w- (cnt.GetLength())*lpMetrics.tmAveCharWidth))
			n++;

		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w,yPos-fHeight* n,cnt);		//����
		cnt.Format("%d",it->food_num);
		//dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_3_w-36,yPos-fHeight* n,cnt);	//����
		cnt.Format("%.2f",it->food_price*it->food_num);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos-fHeight* n, cnt);   //�ܼ�

		n++;
	}

	cnt.Format("%.2f",account.yscost);	//Ӧ���˿�
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("�ϼ�:"));
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);

	n++;	
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("---------------------------------------"));


	if ( account.zhekou > 0){
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight*n,_T("��    ��:"));
		cnt.Format("%.1f ",account.zhekou*10);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	}

	if ( account.subscription > 0)
	{
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight*n,_T("Ѻ    ��:"));
		cnt.Format("%.2f",account.subscription);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	}

	if ( account.daijin > 0){
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos-fHeight*n,_T("  ����ȯ:"));
		dc->SetTextAlign(TA_RIGHT);
		cnt.Format("%.2f",account.daijin);
		dc->TextOut(xPos+lpMetrics.tmAveCharWidth*col_4_w,yPos - fHeight*n,cnt);
	}

	if ( account.erase_zero >0){
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos-fHeight*n,_T("������:"));
		dc->SetTextAlign(TA_RIGHT);
		cnt.Format("%.2f",account.erase_zero);
		dc->TextOut(xPos+lpMetrics.tmAveCharWidth*col_4_w,yPos - fHeight*n,cnt);
	}

	n++;
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("������:"));
	cnt.Format("%.2f",account.sscost);
	dc->SetTextAlign(TA_RIGHT);
	dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);


	dc->SetTextAlign(TA_LEFT);
	if(account.sj > 0)
	{
		n++;
		dc->TextOut(xPos,yPos - fHeight*n,_T("�ֽ�֧��:"));
		cnt.Format("%.2f",account.sj);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	}

	dc->SetTextAlign(TA_LEFT);
	if(account.zfprice >0)
	{
		n++;
		if ( account.paystatus == hotelMIS::HAccount::JSFS::mcard)
		{
			dc->TextOut(xPos,yPos - fHeight*n,_T("��Ա��֧��:"));
			cnt.Format("%.2f",account.zfprice);
			dc->SetTextAlign(TA_RIGHT);
			dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
		}
		else if(account.paystatus == hotelMIS::HAccount::JSFS::xycard)
		{
			dc->TextOut(xPos,yPos - fHeight*n,_T("���ÿ�֧��:"));
			cnt.Format("%.2f",account.zfprice);
			dc->SetTextAlign(TA_RIGHT);
			dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
		}
		else if(account.paystatus == hotelMIS::HAccount::JSFS::zp)
		{
			dc->TextOut(xPos,yPos - fHeight*n,_T("֧Ʊ֧��:"));
			cnt.Format("%.2f",account.zfprice);
			dc->SetTextAlign(TA_RIGHT);
			dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
		}
	}


	if ( account.zy >=0){
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight*n,_T("��    ��:"));
		cnt.Format("%.2f",account.zy);
		dc->SetTextAlign(TA_RIGHT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_4_w,yPos -fHeight*n,cnt);
	}

	if (!account.bz.empty())
	{
		n++;
		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos,yPos - fHeight*n,_T("��ע: "));

		dc->SetTextAlign(TA_LEFT);
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth+90,yPos -fHeight*n,account.bz.c_str());

	}

	n++;
	dc->SetTextAlign(TA_LEFT);
	dc->TextOut(xPos,yPos - fHeight*n,_T("---------------------------------------"));

	if ( ! hotelMsg.hoteltel.empty() ){
		n++;
		dc->TextOut(xPos,yPos - fHeight*n,_T("���͵绰:"));
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w-100,yPos -fHeight*n,hotelMsg.hoteltel.c_str());
	}
	if ( ! hotelMsg.hoteltel2.empty() && ! hotelMsg.hoteltel.empty()){
		n++;
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w-100,yPos -fHeight*n,hotelMsg.hoteltel2.c_str());
	}
	if ( !hotelMsg.hotelhttp.empty()){
		n++;
		dc->TextOut(xPos,yPos - fHeight*n,_T("������ַ:"));
		dc->TextOut(xPos+ lpMetrics.tmAveCharWidth*col_2_w-100,yPos -fHeight*n,hotelMsg.hotelhttp.c_str());
	}

	//print space line
	n = n+restline;
	dc->TextOut(xPos,yPos-fHeight*n,_T("-"));
	dc->SelectObject(&pOldFont);
}

