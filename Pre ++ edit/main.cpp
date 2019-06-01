#include <cstdlib>
#include <iostream>
#include <ctime>
#include "bigInt.h"


using namespace std;
typedef  unsigned long long int linteger;

linteger powerFunc(linteger val, linteger pow){
	if(pow == 1){
		return val;
	}
	return val * powerFunc(val, pow - 1);
	
}

class person{
	public:
		person(){
    		short random_variable = (std::rand() % 10)+(rand() % 3)+2;
    		std::cout << "Random value on [0 " << RAND_MAX << "]: " 
            	<< random_variable << '\n';
			personSecretV = random_variable;
		}
		void displaySecretV(){
			cout << personSecretV << endl;	
		}
		void assignPublicG(linteger val){		
			publicG = new linteger;
			*publicG = val;
			//cout << *publicG << endl;
		}
		void assignPublicP(linteger val){
			publicP = new linteger;
			*publicP = val;
			//cout << *publicP << endl;
		}		
		void prepTrade(){
			//cout <<  powerFunc(*publicG, personSecretV) << " THe power func trade" << endl;
			//bigInt<short int> test1(powerFunc(*publicG, personSecretV));
			userVal = powerFunc(*publicG, personSecretV) % *publicP;
			//biguserVal.assignValEncrypt(publicG, personSecretV, publicP);
		}
		linteger getUserVal(){
			return userVal;
		}
		linteger &getServerVal(){
			return serverVal;
		}
		void postTradeSecretK(){
			//cout << "Public P " << *publicP
			//<< "\n server val : " << serverVal <<
			//"\n personSecret " << personSecretV << endl;
			//cout << powerFunc(serverVal, personSecretV) << endl;
			postSecretKey = powerFunc(serverVal, personSecretV) % *publicP;
		}
		void printSecretKey(){
			cout << postSecretKey << endl;
		}
	private:
		linteger personSecretV;
		linteger * publicG = nullptr;
		linteger * publicP = nullptr;
		linteger serverVal = 0;
		linteger userVal = 0;
		linteger postSecretKey = 0;
		bigInt biguserVal;
		bigInt bigpostSecretKey;
		
};

class keyExchanger{
	public:
		keyExchanger(person &person1, person &person2){
			person1.getServerVal() = person2.getUserVal();
			person2.getServerVal() = person1.getUserVal();
		}	
	private:
};



int main(){
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	int total = 0;
	//crap:
	person person1;
	person person2;
	person1.assignPublicG(5);
	person2.assignPublicG(5);
	person1.assignPublicP(23);
	person2.assignPublicP(23);
	person1.prepTrade();
	person2.prepTrade();
	//cout << person1.getUserVal() << endl;
	//cout << person1.getServerVal() << endl;
	//cout << person2.getUserVal() << endl;
	//cout << person2.getServerVal() << endl;
	//cout << "Pre trade " << endl;
	keyExchanger keyExchange(person1, person2);
	//cout << "Post trade" << endl;
	//cout << person1.getUserVal() << endl;
	//cout << person1.getServerVal() << endl;
	//cout << "\n" << endl;
	person1.postTradeSecretK();
	person2.postTradeSecretK();
	person1.printSecretKey();
	person2.printSecretKey();	
	/*if(total != 10){
		total++;
		goto crap;		
	}*/


	bigInt test1("99");//9123456789 , 987654321
	bigInt test2("1");
	cout << test1 + test2 << " aaaa " << endl;
	//cout << test1.getVec().at(1) << endl;

	long long int tst = std::rand();
	long long int tst1 = std::rand();
	cout << "tst " << tst << "        " << tst1 << endl;
	bigInt test3(tst );
	bigInt test4(tst1 );
	cout << test3 + test4 << " test 3 + 4 " << endl;

	bigInt	ree("451"); //91919191
	bigInt	ree2("6"); //34123
	cout << ree * ree2 <<  " ree * ree2 " << endl;

	bigInt sub1(123456789);//40000, 2000 987654321 123456789
	bigInt sub2(987654321);
	cout << "vals: sub1 " << sub1 << " and sub2 " << sub2 << endl;
	cout << "sub " << sub1 - sub2 << endl;
	//cout << "POWWWAR " << sub1

	bigInt val1(2000);
	bigInt val2(20);
	cout << "POWWWAR   " << "Val1: " << val1 << " Val2: " << val2 << endl;
	//bigInt tempV = pow(val1, val2);
	bigInt tempV("100");
	cout << pow(val1, val2) << endl;
	cout << tempV << endl;

	cout << primes(tempV) << endl;

}













