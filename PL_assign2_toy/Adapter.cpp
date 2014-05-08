#include "stdafx.h"
#include "Adapter.h"

#include "Parser.h"
#include "Interpreter.h"
#include "FileIO.h"
#include "FunctionTable.h"

#include <fstream>

namespace toy
{
	CAdapter::CAdapter(void)
		:m_strPostFix(L""),
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
			std::list<std::wstring> sour =  m_pFileIO->LoadSource(str);
			this->m_listCode.insert(m_listCode.end(), sour.begin(), sour.end());
		}
		catch(int err)
		{
			return false;
		}
		return true;
	}

	bool CAdapter::SaveSource(CString pathName, CString source)
	{
		std::wofstream fout;
		fout.open(pathName,std::ios::trunc);
		if(!fout){ return false; }

		int		curpos = 0;
		CString resToken = source.Tokenize(L"\r\n", curpos);
		std::list<std::wstring> listCode;

		while (resToken != _T(""))
		{
			std::wstring wstr = resToken;
			listCode.push_back(wstr);
			resToken = source.Tokenize(L"\r\n", curpos);
		}

		for(std::wstring line : listCode)
		{
			if(line.substr(1,5) != L"DEFUN")
			{
				fout<<line<<std::endl;
			}
		}

		fout.close();

		return true;

	}

	CString CAdapter::GetSourceString()
	{
		CString str;
		for(std::wstring wstr : m_listCode)
		{
			str.Append(wstr.c_str());
			str.Append(L"\r\n");
		}
		return str;
	}

	bool CAdapter::Parse(std::list<std::wstring> infix)
	{
		this->m_listCode = infix;

		m_strPostFix = L"";
		m_listIntermediate.clear();

		// generate 'm_strPostFix'
		try
		{
			m_pParser->Parse(m_listCode);
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

		auto interms1 = CFunctionTable::shared_table()->GetIntermediates();
		m_listIntermediate.insert(m_listIntermediate.end(), interms1.begin(), interms1.end());

		auto interms2 = m_pParser->GetIntermediateList();
		m_listIntermediate.insert(m_listIntermediate.end(), interms2.begin(), interms2.end());
	}
	
	bool CAdapter::SaveIntermediateCode(CString pathName)
	{
		std::wstring str(pathName);
		try
		{
			m_pFileIO->SaveIntermediateCode(str, m_pParser->GetIntermediateList());
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
			m_listIntermediate.clear();
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
		m_pInterpreter->SetIntermediateCode(m_listIntermediate);
		std::list<int> res;

		try
		{
			res = m_pInterpreter->Execute();
		}
		catch(int err)
		{
			m_strResult = L"undefined";
			return;
		}

		m_strResult = L"";

		for(int val : res)
		{
			m_strResult.append(std::to_wstring(val));
			m_strResult.append(L"\r\n");
		}
	}

	CString CAdapter::GetResultString()
	{
		return CString(m_strResult.c_str());
	}

	void CAdapter::LoadDefun()
	{
		std::wifstream fin;
		fin.open("defun.txt");
		if(!fin)
		{
			throw -1;
		}

		std::list<std::wstring> defun;

		// BLAME
		while(fin.eof() == false)
		{
			std::wstring line = L"";
			std::getline(fin, line);

			defun.push_back(line);
		}

		m_listCode = defun;
		//m_listCode.insert(m_listCode.end(), defun.begin(), defun.end());

		__asm{nop}
		fin.close();
	}

	void CAdapter::SaveDefun(CString source)
	{
		std::wofstream fout;
		fout.open("defun.txt",std::ios::trunc);

		int		curpos = 0;
		CString resToken = source.Tokenize(L"\r\n", curpos);
		std::list<std::wstring> listCode;

		while (resToken != _T(""))
		{
			std::wstring wstr = resToken;
			listCode.push_back(wstr);
			resToken = source.Tokenize(L"\r\n", curpos);
		}

		for(std::wstring line : listCode)
		{
			if(line.substr(1,5) == L"DEFUN")
			{
				fout<<line<<std::endl;
			}
		}

		fout.close();
	}
}
