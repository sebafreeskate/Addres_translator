#pragma once
#include <exception>

class PageFault :
	public std::exception
{
public:
	virtual const char * what() const throw() override;
	PageFault();
	~PageFault();
};

