#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<stack>
#include<queue>
using namespace std;
template<class T>
struct BinarytreeNode
{
	BinarytreeNode(const T &x)
	:_data(x)
	, _left(NULL)
	, _right(NULL)
	{}
	T _data;
	BinarytreeNode<T>*_left;
	BinarytreeNode<T>*_right;
};
template<class T>
class Binarytree
{
public:
	typedef BinarytreeNode<T>Node;
	Binarytree()
		:_root(NULL)
	{}
	Binarytree(const T *a, size_t size)
	{
		size_t index = 0;
		_root = _creatBinarytree(a, size, index);
	}
	~Binarytree()
	{
		_Destroy(_root);
		_root = NULL;
	}
	Binarytree(const Binarytree<T> &s)
	{
		_root = _copy(s._root);
	}
	Binarytree &operator=(Binarytree<T> s)
	{
		swap(_root, s._root);
		return *this;
	}
	void Prevorder()
	{
		_prevorder(_root);
		cout << endl;
	}
	void Prevorder_nor()
	{
		stack<BinarytreeNode<T>*>s;
		if (_root)
		{
			s.push(_root);
		}
		while (!s.empty())
		{
			BinarytreeNode<T>*top = s.top();
			s.pop();
			cout << top->_data << " ";
			if (top->_right)
			{
				s.push(top->_right);
			}
			if (top->_left)
			{
				s.push(top->_left);
			}
		}
		cout << endl;
	}
	void Inorder()
	{
		_inorder(_root);
		cout << endl;
	}

	void Inorder_nor()
	{
		stack<BinarytreeNode<T>*> s;
		BinarytreeNode<T>*cur = _root;
		while (cur || !s.empty())
		{
			//左孩子全部入栈；
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			//右孩子入栈
			if (!s.empty())
			{
				BinarytreeNode<T>*top = s.top();
				s.pop();
				cout << top->_data << " ";
				cur = top->_right;
			}
		}
		cout << endl;
	}
	void Postorder()
	{
		_postorder(_root);
		cout << endl;
	}
	void Postorder_nor()
	{
		stack<BinarytreeNode<T>*>s;
		BinarytreeNode<T>*cur = _root;
		BinarytreeNode<T>*previsited = NULL;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			BinarytreeNode<T>*top = s.top();
			if (top->_right == NULL || top->_right == previsited)
			{
				cout << top->_data << " ";
				previsited = top;
				s.pop();
			}
			else
			{
				cur = top->_right;
			}
		}
		cout << endl;
	}
	size_t Size()
	{
		size_t size = 0;
		_size(_root, size);
		return size;
	}
	int Depth()
	{
		return _depth(_root);
	}
	void Levelorder()
	{
		queue<BinarytreeNode<T>*> q;
		if (_root)
			q.push(_root);
		while (!q.empty())
		{
			BinarytreeNode<T>*front = q.front();
			cout << front->_data << " ";
			q.pop();
			if (front->_left)
			{
				q.push(front->_left);
			}
			if (front->_right)
			{
				q.push(front->_right);
			}
		}
		cout << endl;
	}
	BinarytreeNode<T>* Find(const T &x)
	{
		return _find(_root, x);
	}
	int GetleafNum()
	{
		int num = 0;
		_getleafnum(_root, num);
		return num;
	}
protected:
	BinarytreeNode<T>*_creatBinarytree(const T*a, size_t size, size_t &index)
	{
		BinarytreeNode<T>*root = NULL;
		if (index < size && a[index] != '#')
		{
			root = new BinarytreeNode<T>(a[index]);
			root->_left = _creatBinarytree(a, size, ++index);
			root->_right = _creatBinarytree(a, size, ++index);
		}
		return root;
	}
	BinarytreeNode<T>*_copy(BinarytreeNode<T>*root)
	{
		if (root == NULL)
		{
			return NULL;
		}
		BinarytreeNode<T>*newroot = new BinarytreeNode<T>(_root->_data);
		newroot->_left = new BinarytreeNode<T>(_root->_left);
		newroot->right = new BinarytreeNode<T>(_root->_right);
		return newroot;
	}
	void _Destroy(BinarytreeNode<T>*root)
	{
		if (root == NULL)//为空
		{
			return;
		}
		if (root->_left == NULL || root->_right == NULL)//一个节点
		{
			delete root;
			root = NULL;
			return;
		}
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}
	void _prevorder(BinarytreeNode<T>*root)
	{
		if (root == NULL)
			return;
		cout << root->_data << " ";
		_prevorder(root->_left);
		_prevorder(root->_right);
	}
	void _inorder(BinarytreeNode<T>*root)
	{
		if (root == NULL)
			return;

		_inorder(root->_left);
		cout << root->_data << " ";
		_inorder(root->_right);
	}
	void _postorder(BinarytreeNode<T>*root)
	{
		if (root == NULL)
		{
			return;
		}
		_postorder(root->_left);
		_postorder(root->_right);
		cout << root->_data << " ";

	}
	BinarytreeNode<T>* _find(BinarytreeNode<T>*root, const T &x)
	{
		if (root == NULL)
		{
			return NULL;
		}
		else if (x == root->_data)
		{
			return root;
		}
		else
		{
			BinarytreeNode<T>*ret = _find(root->_left, x);
			if (ret)
				return ret;
			else
				return _find(root->_right, x);
		}
	}
	void _size(BinarytreeNode<T>*root, size_t &size)
	{
		if (root == NULL)
			return;
		else
			++size;
		_size(root->_left, size);
		_size(root->_right, size);
	}
	int _depth(BinarytreeNode<T>*root)
	{
		if (root == NULL)
			return 0;
		int leftdepth = _depth(root->_left);
		int rightdepth = _depth(root->_right);
		return leftdepth > rightdepth ? leftdepth + 1 : rightdepth + 1;
	}
	void _getleafnum(BinarytreeNode<T>*root, int &num)
	{
		if (root == NULL)
		{
			return;
		}
		if (root->_right == NULL && root->_left == NULL)
		{
			++num;
			return;
		}
		_getleafnum(root->_left, num);
		_getleafnum(root->_right, num);
	}
	public:
   //求第K层节点个数
		int _GetLevelLeafNum(const BinaryTreeNode<T> * root, const int k)
		{
			static int count = 0;
			if (root == NULL || k < 0)
			{
				return 0;
			}
			if (k == 0)
			{
				count++;
			}
			_GetLevelLeafNum(root->_left, k - 1);
			_GetLevelLeafNum(root->_right, k - 1);
			return count;
		}
		//判断一颗二叉树是不是平衡树
		int Isbalance(Node*root)
		{
			if (root == NULL)
			{
				return 0;
			}
			int left = Isbalance(root->_left);
			if (left < 0)
			{
				return -1;
			}
			int right = Isbalance(root->_right);
			if (right < 0)
			{
				return -1;
			}
			if (abs(left - right)>1)
			{
				return -1;
			}
			return left > right ? left + 1 : right + 1;
		}
		//求一颗二叉树的镜像
		void Tomirror(Node*root)
		{
			if (root == NULL)
			{
				return;
			}
			swap(root->_left, root->_right);
			Tomirror(root->_left);
			Tomirror(root->_right);
		}
	//求两个节点的最近的公共祖先
	Node* FindRecentCommonAncestor(const T&p,const T&q)
	{
		return _FindRecentCommonAncestor(_root,p,q);
	}
	Node*_FindRecentCommonAncestor(Node*root,const T&p,const T&q)
	{
		Node*m, *n;
		if (root == NULL)
		{
			return NULL;
		}
		if (p==root->_data||q==root->_data)
		{
			return root;
		}
		else
		{
			//找要求的两个节点的位置
			m = _FindRecentCommonAncestor(root->_left, p, q);
			n = _FindRecentCommonAncestor(root->_right, p, q);
		}
		if (m&&n)//如果找两个节点到了说明在左右两个子树上，则最近的祖先节点就是根节点
		{
			return root;
		}
		else
			return (n != NULL) ? n : m;//如果有一个没找到说明在一个子树上
	}
	//求二叉树中最远两个节点的距离
	int longestPath(int& maxLeft, int& maxRight, int& maxLen)
	{
		return _longestPath(_root, maxLeft, maxRight, maxLen);
	}
	int  _longestPath(Node* pRoot, int& maxLeft, int& maxRight, int& maxLen)
	{
		if (pRoot == NULL)
		{
			maxLeft = 0;
			maxRight = 0;
			maxLen = 0;
			return 0;
		}

		int maxLeft_1, maxLeft_2, maxRight_1, maxRight_2;
		_longestPath(pRoot->_left, maxLeft_1, maxRight_1, maxLen);
		_longestPath(pRoot->_right, maxLeft_2, maxRight_2, maxLen);

		maxLeft = 1 + max(maxLeft_1, maxRight_1);
		maxRight = 1 + max(maxLeft_2, maxRight_2);

		maxLen = max(maxLeft, maxRight) + 1;
	}
	
private:
	BinarytreeNode<T>* _root;
};
