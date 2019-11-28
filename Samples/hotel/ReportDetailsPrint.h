//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  ReportDetailsPrint.h
// 
// Desc: 打印经营详细表
//
// Author:  邢泉
//
// Modified: 2006年 6月 14日
//--------------------------------------------------------------------------------------

#include "ExcelPrint.h"
#include "HInOutRep.h"
class ReportDetailsPrint : public ExcelPrint
{
public:
	ReportDetailsPrint(string datetimeStart,string datetimeEnd);
	~ReportDetailsPrint();
    
public:
	void SendExcel();

protected:
	string m_dtStart;
	string m_dtEnd;


};