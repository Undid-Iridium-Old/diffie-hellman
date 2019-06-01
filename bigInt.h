

#ifndef BIG_INT_H_
#define BIG_INT_H_

#include<string>
#include<vector>
#include<iostream>

class bigInt{

public:

    bigInt();
    explicit bigInt(const int);
	explicit bigInt(const long long int);
    explicit bigInt(const char *);
    explicit bigInt(const std::string &);


	
	void assignPrimeContainer(std::vector<int> cont);
	std::vector<int> primes(bigInt&);
	bool primeContainerEmpty();


	//Wrapper Operator
    const bigInt operator++(int);
    const bigInt operator--(int);

	//Member Function operators
	bigInt& operator++();
    bigInt& operator--();
    bigInt& operator+();
    bigInt& operator-();
	bigInt& operator+=(const bigInt&);
    bigInt& operator-=(const bigInt&);
    bigInt& operator*=(const bigInt&);
    bigInt& operator/=(const bigInt&);
    bigInt& operator%=(const bigInt&);
    bigInt operator=(const bigInt&);
    bigInt operator=(const std::string&);
	
	//bigInt operator(const std::string&);

	//Wrapper/Friend functions
    friend bigInt pow(const bigInt&, const bigInt&);
    friend bigInt pow(const bigInt&, const int);
	friend std::vector<int> primesWrapper(bigInt&);
	friend long long int toLongInt(const bigInt&);
	friend std::vector<int> primitiveRoots(const bigInt&);
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

	//Integer container, Prime of integer container.
    std::vector<int> container;
	std::vector<int> primeContainer;

	//Pos/Neg Sign
    bool currentSign;

	//Remove Leading Zeros
    void trimVec();

	//Quick Value Checkers

    static bigInt NUMZERO;
    static bigInt NUMONE;
    static bigInt NUMTWO;
    static bigInt NUMTEN;
};









#endif
