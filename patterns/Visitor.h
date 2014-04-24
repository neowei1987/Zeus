#ifndef ZUES_PATTERNS_VISITOR_H
#define ZUES_PATTERNS_VISITOR_H

#include <stdio.h>

//设计模式 访问者模式
//表示一个作用于某对象结构中的各元素的操作。它使你可以在不改变各元素的类的前提下定义作用于这些元素的新操作。
namespace visitor 
{

class Visitor;
class Element
{
public:
	virtual void Accept(Visitor* pVistor) = 0;
};

class ElementA : public Element
{
public:
	void Accept(Visitor* pVistor);
};

class ElementB : public Element
{
public:
	void Accept(Visitor* pVistor);
};

class Visitor
{
public:
	virtual void visitElementA(ElementA* e) = 0;
	virtual void visitElementB(ElementB* e) = 0;
};

void ElementA::Accept(Visitor* pVistor) 
{
	pVistor->visitElementA(this);
}
void ElementB::Accept(Visitor* pVistor) 
{
	pVistor->visitElementB(this);
}

class OneVisitor : public Visitor
{
public:
	virtual void visitElementA(ElementA* e)
	{
		printf("visit A element in one way!\n");	
	}

	virtual void visitElementB(ElementB* e)
	{
		printf("visit B element in one way!\n");	
	}
}; 

class TwoVisitor : public Visitor
{
public:
	virtual void visitElementA(ElementA* e)
	{
		printf("visit A element in two way!\n");	
	}

	virtual void visitElementB(ElementB* e)
	{
		printf("visit B element in two way!\n");	
	}
}; 

};
#endif//ZUES_PATTERNS_VISITOR_H

