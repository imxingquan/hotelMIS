#include "stdafx.h"
#include ".\printreportday.h"
#include "HAdminBdy.h"
#include "comutil.h"
#include <math.h>

PrintReportDay::PrintReportDay(hotelMIS::HAccountVec& vec,string exp,string hotelname,string jsfsMsg)
{
	m_accVec = vec;
	m_exp = exp;
	m_hotelname = hotelname;
	m_jsfsMsg = jsfsMsg;
}

PrintReportDay::~PrintReportDay(void)
{
}


void PrintReportDay::SendExcel()
{
	TRY{
		if (m_ExcelApp.m_lpDispatch == NULL)
			return;
		CString str;
		str.Format("%s ��Ӫ�ձ��� %s",m_hotelname.c_str(),m_jsfsMsg.c_str());
		m_rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)4),_variant_t(str)); 
		//д���Ʊ���

		str.Format("%s",hotelMIS::HAdminBdy::_ad_name.c_str());
		m_rgMyRge.SetItem(_variant_t((long)2),_variant_t((long)10),_variant_t(str)); 
		//д��ͳ������

		m_rgMyRge.SetItem(_variant_t((long)2),_variant_t((long)2),_variant_t(m_exp.c_str())); 


		hotelMIS::HAccountVec::iterator it ;


		int j=0;
		float sum_sscost = 0.0f;
		float sum_ys =0.0f;
		float sum_subscription = 0.0f;
		float sum_mcard = 0.0f,sum_xj = 0.0f,sum_xycard=0.0f,sum_zp=0.0f,sum_daiji=0.0f;

		int i = 4; //�ӵ����п�ʼ
		CString t;

		for ( it = m_accVec.begin(); it != m_accVec.end(); it++)
		{
			j = 1;

			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(it->account_id.c_str()));  //�ʵ���

			t.Format("%.2f",it->yscost);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));  //�ʵ���

			t.Format("%.2f",it->zhekou);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));//�ۿ�
			t.Format("%.2f",it->erase_zero);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));//Ĩ��
			float ss = it->sscost+it->erase_zero+it->subscription+it->daijin;
			if ( it->sswr == 1) ss = myRound(ss);
			t.Format("%.2f",ss);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t)); //ʵ���˿�

			t.Format("%.2f",it->subscription);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t)); //����
			t.Format("%.2f",(it->sswr==1 ? myRound(it->sj-it->zy):it->sj-it->zy));
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t)); //�ֽ�
			t.Format("%.2f",it->daijin);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t)); //����

			if ( it->paystatus== hotelMIS::HAccount::JSFS::mcard) //��Ա��
			{	
				sum_mcard += it->zfprice;
				t.Format("%.2f",it->zfprice);
				m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
			}
			else
				m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(_T("0.00")));

			if ( it->paystatus== hotelMIS::HAccount::JSFS::xycard) //���ÿ�
			{	
				sum_xycard += it->zfprice;
				t.Format("%.2f",it->zfprice);
				m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
			}
			else
				m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(_T("0.00")));

			if ( it->paystatus== hotelMIS::HAccount::JSFS::zp) //֧Ʊ
			{	
				sum_zp += it->zfprice;
				t.Format("%.2f",it->zfprice);
				m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
			}
			else
				m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(_T("0.00")));

			//m_GuiListCtrlReporyDay.SetItemText(i,j++,it->bz.c_str()); //��ע
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(it->bz.c_str()));

			sum_sscost += it->sscost+it->erase_zero+it->subscription+it->daijin;
			sum_ys += it->yscost;
			sum_daiji += it->daijin;
			sum_xj += it->sj-it->zy;
			sum_subscription += it->subscription;
			i++;
		}

		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)1),_variant_t(_T("  ��  ��  ")));

		//Ӧ���˿�
		t.Format("%.2f",sum_ys);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)2),_variant_t(t));


		//�ϼ�
		t.Format("%.2f",sum_sscost);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)5),_variant_t(t));

		//����
		t.Format("%.2f",sum_subscription);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)6),_variant_t(t));

		//�ֽ�
		t.Format("%.2f",sum_xj);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)7),_variant_t(t));

		//����ϼ�
		t.Format("%.2f",sum_daiji);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)8),_variant_t(t));


		//��Ա��
		t.Format("%.2f",sum_mcard);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)9),_variant_t(t));

		//���ÿ�
		t.Format("%.2f",sum_xycard);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)10),_variant_t(t));

		//֧Ʊ
		t.Format("%.2f",sum_zp);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)11),_variant_t(t));

		/*for ( int row=4;row<=i;row++)
		{
		for ( int col=0;col<j-1;col++)
		{
		t.Format("%c%d",c+col,row);
		DrawFrame(t);
		}
		}*/

		DrawLine(i,j-1,4,0);

	}
	CATCH(CException,e)
	{
		e->ReportError();
		Close();
	}
	END_CATCH
}

float PrintReportDay::myRound(float x)
{
	if((int)x*10+5 > (int)(x*10))
		return floor(x);
	else
		return ceil(x);
}