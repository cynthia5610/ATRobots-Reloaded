mac:
	g++ -c -std=c++17 ../bin/mainMenuGUI.cpp
	g++ -c ../bin/atrr2.cpp
	g++ -c ../bin/atrrfunc.cpp
	g++ -c ../bin/filelib.cpp
	g++ -o atrr atrr2.o atrrfunc.o filelib.o mainMenuGUI.o -I -L -lSDL2-2.0.0 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

linux:
	g++ -c ../bin/mainMenuGUI.cpp
	g++ -c ../bin/atrr2.cpp
	g++ -c ../bin/atrrfunc.cpp
	g++ -c ../bin/filelib.cpp
	g++ -o atrr atrr2.o atrrfunc.o filelib.o mainMenuGUI.o -I include -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf


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