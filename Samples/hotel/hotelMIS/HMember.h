//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		HMember.h
//
// Description:    
//				��Ա������Ϣ
//
// Version: 1.4
//
// Hostory:		
//			05-8-2006	��Ȫ	Created	
//			
//---------------------------------------------------------

#pragma once

#include <string>
using namespace std;

namespace hotelMIS
{
	//
	//��Ա������Ϣ��
	//
	class HMember
	{
	public:
			HMember();
			~HMember();

	public:
		string		bh;		//��Ա���
		string		mname;	//��Ա����
		string		sex;	//�Ա�
		string		mbirth;	//��������
		string		telphone;	//��ϵ�绰
		int			mdjid;		//��Ա�ȼ�
		string		mdjname;	//�ȼ�����
		float		zhekou;		//�ۿ�
		float		czmoney;	//��ֵ���
		string		rhdate;		//�������
		string		remark;		//��ע
	};

	//
	// ��Ա�ȼ���
	class HMdj
	{
	public:
		HMdj();
		~HMdj();

	public:
		int		id;		//id
		string		djname;		//�ȼ�����
		float		zhekou;		//�ۿ�
	};

	//
	// ��Ա��ֵ
	class HMcz
	{
	public :
		HMcz();
		~HMcz();

	public:
		int			id;		//id
		string		bh;		//��Ա���
		float		czmoney;	//��ֵ���
		string		czdate;		//��ֵ���
		string		opname;		//������Ա
		string		remark;		//��ע
	};
	
	//
	// ��Աת��
	class HMzz
	{
	public:
		HMzz();
		~HMzz();

	public:
		int		id;		//id
		string	sbh;	//ת���˺�
		string  dbh;	//ת���˺�
		float	zzmoney;	//ת�˽��
		string	zzdate;		//ת������
		string	remark;		//��ע

	};
}