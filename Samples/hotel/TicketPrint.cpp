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

#include "stdAfx.h"
#include "TicketPrint.h"
#include "comutil.h"
#include "HAdminBdy.h"

TickPrint::TickPrint(CString AccountId,int roomId,int tableId,hotelMIS::HRepDetailsVec &vec)
{
	m_accontId = AccountId;
	m_roomId = roomId;
	m_tableId = tableId;
	m_vec = vec;
}

TickPrint::~TickPrint()
{

}
	
void TickPrint::SendExcel()
{	
	
}