#include "Gioco.h"
#include <iostream>
#include <string>
using namespace std;

int main(){

	cout<< "Nome dell'eroe:";
	// prende nome
	string nome;
	cin>>nome;
	// definizione gioco
	Gioco partita(nome);

	// Inserire parte con guida


	// parte con guida

	Enemy e0;
	Enemy e1;
	Enemy e2;
	// inserimento dei nemici
	partita.insertEnemy(&e0);
	partita.insertEnemy(&e1);
	partita.insertEnemy(&e2);

	// risultato

		int result = 0;
		partita.show();
		while(result == 0){
			string choice = partita.showMenu();
			result=partita.heroMove(choice);
		}

	return 0;
}
