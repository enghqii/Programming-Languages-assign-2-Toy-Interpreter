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

		CNode* CNode::GetLeft()
		{
			return m_pLeft;
		}

		CNode* CNode::GetRight()
		{
			return m_pRight;
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
		// TODO : Àç±ÍÀû ³ëµå ÆÄ±« ¿ä¸Á
	}
	
	void CTree::SetExpNode(tree::CNode * exp)
	{
		root->SetLeft(exp);
	}
	
	std::list<std::wstring> CTree::GeneratePostorderInterms()
	{
		std::list<std::wstring> interms;
		this->PostInterm(root->GetLeft(), interms);

		return interms;
	}

	std::wstring CTree::GeneratePostFixString()
	{
		std::wstring postFix;
		this->PostFix(root->GetLeft(), postFix);
		return postFix;
	}

	void CTree::PostInterm(tree::CNode *n, std::list<std::wstring>& interms)
	{
		if(n == NULL)
		{ 
			return;
		}
		
		PostInterm(n->GetLeft(), interms);
		PostInterm(n->GetRight(), interms);
		
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

	void CTree::PostFix(tree::CNode *n, std::wstring& postFix)
	{
		if(n == NULL)
		{
			return;
		}

		PostFix(n->GetLeft(), postFix);
		PostFix(n->GetRight(), postFix);
		
		std::wstring str = L" " + n->GetName();
		postFix.append(str);
	}

	void CTree::OutputInorderTraverse()
	{
		this->Inorder(root->GetLeft());	
		OutputDebugString(L"\n");
	}
	void CTree::Inorder(tree::CNode *n)
	{
		if(n == NULL)
		{ 
			return;
		}
		Inorder(n->GetLeft());
		OutputDebugString(n->GetName().c_str());
		OutputDebugString(L" ");
		Inorder(n->GetRight());
	}

	void CTree::OutputPostorderTraverse()
	{
		this->Postorder(root->GetLeft());
		OutputDebugString(L"\n");
	}
	void CTree::Postorder(tree::CNode *n)
	{
		if(n == NULL)
		{ 
			return;
		}
		Postorder(n->GetLeft());
		Postorder(n->GetRight());
		OutputDebugString(n->GetName().c_str());
		OutputDebugString(L" ");
	}

}