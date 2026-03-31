#include "pch.h"
#include "CppUnitTest.h"
extern "C" {
#include "../Project_Solution/Truck.h"
#include "../Project_Solution/mapping.h"
#include "../Project_Solution/Truck.c"
#include "../Project_Solution/mapping.c"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        // validatePackageWeight BlackBox
        TEST_METHOD(TestValidatePackageWeight)
        {
            Assert::IsTrue(validatePackageWeight(2500));
            Assert::IsTrue(validatePackageWeight(1));
            Assert::IsFalse(validatePackageWeight(3000));
            Assert::IsFalse(validatePackageWeight(-1));
        }

        // validatePackageBox 
        TEST_METHOD(TestValidatePackageBox)
        {
            Assert::IsTrue(validatePackageBox(1));
            Assert::IsTrue(validatePackageBox(3));
            Assert::IsTrue(validatePackageBox(5));
            Assert::IsFalse(validatePackageBox(2));
            Assert::IsFalse(validatePackageBox(4));
            Assert::IsFalse(validatePackageBox(6));
            //테스트 더 쓰기 0, CHARACTER
        }

        // returnInt 
        TEST_METHOD(TestReturnInt)
        {
            Assert::AreEqual(returnInt('A'), 0);
            Assert::AreEqual(returnInt('B'), 1);
            Assert::AreEqual(returnInt('a'), -1); // lowercase letter
            Assert::AreEqual(returnInt('1'), -1); // number
            Assert::AreEqual(returnInt('@'), -1); // special character

        }

        // isDestinationValid 
        //TEST_METHOD(TestIsDestinationValid)
        //{
        //    struct Map routeMap = populateMap();
        //    Assert::IsTrue(isDestinationValid(&routeMap, 1, 4)); // valid destinatin
        //    Assert::IsTrue(isDestinationValid(&routeMap, 7, 18)); // valid destinatin
        //    Assert::IsFalse(isDestinationValid(&routeMap, -1, 0)); // negative row
        //    Assert::IsFalse(isDestinationValid(&routeMap, 0, -1)); // negative column
        //    Assert::IsFalse(isDestinationValid(&routeMap, 30, 30)); // out of bounds
        //}

        // checkDestInput 
        TEST_METHOD(TestCheckDestInput)
        {
            int num;
            char character;

            checkDestInput("12A", &num, &character);
            Assert::AreEqual(num, 12);
            Assert::AreEqual(character, 'A');

            checkDestInput("5B", &num, &character);
            Assert::AreEqual(num, 5);
            Assert::AreEqual(character, 'B');

            checkDestInput("X", &num, &character);
            Assert::AreEqual(num, 0);
            Assert::AreEqual(character, 'X');

            checkDestInput("24Z", &num, &character);
            Assert::AreEqual(num, 24);
            Assert::AreEqual(character, 'Z');
        }

        // returnSymb 
        TEST_METHOD(TestReturnSymb)
        {
            struct Map routeMap = populateMap();
            char symb = returnSymb(&routeMap, 1, 1);
            Assert::AreEqual(symb, 'X'); // 1 is converted to 'X'

            symb = returnSymb(&routeMap, 0, 0);
            Assert::AreEqual(symb, ' '); // 0 is converted to ' '

            symb = returnSymb(&routeMap, 1, 4);
            Assert::AreEqual(symb, 'X'); // 1 is converted to 'X'

            symb = returnSymb(&routeMap, 3, 0);
            Assert::AreEqual(symb, ' '); // 0 is converted to ' '

            symb = returnSymb(&routeMap, 24, 24);
            Assert::AreEqual(symb, ' '); // 0 is converted to ' '
        }

    };
}