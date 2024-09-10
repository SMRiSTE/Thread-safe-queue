#pragma once
#include<thread>
#include<vector>
#include<queue>
#include<functional>
#include<mutex>
#include<chrono>

class thread_pool {
public:
	thread_pool() {
		for (int i = 0; i < std::thread::hardware_concurrency(); i++) {
			threads.push_back(std::thread(&thread_pool::work, this));
		}
	}

	void work() {
		std::unique_lock<std::mutex> u_l(m);
		if (func.empty()) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		else {
			auto task = func.front();
			func.pop();
			task();
		}
	}

	void submit(std::function<void()> fu) {
		func.push(fu);
	}

	~thread_pool() {
		for (auto& thread : threads) {
			thread.join();
		}
	}

private:
	std::vector<std::thread> threads;
	std::queue<std::function<void()>> func;
	std::mutex m;
};