// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start + (increment * steps)</returns>
template <typename T>
T add_numbers(T const& start, T const& increment, unsigned long int const& steps)
{
    T result = start;
    const T max = std::numeric_limits<T>::max(); // Max possible value for T
    for (unsigned long int i = 0; i < steps; ++i)
    {
        // If adding increment to result would cause an overflow, don't do it
        // If we are incrementing a positive number and the maximum value minus
        // the increment is less than the current result, it means it looped around to a negative number
        if ((increment > 0) && (result > (max - increment))) {
            throw std::overflow_error("Overflow occurred.");
        }

        result += increment;
    }

    return result;
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="decrement">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start - (decrement * steps)</returns>

template <typename T>
T subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps)
{
    T result = start;

    T max = std::numeric_limits<T>::max(); // Max possible value for T
    T min = std::numeric_limits<T>::min(); // Max possible value for T
   
    for (unsigned long int i = 0; i < steps; ++i)
    {
        // if we are subtracting a negative number, it's like addition so we need to check for overflow
        // if the maximum value for T plus the amount that we are adding (due to subtracting a negative) is greater
        // than the current result, it means it wrapped around to negative (overflowed)
        if (decrement < 0 && result > max + decrement) {
            throw std::overflow_error("overflow");
        } 
           
        // Similarly, if we are subtracting a positive number from result,
        // we need to check if the current result is less than the minimum value plus the decrement,
        // in which case it would imply that we went too far negative and wrapped around to a large positive number
        // but consider the case that we overflow so much that it does a full loop around the range of possible values,
        // we will get a false negative for underflow...
        if (decrement > 0 && result < min + decrement) {
            throw std::underflow_error("underflow");
        }

        result -= decrement;
    }

    return result;
}


//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we add each step (result should be: start + (increment * steps))
    const T increment = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
	T result = add_numbers<T>(start, increment, steps);
	std::cout << +result << std::endl;

    std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
    try {
        result = add_numbers<T>(start, increment, steps + 1);
        std::cout << +result << std::endl;
    }
    catch (...) {
        std::cout << "Overflow error." << std::endl;
    }
    
}

template <typename T>
void test_underflow()
{
    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we subtract each step (result should be: start - (increment * steps))
    const T decrement = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    std::cout << "\tSubtracting Numbers Without Underflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
    auto result = subtract_numbers<T>(start, decrement, steps);
    std::cout << +result << std::endl;
    
    std::cout << "\tSubtracting Numbers With Underflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";
    try {
		result = subtract_numbers<T>(start, decrement, steps + 1);
		std::cout << +result << std::endl;     
    }
    catch (...) {
        std::cout << "Underflow error." << std::endl;
    }
    
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Undeflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    //  create a string of "*" to use in the console
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu