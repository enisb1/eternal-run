#include "entities.hpp"

// Methods of class Entity

Entity::Entity(int y, int x) {
    this->y = y;
    this->x = x;
}

void Entity::set_y(int y) {
    this->y = y;
}

int Entity::get_y() {
    return this->y; 
}

void Entity::set_x(int x) {
    this->x = x;
}

int Entity::get_x() {
    return this->x; 
}

void Entity::move(int dy, int dx) {
    this->y += dy;
    this->x += dx;
}

// Methods of class Player

Player::Player(
    int y, int x, int direction,
    int life, int shield, bool has_weapon
):Entity(y, x) {
    this->direction = direction;
    this->life = life;
    this->shield = shield; 
    this->has_weapon = has_weapon;
}

void Player::set_direction(int direction) {
    this->direction = direction;
}

int Player::get_direction() {
    return this->direction;
}

void Player::set_life(int life) {
    this->life = life;
}

int Player::get_life() {
    return this->life;
}

void Player::set_shield(int shield) {
    this->shield = shield; 
}

int Player::get_shield() {
    return this->shield; 
}

void Player::set_has_weapon(bool has_weapon) {
    this->has_weapon = has_weapon;
}

int Player::get_has_weapon() {
    return this->has_weapon;
}

void Player::set_bullet_speed(int bullet_speed) {
    this->bullet_speed = bullet_speed; 
}

int Player::get_bullet_speed(int bullet_speed) {
    return this->bullet_speed;
}

void Player::increase_life() {
    this->life += 1;
}

void Player::decrease_life() {
    this->life -= 1; 
}

void Player::shoot() {

}