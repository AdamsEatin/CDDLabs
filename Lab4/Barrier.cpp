/*
  Author: Adam Eaton
  Created: 20th October 2017
  Last Edit: 21st October 2017
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>

bool threadCondition = true;
int threadCount=0;
int threadNum=3;


void barrier(std::shared_ptr<Semaphore> semA, std::shared_ptr<Semaphore> semB, std::shared_ptr<Semaphore> mutex){
  while(threadCondition){
      mutex->Wait();
      threadCount++;

      //Testing to see the order that threads initialise
      std::cout<<"Thread No: " << threadCount << std::endl;
      
      if(threadCount==threadNum){
	semB->Wait();
        semA->Signal();
      }
      mutex->Signal();
      semA->Wait();
      semA->Signal();     
      mutex->Wait();
      threadCount--;
      
      if(threadCount==0){
	semA->Wait();
	semB->Signal();
	threadCondition=false;
      }
      mutex->Signal();
      semB->Wait();
      semB->Signal();  
  }
}

int main(){
  //initialising semaphores
  std::shared_ptr<Semaphore> semA( new Semaphore());
  std::shared_ptr<Semaphore> semB( new Semaphore(1));
  std::shared_ptr<Semaphore> mutex( new Semaphore(1));
  
  //look into using vector and loop to initialise in future
  std::thread threadOne(barrier, semA, semB, mutex);
  std::thread threadTwo(barrier, semA, semB, mutex);
  std::thread threadThree(barrier, semA, semB, mutex);
  
  threadOne.join();
  threadTwo.join();
  threadThree.join();
  
}
