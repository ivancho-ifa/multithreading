#include <iostream>
#include <thread>

void print_message()
{
	using std::cout; using std::endl;

	cout << "hi" << endl;
}

// thread should allways 
// be joined or detached
// before it goes out of scope

// this should crash
void start_local_thread()
{
	using std::thread;

	thread t_01(print_message);
}
// it crashes

void wait_for_thread(std::thread&& t)
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
	using std::cout; using std::endl;

	thread t_01(print_message);
	// threads can not be copied
	//thread t_02 = std::move(t_02);

	wait_for_thread(std::move(t_01));


	//start_local_thread();
	//cout << "exit normally" << endl;
	return 0;
}