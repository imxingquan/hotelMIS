String ReplaceChar(CString &str)
{
	//替换字符中的 "'" 以及
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