// ThreadedQueue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <thread>

#include "windows.h"

struct Queue
{

};

struct Producer
{
   static int counter;
   
   std::string id_;

   std::thread t;
   Producer(std::string&& id) : id_(std::move(id)) {
      t = std::thread(&Producer::produce, this);
   }

   void produce() {
      while (true) {
         PROCESSOR_NUMBER procNumber;
         ::GetCurrentProcessorNumberEx(&procNumber);
         std::ostringstream current_core;
         current_core << (int)(procNumber.Group) << ":" << (int)(procNumber.Number);


         std::cout << id_ << " << " << current_core.str() << " << " << counter++ << std::endl;
         std::this_thread::sleep_for(std::chrono::seconds(1));
      }
   }

   void join() {
      t.join();
   }
};
int Producer::counter = 0;

struct Consumer
{

};

int main()
{
   Producer p1("p1");
   Producer p2("p2");
   Producer p3("p3");

   p1.join();
   p2.join();
   p3.join();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
