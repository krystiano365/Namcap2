#ifndef AUXFUNC_H
#define AUXFUNC_H

#include <unistd.h>
#include <iostream>

class AuxFunc{
public:
	static std::string getPath(){
		char cwd[4096];
		getcwd(cwd, sizeof(cwd));
		return std::string(cwd);
	}
};

#endif // AUXFUNC_H
