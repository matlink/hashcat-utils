#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdexcept>

/**
 * use like this:
 * cut -d':' -f2 hashcat.pot | ./unhex > passwords.found
 */

std::string hex_to_string(const std::string& input)
{
    static const char* const lut = "0123456789abcdef";
    size_t len = input.length();
    if (len & 1) throw std::invalid_argument("odd length");

    std::string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)
    {
        char a = input[i];
        const char* p = std::lower_bound(lut, lut + 16, a);
        if (*p != a) throw std::invalid_argument("not a hex digit");

        char b = input[i + 1];
        const char* q = std::lower_bound(lut, lut + 16, b);
        if (*q != b) throw std::invalid_argument("not a hex digit");

        output.push_back(((p - lut) << 4) | (q - lut));
    }
    return output;
}

void usage(){
        static const std::string usage_str = "Read passwords from stdin and output $HEX[deadbeef] format into ascii if needed";
        std::cout << usage_str << std::endl;
}

int main(int argc, char** argv) {
    if (argc == 2 && strcmp(argv[1], "--help") == 0){
            usage();
            return EXIT_SUCCESS;
    }
    static const std::string hex = "$HEX[";
    for (std::string line; std::getline(std::cin, line);) {
        if ( strcmp(line.substr(0, 5).c_str(), hex.c_str()) == 0 ){
                line = hex_to_string(line.substr(5, line.size()-6));
        }
        std::cout << line << std::endl;
    }
    return 0;
}
