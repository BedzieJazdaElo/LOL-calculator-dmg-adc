#pragma once
#include <iostream>
#include <fstream>
#include <string>

using units = double;
#define CONVERT std::stod

// equation for calculating damage after armor and magic resist
units DMG_after_resist(units dmg, units resist) // https://leagueoflegends.fandom.com/wiki/Armor , the same for magic resist
{
    if (resist >= 0)
    {
        return dmg * (100 / (100 + resist));
    }
    else
    {
        return 2 - (100 / (100 - resist));
    }
}

class Champion_class
{
    std::string name;

    units health, healt_regeneration, // per 5 sec
        armor, magic_resist, movement_speed, mana, mana_regeneration, attack_damage, crit_damage=1.75, attack_range, base_AS, attack_windup=0, AS_ratio = 1;

    units healthPerLevel, healt_regenerationPerLevel, armorPerLevel, magic_resistPerLevel, manaPerLevel, mana_regenerationPerLevel, attack_damagePerLevel, AS_PerLevel;

public:
    Champion_class(units health, units healt_regeneration, units armor, units magic_resist, units movement_speed, units mana, units mana_regeneration, units attack_damage, units crit_damage, units attack_range, units base_AS, units attack_windup, units AS_ratio, units healthPerLevel, units healt_regenerationPerLevel, units armorPerLevel, units magic_resistPerLevel, units manaPerLevel, units mana_regenerationPerLevel, units attack_damagePerLevel, units AS_PerLevel)
    {
        this->health = health;
        this->healt_regeneration = healt_regeneration;
        this->armor = armor;
        this->magic_resist = magic_resist;
        this->movement_speed = movement_speed;
        this->mana = mana;
        this->mana_regeneration = mana_regeneration;
        this->attack_damage = attack_damage;
        this->crit_damage = crit_damage;
        this->attack_range = attack_range;
        this->base_AS = base_AS;
        this->attack_windup = attack_windup;
        this->AS_ratio = AS_ratio;
        this->healthPerLevel = healthPerLevel;
        this->healt_regenerationPerLevel = healt_regenerationPerLevel;
        this->armorPerLevel = armorPerLevel;
        this->magic_resistPerLevel = magic_resistPerLevel;
        this->manaPerLevel = manaPerLevel;
        this->mana_regenerationPerLevel = mana_regenerationPerLevel;
        this->attack_damagePerLevel = attack_damagePerLevel;
        this->AS_PerLevel = AS_PerLevel;
    }

    Champion_class(std::string name)
    {
        std::ifstream file("dane.csv");// https://leagueoflegends.fandom.com/wiki/List_of_champions/Base_statistics
        std::string line;
        if (file.is_open())
        {

            while (std::getline(file, line))
            {
                if (line.find(name) != std::string::npos)
                {
                    size_t i{};
                    std::string temp;
                    do
                    {
                        temp = line.substr(0, line.find(";"));
                        switch (i)
                        {
                        case 0:
                            this->name = temp;
                            break;
                            break;

                        case 1:
                            this->health = CONVERT(temp);
                            break;

                        case 2:
                            this->healthPerLevel = CONVERT(temp);
                            break;

                        case 3:
                            this->healt_regeneration = CONVERT(temp);
                            break;

                        case 4:
                            this->healt_regenerationPerLevel = CONVERT(temp);
                            break;

                        case 5:
                            this->mana = CONVERT(temp);
                            break;

                        case 6:
                            this->manaPerLevel = CONVERT(temp);
                            break;

                        case 7:
                            this->mana_regeneration = CONVERT(temp);
                            break;

                        case 8:
                            this->mana_regenerationPerLevel = CONVERT(temp);
                            break;

                        case 9:
                            this->attack_damage = CONVERT(temp);
                            break;

                        case 10:
                            this->attack_damagePerLevel = CONVERT(temp);
                            break;

                        case 11:
                            this->base_AS = CONVERT(temp);
                            break;

                        case 12:
                            this->AS_PerLevel = CONVERT(temp)/100;
                            break;

                        case 13:
                            this->armor = CONVERT(temp);
                            break;

                        case 14:
                            this->armorPerLevel = CONVERT(temp);
                            break;

                        case 15:
                            this->magic_resist = CONVERT(temp);
                            break;

                        case 16:
                            this->magic_resistPerLevel = CONVERT(temp);
                            break;

                        case 17:
                            this->movement_speed = CONVERT(temp);
                            break;

                        case 18:
                            this->attack_range = CONVERT(temp);
                            break;

                        case 19:
                            goto exit;
                            break;

                        default:
                            std::cout << "Error" << std::endl;
                            goto exit;
                        }
                        line.erase(0, temp.length() + 1);
                        i++;
                    } while (line != "");
                }
            }
        }
        
    exit:
        file.close();
    }

    units outputMovementSpeed()
    {
        return movement_speed;
    }
    //
    units outputAttackSpeed(uint8_t level, units bonusAttackSpeed) // https://leagueoflegends.fandom.com/wiki/Champion_statistic#Attack_speed_calculations
    {
        return base_AS + (AS_ratio + ((AS_PerLevel * (level - 1) * (0.7025 + 0.0175 * (level - 1))) + bonusAttackSpeed));
    }

    units outputHealth(uint8_t level)
    {
        return health + (healthPerLevel * (level - 1));
    }

    units outputHealthRegeneration(uint8_t level)
    {
        return healt_regeneration + (healt_regenerationPerLevel * (level - 1));
    }

    units outputArmor(uint8_t level)
    {
        return armor + (armorPerLevel * (level - 1));
    }

    units outputMagicResist(uint8_t level)
    {
        return magic_resist + (magic_resistPerLevel * (level - 1));
    }

    units outputMana(uint8_t level)
    {
        return mana + (manaPerLevel * (level - 1));
    }

    units outputManaRegeneration(uint8_t level)
    {
        return mana_regeneration + (mana_regenerationPerLevel * (level - 1));
    }

    units outputAttackDamage(uint8_t level)
    {
        return attack_damage + (attack_damagePerLevel * (level - 1));
    }

    units outputAttackRange()
    {
        return attack_range;
    }

    units outputAttackWindup()
    {
        return attack_windup;
    }

    units outputCritDamage()
    {
        return crit_damage;
    }

    std::string outputName()
    {
        return name;
    }

    void outputStats(uint8_t level)
    {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Health: " << outputHealth(level) << std::endl;
        std::cout << "Health regeneration: " << outputHealthRegeneration(level) << std::endl;
        std::cout << "Armor: " << outputArmor(level) << std::endl;
        std::cout << "Magic resist: " << outputMagicResist(level) << std::endl;
        std::cout << "Movement speed: " << outputMovementSpeed() << std::endl;
        std::cout << "Mana: " << outputMana(level) << std::endl;
        std::cout << "Mana regeneration: " << outputManaRegeneration(level) << std::endl;
        std::cout << "Attack damage: " << outputAttackDamage(level) << std::endl;
        std::cout << "Attack speed: " << outputAttackSpeed(level, 0) << std::endl;
        std::cout << "Attack range: " << outputAttackRange() << std::endl;
        std::cout << "Attack windup: " << outputAttackWindup() << std::endl;
        std::cout << "Crit damage: " << outputCritDamage() << std::endl;
    }
};