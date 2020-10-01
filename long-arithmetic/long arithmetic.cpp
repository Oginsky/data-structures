#include "long arithmetic.h"

BIGINT::BIGINT() {
	
}
BIGINT::BIGINT(unsigned size) {
	if(size < 0) exit(2);
	digit.reserve(size);
}
BIGINT::BIGINT(string value) {
	int i = value.size()-1;
	while(i) this->digit.push_back((int)value[i] - (int)'0'), i--;
	if(value[0] == '-') 
		this->_negative = true;
	else
		digit.push_back((int)value[0] - (int)'0');
	
}
BIGINT::BIGINT(char* value) {
	*this = (string)value;
//	int i = strlen(value)-1;
//	while(i) this->digit.push_back((int)value[i] - (int)'0'), i--;
//	if(value[0] == '-') 
//		this->_negative = true;
//	else
//		digit.push_back((int)value[0] - (int)'0');
} 
BIGINT::BIGINT(const BIGINT& copy) {
	this->_negative = copy._negative;
	this->_digree_of_ten = copy._digree_of_ten;
	this->digit = copy.digit;
}
BIGINT::~BIGINT() {
	_negative = false;
	_digree_of_ten = true;
	digit.clear();
}

BIGINT BIGINT::operator+(const BIGINT& right) const {
	if(this->_negative == right._negative)
		return sum(*this, right);
	else 
		return minus(*this, right);
}
BIGINT BIGINT::operator-(const BIGINT& right) const {
	if(this->_negative != right._negative) {
		if(right._negative) return sum(*this, right);
		else {
			BIGINT result = sum(*this, right);
			result._negative  = true;
			return result;
		}
	}
	return minus(*this, right);
}
BIGINT sum(const BIGINT& left, const BIGINT& right) {
	BIGINT result;
		if(left._negative && right._negative) result._negative = true;
		vector<int>::const_iterator max, min;
		int lenght, lmax, mod = 0, temp;
		
		if(left.digit.size() >= right.digit.size()) {
			max = left.digit.begin();
			min = right.digit.begin();
			lenght = right.digit.size();
			lmax = left.digit.size() - lenght;
		}
		else {
			max = right.digit.begin();
			min = left.digit.begin();
			lenght = left.digit.size();
			lmax = right.digit.size() - lenght;
		}
		
		while(lenght--) {
			temp = *max + *min + mod;
			result.digit.push_back( (temp >= 10) ? temp - 10 : temp );
			mod = (temp >= 10) ? 1 : 0;
			min++, max++;
		}
		while(lmax--) { 
			temp = *max + mod;
			result.digit.push_back( (temp >= 10) ? temp - 10 : temp );
			mod = (temp >= 10) ? 1 : 0;
			max++;
		}
		if(mod) result.digit.push_back(1);
		
		return result;
}
BIGINT minus(const BIGINT& left, const BIGINT& right) {
	BIGINT res;
		int carry = 0;
		int i;
		for(i = 0; i < right.digit.size(); i++) {
			res.digit.push_back(left.digit[i] - right.digit[i] - carry);
			carry = 0;
			if(res.digit[i] < 0) {
				res.digit[i] += 10;
				carry = 1;
			}
		}
		while(i < left.digit.size()) {
			res.digit.push_back(left.digit[i++] - carry);
			carry = 0;
		}
		while(!res.digit.back()) res.digit.pop_back();
		if(res.digit.empty()) res.digit.push_back(0);
		return res;
}
		
pair<int,int> normalization(const BIGINT& first, const BIGINT& second) {
	// first - extra zeros for xr, second - extra zeros for yr;
	int size = max(first.digit.size(), second.digit.size());
	if(size % 2) size++;
	return std::make_pair(size - first.digit.size(), size - second.digit.size());
}
BIGINT BIGINT::operator*(const BIGINT& right) const {
	BIGINT result;
	if(this->_negative != right._negative) result._negative = true;
	
	if(this->digit.size() + right.digit.size() <= 4) {
		result.digit.resize(this->digit.size() + right.digit.size(), 0);
		int mod, i, j;
		for (i = 0; i < this->digit.size(); i++) {
			mod = 0;
			for (j = 0; j < right.digit.size(); j++) {
				result.digit[i+j] += this->digit[i] * right.digit[j] + mod;
			//	cout << i+j << ": " << result.digit[i+j];
				mod = result.digit[i+j] / 10;
			//	cout << " " << result.digit[i+j] << " ";
				result.digit[i+j] -= mod*10;
			//	cout << "¬ " << i + j << " разр€д положили " << result.digit[i+j] << endl;
			}
			cout << endl;
		if(mod) result.digit[i+j+1] += mod;
		}
		while(!result.digit.back()) result.digit.pop_back();
		cout << "standart: ";
		this->print();
		cout << " * ";
		right.print();
		cout <<  " = ";
		cout << result << endl;
		if(!result.digit.size()) result.digit.push_back(0);
	}
	// Karatsuba
	else {
		cout << "---------------------------------------------\n";
		
		unsigned fic_zero = 0;
		BIGINT xl, xr, yl, yr;
		pair<int, int> zero = normalization(*this, right);
		xl.digit.resize((this->digit.size()+zero.first)/ 2);
		xr.digit.resize((this->digit.size()+zero.first )/ 2, 0);
		yl.digit.resize((right.digit.size() + zero.second) / 2);
		yr.digit.resize((right.digit.size() + zero.second) / 2, 0);
		int i, j = 0;
		fic_zero = zero.first + zero.second;
		
		for(i = this->digit.size()/2; i < this->digit.size(); i++, j++) xl.digit[j] = this->digit[i];
		for(i = 0; i < this->digit.size()/2; i++) xr.digit[zero.first++] = this->digit[i];
		
		j = 0;
		
		for(i = right.digit.size()/2; i < right.digit.size(); i++, j++) yl.digit[j] = right.digit[i];
		for(i = 0; i < right.digit.size()/2; i++) yr.digit[zero.second++] = right.digit[i];
		
			cout << "xl = " << xl << "\txr = " << xr << endl;
		cout << "yl = " << yl << "\tyr = " << yr << endl;
	
		int msize = max(this->digit.size(), right.digit.size());
		if(msize%2) msize++;
		
		BIGINT t1 = (xl * yl);
		BIGINT t2 = (xr * yr);
		BIGINT t3 = (xl+xr)*(yl+yr);
		t3 = t3 - t1;
		t3 = t3 - t2;
		t3 << msize/2;
		t1 << msize;
		
		cout << t1 << " " << t3 << " " << t2 << endl;
		result = t1 + t3 + t2;
		while(fic_zero--) result.digit.pop_back();
	}

  return result;
}
BIGINT operator<<(BIGINT& left, int n) {
	left.digit.reserve(left.digit.size() + n);
	while(n--) left.digit.insert(left.digit.begin(), 0);
	return left;
}


bool BIGINT::operator>(const BIGINT& right) const {
	if(this->_negative && !right._negative) return true;
	if(this->digit.size() != right.digit.size()) return this->digit.size() > right.digit.size();
	for(int i = 0; i < this->digit.size(); i++)
		if(this->digit[i] != right.digit[i])
			return this->digit[i] > right.digit[i];
	return false;
}
bool BIGINT::operator<(const BIGINT& right) const {
	if(!this->_negative && right._negative) return true;
	if(this->digit.size() != right.digit.size()) return this->digit.size() < right.digit.size();
	for(int i = 0; i < this->digit.size(); i++)
		if(this->digit[i] != right.digit[i])
			return this->digit[i] < right.digit[i];
	return false;
}
bool BIGINT::operator==(const BIGINT& right) const {
	if(this->_negative != right._negative) return false;
	if(this->digit.size() != right.digit.size()) return false;
	for(int i = 0; i < this->digit.size(); i++)
		if(this->digit[i] != right.digit[i])
			return false;
	return true;
}
bool BIGINT::operator>=(const BIGINT& right) const {
	return ( (*this > right) || (*this == right) );
}
bool BIGINT::operator<=(const BIGINT& right) const {
	return ( (*this < right) || (*this == right) );
}
bool BIGINT::operator!=(const BIGINT& right) const {
	return !(*this == right);
}


int& BIGINT::operator[](unsigned index) {
	if(index < 0) exit(1);
	if(index >= digit.size()) {
		cout << "индекс больше разр€дов";
		exit(1);
	}
	return digit[index];
}

bool BIGINT::isnegative() {
	return _negative;
}

istream& operator>>(istream& is, BIGINT& right) {
	string value;
	getline(is, value);
	right = value;
	return is;
}
ostream& operator<<(ostream& os, BIGINT& right) {
	if(right._negative) os << "-";
	for(int i = right.digit.size(); i; i--)
		os << right.digit[i-1];
	return os;
}
void BIGINT::print() const{
	if(this->_negative) cout << "-";
	for(int i = this->digit.size(); i; i--)
		cout << this->digit[i-1];
}
