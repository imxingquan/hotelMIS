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
#ifndef HROOM_H_HEADER_INCLUDED_BDA34F4E
#define HROOM_H_HEADER_INCLUDED_BDA34F4E
#include <string>
using namespace std;

namespace hotelMIS{

class HRoom
{
  public:
    HRoom();


    HRoom(int roomId, string roomName, int tableNum);


    void setId(int roomId);

  
    int getId();

  
    void setName(string name);

  
    string getName();

  
    void setTableNum(int tableNum);

  
    int getTableNum();

  public:
    int room_id;
    string room_name;
    int table_num;

};

}

#endif /* HROOM_H_HEADER_INCLUDED_BDA34F4E */
