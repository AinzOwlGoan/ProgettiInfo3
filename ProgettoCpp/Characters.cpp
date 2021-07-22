#include "Characters.h"
#include <iostream>


Character::Character(string n, int h):name(n), hp(h){
}

string Character::checkName(){
	return name;
}

int Character::checkHp(){
	return hp;
}
/*int Character::checkLuck(){

}*/
void Character::hpLost(int h){
	hp-=1;
}

void Character::attacca(Character *c){
}
int Character::tiroDado(){
	return (rand()%6)+1;
}
Character::~Character(){}

// DEFINIZIONE EROE
// composto semplicemente da nome e dalla vita
Hero::Hero(string n):Character(n, 10){}


void Hero::attacca(Character* c){
	// La dinamica di attacco riguarda l'utilizzo dei dadi, 3 vite per il nemico

	 c->hpLost(1);
	 cout<<c->checkName()<<" ha "<<c->checkHp()<<" vite "<<endl;

}
Hero::~Hero(){}

// Dichiarazione del nemico
Enemy::Enemy():Character("Enemy",3){}

void Enemy::attacca(Character* c){

	c->hpLost(1);
	cout<<c->checkName()<<" ha "<<c->checkHp()<<" vite "<<endl;

}
// Definizione metodo
// Distruttore virtuale
Enemy::~Enemy(){}
