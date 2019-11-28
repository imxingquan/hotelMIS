#define MYSQLPP_NOT_HEADER
#include "stdafx.h"
#include "platform.h"

#include "field_types.h"

#include "result.h"

namespace mysqlpp {

void FieldTypes::init(const ResUse * res)
{
	int num = res->num_fields();
	reserve(num);
	for (int i = 0; i < num; i++) {
		push_back(res->fields(i));
	}
}

} // end namespace mysqlpp
