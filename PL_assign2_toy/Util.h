#pragma once
#include "stdafx.h"
#include <string>

namespace toy{

	class CUtil
	{
	public:
		CUtil(void);
		~CUtil(void);

		static std::string ConvertString(CString str);
	};

}