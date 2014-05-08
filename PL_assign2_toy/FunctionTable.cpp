#include "stdafx.h"
#include "FunctionTable.h"

#include "UserFunction.h"

namespace toy
{
	CFunctionTable* CFunctionTable::shared_table(){

		static CFunctionTable * table = NULL;

		if(table == NULL){
			table = new CFunctionTable();
		}

		return table;
	}

	CFunctionTable::CFunctionTable(void)
	{
	}

	CFunctionTable::~CFunctionTable(void)
	{
	}

	void CFunctionTable::ClearMap()
	{
		m_Defuns.clear();
	}

	FunctionMap& CFunctionTable::GetMap()
	{
		return m_Defuns;
	}

	bool CFunctionTable::Find(std::wstring name)
	{
		if(m_Defuns.end() != m_Defuns.find(name))
		{
			return true;
		}

		return false;
	}
	
	void CFunctionTable::Add(std::wstring name, CUserFunction * func)
	{
		m_Defuns[name] = func;
	}

	CUserFunction* CFunctionTable::GetFunction(std::wstring name)
	{
		if(Find(name) == true)
		{
			return (m_Defuns[name]);
		}

		return 0;
	}

	std::list<std::wstring> CFunctionTable::GetIntermediates()
	{
		std::list<std::wstring> interms;

		FunctionMap::iterator iter = m_Defuns.begin();
		for(; iter != m_Defuns.end(); ++iter)
		{
			std::list<std::wstring> t = iter->second->GetObjCode();

			interms.push_back(iter->first + L" : ");
			interms.insert(interms.end(), t.begin(), t.end());

			interms.push_back(L"");
		}

		return interms;
	}
}
