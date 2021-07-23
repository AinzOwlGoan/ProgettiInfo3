#include <string>
using namespace std;

class Esploratore{
private:
	string name;
	int hp;
public:
	Esploratore(string n, int h);
	string checkNome();
	int checkVita();
	void hpLost(int h);
	int tiroDado();
	void virtual attacca(Esploratore *c);
	virtual ~Esploratore();
};


class Hero:public Esploratore{
public:
	Hero(string n);
	void virtual attacca(Esploratore *c);
	virtual ~Hero();
};

class Enemy: public Esploratore {
public:
	Enemy();
	void virtual attacca(Esploratore *c);
	virtual ~Enemy();
};
