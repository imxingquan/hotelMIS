//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HMember.cpp
//
// Description:    
//				��Ա������Ϣ
//
// Version: 1.5
//
// Hostory:		
//			06-03-2006	��Ȫ	Created	
//			
//---------------------------------------------------------
#include "stdAfx.h"
#include "HMember.h"
using namespace hotelMIS;

HMember::HMember()
:bh(""),
	mname(""),
	sex(""),
	mbirth(""),
	telphone(""),
	mdjid(0),
	mdjname(""),
	zhekou(0.0f),
	czmoney(0.0f),
	rhdate(""),
	remark("")
{
}

HMember::~HMember()
{
}
//======================================================
//
// HMdj
//
HMdj::HMdj()
:id(0),
	djname(""),
	zhekou(0.0f)
{
}

HMdj::~HMdj()
{
}


//=====================================================
//
// HMcz
//

HMcz::HMcz()
:id(0),		
 bh(""),		
 czmoney(0.0f),
 czdate(""),
 opname(""),
 remark("")
{
}

HMcz::~HMcz()
{
}


//----------------------------------------------------------------------------------------
//class HMzz

HMzz::HMzz()
	: id(0)
	, sbh("")
	, dbh("")
	, zzmoney(0)
	, zzdate("")
	, remark("")
{
}

HMzz::~HMzz()
{
}