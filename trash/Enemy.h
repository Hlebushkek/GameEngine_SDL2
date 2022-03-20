#include <iostream>
#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{
private:
    int hp;
    int attackDmg;
    const char* name;
public:
    Enemy(const char* name);
    ~Enemy();
    void Attack(class Player* player);
    void TakeDamage(int dmg);
};
#endif