#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <chrono> // Dodajemy do pomiaru czasu

extern "C" void compressRLEAsm(const uint8_t* data, size_t size, uint8_t* output, size_t* outputSize);

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BMPInfoHeader {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

std::vector<uint8_t> readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Can't open file: " + filename);
    }
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<uint8_t> buffer(fileSize);
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
    return buffer;
}

void writeFile(const std::string& filename, const std::vector<uint8_t>& buffer) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Can't open file: " + filename);
    }
    file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
}

std::vector<uint8_t> compressRLE(const std::vector<uint8_t>& data) {
    std::vector<uint8_t> compressed;
    size_t i = 0;
    while (i < data.size()) {
        uint8_t value = data[i];
        size_t count = 1;
        while (i + count < data.size() && data[i + count] == value && count < 255) {
            ++count;
        }
        compressed.push_back(count);
        compressed.push_back(value);
        i += count;
    }
    return compressed;
}

int main() {
    try {
        std::string inputFilename = "sample.bmp";
        std::string outputFilenameCpp = "output_rle_cpp.bmp";
        std::string outputFilenameAsm = "output_rle_asm.bmp";

        auto fileData = readFile(inputFilename);
        BMPHeader* header = reinterpret_cast<BMPHeader*>(fileData.data());
        BMPInfoHeader* infoHeader = reinterpret_cast<BMPInfoHeader*>(fileData.data() + sizeof(BMPHeader));

        if (header->bfType != 0x4D42) {
            throw std::runtime_error("Incorrect BMP file format");
        }
        if (infoHeader->biBitCount != 8) {
            throw std::runtime_error("Only 8 bit BMP file supported");
        }

        size_t pixelArrayOffset = header->bfOffBits;
        std::vector<uint8_t> pixelData(fileData.begin() + pixelArrayOffset, fileData.end());

        // Mierzenie czasu kompresji C++ (start)
        auto startCpp = std::chrono::high_resolution_clock::now();

        auto compressedDataCpp = compressRLE(pixelData);

        auto endCpp = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationCpp = endCpp - startCpp;

        // Zapisujemy wynik kompresji C++ do pliku
        std::vector<uint8_t> outputFileCpp;
        outputFileCpp.insert(outputFileCpp.end(), fileData.begin(), fileData.begin() + pixelArrayOffset);
        outputFileCpp.insert(outputFileCpp.end(), compressedDataCpp.begin(), compressedDataCpp.end());
        writeFile(outputFilenameCpp, outputFileCpp);

        std::cout << "C++ compression successful, saved as: " << outputFilenameCpp << std::endl;
        std::cout << "C++ Compression Time: " << durationCpp.count() << " seconds" << std::endl;

        // Przygotowanie bufora wyjściowego dla funkcji assemblerowej
        std::vector<uint8_t> compressedDataAsm(pixelData.size() * 2, 0);
        size_t compressedSizeAsm = 0;

        // Mierzenie czasu kompresji ASM (start)
        auto startAsm = std::chrono::high_resolution_clock::now();

        compressRLEAsm(pixelData.data(), pixelData.size(), compressedDataAsm.data(), &compressedSizeAsm);

        auto endAsm = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationAsm = endAsm - startAsm;

        compressedDataAsm.resize(compressedSizeAsm);

        // Zapisujemy wynik kompresji ASM do pliku
        std::vector<uint8_t> outputFileAsm;
        outputFileAsm.insert(outputFileAsm.end(), fileData.begin(), fileData.begin() + pixelArrayOffset);
        outputFileAsm.insert(outputFileAsm.end(), compressedDataAsm.begin(), compressedDataAsm.end());
        writeFile(outputFilenameAsm, outputFileAsm);

        std::cout << "ASM compression successful, saved as: " << outputFilenameAsm << std::endl;
        std::cout << "ASM Compression Time: " << durationAsm.count() << " seconds" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
