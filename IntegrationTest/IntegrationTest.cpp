#include "pch.h"
#include "CppUnitTest.h"
extern "C" {
#include "../Project_Solution/Truck.h"
#include "../Project_Solution/mapping.h"
#include "../Project_Solution/Truck.c"
#include "../Project_Solution/mapping.c"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTest
{
    TEST_CLASS(UnitTestProject)
    {
    public:

        TEST_METHOD(TestValidatePackageBoxIntegration)
        {
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
                Assert::AreEqual(expected_results[i], validate_result);

                if (validate_result == 1) {
                    struct Point closestPt = lineToShip(dest[i % 4], blueRoute, greenRoute, yellowRoute, trucks, baseMap);
                    Assert::IsTrue(closestPt.row >= 0 && closestPt.col >= 0);
                }
            }
        }

        TEST_METHOD(TestLineToShip)
        {
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

                struct Point closestPt = lineToShip(dest[i], blueRoute, greenRoute, yellowRoute, trucks, baseMap);
                Assert::IsTrue(closestPt.row >= 0 && closestPt.col >= 0);
            }
        }

        TEST_METHOD(TestInvalidWeight)
        {
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

                Assert::AreEqual(0, result);
            }
        }

        TEST_METHOD(TestInvalidDestination)
        {
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

                Assert::AreEqual(0, result);
            }
        }
    };
}
