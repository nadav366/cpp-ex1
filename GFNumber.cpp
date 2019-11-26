
    #include "GFNumber.h"
    #include <iostream>

    /**
     * @brief constructor
     * @param n number to insert
     * @param field field object to insert
     */
    GFNumber::GFNumber(long n, const GField &field)
    {
        _field = field;

        // Matching the number to the correct field
        while (n < 0)
        {
            n += field.getOrder();
        }
        while (n >= field.getOrder())
        {
            n -= field.getOrder();
        }
        _n = n;
    }

    /**
     * @brief A function that returns an array containing decomposition to the prime factors of
     *      the number
     * @param numOfFactors Indicates the number of factors in decomposition
     * @return Pointer to a set of factors
     * It is the user's responsibility to delete the array at the end of use
     */
    GFNumber *GFNumber::getPrimeFactors(int *numOfFactors) const
    {
        // initialization variable and array
        auto *allFactors = new GFNumber[0];
        GFNumber copy(*this);
        *numOfFactors = 0;

        // Check if there is no decomposition for causes
        if (copy == 0 || copy == 1 || copy.getIsPrime())
        {
            return allFactors;
        }

        // Finding the even causes
        allFactors = _checkEven(numOfFactors, copy, allFactors);
        if (copy == 1)
        {
            return allFactors;
        }
        if (copy.getIsPrime())
        {
            return _insertNum(numOfFactors, copy, allFactors);
        }

        // Running Pollard's RUE Algorithm
        long p;
        while ((p = _pollardRho(copy)) != -1)
        {
            // Run brute force algorithm About the cause found
            allFactors = _bruteForceAlg(GFNumber(p, copy.getField()), numOfFactors, allFactors);
            copy = GFNumber(copy.getNumber() / p, copy.getField());
            if (copy.getIsPrime())
            {
                return _insertNum(numOfFactors, copy, allFactors);
            }
        }
        allFactors = _bruteForceAlg(copy, numOfFactors, allFactors); // Run brute force algorithm
        return allFactors;
    }

    /**
     * @brief Extracting function numbers all of its spousal factors
     * @param numOfFactors pointer for the number of current factors found
     * @param copy The current number being analyzed
     * @param allFactors pointer to an array of elements already found
     * @return pointer to set of factors, after the additional decomposition.
     * It is the user's responsibility to delete the array at the end of use
     */
    GFNumber *GFNumber::_checkEven(int *numOfFactors, GFNumber &copy, GFNumber *allFactors) const
    {
        while ((copy % 2) == 0)
        {
            allFactors = _insertNum(numOfFactors, GFNumber(2, copy.getField()), allFactors);
            copy /= 2;
        }
        return allFactors;
    }

    /**
     * @brief Add a number to the decomposition array
     * @param numOfFactors pointer for the number of current factors found
     * @param numToInsert Number to be added to the array
     * @param oldList pointer to an array of elements already found
     * @return pointer to set of factors, after the additional decomposition.
     * It is the user's responsibility to delete the array at the end of use
     */
    GFNumber *GFNumber::_insertNum(int *numOfFactors, const GFNumber &numToInsert,
                                   GFNumber *oldList) const
    {
        (*numOfFactors)++;
        auto *newList = new GFNumber[*numOfFactors];
        // Copy the old list
        int i = 0;
        for (; i < (*numOfFactors) - 1; i++)
        {
            newList[i] = oldList[i];
        }
        newList[i] = numToInsert;
        delete[] oldList;
        return newList;
    }

    /**
     * @brief A function that prints the decomposition into prime factors of the number
     */
    void GFNumber::printFactors() const
    {
        std::cout << _n;
        int numOfFact = 0;
        GFNumber *factorsList = getPrimeFactors(&numOfFact);
        if (numOfFact == 0)
        {
            std::cout << "=" << getNumber() << "*1";
        }

        if (numOfFact > 1)
        {
            int i = 0;
            std::cout << "=" << factorsList[i].getNumber();
            i++;
            for (; i < numOfFact; i++)
            {
                std::cout << "*" << factorsList[i].getNumber();
            }
        }
        std::cout << std::endl;
        delete[] factorsList;
    }

    /**
     * @brief Pollard Row algorithm, gets a number under field, and returns one of its decomposers
     * @param number Number under field, for decomposition
     * @return The cause, if found. -1 otherwise
     */
    long GFNumber::_pollardRho(const GFNumber &number) const
    {
        // initialization variables
        GFNumber x(rand() % number.getNumber() + 1, number.getField());
        GFNumber y(x);
        GFNumber p(1, number.getField());

        while (p.getNumber() == 1)
        {
            x = _f(x, number);
            y = _f(_f(y, number), number);
            if (x > y)
            {
                p = number.getField().gcd((x - y), number);
            }
            else
            {
                p = number.getField().gcd((y - x), number);
            }
        }
        if (p == number)
        {
            return -1;
        }
        return p.getNumber();
    }

    /**
     * @brief A naive algorithm for decomposing factors
     * @param num Number under field for decomposition
     * @param numOfFactors pointer for the number of current factors found
     * @param allFactors Indicates an array of elements already found
     * @return pointer to set of factors, after the additional decomposition.
     * It is the user's responsibility to delete the array at the end of use
     */
    GFNumber *GFNumber::_bruteForceAlg(GFNumber num, int *numOfFactors, GFNumber *allFactors) const
    {
        GFNumber i(2, num.getField());
        while (i <= (long) sqrtl(num.getNumber()))
        {
            if (num % i == 0)
            {
                allFactors = _insertNum(numOfFactors, i, allFactors);
                num /= i;
            }
            else
            {
                i += 1;
            }
        }
        if (num > 1)
        {
            allFactors = _insertNum(numOfFactors, num, allFactors);
        }
        return allFactors;
    }


    /** OPERATORS */

    /* operator+ */

    /**
     * @brief Operator Adds a number object to the current number.
     * @param other number object to add
     * @return A reference to the current object
     */
    GFNumber &GFNumber::operator+=(const GFNumber &other)
    {
        *this = *this + other;
        return *this;
    }

    /**
     * @brief Operator Adds number object and the current number.
     * @param other number object to add
     * @return Object number, which is the connection of both numbers
     */
    GFNumber GFNumber::operator+(const GFNumber &other) const
    {
        assert(this->_field == other._field);
        return this->_field.createNumber(this->_n + other._n);
    }

    /**
     * @brief Operator Adds a long number  to the current number.
     * @param other long number to add
     * @return A reference to the current object
     */
    GFNumber &GFNumber::operator+=(const long &other)
    {
        *this = *this + other;
        return *this;
    }

    /**
     * @brief Operator Adds long number and the current number.
     * @param other long number to add
     * @return Object number, which is the connection of both numbers
     */
    GFNumber GFNumber::operator+(const long &other) const
    {
        return this->_field.createNumber(this->_n + other);
    }

    /* operator- */

    /**
     * @brief Operator subtracting a number object from the current number.
     * @param other number object to subtract
     * @return A reference to the current object
     */
    GFNumber &GFNumber::operator-=(const GFNumber &other)
    {
        *this = *this - other;
        return *this;
    }

    /**
     * @brief Operator subtracting a number object from current number.
     * @param other number object to subtract
     * @return Object number, which is the Subtraction of both numbers
     */
    GFNumber GFNumber::operator-(const GFNumber &other) const
    {
        assert(this->_field == other._field);
        return this->_field.createNumber(this->_n - other._n);
    }

    /**
     * @brief Operator subtracting a long number from the current number.
     * @param other long number to subtract
     * @return Object number, which is the Subtraction of both numbers
     */
    GFNumber &GFNumber::operator-=(const long &other)
    {
        *this = *this - other;
        return *this;
    }

    /**
     * @brief Operator subtracting a long number from current number.
     * @param other long number to subtract
     * @return Object number, which is the Subtraction of both numbers
     */
    GFNumber GFNumber::operator-(const long &other) const
    {
        return this->_field.createNumber(this->_n - other);
    }

    /* operator* */

    /**
     * @brief Operator multiplication the current number by number object.
     * @param other number object to multiplication
     * @return A reference to the current object
     */
    GFNumber &GFNumber::operator*=(const GFNumber &other)
    {
        *this = *this * other;
        return *this;
    }

    /**
     * @brief Operator multiplication a number object and the current number.
     * @param other number object to multiplication
     * @return Object number, which is the multiplication of both numbers
     */
    GFNumber GFNumber::operator*(const GFNumber &other) const
    {
        assert(this->_field == other._field);
        return this->_field.createNumber(this->_n * other._n);
    }

    /**
     * @brief Operator multiplication the current number by long number.
     * @param other long number to multiplication
     * @return A reference to the current object
     */
    GFNumber &GFNumber::operator*=(const long &other)
    {
        *this = *this * other;
        return *this;
    }

    /**
     * @brief Operator multiplication a long number and the current number.
     * @param other long number to multiplication
     * @return Object number, which is the multiplication of both numbers
     */
    GFNumber GFNumber::operator*(const long &other) const
    {
        return this->_field.createNumber(this->_n * other);
    }

    /* operator% */

    /**
     * @brief
     * @param other
     * @return
     */
    GFNumber &GFNumber::operator%=(const GFNumber &other)
    {
        *this = *this % other;
        return *this;
    }

    /**
     * @brief Operator modulo the current number by number object.
     * @param other number object to modulo
     * @return A reference to the current object
     */
    GFNumber GFNumber::operator%(const GFNumber &other) const
    {
        assert(this->_field == other._field);
        assert(other != 0);
        return this->_field.createNumber(this->_n % other._n);
    }

    /**
     * @brief Operator modulo the current number by long number.
     * @param other long number to modulo
     * @return A reference to the current object
     */
    GFNumber &GFNumber::operator%=(const long &other)
    {
        *this = *this % other;
        return *this;
    }

    /**
     * @brief Operator modulo from the current number and long number.
     * @param other long number to modulo
     * @return Object number, which is the modulo of both numbers
     */
    GFNumber GFNumber::operator%(const long &other) const
    {
        assert(other != 0);
        return *this % GFNumber(other, this->getField());
    }

    /* operator/ */

    /**
     * @brief Operator division the current number by number object.
     * @param other number object to division
     * @return A reference to the current object
     */
    GFNumber &GFNumber::operator/=(const GFNumber &other)
    {
        *this = *this / other;
        return *this;
    }

    /**
     * @brief Operator division the current number and number object.
     * @param other number object to division
     * @return Object number, which is the division of both numbers
     */
    GFNumber GFNumber::operator/(const GFNumber &other) const
    {
        assert(other != 0);
        assert(this->_field == other._field);
        return this->_field.createNumber(this->_n / other._n);
    }

    /**
     * @brief Operator division the current number by long number.
     * @param other long number to division
     * @return A reference to the current object
     */
    GFNumber &GFNumber::operator/=(const long &other)
    {
        *this = *this / other;
        return *this;
    }

    /**
     * @brief Operator division the current number and long number.
     * @param other long number to division
     * @return Object number, which is the division of both numbers
     */
    GFNumber GFNumber::operator/(const long &other) const
    {
        assert(other != 0);
        return this->_field.createNumber(this->_n / other);
    }


    /* operator== */

    /**
     * @brief A two-naumber comparison operator
     * @param other Another GFNumber for comparison
     * @return True if they are equal, otherwise false
     */
    bool GFNumber::operator==(const GFNumber &other) const
    {
        return (this->_field == other._field && this->_n == other._n);
    }

    /**
     * @brief A two-naumber ancomparison operator
     * @param other Another GFNumber for ancomparison
     * @return false if they are equal, otherwise true
     */
    bool GFNumber::operator!=(const GFNumber &other) const
    {
        return !(this->_field == other._field && this->_n == other._n);
    }

    /**
     * @brief A current GFNumber and long number comparison operator
     * @param other long number for comparison
     * @return True if they are equal, otherwise false
     */
    bool GFNumber::operator==(const long &other) const
    {
        return (this->getNumber() == other);
    }

    /**
     * @brief A current GFNumber and long number ancomparison operator
     * @param other long number for ancomparison
     * @return false if they are equal, otherwise true
     */
    bool GFNumber::operator!=(const long &other) const
    {
        return (this->getNumber() != other);
    }

    /* operator</> */

    /**
     * @brief Operator checks whether the current number is smaller than another number object
     * @param other Another number object for comparison
     * @return true if the current number is smaller, otherwise false
     */
    bool GFNumber::operator<(const GFNumber &other) const
    {
        assert(this->_field == other._field);
        return this->_n < other._n;
    }

    /**
     * @brief Operator checks whether the current number is bigger than another number object
     * @param other Another number object for comparison
     * @return true if the current number is bigger, otherwise false
     */
    bool GFNumber::operator>(const GFNumber &other) const
    {
        assert(this->_field == other._field);
        return this->_n > other._n;
    }

    /**
     * @brief Operator checks if the current number is smaller or equal than another number object
     * @param other number object for comparison
     * @return true if the current number is smaller or equal, otherwise false
     */
    bool GFNumber::operator<=(const GFNumber &other) const
    {
        return ((*this == other) || *this < other);
    }

    /**
     * @brief Operator checks if the current number is bigger or equal than another number object
     * @param other number object for comparison
     * @return true if the current number is bigger or equal, otherwise false
     */
    bool GFNumber::operator>=(const GFNumber &other) const
    {
        return ((*this == other) || *this > other);
    }

    /**
     * @brief Operator checks whether the current number is smaller than another long number
     * @param other long number for comparison
     * @return true if the current number is smaller, otherwise false
     */
    bool GFNumber::operator<(const long &other) const
    {
        return (*this < this->getField().createNumber(other));
    }

    /**
     * @brief Operator checks if the current number is bigger than another long number
     * @param other long number for comparison
     * @return true if the current number is bigger, otherwise false
     */
    bool GFNumber::operator>(const long &other) const
    {
        return (*this > this->getField().createNumber(other));
    }

    /**
     * @brief Operator checks if the current number is smaller or equal than another long number
     * @param other long number for comparison
     * @return true if the current number is smaller or equal, otherwise false
     */
    bool GFNumber::operator<=(const long &other) const
    {
        return (*this <= this->getField().createNumber(other));
    }

    /**
     * @brief Operator checks if the current number is bigger or equal than another long number
     * @param other long number for comparison
     * @return true if the current number is bigger or equal, otherwise false
     */
    bool GFNumber::operator>=(const long &other) const
    {
        return (*this >= this->getField().createNumber(other));
    }

    /* operator<< / >> */

    /**
     * @brief operator Print the object through a stream
     * @param str stream to print the object
     * @param num The Number object to print
     * @return Reference to the stream
     */
    std::ostream &operator<<(std::ostream &str, const GFNumber &num)
    {
        return (str << num._n << " " << num._field);
    }

    /**
     * @brief operator to get the object through a stream
     * @param str stream to get the object from
     * @param num The Number object to set
     * @return Reference to the stream
     */
    std::istream &operator>>(std::istream &str, GFNumber &num)
    {
        long newNum;
        str >> newNum >> num._field;
        num = GFNumber(newNum, num.getField());
        return str;
    }
