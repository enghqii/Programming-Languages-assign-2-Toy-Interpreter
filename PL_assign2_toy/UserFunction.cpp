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
		args(argn.size())
	{
		expTree = new CTree();
		expTree->AddExpTree(expNode);

		this->objCode = expTree->GeneratePostorderInterms();
		__asm{nop}
	}


	CUserFunction::~CUserFunction(void)
	{
		delete expTree;
	}
}