/* soapWeatherWebServiceSoapProxy.cpp
   Generated by gSOAP 2.8.14 from weather.h

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under ONE of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#include "soapWeatherWebServiceSoapProxy.h"

WeatherWebServiceSoapProxy::WeatherWebServiceSoapProxy()
{	WeatherWebServiceSoapProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

WeatherWebServiceSoapProxy::WeatherWebServiceSoapProxy(const struct soap &_soap) : soap(_soap)
{ }

WeatherWebServiceSoapProxy::WeatherWebServiceSoapProxy(const char *url)
{	WeatherWebServiceSoapProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
	soap_endpoint = url;
}

WeatherWebServiceSoapProxy::WeatherWebServiceSoapProxy(soap_mode iomode)
{	WeatherWebServiceSoapProxy_init(iomode, iomode);
}

WeatherWebServiceSoapProxy::WeatherWebServiceSoapProxy(const char *url, soap_mode iomode)
{	WeatherWebServiceSoapProxy_init(iomode, iomode);
	soap_endpoint = url;
}

WeatherWebServiceSoapProxy::WeatherWebServiceSoapProxy(soap_mode imode, soap_mode omode)
{	WeatherWebServiceSoapProxy_init(imode, omode);
}

WeatherWebServiceSoapProxy::~WeatherWebServiceSoapProxy()
{ }

void WeatherWebServiceSoapProxy::WeatherWebServiceSoapProxy_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	soap_endpoint = NULL;
	static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope", "http://schemas.xmlsoap.org/soap/envelope/", NULL},
	{"SOAP-ENC", "http://www.w3.org/2003/05/soap-encoding", "http://schemas.xmlsoap.org/soap/encoding/", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns1", "http://WebXml.com.cn/", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap_set_namespaces(this, namespaces);
}

void WeatherWebServiceSoapProxy::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void WeatherWebServiceSoapProxy::reset()
{	destroy();
	soap_done(this);
	soap_init(this);
	WeatherWebServiceSoapProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

void WeatherWebServiceSoapProxy::soap_noheader()
{	this->header = NULL;
}

const SOAP_ENV__Header *WeatherWebServiceSoapProxy::soap_header()
{	return this->header;
}

const SOAP_ENV__Fault *WeatherWebServiceSoapProxy::soap_fault()
{	return this->fault;
}

const char *WeatherWebServiceSoapProxy::soap_fault_string()
{	return *soap_faultstring(this);
}

const char *WeatherWebServiceSoapProxy::soap_fault_detail()
{	return *soap_faultdetail(this);
}

int WeatherWebServiceSoapProxy::soap_close_socket()
{	return soap_closesock(this);
}

int WeatherWebServiceSoapProxy::soap_force_close_socket()
{	return soap_force_closesock(this);
}

void WeatherWebServiceSoapProxy::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void WeatherWebServiceSoapProxy::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}
#endif

char *WeatherWebServiceSoapProxy::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

int WeatherWebServiceSoapProxy::getSupportCity(const char *endpoint, const char *soap_action, _ns1__getSupportCity *ns1__getSupportCity, _ns1__getSupportCityResponse *ns1__getSupportCityResponse)
{	struct soap *soap = this;
	struct __ns1__getSupportCity soap_tmp___ns1__getSupportCity;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://www.webxml.com.cn/WebServices/WeatherWebService.asmx";
	if (soap_action == NULL)
		soap_action = "http://WebXml.com.cn/getSupportCity";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__getSupportCity.ns1__getSupportCity = ns1__getSupportCity;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__getSupportCity(soap, &soap_tmp___ns1__getSupportCity);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__getSupportCity(soap, &soap_tmp___ns1__getSupportCity, "-ns1:getSupportCity", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__getSupportCity(soap, &soap_tmp___ns1__getSupportCity, "-ns1:getSupportCity", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__getSupportCityResponse)
		return soap_closesock(soap);
	ns1__getSupportCityResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__getSupportCityResponse->soap_get(soap, "ns1:getSupportCityResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int WeatherWebServiceSoapProxy::getSupportProvince(const char *endpoint, const char *soap_action, _ns1__getSupportProvince *ns1__getSupportProvince, _ns1__getSupportProvinceResponse *ns1__getSupportProvinceResponse)
{	struct soap *soap = this;
	struct __ns1__getSupportProvince soap_tmp___ns1__getSupportProvince;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://www.webxml.com.cn/WebServices/WeatherWebService.asmx";
	if (soap_action == NULL)
		soap_action = "http://WebXml.com.cn/getSupportProvince";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__getSupportProvince.ns1__getSupportProvince = ns1__getSupportProvince;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__getSupportProvince(soap, &soap_tmp___ns1__getSupportProvince);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__getSupportProvince(soap, &soap_tmp___ns1__getSupportProvince, "-ns1:getSupportProvince", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__getSupportProvince(soap, &soap_tmp___ns1__getSupportProvince, "-ns1:getSupportProvince", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__getSupportProvinceResponse)
		return soap_closesock(soap);
	ns1__getSupportProvinceResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__getSupportProvinceResponse->soap_get(soap, "ns1:getSupportProvinceResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int WeatherWebServiceSoapProxy::getSupportDataSet(const char *endpoint, const char *soap_action, _ns1__getSupportDataSet *ns1__getSupportDataSet, _ns1__getSupportDataSetResponse *ns1__getSupportDataSetResponse)
{	struct soap *soap = this;
	struct __ns1__getSupportDataSet soap_tmp___ns1__getSupportDataSet;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://www.webxml.com.cn/WebServices/WeatherWebService.asmx";
	if (soap_action == NULL)
		soap_action = "http://WebXml.com.cn/getSupportDataSet";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__getSupportDataSet.ns1__getSupportDataSet = ns1__getSupportDataSet;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__getSupportDataSet(soap, &soap_tmp___ns1__getSupportDataSet);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__getSupportDataSet(soap, &soap_tmp___ns1__getSupportDataSet, "-ns1:getSupportDataSet", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__getSupportDataSet(soap, &soap_tmp___ns1__getSupportDataSet, "-ns1:getSupportDataSet", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__getSupportDataSetResponse)
		return soap_closesock(soap);
	ns1__getSupportDataSetResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__getSupportDataSetResponse->soap_get(soap, "ns1:getSupportDataSetResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int WeatherWebServiceSoapProxy::getWeatherbyCityName(const char *endpoint, const char *soap_action, _ns1__getWeatherbyCityName *ns1__getWeatherbyCityName, _ns1__getWeatherbyCityNameResponse *ns1__getWeatherbyCityNameResponse)
{	struct soap *soap = this;
	struct __ns1__getWeatherbyCityName soap_tmp___ns1__getWeatherbyCityName;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://www.webxml.com.cn/WebServices/WeatherWebService.asmx";
	if (soap_action == NULL)
		soap_action = "http://WebXml.com.cn/getWeatherbyCityName";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__getWeatherbyCityName.ns1__getWeatherbyCityName = ns1__getWeatherbyCityName;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__getWeatherbyCityName(soap, &soap_tmp___ns1__getWeatherbyCityName);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__getWeatherbyCityName(soap, &soap_tmp___ns1__getWeatherbyCityName, "-ns1:getWeatherbyCityName", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__getWeatherbyCityName(soap, &soap_tmp___ns1__getWeatherbyCityName, "-ns1:getWeatherbyCityName", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__getWeatherbyCityNameResponse)
		return soap_closesock(soap);
	ns1__getWeatherbyCityNameResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__getWeatherbyCityNameResponse->soap_get(soap, "ns1:getWeatherbyCityNameResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int WeatherWebServiceSoapProxy::getWeatherbyCityNamePro(const char *endpoint, const char *soap_action, _ns1__getWeatherbyCityNamePro *ns1__getWeatherbyCityNamePro, _ns1__getWeatherbyCityNameProResponse *ns1__getWeatherbyCityNameProResponse)
{	struct soap *soap = this;
	struct __ns1__getWeatherbyCityNamePro soap_tmp___ns1__getWeatherbyCityNamePro;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://www.webxml.com.cn/WebServices/WeatherWebService.asmx";
	if (soap_action == NULL)
		soap_action = "http://WebXml.com.cn/getWeatherbyCityNamePro";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__getWeatherbyCityNamePro.ns1__getWeatherbyCityNamePro = ns1__getWeatherbyCityNamePro;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__getWeatherbyCityNamePro(soap, &soap_tmp___ns1__getWeatherbyCityNamePro);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__getWeatherbyCityNamePro(soap, &soap_tmp___ns1__getWeatherbyCityNamePro, "-ns1:getWeatherbyCityNamePro", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__getWeatherbyCityNamePro(soap, &soap_tmp___ns1__getWeatherbyCityNamePro, "-ns1:getWeatherbyCityNamePro", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__getWeatherbyCityNameProResponse)
		return soap_closesock(soap);
	ns1__getWeatherbyCityNameProResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__getWeatherbyCityNameProResponse->soap_get(soap, "ns1:getWeatherbyCityNameProResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int WeatherWebServiceSoapProxy::getSupportCity_(const char *endpoint, const char *soap_action, _ns1__getSupportCity *ns1__getSupportCity, _ns1__getSupportCityResponse *ns1__getSupportCityResponse)
{	struct soap *soap = this;
	struct __ns1__getSupportCity_ soap_tmp___ns1__getSupportCity_;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://www.webxml.com.cn/WebServices/WeatherWebService.asmx";
	if (soap_action == NULL)
		soap_action = "http://WebXml.com.cn/getSupportCity";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__getSupportCity_.ns1__getSupportCity = ns1__getSupportCity;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__getSupportCity_(soap, &soap_tmp___ns1__getSupportCity_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__getSupportCity_(soap, &soap_tmp___ns1__getSupportCity_, "-ns1:getSupportCity", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__getSupportCity_(soap, &soap_tmp___ns1__getSupportCity_, "-ns1:getSupportCity", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__getSupportCityResponse)
		return soap_closesock(soap);
	ns1__getSupportCityResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__getSupportCityResponse->soap_get(soap, "ns1:getSupportCityResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int WeatherWebServiceSoapProxy::getSupportProvince_(const char *endpoint, const char *soap_action, _ns1__getSupportProvince *ns1__getSupportProvince, _ns1__getSupportProvinceResponse *ns1__getSupportProvinceResponse)
{	struct soap *soap = this;
	struct __ns1__getSupportProvince_ soap_tmp___ns1__getSupportProvince_;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://www.webxml.com.cn/WebServices/WeatherWebService.asmx";
	if (soap_action == NULL)
		soap_action = "http://WebXml.com.cn/getSupportProvince";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__getSupportProvince_.ns1__getSupportProvince = ns1__getSupportProvince;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__getSupportProvince_(soap, &soap_tmp___ns1__getSupportProvince_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__getSupportProvince_(soap, &soap_tmp___ns1__getSupportProvince_, "-ns1:getSupportProvince", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__getSupportProvince_(soap, &soap_tmp___ns1__getSupportProvince_, "-ns1:getSupportProvince", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__getSupportProvinceResponse)
		return soap_closesock(soap);
	ns1__getSupportProvinceResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__getSupportProvinceResponse->soap_get(soap, "ns1:getSupportProvinceResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int WeatherWebServiceSoapProxy::getSupportDataSet_(const char *endpoint, const char *soap_action, _ns1__getSupportDataSet *ns1__getSupportDataSet, _ns1__getSupportDataSetResponse *ns1__getSupportDataSetResponse)
{	struct soap *soap = this;
	struct __ns1__getSupportDataSet_ soap_tmp___ns1__getSupportDataSet_;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://www.webxml.com.cn/WebServices/WeatherWebService.asmx";
	if (soap_action == NULL)
		soap_action = "http://WebXml.com.cn/getSupportDataSet";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__getSupportDataSet_.ns1__getSupportDataSet = ns1__getSupportDataSet;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__getSupportDataSet_(soap, &soap_tmp___ns1__getSupportDataSet_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__getSupportDataSet_(soap, &soap_tmp___ns1__getSupportDataSet_, "-ns1:getSupportDataSet", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__getSupportDataSet_(soap, &soap_tmp___ns1__getSupportDataSet_, "-ns1:getSupportDataSet", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__getSupportDataSetResponse)
		return soap_closesock(soap);
	ns1__getSupportDataSetResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__getSupportDataSetResponse->soap_get(soap, "ns1:getSupportDataSetResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int WeatherWebServiceSoapProxy::getWeatherbyCityName_(const char *endpoint, const char *soap_action, _ns1__getWeatherbyCityName *ns1__getWeatherbyCityName, _ns1__getWeatherbyCityNameResponse *ns1__getWeatherbyCityNameResponse)
{	struct soap *soap = this;
	struct __ns1__getWeatherbyCityName_ soap_tmp___ns1__getWeatherbyCityName_;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://www.webxml.com.cn/WebServices/WeatherWebService.asmx";
	if (soap_action == NULL)
		soap_action = "http://WebXml.com.cn/getWeatherbyCityName";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__getWeatherbyCityName_.ns1__getWeatherbyCityName = ns1__getWeatherbyCityName;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__getWeatherbyCityName_(soap, &soap_tmp___ns1__getWeatherbyCityName_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__getWeatherbyCityName_(soap, &soap_tmp___ns1__getWeatherbyCityName_, "-ns1:getWeatherbyCityName", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__getWeatherbyCityName_(soap, &soap_tmp___ns1__getWeatherbyCityName_, "-ns1:getWeatherbyCityName", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__getWeatherbyCityNameResponse)
		return soap_closesock(soap);
	ns1__getWeatherbyCityNameResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__getWeatherbyCityNameResponse->soap_get(soap, "ns1:getWeatherbyCityNameResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int WeatherWebServiceSoapProxy::getWeatherbyCityNamePro_(const char *endpoint, const char *soap_action, _ns1__getWeatherbyCityNamePro *ns1__getWeatherbyCityNamePro, _ns1__getWeatherbyCityNameProResponse *ns1__getWeatherbyCityNameProResponse)
{	struct soap *soap = this;
	struct __ns1__getWeatherbyCityNamePro_ soap_tmp___ns1__getWeatherbyCityNamePro_;
	if (endpoint)
		soap_endpoint = endpoint;
	if (soap_endpoint == NULL)
		soap_endpoint = "http://www.webxml.com.cn/WebServices/WeatherWebService.asmx";
	if (soap_action == NULL)
		soap_action = "http://WebXml.com.cn/getWeatherbyCityNamePro";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__getWeatherbyCityNamePro_.ns1__getWeatherbyCityNamePro = ns1__getWeatherbyCityNamePro;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__getWeatherbyCityNamePro_(soap, &soap_tmp___ns1__getWeatherbyCityNamePro_);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__getWeatherbyCityNamePro_(soap, &soap_tmp___ns1__getWeatherbyCityNamePro_, "-ns1:getWeatherbyCityNamePro", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__getWeatherbyCityNamePro_(soap, &soap_tmp___ns1__getWeatherbyCityNamePro_, "-ns1:getWeatherbyCityNamePro", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__getWeatherbyCityNameProResponse)
		return soap_closesock(soap);
	ns1__getWeatherbyCityNameProResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__getWeatherbyCityNameProResponse->soap_get(soap, "ns1:getWeatherbyCityNameProResponse", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}
/* End of client proxy code */