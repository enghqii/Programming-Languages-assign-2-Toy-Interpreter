#include "stdafx.h"
#include "Adapter.h"

#include "Parser.h"
#include "Interpreter.h"

namespace toy
{
	CAdapter::CAdapter(void)
		:m_strCode(L""),
		m_strPostFix(L""),
		m_strIntermediate(L""),
		m_strResult(L""),
		m_pParser(NULL)
	{
		m_pParser		= new CParser();
		m_pInterpreter	= new CInterpreter();
	}


	CAdapter::~CAdapter(void)
	{
		delete m_pParser;
		delete m_pInterpreter;
	}
	
	void CAdapter::Parse(std::wstring infix)
	{
		this->m_strCode = infix;
		// generate 'm_strPostFix'
		try
		{
			m_pParser->Parse(m_strCode);
		}
		catch(SYNTAX_ERR err)
		{
			switch(err)
			{
			case ERR_NOTHING:
				OutputDebugString(m_strCode.c_str());
				break;
			}
		}
	}

	CString CAdapter::GenerateIntermediateString()
	{
		CString interms = L"";
		std::list<std::wstring> intermList = m_pParser->GetIntermediateList();

		for( auto iter : intermList )
		{
			CString str(iter.c_str());
			interms.Append(str + L"\r\n");
		}

		return interms;
	}

	void CAdapter::Execute()
	{
		std::list<std::wstring> intermList = m_pParser->GetIntermediateList();
		m_pInterpreter->SetIntermediateCode(intermList);
		int res = m_pInterpreter->Execute();

		m_strResult = std::to_wstring(res);
	}

	CString CAdapter::GetResultString()
	{
		return CString(m_strResult.c_str());
	}
}
