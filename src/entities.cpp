#include "entities.hpp"

// Methods of class Entity

Entity::Entity() {};

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

// Methods of class Player

Player::Player() {};

Player::Player(
    int y, int x, int direction, bool is_moving,
    int life, int shield, bool has_weapon
):Entity(y, x) {
    this->direction = direction;
    this->is_moving = is_moving; 
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

void Player::set_is_moving(bool is_moving) {
    this->is_moving = is_moving;
}

bool Player::get_is_moving() {
    return this->is_moving;
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

// Methods of class Enemy

Enemy::Enemy() {};

Enemy::Enemy(int y, int x, int level):Entity(y, x) {
    this->level = level; 
    this->life = level; 
    this->damage = level;
};
        
int Enemy::get_life() {
    return this->life; 
}

int Enemy::get_damage() {
    return this->damage;
}

void Enemy::decrease_level() {
    this->level -= 1; 
    this->life -= 1; 
    this->damage -= 1;
}

/* Struct enemy methods */

void add_enemy(enemy_node *head, Enemy new_enemy) {
    enemy_node *new_head = new enemy_node; 
    new_head->current_enemy = new_enemy;
    new_head->next = head; 
    head = new_head;
}