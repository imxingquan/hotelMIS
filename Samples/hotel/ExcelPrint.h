//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  ExcelPrint.h
// 
// Desc: 打印通用类
//
// Author:  邢泉
//
// Modified: 2006年 6月 12日
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
	// 创建 Excel
	bool CreateExcel();
	
	//载入模板
	void LoadTemplate(CString tmplName);
	
	// 打印预览
	void PrintPreview();

	// 打印
	void Print();

	//保存到文件
	void SaveAs(CString fileName=_T(""));

	//将数据写入 Excel
	virtual void SendExcel(){ }

	//为单无格画线
	void DrawFrame(CString unit,short int LineStyles=1,long Weight=2,long ColorIndex=1);

	void SetExcelVisible(bool isVisible);

	void DrawLine(int rowNum,int colNum,int start_Row=0,int start_Col=0,short int lineStyle=1,long weight=2,long colorIndex=1);

	//CLOSE
	void Close();
protected:
	CString m_excelTmpl; //Exel 模板名

	_Application m_ExcelApp; 
	Workbooks m_wbsMyBooks; 
	_Workbook m_wbMyBook; 
	Worksheets m_wssMysheets; 
	_Worksheet m_wsMysheet; 
	Range m_rgMyRge; 	
};