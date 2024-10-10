// Filip Jarzyna
class BRANCH_CLASS;

class FRUIT_CLASS {
private:
    unsigned int weight;
    unsigned int length; // dlugosc na ktorej rosnie owoc
    BRANCH_CLASS* motherBranch;
    FRUIT_CLASS* prev;
    FRUIT_CLASS* next;

public:
    FRUIT_CLASS();
    FRUIT_CLASS(const FRUIT_CLASS& copy);

    FRUIT_CLASS(unsigned int len, BRANCH_CLASS* mother, FRUIT_CLASS* nextS, FRUIT_CLASS* prevS);

    FRUIT_CLASS(const FRUIT_CLASS& copy, FRUIT_CLASS* nextS, FRUIT_CLASS* prevS, BRANCH_CLASS* mother);

    ~FRUIT_CLASS();

    unsigned int getWeight();

    unsigned int getLength();

    void growthFruit();

    void fadeFruit();
    void pluckFruit();

    BRANCH_CLASS* getBranchPointer();

    // DODATKOWE METODY

    FRUIT_CLASS* getNext();
    FRUIT_CLASS* getPrev();
    void setNext(FRUIT_CLASS* fruit);
    void setPrev(FRUIT_CLASS* fruit);

    void displayMoj();

};