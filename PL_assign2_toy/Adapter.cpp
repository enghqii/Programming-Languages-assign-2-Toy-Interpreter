#include "stdafx.h"
#include "Adapter.h"

#include "Parser.h"
#include "Interpreter.h"
#include "FileIO.h"

namespace toy
{
	CAdapter::CAdapter(void)
		:m_strCode(L""),
		m_strPostFix(L""),
		m_strResult(L""),
		m_pParser(NULL)
	{
		m_pParser		= new CParser();
		m_pInterpreter	= new CInterpreter();
		m_pFileIO		= new CFileIO();
	}


	CAdapter::~CAdapter(void)
	{
		delete m_pParser;
		delete m_pInterpreter;
		delete m_pFileIO;
	}

	bool CAdapter::LoadSource(CString pathName)
	{
		std::wstring str(pathName);
		try
		{
			this->m_strCode = m_pFileIO->LoadSource(str);
		}
		catch(int err)
		{
			return false;
		}
		return true;
	}

	CString CAdapter::GetSourceString()
	{
		return CString(m_strCode.c_str());
	}

	bool CAdapter::Parse(std::wstring infix)
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
			case ERR_BRACE_MISMATCH:
				m_strResult = L"error : brace mismatch\n";
				return false;
			case ERR_INVALID_INT:
				m_strResult = L"error : invalid integer\n";
				return false;
			case ERR_INVALID_CHAR:
				m_strResult = L"error : invalid character\n";
				return false;

			case ERR_UNEXPECTED_BRACE_OPEN:
				m_strResult = L"error : unexpected brace open detected\n";
				return false;
			case ERR_UNEXPECTED_BRACE_CLOSE:
				m_strResult = L"error : unexpected brace close detected\n";
				return false;
			case ERR_UNEXPECTED_OPERATOR:
				m_strResult = L"error : unexpected operator detected\n";
				return false;
			case ERR_UNEXPECTED_OPERAND:
				m_strResult = L"error : unexpected operand detected\n";
				return false;

			case ERR_NOTHING:
				OutputDebugString(m_strCode.c_str());
				return false;
			}
		}

		m_strResult = L" >> PARSE SUCCEED << ";
		return true;
	}

	CString CAdapter::GetPostFixString()
	{
		m_strPostFix = m_pParser->GetPostFixString();
		return CString(m_strPostFix.c_str());
	}

	void CAdapter::GenerateIntermediateString()
	{
		m_listIntermediate.clear();
		m_listIntermediate = m_pParser->GetIntermediateList();
	}
	
	bool CAdapter::SaveIntermediateCode(CString pathName)
	{
		std::wstring str(pathName);
		try
		{
			m_pFileIO->SaveIntermediateCode(str, m_listIntermediate);
		}
		catch(int err)
		{
			return false;
		}
		return true;
	}

	bool CAdapter::LoadIntermediateCode(CString pathName)
	{
		std::wstring str(pathName);
		try
		{
			m_listIntermediate = m_pFileIO->LoadIntermediateCode(str);
		}
		catch(int err)
		{
			return false;
		}
		return true;
	}

	CString CAdapter::GetIntermediateString()
	{
		CString interms = L"";

		for( auto iter : m_listIntermediate )
		{
			CString str(iter.c_str());
			interms.Append(str + L"\r\n");
		}

		return interms;
	}

	void CAdapter::Execute()
	{
		//std::list<std::wstring> intermList = m_pParser->GetIntermediateList();
		m_pInterpreter->SetIntermediateCode(m_listIntermediate);
		int res = 0;

		try
		{
			res = m_pInterpreter->Execute();
		}
		catch(int err)
		{
			m_strResult = L"undefined";
			return;
		}

		m_strResult = std::to_wstring(res);
	}

	CString CAdapter::GetResultString()
	{
		return CString(m_strResult.c_str());
	}
}
