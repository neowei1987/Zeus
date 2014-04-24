#include "Factory.h"
#include "AbstrctFactory.h"
#include "Builder.h"
#include "ProtoType.h"
#include "Singleton.h"
#include "Adapt.h"
#include "Bridge.h"
#include "Composite.h"
#include "Decorator.h"
#include "Proxy.h"
#include "TemplateMethod.h"
#include "ChainOfResponsibility.h"
#include "FlyWeight.h"
#include "Command.h"
#include "Observer.h"
#include "Strategy.h"
#include "State.h"
#include "Iterator.h"
#include "Memento.h"
#include "Visitor.h"

int PatternsTestEntry(int argc, char* argv[])
{
	{
		using namespace factory;
		ProductFactory* pf = new ProductAFactory();
		Product* p = pf->create();
		p->Run();
	};
	{
		using namespace abstract_factory;
		ProductFactory* pf = new Product1Factory();
		ProductA* pa = pf->createA();
		ProductB* pb = pf->createB();
		pa->Run();
		pb->Run();
	};
	{
		using namespace builder;
		BMWBuilder* builder = new BMWBuilder();
		Director* d = new Director(builder);
		d->construct();
	}

	{
		using namespace prototype;
		Product* p = new ProductA();
		Product* p2 = p->Clone();
		p2->Run();
	}

	{
		using namespace singleton; 
		Manager::Instance()->Run();
	}

	{
		using namespace adapt;
		Target* t = new ClassAdapter();
		t->Request();
		Adaptee* e = new Adaptee();
		t = new ObjectAdapter(e);
		t->Request();
	}

	{
		using namespace bridge;
		Logger* logger = new Logger(new LoggerImpByA);
		logger->doWork();
	}

	{
		using namespace composite;
		Compontent* leaf1 = new Leaf();
		Compontent* leaf2 = new Leaf();
		Compontent* c1 = new Composite();
		c1->add(leaf1);
		c1->add(leaf2);
		Compontent* c2 = new Composite();
		c2->add(new Leaf());
		c2->add(c1);
		c2->doWork();
	}

	{
		using namespace decorator;
		Compontent* c = new ConcreateCompontent();
		c->doWork();
		Compontent* one = new OneDecorator(c);
		one->doWork();
		Compontent* two = new TwoDecorator(one);
		two->doWork();
	}

	{
		using namespace proxy;
		Subject* proxy = new SubjectProxy();
		proxy->Request();
	}

	{
		using namespace template_method;
		People* p = new MondayPeople();
		p->doWork();
	}

	{
		using namespace chain_of_responsibility;
		Handler* h1 = new ConcreteHandler1();
		Handler* h2 = new ConcreteHandler2(h1);
		h2->Request();
	}

	{
		using namespace flyweight;
		FlyWeightFactory* ff = new FlyWeightFactory();
		FlyWeight* f = ff->get(0);
		f->Run();
		f = ff->get(0);
		f->Run();
	}

	{
		using namespace command;
		Command* cmd = new ConcreteCommand(new Receiver());
		Invoker invoker(cmd);
		invoker.invoke();	
	}

	{
		using namespace observer;
		Observer* o1 = new OneObserver();
		Observer* o2 = new TwoObserver();
		Subject* s = new ConcreteSubject();
		s->addObserver(o1);
		s->addObserver(o2);
		s->setState(10);
		s->notify();
	}

	{
		using namespace strategy;
		Context c(new MyStrategy);
		c.doJob();
	}

	{
		using namespace state;
		Context c(new StateA()); //设置开始状态
		c.Request();
		c.Request();
		c.Request();
	}

	{
		using namespace iterator;
		ArrayContainer c(4);
		ArrayContainer::Iterator& it = *(c.getIterator());
		for (it.First(); it.HasNext(); it.Next())
		{
			printf("iterator: %d\n", *it);
		}
	}

	{
		using namespace memento;
		Originator originator;
		originator.setState("old state");
		originator.printState();
		Memento* m = originator.createMemento(); //设置备忘录
		originator.setState("new state");
		originator.printState();
		originator.recoverState(m); //恢复
		originator.printState();
	}

	{
		using namespace visitor;
		Visitor* v = new OneVisitor();
		Element* e = new ElementA();
		e->Accept(v);
	}
}

