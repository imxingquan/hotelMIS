//+-------------------------------------------------------
// HotelMIS ���ֻ��Ƶ����ϵͳ
// Copyright (C) �����������缼�����޹�˾, 2005-2006.
//
// File:		KProfile.h
//
// Description:    
//				���� ini �����ļ�����
//		
//
// Version: 1.0
//
// Hostory:		
//			04-28-2005	��Ȫ	Created	
//			
//---------------------------------------------------------
#pragma once
#include <string>
namespace hotelMIS{
	
	/*--------------------------------------------------------------------------------------
	* class KProfile
	*
	*	member function:
	*		KProfile(std::string file,std::string path="");
	*			parameters:
	*				- file	�ļ�����
	*				- path	�ļ�·�� 
	*		
	*		// ��ȡ ��Ӧ������Ӧ����ֵ
	*		GetProfile(std::string appName,std::string key,	std::string defVal="")
	*			parameters:
	*				- appname	����(ini �ļ�[appName]�е�����
	*				- key		��
	*				- defVal	ֵ Ĭ��Ϊ��
	*			return : bool	
	*		
	*		// ����ֵд�������ļ�
	*		WirteProfile(std::string appName,std::string key,std::string value)
	*			parameters:
	*				- appName	����
	*				- key		��
	*				- value		ֵ
	*
	*		Example:
	*			KProfile profile("set.ini"); //���δ���� path ������Ϊ��ǰӦ�ó����Ŀ¼
	*			//��ȡ���ݿ����ӵ��ַ���
	*			string connectionString = profile.GetProfile("DATA","ConnectinString");
	*		
	*----------------------------------------------------------------------------------------*/

	class KProfile
	{
	public:
		KProfile(std::string file,std::string path="");
		~KProfile(void);
	public:

		std::string KProfile::GetProfile(std::string appName,std::string key,
			std::string defVal="");

		bool WirteProfile(std::string appName,std::string key,std::string value);
	
	private:
		std::string filePath;

	}; // end class KProfile

} // end namespace hotelMIS