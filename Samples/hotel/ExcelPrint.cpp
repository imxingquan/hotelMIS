//--------------------------------------------------------------------------------------
// Copyright (c) Idcwest Corporation. All rights reserved.
// 
// File:  ExcelPrint.cpp
// 
// Desc: 打印通用类
//
// Author:  邢泉
//
// Modified: 2006年 6月 12日
//--------------------------------------------------------------------------------------


#include "stdAfx.h"
#include "ExcelPrint.h"
#include "comdef.h" 
//------------------------------------------------------------------------------------------------
ExcelPrint::ExcelPrint()
:m_excelTmpl(_T(""))
{
}

//------------------------------------------------------------------------------------------------
ExcelPrint::ExcelPrint(CString tmplName)
:m_excelTmpl(tmplName)
{
	
}

//--------------------------------------------------------------------------------------------------
ExcelPrint::~ExcelPrint()
{
	Close();

}

void ExcelPrint::Close()
{
	TRY{
	//释放对象
	m_rgMyRge.ReleaseDispatch(); 
	m_wsMysheet.ReleaseDispatch(); 
	m_wssMysheets.ReleaseDispatch(); 
	m_wbMyBook.ReleaseDispatch(); 
	m_wbsMyBooks.Close();
	m_wbsMyBooks.ReleaseDispatch(); 
	m_ExcelApp.ReleaseDispatch();
	m_ExcelApp.Quit();
	}CATCH(CException,e)
	{
		e->ReportError();
		m_ExcelApp.Quit();
	}
	END_CATCH
}
//-----------------------------------------------------------------------------------------------------
// 创建 Excel
bool ExcelPrint::CreateExcel()
{
	TRY{
		if ( ! m_ExcelApp.CreateDispatch("Excel.Application",NULL) )
		{
			MessageBox(NULL,_T("连接Excel 服务回失败!"),_T("提示"),MB_OK);
			return false;
		}
		m_ExcelApp.SetVisible(true);
	}CATCH(CException,e)
	{
		e->ReportError();
		m_ExcelApp.Quit();
	}
	END_CATCH
		return true;
}

//-----------------------------------------------------------------------------------------------------
//载入模板
void ExcelPrint::LoadTemplate(CString tmplName)
{
	TRY{
		if (m_ExcelApp.m_lpDispatch == NULL)
			return;

	//利用模板文件建立新文档 
	m_excelTmpl = tmplName;
	char path[MAX_PATH];
	//GetCurrentDirectory(MAX_PATH,path);
	//GetModuleFileName(NULL,path,MAX_PATH);//AfxGetApp()->m_pszAppName)
	/*CString strPath = path;
	strPath += tmplName;*/

	CString strAppName = AfxGetApp()->m_pszHelpFilePath;
	char dirve[_MAX_DRIVE];
	char dir[_MAX_DIR];
	_splitpath(strAppName,dirve,dir,NULL,NULL);
	CString strPath;
	strPath.Format("%s%s",dirve,dir);
	strPath += tmplName;
	
	//m_ExcelApp.SetVisible(false); 
	
	m_wbsMyBooks.AttachDispatch(m_ExcelApp.GetWorkbooks(),true); 
	m_wbMyBook.AttachDispatch(m_wbsMyBooks.Add(_variant_t(strPath)));
	//得到Worksheets 
	m_wssMysheets.AttachDispatch(m_wbMyBook.GetWorksheets(),true);
	//得到sheet1 
	m_wsMysheet.AttachDispatch(m_wssMysheets.GetItem(_variant_t("sheet1")),true);

	//得到全部Cells，此时,rgMyRge是cells的集合 
	m_rgMyRge.AttachDispatch(m_wsMysheet.GetCells(),true);
	}
	CATCH(CException,e)
	{
		e->ReportError();
		Close();
	}
	END_CATCH
}

//-----------------------------------------------------------------------------------------------------
// 打印预览
void ExcelPrint::PrintPreview()
{
	TRY{
	if (m_ExcelApp.m_lpDispatch == NULL)
			return;
	m_wbMyBook.PrintPreview(_variant_t(false)); 
	}CATCH(CException,e)
	{
		e->ReportError();
		Close();
	}
	END_CATCH
}

//-----------------------------------------------------------------------------------------------------
// 打印
void ExcelPrint::Print()
{
	TRY{
	if (m_ExcelApp.m_lpDispatch == NULL)
			return;
	m_wbMyBook.PrintOut(vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing);
	}CATCH(CException,e)
	{
		e->ReportError();
		Close();
	}
	END_CATCH
}

void ExcelPrint::SetExcelVisible(bool isVisible)
{
	TRY{
		if (m_ExcelApp.m_lpDispatch == NULL)
			return;
		m_ExcelApp.SetVisible(isVisible); 
	}
	CATCH(CException,e)
	{
		e->ReportError();
		Close();
	}
	END_CATCH
}
//-----------------------------------------------------------------------------------------------------

void ExcelPrint::SaveAs(CString fileName)
{
	TRY{
	//将表格保存
	/*char p[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,p);
	CString strPath ,ftName;
	CTime time=CTime::GetCurrentTime();
	ftName.Format("%s%s.xls",fileName,time.Format("%Y_%m_%d_%H_%M_%S"));
	strPath.Format("%s\\print\\%s",p,ftName);*/
	m_wsMysheet.SaveAs(fileName,vtMissing,vtMissing,vtMissing,vtMissing,
		vtMissing,vtMissing,vtMissing,vtMissing);
	}CATCH(CException,e)
	{
		e->ReportError();
		Close();
	}
	END_CATCH
	
}

//----------------------------------------------------------------------------------------------------
//为单无格画线
void ExcelPrint::DrawFrame(CString unit,short int LineStyles,long Weight,long ColorIndex)
{
	Range myrange=m_wsMysheet.GetRange(COleVariant(unit),COleVariant(unit));
	myrange.BorderAround(COleVariant((short)LineStyles),(long)Weight,(long)ColorIndex,vtMissing);
}

void ExcelPrint::DrawLine(int rowNum,int colNum,int start_Row,int start_Col,short int lineStyle,long weight,long colorIndex)
{
	char c='A';
	CString t;
	for ( int row=start_Row;row<=rowNum;row++)
	{
		for ( int col=start_Col;col<colNum;col++)
		{
			t.Format("%c%d",c+col,row);
			DrawFrame(t,lineStyle,weight,colorIndex);
		}
	}
}
