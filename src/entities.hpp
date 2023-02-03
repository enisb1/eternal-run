#ifndef ENTITIES_HPP
#define ENTITIES_HPP

/* Vars */

const int DOWN = 1;
const int UP = 2;
const int RIGHT = 3;
const int LEFT = 4;

/* Classes */

class Entity {
    protected:
        int y;
        int x;

    public:
        Entity();
        Entity(int y, int x);

        // getter and setter
        void set_y(int y);
        int get_y();

        void set_x(int x);
        int get_x();
};

class Player: public Entity {
    protected:
        int direction;
        bool is_moving;
        int life;
        int shield;
        bool has_weapon;
        int bullet_speed;

    public:
        Player();
        Player(
            int y, int x, int direction, bool is_moving,
            int life, int shield, bool has_weapon
        );

        // getter and setter
        void set_direction(int direction);
        int get_direction();

        void set_is_moving(bool is_moving);
        bool get_is_moving();

        void set_life(int life);
        int get_life();

        void set_shield(int shield);
        int get_shield();

        void set_has_weapon(bool has_weapon);
        int get_has_weapon();

        void set_bullet_speed(int bullet_speed);
        int get_bullet_speed(int bullet_speed);

        // increase and decrease the life by one
        void increase_life();
        void decrease_life();

        // create a new Bullet and shoot
        void shoot();
};

class Enemy: public Entity {
    protected:
        int level;
        int life;
        int damage;

    public:
        Enemy();
        Enemy(int y, int x, int level);
        
        // getter and setter
        int get_life();
        int get_damage();

        // decrease the level by one
        void decrease_level();
};

class Bullet: public Entity {
    protected:
        int direction_y;
        int direction_x;
        int speed;

    public:
        Bullet(
            int y, int x, 
            int direction_y, int direction_x, int speed);
        
        // move the entity inside the map
        // following the bullet movement
        void move();
};

/* Structs */

struct enemy_node {
    Enemy current_enemy;
    enemy_node *next;
};

/* Methods */

void add_enemy(enemy_node *head, Enemy new_enemy);

#endif