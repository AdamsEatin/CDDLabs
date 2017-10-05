#include "Semaphore.h"
#include <iostream>
#include <thread>

void taskOne(std::shared_ptr<Semaphore> aArrived,std::shared_ptr<Semaphore> bArrived ){
  std::cout <<"I ";
  std::cout << "must "<<std::endl;
  aArrived->Signal();
  bArrived->Wait();
  std::cout << "print ";
  std::cout << "first"<<std::endl;
}
void taskTwo(std::shared_ptr<Semaphore> aArrived,std::shared_ptr<Semaphore> bArrived){
  std::cout <<"This ";
  std::cout << "will "<<std::endl;
  bArrived->Signal();
  aArrived->Wait();
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> aArrived( new Semaphore);
  std::shared_ptr<Semaphore> bArrived( new Semaphore);
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo, aArrived, bArrived);
  threadTwo=std::thread(taskOne, aArrived, bArrived);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
