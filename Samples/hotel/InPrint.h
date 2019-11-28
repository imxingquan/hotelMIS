//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  InPrint.cpp
// 
// Desc: 打印入库单
//
// Author:  邢泉
//
// Modified: 2006年 6月 12日
//--------------------------------------------------------------------------------------

#pragma once

#include "ExcelPrint.h"
#include "HInOutRep.h"
class InPrint : public ExcelPrint
{
public:
	InPrint(list<hotelMIS::HInOutRep> &list);
	~InPrint();
    
public:
	list<hotelMIS::HInOutRep> m_list;

	void SendExcel();

};