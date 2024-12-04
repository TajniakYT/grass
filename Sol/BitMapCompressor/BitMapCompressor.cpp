#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <stdexcept>

extern "C" void compressRLEAsm(const uint8_t* data, size_t size, uint8_t* output, size_t* outputSize);

#pragma pack(push, 1) // Struktury dopasowane do zapisu/odczytu z pliku
struct BMPHeader {
    uint16_t bfType;      // 2 bajty
    uint32_t bfSize;      // 4 bajty
    uint16_t bfReserved1; // 2 bajty
    uint16_t bfReserved2; // 2 bajty
    uint32_t bfOffBits;   // 4 bajty
};

struct BMPInfoHeader {
    uint32_t biSize;          // 4 bajty
    int32_t biWidth;          // 4 bajty
    int32_t biHeight;         // 4 bajty
    uint16_t biPlanes;        // 2 bajty
    uint16_t biBitCount;      // 2 bajty
    uint32_t biCompression;   // 4 bajty
    uint32_t biSizeImage;     // 4 bajty
    int32_t biXPelsPerMeter;  // 4 bajty
    int32_t biYPelsPerMeter;  // 4 bajty
    uint32_t biClrUsed;       // 4 bajty
    uint32_t biClrImportant;  // 4 bajty
};
#pragma pack(pop)

// Funkcja do odczytu całego pliku do bufora
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

// Funkcja zapisu bufora do pliku
void writeFile(const std::string& filename, const std::vector<uint8_t>& buffer) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Can't open file: " + filename);
    }
    file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
}

// Funkcja kompresji RLE
std::vector<uint8_t> compressRLE(const std::vector<uint8_t>& data) {
    std::vector<uint8_t> compressed;

    size_t i = 0;
    while (i < data.size()) {
        uint8_t value = data[i];
        size_t count = 1;

        // Liczymy ile razy powtarza się dany bajt
        while (i + count < data.size() && data[i + count] == value && count < 255) {
            ++count;
        }

        // Dodajemy do skompresowanych danych
        compressed.push_back(count);
        compressed.push_back(value);

        i += count;
    }

    return compressed;
}

int main() {
    try {
        // Odczytujemy plik BMP
        std::string inputFilename = "sample.bmp";
        std::string outputFilename = "output_rle.bmp";
        auto fileData = readFile(inputFilename);

        // Nagłówki BMP
        BMPHeader* header = reinterpret_cast<BMPHeader*>(fileData.data());
        BMPInfoHeader* infoHeader = reinterpret_cast<BMPInfoHeader*>(fileData.data() + sizeof(BMPHeader));

        // Walidacja formatu pliku
        if (header->bfType != 0x4D42) { // "BM" w hex
            throw std::runtime_error("Incorrect BMP file format");
        }
        if (infoHeader->biBitCount != 8) {
            throw std::runtime_error("Only 8 bit BMP file");
        }

        // Wczytanie danych pikseli
        size_t pixelArrayOffset = header->bfOffBits;
        std::vector<uint8_t> pixelData(fileData.begin() + pixelArrayOffset, fileData.end());

        // Kompresja danych za pomocą RLE
        auto compressedData = compressRLE(pixelData);
        //size_t compressedSize = 0;

        //compressRLEAsm(pixelData.data(), pixelData.size(), compressedData.data(), &compressedSize);

        // Tworzymy nowy plik BMP z danymi RLE
        std::vector<uint8_t> outputFile;
        outputFile.insert(outputFile.end(), fileData.begin(), fileData.begin() + pixelArrayOffset); // Kopiujemy nagłówki
        outputFile.insert(outputFile.end(), compressedData.begin(), compressedData.end());         // Dodajemy dane RLE

        // Zapisujemy wynik do pliku
        writeFile(outputFilename, outputFile);

        std::cout << "Compression succesful, saved as:  " << outputFilename << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}