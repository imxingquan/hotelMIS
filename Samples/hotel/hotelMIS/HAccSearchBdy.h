//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HAccSearchBdy.h
//
// Description:    
//			ʵ���˵���ϸ��Ĳ���	
//			
//		
//
// Version: 1.0
//
// Hostory:		
//			05-6-2005	��Ȫ	Created	
//			
//---------------------------------------------------------
#if !defined(__hotelMIS_HAccSearchBdy_h)
#define __hotelMIS_HAccSearchBdy_h

//#include <HAccount.h>
#include <HAccDetailsCtrl.h>
#include <HAccountCtrl.h>
#include <KDBCon.h>
#include <string>

using namespace std;

namespace hotelMIS{

	/*---------------------------------------------------------------------
	* class HAccSearchBdy
	*	member function
	*		
	*		//��ѯָ��������ĳ���Ͳ�״̬���˵���ϸ
	*		search(string sDate,string eDate,int accStatus)
	*			parameters:
	*				- sDate	string	
	*				- eDate string
	*				- accStatus	int
	*
	*			return HAccountVec
	*
	*----------------------------------------------------------------------*/
	class HAccSearchBdy
	{
	public:
		//Construct /Destruct
		HAccSearchBdy();
		~HAccSearchBdy();
		
		HAccountVec search(string sDate, string eDate, int accStatus,int arid=0,int cw=0,int jsfs=0);
		HAccount search(string accid);
		HAccDetailsVec searchDetails(string accid);

	private:
		hotelMIS::HAccountCtrl* pAccCtrl;
		hotelMIS::HAccDetailsCtrl* pAccDetailsCtrl;
		hotelMIS::KDBCon m_con;

	};
}
#endif