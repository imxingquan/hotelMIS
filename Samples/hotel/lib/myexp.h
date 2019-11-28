#ifndef _MY_EXP
#define _MY_EXP
/***************************************************
* DEBUG Macros
*
*/

//#ifdef _DEBUG
#include <windows.h>
#include <time.h>
#include <string>
using namespace std;
namespace mysqlpp{
void WriteErrFile(const char* strErr);

#ifdef _DEBUG
#define myASSERT(x)  if(!(x)) DebugBreak()
#define ODS(x)	OutputDebugString(x)

#define myTRACE1(sz, arg1) { \
	CHAR ach[100]; \
	wsprintf(ach, (sz), (arg1)); \
	ODS(ach); }

#define myTRACE2(sz, arg1, arg2) { \
	CHAR ach[100]; \
	wsprintf(ach, (sz), (arg1), (arg2)); \
	ODS(ach); }

#define myTRACE3(sz, arg1, arg2, arg3) { \
	CHAR ach[100]; \
	wsprintf(ach, (sz), (arg1), (arg2), (arg3)); \
	ODS(ach); }

#else !defined(_DEBUG)

#define myASSERT(x)
#define ODS(x)
#define myTRACE1(sz, arg1)
#define myTRACE2(sz, arg1, arg2)
#define myTRACE3(sz, arg1, arg2, arg3)

#endif // (_DEBUG)


#ifdef _DEBUG
	#define mycatch()																			\
		catch(mysqlpp::BadQuery er){															\
			myTRACE3("BadQuery Error:%s,File:%s,Line:%d\n", er.what(),__FILE__,__LINE__);		\
		}catch(mysqlpp::BadConversion er){														\
			myTRACE3("BadConversion Error:%s,File:%s,Line:%d\n",er.what(),__FILE__,__LINE__);	\
		}catch(exception& er) {																	\
			myTRACE3("Exception:%s,File:%s,Line:%d\n",er.what(),__FILE__,__LINE__);				\
	    }
#else
#define mycatch()						\
	catch(mysqlpp::BadQuery er){		\
		WriteErrFile(er.what());		\
	}catch(mysqlpp::BadConversion er){	\
		WriteErrFile(er.what());		\
	}catch(exception& er){				\
		WriteErrFile(er.what());		\
	}
		
#endif
}

#endif
