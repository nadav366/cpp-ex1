
#ifndef CPP_EX1_GFNUMBER_H
#define CPP_EX1_GFNUMBER_H

#include "GField.h"

/**   Default values to create the field   */
const long NUM_DEFAULT = 0;

/**
 * @brief A class that is a number under a particular field
 */
class GFNumber
{
private:
    /**    The number field object   */
    GField _field;
    /**   The value of the number itself    */
    long _n;

    /**
     * @brief Auxiliary function for Pollard's RUE algorithm
     * @param x Number, the entry value of the function
     * @return Number, the function result
     */
    GFNumber _f(const GFNumber &x, const GFNumber &num) const
    {
        return (x * x + 1) % num;
    }

    /**
     * @brief Pollard Row algorithm, gets a number under field, and returns one of its decomposers
     * @param number Number under field, for decomposition
     * @return The cause, if found. -1 otherwise
     */
    long _pollardRho(const GFNumber &number) const;

    /**
     * @brief A naive algorithm for decomposing factors
     * @param num Number under field for decomposition
     * @param numOfFactors pointer for the number of current factors found
     * @param allFactors Indicates an array of elements already found
     * @return pointer to set of factors, after the additional decomposition.
     * It is the user's responsibility to delete the array at the end of use
     */
    GFNumber *_bruteForceAlg(GFNumber num, int *numOfFactors, GFNumber *allFactors) const;

    /**
     * @brief Extracting function numbers all of its spousal factors
     * @param numOfFactors pointer for the number of current factors found
     * @param copy The current number being analyzed
     * @param allFactors pointer to an array of elements already found
     * @return pointer to set of factors, after the additional decomposition.
     * It is the user's responsibility to delete the array at the end of use
     */
    GFNumber *_checkEven(int *numOfFactors, GFNumber &copy, GFNumber *allFactors) const;

    /**
     * @brief Add a number to the decomposition array
     * @param numOfFactors pointer for the number of current factors found
     * @param numToInsert Number to be added to the array
     * @param oldList pointer to an array of elements already found
     * @return pointer to set of factors, after the additional decomposition.
     * It is the user's responsibility to delete the array at the end of use
     */
    GFNumber *_insertNum(int *numOfFactors, const GFNumber &numToInsert, GFNumber *oldList) const;

public:
    /**
     * @brief Default constructor, initializes a default field to number 0
     */
    GFNumber() : GFNumber(NUM_DEFAULT)
    {};

    /**
     * @brief Builds a default half, gets a number and initializes it to a default field
     * @param n number to insert
     */
    GFNumber(long n) : GFNumber(n, GField())
    {};

    /**
     * @brief constructor
     * @param n number to insert
     * @param field field object to insert
     */
    GFNumber(long n, const GField &field);

    /**
     * @brief Copy constructor
     * @param other Another number object to copy
     */
    GFNumber(const GFNumber &other) : GFNumber(other._n, other._field)
    {};

    /**
     * @brief destructor
     */
    ~GFNumber() = default;

    /**
     * @brief A function that returns the number value
     * @return the number value
     */
    long getNumber() const
    {
        return _n;
    }

    /**
     * @brief A function that returns the number field
     * @return the number field
     */
    GField getField() const
    {
        return _field;
    }

    /**
     * @brief A function that returns an array containing decomposition to the prime factors of
     *      the number
     * @param numOfFactors Indicates the number of factors in decomposition
     * @return Pointer to a set of factors
     * It is the user's responsibility to delete the array at the end of use
     */
    GFNumber *getPrimeFactors(int *numOfFactors) const;

    /**
     * @brief A function that prints the decomposition into prime factors of the number
     */
    void printFactors() const;

    /**
     * @brief Function that checks whether the current number is prime
     * @return true If yes, false otherwise
     */
    bool getIsPrime() const
    {
        return GField::isPrime(_n);
    }

    /** OPERATORS */

    /**
     * @brief Object number placement operator
     * @param other Another number object, for placement
     * @return A reference to the current object
     */
    GFNumber &operator=(const GFNumber &other) = default;

    /* operator+ */

    /**
     * @brief Operator Adds a number object to the current number.
     * @param other number object to add
     * @return A reference to the current object
     */
    GFNumber &operator+=(const GFNumber &other);

    /**
     * @brief Operator Adds number object and the current number.
     * @param other number object to add
     * @return Object number, which is the connection of both numbers
     */
    GFNumber operator+(const GFNumber &other) const;

    /**
     * @brief Operator Adds a long number  to the current number.
     * @param other long number to add
     * @return A reference to the current object
     */
    GFNumber &operator+=(const long &other);

    /**
     * @brief Operator Adds long number and the current number.
     * @param other long number to add
     * @return Object number, which is the connection of both numbers
     */
    GFNumber operator+(const long &other) const;

    /* operator- */

    /**
     * @brief Operator subtracting a number object from the current number.
     * @param other number object to subtract
     * @return A reference to the current object
     */
    GFNumber &operator-=(const GFNumber &other);

    /**
     * @brief Operator subtracting a number object from current number.
     * @param other number object to subtract
     * @return Object number, which is the Subtraction of both numbers
     */
    GFNumber operator-(const GFNumber &other) const;

    /**
     * @brief Operator subtracting a long number from the current number.
     * @param other long number to subtract
     * @return Object number, which is the Subtraction of both numbers
     */
    GFNumber &operator-=(const long &other);

    /**
     * @brief Operator subtracting a long number from current number.
     * @param other long number to subtract
     * @return Object number, which is the Subtraction of both numbers
     */
    GFNumber operator-(const long &other) const;

    /* operator* */

    /**
     * @brief Operator multiplication the current number by number object.
     * @param other number object to multiplication
     * @return A reference to the current object
     */
    GFNumber &operator*=(const GFNumber &other);

    /**
     * @brief Operator multiplication a number object and the current number.
     * @param other number object to multiplication
     * @return Object number, which is the multiplication of both numbers
     */
    GFNumber operator*(const GFNumber &other) const;

    /**
     * @brief Operator multiplication the current number by long number.
     * @param other long number to multiplication
     * @return A reference to the current object
     */
    GFNumber &operator*=(const long &other);

    /**
     * @brief Operator multiplication a long number and the current number.
     * @param other long number to multiplication
     * @return Object number, which is the multiplication of both numbers
     */
    GFNumber operator*(const long &other) const;

    /* operator% */

    /**
     * @brief Operator modulo the current number by number object.
     * @param other number object to modulo
     * @return A reference to the current object
     */
    GFNumber &operator%=(const GFNumber &other);

    /**
     * @brief Operator modulo the current number and number object.
     * @param other number object to modulo
     * @return Object number, which is the modulo of both numbers
     */
    GFNumber operator%(const GFNumber &other) const;

    /**
     * @brief Operator modulo the current number by long number.
     * @param other long number to modulo
     * @return A reference to the current object
     */
    GFNumber &operator%=(const long &other);

    /**
     * @brief Operator modulo from the current number and long number.
     * @param other long number to modulo
     * @return Object number, which is the modulo of both numbers
     */
    GFNumber operator%(const long &other) const;

    /* operator/ */

    /**
     * @brief Operator division the current number by number object.
     * @param other number object to division
     * @return A reference to the current object
     */
    GFNumber &operator/=(const GFNumber &other);

    /**
     * @brief Operator division the current number and number object.
     * @param other number object to division
     * @return Object number, which is the division of both numbers
     */
    GFNumber operator/(const GFNumber &other) const;

    /**
     * @brief Operator division the current number by long number.
     * @param other long number to division
     * @return A reference to the current object
     */
    GFNumber &operator/=(const long &other);

    /**
     * @brief Operator division the current number and long number.
     * @param other long number to division
     * @return Object number, which is the division of both numbers
     */
    GFNumber operator/(const long &other) const;

    /* operator== */

    /**
     * @brief A two-naumber comparison operator
     * @param other Another GFNumber for comparison
     * @return True if they are equal, otherwise false
     */
    bool operator==(const GFNumber &other) const;

    /**
     * @brief A two-naumber ancomparison operator
     * @param other Another GFNumber for ancomparison
     * @return false if they are equal, otherwise true
     */
    bool operator!=(const GFNumber &other) const;

    /**
     * @brief A current GFNumber and long number comparison operator
     * @param other long number for comparison
     * @return True if they are equal, otherwise false
     */
    bool operator==(const long &other) const;

    /**
     * @brief A current GFNumber and long number ancomparison operator
     * @param other long number for ancomparison
     * @return false if they are equal, otherwise true
     */
    bool operator!=(const long &other) const;

    /* operator</> */

    /**
     * @brief Operator checks whether the current number is smaller than another number object
     * @param other Another number object for comparison
     * @return true if the current number is smaller, otherwise false
     */
    bool operator<(const GFNumber &other) const;

    /**
     * @brief Operator checks whether the current number is bigger than another number object
     * @param other Another number object for comparison
     * @return true if the current number is bigger, otherwise false
     */
    bool operator>(const GFNumber &other) const;

    /**
     * @brief Operator checks if the current number is smaller or equal than another number object
     * @param other number object for comparison
     * @return true if the current number is smaller or equal, otherwise false
     */
    bool operator<=(const GFNumber &other) const;

    /**
     * @brief Operator checks if the current number is bigger or equal than another number object
     * @param other number object for comparison
     * @return true if the current number is bigger or equal, otherwise false
     */
    bool operator>=(const GFNumber &other) const;

    /**
     * @brief Operator checks whether the current number is smaller than another long number
     * @param other long number for comparison
     * @return true if the current number is smaller, otherwise false
     */
    bool operator<(const long &other) const;

    /**
     * @brief Operator checks if the current number is bigger than another long number
     * @param other long number for comparison
     * @return true if the current number is bigger, otherwise false
     */
    bool operator>(const long &other) const;

    /**
     * @brief Operator checks if the current number is smaller or equal than another long number
     * @param other long number for comparison
     * @return true if the current number is smaller or equal, otherwise false
     */
    bool operator<=(const long &other) const;

    /**
     * @brief Operator checks if the current number is bigger or equal than another long number
     * @param other long number for comparison
     * @return true if the current number is bigger or equal, otherwise false
     */
    bool operator>=(const long &other) const;

    /* operator<< / >> */

    /**
     * @brief operator Print the object through a stream
     * @param str stream to print the object
     * @param num The Number object to print
     * @return Reference to the stream
     */
    friend std::ostream &operator<<(std::ostream &str, const GFNumber &num);

    /**
     * @brief operator to get the object through a stream
     * @param str stream to get the object from
     * @param num The Number object to set
     * @return Reference to the stream
     */
    friend std::istream &operator>>(std::istream &str, GFNumber &num);
};

#endif //CPP_EX1_GFNUMBER_H
