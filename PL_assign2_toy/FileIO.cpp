#include "stdafx.h"
#include "FileIO.h"

#include <fstream>

namespace toy
{

	CFileIO::CFileIO(void)
	{
	}


	CFileIO::~CFileIO(void)
	{
	}

	/* throws -1 if there's an FSTREAM exception */
	std::wstring CFileIO::LoadSource(std::wstring pathName)
	{
		std::wifstream fin;
		fin.open(pathName.c_str());
		if(!fin)
		{
			throw -1;
		}

		std::wstring line = L"";
		std::getline(fin, line);

		return line;
	}
	
	/* throws -1 if there's an FSTREAM exception */
	bool CFileIO::SaveIntermediateCode(std::wstring pathName, std::list<std::wstring>& interms)
	{
		std::wofstream fout;
		fout.open(pathName.c_str());
		if(!fout)
		{
			throw -1;
		}

		for( auto iter : interms )
		{
			fout<<iter<<std::endl;
		}
	}
	
	/* throws -1 if there's an FSTREAM exception */
	std::list<std::wstring> CFileIO::LoadIntermediateCode(std::wstring pathName)
	{
		std::wifstream fin;
		fin.open(pathName.c_str());
		if(!fin)
		{
			throw -1;
		}

		std::list<std::wstring> interms;
		std::wstring			line = L"";
		while(std::getline(fin, line))
		{
			interms.push_back(line);
		}

		return interms;
	}
}