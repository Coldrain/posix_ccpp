#include <stdio.h>

class Value
{
public:
	Value(int nVal) {
		m_nVal=nVal;
		printf("Call Value::Value(int nValue)\n");
	}
	~Value() {
		printf("Call Value::~Value()\n");
	}
	Value& operator=(int nVal)
	{
		m_nVal=nVal;
		printf("Call Value::operator=\n");
		return *this;
	}
	void Dump() {
		printf("Value::m_nVal=%d\n",m_nVal);
	}
protected:
	int m_nVal;
};

class Base
{
public:
	Base() {
		Init();
	}
	virtual ~Base() {
		Release();
	}
	virtual void Init() {
		printf("Call Base::Init()\n");
	}
	virtual void Release() {
		printf("Call Base::Release()\n");
	}
	virtual void Dump() {
		printf("Call Base::Dump()\n");
	}
};

class Derive:public Base 
{ 
public:
	Derive() {
		printf("Call Derive::Derive()\n");
	}
	// add virtual
	virtual ~Derive() {
		printf("Call Derive::~Derive()\n");
	}
	virtual void Init() {
		m_Val=2;printf("Call Derive::Init()\n");
	}
	virtual void Release() {
		printf("Call Derive::Release()\n");
	}
	virtual void Dump() {
		m_Val.Dump();
	}
protected:
	static Value m_Val;
};

Value Derive::m_Val = 0;

void DestroyObj(Base* pOb)
{
	pOb->Dump();
	delete pOb;
}

int main()
{
	Derive *pOb = new Derive;
	DestroyObj(pOb);
	return 0;
}
