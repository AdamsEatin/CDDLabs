/*
  Author: Adam Eaton
  Created: October 5th 2017
  Last Edit: October 20th 2017
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>

void taskOne(std::shared_ptr<Semaphore> mutex, int *cPointer){
  std::cout << "taskOne started" << std::endl;
  mutex->Wait();
  *cPointer += 1;
  std::cout << "taskOne" << std::endl;
  mutex->Signal();
}
void taskTwo(std::shared_ptr<Semaphore> mutex, int *cPointer){
  std::cout << "taskTwo started" << std::endl;
  mutex->Wait();
  *cPointer += 1;
  std::cout << "taskTwo" << std::endl;
  mutex->Signal();
}

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> mutex( new Semaphore(1));
  int count = 0;
  int *cPointer = &count;
  
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo, mutex, &count);
  threadTwo=std::thread(taskOne, mutex, &count);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();

  std::cout << count << std::endl;
  return 0;
}
