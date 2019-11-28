/*--
Company: 大连西数网络技术有限公司
Author: 邢泉 QQ:402059985 
Email: support@idcwest.net booma999@hotmail.com
Description: 
		换桌
Revision History:
	Author	Date		Description
	------	----		------------
	邢泉    04/23/05	v1.2 
	邢泉	08/28/05	v1.3 

--*/
#pragma once
#include "afxwin.h"

#include "HChgTableBdy.h"
#include "config.h"
// CChangeTableDialog 对话框
#include <map>
using namespace std;

class CChangeTableDialog : public CDialog
{
	DECLARE_DYNAMIC(CChangeTableDialog)

public:
	CChangeTableDialog(CWnd* pParent,int tableId,int roomId);   // 标准构造函数
	virtual ~CChangeTableDialog();
	
	int getDestTable() const
	{
		return m_destTid;
	}
// 对话框数据
	enum { IDD = IDD_CHANGTABLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//Control var
	CGuiGroupBox m_GuiGroupBox;
	CGuiComboBoxExt m_GuiComboBox;	
	CGuiComboBoxExt m_GuiRoomNoComBo;
	CGuiButton m_GuiButtonOk;
	CGuiButton m_GuiButtonCancel;
	//binding var
	int m_destTableNo;
	int m_destTid;
	hotelMIS::HChgTableBdy *pChgTableBdy;
	map<int,int> m_mapTable; //map<pos,tId>;
	map<int,int> m_roomMap; //map<pos,id>
	
	hotelMIS::KDBCon m_con;
	//msg
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	void InitRoomNoAndTalbeId();
	afx_msg void OnCbnSelchangeRoomnoCombo();
};
