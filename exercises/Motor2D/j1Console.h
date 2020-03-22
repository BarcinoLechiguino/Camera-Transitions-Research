#include "j1Module.h"
#include "p2SString.h"

class Command
{
public:
	p2SString name;				//"map iso.tmx" --> The string is separated at the space and the first string will be the name of the command 
								//and the second one are the number of arguments that the command has (speed would have 1 argument.
	uint n_arguments;			

	j1Module* lisener;
};