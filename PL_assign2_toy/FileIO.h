#pragma once
#include <string>
#include <list>

namespace toy
{

	class CFileIO
	{
	public:
		CFileIO(void);
		~CFileIO(void);

		std::wstring			LoadSource(std::wstring pathName);

		bool					SaveIntermediateCode(std::wstring pathName, std::list<std::wstring>& interms);
		std::list<std::wstring> LoadIntermediateCode(std::wstring pathName);

	private:
	};

}