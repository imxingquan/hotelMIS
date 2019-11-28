#pragma once
#include "excelprint.h"
#include "HAccountCtrl.h"
#include "HAccount.h"
#include "KDBCon.h"

class PrintReportSyy :
	public ExcelPrint
{
public:
	PrintReportSyy(hotelMIS::HAccountVec vec,string acc_status,string exp,string hotelname,string dwmc,int jsfs);
	~PrintReportSyy(void);

	void SendExcel();

	float myRound(float x);
protected:
	hotelMIS::KDBCon m_con;
	hotelMIS::HAccountVec m_vec;
	string m_exp,m_hotelname;
	string m_acc_status;
	string m_dwmc;
	string m_jsfs;
};
