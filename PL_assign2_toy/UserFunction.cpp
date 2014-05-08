#include "stdafx.h"
#include "UserFunction.h"

#include "Tree.h"

namespace toy
{
	CUserFunction::CUserFunction(
		std::wstring name, 
		std::list<std::wstring> argn, 
		toy::tree::CNode* expNode)
		:name(name),
		argn(argn),
		argc(argn.size())
	{
		expTree = new CTree();
		expTree->AddExpTree(expNode);

		// Generate obj code
		this->objCode = expTree->GeneratePostorderInterms();

		// we don't need 'begin' and 'end'
		this->objCode.pop_front();
		this->objCode.pop_back();

		this->objCode.push_back(L"rsub");

		__asm{nop}
	}

	CUserFunction::~CUserFunction(void)
	{
		delete expTree;
	}
	
	int CUserFunction::FindSymbol(std::wstring symbol)
	{
		if( argv.find(symbol) != argv.end() )
		{
			return argv[symbol];
		}

		return -1;
	}

	void CUserFunction::SetSymbols(std::stack<int> vals)
	{
		if( vals.size() == argn.size() )
		{
			int size = vals.size();

			for(int i = 0; i < size; i++)
			{
				std::wstring symName = argn.front();
				int val = vals.top();

				argv[symName] = val;

				vals.pop();
				argn.pop_front();
			}
		}
	}

	std::list<std::wstring> CUserFunction::GetObjCode()
	{
		return objCode;
	}
}