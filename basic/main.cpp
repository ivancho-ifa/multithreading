#include <iostream>
#include <thread>

void print_message()
{
	using std::cout; using std::endl;

	cout << "hi" << endl;
}

void detach_thread(std::thread& t)
{
	t.detach();
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
	using std::thread;

	thread t_01(print_message);
	
	detach_thread(t_01);
	wait_for_thread(t_01);

	return 0;
}