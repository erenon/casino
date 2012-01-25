#ifndef CTC_ISTREAM_MOCK_H_
#define CTC_ISTREAM_MOCK_H_

#include <fstream>

namespace Casino { namespace Test { namespace Common {

using ::std::istream;

class IstreamMock
:public ifstream
{
public:
	IstreamMock(const char* filename)
	{
		open(filename);
		if (!is_open()) {
			ADD_FAILURE() << "Unable to open mock input";
			//throw std::runtime_error("failed to open file to read");
		}
	}

	~IstreamMock() {
		close();
	}
};

}}} //namespace

#endif /* CTC_ISTREAM_MOCK_H_ */
