#include <string>
using namespace std;

class Character{
private:
	string name;
	int hp;
public:
	Character(string n, int h);
	string checkName();
	int checkHp();
	void hpLost(int h);
	int tiroDado();
	void virtual attacca(Character *c);
	virtual ~Character();
};


class Hero:public Character{
public:
	Hero(string n);
	void virtual attacca(Character *c);
	virtual ~Hero();
};

class Enemy: public Character {
public:
	Enemy();
	void virtual attacca(Character *c);
	virtual ~Enemy();
};
