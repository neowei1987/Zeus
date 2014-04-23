#ifndef ZUES_PATTERNS_PROTO_TYPE_H_
#define ZUES_PATTERNS_PROTO_TYPE_H_

#include <stdio.h>

//设计模式 原型模式
//用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。
namespace prototype
{

class Product
{
public:
	virtual void Run()
	{
		printf("base A run!\n");
	}
	virtual Product* Clone() = 0;
};

class ProductA : public Product
{
public:
	void Run()
	{
		printf("product A run!\n");
	}
	virtual Product* Clone()
	{
		//利用自己拷贝一个新的
		return new ProductA(*this);
	}
};

};
#endif//ZUES_PATTERNS_PROTO_TYPE_H_

