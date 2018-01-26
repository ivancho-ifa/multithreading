#include <thread>
#include <string>
#include <mutex>
#include <iostream>
#include <fstream>

// use mutex via a guard_lock
// this way if code executed 
// throws exception, mutex is unlocked

std::mutex global_mutex;

// not thread safe
// every resource in a thread safe code must be 
// accessed only via section surrounded with mutex
// cout is global resource
void thread_safe_print(const std::string& msg)
{
	std::lock_guard<std::mutex> lock(global_mutex);
	// global_mutex.lock();
	// better use guard lock
	// here exception may be thrown
	std::cout << msg << std::endl;
	// global_mutex.unlock();
}

class Log
{
public:
	Log(const std::string& file_path)
		: _out{ file_path, std::ios::out | std::ios::app }, _mutex{}
	{}
	Log(Log&&) = default;
	Log& operator=(Log&&) = default;
	~Log() = default;
public:
	Log() = delete;
	Log(const Log&) = delete;
	Log& operator=(const Log&) = delete;

public:
	void msg(const std::string& msg)
	{
		std::lock_guard<std::mutex> locker(_mutex);
		_out << msg << std::endl;
	}

private:
	std::ofstream _out;
	std::mutex _mutex;
};

void shared_log(Log& log, const std::string& msg)
{
	for (size_t i = 0; i < 100; i++)
		log.msg(msg);
}

void not_shared_log(std::ofstream& out, const std::string& msg)
{
	for (size_t i = 0; i < 100; i++)
		out << msg << std::endl;
}

void wait_for_thread(std::thread& t)
{
	// if thread is detached 
	// thread is not joinable
	// and join will crash
	if (t.joinable()) {
		t.join();
	}
}

int main()
{
	Log log("log.txt");

	// thread safe
	std::thread t_01(shared_log, std::ref(log), "thread");
	shared_log(std::ref(log), "main");

	//not thread safe
	//std::ofstream out("log.txt", std::ios::app | std::ios::out);
	//std::thread t_01(not_shared_log, std::ref(out), "thread");

	//not_shared_log(out, "main");

	wait_for_thread(t_01);

	//out.close();

	return 0;
}