// STL
#include <iostream>

// Fairy::Kernel
#include <kernel/Kernel.hpp>

int main(int argc, char * argv[])
{
	Fairy::Kernel::instance().start();

	return Fairy::kernel::instance().loop();
}//main

