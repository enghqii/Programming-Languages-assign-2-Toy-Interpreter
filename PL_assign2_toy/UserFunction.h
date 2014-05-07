#pragma once

#include <stack>
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

		/* 
		returns Symbol value if exists
		returns -1 if not exists
		*/
		int							FindSymbol(std::wstring symbol);

		int							GetArgc()		{ return argc; }
		std::map<std::wstring, int> GetSymbolTable(){ return argv; }

		void						SetSymbols(std::stack<int> vals);

	private:

		std::wstring				name;

		std::list<std::wstring>		argn;
		int							argc;
		std::map<std::wstring, int> argv;

		CTree *						expTree;
		std::list<std::wstring>		objCode;

	};
}