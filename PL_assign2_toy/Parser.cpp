#include "stdafx.h"
#include "Parser.h"
#include "Tree.h"

namespace toy
{

	CParser::CParser(void)
	{
		m_listLexemes.clear();
	}


	CParser::~CParser(void)
	{
	}

	void CParser::Parse(std::wstring infix)
	{
		// Lexical Analysis
		this->LexicalAnalysis(infix);

		OutputDebugList();

		// Syntax Analysis
		this->SyntaxAnalysis();

	}

	/* generate Lexme List */
	void CParser::LexicalAnalysis(std::wstring infix)
	{
		m_listLexemes.clear();

		int len = infix.length();
		for(int i =0; i < len; i++)
		{

			if( '(' == infix[i] || ')' == infix[i] )
			{
				// braces
				CLexeme lexeme;
				lexeme.name += infix[i];
				
				if( '(' == infix[i] )
				{
					lexeme.type = LEX_BRACE_OPEN;
				}
				else if( ')' == infix[i] )
				{
					lexeme.type = LEX_BRACE_CLOSE;
				}

				m_listLexemes.push_back(lexeme);
			}
			else if(isalpha(infix[i]))
			{
				// identifiers
				CLexeme lexeme;

				for( int j = i; (j < len) && (isalpha(infix[j]) || isdigit(infix[j])); j++ )
				{
					lexeme.name += infix[j];
				}
				i += lexeme.name.length() - 1;

				// is really a identifier ? or an operator?
				if( (lexeme.name.compare(L"MINUS") == 0) ||
					(lexeme.name.compare(L"IF") == 0) ) 
				{
					lexeme.type = LEX_OPERATOR;
				}
				else
				{
					lexeme.type = LEX_IDENTIFIER;
				}

				m_listLexemes.push_back(lexeme);
			}
			else if( isdigit(infix[i]) || '-' == infix[i] )
			{
				// numeric
				CLexeme lexeme;
				int j = i;

				do
				{
					lexeme.name += infix[j];
					j++;
				}
				while( (j < len) && (isdigit(infix[j]) || infix[j] == '.') );

				i += lexeme.name.length() - 1;

				lexeme.type = LEX_CONSTANT;
				m_listLexemes.push_back(lexeme);
			}
			else if(isspace(infix[i])){

				// whitespace (ignore)
				continue;
			}
		}
	}

	void CParser::OutputDebugList()
	{
		for(auto it : m_listLexemes){
			std::wstring str = it.name;
			str += L"\n";
			OutputDebugString(str.c_str());
		}
	}
	
	void CParser::SyntaxAnalysis()
	{
		SYNTAX_ERR err = ERR_NOTHING;
		// throw err;

		for( auto it : m_listLexemes ) 
		{
			it.name;
		}
	}
}