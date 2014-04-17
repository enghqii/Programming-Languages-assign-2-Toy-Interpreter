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

	/* �������� ���ܵ��� ����Ϳ��� ó���˴ϴ�. */
	void CParser::Parse(std::wstring infix)
	{
		// Lexical Analysis
		// TODO : ������� ���ڰ� �ְų� ��ư �̻��� ���ڿ��� ������ throw.
		this->LexicalAnalysis(infix);

		OutputDebugList();

		// Syntax Analysis
		// TODO : ���� ���� �ڵ鸵 �ؾ���. ���� �������� ����Ǵ°� �������� �����Ѵٴ� ��.
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

	/* ------------------------------------------------------------------
	 *	Generate Lexme List
	 *	throws : ERR_INVALID_INT, ERR_INVALID_CHAR, ERR_BRACE_MISMATCH
	 -------------------------------------------------------------------- */
	void CParser::LexicalAnalysis(std::wstring infix)
	{
		m_listLexemes.clear();

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

				// �ϴ� �ĺ��ڿ��� ���ڴ� ���°ɷ�. ( �ٿ��� ��� lexeme �и��� ���� ���� )
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
		
		// TODO : ��ȣ ���� �´��� �Ǻ�
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
	 *	throws : ERR_INVALID_INT, ERR_INVALID_CHAR, ERR_BRACE_MISMATCH
	 -------------------------------------------------------------------- */
	void CParser::SyntaxAnalysis()
	{
		// throw err;
		std::stack<tree::CNode *> stk;

		// TODO : �� Ÿ���� �����غ��°� � expecto!
		LEXEME_TYPE lastType = LEX_NULL;

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
					// TODO : ����� ��ȿ�� �Ǻ� - DONE
					try
					{
						int val = std::stoi(it.name);
						__asm{nop}
					}
					catch(std::invalid_argument err)
					{
						throw ERR_INVALID_INT;
					}

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
					tree::CNode * rValue	= NULL;
					tree::CNode * op		= NULL;
					tree::CNode * lValue	= NULL;

					if( stk.empty() == false )
					{
						rValue = stk.top();
						stk.pop();
					}

					if( stk.empty() == false )
					{
						op = stk.top();
						stk.pop();
					}
					
					if( stk.empty() == false )
					{
						lValue = stk.top();
						stk.pop();
					}

					// TODO : rValue , lValue , op�� ��� Ÿ�� �˻� �ʿ� 

					op->SetLeft(lValue);
					op->SetRight(rValue);

					stk.push(op);

					// TODO : ���� push, pop �Ҷ� �ͼ��� ó�� �ؾ� �Ҳ�? - 
				}
				break;

			case LEX_NULL:

			default:
				break;
			}

			lastType =  it.type;
		}

		// TODO : merge all nodes in stack?
		// TODO : ���ÿ� ���� �ϳ��� ����? �� Ȯ���ؾ���
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