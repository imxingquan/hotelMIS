//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  ReportDetailsPrint.cpp
// 
// Desc: 打印经营详细表
//
// Author:  邢泉
//
// Modified: 2006年 6月 14日
//--------------------------------------------------------------------------------------
#include "stdAfx.h"
#include "ReportDetailsPrint.h"
#include "comutil.h"
#include "KDBCon.h"
#include "HReportDtailsCtrl.h"
#include "HFoodKindCtrl.h"
#include "HAdminBdy.h"

//--------------------------------------------------------------------------------------
ReportDetailsPrint::ReportDetailsPrint(string datetimeStart,string datetimeEnd)
{
	m_dtStart = datetimeStart;
	m_dtEnd = datetimeEnd;
}

//---------------------------------------------------------------------------------------
ReportDetailsPrint::~ReportDetailsPrint()
{

}

//----------------------------------------------------------------------------------------
void ReportDetailsPrint::SendExcel()
{
	
	hotelMIS::KDBCon m_con;

	hotelMIS::HReportDetailsCtrl repDetailsCtrl(m_con.get_con());
	
	hotelMIS::HFoodKindCtrl kindCtrl(m_con.get_con());
	
	hotelMIS::HFoodKindVec kindVec = kindCtrl.getAllKind();
	hotelMIS::HFoodKindVec::iterator it ;
	
	hotelMIS::HReportDetailsVec::iterator it2;
	hotelMIS::HReportDetailsVec vec;

	int nRow = 4, j = 1;

		
	float uSum = 0.0f;
	float aSum = 0.0f;
	
	CString str;

	//写入制表人
	str.Format("%s",hotelMIS::HAdminBdy::_ad_name.c_str());
	m_rgMyRge.SetItem(_variant_t((long)2),_variant_t((long)2),_variant_t(str)); 
	//写入统计日期
	str.Format(_T("%s 至 %s"),m_dtStart.c_str(),m_dtEnd.c_str());
	m_rgMyRge.SetItem(_variant_t((long)2),_variant_t((long)4),_variant_t(str)); 
	for ( it = kindVec.begin(); it != kindVec.end(); it++)
	{
		if ( it->kind_id == hotelMIS::HFoodKind::HOUCHU_FLAG){
			continue;
		}
		
		vec = repDetailsCtrl.reportDetails(m_dtStart,m_dtEnd,it->kind_id);
		if ( !vec.empty() )
		{
			str.Format("A%d",nRow);
			DrawFrame(str);
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)1),_variant_t(_T("类名"))); 
			
			str.Format("B%d",nRow);
			DrawFrame(str);
			str.Format("%s",it->kind_name.c_str());
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)2),_variant_t(str)); 

			str.Format("C%d",nRow);
			DrawFrame(str);
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)3),_variant_t(_T(""))); 

			str.Format("D%d",nRow);
			DrawFrame(str);
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)4),_variant_t(_T(""))); 
			
			str.Format("E%d",nRow);
			DrawFrame(str);
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)5),_variant_t(_T(""))); 

			nRow++;
			uSum = 0.0f;
			for ( it2 = vec.begin(); it2 != vec.end(); it2++)
			{
				j = 1;
				
				str.Format("A%d",nRow);
				DrawFrame(str);
				str.Format("%d",it2->food_id);
				//m_list.InsertItem(nRow,t);
				m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)j),_variant_t(str));

				str.Format("B%d",nRow);
				DrawFrame(str);
				str.Format("%s",it2->food_name.c_str());
				//m_list.SetItemText(nRow,j++,it2->food_name.c_str());
				m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)++j),_variant_t(str));

				str.Format("C%d",nRow);
				DrawFrame(str);
				str.Format("%.2f",it2->sum_num);
				//m_list.SetItemText(nRow,j++,t);
				m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)++j),_variant_t(str));
				
				str.Format("D%d",nRow);
				DrawFrame(str);
				str.Format("%s",it2->food_unit.c_str());
				//m_list.SetItemText(nRow,j++,it2->food_unit.c_str());
				m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)++j),_variant_t(str));

				str.Format("E%d",nRow);
				DrawFrame(str);
				str.Format("%.2f",it2->sum_price);
				//m_list.SetItemText(nRow,j++,t);
				m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)++j),_variant_t(str));

				uSum += it2->sum_price;

				nRow++;
			}
						
			if ( uSum != 0){
				
				//m_list.InsertItem(nRow,_T("合计:"));
				str.Format("A%d",nRow);
				DrawFrame(str);
				m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)1),_variant_t(_T("合计:")));
				str.Format("B%d",nRow);
				DrawFrame(str);
				m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)2),_variant_t(_T("-")));
				str.Format("C%d",nRow);
				DrawFrame(str);
				m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)3),_variant_t(_T("-")));
				str.Format("D%d",nRow);
				DrawFrame(str);
				m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)4),_variant_t(_T("-")));
				
				str.Format("E%d",nRow);
				DrawFrame(str);
				//m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)5),_variant_t(str));
				
				str.Format("%.2f",uSum);
				m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)5),_variant_t(str));
				nRow++;
			}
			//m_list.InsertItem(nRow++,_T("")); //空行
			nRow++;
			aSum += uSum;
		}
	}	
	
	if ( aSum != 0){
		
		str.Format("A%d",nRow);
		DrawFrame(str);
		m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)1),_variant_t(_T("总合计:")));

		str.Format("B%d",nRow);
		DrawFrame(str);
		m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)2),_variant_t(_T("-")));

		str.Format("C%d",nRow);
		DrawFrame(str);
		m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)3),_variant_t(_T("-")));

		str.Format("D%d",nRow);
		DrawFrame(str);
		m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)4),_variant_t(_T("-")));

		str.Format("E%d",nRow);
		DrawFrame(str);
		
		str.Format("%.2f",aSum);
		m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)5),_variant_t(str));
	}
}