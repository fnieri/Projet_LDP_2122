#include "GameObjective.h"


void GameObjective::createObjective() {
    srand(time(NULL));
    currentObjective = static_cast<Objective>(random() % static_cast<int>(Objective::OBJECTIVE_COUNT));
}

void GameObjective::makeNumberToAchieve() {
    switch (currentObjective) {
        case CLEAR_CANDIES: {
            auto speciality = static_cast<CandySpeciality>(rand() % ( ((int) SPECIALITY_COUNT) - 1));
            Color color = CandyFactory::generateColor();
            Candy tmp = makeObjectiveCandy(speciality, color);
            candyToRemove = make_unique<Candy>(tmp);
            makeCandyNoToAchieve(speciality);
            return;
        }
        case CLEAR_ICING:
            setNumberToAchieve(5, 15);
            return;
        case POINTS:
            setNumberToAchieve(7 * getMovesLeft(), 15   * getMovesLeft());
            return;
        default:
            return;
    }
    
}

Candy GameObjective::makeObjectiveCandy(CandySpeciality speciality, Color color) {
    return ClickableFactory::makeCandy(speciality, color);
}

void GameObjective::makeCandyNoToAchieve(CandySpeciality speciality) {
    int min = 10, max = 30;
    switch (speciality){
        case NONE:
            min = 20, max = 45;        
            break;
        case BOMB:
        case STRIPED_VERTICAL:
        case STRIPED_HORIZONTAL:
            min = 3, max = 8; 
            break; 
        case MULTICOLOR:
            min = 1, max = 2;
        default:
            break;
        }
    setNumberToAchieve(min, max);
}

//https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
void GameObjective::setNumberToAchieve(int min, int max) {
    int range = max - min + 1;
    srand(time(NULL));
    initialNumberToAchieve = rand() % range + min;
    currentNumberToAchieve = initialNumberToAchieve;
}

void GameObjective::decreaseCandyObjective(Cell cell) {
    if (candyToRemove) {
        if (isCandy(cell) && currentObjective == CLEAR_CANDIES) {
            
            CandySpeciality thisSpeciality = candyToRemove->getSpeciality();
            Color thisColor = candyToRemove->getColor();

            if (thisColor == cell.getColor()) {
                if (thisSpeciality == NONE || (thisSpeciality == cell.getSpeciality())) {
                    currentNumberToAchieve -= 1; }
            }
        }
    }
}

void GameObjective::decreaseIcingObjective() {
    if (currentObjective == CLEAR_ICING)
        currentNumberToAchieve -= 1;
}

void GameObjective::decreasePointObjective() {
    currentNumberToAchieve = initialNumberToAchieve - getScore();
}

void GameObjective::objectiveInit() {
    isComplete = false;
    setGameState(false);
    createObjective();
    makeNumberToAchieve();
}

void GameObjective::decreaseObjective(Cell cell) {
    if (isCandy(cell) && isObjective(CLEAR_CANDIES)) {
        decreaseCandyObjective(cell);
    }
    else if((isIcing(cell) && cell.getStatus() == HALF_ICING) && isObjective(CLEAR_ICING)) {
        currentNumberToAchieve -= 1;
    }
    else if (isObjective(POINTS)) {
        decreasePointObjective();
    }
    updateObjective();
}

std::string GameObjective::getObjectiveString() {
    std::string objectiveString;
    switch (currentObjective) {
    
        case CLEAR_CANDIES: {
            objectiveString = buildCandyString();
            break;
        }
        case CLEAR_ICING:
            objectiveString = "Clear " + to_string(currentNumberToAchieve) +
                " icing blocks";
            break;
        case POINTS:
            objectiveString = "Get " + to_string(currentNumberToAchieve) +
                " points";
            break;
        default:
            break;
    }
    return objectiveString;
}

std::string GameObjective::buildCandyString() {
    CandySpeciality thisSpeciality = candyToRemove->getSpeciality();
    Color thisColor = candyToRemove->getColor();
    return "Clear " + to_string(currentNumberToAchieve) + " " +
        CandyFactory::generateColorPrefix(thisColor) + 
            getSpecialityString(thisSpeciality) + " candies";

}
std::string GameObjective::getSpecialityString(CandySpeciality speciality) {
    switch (speciality){
        case NONE: return " normal";
        case STRIPED_HORIZONTAL: return " horizontal striped";
        case STRIPED_VERTICAL: return " vertical striped";
        case BOMB: return " wrapped";
        case MULTICOLOR: return " multicolor";
    default:
        return "";
    }
    
}

void GameObjective::updateObjective() {
    if (currentNumberToAchieve <= 0) {
        currentNumberToAchieve = 0;
        isComplete = true;
    } 
}

bool GameObjective::objectiveIsComplete() {
    return isComplete;
}

bool GameObjective::isObjective(Objective objective) {
    return currentObjective == objective;
}

int GameObjective::getRemainingObjective() {
    return currentNumberToAchieve;
}

Objective GameObjective::getObjective() {
    return currentObjective; 
}