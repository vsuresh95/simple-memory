/* 
 * Name: mem_load_dump.cpp
 * Title: Initializes a memory with contents of a file and dumps
 * Author: Vignesh Suresh
 * Date: May 9, 2020
 *
 */

#include <iostream>
#include <dram.h>
#include <stdlib.h>

// Using the entire std library to avoid importing libraries individually
using namespace std;

int main(void)
{
	cout << "[MAIN] Starting the main code!" << endl;

	DRAM dmem1((const char &) "memory_m1", (const char &) "images/mem_load_dump_4096_4.hex");
	
	cout << "Reading data from location 4095 = 0x";
	cout << std::hex << dmem1.get_word(4095) << endl;

	dmem1.mem_load((const char &) "images/mem_load_dump_1024_4.hex", 4096, 4096); 

	dmem1.mem_dump((const char &) "bin/mem_load_dump_4096_4.hex", 0, 16384); 

	return 0;
}

// TODO: Theory for template in case of future use
// When you are building functions or classes that need to be portable across
// different datatypes (int, double, etc), you will use a template typedef
// instead of using a particular datatype. 
// For example,
// 		template <class T> // here T is a user defined template
// 		
// 		class Shape
// 		{
// 			T data;
//
// 			T area();
// 		};
//
//		// before member functions outside the class, you need to use
//		// the template line again - C++ rules
//		// and, use <T> after the class name - C++ rules
//		template <class T> 
// 		T Shape<T>::area()
// 		{
// 			return data;
// 		}
//
// 		int main()
// 		{
// 			Shape <int> square; // through the <int>, you are specifying the type
// 		}
//
// TODO: Vectors are pretty much like arrays but allow for dynamic memory
// allocation. They have their pre-defined functions to do push_back or pop_back
// to add or remove elements at the end. They also allow you to use insert
// function to insert or erase function to erase elements in between but
// they are more resource intensive and take more CPU time than they do
// for arrays.
