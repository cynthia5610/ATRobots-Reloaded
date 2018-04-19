mac:

	g++ -c ../bin/atrr2.cpp
	g++ -c ../bin/atrrfunc.cpp
	g++ -c ../bin/filelib.cpp
	g++ -o atrr atrr2.o atrrfunc.o filelib.o

linux:

	g++ -c ../bin/atrr2.cpp
	g++ -c ../bin/atrrfunc.cpp
	g++ -c ../bin/filelib.cpp
	g++ -o atrr atrr2.o atrrfunc.o filelib.o


installMac:
	brew install sdl2
	brew install sdl2_image
	brew install sdl2_mixer
	brew install sdl2_ttf

installLinux:
	sudo apt-get install libsdl2-dev
	sudo apt-get install libsdl2-image-dev
	sudo apt-get install libsdl2-mixer-dev
	sudo apt-get install libsdl2-ttf-dev

clean:
	rm atrr atrr2.o atrrfunc.o filelib.o