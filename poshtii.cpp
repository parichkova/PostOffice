#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <stdio.h>
using namespace std;
mutex mailMutex;
int currentMailNumber = 0;
void threadSortFunction(int mailCount, int time)
{
	bool sleepFlag = false;
	while (true)
	{
		mailMutex.lock();
		if (currentMailNumber < 0 || currentMailNumber + mailCount <= 0)
		{
			sleepFlag = true;
		}
		else {
			currentMailNumber += mailCount;
		}
		mailMutex.unlock();
		if (sleepFlag)
		{
			this_thread::sleep_for(chrono::milliseconds(15));
			sleepFlag = false;
		}
		else
		{
			this_thread::sleep_for(chrono::seconds(time));
		}
	}
}
int main()
{
	thread *t1, *t2, *t3, *t4, *t5;
	/*Сортиращите служители разпределят както следва: 10 писма/мин, 15п/мин, 12 п/мин.
	Зареждащите служители изсипват както следва: 2000 п/час и 1500 п/час.*/
	t1 = new thread(threadSortFunction, -10, 1);
	t2 = new thread(threadSortFunction, -15, 1);
	t3 = new thread(threadSortFunction, -12, 1);
	t4 = new thread(threadSortFunction, 60,5);
	t5 = new thread(threadSortFunction, 40, 10);
	while (true)
	{
		mailMutex.lock();
		printf("You have %d mails on the table\n", currentMailNumber);
		mailMutex.unlock();
		this_thread::sleep_for(chrono::seconds(1));
	}
	t1->join();
	t2->join();
	t3->join();
	t4->join();
	t5->join();
}