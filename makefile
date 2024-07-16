# The target executable name
output: main.o linkedlist.o polycalculator.o
	g++ main.o linkedlist.o polycalculator.o -o output

# Compilation rule for main.cpp
main.o: main.cpp
	g++ -c main.cpp

# Compilation rule for linkedlist.cpp
linkedlist.o: linkedlist.cpp linkedlist.h
	g++ -c linkedlist.cpp

# Compilation rule for polycalculator.cpp
polycalculator.o: polycalculator.cpp polycalculator.h
	g++ -c polycalculator.cpp

# Clean rule to remove object files and the executable
clean:
	rm main.o linkedlist.o polycalculator.o output