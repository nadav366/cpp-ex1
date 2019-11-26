//
// Created by tomer on 30/08/2019.
//
#include <sstream>
#include <fstream>
#include <cassert>
#include "GFNumber.h"
#include "GField.h"


using namespace std;

void test1() // basic test - check if you handled n = 0, 1 and prime when getting the prime factors
{
    cout << "------------- test1 - basic template -------------" << endl;
    cout << "If the len is wrong, you will see a msg an abort." << endl;
    cout << "you should check if the printing format is correct yourself" << endl;
    GField field(2, 1);
    GField field2(13, 1);
    GFNumber n1(0, field), n2(1, field);
    GFNumber nPrime(7, field2);
    int len;
    n1.getPrimeFactors(&len);
    if (len != 0)
    {
        cout << "in test 1, n = 0, expected: len=0, got: " << len;
        cout.flush();
        assert(0);
    }
    cout << "expected: " << "0=0*1" << endl;
    cout << "got: ";
    n1.printFactors();
    cout << endl;
    n2.getPrimeFactors(&len);
    if (len != 0)
    {
        cout << "in test 1, n = 1, expected: len=0, got: " << len;
        cout.flush();
        assert(0);
    }
    cout << "expected: " << "1=1*1" << endl;
    cout << "got: ";
    n2.printFactors();
    cout << endl;
    GFNumber* primeList = nPrime.getPrimeFactors(&len);
    if (len != 0)
    {
        cout << "in test 1, n = 7, expected: len=0, got: " << len;
        cout.flush();
        assert(0);
    }
    cout << "expected: " << "7=7*1" << endl;
    cout << "got: ";
    nPrime.printFactors();
    cout << "------------- test1 - ended. check your results -------------" << endl;
}

void test2() // ctors tests, including basic tests and advance: adjusting negative numbers, conversions etc
{
    cout << "------------- test2 - ctors tests -------------" << endl;
    // creates 3 different fields
    GField f1;
    GField f2(7);
    GField f3(5, 2);
    GField f4(-5, 2);

    // checks the validation of the created fields
    if (f1.getChar() != 2)
    {
        cout << "in test 2, problem with f1: expected p == 2, got: p==" << f1.getChar();
        cout.flush();
        assert(0);
    }
    if (f1.getDegree() != 1)
    {
        cout << "in test 2, problem with f1: expected l == 1, got: l==" << f1.getDegree();
        cout.flush();
        assert(0);
    }
    if (f2.getDegree() != 1)
    {
        cout << "in test 2, problem with f2: expected l == 1, got: l==" << f2.getDegree();
        cout.flush();
        assert(0);
    }
    if (f3.getChar() != 5)
    {
        cout << "in test 2, problem with f3: expected p == 5, got: p==" << f3.getChar();
        cout.flush();
        assert(0);
    }
    if (f3.getDegree() != 2)
    {
        cout << "in test 2, problem with f3: expected l == 2, got: l==" << f3.getDegree();
        cout.flush();
        assert(0);
    }

    GFNumber n1;
    GFNumber n2 = -5; // should work as a conversion of long to GFNumber. field should be 2, n should be 1.
    GFNumber n3(16, f2);

    if (n1.getNumber() != 0)
    {
        cout << "in test 2, problem with n1: expected n == 0, got: n==" << n1.getNumber();
        cout.flush();
        assert(0);
    }

    if (n1.getField().getOrder() != 2)
    {
        cout << "in test 2, problem with n1: expected order == 2, got: order==" << n1.getField().getOrder();
        cout.flush();
        assert(0);
    }

    if (n2.getNumber() != 1)
    {
        cout << "in test 2, problem with n2: expected n == 1, got: n==" << n2.getNumber();
        cout.flush();
        assert(0);
    }

    if (n2.getField().getOrder() != 2)
    {
        cout << "in test 2, problem with n2: expected order == 2, got: order==" << n2.getField().getOrder();
        cout.flush();
        assert(0);
    }

    if (n3.getNumber() != 2)
    {
        cout << "in test 2, problem with n3: expected n == 2, got: n==" << n3.getNumber();
        cout.flush();
        assert(0);
    }
    GFNumber n4(-3, f2);  // f2.field == 7.
    if (n4.getNumber() != 4)
    {
        cout << "in test 2, problem with n4: expected n == 4, got: n==" << n4.getNumber();
        cout.flush();
        assert(0);
    }
    // check copy ctor and "=" operator (to make sure you really do deep copy)
    GField copiedF2 = f2;
    GField newF2(17, 2);
    f2 = newF2; // should not change the copy.
    GFNumber copiedN2 = n2;
    n2 = 17;  // should not change the copy.
    if (copiedF2.getDegree() != 1)
    {
        cout << "in test 2, problem with copiedF2: expected l == 1, got: l==" << copiedF2.getDegree();
        cout.flush();
        assert(0);
    }
    if (copiedF2.getChar() != 7)
    {
        cout << "in test 2, problem with copiedF2: expected p == 7, got: p==" << copiedF2.getChar();
        cout.flush();
        assert(0);
    }

    if (copiedN2.getNumber() != 1)
    {
        cout << "in test 2, problem with copiedN2: expected n == 1, got: n==" << copiedN2.getNumber();
        cout.flush();
        assert(0);
    }

    if (copiedN2.getField().getOrder() != 2)
    {
        cout << "in test 2, problem with copiedN2: expected order == 2, got: order==" << copiedN2.getField().getOrder();
        cout.flush();
        assert(0);
    }

    if (f4.getChar() != 5)
    {
        cout << "in test 2, problem with f4: expected char == 5, got: order==" << f4.getChar();
        cout.flush();
        assert(0);
    }
    cout << "------------- test2 - ended, you passed it all! -------------" << endl;
}

void test3() // check arithmetic operations, including negative numbers and din or ,mod 0. also checks the print format
{
    cout << "------------- test3 - arithmetic and field + number printing format -------------" <<endl;
    cout << "if you got the wrong value, you will see a msg an abort. compare the printing format yourself" << endl;

    GField field(13, 1);
    GFNumber n1(6, field);
    GFNumber n2(9, field);
    GFNumber n3(-10, field);  // n = 3

    // checking +
    GFNumber n12 = n1 + n2;
    if (n12.getNumber() != 2)
    {
        cout << "in test 3, problem with n1 + n2: expected 2, got: "<< n12.getNumber();
        cout.flush();
        assert(0);
    }
    cout << "expected: " << "2 GF(13**1)" << endl;
    cout << "got: " << n12;
    cout << endl;

    GFNumber n13 = n1 + n3;
    if (n13.getNumber() != 9)
    {
        cout << "in test 3, problem with n1 + n3: expected 9, got: "<< n13.getNumber();
        cout.flush();
        assert(0);
    }
    cout << "expected: " << "9 GF(13**1)" << endl;
    cout << "got: " << n13;
    cout << endl;

    cout << "not gonna check the printing format anymore. running more tests......." << endl;
    GFNumber n2m6 = n2 + (-6);
    if (n2m6.getNumber() != 3)
    {
        cout << "in test 3, problem with n2 + (-6): expected 3, got: "<< n2m6.getNumber();
        cout.flush();
        assert(0);
    }

    GFNumber n2m12 = n2 + (-12);
    if (n2m12.getNumber() != 10)
    {
        cout << "in test 3, problem with n2 + (-12): expected 10, got: "<< n2m12.getNumber();
        cout.flush();
        assert(0);
    }

    // checking +=
    n1 += n2;  // now n1 is 2
    if (n1.getNumber() != 2)
    {
        cout << "in test 3, problem with n1 += n2: expected 2, got: "<< n1.getNumber();
        cout.flush();
        assert(0);
    }

    n1 += (-3);
    if (n1.getNumber() != 12)
    {
        cout << "in test 3, problem with n1 += (-3): expected 12, got: "<< n1.getNumber();
        cout.flush();
        assert(0);
    }
    n3 += (-3);
    if (n3.getNumber() != 0)
    {
        cout << "in test 3, problem with n3 += (-3): expected 0, got: "<< n3.getNumber();
        cout.flush();
        assert(0);
    }

    // checking -
    n2 = n2 - n3;
    if (n2.getNumber() != 9)
    {
        cout << "in test 3, problem with n2 - n3: expected 9, got: "<< n2.getNumber();
        cout.flush();
        assert(0);
    }
    n2 -= (-3); // -3 = 10 --> 9 - 10 = -1 -->12
    if (n2.getNumber() != 12)
    {
        cout << "in test 3, problem with n2 += -3: expected 12, got: "<< n2.getNumber();
        cout.flush();
        assert(0);
    }
    // checking %
    if((n1 % n2).getNumber() != 0)
    {
        cout << "in test 3, problem with n1 % n2: expected 0, got: "<< (n1 % n2).getNumber();
        cout.flush();
        assert(0);
    }
    n1 %= (-8);  // -8 --> 5; n1 = 12
    if(n1.getNumber() != 2)
    {
        cout << "in test 3, problem with n1 %= (-8): expected 2, got: "<< n1.getNumber();
        cout.flush();
        assert(0);
    }
    cout << "------------- test3 - ended, make sure you print in the right format. did not check *, *= -------------" << endl;
}
void test4() // assert tests
{
    cout << "------------- test4 - assert tests -------------" << endl;
    cout << "all the tests here are in a comment. each should abort the program" << endl;
    cout << "uncomment each one every time, and make sure your program abort with assert" << endl;
    GField constF(3, 4); // don't make this comment!
    GField constF2(5, 4);  // don't make this comment!
    GFNumber n1(7, constF);
    GFNumber n2(7, constF2);
//    GField _f(6, 4); // (1)
//    GField _f(5, 0); // (2)
//    GField _f(5, -2); // (3)
//    GFNumber n3 = n1 + n2; // (4)
//    GFNumber n4 = n1 - n2;  // (5)
//    n1 *= n2;  // (6)
//    n2 % 0; // (7)
//    constF.gcd(n1, n2); // (8)
//    GField _f(1, 3); // (9)
    cout << "------------- test4 - ended successfully -------------" << endl;

}

void test5() // iostrem
{
    cout << "------------- test5 - cin -------------" << endl;
    cout << "type 12 3 2 and press ENTER" << endl;
    GFNumber n;
    cin >> n;
    if (n.getNumber() != 3)
    {
            cout << "in test 5, problem with first read: expected n = 3, got: "<< n.getNumber();
            cout.flush();
            assert(0);
    }
    if (n.getField().getOrder() != 9)
    {
        cout << "in test 5, problem with first read: expected order = 9, got: "<< n.getField().getOrder();
        cout.flush();
        assert(0);
    }
    cout << "type -5 13 1 and press ENTER" << endl;
    cin >> n;
    if (n.getNumber() != 8)
    {
        cout << "in test 5, problem with second read: expected n = 8, got: "<< n.getNumber();
        cout.flush();
        assert(0);
    }
    cout << "------------- test5 - finished -------------" << endl;
}

void test6() // other GField functions
{
    if (GField::isPrime(122644))
    {
        cout << "in test 6, returned 122644 is prime";
        cout.flush();
        assert(0);
    }
    if (!GField::isPrime(2311))
    {
        cout << "in test 6, returned 2311 is not prime, when it is";
        cout.flush();
        assert(0);
    }
    GField f(2311, 1);
    GFNumber a(1532, f);
    GFNumber b = f.createNumber(12);
    if (b.getNumber()!= 12)
    {
        cout << "in test 6, failed to create number. expected: 12, got: " << b.getNumber();
        cout.flush();
        assert(0);
    }
    GFNumber g = f.gcd(a, b);
    if (g.getNumber()!= 4)
    {
        cout << "in test 6, got wrong gcd. expected: 4, got: " << g.getNumber();
        cout.flush();
        assert(0);
    }
    if (g.getField() != f || b.getField() != f)
    {
        cout << "in test 6, got wrong field back from gcd of from createNumber.";
        cout.flush();
        assert(0);
    }
    GFNumber n = f.createNumber(-7);
    if (n.getNumber() != 2304)
    {
        cout << "in test 6, got wrong n in create number. expected: 2304, got: " << n.getNumber();
        cout.flush();
        assert(0);
    }
    cout << "------------- test6 - finished -------------" << endl;
}

void test7() // tests the primeList and the print function (not the same as test 1).
{
    cout << "------------- test7 - primeList -------------" << endl;
    cout << "If the len is wrong, you will see a msg an abort." << endl;
    cout << "you should check that the printing format is correct yourself" << endl;
    int len;
    GFNumber* primeList;
    GField field(9699631, 1);
    GFNumber n1(297936, field);
    GFNumber n2(68, field);
    primeList = n1.getPrimeFactors(&len);
    if (len != 7)
    {
        cout << "in test 7, n = 297936, expected: len=7, got: " << len;
        cout.flush();
        assert(0);
    }
    cout << "expected: " << "297936=2*2*2*2*3*3*2069" << endl;
    cout << "got: ";
    n1.printFactors();
    if(primeList[4].getNumber() != 3)
    {
        cout << "in test 7, n = 297936, expected: number to be 3, got: " << primeList[4].getNumber();
        cout.flush();
        assert(0);
    }

    primeList = n2.getPrimeFactors(&len);
    if (len != 3)
    {
        cout << "in test 7, n = 68, expected: len=3, got: " << len;
        cout.flush();
        assert(0);
    }
    cout << "expected: " << "68=2*2*17" << endl;
    cout << "got: ";
    n2.printFactors();

    cout << "------------- test7 - finished -------------" << endl;
}


int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
}