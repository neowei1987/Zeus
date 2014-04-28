#ifndef ZUES_STRUCTURES_SEGMENT_TREE_H
#define ZUES_STRUCTURES_SEGMENT_TREE_H

//用于解决线段覆盖长度的线段树

class SegmentTreeNode
{
	friend class SegmentTree;
private:
	int left_;
	int right_;	
	int cover_;
	SegmentTreeNode* leftchild_;
	SegmentTreeNode* rightchild_;
};

class SegmentTree
{
public:
	SegmentTree(int min, int max);
	~SegmentTree();

	SegmentTreeNode* build(int min, int max);
	void insert(int a, int b);
	int count();
private:
	void insert(SegmentTreeNode* node, int l, int r);
	int count(SegmentTreeNode* node);
private:
	SegmentTreeNode* root_;
};
#endif//ZUES_STRUCTURES_SEGMENT_TREE_H
