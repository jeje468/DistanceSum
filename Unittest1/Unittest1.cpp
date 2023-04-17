#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <fstream>
#include <string>
#include "DistanceSum.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Unittest1
{
	struct TestInput
	{
		std::string path;
		int M, N;
		std::string result;
	};

	std::vector<TestInput> testInputs
	{
		{"test_input_1.txt", 7, 33, "105"},		//given example
		{"test_input_2.txt", 2, 2, "0"},		//one cell to find, that is the neighbour of the starting point
		{"test_input_3.txt", 4, 6, "0"},		//one cell to find, that is surrounded by barriers
		{"test_input_4.txt", 6, 8, "8"},		//two cells to find, both are can be reached from the closest side
		{"test_input_5.txt", 6, 8, "5"},		//two cells to find, only one can be reached
		{"test_input_6.txt", 10, 10, "37"}		//one cell to be found, lots of barriers, can only be reached from the oppoisite side
	};

	TEST_CLASS(Unittest1)
	{
	public:
		
		TEST_METHOD(ReadGridTest)
		{
			DistanceSum problem = DistanceSum();
			for (size_t i = 0; i < testInputs.size(); i++)
			{
				std::ifstream input_file("test_input\\" + testInputs[i].path);
				if (input_file.is_open())
				{
					problem.readGrid(input_file);
					Assert::AreEqual(testInputs[i].M, problem.getM());
					Assert::AreEqual(testInputs[i].N, problem.getN());
					Assert::AreEqual(size_t(testInputs[i].M), problem.getGrid().size());
					Assert::AreEqual(size_t(testInputs[i].N), problem.getGrid()[0].size());
				}
				else
				{
					std::cout << "Error: could not open input file" << std::endl;
				}
				input_file.close();
			}
		}

		TEST_METHOD(TestResult)
		{
			DistanceSum problem = DistanceSum();
			for (size_t i = 0; i < testInputs.size(); i++)
			{
				std::ifstream input_file("test_input\\" + testInputs[i].path);
				if (input_file.is_open())
				{
					problem.readGrid(input_file);
				}
				else
				{
					std::cout << "Error: could not open input file" << std::endl;
				}
				input_file.close();

				std::stringstream buffer;
				std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
				
				problem.dijkstra(std::cout);

				std::string d = buffer.str();
				Assert::IsTrue(d == testInputs[i].result);
			}
		}
	};
}