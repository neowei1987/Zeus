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

}
