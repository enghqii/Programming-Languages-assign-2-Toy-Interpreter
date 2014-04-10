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
		std::string m_strPostFix;		// postfix TOY code
		std::string m_strIntermediate;	// intermediate code

		// pass 2
		std::string m_strResult;
	};

}
