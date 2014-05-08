#pragma once

#include <map>
#include <list>
#include <string>

namespace toy
{
	class	CUserFunction;
	typedef std::map<std::wstring, CUserFunction *> FunctionMap;

	// Singleton pattern

	class CFunctionTable
	{
	public:
		static CFunctionTable* shared_table();
		~CFunctionTable(void); // dtor

		void			ClearMap();
		FunctionMap&	GetMap();
		bool			Find(std::wstring name);
		void			Add(std::wstring name, CUserFunction * func);
		CUserFunction*	GetFunction(std::wstring name);

		std::list<std::wstring> GetIntermediates();

	private:
		CFunctionTable(void); // ctor

		FunctionMap m_Defuns;
	};

}