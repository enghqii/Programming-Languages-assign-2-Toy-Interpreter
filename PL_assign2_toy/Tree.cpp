#include "stdafx.h"
#include "Tree.h"

namespace toy
{
	namespace tree
	{
		CNode::CNode(CNode* parent, NodeType type, std::wstring name)
			:m_eType(type),
			m_strName(name),
			m_pParent(parent),
			m_pLeft(NULL),
			m_pRight(NULL)
		{
		}
	
		CNode::~CNode()
		{
		}

		void CNode::SetLeft(CNode* left)
		{
			left->m_pParent = this;
			this->m_pLeft = left;
		}
		
		void CNode::SetRight(CNode* right)
		{
			right->m_pParent = this;
			this->m_pRight = right;
		}
	}

	CTree::CTree(void)
	{
		root = new tree::CNode(NULL, tree::NODE_ROOT, L"root");
		curNode = root;
	}


	CTree::~CTree(void)
	{
	}
	
}