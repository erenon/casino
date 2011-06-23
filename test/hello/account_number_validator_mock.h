#ifndef __MOCK_ACCOUNT_NUMBER_VALIDATOR_H_
#define __MOCK_ACCOUNT_NUMBER_VALIDATOR_H_

#include "gmock/gmock.h"
#include "account_number_validator.h"

class MockAccountNumberValidator :public AccountNumberValidator
{
public:
	MOCK_METHOD1(isValid, bool(const char *account_number));
};

#endif //__MOCK_ACCOUNT_NUMBER_VALIDATOR_H_
