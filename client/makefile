cli : 
	g++ client.cpp -o client -lpthread -ljsoncpp
ndn_cli :
	g++ ndn_client.cpp -o ndn_client -std=c++14 -lndn-cxx -lboost_system -lpthread

lcndn : 
	g++ lclient.cpp -o lcndn -lpthread

rcndn : 
	g++ rclient.cpp -o rcndn -lpthread

clean :
	rm lcndn rcndn ndn_client output
