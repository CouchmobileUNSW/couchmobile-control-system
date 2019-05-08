# Requires main.cpp and pid.o
# Final executable is 'pid'
main: main.cpp pid.o
	g++ main.cpp pid.o -o pid

# Requires pid.cpp
pid.o: pid.cpp
	g++ -c pid.cpp -o pid.o

# Cleanup
clean:
	rm pid.o pid