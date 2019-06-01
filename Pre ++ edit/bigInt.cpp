#include"bigInt.h"
#include<vector>
#include<string.h>
#include<algorithm>

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
    returnVec %= rightHSide;
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


bigInt primes(const bigInt& obj){

	std::vector<int> currprimes;
	bigInt count(0);
	while(count < obj){
		if(count == obj) break;
		//std::cout << "why tho" << count << std::endl;
		currprimes.push_back(1);
		count++;
	}
	bigInt pos(2); 
	std::cout << "currprimes" << currprimes.size() << std::endl;
	std::cout << obj << std::endl;
	for(; pos * pos < obj; pos++){
		if(currprimes.at(toLongInt(pos)) == 1){
			bigInt secondPos = pos * pos;
			//std::cout << " secondPos " << secondPos << std::endl;
			for(; secondPos < obj; secondPos += pos){
				currprimes.at(toLongInt(secondPos)) = false;
			}
			//std::cout << " secondPos " << secondPos << std::endl;
		}
	}
	long long int countV = 2;
	for(auto x : currprimes){
		//std::cout << "nani" << std::endl;
		if(x == 1){
			std::cout << countV << " ";
		}
		countV++;
	}
	std::cout << std::endl;	
	
	return obj ;
}

void bigInt::trimVec() {
    while (container.size() > 1 && container.at(container.size() - 1) == 0)
        container.pop_back();
}

