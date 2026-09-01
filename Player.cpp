#include <iostream>
#include <cstring>


class Player{
private:
    char name[50];
    int HP;
    int maxHP;
    int stagRes;
    int maxStagRes;
    int light;
    int maxLight;

    //boons
    int poise = 0;
    int safeguard = 0;
    int thorns = 0;
    int aggro = 0;
    int charge = 0;

    //ailment
    int paralyze = 0;
    int burn = 0;
    int tremor = 0;
    int bleed = 0;
    int sinking = 0;

    //buff / debuff
    int strength = 0;
    int endure = 0;
    int protect = 0;
    int resolve = 0;
    int haste = 0;

public:
    // default constructor
    Player(char* name, int health, int stagger, int light){
        std::strcpy(this->name, name);
        HP = health;
        maxHP = health;
        stagRes = stagger;
        maxStagRes = stagger;
        light = light;
        maxLight = light;

    }

    void endScene(Player player){
        //buff / debuff reset
        player.strength = 0;
        player.endure = 0;
        player.protect = 0;
        player.resolve = 0;
        player.haste = 0;

        //boon reduction
        player.aggro = player.aggro / 2;
        player.thorns = 0;

        //burn
        takeBurn(player);
        takeBleed(player, 1);
        takeSinking(player);
    }

    void takeBurn(Player player){
        changeHP(player, -player.burn);
        player.burn = player.burn / 2;
    }

    void takeBleed(Player player, int stat){
        if(stat == 1){
            changeHP(player, -player.bleed);
            player.bleed = player.bleed / 2;
        }
        else{
            changeHP(player, -player.bleed);
            player.bleed--;
        }

    }

    void takeSinking(Player player){
        if(player.stagRes > 0){
            changeStagRes(player, -player.sinking);
            player.sinking = player.sinking / 2;
            if(player.stagRes < 1)
                player.stagRes = 1;
        }
    }

    void changeStagRes(Player player, int stagger){
        player.stagRes = player.stagRes + stagger;
        if(player.stagRes < 0)
            player.stagRes = 0;
        else if(player.stagRes > player.maxStagRes)
            player.stagRes = player.maxStagRes;
    }

    void changeHP(Player player, int HP){
        player.HP = player.HP + HP;
        if(player.HP < 0)
            player.HP = 0;
        else if(player.HP > player.maxHP)
            player.HP = player.maxHP;
    }

};


int main(){
    return 0;
}


