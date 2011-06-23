#include "gtest/gtest.h"

#include "gmock/gmock.h"
using ::testing::Exactly;
using ::testing::Return;
#include <stdexcept>
#include "account_number_validator_mock.h"
#include "bank_account.h"

// Tests test suite
TEST(HelloTest, Hello) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


TEST(HelloTest, Mock) {
	MockAccountNumberValidator validator;

	EXPECT_CALL(validator, isValid("foobar"))
		.Times(Exactly(2))
		.WillOnce(Return(true))
		.WillOnce(Return(false));

	BankAccount a("foobar", &validator);

	ASSERT_THROW(BankAccount b("foobar", &validator), std::invalid_argument);

}
