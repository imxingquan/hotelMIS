/***********************************************************************
 * Module:  HRepast.h
 * Author:  babala
 * Modified: 2005��5��6�� 15:39:10
 * Purpose: Declaration of the class HRepast
 ***********************************************************************/

#if !defined(__hotelMIS_HRepast_h)
#define __hotelMIS_HRepast_h

class HRepast
{
public:
   HRepast();
   ~HRepast();

   /* �˺� */
   string account_id;
   /* ���� */
   int table_id;
   /* �������� */
   string cust_date;
   /* ����ʱ�� */
   string cust_time;
   /* ������ */
   int room_id;
   /* ����״̬
    * 0: ����
    * 1: �Ͳ�
    * 2: Ԥ�� */
   int re_state;

protected:
private:

};

#endif