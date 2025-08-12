#include "headers.h"

int main()
{
    void* rawMemory = _aligned_malloc(sizeof(std::ifstream), alignof(std::ifstream));
    if(!rawMemory)
    {
        std::cerr << "Could not allocate memory";
        std::cin.get();
        return -1;
    }

    std::ifstream* inputFile = new(rawMemory) std::ifstream("input.txt");

    std::cout << "Input file" << std::endl;
    if(!inputFile->is_open())
    {
        std::cerr << "Can open file. Check if file exists";
        std::cin.get();
        return -1;
    }

    std::string line;

    while(std::getline(*inputFile, line))
    {
        std::cout << line << std::endl;
    }

    inputFile->close();

    std::cout << "End of input file" << std::endl;

    inputFile->~basic_ifstream();
    inputFile = nullptr;

    rawMemory = _aligned_realloc(rawMemory, sizeof(std::ofstream), alignof(std::ofstream));
    if(!rawMemory)
    {
        std::cerr << "Memory reallocation failed";
        std::cin.get();
        return -1;
    }

    std::ofstream* outputFile = new(rawMemory) std::ofstream("output.txt");

    std::cout << "\nOutput file" << std::endl;
    if(!outputFile->is_open())
    {
        std::cerr << "Could not open file, please check if file exists";
        std::cin.get();
        return -1;
    }

    *outputFile << "Hello" << std::endl;
    *outputFile << "This text was written by the program";

    outputFile->close();

    std::cout << "File was written successfully" << std::endl;
    std::cout << "End of output file" << std::endl;

    outputFile->~basic_ofstream();
    outputFile = nullptr;

    _aligned_free(rawMemory);
    rawMemory = nullptr;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Press any key to exit...";
    std::cin.get();

    return 0;
}