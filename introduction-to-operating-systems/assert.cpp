#include <iostream>
#include <thread>
#include <assert.h>

using std::cout;
using std::endl;
using std::thread;

void hello(){
	cout << "hello" << endl;
}

int main(){
	thread t(&hello);
	t.join();
	
	assert(t.joinable() == false);
	return 0;
}
