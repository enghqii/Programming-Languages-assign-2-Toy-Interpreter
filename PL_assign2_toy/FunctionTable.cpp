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

}
