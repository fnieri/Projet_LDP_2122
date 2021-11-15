FLAGS=-lfltk  -Wall -std=c++17

all: mainwindow

mainwindow: mainwindow.cpp
	g++ mainwindow.cpp common.h canvas.cpp canvas.h cell.cpp cell.h -o game $(FLAGS)
	./game
