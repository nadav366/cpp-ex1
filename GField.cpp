#include "GFNumber.h"
#include "GField.h"

/**
 * @brief constructor
 * @param p The new field base
 * @param l  The new field exponent
 */
GField::GField(long p, long l)
{
    p = labs(p);
    // Input integrity check
    assert(p >= 2);
    assert(l > 0);
    assert(isPrime(p));
    _p = p;
    _l = l;
}

/**
 * @brief Function that checks whether a number has a small divider from another given number
 * @param num The number being tested
 * @param i The tester number
 * @return true If there is, false otherwise
 */
bool GField::_hasDivisorSmallerThen(long num, long i)
{
    if (num % i == 0 and i > 1)
    {
        return true;
    }
    if (i > 2)
    {
        return _hasDivisorSmallerThen(num, i - 1);
    }
    return false;
}

/**
 * @brief A function that checks whether a number is prime
 * @param num Number to check
 * @return true If so, false otherwise
 */
bool GField::isPrime(long num)
{
    num = std::abs(num); // checks also for negative numbers
    if (num <= 1)
    {
        return false;
    }
    return !_hasDivisorSmallerThen(num, (long) sqrtl(num));
}

/**
 * @brief A function that calculates the maximum shared divisor of two numbers
 * @param a The first number
 * @param b the second number
 * @return  the maximum shared divisor of the numbers
 */
GFNumber GField::gcd(const GFNumber &a, const GFNumber &b) const
{
    // Check that both numbers are under the current field
    assert(a.getField() == b.getField());
    assert(a.getField() == *this);

    // Euclid algorithm
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

/**
 * @brief A function that receives a number and returns a number object in the field
 * @param k Number to create the object
 * @return Number type object in the field
 */
GFNumber GField::createNumber(long k) const
{
    return GFNumber(k, *this); // Use the number constructor, under the current field
}

/**
 * @brief operator Print the object through a stream
 * @param str stream to print the object
 * @param field The field object to print
 * @return Reference to the stream
 */
std::ostream &operator<<(std::ostream &str, const GField &field)
{
    return (str << "GF(" << field._p << "**" << field._l << ")");
}

/**
 * @brief operator to get the object through a stream
 * @param str stream to get the object from
 * @param field The field object to set
 * @return Reference to the stream
 */
std::istream &operator>>(std::istream &str, GField &field)
{
    return (str >> field._p >> field._l);
}

