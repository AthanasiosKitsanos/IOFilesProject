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

   //-------------------------------------------------------------------------------------------------------
    rawMemory = _aligned_realloc(rawMemory, sizeof(std::ofstream), alignof(std::ofstream));
    if(!rawMemory)
    {
        std::cerr << "Memory reallocation failed";
        std::cin.get();
        return -1;
    }

    std::ofstream* outputFile = new(rawMemory) std::ofstream("output.txt", std::ios::app); //adding the std::ios::app

    std::cout << "\nOutput file" << std::endl;
    if(!outputFile->is_open())
    {
        std::cerr << "Could not open file, please check if file exists";
        std::cin.get();
        return -1;
    }

    // *outputFile << "Hello" << std::endl;
    // *outputFile << "This text was written by the program";
    // *outputFile << "This is added using std::ios::app";

    outputFile->close();

    std::cout << "File was written successfully" << std::endl;
    std::cout << "End of output file" << std::endl;

    outputFile->~basic_ofstream();
    outputFile = nullptr;
    
    //-------------------------------------------------------------------------------------------------------
    rawMemory = _aligned_realloc(rawMemory, sizeof(std::ifstream), alignof(std::ifstream));
    if(!rawMemory)
    {
        std::cout << "Could not allocate for binary ofstream";
        std::cin.get();
        return -1;
    }

    std::cout << "Binary file" << std:: endl;
    inputFile = new(rawMemory) std::ifstream("input.bin", std::ios::binary);

    if(!inputFile->is_open())
    {
        std::cerr << "Could not open file. Please check if file exists" << std::endl;
        std::cin.get();
        return - 1;
    }

    //Going to the end to get the size of the file
    inputFile->seekg(0, std::ios::end);
    std::streampos size = inputFile->tellg();

    //Going to the beginning of the file
    inputFile->seekg(0, std::ios::beg);

    //Buffer creationg to read byte by byte
    void* rawBuffer = _aligned_malloc(sizeof(std::vector<char>), alignof(std::vector<char>));
    std::vector<char>* buffer = new(rawBuffer) std::vector<char>();

    //Reading all the bytes to the buffer
    inputFile->read(buffer->data(), size);

    inputFile->close();

    for(size_t i = 0; i < buffer->size(); i++)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(static_cast<unsigned char>(buffer->at(i))) <<  " ";
        if((i + 1) % 16 == 0)
        {
            std::cout << std::endl;
        }
    }

    inputFile->~basic_ifstream();
    inputFile = nullptr;

    //-------------------------------------------------------------------------------------------------------
    std::cout << "Output Binary" << std::endl;

    buffer->resize(5);

    buffer->at(0) = 0x48;
    buffer->at(1) = 0x65;
    buffer->at(2) = 0x6C;
    buffer->at(3) = 0x6C;
    buffer->at(4) = 0x6F;

    outputFile = new(rawMemory) std::ofstream("output.bin", std::ios::binary);

    if(!outputFile->is_open())
    {
        std::cerr << "Failed to open file, please check if file exists" << std::endl;
        std::cin.get();
        return -1;
    }

    outputFile->write(buffer->data(), buffer->size());

    outputFile->close();

    std::cout << "data have been registered" << std::endl;

    outputFile->~basic_ofstream();
    outputFile = nullptr;

    buffer->~vector<char>();
    buffer = nullptr;
    
    _aligned_free(rawBuffer);
    rawBuffer = nullptr;
    buffer = nullptr;

    //-------------------------------------------------------------------------------------------------------
    _aligned_free(rawMemory);
    rawMemory = nullptr;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Press any key to exit...";
    std::cin.get();

    return 0;
}