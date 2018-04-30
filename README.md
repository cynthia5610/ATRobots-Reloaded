# ATRobots Reloaded

This project's main focus is to translate the 1997 programming game, "ATRobots" to a modern computer language (C++).

# Prerequisites

Here are a few of the packages required to get the program to work on either Mac OS or Linux.

## Mac OS:

### XCode Command Line Tools
```
xcode-select --install
```

### Brew
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

## Linux

### Essentials Package
```
sudo apt-get install build-essential
```

# Getting Started

Clone the repository.
```
git clone https://github.com/LEKrensta/ATRobots-Reloaded.git
```

# Installing and Running

## Mac OS
### Install dependencies
```
brew install sdl2
brew install sdl2_image
brew install sdl2_mixer
brew install sdl2_ttf
```

## Linux
### Install dependencies
```
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-mixer-dev
sudo apt-get install libsdl2-ttf-dev
```

### Run
```
./atrr [flags]
```

## Flags
- /M [set number of matches]
- /G [enable grahpics]
- /S [disables showing source]
- /^ [disables Cnotice]

## Clean up
```
make clean
```