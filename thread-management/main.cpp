#include <iostream>
#include <thread>
#include <string>

void print_message(const std::string& msg)
{
	using std::cout; using std::endl;

	cout << msg << endl;
}

// thread should allways 
// be joined or detached
// before it goes out of scope

// this should crash
void start_local_thread()
{
	std::thread t_01(print_message);
}
// confirmed, it crashes

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
	using std::thread;
	using std::string;
	using std::cout; using std::endl;

	string msg = "hi";

	// thread constructor accepts function pointers, functors and lambdas
	// all arguments that the threaded function accepts are deep copied
	// else resource management proglems arise
	// solution for that is std::move
	thread t_01(print_message, std::move(msg));
	// threads can not be copied
	// use std::move()

	try
	{
		// work for the main thread
		// can throw exception
		// then the thread will be destroyed 
		// before joining or detaching
		// so catch exception and handle threads
	}
	catch (const std::exception&)
	{
		wait_for_thread(t_01);
	}

	wait_for_thread(t_01);

	//start_local_thread();
	//cout << "exit normally" << endl;
	return 0;
}