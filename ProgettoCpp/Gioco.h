#include <vector>
#include "Characters.h"


class Spelonca{
private:
vector<Character*> enemies;
char **room;
public:
Spelonca();
vector<Character*> checkEnemies();
void insertEnemy(Character* e);
void uccisione(Character* e);
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
int fight(Character* e);

virtual ~Gioco();
};


