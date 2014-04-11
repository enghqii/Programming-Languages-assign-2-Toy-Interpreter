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
			CNode(CNode* parent, NodeType type, std::wstring name);
			~CNode();
			
			void SetLeft(CNode * left);
			void SetRight(CNode * right);

		private:
			NodeType	m_eType;
			std::wstring m_strName;

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

	private:
		tree::CNode * root;
		tree::CNode * curNode;
	};
}