//+-------------------------------------------------------
// HotelMIS 数字化酒店管理系统
// Copyright (C) 大连西数网络技术有限公司, 2005-2006.
//
// File:		HMember.h
//
// Description:    
//				会员基本信息
//
// Version: 1.4
//
// Hostory:		
//			05-8-2006	邢泉	Created	
//			
//---------------------------------------------------------

#pragma once

#include <string>
using namespace std;

namespace hotelMIS
{
	//
	//会员基本信息类
	//
	class HMember
	{
	public:
			HMember();
			~HMember();

	public:
		string		bh;		//会员编号
		string		mname;	//会员姓名
		string		sex;	//性别
		string		mbirth;	//出生日期
		string		telphone;	//联系电话
		int			mdjid;		//会员等级
		string		mdjname;	//等级名称
		float		zhekou;		//折扣
		float		czmoney;	//充值金额
		string		rhdate;		//入会日期
		string		remark;		//备注
	};

	//
	// 会员等级类
	class HMdj
	{
	public:
		HMdj();
		~HMdj();

	public:
		int		id;		//id
		string		djname;		//等级名称
		float		zhekou;		//折扣
	};

	//
	// 会员充值
	class HMcz
	{
	public :
		HMcz();
		~HMcz();

	public:
		int			id;		//id
		string		bh;		//会员编号
		float		czmoney;	//充值金额
		string		czdate;		//充值金额
		string		opname;		//操作人员
		string		remark;		//备注
	};
	
	//
	// 会员转账
	class HMzz
	{
	public:
		HMzz();
		~HMzz();

	public:
		int		id;		//id
		string	sbh;	//转出账号
		string  dbh;	//转入账号
		float	zzmoney;	//转账金额
		string	zzdate;		//转账日期
		string	remark;		//备注

	};
}