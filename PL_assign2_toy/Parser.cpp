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

	void CParser::Parse(std::string infix)
	{
		// Lexical Analysis
		this->LexicalAnalysis(infix);

		OutputDebugList();

		// Syntax Analysis

		/*
		SYNTAX_ERR err = ERR_NOTHING;
		// throw err;
		}*/
	}

	/* generate Lexme List */
	void CParser::LexicalAnalysis(std::string infix)
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
			std::string str = it.name;
			str += "\n";
			OutputDebugStringA(str.c_str());
		}
	}
}