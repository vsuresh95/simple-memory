/* 
 * Name: memory.cpp
 * Title: Memory class definition
 * Author: Vignesh Suresh
 * Date: May 5, 2020
 *
 */

#include <memory.h>

// Using the entire std library to avoid importing libraries individually
using namespace std;

// Constructor for Memory class
// Parameters are references to the name char array and the initization vector
Memory::Memory(const char &name, const char &init_filename)
{
	// the function new returns the address that has been allocated
	// for the pointer
	memory_array = new unsigned int;

	mem_load(init_filename, 0);
	
	#ifdef DEBUG
		// creating a dummy output file name from the 
		// original input file name.
		// Unable to directly add the char's because 
		// they are const.
		char *output_filename;
		output_filename = new char;
		strcpy(output_filename, &init_filename);
		strcat(output_filename, ".debug");
		cout << output_filename << endl;
		
		// Need to explicitly give the size of the image
		// as there is no method implemented to assess
		// memory size yet
		mem_dump(output_filename, 0, 16384);
	#endif

	memory_name = &name;

	cout << "[MEMORY CONSTRUCTOR] Memory " << memory_name;
	cout << " has been created!" << endl;
}

// Destructor for Memory class
// Since memory_array was allocated with memory in the constructor, we need to
// delete the allocation. However, we do not need to allocate memory for memory_name
// because const data types are compiled into the code itself and are not 
// dynamically allocated.
// 
// Update (May 7, 2020): I have removed the delete for memory_array because
// it results in deallocation when you have a copy object.
// TODO: Create a mechanism where objects can copied and their members can
// be removed without problem, otherwise you will end up with memory overflow
// issues.
// 
// Update (November 17, 2020): memory_array in the case of this example is intended to
// be a shared memory area and unique to any object. Thus, any object of memory or a
// derived class can use it, and must not be deleted.
Memory::~Memory(void)
{
	cout << "[MEMORY DESTRUCTOR] Memory " << memory_name;
	cout << " has been deleted!" << endl;
}

// Copy constructor for Memory class
// The member memory_name is not allocated memory in the new object, since it
// is a const char, whereas memory_array is allocated.
Memory::Memory(const Memory &obj)
{
	memory_name = obj.memory_name;

	// Currently the issue is, when we assign the pointers addresses directly
	// to each other, I am able to read the correct values in case of mem2. 
	// However, since we delete mem1's memory_array before mem2,
	// the pointer gets deallocated before mem2's delete happens
	//
	// Second, when I assign the pointed values to each other, I am seeing a
	// mismatch in the values being read back because mem2 pointer was 
	// created at a different address but supposed to point to the same data
	//
	// the solution is to assign pointer addresses to each other but find a way
	// to avoid the deallocation problem
	memory_array = new unsigned int;
	memory_array = obj.memory_array;

	cout << "[MEMORY COPY CONSTRUCTOR] Memory " << memory_name;
	cout << " has been copied from " << obj.memory_name << endl;
}

void Memory::mem_load(const char &load_filename, unsigned int load_addr, unsigned int bytes)
{
	unsigned int i = 0;

	ifstream init_file;
	init_file.open(&load_filename);

	cout << "[MEM_LOAD] Opened input file " << &load_filename << endl;

	while((init_file >> std::hex >> *(memory_array+(load_addr/4)+i)) && 4*i < bytes)
		i++;
}

void Memory::mem_dump(const char *dump_filename, unsigned int dump_addr, unsigned int bytes)
{	
	unsigned int i = 0;
	ofstream check_file;
	check_file.open(dump_filename);
	
	cout << "[MEM_DUMP] Opened output file " << dump_filename << endl;

	while(4*i < bytes)
	{
		check_file << std::hex << *(memory_array+(dump_addr/4)+i) << endl;
		i++;
	}
}
