#include "io_utils.hpp"
#include <iostream>
#include <vector>
#include <regex>
# include <janum>

int main(){
    static const std::regex size_pattern(R"(^\s*\d+\s*[xX,]\s*\d+\s*$)");

    std::cout << "This is the Gaussian Elimination Algorithm\n";
    
    // get and validate user's input
    std::string matSize = get_input("Size (row x column): ", size_pattern);
    bool augumented = std::tolower(get_input("Is the matrix augumented? (y/n): ", std::regex(R"(^\s*[yYnN]\s*$)"))[0]) == 'y';
    

    try{
        // assign no. of rows and columns
        auto [rows, columns] = get_dimensions(matSize);
        size_t element_count = rows * columns;

        std::cout << "Next enter matrix row-wise. For instance:\n";
        std::cout << "| 1 0 0 |\n";
        std::cout << "| 0 1 0 |\n";
        std::cout << "| 0 0 1 |\n";
        std::cout << "becomes \' 1 0 0  0 1 0  0 0 1\'\n";

        // get matrix row-wise from user
        std::vector<double> vmatrix = get_matrix(element_count);
        auto matrix = std::mdspan(vmatrix.data(), rows, columns);

        janum::gauss_jordan({.matrix = matrix, .cols = columns, .rowA = rows}, augumented);

        //print matrix
        janum::row_op({.matrix = matrix, .cols = columns, .rowA = rows});

    }catch(const std::out_of_range& e){
        std::cerr << "Error: Number is too large (" << e.what() << ")\n";
    }
    return 0;
}