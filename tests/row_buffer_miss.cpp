/* 
 * Name: row_buffer_miss.cpp
 * Title: Helps visualize the performance improvement from row buffer hits
 * Author: Vignesh Suresh
 * Date: May 8, 2020
 *
 */

#include <iostream>
#include <dram.h>
#include <stdlib.h>
#include <ctime>

// Using the entire std library to avoid importing libraries individually
using namespace std;

int main(void)
{
	cout << "[MAIN] Starting the main code!" << endl;

	// When you declare a constant char array, you are allocating a fixed
	// number of bytes in memory for it (like string), and this cannot be
	// changed. If you had not used const, the compiler will throw an error
	// for the below line that you are assigning const char * to a char *
	const char *m1_name = "memory_m1";

	// If instead of instantiating the object directly, you created two pointers
	// to the two below DRAM's, such as below: 
	// 		DRAM *dmem1 = new DRAM(*m1_name, *m1_data); 
	// it would call a constructor, but no copy constructor, assignment overload
	// or desrtructor, since you are explicitly allocating memory for the pointer
	// by saying new DRAM. Further, in case of read_check, you would have to
	// pass *dmem1 as the argument.
	DRAM dmem1(*m1_name, (const char &) "images/mem_load_dump_4.hex");

	clock_t time;
	
	// First, we cycle through elements that would hit in the row buffer
	time = clock();
	for(int i = 0; i < 0x100000; i++)
	{
		dmem1.get_word(i%ROW_BUFFER_WIDTH);
	}
	time = clock() - time;

	cout << "Time taken for first operation = " << time << endl;

	// Second, we increase the stride to twice the row buffer size so that half
	// of the accesses always miss
	time = clock();
	for(int i = 0; i < 0x100000; i++)
	{
		dmem1.get_word(i%(2*ROW_BUFFER_WIDTH));
	}
	time = clock() - time;

	cout << "Time taken for second operation = " << time << endl;

	// Third, we ensure all accesses result in a row buffer miss
	time = clock();
	for(int i = 0; i < 0x100000; i++)
	{
		dmem1.get_word((i*ROW_BUFFER_WIDTH)%10000);
	}
	time = clock() - time;

	cout << "Time taken for third operation = " << time << endl;


	return 0;
}
