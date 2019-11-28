/***********************************************************************
 * Module:  HChgTableBdy.h
 * Author:  babala
 * Modified: 2005Äê5ÔÂ16ÈÕ 9:13:59
 * Purpose: Declaration of the class HChgTableBdy
 ***********************************************************************/

#if !defined(__hotelMIS_HChgTableBdy_h)
#define __hotelMIS_HChgTableBdy_h

class HChgTableBdy
{
public:
   HChgTableBdy(int table_id, int room_id);
   ~HChgTableBdy();
   TableCol getEmptyTable(void);

protected:
private:
   int talbeId;
   int roomId;
   hotelMIS::KDBCon m_con;
   hotelMIS::HTableStatusCtrl* pTableStatusCtrl;


};

#endif