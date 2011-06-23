#ifndef __BANK_ACCOUNT_H_
#define __BANK_ACCOUNT_H_

#include "account_number_validator.h"
#include <stdexcept>

class BankAccount
{
public:
	BankAccount(const char *account_number, AccountNumberValidator *validator) {
		if (!validator->isValid(account_number)) {
			throw std::invalid_argument("Invalid account number");
		}
	}
};

#endif //__BANK_ACCOUNT_H_
