#include "stdafx.h"
#include "Util.h"

namespace toy
{

	CUtil::CUtil(void)
	{
	}


	CUtil::~CUtil(void)
	{
	}

	/*static*/ std::string CUtil::ConvertString(CString str){
		CT2CA pszConvertedAnsiString(str);
		std::string strStd(pszConvertedAnsiString);

		return strStd;
	}
}