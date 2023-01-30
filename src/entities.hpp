#ifndef ENTITIES_HPP
#define ENTITIES_HPP

class Entity {
    protected:
        int x;
        int y;
        char symbol;

    public:
        Entity(int x, int y, char symbol);

        // getter and setter
        int get_x();
        int get_y();
        char get_symbol();
        
        // move the entity inside the map
        void move(int dx, int dy);
};

class Player: public Entity {
    protected:
        int life;
        int shield;
        bool has_weapon;
        int bullet_speed;

    public:
        Player(
            int x, int y, char symbol, int life, 
            int shield, int has_weapon
        ):Entity(x, y, symbol);

        // getter and setter
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
        Player(int x, int y, char symbol, int level)
            :Entity(x, y, symbol);
        
        // getter and setter
        int get_life();
        int get_damage();

        // decrease the level by one
        void decrease_level();
};

class Bullet: public Entity {
    protected:
        int direction_x;
        int direction_y;
        int speed;

    public:
        Player(
            int x, int y, char symbol, 
            int direction_x, int direction_y, int speed
        ):Entity(x, y, symbol);
        
        // move the entity inside the map
        // following the bullet movement
        void move();
};

#endif