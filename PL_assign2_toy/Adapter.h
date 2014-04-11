#pragma once
#include "stdafx.h"
#include <string>

namespace toy
{

	class CParser;
	class CInterpreter;

	/***********************************
	* TOY언어의 해석, Dialog 적응 담당 *
	***********************************/

	class CAdapter
	{
	public:
		
		CAdapter(void);
		~CAdapter(void);

	public:

		void		Parse(std::wstring infix);
		CString		GenerateIntermediateString();

		void		Execute();

		CString		GetResultString();

	private:

		CParser *		m_pParser;
		CInterpreter *	m_pInterpreter;

	private:

		// TODO : use those vars

		// Raw
		std::wstring m_strCode;			// infix TOY code

		// pass 1
		std::wstring m_strPostFix;		// postfix TOY code
		std::wstring m_strIntermediate;	// intermediate code

		// pass 2
		std::wstring m_strResult;
	};

}
