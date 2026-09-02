#include <iostream>
#include <cstring>
#include <vector>


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
    Player() {

    }

    Player(char* name, int health, int stagger, int light){
        std::strcpy(this->name, name);
        HP = health;
        maxHP = health;
        stagRes = stagger;
        maxStagRes = stagger;
        light = light;
        maxLight = light;
    }

    // getter and setter functions
    void setName(char* newName) {
        std::strcpy(name, newName);
    }
    char* getName() {
        return name;
    }

    void setMaxHP(int newMaxHP) {
        maxHP = newMaxHP;
        HP = maxHP;
    }
    int getMaxHP() {
        return maxHP;
    }
    int getHP() {
        return HP;
    }

    void setMaxStagRes(int newMaxStagRes) {
        maxStagRes = newMaxStagRes;
        stagRes = maxStagRes;
    }
    int getMaxStagRes() {
        return maxStagRes;
    }
    int getStagRes() {
        return stagRes;
    }

    void setMaxLight(int newMaxLight) {
        maxLight = newMaxLight;
        light = maxLight;
    }
    int getMaxLight() {
        return maxLight;
    }
    int getLight() {
        return light;
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

void printPlayerStats(Player player) {
    std::cout << "Name: " << player.getName() << "\n";
    std::cout << "HP: " << player.getHP() << "/" << player.getMaxHP() << "\n";
    std::cout << "Stagger Resistance: " << player.getStagRes() << "/" << player.getMaxStagRes() << "\n";
    std::cout << "Light: " << player.getLight() << "/" << player.getMaxLight() << "\n\n";
} //end printplayerstats

Player initPlayer() {
    char name[50];
    int health;
    int stagger;
    int light;

    std::cin.ignore(1000, '\n'); // Clears the buffer
    std::cout << "Enter player's name: ";
    std::cin.ignore(1000, '\n'); // Clears the buffer
    std::cout << "Enter Player's Max HP: ";
    std::cin.ignore(1000, '\n'); // Clears the buffer
    std::cout << "Enter Player's Max Stagger Resistance: ";
    std::cin.ignore(1000, '\n'); // Clears the buffer
    std::cout << "Enter Player's Max Light: ";
    std::cin.ignore(1000, '\n'); // Clears the buffer

    //not storing properly
    return {name, health, stagger, light};
} //end initParty

int main(){
    //ask how many players there are with input read
    int numPlayers;
    std::cout << "Enter number of players: ";
    std::cin >> numPlayers;

    //initialize class objects
    Player players[numPlayers];

    //ask player names and stats
    for (int i = 0; i < numPlayers; i++) {
        players[i] = initPlayer();
    }

    std::cout << "Printing Party Details... \n";
    for (int i = 0; i < numPlayers; i++) {
        printPlayerStats(players[i]);
    }
    return 0;
}
