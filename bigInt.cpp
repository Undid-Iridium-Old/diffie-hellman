#include"bigInt.h"
#include<vector>
#include<string.h>
#include<algorithm>
#include<ctime>

//Francis X Irizarry

bigInt bigInt::NUMZERO = bigInt(0);
bigInt bigInt::NUMONE  = bigInt(1);
bigInt bigInt::NUMTWO  = bigInt(2);
bigInt bigInt::NUMTEN  = bigInt(10);

bigInt::bigInt(){
    container.clear();
    currentSign = true;
}

bigInt::bigInt(int currVal){
    container.clear();
    if (currVal >= 0)
        currentSign = true;
    else{
        currentSign = false;
        currVal = -currVal;
    }
    if (currVal == 0){
        container.push_back(0);
    }
    while (currVal > 0){
        container.push_back(currVal % 10);
        currVal /= 10;
    }
}

bigInt::bigInt(long long int currVal){
    container.clear();
    if (currVal >= 0)
        currentSign = true;
    else{
        currentSign = false;
        currVal = -currVal;
    }
    if (currVal == 0){
        container.push_back(0);
    }
    while (currVal > 0){
        container.push_back(currVal % 10);
        currVal /= 10;
    }
}

bigInt::bigInt(const char* currVal){
    container.clear();
    currentSign = true;
    int tmpStr = 0;
    if (currVal[0] == '-'){
        currentSign = false;
        tmpStr = 1;
    }
    int len = strlen(currVal);
    for (int currLoc = len - 1; currLoc > 0 + tmpStr; --currLoc){
        container.push_back(currVal[currLoc] - '0');
    }
    container.push_back(currVal[0 + tmpStr] - '0');
}



bigInt::bigInt(const std::string& currVal){
    container.clear();
    currentSign = true;
    int tmpStr = 0;
    if (currVal[0] == '-'){
        currentSign = false;
        tmpStr = 1;
    }
    for (std::string::size_type currLoc = currVal.size() - 1; currLoc > 0 + tmpStr; --currLoc){
        container.push_back(currVal[currLoc] - '0');
    }
    container.push_back(currVal[0 + tmpStr] - '0');
}

bigInt bigInt::operator=(const bigInt& currVal) {
    container.clear();
    currentSign = currVal.currentSign;
    for (std::vector<int>::size_type currLoc = 0; currLoc < currVal.container.size(); ++currLoc) {
        container.push_back(currVal.container.at(currLoc));
    }
    return *this;
}

bigInt bigInt::operator=(const std::string& currVal){
    container.clear();
    currentSign = true;
    int tmpStr = 0;
    if (currVal[0] == '-'){
        currentSign = false;
        tmpStr = 1;
    }
    for (std::string::size_type currLoc = currVal.size() - 1; currLoc > 0 + tmpStr; --currLoc) {
        container.push_back(currVal[currLoc] - '0');
    }
    container.push_back(currVal[0 + tmpStr] - '0');
    return *this;
}

bigInt operator+(const bigInt& leftHSide, const bigInt& rightHSide) {
    bigInt returnVec(leftHSide);
    returnVec += rightHSide;
    return returnVec;
}

bigInt operator-(const bigInt& leftHSide, const bigInt& rightHSide) {
    bigInt returnVec(leftHSide);
    returnVec -= rightHSide;
    return returnVec;
}

bigInt operator*(const bigInt& leftHSide, const bigInt& rightHSide) {
    bigInt returnVec(leftHSide);
    returnVec *= rightHSide;
    return returnVec;
}

bigInt operator/(const bigInt& leftHSide, const bigInt& rightHSide) {
    bigInt returnVec(leftHSide);
    returnVec /= rightHSide;
    return returnVec;
}

bigInt operator%(const bigInt& leftHSide, const bigInt& rightHSide) {
    bigInt returnVec(leftHSide);
	if(leftHSide >= rightHSide){
    	returnVec %= rightHSide;
	}
	return returnVec;
}

bigInt& bigInt::operator+=(const bigInt& currVal){
    if (currentSign == currVal.currentSign) {
        while (container.size() <= currVal.container.size()){
            container.push_back(0);
        }
        int carry = 0;
        std::vector<int>::size_type currLoc;
        for (currLoc = 0; currLoc < currVal.container.size(); ++currLoc){
            container.at(currLoc) += carry + currVal.container.at(currLoc);
            if (container.at(currLoc) >= 10){
                carry = 1;
                container.at(currLoc) -= 10;
            }else
                carry = 0;
        }
        for ( ; currLoc < container.size(); ++currLoc){
            container.at(currLoc) += carry + 0;
            if (container.at(currLoc) >= 10){
                carry = 1;
                container.at(currLoc) -= 10;
				if(currLoc + 1 == container.size()){
					container.push_back(0);
				}
            }else
                carry = 0;
        }
    }else{
        if (currentSign == true && currVal.currentSign == false){
            bigInt tmpStr(currVal);
            tmpStr.currentSign = true;
            *this -= tmpStr;
        }else{
            bigInt tmpStr(*this);
            tmpStr.currentSign = true;
            *this = currVal - tmpStr;
        }
    }
    trimVec();
    return *this;
}

bigInt& bigInt::operator-=(const bigInt& currVal){
    bigInt tmpStr;
    if (*this < currVal){
        tmpStr = *this;
        *this = currVal;
        this->currentSign = false;
    }else{
        tmpStr = currVal;
    }
    int bor = 0;
    std::vector<int>::size_type currLoc;
    for (currLoc = 0; currLoc < tmpStr.container.size(); ++currLoc) {
        container.at(currLoc) -= bor + tmpStr.container.at(currLoc);
        if (container.at(currLoc) < 0){
            bor = 1;
            container.at(currLoc) += 10;
        }else
            bor = 0;
    }
    for ( ; currLoc < container.size(); ++currLoc){
        container.at(currLoc) -= bor;
        if (container.at(currLoc) < 0){
            bor = 1;
            container.at(currLoc) += 10;
        }else
            bor = 0;
    }
    trimVec();
    return *this;
}

bigInt& bigInt::operator*=(const bigInt& currVal){
    bigInt returnVec;
    if (this->currentSign == currVal.currentSign)
        returnVec.currentSign = true;
    else
        returnVec.currentSign = false;
    for (std::vector<int>::size_type currLoc = 0; currLoc < container.size(); ++currLoc){
        for (std::vector<int>::size_type j = 0; j < currVal.container.size(); ++j){
            if (currLoc + j < returnVec.container.size()){
                returnVec.container[currLoc + j] += container.at(currLoc) * currVal.container[j];
            }else{
                returnVec.container.push_back(container.at(currLoc) * currVal.container[j]);
            }
        }
    }
    for (std::vector<int>::size_type currLoc = 0; currLoc < returnVec.container.size(); ++currLoc){
        if (currLoc + 1 < returnVec.container.size()){
            returnVec.container[currLoc + 1] += returnVec.container.at(currLoc) / 10;
        }else if (returnVec.container.at(currLoc) >= 10){
            returnVec.container.push_back(returnVec.container.at(currLoc) / 10);
        }else{
            break;
        }
        returnVec.container.at(currLoc) %= 10;
    }
    returnVec.trimVec();
    *this = returnVec;
    return *this;
}

bigInt& bigInt::operator/=(const bigInt& currVal){
    if (*this == currVal){
        *this = bigInt::NUMONE;
        return *this;
    }
    bigInt returnVec(0);
    if (currentSign == currVal.currentSign)
        returnVec.currentSign = true;
    else
        returnVec.currentSign = false;

    bigInt divider(currVal);

    this->currentSign = true;
    divider.currentSign = true;

    if (*this < divider){
        *this = bigInt::NUMZERO;
        return *this;
    }

    int curCount = 0;
    while (*this > bigInt::NUMZERO){
        if (*this >= divider){
            *this -= divider;
            returnVec += pow(bigInt::NUMTEN, curCount);
            divider *= bigInt::NUMTEN;
            curCount++;
        }else{
            divider = currVal;
            curCount = 0;
            if (*this < divider){
                returnVec.trimVec();
                *this = returnVec;
                return *this;
            }
        }
        divider.currentSign = true;
    }

    returnVec.trimVec();
    *this = returnVec;
    return *this;
}






bigInt& bigInt::operator%=(const bigInt& currVal) {
    *this = *this - (*this / currVal) * currVal;
    return *this;
}

bigInt& bigInt::operator++() {
    *this += bigInt::NUMONE;
    return *this;
}

bigInt& bigInt::operator--() {
    *this -= bigInt::NUMONE;
    return *this;
}

const bigInt bigInt::operator++(int) {
    bigInt temp = *this;
    ++(*this);
    return bigInt(temp);
}

const bigInt bigInt::operator--(int) {
    bigInt temp = *this;
    --(*this);
    return bigInt(temp);
}

bigInt& bigInt::operator+() {
    return *this;
}

bigInt& bigInt::operator-() {
    this->currentSign = !(this->currentSign);
    return *this;
}

bool operator>(const bigInt& leftHSide, const bigInt& rightHSide) {
    return (leftHSide != rightHSide) && (rightHSide < leftHSide);
}

bool operator>=(const bigInt& leftHSide, const bigInt& rightHSide) {
    return !(leftHSide < rightHSide);
}

bool operator<(const bigInt& leftHSide, const bigInt& rightHSide) {
    if (leftHSide.currentSign == false && rightHSide.currentSign == true)
        return true;
    if (leftHSide.currentSign == true && rightHSide.currentSign == false)
        return false;
    if (leftHSide.currentSign){
        if (leftHSide.container.size() < rightHSide.container.size())
            return true;
        else if (leftHSide.container.size() > rightHSide.container.size())
            return false;
    }else{
        if (leftHSide.container.size() < rightHSide.container.size())
            return false;
        else if (leftHSide.container.size() > rightHSide.container.size())
            return true;
    }
    for (std::vector<int>::size_type currLoc = leftHSide.container.size() - 1; currLoc > 0; --currLoc) {
        if (leftHSide.container.at(currLoc) < rightHSide.container.at(currLoc)){
            if (leftHSide.currentSign)
                return true;
            else
                return false;
        }else if (leftHSide.container.at(currLoc) > rightHSide.container.at(currLoc)){
            if (leftHSide.currentSign)
                return false;
            else
                return true;
        }
    }
    if (leftHSide.container.at(0) < rightHSide.container.at(0)){
        if (leftHSide.currentSign)
            return true;
        else
            return false;
    }
    return false;
}

bool operator<=(const bigInt& leftHSide, const bigInt& rightHSide) {
    return !(leftHSide > rightHSide);
}

bool operator==(const bigInt& leftHSide, const bigInt& rightHSide) {
    if (leftHSide.currentSign != rightHSide.currentSign
        || leftHSide.container.size() != rightHSide.container.size())
        return false;
    for (std::vector<int>::size_type currLoc = 0; currLoc < leftHSide.container.size(); currLoc++){
        if (leftHSide.container.at(currLoc) != rightHSide.container.at(currLoc))
            return false;
    }
    return true;
}

bool operator!=(const bigInt& leftHSide, const bigInt& rightHSide) {
    return !(leftHSide == rightHSide);
}


std::istream& operator>>(std::istream& in, bigInt& out_value) {
    std::string tmpStr;
    in >> tmpStr;
    out_value = tmpStr;
    return in;
}

std::ostream& operator<<(std::ostream& ostr, const bigInt& currVal) {
    if (currVal.container.size() == 0){
        ostr << "0";
    }else{
        if (currVal.currentSign == false)
            ostr << '-';
        for (std::vector<int>::size_type currLoc = currVal.container.size() - 1; currLoc > 0; --currLoc) {
            ostr << currVal.container.at(currLoc);
        }
        ostr << currVal.container.at(0);
    }
    return ostr;
}

bigInt pow(const bigInt& currVal, const bigInt& currLoc_powerEXP) {
    if (currLoc_powerEXP == bigInt::NUMZERO || currVal == bigInt::NUMONE){
        return bigInt::NUMONE;
    }
    if (currVal == bigInt::NUMZERO){
        return bigInt::NUMZERO;
    }

    bigInt currLoc(0);
    bigInt returnVec(currVal);
    bigInt powerEXP(currLoc_powerEXP);

    powerEXP -= bigInt::NUMONE;

    while (currLoc < powerEXP){
        returnVec *= currVal;
        ++currLoc;
    }

    return returnVec;
}

bigInt pow(const bigInt& currVal, const int currLoc_powerEXP) {
    bigInt powerEXP(currLoc_powerEXP);
    return pow(currVal, powerEXP);
}


long long int toLongInt(const bigInt& currVal){
	long long int newInt = 0;
	int mul = 1;
	bigInt temp  = currVal;
	reverse(temp.container.begin(), temp.container.end());
	for(int pos = temp.container.size()-1; pos >= 0; pos--){	
		newInt += temp.container.at(pos) * mul;
		mul *= 10;
	}
	return newInt;
}


void bigInt::assignPrimeContainer(std::vector<int> cont) {
	(*this).primeContainer = cont;
}
std::vector<int> bigInt::primes(bigInt& obj) {
	std::vector<int> currprimes;
	bigInt count(0);
	while(count <= obj) {
		currprimes.push_back(1);
		count++;
	}

	bigInt pos(2); 
	for(; pos * pos <= obj; pos++) {
		if(currprimes.at(toLongInt(pos)) == 1) {
			bigInt secondPos = pos * pos;
			for(; secondPos <= obj; secondPos = secondPos + pos) {
				currprimes.at(toLongInt(secondPos)) = 0;
			}
		}
	}

	std::vector<int> onlyPrimes;	
	for (long int ppos=2; ppos<=currprimes.size()-1; ppos++) 
		if (currprimes.at(ppos)) {
		//std::cout << ppos << " "; 
		onlyPrimes.push_back(ppos);
		}
	//std::cout << std::endl;
	obj.assignPrimeContainer(onlyPrimes);
	
	return onlyPrimes ;
}

std::vector<int> primesWrapper(bigInt& obj) {
    obj.primes(obj);
    return obj.primeContainer;
}

bool bigInt::primeContainerEmpty() {
	return primeContainer.empty();
}
/*
#include <set>
#include <unordered_set>

void bigInt::findPrimefactors(unordered_set<bigInt> &s, bigInt n) 
{ 
	// Print the number of 2s that divide n 
	while (n%2 == bigInt::NUMZERO) 
	{ 
		s.insert(NUMTWO);
        cout << n << endl; 
		n = n/2; 
	} 

	// n must be odd at this point. So we can skip 
	// one element (Note i = i +2) sqrt(n)
	for (int i = 3; i <= n/2; i = i+2) 
	{ 
		// While i divides n, print i and divide n 
		while (n%i == 0) 
		{ 
			bigInt newInt(i);
			s.insert(newInt); 
			n = n/i; 
		} 
	} 

	// This condition is to handle the case when 
	// n is a prime number greater than 2 
	if (n > 2) 
		s.insert(n); 

} 
*/
#include <set>
std::vector<int> primitiveRoots(const bigInt& obj) {
	if(obj.primeContainer.empty()){
		std::vector<int> empty(0);
		return empty;
	}
	
	std::srand(std::time(nullptr));
	std::cout << obj << std::endl;
	std::cout << obj.primeContainer.size() << std::endl;
	long int random_variable = (std::rand() % obj.primeContainer.size());
    		std::cout << "Random value on [0 " << RAND_MAX << "]: " 
            	<< random_variable << '\n';
	
	std::cout << obj.primeContainer.at(random_variable) << std::endl;
	std::vector<int> allPrimitiveRoots;

	
	bigInt tempCopyRV(obj.primeContainer.at(random_variable));
	int secondLimit = obj.primeContainer.at(random_variable)-1	;
	int posFound = std::rand() % random_variable;
	std::cout <<tempCopyRV << "   random_variable " << random_variable << " posFound " << posFound << std::endl; //if in set no primitive
	//bool notFound = false;
	//std::vector<long long int> allInts;
	std::set<long long int> allInts;
	

	bigInt finalV;
	bool reset = false;
	while(1){
		bool primitive = true;
		//std::cout << posFound << "\n\n\n\n" << std::endl;
		bigInt objPrime(posFound);
		for(int pos = 0; pos < secondLimit; pos++){
			bigInt tempObj;
			tempObj = pow(objPrime, pos);
			//std::cout << "objPrime : " << objPrime << "  tempCopyRV: " << tempCopyRV << std::endl;
			//std::cout << tempObj % tempCopyRV  << std::endl;
			bigInt modResult = tempObj % tempCopyRV ;
			if(modResult == bigInt::NUMZERO) {
				primitive = false;
				break;
			}
			allInts.insert(toLongInt(modResult));
		}
		//return allInts;
		if(primitive){
			//sort(allInts.begin(), allInts.end());
			if(allInts.size() != secondLimit){
				primitive = false;
			}
			//for(auto val : allInts){
			//	//std::cout << "vall: " << val << "   count " << count << std::endl;
			//	if(count != val){ primitive = false; break;}
			//	count++;
			//}
			
			if(primitive){
				bigInt tempV(posFound);
				finalV = tempV;
				break;
			}
		}
		if(posFound + 1 >= secondLimit){
			if(reset){
				break;
			}
			posFound = 2;
			reset = true;
		}
		else{
			posFound++;
		}
	}
	


	std::cout << "FinalV " << finalV << std::endl;

	for(auto x : allPrimitiveRoots) {
		std::cout << x << std::endl;
	}
	//std::vector<int> n(0);
	return allPrimitiveRoots;

}

void bigInt::trimVec() {
    while (container.size() > 1 && container.at(container.size() - 1) == 0)
        container.pop_back();
}


	//Don't need to use prime numbers for loop, can use any number as long as it is a primitive root; however, using primes reduces time to check
	/*for(int loc = 0; loc < random_variable; loc++) {
		bool primitive = true;
		std::vector<long long int> allInts;
		for(int pos = 0; pos < secondLimit; pos++) {
			bigInt objPrime(obj.primeContainer.at(loc));
			objPrime = pow(objPrime, pos);
			//std::cout << "objPrime : " << objPrime << "  tempCopyRV: " << tempCopyRV << std::endl;
			//std::cout << objPrime % tempCopyRV  << std::endl;
			bigInt modResult = objPrime % tempCopyRV ;
			if(modResult == bigInt::NUMZERO) {
				primitive = false;
				break;
			}
			allInts.push_back(toLongInt(modResult));
		}
		if(primitive){
			std::sort(allInts.begin(), allInts.end());
			for(int count = 1; count < secondLimit; count++){
				if(allInts.at(count-1) != count){
					primitive = false;
				}
			}
			if(primitive){
			allPrimitiveRoots.push_back(obj.primeContainer.at(loc));
			}
		}
	}*/
	//sort(allPrimitiveRoots.begin(), allPrimitiveRoots.end());





/*
bigInt finalV;
	bool reset = false;
	while(1){
		bool primitive = true;
		//std::cout << posFound << "\n\n\n\n" << std::endl;
		bigInt objPrime(posFound);
		for(int pos = 0; pos < secondLimit; pos++){
			bigInt tempObj;
			tempObj = pow(objPrime, pos);
			//std::cout << "objPrime : " << objPrime << "  tempCopyRV: " << tempCopyRV << std::endl;
			//std::cout << tempObj % tempCopyRV  << std::endl;
			bigInt modResult = tempObj % tempCopyRV ;
			if(modResult == bigInt::NUMZERO) {
				primitive = false;
				break;
			}
			allInts.insert(toLongInt(modResult));
		}
		//return allInts;
		if(primitive){
			//sort(allInts.begin(), allInts.end());
			if(allInts.size() != secondLimit){
				primitive = false;
			}
			//for(auto val : allInts){
			//	//std::cout << "vall: " << val << "   count " << count << std::endl;
			//	if(count != val){ primitive = false; break;}
			//	count++;
			//}
			
			if(primitive){
				bigInt tempV(posFound);
				finalV = tempV;
				break;
			}
		}
		if(posFound + 1 >= secondLimit){
			if(reset){
				break;
			}
			posFound = 2;
			reset = true;
		}
		else{
			posFound++;
		}
	}
*/



/*


bool isPrime(int n) 
{ 
    // Corner cases 
    if (n <= 1)  return false; 
    if (n <= 3)  return true; 
  
    // This is checked so that we can skip 
    // middle five numbers in below loop 
    if (n%2 == 0 || n%3 == 0) return false; 
  
    for (int i=5; i*i<=n; i=i+6) 
        if (n%i == 0 || n%(i+2) == 0) 
            return false; 
  
    return true; 
}

*/

/*

//Iterative Function to calculate (x^n)%p in O(logy)
int power(int x, unsigned int y, int p) 
{ 
    int res = 1;     // Initialize result 
  
    x = x % p; // Update x if it is more than or 
    // equal to p 
  
    while (y > 0) 
    { 
        // If y is odd, multiply x with result 
        if (y & 1) 
            res = (res*x) % p; 
  
        // y must be even now 
        y = y >> 1; // y = y/2 
        x = (x*x) % p; 
    } 
    return res; 
} 


*/

/*

/*void bigInt::findPrimefactors(std::unordered_set<bigInt, compareFunc> &s, bigInt n) 
{ 
	// Print the number of 2s that divide n 
	
	while (n%bigInt::NUMTWO == bigInt::NUMZERO) 
	{ 
		s.insert(bigInt::NUMTWO);
        std::cout << n << std::endl; 
		n = n/(bigInt::NUMTWO); 
	} 

	// n must be odd at this point. So we can skip 
	// one element (Note i = i +2) sqrt(n)
	bigInt newInt(3);
	for (; newInt <= n/bigInt::NUMTWO; newInt += bigInt::NUMTWO) 
	{ 
		// While i divides n, print i and divide n 
		
		while (n%newInt == bigInt::NUMZERO) 
		{ 
			s.insert(newInt); 
			n = n/newInt; 
		} 
	} 

	// This condition is to handle the case when 
	// n is a prime number greater than 2 
	if (n > bigInt::NUMTWO) 
		s.insert(n); 

} */
 

	
