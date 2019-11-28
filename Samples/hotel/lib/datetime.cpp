#define MYSQLPP_NOT_HEADER
#include "stdafx.h"

#include "platform.h"

#include "datetime.h"

#include <iomanip>

using namespace std;

namespace mysqlpp {

ostream& mysql_date::out_stream(ostream& s) const
{
	char fill = s.fill('0');
	ios::fmtflags flags = s.setf(ios::right);
	s << setw(4) << year << '-' 
			<< setw(2) << month << '-'
			<< setw(2) << day;
	s.flags(flags);
	s.fill(fill);
	return s;
}

ostream& mysql_time::out_stream(ostream& s) const
{
	char fill = s.fill('0');
	ios::fmtflags flags = s.setf(ios::right);
	s << setw(2) << hour << ':' 
			<< setw(2) << minute << ':'
			<< setw(2) << second;
	s.flags(flags);
	s.fill(fill);
	return s;
}

ostream& DateTime::out_stream (ostream& s) const
{
	mysql_date::out_stream(s);
	s << " ";
	mysql_time::out_stream(s);
	return s;
}

cchar* mysql_date::convert(cchar* str)
{
	char num[5];

	num[0] = *str++;
	num[1] = *str++;
	num[2] = *str++;
	num[3] = *str++;
	num[4] = 0;
	year = short(strtol(num, 0, 10));
	if (*str == '-') str++;

	num[0] = *str++;
	num[1] = *str++;
	num[2] = 0;
	month = short(strtol(num, 0, 10));
	if (*str == '-') str++;

	num[0] = *str++;
	num[1] = *str++;
	num[2] = 0;
	day = short(strtol(num, 0, 10));

	return str;
}

cchar* mysql_time::convert(cchar* str)
{
	char num[5];

	num[0] = *str++;
	num[1] = *str++;
	num[2] = 0;
	hour = short(strtol(num,0,10));
	if (*str == ':') str++;

	num[0] = *str++;
	num[1] = *str++;
	num[2] = 0;
	minute = short(strtol(num,0,10));
	if (*str == ':') str++;

	num[0] = *str++;
	num[1] = *str++;
	num[2] = 0;
	second = short(strtol(num,0,10));

	return str;
}

cchar* DateTime::convert(cchar* str)
{
	str = mysql_date::convert(str);
	if (*str == ' ') str++;
	str = mysql_time::convert(str);
	return str;
}

short int mysql_date::compare(const mysql_date* other) const
{
	if (year != other->year) return year - other->year;
	if (month != other->month) return month - other->month;
	return day - other->day;
}

short int mysql_time::compare(const mysql_time* other) const
{
	if (hour != other->hour) return hour - other->hour;
	if (minute != other->minute) return minute - other->minute;
	return second - other->second;
}

short int DateTime::compare(const DateTime &other) const
{
	int x;
	x = mysql_date::compare(&other);
	if (x) return x;
	return mysql_time::compare(&other);
}

} // end namespace mysqlpp

