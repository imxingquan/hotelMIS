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
#ifndef HROOMCTRL_H_HEADER_INCLUDED_BDA2D260
#define HROOMCTRL_H_HEADER_INCLUDED_BDA2D260
#include "HRoom.h"
#include "config.h"
#include <string>
#include <vector>
using namespace std;

namespace hotelMIS{
typedef vector<HRoom> HRoomVector;
class HRoomCtrl
{
  public:
    HRoomCtrl(mysqlpp::Connection *pCon );

    int insertRoom(int roomid,string name,int tableNum);

    void updateRoom(HRoom &room);

    void deleteRoom(int id);

    vector<HRoom> getAllRoom();
	
	HRoom getRoom(int roomId);
	
	int	  getRoomCount()const;

	bool isExistRoom(int roomid);
	
	int getRoomMax();

	string getRoomName(int roomId);
  private:
   
	
    mysqlpp::Connection *_pCon;

};

}

#endif /* HROOMCTRL_H_HEADER_INCLUDED_BDA2D260 */
