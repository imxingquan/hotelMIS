//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  ExcelPrint.h
// 
// Desc: ��ӡͨ����
//
// Author:  ��Ȫ
//
// Modified: 2006�� 6�� 12��
//--------------------------------------------------------------------------------------

#pragma once
#include "excel9.h"

#include <list>
#include <vector>
using namespace std;

class ExcelPrint
{
public:
	ExcelPrint();
	ExcelPrint(CString tmplName);
	~ExcelPrint();

public:
	// ���� Excel
	bool CreateExcel();
	
	//����ģ��
	void LoadTemplate(CString tmplName);
	
	// ��ӡԤ��
	void PrintPreview();

	// ��ӡ
	void Print();

	//���浽�ļ�
	void SaveAs(CString fileName=_T(""));

	//������д�� Excel
	virtual void SendExcel(){ }

	//Ϊ���޸���
	void DrawFrame(CString unit,short int LineStyles=1,long Weight=2,long ColorIndex=1);

	void SetExcelVisible(bool isVisible);

	void DrawLine(int rowNum,int colNum,int start_Row=0,int start_Col=0,short int lineStyle=1,long weight=2,long colorIndex=1);

	//CLOSE
	void Close();
protected:
	CString m_excelTmpl; //Exel ģ����

	_Application m_ExcelApp; 
	Workbooks m_wbsMyBooks; 
	_Workbook m_wbMyBook; 
	Worksheets m_wssMysheets; 
	_Worksheet m_wsMysheet; 
	Range m_rgMyRge; 	
};