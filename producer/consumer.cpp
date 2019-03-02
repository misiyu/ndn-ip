#include <ndn-cxx/face.hpp>
#include <iostream>

using namespace ndn ;

class Consumer : noncopyable
{
	public:
		void
			run()
			{
				Interest interest(Name("/localhost/nfd/testApp/002.txt"));
				interest.setInterestLifetime(2_s); // 2 seconds
				interest.setMustBeFresh(true);

				m_face.expressInterest(interest,
						bind(&Consumer::onData, this,  _1, _2),
						bind(&Consumer::onNack, this, _1, _2),
						bind(&Consumer::onTimeout, this, _1));

				std::cout << "Sending " << interest << std::endl;

				m_face.processEvents();
			}

	private:
		void
			onData(const Interest& interest, const Data& data)
			{
				std::cout << data << std::endl;
				std::cout << data.getContent() << std::endl;
			}

		void
			onNack(const Interest& interest, const lp::Nack& nack)
			{
				std::cout << "received Nack with reason " << nack.getReason()
					<< " for interest " << interest << std::endl;
			}

		void
			onTimeout(const Interest& interest)
			{
				std::cout << "Timeout " << interest << std::endl;
			}

	private:
		Face m_face;
};


int main()
{
	Consumer consumer;
	try {
		consumer.run();
	}
	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
	return 0;
}
