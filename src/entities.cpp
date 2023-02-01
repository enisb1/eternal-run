#include "entities.hpp"

// Methods of class Entity

Entity::Entity(int x, int y) {
    this->x = x; 
    this->y = y; 
}

int Entity::get_x() {
    return this->x; 
}

int Entity::get_y() {
    return this->y; 
}

void Entity::move(int dx, int dy) {
    this->x += dx; 
    this->y += dy;
}

// Methods of class Player

Player::Player(int x, int y, int life, int shield, int has_weapon):Entity(x, y) {
            this->life = life; 
            this->shield = shield; 
            this->has_weapon = has_weapon;
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