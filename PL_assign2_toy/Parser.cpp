#include "stdafx.h"
#include "Parser.h"
#include "Tree.h"

#include <stack>

namespace toy
{

	CParser::CParser(void)
		:m_strPostFix(L"")
	{
		m_listLexemes.clear();
		m_listIntermCodes.clear();
		m_pExpTree = new CTree();
	}


	CParser::~CParser(void)
	{
		delete m_pExpTree;
	}

	void CParser::Parse(std::wstring infix)
	{
		// Lexical Analysis
		// TODO : 쓸모없는 문자가 있거나 여튼 이상한 문자열이 들어오면 throw.
		this->LexicalAnalysis(infix);

		OutputDebugList();

		// Syntax Analysis
		// TODO : 문법 오류 핸들링 해야함. 다음 라인으로 진행되는건 정상동작을 보증한다는 뜻.
		this->SyntaxAnalysis();
		
		/*m_pExpTree->OutputInorderTraverse();
		m_pExpTree->OutputPostorderTraverse();*/

		this->GeneratePostFix();
		this->GenerateIntermediateCode();

	}

	std::list<std::wstring> CParser::GetIntermediateList()
	{
		return this->m_listIntermCodes;
	}

	std::wstring CParser::GetPostFixString()
	{
		return this->m_strPostFix;
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

				// 일단 식별자에서 숫자는 없는걸로. ( 붙여쓸 경우 lexeme 분리가 되지 않음 )
				for( int j = i; (j < len) && (isalpha(infix[j]) /*|| isdigit(infix[j])*/ ); j++ )
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
		// TODO : 괄호 갯수 맞는지 판별

		SYNTAX_ERR err = ERR_NOTHING;
		// throw err;
		std::stack<tree::CNode *> stk;

		for( auto it : m_listLexemes ) 
		{
			switch( it.type )
			{
			case LEX_BRACE_OPEN:
				// ignore
				break;
			case LEX_IDENTIFIER:
				{	
					// just push
					tree::CNode * node = new tree::CNode(NULL, tree::NODE_OPERAND, it.name);
					stk.push(node);
				}
				break;
			case LEX_CONSTANT:
				{
					// TODO : 상수값 유효성 판별

					tree::CNode * node = new tree::CNode(NULL, tree::NODE_OPERAND, it.name);
					stk.push(node);
				}
				break;
			case LEX_OPERATOR:
				{
					tree::CNode * node = new tree::CNode(NULL, tree::NODE_OPERATOR, it.name);
					stk.push(node);
				}
				break;
			case LEX_BRACE_CLOSE:
				{
					tree::CNode * rValue;
					tree::CNode * op;
					tree::CNode * lValue;

					rValue = stk.top();
					stk.pop();

					op = stk.top();
					stk.pop();

					lValue = stk.top();
					stk.pop();

					// TODO : rValue , lValue , op의 노드 타입 검사 필요

					op->SetLeft(lValue);
					op->SetRight(rValue);

					stk.push(op);

					// TODO : 스택 push, pop 할때 익셉션 처리 해야 할껄?
				}
				break;
			case LEX_NULL:
			default:
				break;
			}
		}

		// TODO : merge all nodes in stack?
		// TODO : 스택에 값이 하나만 있음? 을 확인해야함
		if(stk.empty() == false)
		{
			tree::CNode * exp = stk.top();
			m_pExpTree->SetExpNode(exp);
		}
		else
		{

		}
	}

	void CParser::GeneratePostFix()
	{
		m_strPostFix = m_pExpTree->GeneratePostFixString();
	}

	void CParser::GenerateIntermediateCode()
	{
		m_listIntermCodes.clear();

		std::list<std::wstring> postTrav = m_pExpTree->GeneratePostorderInterms();
		m_listIntermCodes = postTrav;
		
		m_listIntermCodes.push_front(std::wstring(L"begin"));
		m_listIntermCodes.push_back(std::wstring(L"end"));
	}
}