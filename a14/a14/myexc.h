#pragma once

#include <iostream>
#include <exception>

class Exception {

public:
	Exception(const std::string& msg) : info(msg) {}
	~Exception() {}

	std::string what() const { return(info); }

private:
	std::string info;
};
