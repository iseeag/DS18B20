all: demo

HDRS = DS18B20.h
DS_OBJS = DS18B20.o

CXXFLAGS = -Wall

$(DS_OBJS) : $(HDRS)

demo: $(DS_OBJS)
	$(CXX) -v -o $@ $^ 

clean: 
	rm -f $(DS_OBJS) demo
