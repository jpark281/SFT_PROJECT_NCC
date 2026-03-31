#include "pch.h"
#include "CppUnitTest.h"
extern "C" {
#include "../Project_Solution/Truck.h"
#include "../Project_Solution/mapping.h"
#include "../Project_Solution/Truck.c"
#include "../Project_Solution/mapping.c"
}


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
    TEST_CLASS(AcceptanceTester)
    {
    public:

        TEST_METHOD(TestInvalidDestination)
        {
            struct Map baseMap = populateMap();
            const struct Route blueRoute = getBlueRoute();
            const struct Route greenRoute = getGreenRoute();
            const struct Route yellowRoute = getYellowRoute();
            struct Map routeMap = addRoute(&baseMap, &blueRoute);
            routeMap = addRoute(&routeMap, &greenRoute);
            routeMap = addRoute(&routeMap, &yellowRoute);

            Assert::IsFalse(isDestinationValid(&routeMap, 28, returnInt('x')));
        }

        TEST_METHOD(TestInvalidPackageSize)
        {
            Assert::IsFalse(validatePackageBox(4));
        }

        TEST_METHOD(TestInvalidPackageWeight)
        {
            Assert::IsFalse(validatePackageWeight(2600));
        }

        TEST_METHOD(TestValidPackage)
        {
            struct Map baseMap = populateMap();
            const struct Route blueRoute = getBlueRoute();
            const struct Route greenRoute = getGreenRoute();
            const struct Route yellowRoute = getYellowRoute();
            struct Map routeMap = addRoute(&baseMap, &blueRoute);
            routeMap = addRoute(&routeMap, &greenRoute);
            routeMap = addRoute(&routeMap, &yellowRoute);

            struct PackageInf trucks[4] = { {0} };
            trucks[3].m_boxSize = 5;
            trucks[3].m_weight = 20;
            struct Point dest = rtnPtforDest(12, returnInt('L'));
            struct Point closestPt = lineToShip(dest, blueRoute, greenRoute, yellowRoute, trucks, baseMap);

            Logger::WriteMessage("Testing validatePackageWeight...");
            Assert::IsTrue(validatePackageWeight(20), L"validatePackageWeight failed.");

            Logger::WriteMessage("Testing validatePackageBox...");
            Assert::IsTrue(validatePackageBox(5), L"validatePackageBox failed.");

            Logger::WriteMessage("Testing lineToShip...");
            Assert::IsTrue(closestPt.row >= 0 && closestPt.col >= 0, L"lineToShip failed.");
        }


        TEST_METHOD(TestMultipleValidInputs)
        {
            struct Map baseMap = populateMap();
            const struct Route blueRoute = getBlueRoute();
            const struct Route greenRoute = getGreenRoute();
            const struct Route yellowRoute = getYellowRoute();
            struct Map routeMap = addRoute(&baseMap, &blueRoute);
            routeMap = addRoute(&routeMap, &greenRoute);
            routeMap = addRoute(&routeMap, &yellowRoute);

            struct PackageInf trucks[4] = { {0} };
            trucks[3].m_boxSize = 1;
            trucks[3].m_weight = 1000;

            struct Point dest = rtnPtforDest(8, returnInt('Y'));
            struct Point closestPt = lineToShip(dest, blueRoute, greenRoute, yellowRoute, trucks, baseMap);

            Assert::IsTrue(validatePackageWeight(1000));
            Assert::IsTrue(validatePackageBox(1));
            Assert::IsTrue(closestPt.row >= 0 && closestPt.col >= 0);

            // Repeat for second and third inputs
            trucks[3].m_weight = 1000;
            closestPt = lineToShip(dest, blueRoute, greenRoute, yellowRoute, trucks, baseMap);
            Assert::IsTrue(closestPt.row >= 0 && closestPt.col >= 0);

            trucks[3].m_weight = 1000;
            trucks[1].m_weight = 2000;
            closestPt = lineToShip(dest, blueRoute, greenRoute, yellowRoute, trucks, baseMap);
            Assert::IsTrue(closestPt.row >= 0 && closestPt.col >= 0);
        }

        //TEST_METHOD(TestNormalTermination)
        //{
        //    struct Map baseMap = populateMap();
        //    const struct Route blueRoute = getBlueRoute();
        //    const struct Route greenRoute = getGreenRoute();
        //    const struct Route yellowRoute = getYellowRoute();
        //    struct Map routeMap = addRoute(&baseMap, &blueRoute);
        //    routeMap = addRoute(&routeMap, &greenRoute);
        //    routeMap = addRoute(&routeMap, &yellowRoute);

        //    Assert::IsTrue(validatePackageWeight(0));
        //    Assert::IsTrue(validatePackageBox(0));
        //}
    };
}
