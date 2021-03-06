/*
 * @author harshit
 * Big Integer library in C++
 */
#include "BigInteger.h"
BigInteger::BigInteger()
{ // empty constructor initializes zero
    number = "0";
    sign = false;
}
//defining some useful constants
BigInteger zero("0");
BigInteger one("1");
BigInteger two("2");
BigInteger three("3");


BigInteger::BigInteger(string s)
{ // "string" constructor
    if (isdigit(s[0]))
    {
        // if not signed
        //cout<<"hello";
        setNumber(s);
        sign = false; // +ve
    }
    else
    {
        setNumber(s.substr(1));
        sign = (s[0] == '-');
    }
}

BigInteger::BigInteger(string s, bool sin)
{ // "string" constructor
    setNumber(s);
    setSign(sin);
}

BigInteger::BigInteger(int n)
{ // "int" constructor
    stringstream ss;
    string s;
    ss << n; //converts number into stream of string ,alternative of it is using stoi
    ss >> s;

    if (isdigit(s[0]))
    { // if not signed
        setNumber(s);
        setSign(false); // +ve
    }
    else
    {
        setNumber(s.substr(1));
        setSign(s[0] == '-');
    }
}

void BigInteger::setNumber(string s)
{
    number = s;
}

const string &BigInteger::getNumber()
{ // retrieves the number
    return number;
}

void BigInteger::setSign(bool s)
{
    sign = s;
}

const bool &BigInteger::getSign()
{
    return sign;
}

BigInteger BigInteger::absolute()
{
    return BigInteger(getNumber()); // +ve by default
}
void BigInteger::operator=(const long long &a)
{
    setNumber(to_string(a));
    setSign(a > 0 ? true : false);
}
void BigInteger::operator=(BigInteger b)
{
    setNumber(b.getNumber());
    setSign(b.getSign());
}

bool BigInteger::operator==(BigInteger b)
{
    return equals((*this), b); //this is pointer to object *this is the object which called the function
}

bool BigInteger::operator!=(BigInteger b)
{
    return !equals((*this), b);
}

bool BigInteger::operator>(BigInteger b)
{
    return greater((*this), b);
}

bool BigInteger::operator<(BigInteger b)
{
    return less((*this), b);
}

bool BigInteger::operator>=(BigInteger b)
{
    return equals((*this), b) || greater((*this), b);
}

bool BigInteger::operator<=(BigInteger b)
{
    return equals((*this), b) || less((*this), b);
}

BigInteger &BigInteger::operator++()
{ // prefix
    (*this) = (*this) + 1;
    return (*this);
}

BigInteger BigInteger::operator++(int)
{ // postfix
    BigInteger before = (*this);

    (*this) = (*this) + 1;

    return before;
}

BigInteger &BigInteger::operator--()
{ // prefix
    (*this) = (*this) - 1;
    return (*this);
}

BigInteger BigInteger::operator--(int)
{ // postfix
    BigInteger before = (*this);

    (*this) = (*this) - 1;

    return before;
}

BigInteger BigInteger::operator+(BigInteger b)
{
    BigInteger addition;
    if (getSign() == b.getSign())
    { // both +ve or -ve
        addition.setNumber(add(getNumber(), b.getNumber()));
        addition.setSign(getSign());
    }
    else
    { // sign different
        if (absolute() > b.absolute())
        {
            addition.setNumber(subtract(getNumber(), b.getNumber()));
            addition.setSign(getSign());
        }
        else
        {
            addition.setNumber(subtract(b.getNumber(), getNumber()));
            addition.setSign(b.getSign());
        }
    }
    if (addition.getNumber() == "0") // avoid (-0) problem
        addition.setSign(false);

    return addition;
}

BigInteger BigInteger::operator-(BigInteger b)
{
    b.setSign(!b.getSign()); // x - y = x + (-y)
    return (*this) + b;
}

BigInteger BigInteger::operator*(BigInteger b)
{
    BigInteger mul;

    mul.setNumber(multiply(getNumber(), b.getNumber()));
    mul.setSign(getSign() != b.getSign());

    if (mul.getNumber() == "0") // avoid (-0) problem
        mul.setSign(false);

    return mul;
}

// Warning: Denomerator must be within "long long" size not "BigInteger"
BigInteger BigInteger::operator/(BigInteger b)
{
    long long den = toInt(b.getNumber());
    BigInteger div;

    div.setNumber(divide(getNumber(), den).first);
    div.setSign(getSign() != b.getSign());

    if (div.getNumber() == "0") // avoid (-0) problem
        div.setSign(false);

    return div;
}

// Warning: Denomerator must be within "long long" size not "BigInteger"
BigInteger BigInteger::operator%(BigInteger b)
{
    long long den = toInt(b.getNumber());

    BigInteger rem;
    long long rem_int = divide(number, den).second;
    rem.setNumber(toString(rem_int));
    rem.setSign(getSign() != b.getSign());

    if (rem.getNumber() == "0") // avoid (-0) problem
        rem.setSign(false);

    return rem;
}

BigInteger &BigInteger::operator+=(BigInteger b)
{
    (*this) = (*this) + b;
    return (*this);
}

BigInteger &BigInteger::operator-=(BigInteger b)
{
    (*this) = (*this) - b;
    return (*this);
}

BigInteger &BigInteger::operator*=(BigInteger b)
{
    (*this) = (*this) * b;
    return (*this);
}

BigInteger &BigInteger::operator/=(BigInteger b)
{
    (*this) = (*this) / b;
    return (*this);
}

BigInteger &BigInteger::operator%=(BigInteger b)
{
    (*this) = (*this) % b;
    return (*this);
}

BigInteger &BigInteger::operator[](int n)
{
    return *(this + (n * sizeof(BigInteger)));
}

BigInteger BigInteger::operator-()
{ // unary minus sign
    return (*this) * -1;
}

BigInteger::operator string()
{                                                 // for conversion from BigInteger to string
    string signedString = (getSign()) ? "-" : ""; // if +ve, don't print + sign
    signedString += number;
    return signedString;
}

bool BigInteger::equals(BigInteger n1, BigInteger n2)
{
    return n1.getNumber() == n2.getNumber() && n1.getSign() == n2.getSign();
}

bool BigInteger::less(BigInteger n1, BigInteger n2)
{
    bool sign1 = n1.getSign();
    bool sign2 = n2.getSign();

    if (sign1 && !sign2) // if n1 is -ve and n2 is +ve
        return true;

    else if (!sign1 && sign2)
        return false;

    else if (!sign1)
    { // both +ve
        if (n1.getNumber().length() < n2.getNumber().length())
            return true;
        if (n1.getNumber().length() > n2.getNumber().length())
            return false;
        return n1.getNumber() < n2.getNumber();
    }
    else
    { // both -ve
        if (n1.getNumber().length() > n2.getNumber().length())
            return true;
        if (n1.getNumber().length() < n2.getNumber().length())
            return false;
        return n1.getNumber().compare(n2.getNumber()) > 0; // greater with -ve sign is LESS
    }
}

bool BigInteger::greater(BigInteger n1, BigInteger n2)
{
    return !equals(n1, n2) && !less(n1, n2);
}

string BigInteger::add(string number1, string number2)
{
    string add = (number1.length() > number2.length()) ? number1 : number2;
    char carry = '0';
    int differenceInLength = abs((int)(number1.size() - number2.size()));

    if (number1.size() > number2.size())
        number2.insert(0, differenceInLength, '0'); // put zeros from left

    else // if(number1.size() < number2.size())
        number1.insert(0, differenceInLength, '0');

    for (int i = number1.size() - 1; i >= 0; --i)
    {
        add[i] = ((carry - '0') + (number1[i] - '0') + (number2[i] - '0')) + '0';

        if (i != 0)
        {
            if (add[i] > '9')
            {
                add[i] -= 10;
                carry = '1';
            }
            else
                carry = '0';
        }
    }
    if (add[0] > '9')
    {
        add[0] -= 10;
        add.insert(0, 1, '1');
    }
    return add;
}

string BigInteger::subtract(string number1, string number2)
{
    string sub = (number1.length() > number2.length()) ? number1 : number2;
    int differenceInLength = abs((int)(number1.size() - number2.size()));

    if (number1.size() > number2.size())
        number2.insert(0, differenceInLength, '0');

    else
        number1.insert(0, differenceInLength, '0');

    for (int i = number1.length() - 1; i >= 0; --i)
    {
        if (number1[i] < number2[i])
        {
            number1[i] += 10;
            number1[i - 1]--;
        }
        sub[i] = ((number1[i] - '0') - (number2[i] - '0')) + '0';
    }

    while (sub[0] == '0' && sub.length() != 1) // erase leading zeros
        sub.erase(0, 1);

    return sub;
}

string BigInteger::multiply(string n1, string n2)
{
    if (n1.length() > n2.length())
        n1.swap(n2);

    string res = "0";
    for (int i = n1.length() - 1; i >= 0; --i)
    {
        string temp = n2;
        int currentDigit = n1[i] - '0';
        int carry = 0;

        for (int j = temp.length() - 1; j >= 0; --j)
        {
            temp[j] = ((temp[j] - '0') * currentDigit) + carry;

            if (temp[j] > 9)
            {
                carry = (temp[j] / 10);
                temp[j] -= (carry * 10);
            }
            else
                carry = 0;

            temp[j] += '0'; // back to string mood
        }

        if (carry > 0)
            temp.insert(0, 1, (carry + '0'));

        temp.append((n1.length() - i - 1), '0'); // as like mult by 10, 100, 1000, 10000 and so on

        res = add(res, temp); // O(n)
    }

    while (res[0] == '0' && res.length() != 1) // erase leading zeros
        res.erase(0, 1);

    return res;
}
BigInteger BigInteger::GCD(BigInteger a, BigInteger b)//to find GCD of two BigIntegers
{

    if (a.getNumber() == "0")
        return b;
    else
        return GCD(b % a, a);
}

pair<string, long long> BigInteger::divide(string n, long long den)//to divide two BigIntegers
{
    long long rem = 0;
    string result;
    result.resize(MAX);

    for (int indx = 0, len = n.length(); indx < len; ++indx)
    {
        rem = (rem * 10) + (n[indx] - '0');
        result[indx] = rem / den + '0';
        rem %= den;
    }
    result.resize(n.length());

    while (result[0] == '0' && result.length() != 1)
        result.erase(0, 1);

    if (result.length() == 0)
        result = "0";

    return make_pair(result, rem);
}

string BigInteger::toString(long long n)// to convert to string value
{
    stringstream ss;
    string temp;

    ss << n;
    ss >> temp;

    return temp;
}

long long BigInteger::toInt(string s)// to convert to integer value
{
    long long sum = 0;

    for (int i = 0; i < s.length(); i++)
        sum = (sum * 10) + (s[i] - '0');

    return sum;
}
BigInteger BigInteger::pow(int const &power, std::map<int, BigInteger> &lookup){
    if (power == 1)
        return *this;
    if (lookup.count(power))
        return lookup[power];

    int closestPower = 1;
    while (closestPower < power)
        closestPower <<= 1;
    closestPower >>= 1;

    if (power == closestPower)
        lookup[power] = pow(power / 2, lookup) * pow(power / 2, lookup);
    else
        lookup[power] = pow(closestPower, lookup) * pow(power - closestPower, lookup);

    return lookup[power];
}
BigInteger BigInteger::sqrt() //returns floorsqrt(n)
{
    BigInteger low = zero;
    BigInteger high = *this;
    BigInteger mid;
    BigInteger best;
    while (low <= high)
    {
        mid = (low + high) / two;
        if (mid * mid == *this)
            return mid;
        else if (mid * mid <= *this)
        {
            best = mid;
            low = mid + one;
        }
        else
            high = mid - 1;
    }
    return best;
}
bool BigInteger::prime()//to check if two BigIntegers are prime or not
{

    if ((*this % two) == zero)
        return false;
    if ((*this % three) == zero)
        return false;
    else
    {
        BigInteger a("5");
        BigInteger b = (*this).sqrt();
        while (a < b)
        {
            if (*this % a == zero || *this % (a + 2) == zero)
                return false;
            a++;
        }
        return true;
    }
}
BigInteger &BigInteger::Pow(int const &power)//to calculate BigInteger^power,Note:power is an integer
{
    std::map<int, BigInteger> lookup;
    if (power % 2 == 0 && !sign)
    {
        sign = true;
    }
    *this = pow(power, lookup);

    return *this;
}
BigInteger BigInteger::factorial(int n)//to find factorial of integer which may become too large to be stored by long long .
{
    BigInteger result = 1;
    if (n % 2)
    {
        result = n;
        --n;
    }
    int last = 0;
    for (; n >= 2; n -= 2)
    {
        result = result * BigInteger(to_string(n + last));
        last += n;
    }

    return result;
}
std::istream &operator>>(std::istream &in, BigInteger &a)//overloading operator "stream extraction" to input BigInteger
{
    std::string str;
    in >> str;

    a = str;

    return in;
}

std::ostream &operator<<(std::ostream &out, BigInteger &a)//overloading operator "stream insertion" to output BigInteger
{

    if (a.getSign())
        out << "-";
    out << a.getNumber();
    return out;
}
