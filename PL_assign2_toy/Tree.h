#pragma once

#include<string>

namespace toy
{
	namespace tree
	{
		enum NodeType
		{
			NODE_ROOT = 0,
			NODE_OPERATOR = 1,
			NODE_OPERAND = 2
		};

		class CNode
		{

		public:
			CNode(CNode* parent, NodeType type, std::string name);
			~CNode();

		private:
			NodeType	m_eType;
			std::string m_strName;

		private:

			CNode * m_pParent;

			CNode * m_pLeft;
			CNode * m_pRight;
		};
	}

	class CTree
	{
	public:
		CTree(void);
		~CTree(void);

		void addIdentifier(std::string identifier);

	private:
		tree::CNode * root;
		tree::CNode * curNode;
	};
}