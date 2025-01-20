// A program to calculate quantities of ballast and cement
// for standard (1:2:4) concrete slab

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <limits>


class ConcreteSlab
{
private:
    double m_length{};
    double m_width{};
    double m_depth{};
    int m_ratio{};

public:
    ConcreteSlab(double length, double width, double depth, int ratio)
        : m_length{length}
        , m_width{width}
        , m_depth{depth}
        , m_ratio{ratio}
    {}

    double getLength() const {return m_length;}
    double getWidth() const {return m_width;}
    double getDepth() const {return m_depth;}
    int getRatio() const {return m_ratio;}

    double getArea() const {return m_length * m_width;}
    double getVolume() const {return (m_length * m_width * m_depth);}

    // Roughly 1,750 kg to 1,800 kg per metre squared
    double ballast() const 
    {
        return getVolume() * 1750;
    }

    double cement() const
    {
        if (m_ratio == 5)
            return (ballast() / 5 / 25);
        if (m_ratio == 6)
            return (ballast() / 6 / 25);
        if (m_ratio == 8)
            return (ballast() / 8 / 25);
        else
            return 0;
    }

    void print() 
    {
        std::cout << "\nA concrete slab of length " << getLength() <<
            " m, width " << getWidth() << " m, and depth " << getDepth() <<
            " m will require: " << "\n\n";
        std::cout << "               -------------------------------\n";
        std::cout << "\t\tBallast:    " << ballast() << " kg        \n";
        std::cout << "               -------------------------------\n";
        std::cout << "\t\tCement:     " << cement() << " bags(25 kg)\n";
        std::cout << "               -------------------------------\n\n";
        std::cout << "Area: " << getArea() << " m^2\t\tRatio: 1:" << 
            getRatio() <<"\t\tVolume: " << getVolume() <<
            " m^3\n\n"; 

    }
};

int main()
{
    ConcreteSlab s1{1, 1, 1, 5}; 
    s1.print();

    char input{};

    while (true)
    {
        double length{}, width{}, depth{};
        int ratio{};

        while (true)
        {
            std::cout << "Enter a length, width and depth in meters, followed by a ratio denominator. Press ENTER after each input:\n";
            std::cin >> length >> width >> depth >> ratio;
        
            if (std::cin.fail()) // no extraction took place
            {
                std::cin.clear(); // reset the state bits back to goodbit
                
                // clear out bad input from stream
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
                // print error
                std::cerr << "One or more of your inputs are invalid!\n";
        
                continue; // try again
            }
        
            // clear out any additional input from stream
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // if we cleared out more than one additional character
            if (std::cin.gcount() > 1)
                // consider the input to be invalid
                continue; // try again
        
            if (length < 0 || width < 0 || depth < 0) // make sure values is positive
            {
                std::cerr << "Inputs must be positive!\n";
                continue;
            }
        
            break; // else break
        }
        
        ConcreteSlab s2{length, width, depth, ratio};
        s2.print();

        std::cout << "Would you like to do another calculation? (Y/N):";
        std::cin >> input;
        if (input == 'Y' || input == 'y')
            continue;
        if (input == 'N' || input == 'n')
            break;
        else
            std::cout << "Invalid input";
            break;

    } 

    std::cout << "\nGoodbye!\n";    

    return 0;
}