#include "pch.h"
#include "CppUnitTest.h"
#include "../thread_pool.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<> static std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<std::future<int>>(const class std::future<int>& t) { return L"std::future"; }

namespace MultiFutureUnitTests
{
	TEST_CLASS(MultiFutureUnitTests)
	{
	public:
		TEST_METHOD(ConstructorSizeArgument)
		{
			multi_future<int> multi_future(10);

			Assert::AreEqual(multi_future.size(), (size_t)10);
		}

		TEST_METHOD(AddFuture)
		{
			multi_future<int> multi_future(10);

			std::future<int> future;
			multi_future.push_back(future);

			Assert::AreEqual(multi_future.size(), (size_t)11);
		}

		TEST_METHOD(OperatorSquareBracket)
		{
			multi_future<int> multi_future(10);

			std::future<int> &future = multi_future[9];

			Assert::AreSame(future, multi_future[9]);
		}

	};
}