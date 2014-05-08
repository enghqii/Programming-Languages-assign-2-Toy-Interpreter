#pragma once
#include "stdafx.h"
#include <string>
#include <list>

namespace toy
{

	class CParser;
	class CInterpreter;
	class CFileIO;

	/***********************************
	* TOY언어의 해석, Dialog 적응 담당 *
	***********************************/

	class CAdapter
	{
	public:
		
		CAdapter(void);
		~CAdapter(void);

	public:

		// Controls
		bool		LoadSource(CString pathName);
		bool		SaveSource(CString pathName, CString source);
		CString		GetSourceString();

		// Parser
		bool		Parse(std::list<std::wstring> infix);

		CString		GetPostFixString();

		void		GenerateIntermediateString();

		bool		SaveIntermediateCode(CString pathName);
		bool		LoadIntermediateCode(CString pathName);
		CString		GetIntermediateString();

		void		LoadDefun();
		void		SaveDefun(CString source);

		void		ClearSource(){ m_listCode.clear(); }
		std::list<std::wstring>	GetListCode(){return m_listCode;}

		// Executions
		void		Execute();
		CString		GetResultString();

	private:

		CParser *		m_pParser;
		CInterpreter *	m_pInterpreter;
		CFileIO *		m_pFileIO;

	private:

		// Raw
		std::list<std::wstring>	m_listCode;			// infix TOY code

		// pass 1
		std::wstring			m_strPostFix;		// postfix TOY code
		std::list<std::wstring> m_listIntermediate;	// intermediate code

		// pass 2
		std::wstring			m_strResult;
	};

}
