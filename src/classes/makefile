#FLAGS=-lfltk -lfltk_images -lstdc++fs  -Wall -std=c++17
#
#POBJ=\
#	mainwindow.o\
#	canvas.o\
#	cell.o\
#	board.o\
#	candy.o\
#
#OBJ=$(addprefix $(OBJDIR)/, $(POBJ))
#
#main.out : $(OBJ)
#	g++ -o $@ $^
#
#-include $(OBJDIR)/*.d  # include dependencies
#
#$(OBJ): | $(OBJDIR)
#
#$(OBJDIR):
#	mkdir $(OBJDIR)
#
#$(OBJDIR)/%.o : classes/%.cpp
#	g++ -o $@ -c $< -MMD
#
#.PHONY : clean

TARGET=game
OBJDIR=build
OBJ=canvas.o cell.o board.o candy.o candyfactory.o animation.o mainwindow.o
CC=g++
FLAGS=-lfltk -lfltk_images -lstdc++fs -Wall -std=c++17

all: $(TARGET)

DEPS=$(patsubst %.cpp, %.d, $(OBJ))
-include $(DEPS)
DEPFLAGS=-MMD -MF $(@:.o=.d)

game: $(OBJ)
	$(CC) $(FLAGS) -o $@ $^

%.o : %.cpp
	$(CC) $(FLAGS) -o $@ -c $< $(DEPFLAGS)
#all: game
#
#$(OBJDIR):
#	mkdir $(OBJDIR)
#
#canvas.o: classes/canvas.cpp
#	g++ -c $< -o $(OBJDIR)/$@
#
#cell.o: classes/cell.cpp
#	g++ -c $< -o $(OBJDIR)/$@
#board.o: classes/board.cpp
#	g++ -c $< -o $(OBJDIR)/$@
#
#candy.o: classes/candy.cpp
#	g++ -c $< -o $(OBJDIR)/$@
#
#candyfactory.o: classes/candyfactory.cpp
#	g++ -c $< -o $(OBJDIR)/$@
#
#animation.o: classes/animation.cpp
#	g++ -c $< -o $(OBJDIR)/$@
#
#mainwindow.o: classes/mainwindow.cpp
#	g++ -c $< -o $(OBJDIR)/$@
#
#game: canvas.o cell.o board.o candy.o candyfactory.o animation.o mainwindow.o
#	cd build && g++ mainwindow.o canvas.o cell.o board.o candy.o candyfactory.o animation.o -o ../game $(FLAGS) -MMD
#	./game
#
clean:
	rm -f $(TARGET) $(OBJ) $(DEPS)

#all: mainwindow

#mainwindow: classes/mainwindow.cpp
#	g++ classes/candyfactory.h classes/candyfactory.cpp
#classes/mainwindow.cpp classes/common.h classes/canvas.cpp
#classes/canvas.h classes/cell.cpp classes/cell.h classes/board.cpp
#classes/board.h classes/candy.cpp classes/candy.h classes/animation.cpp classes/animation.h -o game $(FLAGS)
#	./game