#pragma once

#include <string>
#include <list>

namespace toy
{
	class CTree;
	
	enum SYNTAX_ERR
	{
		ERR_NOTHING =0,

		ERR_BRACE_MISMATCH,
		ERR_INVALID_INT,
		ERR_INVALID_CHAR,
		
		ERR_UNEXPECTED_BRACE_OPEN,
		ERR_UNEXPECTED_BRACE_CLOSE,
		ERR_UNEXPECTED_OPERATOR,
		ERR_UNEXPECTED_OPERAND,
	};

	enum LEXEME_TYPE
	{
		LEX_NULL = -1,
		LEX_BRACE_OPEN = 0,
		LEX_OPERATOR,
		LEX_CONSTANT,
		LEX_IDENTIFIER,
		LEX_BRACE_CLOSE,
	};

	struct CLexeme
	{
	public:
		CLexeme():name(L""),type(LEX_NULL){}
		~CLexeme(){}

		std::wstring name;
		LEXEME_TYPE type;
	};

	/***********************************************
	* TOY의 문법성 검사, 파싱트리 생성을 하는 클래스
	************************************************/

	class CParser
	{
	public:
		CParser(void);
		~CParser(void);

		void						Parse(std::list<std::wstring> code);

		std::list<std::wstring>		GetIntermediateList();
		std::wstring				GetPostFixString();

	private:

		// Generate lexeme list
		void LexicalAnalysis(std::wstring infix);
		// Generate Parsing tree
		void SyntaxAnalysis();

		// Generate Post Fix
		void GeneratePostFix();
		// Generate Intermediate codes
		void GenerateIntermediateCode();

		// Debug
		void OutputDebugList();

	private:

		std::wstring			m_strPostFix;
		
		std::list<CLexeme>		m_listLexemes;
		CTree *					m_pExpTree;
		std::list<std::wstring> m_listIntermCodes;
	};

}