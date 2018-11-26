#include <iostream>
#include <stack>

using namespace std;

#define MAX 1000

void decimalToBinary(int n, char s[]){
	stack<char> myStack = stack<char>();
	while (n > 0)
	{
		myStack.push(n % 2);
		n /= 2;
	}

	int i = 0;
	while (!myStack.empty()){
		char ch = myStack.top() + '0';
		myStack.pop();

		s[i] = ch;
		++i;
	}
	s[i] = '\0';
}

void Cau1(){
	int n = 10;
	char s[MAX];

	decimalToBinary(n, s);
	cout << s << endl;
}
//////////////////////////////////////////////////////////////////////
struct BigInteger{
	bool negativeSign; // true: has negative 
	char digits[MAX];
};

int countDigits(const char d[])
{
	int i = 0;
	while (d[i] != '\0'){ ++i; }

	return i;
}

int compareDigits(const char dA[], const char dB[])
{
	int countD1 = countDigits(dA);
	int countD2 = countDigits(dB);

	if (countD1 > countD2){
		return 1;
	}
	if (countD1 < countD2){
		return -1;
	}
	// countD1 == countD2
	for (int i = countD1; i > 0; i--)
	{
		if (dA[i] > dB[i]){
			return 1;
		}
		if (dA[i] < dB[i]){
			return -1;
		}
	}

	return 0;
}

int compare(const BigInteger &n1, const BigInteger &n2){
	// n1 < n2
	if (n1.negativeSign && !n2.negativeSign)
	{
		return -1;
	}
	// n1 > n2
	if (!n1.negativeSign && n2.negativeSign)
	{
		return 1;
	}
	// n1, n2 < 0
	if (n1.negativeSign && n2.negativeSign)
	{
		return -compareDigits(n1.digits, n2.digits);
	}
	// n1, n2 > 0
	return compareDigits(n1.digits, n2.digits);
}
// n1 > 0 && n2 > 0
BigInteger add(BigInteger A, BigInteger B)
{
	BigInteger result;
	for (int i = 0; i < MAX; i++)
	{
		result.digits[i] = '0';
	}
	int countN1 = countDigits(A.digits);
	int countN2 = countDigits(B.digits);
	
	int maxDigit = (countN1 > countN2) ? countN1 : countN2;
	for (int i = 0; i < maxDigit; i++)
	{
		int val1 = A.digits[i] - '0';
		int val2 = B.digits[i] - '0';

		int val = val1 + val2;
		int digitResult = result.digits[i] - '0';
		result.digits[i] = (val % 10) + '0';

		int remember = val / 10;
		int idx = i + 1;
		while (remember > 0)
		{
			digitResult = result.digits[idx] - '0';
			val = remember + digitResult;

			result.digits[idx] = (val % 10) + '0';
			++idx;

			remember = val / 10;
		}
	}

	result.digits[maxDigit] = '\0';
	return result;
}

BigInteger mul(const BigInteger &n1, const BigInteger &n2)
{
	BigInteger result;
	for (int k = 0; k < MAX; k++)
	{
		result.digits[k] = '0';
	}

	if ((n1.negativeSign && n2.negativeSign) || (!n1.negativeSign && !n2.negativeSign))
	{
		result.negativeSign = false;
	}
	else
	{
		result.negativeSign = true;
	}

	int countN1 = countDigits(n1.digits);
	int countN2 = countDigits(n2.digits);

	for (int i = 0; i < countN1; i++)
	{
		for (int j = 0; j < countN2; j++)
		{
			int val1 = n1.digits[i] - '0';
			int val2 = n2.digits[j] - '0';
			int val = val1 * val2;

			int idx = i + j;

			int resultDigit = result.digits[idx] - '0';
			val = val + resultDigit;

			result.digits[idx] = val % 10 + '0';
			idx++;

			int remem = val / 10;
			while (remem > 0)
			{
				resultDigit = result.digits[idx] - '0';
				val = remem + resultDigit;

				result.digits[idx] = (val % 10) + '0';

				remem = val / 10;

			}
		}
	}

	result.digits[countN1 + countN2 - 1] = '\0';
	return result;
}

BigInteger convertNum2BI(int n)
{
	BigInteger b;
	if (n < 0){
		b.negativeSign = true;
	}
	else
	{
		b.negativeSign = false;
	}
	int i = 0;
	n = abs(n);
	while (n > 0)
	{
		b.digits[i] = n % 10 + '0';
		i++;
		n /= 10;
	}
	b.digits[i] = '\0';

	return b;
}

void PrintBigInteger(BigInteger b)
{
	if (b.negativeSign){
		cout << "-";
	}
	int i = 0;
	int count = countDigits(b.digits);
	for (int i = count-1; i >= 0; i--)
	{
		cout << b.digits[i];
	}
}

void Cau2()
{
	int numA = 9999;
	int numB = 88;

	BigInteger b1 = convertNum2BI(numA);
	BigInteger b2 = convertNum2BI(numB);

	//BigInteger b = mul(b1, b2);

	PrintBigInteger(b1);
	cout << endl;
	PrintBigInteger(b2);
	cout << endl;

	BigInteger m = mul(b2, b1);
	PrintBigInteger(m);


}

//void main()
//{
//	Cau2();
//
//
//
//
//}
