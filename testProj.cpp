#include "radVector.h"
#include "unit.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
#include <exception>
#include <algorithm>
#include <thread>

std::vector<unit> readFromFile(std::string fileName, std::ostream &os) {
    std::ifstream file;
    file.open(fileName);
    int unitsNumber;
    float viewSector, viewDistance;

    file >> unitsNumber;
    if (unitsNumber < 1) {
        throw std::invalid_argument("Number of units should be 1 or more");
    }
    os << "Number of units " << unitsNumber << std::endl;

    file >> viewSector;
    if (viewSector < 1 || viewSector > 360) {
        throw std::invalid_argument("The view sector can't more then 360 or less than 1");
    }
    os << "The view sector " << viewSector << std::endl;

    file >> viewDistance;
    if (viewDistance <= 0) {
        throw std::invalid_argument("The view distance must be more then 0");
    }
    os << "The view distance " << viewDistance << std::endl;

    std::vector<unit> units;
    units.reserve(unitsNumber);
    for (size_t i = 0; i < unitsNumber; ++i) {
        float x, y;
        file >> x >> y;
        radVector position(x,y);
        file >> x >> y;
        radVector viewDirection(x,y);
        units.emplace_back(viewSector, viewDistance, viewDirection, position);
    }
    file.close();
    return units;
}

float getRandFloat(float range) {
    return (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) * range;
}

void writeOutput(std::ostream &os, const std::vector<unit>& units, const std::vector<int>& viewCount) {
    for (size_t i = 0; i < units.size(); ++i) {
        os << "Unit " << i << "\n\tPosision " << units[i].getPosition();
        os << "\n\tView direction " << units[i].getViewDirection();
        os << "\n\tUnits in view " << viewCount[i] << std::endl;
    }
}

void randUnits(std::vector<unit>& units, std::ostream &os) {
    const int maxUnits = 10000;
    const int maxViewDistance = 30;
    const int maxCordinats = 100;

    std::srand(std::time(nullptr));
    int unitsNumber = maxUnits % std::rand() + 1;
    os << "Number of units " << unitsNumber << std::endl;
    units.reserve(unitsNumber);
    float viewSector = getRandFloat(360);
    os << "The view sector " << viewSector << std::endl;
    float viewDistance = getRandFloat(maxViewDistance);
    os << "The view distance " << viewDistance << std::endl;

    for (size_t i = 0; i < unitsNumber; ++i) {
        float x, y;

        x = getRandFloat(maxCordinats);
        if (std::rand() > RAND_MAX / 2) {
            x *= -1;
        }
        y = getRandFloat(maxCordinats);
        if (std::rand() > RAND_MAX / 2) {
            y *= -1;
        }
        radVector position(x,y);

        x = getRandFloat(maxCordinats);
        if (std::rand() > RAND_MAX / 2) {
            x *= -1;
        }
        y = getRandFloat(maxCordinats);
        if (std::rand() > RAND_MAX / 2) {
            y *= -1;
        }
        radVector viewDirection(x, y);

        units.emplace_back(viewSector, viewDistance, viewDirection, position);
    }
}

int main(int argc, const char* argv[]) {
    std::vector<unit> units;
    std::string outputName = "output.txt";
    std::ofstream outputFile;
    outputFile.open(outputName);
    bool useFile = argc > 1;

    if (useFile) {
        std::string fileName = argv[1];
        try {
            units = readFromFile(fileName, outputFile);
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
            return 1;
        }
    } else {
        randUnits(units, outputFile);
    }
    
    std::vector<int> viewCount(units.size());

    auto calculateViews = [&viewCount, &units] (int startIndex, int unitsNumber) {
        if (unitsNumber + startIndex > units.size()) {
            unitsNumber = units.size() - startIndex;
        }
        for (size_t i = startIndex; i < startIndex + unitsNumber; ++i) {
            for (size_t j = 0; j < units.size(); ++j) {
                if (i != j && units[i].isInView(units[j].getPosition())) {
                    ++viewCount[i];
                }
            }
        }
    };

    int threadNum = std::thread::hardware_concurrency();
    threadNum = units.size() > threadNum ? threadNum : units.size();

    int threadUnitsNum = units.size() / threadNum;
    if (threadUnitsNum * threadNum < units.size()) {
        ++threadUnitsNum;
    }

    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;
    threads.reserve(threadNum);
    for (int i = 0; i < units.size(); i += threadUnitsNum) {
        threads.emplace_back(calculateViews, i, threadUnitsNum);
    }

    for (auto& threadToWait : threads) {
        threadToWait.join();
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(endTime - startTime);

    writeOutput(outputFile, units, viewCount);
    std::cout << "Result is written into " << outputName << std::endl;
    std::cout << "\nAlgorithm execution time: " << duration.count() << "ms." << std::endl;
    outputFile.close();
    return 0;
}
