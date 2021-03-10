#include "Interpreter.h"

std::vector<std::string>Interpreter::splitText(const std::string& str)
{
    char delim = ' ';
    std::vector<std::string> tokens;
    std::stringstream check(str);
    std::string intermediate;
    while(getline(check, intermediate, delim))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}

Interpreter::enumType Interpreter::GetType(const std::string& value)
{
    std::size_t found = value.find('.');
    if (found != std::string::npos)
    {
          return DOUBLE;
    }
    found = value.find('"');
    if(found != std::string::npos)
    {
        return STRING;
    }
    return INTEGER;
}

void Interpreter::DeclaresVariable(const std::vector<std::string>& TmpTokens)
{
    MyType temporaryObject;
    temporaryObject.name = TmpTokens[1];
    temporaryObject.type = GetType(TmpTokens[3]);
    myAllElements.push_back(temporaryObject);
    int currentIndex = myAllElements.size() - 1;
    SetValue(currentIndex, TmpTokens[3]);
}

void Interpreter::SetValue(int currentIndex, const std::string& value)
{
    if(myAllElements[currentIndex].type == INTEGER)
    {
        int* IntPtr = new int(std::stoi(value));
        myAllElements[currentIndex].value = static_cast<void*>(IntPtr);
    }
    else if(myAllElements[currentIndex].type == DOUBLE)
    {
        double* DoublePtr = new double(std::stod(value));
        myAllElements[currentIndex].value = static_cast<void*>(DoublePtr);
    }
    else
    {
        std::string* StringPtr = new std::string(value);
        myAllElements[currentIndex].value = static_cast<void*>(StringPtr);
    }
}

void Interpreter::PrintVariables(const std::vector<std::string>& TmpTokens)
{
    for(int i = 0; i < myAllElements.size(); ++i)
    {
        if(TmpTokens[1] == myAllElements[i].name)
        {
            if(myAllElements[i].type == INTEGER)
            {
                int* IntPtr = static_cast<int*>(myAllElements[i].value);
                std::cout << *IntPtr << std::endl;
            }
            else if(myAllElements[i].type == DOUBLE)
            {
                double* DoublePtr = static_cast<double*>(myAllElements[i].value);
                std::cout << *DoublePtr << std::endl;
            }
            else
            {
                std::string* StringPtr = static_cast<std::string*>(myAllElements[i].value);
                std::cout << *StringPtr << std::endl;
            }
        }
    }
}
void Interpreter::DeleteOldValues(const int& currentIndex)
{
    if(myAllElements[currentIndex].type == INTEGER)
    {
        int* IntPtr = static_cast<int*>(myAllElements[currentIndex].value);
        delete IntPtr;
        IntPtr = nullptr;
    }
    else if(myAllElements[currentIndex].type == DOUBLE)
    {
        double* DoublePtr = static_cast<double*>(myAllElements[currentIndex].value);
        delete DoublePtr;
        DoublePtr = nullptr;
    }
    else
    {
        std::string* StringPtr = static_cast<std::string*>(myAllElements[currentIndex].value);
        delete StringPtr;
        StringPtr = nullptr;
    }
}

void Interpreter::Assigning(const std::vector<std::string>& TmpTokens)
{
    enumType tmpType = GetType(TmpTokens[2]);
    for(int i = 0; i < myAllElements.size(); ++i)
    {
        if(TmpTokens[0] == myAllElements[i].name)
        {
            if(myAllElements[i].type == tmpType)
            {
                if(myAllElements[i].type == INTEGER)
                {
                    int* IntPtr = static_cast<int*>(myAllElements[i].value);
                    *IntPtr = std::stoi(TmpTokens[2]);
                }
                else if(myAllElements[i].type == DOUBLE)
                {
                    double* DoublePtr = static_cast<double*>(myAllElements[i].value);
                    *DoublePtr = std::stod(TmpTokens[2]);
                }
                else
                {
                    std::string* StringPtr = static_cast<std::string*>(myAllElements[i].value);
                    *StringPtr = TmpTokens[2];
                }
            }
            else
            {
                DeleteOldValues(i);
                
                myAllElements[i].type = tmpType;
                
                SetValue(i, TmpTokens[2]);
            }
        }
    }
}

Interpreter::Interpreter(const std::string& text)
{
    std::string line;
    std::ifstream MyFile(text);
    if(!MyFile.is_open())
    {
        std::cout << "Could not open the file!" << std::endl;
    }
    else
    {
        while(getline(MyFile, line))
        {
            std::vector<std::string> Tokens = splitText(line);
            if(Tokens[0] == "var")
            {
                DeclaresVariable(Tokens);
            }
            else if(Tokens[0] == "print")
            {
                PrintVariables(Tokens);
            }
            else
            {
                Assigning(Tokens);
            }
        }
    }
}

