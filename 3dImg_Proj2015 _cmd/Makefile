CXX=g++ -std=c++11
CFLAGS=-O2 -L/usr/X11R6/lib -lm -lpthread -lX11
LDFLAGS=
EXEC=IMG3D

x86: main.cpp
	$(CXX) -o $(EXEC) src/*.cpp main.cpp $(CFLAGS)

x64: main.cpp
	$(CXX) -o $(EXEC) *.cpp $(CFLAGS)
	
clean:
	rm -f $(EXEC)
