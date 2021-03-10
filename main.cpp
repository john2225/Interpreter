#include <iostream>
#include "Interpreter.h"

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cout << "Could not open the file!" << std::endl;
        return 0;
    }
    Interpreter hello(argv[1]);
    
    return 0;
}
