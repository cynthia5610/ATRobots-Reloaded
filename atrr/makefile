mac:
	g++ -c ../files/mainMenuGUI.cpp
	g++ -c ../files/atrr2.cpp
	g++ -c ../files/atrrfunc.cpp
	g++ -c ../files/filelib.cpp
	g++ -o atrr atrr2.o atrrfunc.o filelib.o mainMenuGUI.o -I -L -lSDL2-2.0.0 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

linux:
	g++ -c ../files/mainMenuGUI.cpp
	g++ -c ../files/atrr2.cpp
	g++ -c ../files/atrrfunc.cpp
	g++ -c ../files/filelib.cpp
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