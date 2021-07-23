#include "Esploratore.h"
#include <iostream>


Esploratore::Esploratore(string n, int h):name(n), hp(h){
}

string Esploratore::checkNome(){
	return name;
}

int Esploratore::checkVita(){
	return hp;
}
// metodo da implementare successivamente per vedere livello fortuna
/*int Esploratore::checkLuck(){

}*/
void Esploratore::hpLost(int h){
	hp-=1;
}

void Esploratore::attacca(Esploratore *c){
}
int Esploratore::tiroDado(){

	return (rand()%6)+1;
}
Esploratore::~Esploratore(){}

// DEFINIZIONE EROE
// composto semplicemente da nome e dalla vita
Hero::Hero(string n):Esploratore(n, 10){}


void Hero::attacca(Esploratore* c){
	// La dinamica di attacco riguarda l'utilizzo dei dadi, 3 vite per il nemico

	 c->hpLost(1);
	 cout<<c->checkNome()<<" ha "<<c->checkVita()<<" vite "<<endl;

}
Hero::~Hero(){}

// Dichiarazione del nemico
Enemy::Enemy():Esploratore("Enemy",3){}

void Enemy::attacca(Esploratore* c){

	c->hpLost(1);
	cout<<c->checkNome()<<" ha "<<c->checkVita()<<" vite "<<endl;

}
// Definizione metodo
// Distruttore virtuale
Enemy::~Enemy(){}
