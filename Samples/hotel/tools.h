String ReplaceChar(CString &str)
{
	//�滻�ַ��е� "'" �Լ�
	CString strReturn("");
	try
	{
		if(str.GetLength()>0)
		{
			strReturn=str;
			strReturn.TrimLeft();
			strReturn.TrimRight();
			strReturn.Replace("'","\'");
		}
	}
	MYCATCH()
	return strReturn;
}