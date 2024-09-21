#pragma once
#include<thread>
#include<mutex>
#include<vector>
#include<queue>
#include<functional>
#include<chrono>
#include"Safe_queue .h"

class thread_pool {
public:
	thread_pool() {
		for (int i = 0; i < std::thread::hardware_concurrency(); i++) {
			threads.push_back(std::thread(&thread_pool::work, this));
		}
	}

	void work() {
		while (true) {
			std::unique_lock<std::mutex> ulm(m);
			if (sq.empty()) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
			else {
				sq.front();
				sq.pop();
			}
		}
	}

	void submit(std::function<void()> fu) {
		sq.push(fu);
	}

	~thread_pool() {
		for (auto& thread : threads) {
			thread.join();
		}
	}

private:
	std::vector<std::thread> threads;
	std::mutex m;
	safe_queue sq;
};