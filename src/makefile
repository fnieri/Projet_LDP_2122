FLAGS=-lfltk -lfltk_images -lstdc++fs  -Wall -std=c++17
OBJDIR = build

POBJ=\
	mainwindow.o\
	canvas.o\
	cell.o\
	board.o\
	candy.o\

OBJ=$(addprefix $(OBJDIR)/, $(POBJ))

main.out : $(OBJ)
	$(CC) -o $@ $^

-include $(OBJDIR)/*.d  # include dependencies

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o : classes/%.cpp
	$(CC) -o $@ -c $< -MMD

.PHONY : clean
clean :
	rm $(OBJDIR)/*.o