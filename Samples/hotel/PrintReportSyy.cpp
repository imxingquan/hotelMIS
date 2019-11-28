#include "stdafx.h"
#include ".\printreportsyy.h"
#include "HRoomCtrl.h"
#include "HAccDetailsCtrl.h"
#include "comutil.h"
#include "HAdminBdy.h"
#include <math.h>
PrintReportSyy::PrintReportSyy(hotelMIS::HAccountVec vec,string acc_status,string exp,string hotelname,string dwmc,int jsfs)
{
	m_vec = vec;
	m_acc_status = acc_status;
	m_exp = exp;
	m_hotelname = hotelname;
	m_dwmc = dwmc;
	switch(jsfs)
	{
	
	case 1:
		m_jsfs = "现金";
		break;
	case 2:
		m_jsfs="会员卡";
		break;
	case 3:
		m_jsfs="信用卡";
		break;
	case 4:
		m_jsfs="支  票";
		break;
	case 5:
		m_jsfs="代金券";
		break;
	default:
		m_jsfs="";
		break;

	}
}

PrintReportSyy::~PrintReportSyy(void)
{
}

void PrintReportSyy::SendExcel()
{
	TRY{
		if (m_ExcelApp.m_lpDispatch == NULL)
			return;

		CString str;
		str.Format("%s 分类统计报表【%s 消费单位:%s】",m_hotelname.c_str(),m_acc_status.c_str(),m_dwmc.c_str());
		m_rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)4),_variant_t(str)); 
		//写入制表人

		str.Format("%s",hotelMIS::HAdminBdy::_ad_name.c_str());
		m_rgMyRge.SetItem(_variant_t((long)2),_variant_t((long)12),_variant_t(str)); 

		//写入统计日期
		m_rgMyRge.SetItem(_variant_t((long)2),_variant_t((long)2),_variant_t(m_exp.c_str())); 

		//写入结算方式
		m_rgMyRge.SetItem(_variant_t((long)2),_variant_t((long)15),_variant_t(m_jsfs.c_str())); 

		int i = 4,j=1;

		CString t;
		hotelMIS::HRoomCtrl roomCtrl(m_con.get_con());
		hotelMIS::HAccDetailsCtrl accDetailsCtrl(m_con.get_con());
		hotelMIS::HAccDetailsVec detailsVec;
		hotelMIS::HAccDetailsVec::iterator detailsIt;

		hotelMIS::HAccountVec::iterator it;

		float shiwu_total=0.0f;
		float yingliao_total=0.0f;
		float jiulei_total=0.0f;
		float xiangyan_total=0.0f;
		float tea_total = 0.0f;			//茶合计
		float zaxiang_total=0.0f;
		float fuwufei_total=0.0f;
		float zongji_total=0.0f;

		float xj_total = 0.0f;
		float dj_total = 0.0f;
		float mc_total = 0.0f;
		float xyk_total = 0.0f;
		float zp_total = 0.0f;
		float ml_total = 0.0f;			//抹零合计
		float yscost_total=0.0f;		//应收总计
		float yh_total =0.0f;			//优惠总计

		for ( it = m_vec.begin(); it != m_vec.end(); it++)
		{	
			j = 1;

			float shiwu=0.0f;
			float yingliao=0.0f;
			float jiulei=0.0f;
			float xiangyan=0.0f;
			float tea=0.0f;				//茶
			float zaxiang=0.0f;
			float fuwufei=0.0f;
			float zongji=0.0f;

			//帐单号
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(it->account_id.c_str())); 
			//桌号		
			t.Format("%s-%d号",roomCtrl.getRoomName(it->room_id).c_str(),it->table_id);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));  

			t.Format("%.2f",it->yscost);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));  

			yscost_total += it->yscost; //应收账款合计

			detailsVec = accDetailsCtrl.getAccDetails(it->account_id);
			for(detailsIt = detailsVec.begin(); detailsIt != detailsVec.end(); detailsIt++)
			{			

				if (detailsIt->total_fl== 1)
				{
					shiwu+=detailsIt->food_price * detailsIt->food_num * detailsIt->zk_num;

				}
				else if(detailsIt->total_fl==  2)
				{
					yingliao+=detailsIt->food_price * detailsIt->food_num * detailsIt->zk_num;

				}
				else if(detailsIt->total_fl== 3)
				{
					jiulei+=detailsIt->food_price * detailsIt->food_num * detailsIt->zk_num;

				}
				else if(detailsIt->total_fl == 4)
				{
					xiangyan+=detailsIt->food_price * detailsIt->food_num * detailsIt->zk_num;

				}
				else if(detailsIt->total_fl== 5)
				{
					zaxiang+=detailsIt->food_price * detailsIt->food_num * detailsIt->zk_num;

				}
				else if(detailsIt->total_fl== 6)
				{
					fuwufei+=detailsIt->food_price * detailsIt->food_num * detailsIt->zk_num;

				}else if(detailsIt->total_fl== 7)
				{
					tea+=detailsIt->food_price * detailsIt->food_num * detailsIt->zk_num;

				}



			}
			if(it->sswr==1)
			{
				shiwu = myRound(shiwu);
				yingliao = myRound(yingliao);
				jiulei = myRound(jiulei);
				xiangyan = myRound(xiangyan);
				tea = myRound(tea);
				zaxiang = myRound(zaxiang);
				fuwufei = myRound(fuwufei);

			}
			zongji += shiwu+yingliao+jiulei+xiangyan+tea+zaxiang+fuwufei;
			shiwu_total += shiwu;
			yingliao_total += yingliao;
			jiulei_total+= jiulei;
			tea_total += tea;
			xiangyan_total+= xiangyan;
			zaxiang_total+=zaxiang;
			fuwufei_total+= fuwufei;
			zongji_total += zongji;
			//食物
			t.Format("%.2f",shiwu);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
			//饮料
			t.Format("%.2f",yingliao);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
			//酒类
			t.Format("%.2f",jiulei);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
			//香烟
			t.Format("%.2f",xiangyan);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
			//茶
			t.Format("%.2f",tea);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
			//杂项
			t.Format("%.2f",zaxiang);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
			//服务费
			t.Format("%.2f",fuwufei);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
			//总计
			t.Format("%.2f",zongji);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));

			t.Format("%.2f",it->yscost-zongji);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
			yh_total += it->yscost-zongji; //优惠总计

			//现金=现金支付-找余-抹零
			float xj = it->sj - it->zy;
			if ( it->sswr == 1) xj = myRound(xj);
			xj_total += xj;
			t.Format("%.2f",xj);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
			//代金券
			dj_total += it->daijin;
			t.Format("%.2f",it->daijin);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));


			if ( it->paystatus== hotelMIS::HAccount::JSFS::mcard) //会员卡
			{	
				mc_total += it->zfprice;
				t.Format("%.2f",it->zfprice);
				m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
			}
			else
				m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(_T("0.0")));

			if ( it->paystatus== hotelMIS::HAccount::JSFS::xycard) //信用卡
			{	
				xyk_total += it->zfprice;
				t.Format("%.2f",it->zfprice);
				m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
			}
			else
				m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(_T("0.0")));

			if ( it->paystatus== hotelMIS::HAccount::JSFS::zp) //支票
			{	
				zp_total += it->zfprice;
				t.Format("%.2f",it->zfprice);
				m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
			}
			else
				m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(_T("0.0")));

			ml_total += it->erase_zero;
			t.Format("%.2f",it->erase_zero);
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
			//备注
			m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(it->bz.c_str()));

			i++;
		}

		j=3;
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)1),_variant_t(_T("  合  计  ")));
		//应收账款合计
		t.Format("%.2f",yscost_total);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
		//食物
		t.Format("%.2f",shiwu_total);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
		//饮料
		t.Format("%.2f",yingliao_total);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
		//酒类
		t.Format("%.2f",jiulei_total);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
		//香烟
		t.Format("%.2f",xiangyan_total);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
		//茶
		t.Format("%.2f",tea_total);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
		//杂项
		t.Format("%.2f",zaxiang_total);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
		//服务费
		t.Format("%.2f",fuwufei_total);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
		//总计
		t.Format("%.2f",zongji_total);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
		//优惠总计
		t.Format("%.2f",yh_total);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
		
		//现金
		t.Format("%.2f",xj_total);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
		//代金券
		t.Format("%.2f",dj_total);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
		//会员卡
		t.Format("%.2f",mc_total);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
		//信用卡
		t.Format("%.2f",xyk_total);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
		//支票
		t.Format("%.2f",zp_total);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
		//抹零
		t.Format("%.2f",ml_total);
		m_rgMyRge.SetItem(_variant_t((long)i),_variant_t((long)j++),_variant_t(t));
		
		DrawLine(i,j,4,0);

	}
	CATCH(CException,e)
	{
		e->ReportError();
		Close();
	}
	END_CATCH
}

float PrintReportSyy::myRound(float x)
{
	if((int)x*10+5 > (int)(x*10))
		return floor(x);
	else
		return ceil(x);
}