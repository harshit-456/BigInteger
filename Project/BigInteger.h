/*
 * @author harshit
 * Big Integer header in C++
 */
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <map>
#define MAX 10000 // for strings

using namespace std;
//-------------------------------------------------------------
class BigInteger
{
private:
    string number;
    bool sign;

public:
    BigInteger();                   // empty constructor initializes zero
    BigInteger(string s);           // "string" constructor
    BigInteger(string s, bool sin); // "string" constructor
    BigInteger(int n);              // "int" constructor
    void setNumber(string s);
    const string &getNumber(); // retrieves the number
    void setSign(bool s);
    const bool &getSign();
    BigInteger absolute(); // returns the absolute value
    void operator=(BigInteger b);
    void operator=(const long long &a);
    bool operator==(BigInteger b);
    bool operator!=(BigInteger b);
    bool operator>(BigInteger b);
    bool operator<(BigInteger b);
    bool operator>=(BigInteger b);
    bool operator<=(BigInteger b);
    bool prime();
    BigInteger &operator++();   // prefix
    BigInteger operator++(int); // postfix
    BigInteger &operator--();   // prefix
    BigInteger operator--(int); // postfix
    BigInteger operator+(BigInteger b);
    BigInteger operator-(BigInteger b);
    BigInteger operator*(BigInteger b);
    BigInteger operator/(BigInteger b);
    BigInteger operator%(BigInteger b);
    BigInteger &operator+=(BigInteger b);
    BigInteger &operator-=(BigInteger b);
    BigInteger &operator*=(BigInteger b);
    BigInteger &operator/=(BigInteger b);
    BigInteger &operator%=(BigInteger b);
    BigInteger &operator[](int n);
    BigInteger operator-(); // unary minus sign
    operator string();      // for conversion from BigInteger to string
    BigInteger GCD(BigInteger a, BigInteger b);
    BigInteger pow(int const &power, std::map<int, BigInteger> &lookup);
    BigInteger &Pow(int const &power);
    BigInteger factorial(int n);
    BigInteger sqrt();

private:
    bool equals(BigInteger n1, BigInteger n2);
    bool less(BigInteger n1, BigInteger n2);
    bool greater(BigInteger n1, BigInteger n2);
    string add(string number1, string number2);
    string subtract(string number1, string number2);
    string multiply(string n1, string n2);
    pair<string, long long> divide(string n, long long den);
    string toString(long long n);
    long long toInt(string s);
};
