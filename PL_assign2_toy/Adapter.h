#pragma once
#include <string>

namespace toy
{

	class CParser;

	/***********************************
	* TOY����� �ؼ�, Dialog ���� ��� *
	***********************************/

	class CAdapter
	{
	public:
		
		CAdapter(void);
		~CAdapter(void);

	public:

		void Parse(std::wstring infix);

	private:

		CParser * m_pParser;

		// Raw
		std::wstring m_strCode;			// infix TOY code

		// pass 1
		std::wstring m_strPostFix;		// postfix TOY code
		std::wstring m_strIntermediate;	// intermediate code

		// pass 2
		std::wstring m_strResult;
	};

}
