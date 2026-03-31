
#include "pch.h"
#include "CppUnitTest.h"
extern "C" {
#include "../Project_Solution/Truck.h"
#include "../Project_Solution/mapping.h"
#include "../Project_Solution/Truck.c"
#include "../Project_Solution/mapping.c"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TruckUnitTests
{
    TEST_CLASS(TruckUnitTests)
    {
    public:

        TEST_METHOD(ValidatePackageBox)
        {
            Assert::AreEqual(validatePackageBox(1), 1);
            Assert::AreEqual(validatePackageBox(3), 1);
            Assert::AreEqual(validatePackageBox(5), 1);
            Assert::AreEqual(validatePackageBox(2), 0);
        }

        TEST_METHOD(ReturnInt)
        {
            Assert::AreEqual(returnInt('A'), 0);
            Assert::AreEqual(returnInt('B'), 1);
            Assert::AreEqual(returnInt('Z'), -1); // Test invalid string
            Assert::AreEqual(returnInt('Y'), 24);
        }

        TEST_METHOD(PopulateMap)
        {
            struct Map map = populateMap();
            Assert::AreEqual(map.numRows, MAP_ROWS);
            Assert::AreEqual(map.numCols, MAP_COLS);
            Assert::AreEqual(map.squares[0][0], 0);
            Assert::AreEqual(map.squares[1][1], 1);
            Assert::AreEqual(map.squares[6][6], 0);
            Assert::AreEqual(map.squares[7][1], 1);
        }

        TEST_METHOD(Distance)
        {
            struct Point p1 = { 0, 0 };
            struct Point p2 = { 3, 4 };
            Assert::AreEqual(distance(&p1, &p2), 5.0);

            struct Point p3 = { 1, 1 };
            struct Point p4 = { 4, 5 };
            Assert::AreEqual(distance(&p3, &p4), 5.0);

            struct Point p5 = { 0, 0 };
            struct Point p6 = { 0, 0 };
            Assert::AreEqual(distance(&p5, &p6), 0.0);

            struct Point p7 = { -1, -1 };
            struct Point p8 = { 2, 2 };
            Assert::AreEqual(distance(&p7, &p8), 4.242640687119285);
        }

        TEST_METHOD(EqPt)
        {
            struct Point p1 = { 0, 0 };
            struct Point p2 = { 0, 0 };
            struct Point p3 = { 1, 1 };
            struct Point p4 = { 0, 1 };
            Assert::AreEqual(eqPt(p1, p2), 1);
            Assert::AreEqual(eqPt(p1, p3), 0);
            Assert::AreEqual(eqPt(p1, p4), 0);
            Assert::AreEqual(eqPt(p3, p3), 1);
        }

        TEST_METHOD(GetClosestPoint)
        {
            struct Route route = { {{0, 0}, {3, 4}, {6, 8}}, 3, 0 };
            struct Point pt1 = { 4, 5 };
            Assert::AreEqual(getClosestPoint(&route, pt1), 1);

            struct Point pt2 = { 7, 9 };
            Assert::AreEqual(getClosestPoint(&route, pt2), 2);

            struct Point pt3 = { 0, 0 };
            Assert::AreEqual(getClosestPoint(&route, pt3), 0);

            struct Point pt4 = { 3, 3 };
            Assert::AreEqual(getClosestPoint(&route, pt4), 1);
        }
    };
}
