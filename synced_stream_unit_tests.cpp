#include "pch.h"
#include "CppUnitTest.h"
#include "../thread_pool.h"
#include <fstream>
#include <thread>
#include <regex>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SyncedStreamUnitTests
{
	TEST_CLASS(SyncedStreamUnitTests)
	{
	public:

		TEST_METHOD(ConstructorNoArguments)
		{
			synced_stream sync_stream;

			Assert::AreEqual(sync_stream.get_num_streams(), (size_t)1);
		}

		TEST_METHOD(ConstructorTwoArguments)
		{
			std::ofstream log_file("log.txt");

			synced_stream sync_stream(&std::cout, &log_file);

			Assert::AreEqual(sync_stream.get_num_streams(), (size_t)2);
		}

		TEST_METHOD(AddExistingStream)
		{
			std::ofstream log_file("log.txt");

			synced_stream sync_stream(&std::cout, &log_file);

			sync_stream.add_stream(&std::cout);

			Assert::AreEqual(sync_stream.get_num_streams(), (size_t)2);

			sync_stream.add_stream(&log_file);

			Assert::AreEqual(sync_stream.get_num_streams(), (size_t)2);
		}
		TEST_METHOD(AddNewStream)
		{
			std::ofstream log_file("log.txt");
			synced_stream sync_stream(&std::cout, &log_file);

			std::ofstream log_file2("log2.txt");
			sync_stream.add_stream(&log_file2);
			Assert::AreEqual(sync_stream.get_num_streams(), (size_t)3);
		}

		TEST_METHOD(RemoveExistingStream)
		{
			std::ofstream log_file("log.txt");
			synced_stream sync_stream(&std::cout, &log_file);

			sync_stream.remove_stream(&log_file);
			Assert::AreEqual(sync_stream.get_num_streams(), (size_t)1);
		}

		TEST_METHOD(RemoveNonExistingStream)
		{
			std::ofstream log_file("log.txt");
			synced_stream sync_stream(&std::cout, &log_file);

			std::ofstream log_file2("log2.txt");
			sync_stream.remove_stream(&log_file2);
			Assert::AreEqual(sync_stream.get_num_streams(), (size_t)2);
		}
	};
}