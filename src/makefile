 FLAGS=-lfltk -lfltk_images -lstdc++fs -Wall -std=c++17 
		#load fltk	 #Load PNG Load Current Path 
all: mainwindow

mainwindow: classes/mainwindow.cpp
	g++ classes/mainwindow.cpp classes/common.h classes/canvas.cpp classes/canvas.h classes/cell.cpp classes/cell.h classes/board.cpp classes/board.h classes/candy.cpp classes/candy.h -o game $(FLAGS)
	./game
