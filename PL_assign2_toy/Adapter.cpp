#include "stdafx.h"
#include "Adapter.h"

#include "Parser.h"

namespace toy
{
	CAdapter::CAdapter(void)
		:m_strCode(L""),
		m_strPostFix(""),
		m_strIntermediate(""),
		m_strResult(""),
		m_pParser(NULL)
	{
		m_pParser = new CParser();
	}


	CAdapter::~CAdapter(void)
	{
		delete m_pParser;
	}
	
	void CAdapter::Parse(std::wstring infix)
	{
		this->m_strCode = infix;
		CString str(m_strCode.c_str());

		// generate 'm_strPostFix'
		try
		{
			//m_pParser->Parse(m_strCode);
		}
		catch(SYNTAX_ERR err)
		{
			switch(err)
			{
			case ERR_NOTHING:
				str.Format(L"NO ERROR\n");
				OutputDebugString(str);
				break;
			}
		}
	}
}
