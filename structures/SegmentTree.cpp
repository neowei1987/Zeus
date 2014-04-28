#include "SegmentTree.h"
#include "base/ZuesDefines.h"

SegmentTree::SegmentTree(int min, int max)
{
	root_ = build(min, max);
}

SegmentTree::~SegmentTree()
{
}

SegmentTreeNode* SegmentTree::build(int min, int max)
{
	SegmentTreeNode* node = new SegmentTreeNode();	
	node->left_ = min;
	node->right_ = max;
	node->cover_ = 0;
	node->leftchild_ = NULL;
	node->rightchild_ = NULL;
	if (min + 1 < max)
	{
		int mid = (min + max) >> 1;
		node->leftchild_ = build(min, mid);
		node->rightchild_ = build(mid, max);
	}
	return node;
}

void SegmentTree::insert(int a, int b)
{
	return insert(root_, a, b);
}

int SegmentTree::count()
{
	return count(root_);
}

void SegmentTree::insert(SegmentTreeNode* node, int l, int r)
{
	if (l == r)
	{
		return;
	}
	int m = 0;
	if (node->cover_ == 0)
	{
		if (l == node->left_ && r == node->right_)
		{
			node->cover_ = 1;
		}
		else
		{
			m = (node->left_ + node->right_) >> 1;
			if (r <= m)
			{
				insert(node->leftchild_, l, r);
			}
			else if (l >= m)
			{
				insert(node->rightchild_, l, r);
			}
			else
			{
				insert(node->leftchild_, l, m);
				insert(node->rightchild_, m, r);
			}
		}
	}
}

int SegmentTree::count(SegmentTreeNode* root)
{
	int  m = 0;
	int n = 0;
	if (root->cover_ == 1)
	{
		return   (root-> right_ - root-> left_);
	}
	else if (root-> right_ - root-> left_ == 1 )
	{
		return 0;
	}
	m = count(root->leftchild_);
	n = count(root->rightchild_);
	return m + n;
}
