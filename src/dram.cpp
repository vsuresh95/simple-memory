/* 
 * Name: dram.cpp
 * Title: DRAM class definition
 * Author: Vignesh Suresh
 * Date: May 6, 2020
 *
 */

#include <dram.h>

using namespace std;

// Constructor for DRAM class
DRAM::DRAM(const char &name, const char &init_filename):Memory(name, init_filename)
{
	row_buffer = new unsigned int;
	row_buffer = memory_array;

	cout << "[DRAM CONSTRUCTOR] DRAM " << memory_name; 
	cout << " has been created!" << endl;
}

// Destructor for DRAM class
DRAM::~DRAM(void)
{
	cout << "[DRAM DESTRUCTOR] DRAM " << memory_name;
	cout << " has been deleted!" << endl;
}

// Copy constructor for DRAM class
DRAM::DRAM(const DRAM &obj):Memory(obj)
{
	row_buffer = new unsigned int;
	row_buffer = memory_array;

	cout << "[DRAM COPY CONSTRUCTOR] DRAM " << memory_name;
	cout << " has been copied from " << obj.memory_name << endl;
}

// Overloading the assignment = operator for DRAM class
void DRAM::operator=(const DRAM &obj)
{
	cout << "[DRAM ASSIGNMENT OVERLOADER] DRAM " << memory_name;
	cout << " has been copied from " << obj.memory_name << endl;
}

// Overloading the subscript [] operator for DRAM class
// This makes the operator similar to how it works for arrays
unsigned int DRAM::operator[](int byte_address)
{
	return this->get_word(byte_address);
}

// get_word function returns the data value if the value requested
// is present in the row buffer, else it calls row_buffer fill function
unsigned int DRAM::get_word(int byte_address)
{
	int offset;

	row_buffer_miss = true;

	offset = (row_buffer - byte_address - memory_array);

	if(abs(offset) < ROW_BUFFER_WIDTH)
	{
		row_buffer_miss = false;
		return row_buffer[abs(offset)];
	}
	else
	{
		row_buffer_fill(byte_address);
		return get_word(byte_address);
	}
}

// row_buffer_fill replaces the current contents with contents for the
// new reuqested location, aligned to the ROW_BUFFER_WIDTH
void DRAM::row_buffer_fill(int byte_address)
{
	int offset;

	offset = byte_address - (byte_address%ROW_BUFFER_WIDTH);

	row_buffer = memory_array + offset;
}
