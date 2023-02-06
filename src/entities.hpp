#ifndef ENTITIES_HPP
#define ENTITIES_HPP

/* Vars */

const int DOWN = 0;
const int RIGHT = 1;
const int UP = 2;
const int LEFT = 3;

/* Classes */

class Entity {
    protected:
        int y;
        int x;
        int direction;

    public:
        Entity();
        Entity(int y, int x, int direction);

        // getter and setter
        void set_y(int y);
        int get_y();

        void set_x(int x);
        int get_x();

        void set_direction(int direction);
        int get_direction();
};

class Player: public Entity {
    protected:
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
        void set_is_moving(bool is_moving);
        bool get_is_moving();

        void set_life(int life);
        int get_life();

        void set_shield(int shield);
        int get_shield();

        void set_has_weapon(bool has_weapon);
        int get_has_weapon();

        void set_bullet_speed(int bullet_speed);
        int get_bullet_speed();

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
        int blocks_traveled;

    public:
        Enemy();
        Enemy(int y, int x, int direction, int level);
        
        // getter and setter
        int get_life();
        int get_damage();
        int get_level();
        int get_blocks_traveled();

        // decrease the level by one
        void decrease_level();

        // increase the blocks_traveled by one
        void increment_blocks_traveled();

        // set blocks_traveled to 0
        void reset_blocks_traveled();
};

class Bullet: public Entity {
    protected:
        int speed;

    public:
        Bullet();
        Bullet(int y, int x, int direction, int speed);

        // getter and setter
        int get_speed();
        void set_speed(int speed);

};

/* Structs */

struct enemy_node {
    Enemy current_enemy;
    enemy_node *next;
};

struct bullet_node {
    Bullet current_bullet;
    bullet_node *next;
};

/* Struct enemy methods */

// add a new enemy to enemy list
void add_enemy(enemy_node* &head, Enemy new_enemy);

// get a random position for the enemy
void get_random_enemy_position(map *map, Player player, int &y, int &x);

// get a random direction for the enemy
int get_random_enemy_direction(map *map, int y, int x);

// create a new enemy list based on the level
void create_enemy_list(map *map, Player player, enemy_node* &head, int level);

/* Struct bullet methods */

// add a bullet to the bullet list
void add_bullet(bullet_node* &head, Bullet new_bullet);

#endif