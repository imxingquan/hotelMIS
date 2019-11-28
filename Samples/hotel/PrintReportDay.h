#pragma once
#include "excelprint.h"
#include "HAccountCtrl.h"

class PrintReportDay :
	public ExcelPrint
{
public:
	PrintReportDay(hotelMIS::HAccountVec& vec,string exp,string hotelname,string jsfsMsg);
	~PrintReportDay(void);
	
	void SendExcel();
	float myRound(float x);
protected:
	hotelMIS::HAccountVec m_accVec;

	string m_exp,m_hotelname,m_jsfsMsg;

};
