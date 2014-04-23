#ifndef ZUES_PATTERNS_ABSTRCT_FACTORY_H
#define ZUES_PATTERNS_ABSTRCT_FACTORY_H

#include <stdio.h>

//设计模式 抽象工厂
//<F12>提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。
namespace abstract_factory 
{

class ProductA
{
public:
	virtual void Run()
	{
		printf("base A run!\n");
	}
};

class ProductA1 : public ProductA
{
public:
	void Run()
	{
		printf("product A1 run!\n");
	}
};

class ProductA2 : public ProductA
{
public:
	void Run()
	{
		printf("product A2 run!\n");
	}
};

class ProductB
{
public:
	virtual void Run()
	{
		printf("base B run!\n");
	}
};

class ProductB1 : public ProductB
{
public:
	void Run()
	{
		printf("product B1 run!\n");
	}
};

class ProductB2 : public ProductB
{
public:
	void Run()
	{
		printf("product B2 run!\n");
	}
};

class ProductFactory
{
public:
	virtual ProductA* createA() = 0;
	virtual ProductB* createB() = 0;
};

class Product1Factory : public ProductFactory
{
public:
	ProductA* createA(){return new ProductA1;}
	ProductB* createB(){return new ProductB1;}
};

class Product2Factory : public ProductFactory
{
public:
	ProductA* createA(){return new ProductA2;}
	ProductB* createB(){return new ProductB2;}
};

};
#endif//ZUES_PATTERNS_ABSTRCT_FACTORY_H

