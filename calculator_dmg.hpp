struct character_lol
{//stats of lol character
    float hp{}, armor{}, magic_resist{};
    
};


struct adc_lol
{//stats of lol adc
    float ad{}, as{}, crit{}, lifesteal{}, flat_armor_penetration{}, percent_armor_penetration{}, flat_magic_resist_penetration{}, percent_magic_resist_penetration{}, hp{};
};


struct dmg
{
    float physical_dmg{}, magic_dmg{}, true_dmg{}, percent_physical_dmg{}, percent_magic_dmg{}, percent_true_dmg{}, flat_armor_penetration{}, percent_armor_penetration{}, flat_magic_resist_penetration{}, percent_magic_resist_penetration{};
};

// equation for calculating damage after armor and magic resist
float after_resist(float dmg, float resist) // https://leagueoflegends.fandom.com/wiki/Armor , the same for magic resist
{
    if(resist >= 0)
    {
        return dmg * (100/(100+resist));
    }
    else
    {
        return 2 - (100/(100-resist));
    }
}



float dmg_calculator(dmg damage, character_lol defender)
{
    return after_resist(damage.percent_magic_dmg * defender.hp, defender.magic_resist*(1-damage.percent_magic_resist_penetration)-damage.flat_magic_resist_penetration) + after_resist(damage.percent_physical_dmg * defender.hp, defender.armor*(1-damage.percent_armor_penetration)-damage.flat_armor_penetration) + damage.percent_true_dmg * defender.hp+ after_resist(damage.magic_dmg, defender.magic_resist) + after_resist(damage.physical_dmg, defender.armor) + damage.true_dmg;
}