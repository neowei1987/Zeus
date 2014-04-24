#ifndef ZUES_PATTERNS_COMMAND_H
#define ZUES_PATTERNS_COMMAND_H

#include <stdio.h>

//设计模式 命令模式
//将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化；对请求排队或记录请求日志，以及支持可撤消的操作。
namespace command
{

class Receiver
{
public:
	void doAction()
	{
		printf("receiver do action\n");
	}
};


class Command 
{
public:
	Command(Receiver* pReceiver = NULL)
	{
		m_pReceiver = pReceiver;
	}

	virtual void execute() = 0;

protected:
	Receiver* m_pReceiver;
};

class ConcreteCommand : public Command
{
public:
	ConcreteCommand(Receiver* pReceiver = NULL) : Command(pReceiver) {}
	virtual void execute()
	{
		printf("command execute\n");
		if (m_pReceiver)
		{
			printf("command call receiver action\n");
			m_pReceiver->doAction();
		}
	}
};

class Invoker 
{
public:
	Invoker(Command* pCommand)
	{
		m_pCommand = pCommand;
	}
	virtual void invoke()
	{
		m_pCommand->execute();
	}
private:
	Command* m_pCommand;
};

};
#endif//ZUES_PATTERNS_FLY_WEIGHT_H

