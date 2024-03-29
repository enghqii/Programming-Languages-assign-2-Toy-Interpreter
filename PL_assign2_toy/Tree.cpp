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
	}


	CTree::~CTree(void)
	{
		this->Clear();
	}

	void CTree::Clear()
	{
		// TODO : ����� ��� �ı� ���
		root->GetChildren().clear();
	}
	
	void CTree::AddExpTree(tree::CNode * node)
	{
		root->AddRight(node);
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
			// if n is not MINUS nor IF then 'call'

			std::wstring name = n->GetName();

			// 2 primitives
			if(name.compare(L"IF") != 0 && 
				name.compare(L"MINUS") != 0 )
			{
				interms.push_back(L"call " + name);
			}
			else
			{
				interms.push_back(name);
			}
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