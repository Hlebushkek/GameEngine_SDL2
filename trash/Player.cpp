#include "Player.h"
#include "Enemy.h"

Player::Player()
{
    this->hp = 10;
    this->attackDmg = 2;
}
void Player::Attack(Enemy* enemy)
{
    enemy->TakeDamage(attackDmg);
}
void Player::TakeDamage(int dmg)
{
    this->hp -= dmg;
    std::cout << "Player take " << dmg << " damage" << std::endl;
    std::cout << "Player have " << this->hp << " left" << std::endl;

    if (this->hp <= 0) std::cout << "You dead" << std::endl;
}