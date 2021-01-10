/* 
 * Name: memory.h
 * Title: Memory class declaration
 * Author: Vignesh Suresh
 * Date: May 5, 2020
 *
 */

#include <iostream>
#include <fstream>

class Memory
{
	protected:
		unsigned int *memory_array;

	public:
		void set_word(int, unsigned int);
		unsigned int get_word(int);

	public:
		Memory(const char &, const char &);
		~Memory();
		Memory(const Memory &);

	protected:
		const char *memory_name;

	public:
		void mem_load(const char &, unsigned int, unsigned int bytes = 0xFFFFFFFF);
		void mem_dump(const char *, unsigned int, unsigned int bytes = 0xFFFFFFFF);
};
