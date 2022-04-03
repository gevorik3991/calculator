#include <iostream>

using namespace std;

int len(string str)
{
	int kol = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		kol++;
	}
	return kol;
}

int to_int(string str)
{
	int num = 0;
	int k = 1;
	for (int i = len(str) - 1; i >= 0; i--) {
		num += (str[i] - '0') * k;
		k *= 10;
	}
	return num;
}

bool is_positive(string str)
{
	if (str[0] == '-')
		return false;
	return true;
}

string slice_str(string str, int start, int end)
{
	string str2 = "";
	if (end > len(str))
		end = len(str) - 1;
	for (int i = start; i <= end; i++)
		str2 += str[i];
	return str2;
}

string reverse_str(string str) {
	string newstr = "";
	for (int i = len(str) - 1; i >= 0; i--) {
		newstr += str[i];
	}
	return newstr;
}

string remove_space(string str) {
	string newstr = "";
	for (int i = 0; i < len(str); i++){
		if (str[i] != ' ')
			newstr += str[i];
	}
	return newstr;
}

string noMinus(string num) {
	return slice_str(num, 1, len(num));
}

char znak(string str)
{
	for (int i = 1; i < len(str); i++) {
		if (str[i] == '+' || str[i] == '-' || str[i] == '*')
			return str[i];
	}
}

string no_zero(string str)
{
	int ind = 0;
	if (str[ind] == '-')
		ind++;
	while (str[ind] == '0' && ind < len(str))
		ind++;
	if (ind == len(str))
		return "0";
	return slice_str(str, ind, len(str));
}

string cout_zero(string str, string str2)
{
	string no_zeros = "";
	int n1 = to_int(str);
	int n2 = to_int(str2);
	while (n1 % 10 == 0){
		n1 /= 10;
		no_zeros += "0";
	}
	while (n2 % 10 == 0) {
		n2 /= 10;
		no_zeros += "0";
	}
	return no_zeros;
}


string cCompare(string num1, string num2) {
	int len1 = len(num1);
	int len2 = len(num2);
	if (len1 > len2)
		return num1;
	else if (len2 > len1)
		return num2;
	for (int i = 0; i < len1; i++) {
		if (num1[i] > num2[i])
			return num1;
		else if (num2[i] > num1[i])
			return num2;
	}
	return num1;
}

string substractCalculation(string num1, string num2) {
	string newstr = "";
	bool desyatok = false;
	int Len = len(num1);
	for (int i = Len - 1; i >= 0; i--) {
		if (num1[i] - desyatok < num2[i]) {
			newstr += num1[i] + 10 - num2[i] + '0' - desyatok;
			desyatok = true;
		}
		else {
			newstr += num1[i] - num2[i] + '0' - desyatok;
			desyatok = false;
		}
	}
	return newstr;
}

string csubstract(string num1, string num2) {
	string newstr = "";
	string buffer = "";
	if (num2 == cCompare(num1, num2)) {
		buffer = num1;
		num1 = num2;
		num2 = buffer;
	}
	while (len(num2) < len(num1))
		num2 = "0" + num2;
	newstr = substractCalculation(num1, num2);
	return no_zero(reverse_str(newstr));
}

string csum(string num1, string num2) {
	string newstr = "";
	bool desyatok = false;
	while (len(num1) < len(num2))
		num1 = "0" + num1;
	while (len(num2) < len(num1))
		num2 = "0" + num2;
	int Len = len(num1);
	for (long long i = Len - 1; i >= 0 || desyatok; i--) {
		if (i >= 0) {
			newstr += (num1[i] - '0' + num2[i] - '0' + desyatok) % 10 + '0';
			if (num1[i] - '0' + num2[i] - '0' + desyatok > 9)
				desyatok = true;
			else
				desyatok = false;
		}
		else {
			newstr += "1";
			desyatok = false;
		}
	}
	return reverse_str(newstr);
}

string calculation_operator_plus(bool firstPositive, bool secondPositive, string num1, string num2) {
	if (firstPositive && secondPositive)
		return csum(num1, num2);
	if (!firstPositive && !secondPositive && csum(num1, num2) != "0")
		return "-" + csum(num1, num2);
	if (((!firstPositive && num1 == cCompare(num1, num2)) || (!secondPositive && num2 == cCompare(num1, num2))) && num1 != num2)
		return (csubstract(num1, num2) != "0") ? "-" + csubstract(num1, num2) : csubstract(num1, num2);
	else
		return csubstract(num1, num2);
	return "Error";
}














void print_calc()
{
	cout << "Calculator" << endl;
}







int main()
{
	print_calc();
	string  str;
	cin >> str;
	cout << calculation_operator_plus(true, true, "00001", "001");

	return 0;
}