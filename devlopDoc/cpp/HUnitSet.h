/***********************************************************************
 * Module:  HUnitSet.h
 * Author:  babala
 * Modified: 2005��4��23�� 8:24:13
 * Purpose: Declaration of the class HUnitSet
 * Comment: ��λ����
 ***********************************************************************/

#if !defined(__hotelMIS_HUnitSet_h)
#define __hotelMIS_HUnitSet_h

class HUnitSet
{
public:
   HUnitSet();
   ~HUnitSet();
   int getUnit_id(void);
   void setUnit_id(int newUnit_id);
   string getUnit_name(void);
   void setUnit_name(string newUnit_name);

protected:
private:
   int unit_id;
   string unit_name;


};

#endif