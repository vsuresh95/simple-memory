/* 
 * Name: basic_object_copy.cpp
 * Title: Initializes one DRAM object and copies it
 * Author: Vignesh Suresh
 * Date: May 8, 2020
 *
 */

#include <iostream>
#include <dram.h>
#include <stdlib.h>

// Using the entire std library to avoid importing libraries individually
using namespace std;

void read_check(DRAM &obj, int byte_address)
{
	cout << "[MAIN] Two ways to read the memory: " << endl;
	cout << "[MAIN] Through get_word function: value at ";
	cout << std::dec << byte_address << " = 0x";
	cout << std::hex << obj.get_word(byte_address) << endl;
	cout << "[MAIN] Through overloaded subscript: value at ";
	cout << std::dec << byte_address << " = 0x";
	cout << std::hex << obj[byte_address] << endl;
}

int main(void)
{
	cout << "[MAIN] Starting the main code!" << endl;

	// Iniitializing an array of random data for m1, and
	// creating an instance of it called m1
	//
	// since it is a pointer (which an array is as well), 
	// we can reference the elements using index
	//
	// we are also giving a name to the object and passing
	// that as a character array
	//
	// Update: We have replaced the mechanism of directly 
	// loading the contents through an array with an image
	// passed as a file.
	//		unsigned int *m1_data;
	//		m1_data = new unsigned int;
	//		
	//		srand (time(NULL));

	//		for(int i = 0; i < 10000; i++)
	//		{
	//			*(m1_data + i) = rand() % 10000;
	//		}

	// When you declare a constant char array, you are allocating a fixed
	// number of bytes in memory for it (like string), and this cannot be
	// changed. If you had not used const, the compiler will throw an error
	// for the below line that you are assigning const char * to a char *
	//
	// As demonstrated in another test - mem_load_dump.cpp, one can also 
	// cast a const char [] to const char &, and directly pass strings 
	// to the class constructor:
	// 		DRAM dmem1((const char &) "memory_m1", *m1_data); // 		
	const char *m1_name = "memory_m1";

	// If instead of instantiating the object directly, you created two pointers
	// to the two below DRAM's, such as below: 
	// 		DRAM *dmem1 = new DRAM(*m1_name, *m1_data); 
	// 		DRAM *dmem2 = new DRAM(*m1_name, *m1_data);
	// it would call a constructor, but no copy constructor, assignment overload
	// or desrtructor, since you are explicitly allocating memory for the pointer
	// by saying new DRAM. Further, in case of read_check, you would have to
	// pass *dmem1 as the argument.
	DRAM dmem2(*m1_name, (const char &) "images/mem_load_dump_4.hex");
	DRAM dmem1(*m1_name, (const char &) "images/mem_load_dump_4.hex");

	read_check(dmem1, 154);

	return 0;
}
