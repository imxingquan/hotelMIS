//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  ReportDetailsPrint.h
// 
// Desc: ��ӡ��Ӫ��ϸ��
//
// Author:  ��Ȫ
//
// Modified: 2006�� 6�� 14��
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