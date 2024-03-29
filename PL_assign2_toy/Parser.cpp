#include "stdafx.h"
#include "Parser.h"
#include "Tree.h"

#include <stack>

#include "FunctionTable.h"

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

	/* 던져지는 예외들은 어댑터에서 처리됩니다. */
	void CParser::Parse(std::list<std::wstring> code)
	{
		// TODO : clear exp tree
		m_pExpTree->Clear();
		m_listIntermCodes.clear();

		for(std::wstring line : code)
		{
			// Lexical Analysis
			m_listLexemes.clear();

			this->LexicalAnalysis(line);
			OutputDebugList();

			// Syntax Analysis
			this->SyntaxAnalysis();
		}

		FunctionMap& map = CFunctionTable::shared_table()->GetMap();

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

	/* ------------------------------------------------------------------
	 *	Generate Lexme List
	 *	throws : ERR_INVALID_INT, ERR_INVALID_CHAR, ERR_BRACE_MISMATCH
	 -------------------------------------------------------------------- */
	void CParser::LexicalAnalysis(std::wstring infix)
	{
		///m_listLexemes.clear();

		int brace = 0;

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
					brace++;
					lexeme.type = LEX_BRACE_OPEN;
				}
				else if( ')' == infix[i] )
				{
					brace--;
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
				// or a KEYWORD?
				else if( (lexeme.name.compare(L"DEFUN") == 0) ||
					(lexeme.name.compare(L"COND") == 0) )
				{
					lexeme.type = LEX_KEYWORD;
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
					if(infix[j] == '.')
					{
						throw ERR_INVALID_INT;
					}
					else
					{
						lexeme.name += infix[j];
						j++;
					}
				}
				while( (j < len) && (isdigit(infix[j]) || infix[j] == '.') );

				i += lexeme.name.length() - 1;

				lexeme.type = LEX_CONSTANT;
				m_listLexemes.push_back(lexeme);

			}
			else if(isspace(infix[i]))
			{
				// whitespace (ignore)
				continue;
			}
			else
			{
				throw ERR_INVALID_CHAR;
			}
		}
		
		// TODO : 괄호 갯수 맞는지 판별
		if( brace != 0 )
		{
			throw ERR_BRACE_MISMATCH;
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

	/* ------------------------------------------------------------------
	 *	Generate expression tree, throws Syntax error if there's
	 *	throws : ERR_UNEXPECTED_BRACE_OPEN, ERR_UNEXPECTED_BRACE_CLOSE, 
	 ERR_UNEXPECTED_OPERATOR, ERR_UNEXPECTED_OPERAND, ERR_INVALID_INT
	 -------------------------------------------------------------------- */
	void CParser::SyntaxAnalysis()
	{
		
		// Default state is "EXPRESSION"
		// if there is 'DEFUN' the state changes into "DECLEAR"
		m_eState = STATE_EXPRESSION;
		
		// tree generating stack
		std::stack<tree::CNode *> stk;

		// saving last lexical type
		LEXEME_TYPE lastType = LEX_NULL;

		// used in DEFUN state
		std::wstring funcName;
		std::list<std::wstring> argn;

		for(std::list<CLexeme>::iterator iter = m_listLexemes.begin();
			iter != m_listLexemes.end();
			lastType = iter->type, ++iter) 
		{

			switch( iter->type )
			{
			case LEX_BRACE_OPEN:

				/*
				if(lastType != LEX_BRACE_OPEN && 
					lastType != LEX_NULL && 
					lastType != LEX_OPERATOR )
				{
					throw ERR_UNEXPECTED_BRACE_OPEN;
				}
				*/
				break;

			case LEX_IDENTIFIER:
				{	
					// find symbol
					if( CFunctionTable::shared_table()->Find(iter->name) ||
						(m_eState == STATE_DEFUN && funcName.compare(iter->name) == 0 ) )
					{
						(*iter).type = LEX_OPERATOR;
						--iter;
						continue;
					}

					if(lastType != LEX_NULL && 
						lastType != LEX_IDENTIFIER &&
						lastType != LEX_CONSTANT &&
						lastType != LEX_OPERATOR &&
						lastType != LEX_BRACE_CLOSE )
					{
						throw ERR_UNEXPECTED_OPERAND;
					}

					// just push
					tree::CNode * node = new tree::CNode(NULL, tree::NODE_OPERAND, iter->name);
					stk.push(node);
				}
				break;

			case LEX_CONSTANT:
				{
					if(lastType != LEX_NULL && 
						lastType != LEX_IDENTIFIER &&
						lastType != LEX_CONSTANT &&
						lastType != LEX_OPERATOR &&
						lastType != LEX_BRACE_CLOSE)
					{
						throw ERR_UNEXPECTED_OPERAND;
					}

					try
					{
						int val = std::stoi(iter->name);
						__asm{nop}
					}
					catch(std::invalid_argument err)
					{
						throw ERR_INVALID_INT;
					}

					tree::CNode * node = new tree::CNode(NULL, tree::NODE_OPERAND, iter->name);
					stk.push(node);
				}
				break;

			case LEX_OPERATOR:
				{
					if(lastType != LEX_NULL &&
						lastType != LEX_BRACE_OPEN )
					{
						throw ERR_UNEXPECTED_OPERATOR;
					}

					tree::CNode * node = new tree::CNode(NULL, tree::NODE_OPERATOR, iter->name);
					stk.push(node);
				}
				break;

			case LEX_BRACE_CLOSE:
				{
					if(	lastType != LEX_CONSTANT &&
						lastType != LEX_IDENTIFIER &&
						lastType != LEX_BRACE_CLOSE)
					{
						throw ERR_UNEXPECTED_BRACE_CLOSE;
					}

					if(stk.size() > 1)
					{
						// merging nodes
						tree::CNode * op		= NULL;

						std::stack<toy::tree::CNode *> tempStk;

						// gathering parameters... into 'tempStk'
						// An operator node which has no childred is the 'op'
						while( !( (stk.top()->GetType() == tree::NODE_OPERATOR) && 
								(stk.top()->GetChildren().size() == 0) ) )
						{
							tempStk.push(stk.top());
							stk.pop();
						}

						op = stk.top();
						stk.pop();

						// and... merge parameters 
						while(tempStk.empty() == false)
						{
							op->AddRight(tempStk.top());
							tempStk.pop();
						}

						stk.push(op);
					}
				}
				break;

			case LEX_KEYWORD:
				{
					if(lastType != LEX_BRACE_OPEN)
					{
						throw ERR_UNEXPECTED_KEYWORD;
					}

					// TODO : ah.... this logic is too strict

					if ( iter->name.compare(L"DEFUN") == 0 )
					{
						m_eState = STATE_DEFUN;

						++iter;
						funcName = (*(iter)).name;
						
						++iter;// '('
						++iter;

						while((*iter).name.compare(L")") != 0)
						{
							CLexeme lex = *iter;
							argn.push_back(lex.name);
							++iter;
						}

						__asm{nop}
					}

					// yeah.

				}
				break;

			case LEX_NULL:

			default:
				break;
			}
		}

		// 수식 트리 저장
		if(stk.empty() == false)
		{
			if(m_eState == STATE_EXPRESSION)
			{
				m_pExpTree->AddExpTree(stk.top());
			}
			else if(m_eState == STATE_DEFUN)
			{
				CUserFunction * func = new CUserFunction(funcName, argn, stk.top());
				CFunctionTable::shared_table()->Add(funcName, func);
				__asm{nop}
			}
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

	}
}