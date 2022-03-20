#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
    int hp;
    int attackDmg;
public:
    Player();
    void Attack(class Enemy* enemy);
    void TakeDamage(int dmg);
};

#endif