#include <vector>
#include "Esploratore.h"


class Spelonca{
private:
vector<Esploratore*> enemies;
char **room;
public:
Spelonca();
vector<Esploratore*> checkEnemies();
void insertEnemy(Esploratore* e);
void uccisione(Esploratore* e);
char** checkRoom();
void updateRoom(char** r);
virtual ~Spelonca();
};


class Menu{
private:
int mode;
public:
Menu();
string showMenu();
void changeMode();
virtual ~Menu();
};


class Gioco: public Spelonca, public Menu{
private:
Hero hero;
public:
Gioco(string n);
void show();
int heroMove(string m);
int fight(Esploratore* e);

virtual ~Gioco();
};


