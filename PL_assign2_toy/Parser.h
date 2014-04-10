#pragma once

#include <string>
#include <list>

namespace toy
{
	class CTree;
	
	enum SYNTAX_ERR
	{
		ERR_NOTHING =0,
		ERR_BRACE_OPEN,
		ERR_BRACE_CLOSE,
		ERR_UNEXPECTED_FLOAT,
		ERR_INVALID_CHAR,
		ERR_MINUS_DUPLICATED,
		ERR_INVALID_OPERATOR,
	};

	enum LEXEME_TYPE
	{
		LEX_NULL = 0,
		LEX_IDENTIFIER,
		LEX_CONSTANT,
		LEX_OPERATOR,
		LEX_BRACE_OPEN,
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

		// Parse LIKE A STATE MACHINE
		void Parse(std::wstring infix); 

	private:

		// Generate lexeme list
		void LexicalAnalysis(std::wstring infix);
		// Generate Parsing tree
		void SyntaxAnalysis();

		void OutputDebugList();

	private:

		CTree *				m_pParseTree;
		std::list<CLexeme>	m_listLexemes;
	};

}