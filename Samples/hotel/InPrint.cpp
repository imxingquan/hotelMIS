//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  InPrint.cpp
// 
// Desc: ��ӡ��ⵥ
//
// Author:  ��Ȫ
//
// Modified: 2006�� 6�� 12��
//--------------------------------------------------------------------------------------

#include "stdAfx.h"
#include "InPrint.h"
#include "comutil.h"
#include "HAdminBdy.h"

//----------------------------------------------------------------------------------------
InPrint::InPrint(list<hotelMIS::HInOutRep> &list)
{
	m_list = list;
}

//---------------------------------------------------------------------------------------
InPrint::~InPrint()
{

}

//---------------------------------------------------------------------------------------
void InPrint::SendExcel()
{

	list<hotelMIS::HInOutRep>::iterator it = m_list.begin();
	int nRow = 4, nCol = 1;
	CString str;

	float fSum = 0.0f;
	
	//д�븺����
	str.Format("%s",hotelMIS::HAdminBdy::_ad_name.c_str());
	m_rgMyRge.SetItem(_variant_t((long)2),_variant_t((long)2),_variant_t(str)); 
	
	// �˵���
	str.Format("%s",it->inout_dh.c_str());
	m_rgMyRge.SetItem(_variant_t((long)2),_variant_t((long)5),_variant_t(str)); 

	for ( ; it != m_list.end(); it++)
	{
			nCol = 1;
		
			str.Format("A%d",nRow);
			DrawFrame(str);
			str.Format("%d",it->food_id);
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)nCol++),_variant_t(str)); 

			str.Format("B%d",nRow);
			DrawFrame(str);
			str.Format("%s",it->food_name.c_str());
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)nCol++),_variant_t(str)); 
			
			str.Format("C%d",nRow);
			DrawFrame(str);
			str.Format("%.2f",it->food_num);
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)nCol++),_variant_t(str)); 
			
			str.Format("D%d",nRow);
			DrawFrame(str);
			str.Format("%s",it->food_unit.c_str());
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)nCol++),_variant_t(str)); 
			
			str.Format("E%d",nRow);
			DrawFrame(str);
			str.Format("%.2f",it->food_price);
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)nCol++),_variant_t(str)); 
			
			str.Format("F%d",nRow);
			DrawFrame(str);
			str.Format("%.2f",it->food_price * it->food_num);
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)nCol++),_variant_t(str)); 
			
			fSum += it->food_price * it->food_num;

			nRow++;
	}
// ���һ�кϼ�:
			nCol = 1;
			str.Format("A%d",nRow);
			DrawFrame(str);
			str = _T("�ϼ�");
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)nCol++),_variant_t(str)); 

			str.Format("B%d",nRow);
			DrawFrame(str);
			str= _T("-");
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)nCol++),_variant_t(str)); 
			
			str.Format("C%d",nRow);
			DrawFrame(str);
			str= _T("-");
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)nCol++),_variant_t(str)); 
			
			str.Format("D%d",nRow);
			DrawFrame(str);
			str= _T("-");
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)nCol++),_variant_t(str)); 
			
			str.Format("E%d",nRow);
			DrawFrame(str);
			str= _T("-");
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)nCol++),_variant_t(str)); 
			
			str.Format("F%d",nRow);
			DrawFrame(str);
			str.Format("%.2f",fSum);
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)nCol++),_variant_t(str)); 

			nRow++;
			str.Format("%s",_T("�Ʊ�ʱ��"));
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)1),_variant_t(str));
			CTime t = CTime::GetCurrentTime();
			str.Format("%s",t.Format("%Y-%m-%d %H:%M:%S"));
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)2),_variant_t(str));

			str.Format("%s",_T("ǩ��"));
			m_rgMyRge.SetItem(_variant_t((long)nRow),_variant_t((long)4),_variant_t(str));
}
