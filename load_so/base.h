class CBase
{
public:
    ~CBase();

public:
    virtual void check() = 0;
};

extern "C"
{
	typedef CBase* create_obj() { return new CBase(); }
	typedef void  destroy_obj(CBase *pBase) { delete pBase; }
}
