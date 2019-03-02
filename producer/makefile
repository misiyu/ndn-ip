obj = main.o ip2ndn_proxy.o connection.o 
LIBS = -lpthread -lndn-cxx -lboost_system
CFLAGS = -std=c++14

main : $(obj)
	g++ -o main $(obj) $(CFLAGS) $(LIBS)

ip2ndn_proxy.o : ip2ndn_proxy.h

connection.o : connection.h

pro: 
	g++ -o producer producer.cpp -std=c++14 -lndn-cxx -lboost_system

con: 
	g++ -o consumer consumer.cpp -std=c++14 -lndn-cxx -lboost_system
prof: 
	g++ -o prof producer_f.cpp -std=c++14 -lndn-cxx -lboost_system

t1: 
	g++ -o t1 main.cpp -std=c++14 -lndn-cxx -lboost_system

clean :
	rm -rf *.o 
	rm -rf *.out
	rm -rf main
