#include "PageFault.h"



override PageFault::what()
{
	return override();
}

const char * PageFault::what() const throw() {
	return "Page Fault";
}

PageFault::PageFault()
{
}


PageFault::~PageFault()
{
}
