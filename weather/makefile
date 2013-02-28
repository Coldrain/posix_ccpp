TARGET=weather
INCLUDE=-I./
DEBUG=-g
OBJS=main.o soapC.o soapWeatherWebServiceSoapProxy.o stdsoap2.o
CCC=g++

$(TARGET):$(OBJS)
	$(CCC) $^ -o $@ $(DEBUG)

.SUFFIXES: .o .cpp
.cpp.o:
	$(CCC) -c $(INCLUDE) $(DEBUG) -o $@ $<

.PHONY:clean
clean:
	rm -rf $(OBJS) $(TARGET) *~


