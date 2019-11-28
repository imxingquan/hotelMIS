//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  TicketPrint.cpp
// 
// Desc: СƱ��ӡ
//
// Author:  ��Ȫ
//
// Modified: 2006�� 6�� 12��
//--------------------------------------------------------------------------------------

#pragma once

#include "ExcelPrint.h"

class TicketPrint  : public ExcelPrint
{
public:
	TickPrint(CString AccountId,int roomId,int tableId,hotelMIS::HRepDetailsVec &vec);
	~TickPrint();
	
	void SendExcel();

protected:
	CString		m_accountId;
	int			m_roomId;
	int			m_tableId;

	hotelMIS::HRepDetailsVec m_vec;

};