#FLAGS=-lfltk -lfltk_images -lstdc++fs -Wall -std=c++17 -fconcepts -mlong-double-128 -ggdb3 -Wpedantic -Wextra -Wconversion -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -lquadmath

FLAGS=-lfltk -lfltk_images -lstdc++fs -Wall -std=c++17 -lpthread

CC=g++

OBJDIR = build

POBJ=\
	Animation.o\
	Board.o\
	Canvas.o\
	Candy.o\
	CandyFactory.o\
	Cell.o\
	ClickableFactory.o\
	Clickable.o\
	EventHandler.o\
	Game.o\
	GameObjective.o\
	Icing.o\
	IcingFactory.o\
	LevelFactory.o\
	MainWindow.o\
	MatchDetection.o\
	MatchHandler.o\
	ScoreCalculator.o\
	Splashscreen.o\
	Wall.o\
	WallFactory.o\
	main.o

OBJ=$(addprefix $(OBJDIR)/, $(POBJ))

main.out : $(OBJ)
	$(CC) -o $@ $^ $(FLAGS)

-include $(OBJDIR)/*.d  # include dependencies

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o : classes/%.cpp
	$(CC) -o $@ -c $< -MMD $(FLAGS)

.PHONY : clean
clean :
	rm $(OBJDIR)/*.o
	rm $(OBJDIR)/*.d
