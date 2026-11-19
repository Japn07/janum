#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <array>
#include <string_view>

inline std::string get_input(std::string prompt, std::regex pattern){
    // get and validate user's input
    std::string input;
    do
    {
        std::cout << prompt;
        std::getline(std::cin, input);
    } while (!(std::regex_match(input, pattern)));
    return input;
}

inline std::array<int, 2> get_dimensions(std::string target){
    // pattern to extract dimensions
    static const std::regex pattern(R"(^\s*(\d+)\s*[xX,]\s*(\d+)\s*$)");
    static const std::regex size_pattern(R"(^\s*\d+\s*[xX,]\s*\d+\s*$)");
    std::smatch matches;
    std::regex_match(target, matches, pattern);
    int rows = std::stoi(matches[1].str());
    int columns =  std::stoi(matches[2].str());

    while (rows == 0 || columns == 0)
    {
        target = get_input("Size (row x column): ", size_pattern);
        return get_dimensions(target);
    }
    
    
    return {rows, columns};
}

inline std::vector<double> get_matrix(size_t n){
    std::vector<double> vmatrix;
    bool status;

    do
    {
        std::cout << "Matrix: ";
        std::string smatrix;
        std::getline(std::cin, smatrix);
        std::string_view smatrix_view = smatrix;
        
        vmatrix.clear();    // clears partial numbers from previous failed attempts
        size_t pos = 0;     // Reset position to start of new string
        status = false;     // Reset error flag

        while (pos < smatrix_view.size())
        {
            //skip whitespaces
            while(pos < smatrix_view.size() && smatrix_view[pos] == ' ') ++pos;
            // end of string
            if (pos == smatrix_view.size()) break;
            
            double value = 0;
            auto[ptr, ec] = std::from_chars(smatrix_view.data() + pos, smatrix_view.data() + smatrix_view.size(), value);

            if (ec != std::errc() || (ptr != smatrix_view.data() + smatrix_view.size() && *ptr != ' '))
            {
                status = true;
                break;
            }
            
            vmatrix.push_back(value);
            pos = ptr - smatrix_view.data();
            status = false;
        }
        if(vmatrix.size() != n) status = true;
    } while (status);
    
    return vmatrix;
}
