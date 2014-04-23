#ifndef ZUES_PATTERNS_FACTORY_H
#define ZUES_PATTERNS_FACTORY_H

#include <stdio.h>

//设计模式 工厂
//定义一个用于创建对象的接口，让子类决定实例化哪一个类。Factory Method 使一个类的实例化延迟到其子类。
namespace factory 
{

class Product
{
public:
	virtual void Run()
	{
		printf("base run!\n");
	}
};

class ProductA : public Product
{
public:
	void Run()
	{
		printf("product A run!\n");
	}
};

class ProductFactory
{
public:
	virtual Product* create() = 0;
};

class ProductAFactory : public ProductFactory
{
public:
	Product* create(){return new ProductA;}
};

};
#endif//ZUES_PATTERNS_FACTORY_H

