#pragma once

#include <list>
#include <string>
#include <stack>

namespace toy
{
	class CInterpreter
	{
	public:
		CInterpreter(void);
		~CInterpreter(void);

		void	SetIntermediateCode(std::list<std::wstring>& interms);
		int		Execute();

	private:

		std::list<std::wstring>		m_listInterms;
		std::stack<int>				m_stk;
	};
}