#include <stdio.h>
#include "mapping.h"
#include "truck.h"

void run_tests();

int main_tester(void) {
    run_tests();
    footer();
    return 0;
}

void run_tests() {
    struct PackageInf pkg;
    struct Map baseMap = populateMap();
    const struct Route blueRoute = getBlueRoute();
    const struct Route greenRoute = getGreenRoute();
    const struct Route yellowRoute = getYellowRoute();
    struct Map routeMap = addRoute(&baseMap, &blueRoute);
    routeMap = addRoute(&routeMap, &greenRoute);
    routeMap = addRoute(&routeMap, &yellowRoute);

    struct PackageInf trucks[4] = { {0} };
    struct Point closestPt = { 0 };

    // Test Case 1: Invalid destination input
    printf("Test Case 1: Invalid destination input\n");
    printf("Enter shipment weight, box size and destination (0 0 x to stop): 20 5 28x\n");
    if (!isDestinationValid(&routeMap, 28, returnInt('x'))) {
        printf("Result: Invalid destination\n");
    }
    else {
        printf("Result: Failure\n");
    }

    // Test Case 2: Invalid package size input
    printf("\nTest Case 2: Invalid package size input\n");
    printf("Enter shipment weight, box size and destination (0 0 x to stop): 20 4 12L\n");
    if (!validatePackageBox(4)) {
        printf("Result: Invalid size\n");
    }
    else {
        printf("Result: Failure\n");
    }

    // Test Case 3: Invalid package weight input
    printf("\nTest Case 3: Invalid package weight input\n");
    printf("Enter shipment weight, box size and destination (0 0 x to stop): 2600 5 12L\n");
    if (!validatePackageWeight(2600)) {
        printf("Result: Invalid weight (must be 1-2500 Kg.)\n");
    }
    else {
        printf("Result: Failure\n");
    }

    // Test Case 4: Valid package weight, size and destination
    printf("\nTest Case 4: Valid package weight, size and destination\n");
    printf("Enter shipment weight, box size and destination (0 0 x to stop): 20 5 12L\n");
    if (validatePackageWeight(20) && validatePackageBox(5) && isDestinationValid(&routeMap, 12, returnInt('L'))) {
        trucks[3].m_boxSize = 5;
        trucks[3].m_weight = 20;
        struct Point dest = rtnPtforDest(12, returnInt('L'));
        closestPt = lineToShip(dest, blueRoute, greenRoute, yellowRoute, trucks, baseMap);
    }
    else {
        printf("Result: Failure\n");
    }

    // Test Case 5: Multiple valid inputs
    // First input
    printf("\n\nTest Case 5: Multiple valid inputs\n");
    printf("Enter shipment weight, box size and destination (0 0 x to stop): 1000 1 8Y\n");
    if (validatePackageWeight(1000) && validatePackageBox(1) && isDestinationValid(&routeMap, 8, returnInt('Y'))) {
        trucks[3].m_boxSize = 1;
        trucks[3].m_weight = 1000;
        trucks[0].m_weight = 0;
        trucks[1].m_weight = 0;
        trucks[2].m_weight = 0;
        struct Point dest = rtnPtforDest(8, returnInt('Y'));
        closestPt = lineToShip(dest, blueRoute, greenRoute, yellowRoute, trucks, baseMap);
        printf("\n");
    }
    else {
        printf("Result: Failure\n");
    }

    // Second input
    printf("Enter shipment weight, box size and destination (0 0 x to stop): 1000 1 8Y\n");
    if (validatePackageWeight(1000) && validatePackageBox(1) && isDestinationValid(&routeMap, 8, returnInt('Y'))) {
        trucks[3].m_boxSize = 1;
        trucks[3].m_weight = 1000;
        trucks[0].m_weight = 0;
        trucks[1].m_weight = 0;
        trucks[2].m_weight = 0;
        struct Point dest = rtnPtforDest(8, returnInt('Y'));
        closestPt = lineToShip(dest, blueRoute, greenRoute, yellowRoute, trucks, baseMap);
        printf("\n");
    }
    else {
        printf("Result: Failure\n");
    }

    // Third input
    printf("Enter shipment weight, box size and destination (0 0 x to stop): 1000 1 8Y\n");
    if (validatePackageWeight(1000) && validatePackageBox(1) && isDestinationValid(&routeMap, 8, returnInt('Y'))) {
        trucks[3].m_boxSize = 1;
        trucks[3].m_weight = 1000;
        trucks[0].m_weight = 0;
        trucks[1].m_weight = 2000;
        trucks[2].m_weight = 0;
        struct Point dest = rtnPtforDest(8, returnInt('Y'));
        closestPt = lineToShip(dest, blueRoute, greenRoute, yellowRoute, trucks, baseMap);

    }
    else {
        printf("Result: Failure\n");
    }

    // Test Case 6: Normal termination
    printf("\n\nTest Case 6: Normal termination\n");
    printf("Enter shipment weight, box size and destination (0 0 x to stop): 0 0 x\n");
    if (validatePackageWeight(0) && validatePackageBox(0) && isDestinationValid(&routeMap, 0, returnInt('x' || 'X'))) {
        printf("Thanks for shipping with Seneca Polytechnic!\n");
    }


}
