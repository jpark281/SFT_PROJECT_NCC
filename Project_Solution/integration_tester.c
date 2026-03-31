#include <stdio.h>
#include <assert.h>
#include "truck.h"
#include "mapping.h"

void test_validate_package_box_integration() {
    struct PackageInf trucks[4] = { {0} };
    struct Map baseMap = populateMap();
    const struct Route blueRoute = getBlueRoute();
    const struct Route greenRoute = getGreenRoute();
    const struct Route yellowRoute = getYellowRoute();

    baseMap = addRoute(&baseMap, &blueRoute);
    baseMap = addRoute(&baseMap, &greenRoute);
    baseMap = addRoute(&baseMap, &yellowRoute);

    struct Point dest[] = { {10, 10}, {15, 15}, {20, 20}, {5, 5} };
    double sizes[] = { 0, 1, 3, 5, 2, 4, 6 };
    double weights[] = { 1000, 1500, 2000, 2500, 1200, 1800, 3000 };
    int expected_results[] = { 1, 1, 1, 1, 0, 0, 0 };

    for (int i = 0; i < 4; i++) {
        trucks[3].m_weight = weights[i];
        trucks[3].m_boxSize = sizes[i];

        int validate_result = validatePackageBox(sizes[i]);
        printf("Expected validation result: %d\n", expected_results[i]);
        printf("Actual validation result: %d\n", validate_result);
        assert(validate_result == expected_results[i]);

        if (validate_result == 1) {
            // Only perform lineToShip if the package box is valid
            struct Point closestPt = lineToShip(dest[i % 4], blueRoute, greenRoute, yellowRoute, trucks, baseMap);
            printf("\nExpected: A valid closest point with coordinates\n");
            printf("Actual: Closest Point (row: %d, col: %d)\n", closestPt.row, closestPt.col);
            assert(closestPt.row >= 0 && closestPt.col >= 0);
        }

        printf("Test Case 1.%d Passed\n", i + 1);
    }
}


void test_line_to_ship() {
    struct PackageInf trucks[4] = { {0} };
    struct Map baseMap = populateMap();
    const struct Route blueRoute = getBlueRoute();
    const struct Route greenRoute = getGreenRoute();
    const struct Route yellowRoute = getYellowRoute();

    baseMap = addRoute(&baseMap, &blueRoute);
    baseMap = addRoute(&baseMap, &greenRoute);
    baseMap = addRoute(&baseMap, &yellowRoute);

    struct Point dest[] = { {10, 10}, {15, 15}, {20, 20}, {5, 5} };
    double weights[] = { 1000, 1500, 2000, 2500 };
    double sizes[] = { 1, 2, 3, 4 };

    for (int i = 0; i < 4; i++) {
        trucks[3].m_weight = weights[i];
        trucks[3].m_boxSize = sizes[i];

        // Expected Result
        printf("Expected: A valid closest point with coordinates\n");

        // Actual Result
        struct Point closestPt = lineToShip(dest[i], blueRoute, greenRoute, yellowRoute, trucks, baseMap);

        // Print out the actual results to check
        printf("\nActual: Closest Point (row: %d, col: %d)\n", closestPt.row, closestPt.col);

        assert(closestPt.row >= 0 && closestPt.col >= 0);
        printf("Test Case 2.%d Passed\n", i + 1);
    }
}

void test_invalid_weight() {
    struct PackageInf pkg;
    struct PackageInf trucks[4] = { {0} };
    struct Map baseMap = populateMap();
    const struct Route blueRoute = getBlueRoute();
    const struct Route greenRoute = getGreenRoute();
    const struct Route yellowRoute = getYellowRoute();

    baseMap = addRoute(&baseMap, &blueRoute);
    baseMap = addRoute(&baseMap, &greenRoute);
    baseMap = addRoute(&baseMap, &yellowRoute);

    double weights[] = { 2600, 2700, 2800, 2900 };
    double sizes[] = { 5, 4, 3, 2 };

    for (int i = 0; i < 4; i++) {
        pkg.m_weight = weights[i];
        pkg.m_boxSize = sizes[i];
        struct Point dest = rtnPtforDest(12, returnInt('L'));

        int result = validatePackageWeight(pkg.m_weight);

        // Print expected result
        printf("Expected result: 0 (Invalid weight)\n");
        printf("Actual result: %d\n", result);

        assert(result == 0);
        printf("Test Case 3.%d Passed\n", i + 1);
    }
}

void test_invalid_destination() {
    struct PackageInf pkg;
    struct PackageInf trucks[4] = { {0} };
    struct Map baseMap = populateMap();
    const struct Route blueRoute = getBlueRoute();
    const struct Route greenRoute = getGreenRoute();
    const struct Route yellowRoute = getYellowRoute();

    baseMap = addRoute(&baseMap, &blueRoute);
    baseMap = addRoute(&baseMap, &greenRoute);
    baseMap = addRoute(&baseMap, &yellowRoute);

    double weights[] = { 20, 40, 60, 80 };
    double sizes[] = { 5, 4, 3, 2 };
    int destRows[] = { 28, 27, 26, 25 };
    char destCols[] = { 'X', 'W', 'V', 'U' };

    for (int i = 0; i < 4; i++) {
        pkg.m_weight = weights[i];
        pkg.m_boxSize = sizes[i];
        struct Point dest = rtnPtforDest(destRows[i], returnInt(destCols[i]));

        int result = isDestinationValid(&baseMap, dest.row, dest.col);

        // Print expected result
        printf("Expected result: 0 (Invalid destination)\n");
        printf("Actual result: %d\n", result);

        assert(result == 0);
        printf("Test Case 4.%d Passed\n", i + 1);
    }
}

int main_inte() {
    test_validate_package_box_integration();
    printf("\n");
    test_line_to_ship();
    printf("\n");
    test_invalid_weight();
    printf("\n");
    test_invalid_destination();
    printf("\n");

    printf("All test cases passed!\n");
    return 0;
}
