// source: http://www.webxml.com.cn/WebServices/WeatherWebService.asmx?wsdl
//		   wsdl2h -o weather http://www.webxml.com.cn/WebServices/WeatherWebService.asmx?wsdl
//		   soapcpp2 -i -C -x weather.h -I/path/gsoap/import/

#include <iostream>
#include "WeatherWebServiceSoap.nsmap"
#include "soapWeatherWebServiceSoapProxy.h"
#include <string.h>
#include <vector>

using namespace std;

int main(int argc, const char* argv[])
{
	WeatherWebServiceSoapProxy proxy;
	_ns1__getWeatherbyCityName cityName;
	_ns1__getWeatherbyCityNameResponse cityNameResponse;

	string srcCityName = "广州";
	cityName.theCityName = &srcCityName;

	if (proxy.getWeatherbyCityName(&cityName, &cityNameResponse) == SOAP_OK)
	{
		cout << "succeeded!" << endl;

		vector<string> weatherString = cityNameResponse.getWeatherbyCityNameResult->string;
		vector<string>::iterator itr;
		for (itr = weatherString.begin(); itr != weatherString.end(); ++itr)
		{
			cout << *itr << endl;
		}
		cout << weatherString.size() << endl;
	}
	else
	{
		cout << "failed!" << endl;
	}

	return 0;
}

