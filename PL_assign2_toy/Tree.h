#pragma once

#include<string>
#include<stack>
#include<deque>
#include<list>

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

			CNode *				GetLeftMost();
			CNode *				GetRightMost();
			
			void				AddLeft(CNode * left);
			void				AddRight(CNode * right);

			std::wstring			GetName();
			NodeType				GetType(){ return this->m_eType; }
			std::deque<CNode *>&	GetChildren(){ return this->m_deqChildren; };

		private:
			NodeType		m_eType;
			std::wstring	m_strName;

		private:
			CNode *				m_pParent;
			std::deque<CNode *> m_deqChildren;
		};
	}

	class CTree
	{
	public:
		CTree(void);
		~CTree(void);

		void Clear();
		void AddExpTree(tree::CNode * node);

		std::list<std::wstring> GeneratePostorderInterms();
		std::wstring			GeneratePostFixString();

	private:

		// rekursiv
		void PostInterm(tree::CNode *n, std::list<std::wstring>& interms);
		void PostFix(tree::CNode *n, std::wstring& postFix);

	private:

		tree::CNode * root;
	};
}