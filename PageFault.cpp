#include "PageFault.h"

const char * PageFault::what() const throw() {
	return "Page Fault";
}

PageFault::PageFault()	{
}


PageFault::~PageFault()	{
}
