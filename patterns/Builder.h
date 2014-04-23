#ifndef ZUES_PATTERNS_BUILDER_H
#define ZUES_PATTERNS_BUILDER_H

#include <stdio.h>

//设计模式 构造者模式 
//将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示。
namespace builder 
{

class Product
{
public:
	virtual void Run()
	{
		printf("base A run!\n");
	}
};

class Builder
{
public:
	virtual void buildPartA() = 0;
	virtual void buildPartB() = 0; 
};

class BMWBuilder : public Builder
{
public:
	virtual void buildPartA()
	{
		printf("BMW build part A\n");
	}
	virtual void buildPartB()
	{
		printf("BMW build part B\n");
	}
};

class HondaBuilder : public Builder
{
public:
	virtual void buildPartA()
	{
		printf("Honda build part A\n");
	}
	virtual void buildPartB()
	{
		printf("Honda build part B\n");
	}
};

class Director
{
public:
	Director(Builder* builder)
	{
		m_pBuilder = builder;
	}

	void construct()
	{
		m_pBuilder->buildPartA();
		m_pBuilder->buildPartB();
	}
private:
	Builder* m_pBuilder;
};

};
#endif//ZUES_PATTERNS_BUILDER_H

