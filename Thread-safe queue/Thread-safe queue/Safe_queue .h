#pragma once
#include<thread>
#include<queue>
#include<functional>
#include<mutex>
#include<chrono>

class safe_queue {

public:
	void push(std::function<void()> func) {
		std::unique_lock<std::mutex> ulm(m);
		tasks.push(func);
	}
	void pop() {
		std::unique_lock<std::mutex> ulm(m);
		tasks.pop();
	}
	void front() {
		std::unique_lock<std::mutex> ulm(m);
		tasks.front()();
	}
	bool empty() {
		std::unique_lock<std::mutex> ulm(m);
		return tasks.empty();
	}

private:
	std::mutex m;
	std::queue<std::function<void()>> tasks;

};