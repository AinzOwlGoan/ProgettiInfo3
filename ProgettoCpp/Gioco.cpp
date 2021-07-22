#include "Gioco.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

Spelonca::Spelonca() {
	// Livello 10x5
	char temp[10][5] = { { '-', '-', 'E', 'O', 'E' },
			{ '-', 'O', 'O', '-', '-' }, { '-', '-', 'O', '-', '-' }, { '-',
					'O', 'O', '-', '-' }, { '-', '-', 'O', '-', '-' }, { '-',
					'O', 'E', '0', '-' }, { '-', '-', 'O', '-', '-' }, { '-',
					'-', 'O', 'O', '-' }, { '-', 'H', 'O', 'O', 'V' }, { '-',
					'-', '-', '-', '-' } };
	room = new char*[5];
	for (int i = 0; i < 10; i++) {
		room[i] = new char[10];
		for (int j = 0; j < 5; j++) {
			room[i][j] = temp[i][j];
		}
	}
}

vector<Character*> Spelonca::checkEnemies() {
	// ritorno tutti i nemici che sono stati inseriti nel Spelonca
	return enemies;
}

void Spelonca::insertEnemy(Character *e) {
	// inserimento nella lista del nemico
	enemies.push_back(e);
}

void Spelonca::uccisione(Character *e) {
	vector<Character*>::iterator i = find(enemies.begin(), enemies.end(), e);
	enemies.erase(i);
	cout << e->checkName() << " è stato ucciso!" << endl;
	cout << endl;
}

char** Spelonca::checkRoom() {
	return room;
}

void Spelonca::updateRoom(char **r) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			room[i][j] = r[i][j];
		}
	}
}

Spelonca::~Spelonca() {
	for (int i = 0; i < 10; i++) {
		delete[] room[i];
	}
	delete[] room;
}

Menu::Menu() {
	mode = 1;
}

string Menu::showMenu() {
	string choice;
	if (mode == 1) {
		cout << "Dove vuoi andare?" << endl;
		cout << endl;
		cout << "(Muoversi con w a s d)" << endl;
		cout << endl;
	} else {
		cout << "Modalità combattimento: " << endl;
		cout << "Che azione vuoi fare?" << endl;
		cout << endl;
		cout << "Lancio dadi (a)" << endl;
		cout << "Scappare (h)" << endl;
	}
	cin >> choice;
	return choice;
}

void Menu::changeMode() {
	if (mode == 1)
		mode = 2;
	else
		mode = 1;
}

Menu::~Menu() {
}

Gioco::Gioco(string n) :
		Spelonca(), Menu(), hero(Hero(n)) { // @suppress("Symbol is not resolved")
}

void Gioco::show() {
	char **r = checkRoom();
	for (int i = 0; i < 10; i++) { // righe
		for (int j = 0; j < 5; j++) { // colonne
			if (r[i][j] == 'H') {
				cout << r[i - 1][j - 1] << " " << r[i - 1][j] << " "
						<< r[i - 1][j + 1];
				cout << endl;
				cout << r[i][j - 1] << " " << r[i][j] << " " << r[i][j + 1]
						<< "     Legenda: 'H'-> eroe, '-'-> Muro, 'O'-> Percorso,  'E'-> Nemico";
				cout << endl;
				cout << r[i + 1][j - 1] << " " << r[i + 1][j] << " "
						<< r[i + 1][j + 1];
				cout << endl;
				return;
			}
		}
	}
}

int Gioco::heroMove(string m) {
	char **r = checkRoom(); // vado a controllare la stanza
	int i1 = 0, j1 = 0;

	// Non è possibile utilizzare il costrutto switch-case con le stringhe
	if (m == "w") {
		i1 = -1;
	}
	if (m == "a") {
		j1 = -1;
	}
	if (m == "s") {
		i1 = 1;
	}
	if (m == "d") {
		j1 = 1;
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 5; j++) {
			if (r[i][j] == 'H') {
				if (r[i + i1][j + j1] == '-') {
					cout << "Attenzione, presenza muro" << endl;
					show();
					return 0;
				} else {
					if (r[i + i1][j + j1] == 'V') {
						cout << "Hai vinto!" << endl;
						return 1;
					}
					if (r[i + i1][j + j1] == 'E') {
						vector<Character*> e = checkEnemies();
						int rnd = rand() % e.size();
						Character *nemico = e.at(rnd);
						cout << "Appare " << nemico->checkName();
						cout << endl;
						cout << "Vite:" << nemico->checkHp();
						cout << endl;
						changeMode();
						int result = fight(nemico);
						if (result == 1)
							return 1;
					}
					r[i][j] = 'O';
					r[i + i1][j + j1] = 'H';
					updateRoom(r);
					show();
					return 0;
				}
			}
		}
	}
	return 0;
}

// Lotta tra nemico ed eroe
int Gioco::fight(Character *e) {
	while (hero.checkHp() > 0 && e->checkHp() > 0) {
		// Premendo g lancio i dadi
		if (showMenu() == "a") { // da sostituire con g, lancio dadi

			// Lancio dadi da entrambi i membri
			int HeroDice = hero.tiroDado();
			int EnemyDice = e->tiroDado();

			cout << "Dado eroe: " << HeroDice << " Dado nemico: " << EnemyDice
					<< endl;
			if (HeroDice >= EnemyDice) {

				hero.attacca(e);

				if (e->checkHp() <= 0) {
					uccisione(e);
					changeMode();
					return 0;
				}
			} else if (HeroDice < EnemyDice) {

				e->attacca(&hero);
				if (hero.checkHp() <= 0) {
					cout << "Sei morto!" << endl;
					return 1;
				}

			}
		}
		if (showMenu() == "h") {

			// Tento di scappare dal nemico
			cout << "Tentata fuga: ";
			int coefficienteFuga = (rand() % 100) + 1;

			if (coefficienteFuga >= 80) {
				cout << "Fuga avvenuta con successo" << endl;
				changeMode();
				return 0;
			} else if (coefficienteFuga < 80) {

				cout << "Fuga fallita" << endl;
				cout << "L'eroe ha" << hero.checkHp() << "vite" << endl;
				e->attacca(&hero);
				if (hero.checkHp() <= 0) {
					cout << "Sei morto!" << endl;
					return 1;
				}
			}
		}
	}
	return 0;
}

Gioco::~Gioco() {
}
