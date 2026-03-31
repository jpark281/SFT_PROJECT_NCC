
#ifndef TRUCK_H
#define TRUCK_H

#define MAX_CARGO_WEIGHT 2500  // kg

#include "mapping.h"

struct PackageInf {
    double m_weight;    // valid 1-25000 Kg.
    double m_boxSize;
};

void header();
void footer();
void input(struct PackageInf* pkg);
int isDestinationValid(const struct Map* routeMap, int destRow, int destCol);
void checkDestInput(const char* inputString, int* num, char* character);
int validatePackageWeight(double);
int validatePackageBox(double);
char returnSymb(const struct Map* routeMap, int destRow, int destCol);
int returnInt(char letter);
struct Point rtnPtforDest(int row, int col);
struct Point lineToShip(const struct Point dest, struct Route blueRoute, struct Route greenRoute, struct Route yellowRoute, struct PackageInf validPack[], const struct Map base);
void printRouteDiversion(const struct Route* diversion, const struct Route* originalRoute, const struct Point* dest);
struct Point calculateDiversionDistance(int row, char col);
struct Map routeToMap(const struct Route* route);

#endif
