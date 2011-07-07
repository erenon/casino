#ifndef CTC_OSTREAM_MOCK_H_
#define CTC_OSTREAM_MOCK_H_

#include <fstream>
#include <stdexcept>
#include <cstring>

#include "gtest/gtest.h"

namespace Casino { namespace Test { namespace Common {

using ::std::ofstream;
using ::std::ifstream;

/**
 * @todo use stringbuf
 */
class OstreamMock
:public ofstream
{
protected:
	char *filename;
	const unsigned int MAX_CONTENT_SIZE;
public:
	OstreamMock(const char* filename)
		:MAX_CONTENT_SIZE(5000)
	{
		open(filename);
		if (!is_open()) {
			ADD_FAILURE() << "Unable to open mock output";
			//throw std::runtime_error("failed to open file to write");
		}

		this->filename = new char[strlen(filename)];
		strcpy(this->filename, filename);
	}

	void assert_eq(const char* expected) {
		close();

		// check expected's length
		if (strlen(expected) > MAX_CONTENT_SIZE) {
			throw std::overflow_error("expected output is too long");
		}

		ifstream current;

		current.open(filename);
		if (!current.is_open()) {
			throw std::runtime_error("failed to open file to read");
		}

		// get current length
		current.seekg(0, std::ios::end);
		unsigned int current_length = current.tellg();
		current.seekg(0, std::ios::beg);

		// check current's length
		if (current_length > MAX_CONTENT_SIZE) {
			throw std::overflow_error("current output is too long");
		}

		// read the whole file
		char *current_buf = new char[current_length + 1];
		current.read(current_buf, current_length);
		current_buf[current_length] = '\0';

		ASSERT_STREQ(expected, current_buf);

		delete[] current_buf;
		current.close();
	}

	~OstreamMock() {
		delete[] filename;
	}
};

}}} //namespace

#endif /* OSTREAM_MOCK_H_ */
