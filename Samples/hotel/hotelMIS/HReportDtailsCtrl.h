//-----------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
//
// File:  HReportDetailsCtrl.h
// 
// Desc:  ��Ӫ��ϸ����
//
// Author:  xq
// 
// Modified: 2005��6��14�� 6:09
//-----------------------------------------------------------------------
#if !defined(__hotelMIS_HReportDetailsCtrl_h)
#define __hotelMIS_HReportDetailsCtrl
#include "config.h"
#include "HReportDetails.h"

namespace hotelMIS{

typedef vector<HReportDetails> HReportDetailsVec;

class HReportDetailsCtrl
{
public:
	HReportDetailsCtrl(mysqlpp::Connection *pCon);
	~HReportDetailsCtrl();

public:
	vector<HReportDetails> reportDetails(string datetimeStart,string datetimeEnd,int kind_id);	
private:
	mysqlpp::Connection *_pCon;
};

}
#endif