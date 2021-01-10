/* 
 * Name: dram.h
 * Title: DRAM class declaration
 * Author: Vignesh Suresh
 * Date: May 6, 2020
 *
 */

#include <iostream>
#include <memory.h>

#define ROW_BUFFER_WIDTH 20

// A derived class from Memory
class DRAM: public Memory
{
	private:
		unsigned int *row_buffer;

	private:
		bool row_buffer_miss;

	public:
		unsigned int get_word(int);

	public:
		void row_buffer_fill(int);

	public:
		// constructors and destructors cannot have a return type
		DRAM(const char &, const char &);
		~DRAM();
		DRAM(const DRAM &);
		void operator=(const DRAM &);
		unsigned int operator[](int);
};
