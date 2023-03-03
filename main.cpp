#include "DNSCache.h"
#include <string>
#include <iostream>
#include <thread>
#include <vector>

int main()
{	
	// Test application
	std::vector < std::pair<std::string, std::string>> inputs{
	std::make_pair<std::string, std::string>("localhost", "0.0.0.0"),
	std::make_pair<std::string, std::string>("yandex", "0.0.0.1"),
	std::make_pair<std::string, std::string>("google", "0.0.0.2"),
	std::make_pair<std::string, std::string>("yahoo", "0.0.0.3"),
	};

	std::vector<std::thread> threads;
	threads.resize(inputs.size());

	for (int i = 0; i < inputs.size(); ++i) {
		threads[i] = std::thread([&]() {
			DNSCache::get_instance()->update(inputs[i].first, inputs[i].second);
			});
	}

	for (int i = 0; i < inputs.size(); ++i) {
		threads[i].join();
	}

	return 0;
}
