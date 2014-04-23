#ifndef ZUES_PATTERNS_SINGLETON_H
#define ZUES_PATTERNS_SINGLETON_H

#include <stdio.h>

//设计模式 单例模式 
//保证一个类仅有一个实例，并提供一个访问它的全局访问点。
namespace singleton 
{
template <class T>
class Singleton
{
public:
	static T* Instance()
	{
		static T sT;
		printf("static: %p\n", &sT);
		return &sT;	
	}
};

class Manager : public Singleton<Manager>
{
public:
	void Run()
	{
		printf("run in this: %p\n", this);
	}
};
};
#endif//ZUES_PATTERNS_SINGLETON_H

