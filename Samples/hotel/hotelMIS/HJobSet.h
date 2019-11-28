/***********************************************************************
* Module:  HJobSet.h
* Author:  babala
* Modified: 2005年4月23日 17:12:10
* Purpose: Declaration of the class HJobSet
***********************************************************************/
/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985
Email: support@idcwest.net
Description: 
		
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#if !defined(__hotelMIS_HJobSet_h)
#define __hotelMIS_HJobSet_h
#include <string>
#include <vector>
using namespace std;
namespace hotelMIS{
	
	class HJobSet
	{
	public:
		HJobSet();
		~HJobSet();
		int getJob_id(void);
		void setJob_id(int newJob_id);
		string getJob_name(void);
		void setJob_name(string newJob_name);

	protected:
	private:
		int job_id;
		string job_name;


	};
	typedef vector<HJobSet> HJobSetVec;
}
#endif