#FLAGS=-lfltk -lfltk_images -lstdc++fs -Wall -std=c++17 -fconcepts -mlong-double-128 -ggdb3 -Wpedantic -Wextra -Wconversion -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -lquadmath

FLAGS=-lfltk -lfltk_images -lstdc++fs -Wall -std=c++17

CC=g++

OBJDIR = build

POBJ=\
	Display/Animation.o\
	Display/Board.o\
	Display/Canvas.o\
	Clickables/Candy.o\
	Factories/CandyFactory.o\
	Display/Cell.o\
	Factories/ClickableFactory.o\
	Clickables/Clickable.o\
	Game/EventHandler.o\
	Game/Game.o\
	Objectives/GameObjective.o\
	Clickables/Icing.o\
	Factories/IcingFactory.o\
	Factories/LevelFactory.o\
	Display/MainWindow.o\
	Game/MatchDetection.o\
	Game/MatchHandler.o\
	Objectives/ScoreCalculator.o\
	Display/Splashscreen.o\
	Clickables/Wall.o\
	Factories/WallFactory.o

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
