#ifndef ZUES_PATTERNS_ITERATOR_H
#define ZUES_PATTERNS_ITERATOR_H

#include <stdio.h>

//设计模式 迭代器模式
//提供一种方法顺序访问一个聚合对象中各个元素，而又不需暴露该对象的内部表示。

namespace iterator 
{

class Iterator
{
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool HasNext() = 0;
};

class Container
{
public:
	virtual Iterator* getIterator() = 0;
};

class ArrayContainer : public Container
{
	friend class Iterator;
public:
	class Iterator : public iterator::Iterator //从全局范围内继承
	{
	public:
		Iterator(ArrayContainer* container)
		{
			m_pContainer = container;
		}

		virtual void First()
		{
			m_pContainer->m_iCurIndex = 0;
		}
		virtual void Next()
		{
			m_pContainer->m_iCurIndex++;
		}
		virtual bool HasNext()
		{
			return m_pContainer->m_iCurIndex < m_pContainer->m_iSize;
		}
		int operator *() //对对象解引用
		{
			return m_pContainer->m_pData[m_pContainer->m_iCurIndex];
		}
	private:
		ArrayContainer* m_pContainer;
	};
public:
	ArrayContainer(int size)
	{
		m_pData = new int[size];
		m_iSize = size;
		m_iCurIndex = 0;
	}
	virtual Iterator* getIterator()
	{
		return new ArrayContainer::Iterator(this);
	}
private:
	int* m_pData;
	int m_iSize;
	int m_iCurIndex;
};

};
#endif//ZUES_PATTERNS_ITERATOR_H

