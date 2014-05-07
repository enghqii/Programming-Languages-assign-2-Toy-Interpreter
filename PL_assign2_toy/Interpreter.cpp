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

	std::list<int> CInterpreter::Execute()
	{
		std::list<int> output;
		output.clear();

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
				
				if( m_stk.empty() == false )
				{
					std::wstring wstr = std::to_wstring(m_stk.top());
					OutputDebugString(wstr.c_str());

					output.push_back(m_stk.top());
				}
				else
				{
					throw -1;
				}
				
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
				int rValue = m_stk.top();
				m_stk.pop();

				int lValue = m_stk.top();
				m_stk.pop();

				int val;

				if( lValue > 0 && rValue )
				{
					val = rValue;
				}
				else
				{
					val = 0;
				}

				m_stk.push(val);
			}
			else if( iter.substr(0,4).compare(L"push") == 0 )
			{
				int len = iter.length();
				std::wstring str = iter.substr(5,len);

				try
				{
					int val = std::stoi(str);
					m_stk.push(val);
				}
				catch(std::invalid_argument err)
				{
					throw -1;
				}
			}
			else if( iter.substr(0,4).compare(L"call") == 0 )
			{
				int len = iter.length();
				std::wstring str = iter.substr(5,len);
			}
		}

		/*
		if( m_stk.empty() == false )
		{
			return m_stk.top();
		}
		else
		{
			throw -1;
		}*/

		return output;
	}
}