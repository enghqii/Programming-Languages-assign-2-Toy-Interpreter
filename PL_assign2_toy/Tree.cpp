#include "stdafx.h"
#include "Tree.h"

namespace toy
{
	namespace tree
	{
		CNode::CNode(CNode* parent, NodeType type, std::wstring name)
			:m_eType(type),
			m_strName(name),
			m_pParent(parent)
		{
		}
	
		CNode::~CNode()
		{
		}

		CNode* CNode::GetLeftMost()
		{
			return m_deqChildren.front();
		}

		CNode* CNode::GetRightMost()
		{
			return m_deqChildren.back();
		}

		void CNode::AddLeft(CNode* left)
		{
			left->m_pParent = this;
			m_deqChildren.push_front(left);
		}
		
		void CNode::AddRight(CNode* right)
		{
			right->m_pParent = this;
			m_deqChildren.push_back(right);
		}

		std::wstring CNode::GetName()
		{
			return this->m_strName;
		}
	}

	CTree::CTree(void)
	{
		root = new tree::CNode(NULL, tree::NODE_ROOT, L"root");
		curNode = root;
	}


	CTree::~CTree(void)
	{
		this->Clear();
	}

	void CTree::Clear()
	{
		// TODO : Àç±ÍÀû ³ëµå ÆÄ±« ¿ä¸Á
		root->GetChildren().clear();
	}
	
	void CTree::SetExpNode(std::stack<tree::CNode *> exp)
	{
		root->GetChildren().clear();

		while(exp.empty() == false)
		{
			root->AddRight(exp.top());
			exp.pop();
		}
		__asm{nop}
	}
	
	std::list<std::wstring> CTree::GeneratePostorderInterms()
	{
		std::list<std::wstring> interms;

		for( tree::CNode * child : root->GetChildren() )
		{
			interms.push_back(L"begin");
			this->PostInterm(child, interms);
			interms.push_back(L"end");
		}

		return interms;
	}

	void CTree::PostInterm(tree::CNode *n, std::list<std::wstring>& interms)
	{
		if(n == NULL)
		{ 
			return;
		}

		for(tree::CNode * ptr : n->GetChildren())
		{
			PostInterm(ptr, interms);
		}
		
		if(n->GetType() == tree::NODE_OPERATOR)
		{
			interms.push_back(n->GetName());
		}
		else if(n->GetType() == tree::NODE_OPERAND)
		{
			std::wstring str = n->GetName();
			str = L"push " + str;
			interms.push_back(str);
		}
	}

	std::wstring CTree::GeneratePostFixString()
	{
		std::wstring postFix;
		
		for( tree::CNode * child : root->GetChildren() )
		{
			this->PostFix(child, postFix);
		}
		
		return postFix;
	}
	
	void CTree::PostFix(tree::CNode *n, std::wstring& postFix)
	{
		if(n == NULL)
		{
			return;
		}

		for(tree::CNode * ptr : n->GetChildren())
		{
			PostFix(ptr, postFix);
		}
		
		std::wstring str = L" " + n->GetName();
		postFix.append(str);
	}

}