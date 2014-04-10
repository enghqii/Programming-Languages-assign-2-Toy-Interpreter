#include "stdafx.h"
#include "Tree.h"

namespace toy
{
	namespace tree
	{
		CNode::CNode(CNode* parent, NodeType type, std::string name)
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
	}

	CTree::CTree(void)
	{
		root = new tree::CNode(NULL, tree::NODE_ROOT, "root");
		curNode = root;
	}


	CTree::~CTree(void)
	{
	}

}