#pragma once
#include <iostream>
#include <fstream>
#include <string>

using UNITS = double;
using LEVEL = uint8_t;
#define CONVERT std::stod

// equation for calculating damage after armor and magic resist
UNITS DMG_after_resist(UNITS dmg, UNITS resist) // https://leagueoflegends.fandom.com/wiki/Armor , the same for magic resist
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

    UNITS health, healt_regeneration, // per 5 sec
        armor, magic_resist, movement_speed, mana, mana_regeneration, attack_damage, crit_damage=1.75, attack_range, base_AS, attack_windup=0, AS_ratio = 1;

    UNITS healthPerLevel, healt_regenerationPerLevel, armorPerLevel, magic_resistPerLevel, manaPerLevel, mana_regenerationPerLevel, attack_damagePerLevel, AS_PerLevel;

public:
    Champion_class(UNITS health, UNITS healt_regeneration, UNITS armor, UNITS magic_resist, UNITS movement_speed, UNITS mana, UNITS mana_regeneration, UNITS attack_damage, UNITS crit_damage, UNITS attack_range, UNITS base_AS, UNITS attack_windup, UNITS AS_ratio, UNITS healthPerLevel, UNITS healt_regenerationPerLevel, UNITS armorPerLevel, UNITS magic_resistPerLevel, UNITS manaPerLevel, UNITS mana_regenerationPerLevel, UNITS attack_damagePerLevel, UNITS AS_PerLevel)
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

    UNITS outputMovementSpeed()
    {
        return movement_speed;
    }
    //
    UNITS outputAttackSpeed(LEVEL level, UNITS bonusAttackSpeed) // https://leagueoflegends.fandom.com/wiki/Champion_statistic#Attack_speed_calculations
    {
        return base_AS + (AS_ratio + ((AS_PerLevel * (level - 1) * (0.7025 + 0.0175 * (level - 1))) + bonusAttackSpeed));
    }

    UNITS outputHealth(LEVEL level)
    {
        return health + (healthPerLevel * (level - 1));
    }

    UNITS outputHealthRegeneration(LEVEL level)
    {
        return healt_regeneration + (healt_regenerationPerLevel * (level - 1));
    }

    UNITS outputArmor(LEVEL level)
    {
        return armor + (armorPerLevel * (level - 1));
    }

    UNITS outputMagicResist(LEVEL level)
    {
        return magic_resist + (magic_resistPerLevel * (level - 1));
    }

    UNITS outputMana(LEVEL level)
    {
        return mana + (manaPerLevel * (level - 1));
    }

    UNITS outputManaRegeneration(LEVEL level)
    {
        return mana_regeneration + (mana_regenerationPerLevel * (level - 1));
    }

    UNITS outputAttackDamage(LEVEL level)
    {
        return attack_damage + (attack_damagePerLevel * (level - 1));
    }

    UNITS outputAttackRange()
    {
        return attack_range;
    }

    UNITS outputAttackWindup()
    {
        return attack_windup;
    }

    UNITS outputCritDamage()
    {
        return crit_damage;
    }

    std::string outputName()
    {
        return name;
    }

    void outputStats(LEVEL level)
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

    UNITS outputTimeForAA(LEVEL level, UNITS bonusAttackSpeed)
    {
        return (1 / outputAttackSpeed(level, bonusAttackSpeed));
    }
};

void fight(Champion_class champion1, Champion_class champion2, LEVEL level1, LEVEL level2)
{
    UNITS time{};
    UNITS health1{ champion1.outputHealth(level1) };
    UNITS health2{ champion2.outputHealth(level2) };
    UNITS timeAA1{ champion1.outputTimeForAA(level1, 0) };
    UNITS timeAA2{ champion2.outputTimeForAA(level2, 0) };

    while(health1 > 0 && health2 > 0)
    {
        if (timeAA1 < timeAA2)
        {
            health2 -= champion1.outputAttackDamage(level1);
            time += timeAA1;
            timeAA2 -= timeAA1;
            timeAA1= champion1.outputTimeForAA(level1, 0);
        }
        else if (timeAA1 > timeAA2)
        {
            health1 -= champion2.outputAttackDamage(level2);
            time += timeAA2;
            timeAA1 -= timeAA2;
            timeAA2 = champion2.outputTimeForAA(level2, 0);
        }
        else
        {
            health1 -= champion2.outputAttackDamage(level2);
            health2 -= champion1.outputAttackDamage(level1);
            time += timeAA1;
            timeAA1 = champion1.outputTimeForAA(level1, 0);
            timeAA2 = champion2.outputTimeForAA(level2, 0);
        }
    }

    if(health1 <= 0 && health2 <= 0)
    {
        std::cout << "Draw" << std::endl;
    }
    else if(health1 <= 0)
    {
        std::cout << champion2.outputName() << " won " << "in " << time <<" seconds"<< std::endl;
    }
    else
    {
        std::cout << champion1.outputName() << " won " << "in " << time <<" seconds"<< std::endl;
    }
}