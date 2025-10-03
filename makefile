CXX=g++
CXXFLAGS=-Wall -Wextra -fpermissive
user.o:user.c
	$(CXX) $(CXXFLAGS) -g -c $< -o $@
queries.o:queries.c
	$(CXX) $(CXXFLAGS) -g -c $< -o $@
db.o:db.c
	$(CXX) $(CXXFLAGS) -g -c $< -o $@
main:main.c db.o queries.o user.o net.o
	$(CXX) $(CXXFLAGS) -g $^ -lpqxx -lpq -o $@
client:client.c net.h
	$(CXX) $(CXXFLAGS) -g $< -o $@
server:server.c net.h db.o user.o queries.o
	$(CXX) $(CXXFLAGS) -g $^ -lpqxx -lpq -o $@
c:c.c
	$(CXX) $(CXXFLAGS) -g $^ -lpqxx -lpq -o $@

