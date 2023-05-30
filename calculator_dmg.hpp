#pragma once
#include<iostream>
#include <fstream>
#include <string>

using units=float;

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
    units health, healt_regeneration,// per 5 sec
     armor, magic_resist, movement_speed, mana, mana_regeneration, attack_damage, crit_damage, attack_range, base_AS, attack_windup, AS_ratio=1;

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
        std::ifstream file("dane.csv");
        std::string line;
        if(file.is_open())
        {
            while(std::getline(file, line))
            {
                if(line.find(name)!=std::string::npos)
                {
                        std::cout<<line<<std::endl;
                }
            }
        }
        
    }

    units outputMovementSpeed()
    {
        return movement_speed;
    }
//
    units outputAttackSpeed(uint8_t level, units bonusAttackSpeed)// https://leagueoflegends.fandom.com/wiki/Champion_statistic#Attack_speed_calculations
    {
        return base_AS + (AS_ratio+((AS_PerLevel*(level-1)*(0.7025+0.0175*(level-1)))+bonusAttackSpeed));
    }

    units outputHealth(uint8_t level)
    {
        return health + (healthPerLevel*(level-1));
    }

    units outputHealthRegeneration(uint8_t level)
    {
        return healt_regeneration + (healt_regenerationPerLevel*(level-1));
    }

    units outputArmor(uint8_t level)
    {
        return armor + (armorPerLevel*(level-1));
    }

    units outputMagicResist(uint8_t level)
    {
        return magic_resist + (magic_resistPerLevel*(level-1));
    }

    units outputMana(uint8_t level)
    {
        return mana + (manaPerLevel*(level-1));
    }

    units outputManaRegeneration(uint8_t level)
    {
        return mana_regeneration + (mana_regenerationPerLevel*(level-1));
    }

    units outputAttackDamage(uint8_t level)
    {
        return attack_damage + (attack_damagePerLevel*(level-1));
    }

};