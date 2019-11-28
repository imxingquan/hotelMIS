/***********************************************************************
 * Module:  HAdmin.h
 * Author:  babala
 * Modified: 2005Äê4ÔÂ15ÈÕ 9:57:44
 * Purpose: Declaration of the class HAdmin
 ***********************************************************************/

#if !defined(__hotelMIS_HAdmin_h)
#define __hotelMIS_HAdmin_h

namespace hotelMIS {

class HAdmin
{
public:
   int get_id(void);
   void set_id(int new_id);
   string get_login_id(void);
   void set_login_id(string new_login_id);
   string get_name(void);
   void set_name(string new_name);
   string get_opType(void);
   void set_opType(string new_opType);
   string get_password(void);
   void set_password(string new_password);
   string get_desc(void);
   void set_desc(string new_desc);

protected:
private:
   int _id;
   string _login_id;
   string _name;
   string _opType;
   string _password;
   string _desc;


};

}

#endif