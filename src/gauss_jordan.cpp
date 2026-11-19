#include "modules/gauss_jordan.hpp"
#include <iostream>
#include <vector>
namespace janum
{
    void row_op(row_operations op){
        switch (op.flag)
        {
            // Print operation
            case 'p':
                for (size_t i = 0; i < op.rowA; i++)
                {
                    std::cout << "|\t";
                    for (size_t j = 0; j < op.cols; j++)
                    {
                        std::cout << op.matrix[i, j] << '\t';
                    }
                    std::cout << "|\n";
                }
                std::cout << '\n';
                break;

            // Scaling operation
            case 's':
                for (size_t i = 0; i < op.cols; i++)
                {
                    op.matrix[op.rowA, i] = op.scale * op.matrix[op.rowA, i] + 0.0;
                }
                break;

            // Interchange operation
            case 'w':
            {
                double x = 0; // dummy variable

                for (size_t i = 0; i < op.cols; i++)
                {
                    x = op.matrix[op.rowA, i];
                    op.matrix[op.rowA, i] = op.matrix[op.rowB, i];
                    op.matrix[op.rowB, i] = x;
                }
                break;
            }

            // Replacement operation
            case 'r':
                for (size_t i = 0; i < op.cols; i++)
                {
                    op.matrix[op.rowA, i] += op.scale * op.matrix[op.rowB, i];
                }
                
                break;
            
            default:
                break;
        }
        
        
    }
    
    std::array<int, 2> find_pivot(row_operations op, int row, bool augumented, char flag, int col){
        switch (flag)
        {
            case 'r':
                {
                    int limit = (augumented)? op.cols - 1 : op.cols;
                    if(col >= limit) return {0, 1};

                    for (size_t i = row; i < op.rowA; i++)
                    {
                        if (op.matrix[i, col] != 0)
                        {
                            return {static_cast<int>(i), 0};
                        }
                        
                    }
                    break;
                }
            case 'c':
                for (size_t j = 0; j < op.cols; j++)
                {
                    if (op.matrix[row, j] == 1)
                    {
                        return {static_cast<int>(j), 0};
                    }
                    
                }
                break;
            default:
                break;
        }
        return {0, 1};
    }

    void gauss_jordan(row_operations op, bool augumented){
        std::vector<std::string> history;
        int col = 0;
        int last_pivot_row = 0;

        // Row Echelon Form (REF)
        for(int i = 0; i < op.rowA; i++)
        {
            if(augumented == true && col >= op.cols - 1) 
            {
                break;
            } else if(augumented == false, col >= op.cols) break;

            // Find pivot position
            auto [pivot_row, ec] = find_pivot(op, i, augumented, 'r', col);
            
            if(ec == 0)
            {
                history.push_back(std::format("Found pivot position: {}\n", i));
            }else{ 
                col++; // move to next column
                i--; // remain on current row on the next iteration
                history.push_back("No pivot position\n");
                // for (const auto& entry : history)
                // {
                //     std::cerr << entry;
                // }
                continue;
            }
            
            // Interchange rows for current pivot position
            if (pivot_row != i)
            {
                // swap row i with pivot row
                row_op({.matrix = op.matrix, .cols = op.cols, .rowA = i, .rowB = pivot_row, .flag = 'w'});
            }
            history.push_back(std::format("Pivot position is at row {}", i));

            // Normalize pivot row
            row_op({.matrix = op.matrix, .cols = op.cols, .rowA = i, .scale = 1/op.matrix[i, col], .flag = 's'});

            // Create Zeores beneath pivot position
            for (int j = i+1; j < op.rowA; j++)
            {
                row_op({.matrix = op.matrix, .cols = op.cols, .rowA = j, .rowB = i, .scale = -op.matrix[j, col], .flag = 'r'});
            }
            
            // store value of pivot_row in row variable
            last_pivot_row = i;

            // Reset pivot row and move to next column if not on the last row
            if ((i + 1) < op.rowA)  
            {
                pivot_row = 0;   
                col++;
            }
        }
        
        // Reduced Row Echelon Form (RREF)
        for (int i = last_pivot_row; i >= 0; i--)
        {
            auto[pivot_col, ec] = find_pivot(op, i, augumented, 'c');
            for (int j = i - 1; j >= 0; j--)
            {
                //op.matrix[op.rowA, i] += op.scale * op.matrix[op.rowB, i];
                row_op({.matrix = op.matrix, .cols = op.cols, .rowA = j, .rowB = i, .scale = -op.matrix[j, pivot_col], .flag = 'r'});
            }
            
        }
        

        return;
    }
} // namespace janum
