#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <sstream>
#undef max;

template <typename T>
std::string toString(T val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

using namespace std;

class Polynom {
private:
	vector<double> koef; //������ �������������
	int n; //�������

public:

	//����������� �� ���������
	Polynom() :n(1) {
		koef = vector<double>(n, 0);
	}

	//����������� ��������
	Polynom(int _n) {
		if (_n <= 0) {
			n = 1;
		}
		else {
			n = _n;
		}
		koef = vector<double>(n, 0);
	}

	//��� ����� �������������
	void Input() {
		for (int i = 0; i < n; i++) {
			cout << "x^" << i << " -> ";
			cin >> koef[i];
		}
		cout << endl;
	}

	//�������� �����������
	Polynom plus(const Polynom& a) {
		if (n >= a.n) {
			Polynom z(n);
			for (int i = 0; i < a.n; i++)
				z.koef[i] = koef[i] + a.koef[i];
			for (int i = a.n; i < n; i++)
				z.koef[i] = koef[i];
			return z;
		}
		else
		{
			Polynom z(a.n);
			for (int i = 0; i < n; i++)
				z.koef[i] = a.koef[i] + koef[i];
			for (int i = n; i < a.n; i++)
				z.koef[i] = a.koef[i];
			return z;
		}
	}

	//��������� �����������
	Polynom minus(const Polynom& a) {
		if (n >= a.n) {
			Polynom z(n);
			for (int i = 0; i < a.n; i++)
				z.koef[i] = koef[i] - a.koef[i];
			for (int i = a.n; i < n; i++)
				z.koef[i] = koef[i];
			return z;
		}
		else
		{
			Polynom z(a.n);
			for (int i = 0; i < n; i++)
				z.koef[i] = a.koef[i] - koef[i];
			for (int i = n; i < a.n; i++)
				z.koef[i] = a.koef[i];
			return z;
		}
	}

	//��������� �����������
	Polynom mult(const Polynom& a) {
		Polynom z(n + a.n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < a.n; j++)
				z.koef[i + j] += koef[i] * a.koef[j];
		auto it = z.koef.begin();
		advance(it, z.n - 1);
		while (*it <= 0.000001) {
			z.koef.erase(it); 
			z.n--; 
			it = z.koef.begin();
			advance(it, n - 1);
		}
		return z;
	}

	
	void Print() {
		string res = "";
		for (int i = n - 1; i > 0; i--) {
			if (koef[i] >= 0) {
				res += "+";
			}
			res += toString(koef[i]);
			res += "x^";
			res += toString(i);
		}
		if (koef[0] >= 0) {
			res += '+';
		}
		res += toString(koef[0]);
		cout << res << endl;
	}

	
	double f(double x) {
		double res = 0;
		for (int i = 0; i < n; i++) {
			res += koef[i] * pow(x, i);
		}
		return res;
	}
};


void Menu() {
	cout << "1 - ������ ����������" << endl;
	cout << "2 - ������� ����������" << endl;
	cout << "3 - �������" << endl;
	cout << "4 - �������" << endl;
	cout << "5 - �����������" << endl;
	cout << "6 - ��������� ��������" << endl;
	cout << "7 - ��������� ������" << endl;
	cout << "����_> ";
}

//������� ������� ����������
int main() {

	setlocale(LC_ALL, "RUS");
	int ch = 0;
	Polynom a, b; 


	do {

		Menu();
		cin >> ch;
		cout << endl;

		switch (ch) {
		case 1: {

			int n1, n2;
			cout << "������� ������� �������� a -> ";
			cin >> n1;
			cout << "������� ������� �������� b -> ";
			cin >> n2;

			Polynom _a(n1), _b(n2);
			cout << "������� ������������ �������� a:" << endl;
			_a.Input();

			cout << "������� ������������ �������� b:" << endl;
			_b.Input();

			cout << "��� ������ ���� ������� �������!" << endl << endl;
			a = _a;
			b = _b;
			break;
		}
		case 2: {
			cout << "������� a:" << endl;
			a.Print();
			cout << endl << "������� b:" << endl;
			b.Print();
			cout << endl;
			break;
		}
		case 3: {
			cout << "���������� �������� a = a + b" << endl;
			a = a.plus(b);
			cout << "��������� ��������:" << endl;
			a.Print();
			cout << endl;
			break;
		}
		case 4: {
			cout << "�������� �������� a = a - b" << endl;
			a = a.minus(b);
			cout << "��������� ���������:" << endl;
			a.Print();
			cout << endl;
			break;
		}
		case 5: {
			cout << "�������� �������� a = a * b" << endl;
			a = a.mult(b);
			cout << "��������� ������������:" << endl;
			a.Print();
			cout << endl;
			break;
		}
		case 6: {
			cout << "������� �������� ���������� x -> ";
			double x = 0;
			cin >> x;
			cout << endl << "��������� ���������� a.f(x) -> " << a.f(x) << endl << endl;
			cout << "��������� ���������� b.f(x) -> " << b.f(x) << endl << endl;
			break;
		}
		}

		if (cin.fail()) { 
			cout << "���� ��� ���������� � �������!" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			ch = 100;
			cout << endl;
		}

	} while (ch != 7);

	cout << "end." << endl;
	cout << endl;
	system("pause");
	return 0;
}
