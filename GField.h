
#ifndef CPP_EX1_GFIELD_H
#define CPP_EX1_GFIELD_H

#include <cmath>
#include <iostream>
#include <iosfwd>
#include <cassert>


class GFNumber;

/**   Default values to create the field   */
const long P_DEFAULT = 2;
const long L_DEFAULT = 1;

/**
 * @brief The class which is an object that represents a number field
 */
class GField
{
private:
    /**   A variable that returns the field base    */
    long _p;
    /**  A variable that returns the field exponent     */
    long _l;

    /**
     * @brief Function that checks whether a number has a small divider from another given number
     * @param num The number being tested
     * @param i The tester number
     * @return true If there is, false otherwise
     */
    static bool _hasDivisorSmallerThen(long num, long i);

public:
    /**
     * @brief Default constructor. Initializes the base to be 2 and the exponent 1
     */
    GField() : GField(P_DEFAULT, L_DEFAULT)
    {};

    /**
     * @brief Semi-default constructor. Gets the base and sets the exponent to be 1
     * @param p Field base
     */
    GField(long p) : GField(p, L_DEFAULT)
    {};

    /**
     * @brief constructor
     * @param p The new field base
     * @param l  The new field exponent
     */
    GField(long p, long l);

    /**
     * @brief copy constructor
     * @param org The original field object
     */
    GField(const GField &org) : GField(org._p, org._l)
    {};

    /**
     * @brief destructor
     */
    ~GField() = default;

    /**
     * @brief Returns the field base
     * @return field base
     */
    long getChar() const
    {
        return _p;
    }

    /**
     * @brief Returns the field exponent
     * @return field exponent
     */
    long getDegree() const
    {
        return _l;
    }

    /**
     * @brief Returns the field order
     * @return field order
     */
    long getOrder() const
    {
        return (long) powl(_p, _l);
    }

    /**
     * @brief A function that checks whether a number is prime
     * @param num Number to check
     * @return true If so, false otherwise
     */
    static bool isPrime(long num);

    /**
     * @brief A function that calculates the maximum shared divisor of two numbers
     * @param a The first number
     * @param b the second number
     * @return  the maximum shared divisor of the numbers
     */
    GFNumber gcd(const GFNumber &a, const GFNumber &b) const;

    /**
     * @brief A function that receives a number and returns a number object in the field
     * @param k Number to create the object
     * @return Number type object in the field
     */
    GFNumber createNumber(long k) const;

    /**
     * @brief Placement operator from object to field to field object
     * @param other Field object for placement
     * @return Reference to the current field object
     */
    GField &operator=(const GField &other) = default;

    /**
     * @brief A two-field comparison operator
     * @param other Another field for comparison
     * @return True if they are equal, otherwise false
     */
    bool operator==(const GField &other) const
    {
        return this->getOrder() == other.getOrder();
    }

    /**
     * @brief A two-field ancomparison operator
     * @param other Another field for comparison
     * @return False if they are equal, otherwise True
     */
    bool operator!=(const GField &other) const
    {
        return this->getOrder() != other.getOrder();
    }

    /**
     * @brief operator Print the object through a stream
     * @param str stream to print the object
     * @param field The field object to print
     * @return Reference to the stream
     */
    friend std::ostream &operator<<(std::ostream &str, const GField &field);

    /**
     * @brief operator to get the object through a stream
     * @param str stream to get the object from
     * @param field The field object to set
     * @return Reference to the stream
     */
    friend std::istream &operator>>(std::istream &str, GField &field);
};

#endif //CPP_EX1_GFIELD_H
