/*
	@author: tom
	@date: 2013-07-03
	@version: 0.9
*/

/*
	@note singleton class instance
*/
class CSingleton
{
public:
	static CSingleton& Instance() {
		static CSingleton obj;
		return obj;
	}

private:
	CSingleton(arguments);
	CSingleton(CSingleton const&);
	CSingleton& operator=(CSingleton const&);
	~CSingleton();
};
