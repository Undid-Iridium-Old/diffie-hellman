

#ifndef BIG_INT_H_
#define BIG_INT_H_

#include<string>
#include<vector>
#include<iostream>

class bigInt{

public:

    bigInt();
    explicit bigInt(const int);
    explicit bigInt(const char *);
    explicit bigInt(const std::string &);


    bigInt& operator+=(const bigInt&);
    bigInt& operator-=(const bigInt&);
    bigInt& operator*=(const bigInt&);
    bigInt& operator/=(const bigInt&);
    bigInt& operator%=(const bigInt&);

    bigInt& operator++();
    bigInt& operator--();

    const bigInt operator++(int);
    const bigInt operator--(int);

    bigInt& operator+();
    bigInt& operator-();

    bigInt operator=(const bigInt&);
    bigInt operator=(const std::string&);

    friend bigInt pow(const bigInt&, const bigInt&);
    friend bigInt pow(const bigInt&, const int);
	friend bigInt primes(const bigInt&);
	friend long long int toLongInt(const bigInt&);

    friend std::istream& operator>>(std::istream&, bigInt&);
    friend std::ostream& operator<<(std::ostream&, const bigInt&);

    friend bigInt operator+(const bigInt&, const bigInt&);
    friend bigInt operator-(const bigInt&, const bigInt&);
    friend bigInt operator*(const bigInt&, const bigInt&);
    friend bigInt operator/(const bigInt&, const bigInt&);
    friend bigInt operator%(const bigInt&, const bigInt&);

    friend bool operator>(const bigInt&, const bigInt&);
    friend bool operator>=(const bigInt&, const bigInt&);
    friend bool operator<(const bigInt&, const bigInt&);
    friend bool operator<=(const bigInt&, const bigInt&);

    friend bool operator==(const bigInt&, const bigInt&);
    friend bool operator!=(const bigInt&, const bigInt&);

private:

    std::vector<int> container;
    bool currentSign;

    void trimVec();

    static bigInt NUMZERO;
    static bigInt NUMONE;
    static bigInt NUMTWO;
    static bigInt NUMTEN;
};

#endif
