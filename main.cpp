#include "threadPool.h"

using namespace std;

void helloWorld(){

    cout << "Hello world" << endl;

}

int main(){

    threadPool tP;
    tP.Add_Job(std::bind(&helloWorld));
}