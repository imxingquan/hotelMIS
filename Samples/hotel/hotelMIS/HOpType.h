/*--
Company: �����������缼�����޹�˾
Author: ��Ȫ QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	��Ȫ    04/23/05	v1.2 
	��Ȫ	08/28/05	v1.3 

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
		//��������
		void setM0(int op = 0);
		int getM0();
		
		//������
		void setM1(int op = 0);
		int getM1();

		//�˵���ѯ
		void setM2(int op = 0);
		int getM2();

		//��Ա����
		void setM3(int op = 0);
		int getM3();

		//���׹���
		void setM4(int op = 0);
		int getM4();

		//��������
		void setM5(int op = 0);
		int getM5();

		//ϵͳ����
		void setM6(int op = 0);

		int getM6();

		//��������
		void setM7(int ip = 0);
		int getM7();

		//��Ա����
		void setM8(int op = 0);
		int getM8();

		void addPurview();
		void delPurview();
		//��������Ȩ���б�
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
