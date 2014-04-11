#include "stdafx.h"
#include "Interpreter.h"

namespace toy
{
	CInterpreter::CInterpreter(void)
	{
	}


	CInterpreter::~CInterpreter(void)
	{
	}
	
	void CInterpreter::SetIntermediateCode(std::list<std::wstring>& interms)
	{
		this->m_listInterms = interms;
	}

	int CInterpreter::Execute()
	{
		// TODO : 생각해볼것 : begin 검사를 따로 해줘야 함?

		for( auto iter : m_listInterms )
		{
			if( iter.compare(L"begin") == 0 )
			{
				// clear the stack
				while(m_stk.empty() == false)
				{
					m_stk.pop();
				}
			}
			else if( iter.compare(L"end") == 0 )
			{
				// exodus
				break;
			}
			else if( iter.compare(L"MINUS") == 0 )
			{
				int rValue = m_stk.top();
				m_stk.pop();

				int lValue = m_stk.top();
				m_stk.pop();

				int val = lValue - rValue;
				m_stk.push(val);
			}
			else if( iter.compare(L"IF") == 0 )
			{
				// TODO : add if function
			}
			else if( iter.substr(0,4).compare(L"push") == 0 )
			{
				int len = iter.length();
				std::wstring str = iter.substr(5,len);
				int val = std::stoi(str);

				m_stk.push(val);
			}
		}

		return m_stk.top();
	}
}