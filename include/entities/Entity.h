#pragma once

#include <string>
#include <memory>

namespace RPG {

enum class EntityType {
    PLAYER,
    ENEMY_WEAK,
    ENEMY_NORMAL,
    ENEMY_STRONG,
    ENEMY_BOSS
};

class Entity {
public:
    Entity(const std::string& name, int hp, int attack, int defense, int level);
    virtual ~Entity() = default;

    // Pure virtual methods (abstract interface)
    virtual void takeDamage(int damage) = 0;
    virtual int dealDamage() const = 0;
    virtual bool isAlive() const = 0;
    virtual EntityType getType() const = 0;

    // Virtual methods with default implementation
    virtual void displayStats() const;
    virtual void heal(int amount);

    // Getters
    std::string getName() const { return name; }
    int getHp() const { return hp; }
    int getMaxHp() const { return maxHp; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    int getLevel() const { return level; }

    // Setters
    void setHp(int value) { hp = value; }
    void setMaxHp(int value) { maxHp = value; }
    void setAttack(int value) { attack = value; }
    void setDefense(int value) { defense = value; }
    void setLevel(int value) { level = value; }

protected:
    std::string name;
    int hp;
    int maxHp;
    int attack;
    int defense;
    int level;
};

using EntityPtr = std::shared_ptr<Entity>;

} // namespace RPG
