// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class CustomException : public std::exception {
private:
    std::string message;
public:
    CustomException(const char* msg)  : message(msg) { }
    const char* what() const throw() {
        return message.c_str();
    }
};

bool do_even_more_custom_application_logic()
{
    std::cout << "Running Even More Custom Application Logic." << std::endl;
    throw std::bad_exception(); // Throw random exception derived from std::exception
    return true;
}
void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;
   
    // do_even_more_custom_application_logic throws a std::exception, wrap in exception handler
    try {
		if (do_even_more_custom_application_logic())
		{
			std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
		}
    }
    catch (std::exception& ex) { // Catch the exception
        std::cout << "Exception in do_even_more_custom_application_logic: " << ex.what() << std::endl;
    }
    

    // Throw random CustomException
    throw CustomException("Objection!");

    std::cout << "Leaving Custom Application Logic." << std::endl;
}

float divide(float num, float den)
{
    // Safe division, catch division by 0 before it happens
    if (den == 0.0) throw std::domain_error("Denominator cannot be 0");
    return (num / den);
}

void do_division() noexcept
{
    float numerator = 10.0f;
    float denominator = 0;

    // Divide throws a domain_error exception, wrap in exception handler
    try {
        std::cout << "Dividing..." << std::endl;
		auto result = divide(numerator, denominator);
	    std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (std::domain_error& ex) { // Catch the domain_error
        std::cout << "Caught exception in divide: " << ex.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;
      
    // These functions throw CustomExceptions, wrap in exception handler
    try {
		do_division();
		do_custom_application_logic();
    }
    catch (CustomException& ex) { // Catch exceptions
        std::cout << "Caught CustomException in main: " << std::endl;
        std::cout << ex.what() << std::endl;
    }
    catch (...) { // Catch unhandled exceptions
        std::cout << "An unknown error occurred." << std::endl;
    }
}
