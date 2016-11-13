#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;
mutex cupMutex;
int maxCups = 1000;
int usedCups = 0;
int clientWait = 1;
int drinkCoffee = 1;
int recycle = 2;
int waitForRecycle = 3;
void threadFunction() {
	bool sleepFlag = false;
	bool recycleFlag = false;
	while (true) {
		cupMutex.lock();
		if (maxCups == 0)
		{
			sleepFlag = true;
		}
		else
		{
			maxCups -= 1;
			usedCups += 1;
		}

		cupMutex.unlock();
		if (sleepFlag) {
			this_thread::sleep_for(chrono::seconds(clientWait));
			sleepFlag = false;
		}
		else
		{
			this_thread::sleep_for(chrono::seconds(drinkCoffee));

		}
	}
}
void threadFunction2() {
	bool recycleFlag = false;
	while (true)
	{
		cupMutex.lock();
		if (usedCups >= 3)
		{
			int cupsToReturn = usedCups / 3;
			int remain = usedCups % 3;
			recycleFlag = true;
			
			usedCups -= (cupsToReturn*3) ;
			usedCups += remain;
			maxCups += cupsToReturn;
		}
		else {
			recycleFlag = false;
		}
		cupMutex.unlock();
		if (recycleFlag)
		{
			this_thread::sleep_for(chrono::seconds(recycle));
			recycleFlag = false;

		}
		else {
			this_thread::sleep_for(chrono::seconds(waitForRecycle));
		}
	}
}



int main()
{
	thread *t1, *t2;
	t1 = new thread(threadFunction);
	t2 = new thread(threadFunction2);
	while (true)
	{
		cupMutex.lock();
		printf("Max cups for now are: %d\n", maxCups);
		printf("Used cups for now are: %d\n", usedCups);
		cupMutex.unlock();
		this_thread::sleep_for(chrono::seconds(1));
	}
	
	t1->join();
	t2->join();
return 0;
}