// Filip Jarzyna
#include <iostream>
#include <string>
using namespace std;

class PLAYER_CLASS {
protected:
    PLAYER_CLASS *next;
    PLAYER_CLASS *prev;
    unsigned int maxHp;
    unsigned int hp; // current hp
    unsigned int damage;
    unsigned int agility;

public:

    PLAYER_CLASS() {
        next = NULL;
        prev = NULL;
        maxHp = 0;
        hp = 0;
        damage = 0;
        agility = 0;
    }


    virtual void printParams() = 0;

    virtual string getIdMoje() {
        return  "";
    }

    ////////////////// MOJE

    virtual bool isDeadMoje() {
        return (getRemainingHealth() == 0);
    }

    virtual PLAYER_CLASS *getNext() {
        return next;
    }

    virtual PLAYER_CLASS *getPrev() {
        return prev;
    }

    virtual void setNext(PLAYER_CLASS *next) {
        this->next = next;
    }

    virtual void setPrev(PLAYER_CLASS *prev) {
        this->prev = prev;
    }

    ////////////////////////////////////////

    virtual unsigned int getRemainingHealth() {
        return (100 * hp) / maxHp;
    }

    virtual unsigned int getDamage() {
        return damage;
    }

    virtual unsigned int getAgility() {
        return agility;
    }

    virtual void takeDamage(unsigned int dmgTaken) {
        if (hp == 0) return;

        if (hp > dmgTaken) {
            hp -= dmgTaken;
        } else {
            die();
        }
    }

    virtual void applyWinnerReward() {
        damage += 2;
        agility += 2;
    }

    virtual void cure() {
        hp = maxHp;
    }

private:
    virtual void die() {
        hp = 0;
        if (next != NULL) {
            next->setPrev(prev);
        }

        if (prev != NULL) {
            prev->setNext(next);
        }
    }

    friend class SQUAD_CLASS;
    friend class CAESAR_CLASS;
};

class CAESAR_CLASS {
private:
    unsigned int playerCount;
    friend class PLAYER_CLASS;

public:
    CAESAR_CLASS() {
        playerCount = 0;
    }

    CAESAR_CLASS(const CAESAR_CLASS &copy) {
        playerCount = copy.playerCount;
    }

    void judgeDeathOrLife(PLAYER_CLASS *player) {
        playerCount++;
        if (player == NULL) return;
        if (playerCount % 3 == 0) {
            player->die(); //usmierca gracza
            playerCount = 0;
        }
    }
};

class ARENA_CLASS {
private:
    CAESAR_CLASS caesar;

public:
    ARENA_CLASS(CAESAR_CLASS *copy) {
        caesar = CAESAR_CLASS(*copy);
    }


    void fight(PLAYER_CLASS *p1, PLAYER_CLASS *p2) {
        if (p1 == NULL || p2 == NULL) return;
        if (p1->isDeadMoje() || p2->isDeadMoje()) return; //jesli ktorys jest martwy

        //wybor ktory ma pierwszenstwo
        if (p1->getAgility() < p2->getAgility()) {
            PLAYER_CLASS *temp = p1;
            p1 = p2;
            p2 = temp;
        }

        int atackCount = 0;

        p1->printParams();
        p2->printParams();
        //walka
        while (atackCount < 40 && p1->getRemainingHealth() >= 10 && p2->getRemainingHealth() >= 10) {
            p2->takeDamage(p1->getDamage());
            atackCount++;
            p2->printParams();
            if (atackCount < 40 && p2->getRemainingHealth() >= 10) {
                p1->takeDamage(p2->getDamage());
                atackCount++;
                p1->printParams();
            } else {
                break;
            }
        }

        //cezar osadza
        if (!p1->isDeadMoje()) {
            if (atackCount % 2 == 0) {
                caesar.judgeDeathOrLife(p1);
            } else {
                caesar.judgeDeathOrLife(NULL);
            }

            p1->printParams();
        }

        if (!p2->isDeadMoje()) {
            if (atackCount % 2 == 0) {
                caesar.judgeDeathOrLife(p2);
            } else {
                caesar.judgeDeathOrLife(NULL);
            }

            p2->printParams();
        }

        //nagroda
        if (!p1->isDeadMoje()) {
            p1->applyWinnerReward();
            p1->cure();
        }

        if (!p2->isDeadMoje()) {
            p2->applyWinnerReward();
            p2->cure();
        }

        p1->printParams();
        p2->printParams();
    }
};

class HUMAN_CLASS : virtual public PLAYER_CLASS {
protected:
    std::string id;
    unsigned int defense;

public:
    HUMAN_CLASS(string newid) {
        next = NULL;
        prev = NULL;
        this->id = newid;
        maxHp = 200;
        hp = 200;
        damage = 30;
        agility = 10;
        defense = 10;
    }

    string getIdMoje() {
        return id;
    }

    void takeDamage(unsigned int dmgTaken) {
        if (dmgTaken > defense + agility) {
            dmgTaken = dmgTaken - defense - agility;
            PLAYER_CLASS::takeDamage(dmgTaken);
        }
    }

    void printParams() {
        if (hp != 0) {
            // printf("%s:%d:%d:%d\%:%d:%d:%d\n", id.c_str(), maxHp, hp, this->getRemainingHealth(), damage, agility,
            //        defense);

            cout << id << ':' << maxHp << ':' << hp << ':' << this->getRemainingHealth() << '%' << ':' << damage << ':'
                    << agility << ':' << defense << endl;
        } else {
            // printf("%s:R.I.P.\n", id.c_str());
            cout << id << ':' << "R.I.P." << endl;
        }
    }
};

class BEAST_CLASS : virtual public PLAYER_CLASS {
protected:
    string id;

public:
    BEAST_CLASS(string id) {
        next = NULL;
        prev = NULL;
        this->id = id;
        maxHp = 150;
        hp = 150;
        damage = 40;
        agility = 20;
    }

    string getIdMoje() {
        return id;
    }

    void printParams() {
        if (hp != 0) {
            // printf("%s:%d:%d:%d\%:%d:%d\n", id.c_str(), maxHp, hp, this->getRemainingHealth(), damage, agility);
            cout << id << ':' << maxHp << ':' << hp << ':' << this->getRemainingHealth() << '%' << ':' << getDamage() <<
                    ':'
                    << agility << endl;
        } else {
            // printf("%s:R.I.P.\n", id.c_str());
            cout << id << ':' << "R.I.P." << endl;
        }
    }

    unsigned int getDamage() {
        if (getRemainingHealth() < 25) {
            return 2 * damage;
        }

        return damage;
    }

    void takeDamage(unsigned int dmgTaken) {
        if (dmgTaken > agility / 2) {
            dmgTaken -= (agility / 2);
            PLAYER_CLASS::takeDamage(dmgTaken);
        }
    }

    // private:
    //     void die() {
    //         hp = 0;
    //     }
};

class BERSERKER_CLASS : public HUMAN_CLASS, public BEAST_CLASS {
private:
    bool beastmode;

public:
    BERSERKER_CLASS(string humanId, string beastId): HUMAN_CLASS(humanId), BEAST_CLASS(beastId) {
        next = NULL;
        prev = NULL;
        maxHp = 200;
        hp = 200;
        damage = 35;
        agility = 5;
        defense = 15;
        beastmode = false;
    }

    string getIdMoje() {
        if (beastmode) {
            return BEAST_CLASS::id;
        }

        return HUMAN_CLASS::id;
    }

    void printParams() {
        if (beastmode) {
            BEAST_CLASS::printParams();
        } else {
            HUMAN_CLASS::printParams();
        }
    }

    void takeDamage(unsigned int dmgTaken) {
        if (beastmode) {
            BEAST_CLASS::takeDamage(dmgTaken);
            if (getRemainingHealth() == 0) {
                beastmode = false;
            }
        } else {
            HUMAN_CLASS::takeDamage(dmgTaken);
            if (getRemainingHealth() < 25 && getRemainingHealth() > 0) {
                beastmode = true;
            }
        }
    }

    unsigned int getDamage() {
        if (beastmode) {
            return BEAST_CLASS::getDamage();
        }
        return HUMAN_CLASS::getDamage();
    }

    unsigned int getAgility() {
        if (beastmode) {
            return BEAST_CLASS::getAgility();
        }
        return HUMAN_CLASS::getAgility();
    }

    void applyWinnerReward() {
        PLAYER_CLASS::applyWinnerReward();
        if (getRemainingHealth() >= 25) {
            beastmode = false;
        }
    }

    void cure() {
        PLAYER_CLASS::cure();
        beastmode = false;
    }

private:
    void die() {
        hp = 0;

        if (next != NULL) {
            next->setPrev(prev);
        }

        if (prev != NULL) {
            prev->setNext(next);
        }

        beastmode = false;
    }
};

class SQUAD_CLASS : virtual public PLAYER_CLASS {
private:
    string id;
    unsigned int members;
    PLAYER_CLASS *first;

public:
    SQUAD_CLASS(string id) {
        next = NULL;
        prev = NULL;
        first = NULL;
        this->id = id;
        maxHp = 1;
        hp = 0;
        damage = 0;
        agility = -1;
        members = 0;
    }


    string getIdMoje() {
        return id;
    }

    void takeDamage(unsigned int dmgTaken) {
        dmgTaken /= members;
        if (dmgTaken > 0) {
            //zeby byl update
            hp = 0;
            maxHp = 1;
            agility = -1;

            PLAYER_CLASS *temp = first;

            while (temp != NULL) {
                damage -= temp->getDamage();
                temp->takeDamage(dmgTaken);
                updateHpAndAg(temp);
                if (temp->isDeadMoje()) {
                    //temp to first
                    if (temp == first) {
                        first = temp->getNext();
                    }

                    temp = temp->getNext();
                } else {
                    damage += temp->getDamage();
                    temp = temp->getNext();
                }
            }
        }
    }

    void applyWinnerReward() {
        //zeby byl update
        hp = 0;
        maxHp = 1;
        agility = -1;
        PLAYER_CLASS *temp = first;
        while (temp != NULL) {
            damage -= temp->getDamage();
            temp->applyWinnerReward();
            damage += temp->getDamage();
            updateHpAndAg(temp);
            temp = temp->getNext();
        }
    }

    void cure() {
        //zeby byl update
        hp = 0;
        maxHp = 1;
        agility = -1;
        PLAYER_CLASS *temp = first;
        while (temp != NULL) {
            damage -= temp->getDamage();
            temp->cure();
            damage += temp->getDamage();
            updateHpAndAg(temp);
            temp = temp->getNext();
        }
    }

    bool isDeadMoje() {
        return (members == 0);
    }

    void printParams() {
        if (members != 0) {
            updateAllStats();
            bubbleSort();
            // printf("%s:%d:%d\%:%d:%d\n", id.c_str(), members, this->getRemainingHealth(), damage, agility);
            cout << id << ':' << members << ':' << this->getRemainingHealth() << '%' << ':' << damage << ':' << agility
                    << endl;

            PLAYER_CLASS *temp = first;
            while (temp != NULL) {
                temp->printParams();
                temp = temp->getNext();
            }
        } else {
            // printf("%s:nemo\n", id.c_str());
            cout << id << ":" << "nemo" << endl;
        }
    }

    void addPlayer(PLAYER_CLASS *player) {
        if (player != NULL && !player->isDeadMoje()) {
            if (first != NULL) {
                PLAYER_CLASS *temp = first;
                PLAYER_CLASS *tempPrev = NULL;
                //dodawanie zgodne z kolejnosia leksykograficzna
                //dodawanie przed noda
                while (temp != NULL) {
                    if (temp == player) return;

                    if (!PlayerCompare(temp, player)) {
                        player->setPrev(tempPrev);
                        player->setNext(temp);

                        if (tempPrev != NULL) {
                            tempPrev->setNext(player);
                        } else {
                            first = player;
                        }
                        temp->setPrev(player);
                        updateHpAndAg(player);
                        damage += player->getDamage();
                        members++;
                        return;
                    }

                    tempPrev = temp;
                    temp = temp->getNext();
                }
                //gdy dodajemy player na koniec listy
                player->setPrev(tempPrev);
                tempPrev->setNext(player); //tempPrev nigdy nie bedzie NULL
            } else {
                //jesli members == 0
                first = player;
                player->setNext(NULL);
                player->setPrev(NULL);
            }

            damage += player->getDamage();
            updateHpAndAg(player);
            members++;
        }
    }

private:
    void swapNodes(PLAYER_CLASS *p1, PLAYER_CLASS *p2) {
        if (p1 == p2) return;

        PLAYER_CLASS *prev1 = p1->prev;
        PLAYER_CLASS *next1 = p1->next;
        PLAYER_CLASS *prev2 = p2->prev;
        PLAYER_CLASS *next2 = p2->next;

        if (next1 == p2) {
            //jesli obok siebie 1
            p1->next = next2;
            p1->prev = p2;
            p2->next = p1;
            p2->prev = prev1;

            if (next2 != NULL) next2->prev = p1;
            if (prev1 != NULL) prev1->next = p2;
        } else if (next2 == p1) {
            //obok siebie 2
            p2->next = next1;
            p2->prev = p1;
            p1->next = p2;
            p1->prev = prev2;

            if (next1 != NULL) next1->prev = p2;
            if (prev2 != NULL) prev2->next = p1;
        } else {
            //nie obok siebie
            if (next1 != NULL) next1->prev = p2;
            if (prev1 != NULL) prev1->next = p2;

            if (next2 != NULL) next2->prev = p1;
            if (prev2 != NULL) prev2->next = p1;

            p1->next = next2;
            p1->prev = prev2;

            p2->next = next1;
            p2->prev = prev1;
        }

        //update firsta
        if (p1->prev == NULL) first = p1;
        if (p2->prev == NULL) first = p2;
    }

    void bubbleSort() {
        if (first == NULL) return;

        PLAYER_CLASS *jp;
        int j, i;

        bool swapped;
        for (i = 0; i < members - 1; i++) {
            swapped = false;
            for (j = 0, jp = first; j < members - i - 1; j++, jp = jp->getNext()) {
                if (!PlayerCompare(jp, jp->getNext())) {
                    PLAYER_CLASS *temp = jp->getNext();
                    swapNodes(jp, jp->getNext());
                    jp = temp;
                    swapped = true;
                }
            }

            // If no two elements were swapped
            // by inner loop, then break
            if (swapped == false)
                break;
        }
    }

    // true if player >
    bool PlayerCompare(PLAYER_CLASS *p1, PLAYER_CLASS *p2) {
        if (p1->getIdMoje() != p2->getIdMoje())
            return p1->getIdMoje() < p2->getIdMoje();

        if (p1->maxHp != p2->maxHp)
            return p1->maxHp < p2->maxHp;

        if (p1->hp != p2->hp)
            return p1->hp < p2->hp;

        if (p1->getDamage() != p2->getDamage())
            return p1->getDamage() < p2->getDamage();

        if (p1->getAgility() != p2->getAgility())
            return p1->getAgility() < p2->getAgility();
        return false;
    }

    void updateAllStats() {
        //zeby byl update
        hp = 0;
        maxHp = 1;
        agility = -1;
        damage = 0;
        PLAYER_CLASS *temp = first;
        while (temp != NULL) {
            damage += temp->getDamage();
            updateHpAndAg(temp);
            temp = temp->getNext();
        }
    }

    void updateHpAndAg(PLAYER_CLASS *player) {
        //agillity musi miec najmniejsza wartosc
        if (!player->isDeadMoje()) {
            if (player->agility < agility) {
                agility = player->agility;
            }

            //  hp / maxHp ma byc najwieksze
            if ((player->hp * 1000 / player->maxHp) > (hp * 1000 / maxHp)) {
                hp = player->hp;
                maxHp = player->maxHp;
            }
        } else {
            members--;
            if (player->prev != NULL) {
                updateHpAndAg(player->prev);
            } else {
                if (player->next != NULL) {
                    updateHpAndAg(player->next);
                } else {
                    agility = 0;
                    damage = 0;
                    maxHp = 1;
                    hp = 0;
                    members = 0;
                }
            }
        }
    }

    void die() {
        while (first != NULL) {
            PLAYER_CLASS *tempDel = first;
            first = first->getNext();
            tempDel->die();
        }
        members = 0;
        hp = 0;
        maxHp = 1;
        agility = -1;
        damage = 0;
    }
};