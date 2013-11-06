CXXSOURCES=./Log4cplus.cpp \
		   ./LoggerModule.cpp 
SOURCES=$(CXXSOURCES)
GXX=g++
CPPFLAGS=-I. -I/usr/local/include
LDFLAGS=-L.
LIBS=-llog4cplus
LOG4CPLUSWRAPPERLIB=log4cplusWrapper
target:
	$(GXX) -static -c $(SOURCES) $(CPPFLAGS) $(LDFLAGS) $(LIBS)
	ar -r lib${LOG4CPLUSWRAPPERLIB}.a *.o
	ranlib lib${LOG4CPLUSWRAPPERLIB}.a
test:
	$(GXX) -o main main.cpp $(CPPFLAGS)  $(LDFLAGS) -l${LOG4CPLUSWRAPPERLIB} $(LIBS) 
clean:
	rm *.o lib${LOG4CPLUSWRAPPERLIB}.a main YRXCore.log* -rf 
