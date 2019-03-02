cmake_minimum_required(VERSION 3.5)
project(ndn_ip)

set(CMAKE_CXX_STANDARD 14)


add_executable(ndn_ip main.cpp ip2ndn_proxy.cpp connection.cpp )

target_link_libraries( ndn_ip pcap ndn-cxx boost_system boost_thread jsoncpp pthread)
