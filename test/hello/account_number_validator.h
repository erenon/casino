#ifndef __ACCOUNT_NUMBER_VALIDATOR_H_
#define __ACCOUNT_NUMBER_VALIDATOR_H_

class AccountNumberValidator
{
public:
	virtual bool isValid(const char *account_number) = 0;
	virtual ~AccountNumberValidator() {}
};

#endif //__ACCOUNT_NUMBER_VALIDATOR_H_
