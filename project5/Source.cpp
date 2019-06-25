#include<iostream>
#include<conio.h>
#include<string>
#include<vector>

using namespace std;
struct morph
{
public:
	morph(double a, int c) : val(a), place(c) {};
	friend ostream& operator<<(ostream&, morph);
	friend class Culc;
private:
	double val;
	int place;
};
ostream& operator<<(ostream& os, morph a)
{
	os << a.place << ":" << a.val << endl;
	return os;
}
struct znak
{
public:
	znak(char a, int b, int c) :val(a), place(b), prior(c) {};
	friend ostream& operator<<(ostream& os, znak a);
	friend class Culc;
private:
	char val;
	int place;
	int prior;
};
ostream& operator<<(ostream& os, znak a)
{
	os << a.place << ":" << a.val <<":"<< a.prior <<  endl;
	return os;
}
struct Culc
{
public:
	Culc() = delete;
	Culc(string s) : prim(s), max_pr(1) 
	{
		if (prim == "")
			return;
		analize();
		podschet();
		out();
	}
	Culc(Culc &a) = delete;
	Culc operator=(Culc &a) = delete;
	void out()
	{
		cout <<"Ваш ответ:" << otvet << endl;
	}
	void _out()
	{
		for (morph &a : vec_m)
		{
			cout << a << endl;
		}
		for (znak &a : vec_zn)
		{
			cout << a << endl;
		}
	}
	
private:
	void analize()
	{
		int pr = 0;
		int place_m = 1;
		int place_zn = 1;
		for (int i(0); i != prim.length(); i++)
		{
			double val = 0;
			double dr = 0;
			double caf = 0.1;
			if (prim[i] >= 48 && prim[i] <= 57)
			{
				while (prim[i] >= 48 && prim[i] <= 57)
				{
					val *= 10;
					val += (prim[i] - 48);
					i++;					
				}
				if (prim[i] == '.')
				{
					i++;
					while (prim[i] >= 48 && prim[i] <= 57)
					{
						dr += (prim[i] - 48) * caf;
						caf *= 0.1;
						i++;
					}
				}
				
				i--;
				val += dr;
				vec_m.push_back(morph(val, place_m++));
			}else
			{
				switch (prim[i])
				{
				case '+':
				case '-':
					vec_zn.push_back(znak(prim[i], place_zn++, 0 + pr * 3));
					break;
				case '/':
				case '*':
					vec_zn.push_back(znak(prim[i], place_zn++, 1 + pr * 3));
					break;
				case '^':
					vec_zn.push_back(znak(prim[i], place_zn++, 2 + pr * 3));
					break;
				case '(': 
					pr++;	
					if (pr * 3 + 2 > max_pr)
						max_pr = pr * 3 + 2;
					break;
				case ')':
					pr--;
					break;
				}
			}
		}
	}
	void podschet()
	{
		for (; max_pr != -1; max_pr--)
		{
			for (int i(0); i < vec_zn.size(); i++)
			{
				if (vec_zn[i].prior == max_pr)
				{
					vec_m[i].val = rez(vec_m[i], vec_m[i + 1], vec_zn[i]);
					vec_m.erase(vec_m.begin() + i + 1);
					vec_zn.erase(vec_zn.begin() + i);
					for (int j(i + 1); j < vec_m.size(); j++)
					{
						vec_m[j].place--;
					}
					for (int j(i); j < vec_zn.size(); j++)
					{
						vec_zn[j].place--;
					}
					i--;
				}
			}
		}
		otvet = vec_m[0].val;
	}
	double rez(morph a, morph b, znak c)
	{
		switch (c.val)
		{
		case '*':
			return a.val * b.val;
		case '/':
			return a.val / b.val;
		case '+':
			return a.val + b.val;
		case '-':
			return a.val - b.val;
		case '^':
			return pow(a.val, b.val);
		}
	}
	vector<morph> vec_m;
	vector<znak> vec_zn;
	string prim;
	double otvet;
	int max_pr;
};
int main()
{
	do
	{
		setlocale(LC_ALL, "Russian");
		string str;
		cout << "Введите пример:";
		getline(cin, str);
		Culc CL(str);
	}
	while (cin.good());

	return 0;
}