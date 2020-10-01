#pragma once

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <cstring>
#include "stdlib.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::min;
using std::max;
using std::istream;
using std::ostream;
using std::pair;

class BIGINT {
	private:
		vector<int> digit;
		bool _negative = false;
		bool _digree_of_ten = false;
		
		friend BIGINT sum(const BIGINT& left, const BIGINT& right);
		friend BIGINT minus(const BIGINT& left, const BIGINT& right);
		
		friend pair<int,int> normalization(const BIGINT& first, const BIGINT& second);
		
		
	public:
		BIGINT();
		BIGINT(unsigned size);
		BIGINT(string value);
		BIGINT(char* value);
		BIGINT(const BIGINT& copy);
		~BIGINT();
		
		BIGINT operator+(const BIGINT& right) const;
		BIGINT operator*(const BIGINT& right) const;
		BIGINT operator-(const BIGINT& right) const;
		
		friend BIGINT operator<<(BIGINT& left, int n);
		
		bool operator>(const BIGINT& right) const;
		bool operator<(const BIGINT& right) const;
		bool operator==(const BIGINT& right) const;
		bool operator>=(const BIGINT& right) const;
		bool operator<=(const BIGINT& right) const;
		bool operator!=(const BIGINT& right) const;
		
		int& operator[](unsigned index);
		
		bool isnegative();
		void print() const;
		
		friend istream& operator>>(istream& is, BIGINT& right);
		friend ostream& operator<<(ostream& os, BIGINT& right);
};
