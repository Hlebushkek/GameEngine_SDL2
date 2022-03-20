#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(const char*  name)
{
    this->name = name;
    this->hp = 10;
    this->attackDmg = 1;
}
Enemy::~Enemy()
{
    std::cout << name << " Destructor" << std::endl;
}
void Enemy::Attack(Player* player)
{
    player->TakeDamage(this->attackDmg);
}
void Enemy::TakeDamage(int dmg)
{
    this->hp -= dmg;
    std::cout << name << " take " << dmg << " damage" << std::endl;
    std::cout << name << " have " << this->hp << " left" << std::endl;

    if (this->hp <= 0)
    {
        std::cout << this->name << " dead" << std::endl;
    }
}