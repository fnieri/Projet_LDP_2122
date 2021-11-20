FLAGS=-lfltk -lfltk_images -lstdc++fs -Wall -std=c++17 
		#load fltk	 #Load PNG Load Current Path 
all: mainwindow

mainwindow: mainwindow.cpp
	g++ mainwindow.cpp common.h canvas.cpp canvas.h cell.cpp cell.h board.cpp board.h -o game $(FLAGS)
	./game
