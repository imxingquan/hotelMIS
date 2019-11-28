/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#ifndef HOPTYPE_H_HEADER_INCLUDED_BDA4CBEF
#define HOPTYPE_H_HEADER_INCLUDED_BDA4CBEF
#include "config.h"
#include "HAdmin.h"
namespace hotelMIS{
	typedef vector<string> purviewList;
	class HOpType
	{
	public:
		
		HOpType(string opType,mysqlpp::Connection* pConn);
		HOpType(mysqlpp::Connection* pConn);
		//餐饮管理
		void setM0(int op = 0);
		int getM0();
		
		//库存管理
		void setM1(int op = 0);
		int getM1();

		//账单查询
		void setM2(int op = 0);
		int getM2();

		//人员管理
		void setM3(int op = 0);
		int getM3();

		//菜谱管理
		void setM4(int op = 0);
		int getM4();

		//报表设置
		void setM5(int op = 0);
		int getM5();

		//系统设置
		void setM6(int op = 0);

		int getM6();

		//其它功能
		void setM7(int ip = 0);
		int getM7();

		//会员管理
		void setM8(int op = 0);
		int getM8();

		void addPurview();
		void delPurview();
		//返回所有权限列表
		vector<string> getAllPurview();
		bool isExist(const string& optype);
	private:
		void setQx(int op, const string& moduleNo);
		int getQx(const string& moduleNo);
		int _id;
		mysqlpp::Connection* _pConn;
		string _opType;

	};

}

#endif /* HOPTYPE_H_HEADER_INCLUDED_BDA4CBEF */
