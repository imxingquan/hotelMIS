/***********************************************************************
 * Module:  HFoodKind.h
 * Author:  babala
 * Modified: 2005Äê4ÔÂ25ÈÕ 0:56:22
 * Purpose: Declaration of the class HFoodKind
 ***********************************************************************/

#if !defined(__hotelMIS_HFoodKind_h)
#define __hotelMIS_HFoodKind_h

class HFoodKind
{
public:
   HFoodKind();
   ~HFoodKind();
   int getKind_id(void);
   void setKind_id(int newKind_id);
   string getKind_name(void);
   void setKind_name(string newKind_name);
   int getKind_flag(void);
   void setKind_flag(int newKind_flag);
   int getKind_ts(void);
   void setKind_ts(int newKind_ts);

protected:
private:
   int kind_id;
   string kind_name;
   int kind_flag;
   int kind_ts;


};

#endif