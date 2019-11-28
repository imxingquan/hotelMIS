/***********************************************************************
 * Module:  HJobSet.h
 * Author:  babala
 * Modified: 2005Äê4ÔÂ23ÈÕ 17:12:10
 * Purpose: Declaration of the class HJobSet
 ***********************************************************************/

#if !defined(__hotelMIS_HJobSet_h)
#define __hotelMIS_HJobSet_h

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

#endif