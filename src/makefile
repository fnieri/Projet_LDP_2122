FLAGS=-lfltk -lfltk_images -lstdc++fs -Wall -std=c++17

CC=g++

OBJDIR = build

POBJ=\
	cell.o\
	canvas.o\
	board.o\
	candy.o\
	candyfactory.o\
	animation.o\
	mainwindow.o\
	matchdetection.o

OBJ=$(addprefix $(OBJDIR)/, $(POBJ))

main.out : $(OBJ)
	$(CC) -o $@ $^ $(FLAGS)

-include $(OBJDIR)/*.d  # include dependencies

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o : classes/%.cpp
	$(CC) -o $@ -c $< -MMD

.PHONY : clean
clean :
	rm $(OBJDIR)/*.o