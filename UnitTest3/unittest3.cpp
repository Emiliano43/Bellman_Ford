#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Progr3/Algorithm_Forda.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest3
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(test_set_data)
		{
			Algorithm_Forda path;
			try {
				path.set_data("wrong_test_file.txt");
			}
			catch (runtime_error e) {
				Assert::AreEqual(e.what(), "File is not found");
			}
			path.set_data("C:\\Users\\enazy\\source\\repos\\Progr3\\UnitTest3\\test.txt");
		}
		TEST_METHOD(test_find_way) {
			Algorithm_Forda way;
			try {
				way.find_way(0, 5);
			}
			catch (runtime_error e) {
				Assert::AreEqual(e.what(), "Data is not set");
			}
			path.set_data("C:\\Users\\enazy\\source\\repos\\Progr3\\UnitTest3\\test.txt");
			try {
				way.find_way(0, 5);
			}
			catch (invalid_argument e) {
				Assert::AreEqual(e.what(), "Number of city is incorrect");
			}
			List<int> flight = way.return_way(0, 2);
			Assert::AreEqual(flight.at(0), 0);
			Assert::AreEqual(flight.at(1), 1);
			Assert::AreEqual(flight.at(2), 2);
		}
	};
}
