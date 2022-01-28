#include "radVector.h"
#include "unit.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include <exception>
#include <algorithm>

#define MAX_UNITS 10000
#define MAX_VIEW_DISTANCE 30
#define MAX_CORDINATS 500

std::vector<unit> readFromFile(std::string fileName) {
    std::fstream file;
    file.open(fileName, std::fstream::in);
    int unitsNumber;
    float viewSector, viewDistance;
    file >> unitsNumber;
    if (unitsNumber < 1) {
        throw std::invalid_argument("Number of units should be 1 or more");
    }
    std::cout << "Number of units " << unitsNumber << std::endl;
    file >> viewSector;
    if (viewSector < 1 || viewSector > 360) {
        throw std::invalid_argument("The view sector can't more then 360 or less than 1");
    }
    std::cout << "The view sector " << viewSector << std::endl;
    file >> viewDistance;
    if (viewDistance <= 0) {
        throw std::invalid_argument("The view distance must be more then 0");
    }
    std::cout << "The view distance " << viewDistance << std::endl;
    std::vector<unit> units;
    units.reserve(unitsNumber);
    for (size_t i = 0; i < unitsNumber; ++i) {
        float x,y;
        file >> x >> y;
        radVector position(x,y);
        file >> x >> y;
        radVector viewDirection(x,y);
        units.push_back(unit(viewSector, viewDistance, viewDirection, position));
    }
    file.close();
    return units;
}

float getRandFloat(float range) {
    return (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) * range;
}

std::vector<unit> randUnits() {
    std::vector<unit> units;
    std::srand(std::time(nullptr));
    int unitsNumber = std::rand() % MAX_UNITS + 1;
    std::cout << "Number of units " << unitsNumber << std::endl;
    float viewSector = getRandFloat(360);
    std::cout << "The view sector " << viewSector << std::endl;
    float viewDistance = getRandFloat(MAX_VIEW_DISTANCE);
    std::cout << "The view distance " << viewDistance << std::endl;
    units.reserve(unitsNumber);
    for (size_t i = 0; i < unitsNumber; ++i) {
        float x, y;
        radVector position(0,0);
        auto comperePos = [&position] (unit un) { return un.getPosition() == position; };
        do {
            x = getRandFloat(MAX_CORDINATS);
            if (std::rand() > RAND_MAX / 2) {
                x *= -1;
            }
            y = getRandFloat(MAX_CORDINATS);
            if (std::rand() > RAND_MAX / 2) {
                y *= -1;
            }
            position = radVector(x, y);
        } while (std::find_if(units.begin(), units.end(), comperePos) != std::end(units));
        x = getRandFloat(MAX_CORDINATS);
        if (std::rand() > RAND_MAX / 2) {
            x *= -1;
        }
        y = getRandFloat(MAX_CORDINATS);
        if (std::rand() > RAND_MAX / 2) {
            y *= -1;
        }
        radVector viewDirection(x, y);
        units.push_back(unit(viewSector, viewDistance, viewDirection, position));
    }
    return units;
}

int main(int argc, const char* argv[]) {
    std::vector<unit> units;
    bool useFile = argc > 1;
    if (useFile) {
        std::string fileName = argv[1];
        try {
            units = readFromFile(fileName);
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
            return 1;
        }
    } else {
        units = randUnits();
    }
    std::vector<int> viewCount(units.size());
    for (size_t i = 0; i < units.size(); ++i) {
        for (size_t j = 0; j < units.size(); ++j) {
            if (i != j && units[i].isInView(units[j].getPosition())) {
                ++viewCount[i];
            }
        }
    }
    for (size_t i = 0; i < units.size(); ++i) {
        std::cout << "Unit " << i << "\n\tPosision " << units[i].getPosition();
        std::cout << "\n\tView direction " << units[i].getViewDirection();
        std::cout << "\n\tUnits in view " << viewCount[i] << std::endl;
    }
    return 0;
}
