//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  InPrint.cpp
// 
// Desc: ��ӡ��ⵥ
//
// Author:  ��Ȫ
//
// Modified: 2006�� 6�� 12��
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