#pragma once

#include <string>
#include <list>
#include <map>

// fwd decl
namespace toy
{
	class CTree;
	namespace tree
	{
		class CNode;
	}
}

namespace toy
{

	class CUserFunction
	{
	public:
		CUserFunction(std::wstring name, 
			std::list<std::wstring> argn, 
			toy::tree::CNode* expNode);
		~CUserFunction(void);

	private:

		std::wstring				name;

		std::list<std::wstring>		argn;
		int							args;
		std::map<std::wstring, int> argv;

		CTree *						expTree;
		std::list<std::wstring>		objCode;

	};
}