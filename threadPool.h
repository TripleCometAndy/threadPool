//TODO. Figure out why compiler errors are happening//
//Try making them static and calling them using threadPool::whateverFunction//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include "lib/quickcheck/quickcheck/quickcheck.hh"

using namespace std;

class threadPool
{

  private:
    int Num_Threads;
    vector<thread> Pool;
    static condition_variable condition;
    static mutex Queue_Mutex;
    static queue<function<void()>> Queue;
    static void infiniteLoopFunction()
    {

        while (true)
        {
            
            unique_lock<mutex> lock(Queue_Mutex);

            condition.wait(lock, queueIsEmpty);
            function<void()> Job = Queue.front();
            Queue.pop();
            
            Job(); // function<void()> type
        }
    }
    
    static bool queueIsEmpty()
    {

        return !Queue.empty();
    }
    void init();

  public:
    threadPool();
    void Add_Job(function<void()> New_Job);
};

threadPool::threadPool()
{

    
    Num_Threads = thread::hardware_concurrency();
    init();
}

void threadPool::init()
{
    
    for (int ii = 0; ii < Num_Threads; ii++)
    {
        
        Pool.push_back(thread(infiniteLoopFunction));
    }
}

void threadPool::Add_Job(function<void()> New_Job)
{
    
    
    unique_lock<mutex> lock(Queue_Mutex);
    Queue.push(New_Job);
    
    condition.notify_one();
    
}

condition_variable threadPool::condition;
mutex threadPool::Queue_Mutex;
queue<function<void()>> threadPool::Queue;
