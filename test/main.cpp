#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "hello/hello.h"

GTEST_API_ int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	// The following line must be executed to initialize Google Mock
	// (and Google Test) before running the tests.
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
