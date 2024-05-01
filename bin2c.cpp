#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

std::vector<unsigned char> readFile(const std::string &filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    // Determine the file size
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read the file into a vector
    std::vector<unsigned char> buffer(fileSize);
    file.read(reinterpret_cast<char *>(buffer.data()), fileSize);

    return buffer;
}

void writeFile(const std::string &filename, const std::vector<unsigned char> &data)
{
    std::ofstream file(filename);
    if (!file)
    {
        throw std::runtime_error("Failed to create file: " + filename);
    }

    // Write the array declaration to the file
    file << "unsigned char data[" << data.size() << "] = { ";

    // Write the hex array to the file
    for (size_t i = 0; i < data.size(); i++)
    {
        file << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
        if (i != data.size() - 1)
        {
            file << ", ";
        }
    }
    file << " };\n";
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    try
    {
        // Read the binary file
        std::vector<unsigned char> binaryData = readFile(inputFile);

        // Write the hex array and its length to a new file
        writeFile(outputFile, binaryData);

        std::cout << "Hex array and its length successfully generated in " << outputFile << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
