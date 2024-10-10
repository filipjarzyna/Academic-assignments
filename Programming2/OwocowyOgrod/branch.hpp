// Filip Jarzyna
class FRUIT_CLASS;
class TREE_CLASS;

class BRANCH_CLASS {
private:
    unsigned int lenght; // dlugosc galezi
    unsigned int height;

    unsigned int fruitsTotal;
    unsigned int weightsTotal;

    FRUIT_CLASS* first;
    FRUIT_CLASS* last;

    BRANCH_CLASS* next;
    BRANCH_CLASS* prev;

    TREE_CLASS* tree;

public:
    BRANCH_CLASS();
    BRANCH_CLASS(const BRANCH_CLASS& copy);

    BRANCH_CLASS(TREE_CLASS* treeSet, BRANCH_CLASS* nextSet, BRANCH_CLASS* prevSet, unsigned int height);

    ~BRANCH_CLASS();

    BRANCH_CLASS(const BRANCH_CLASS& copy, BRANCH_CLASS* next, BRANCH_CLASS* prev, TREE_CLASS* tree);
    BRANCH_CLASS(const BRANCH_CLASS& copy, BRANCH_CLASS* swaped, TREE_CLASS* tree);
    unsigned int getFruitsTotal();

    unsigned int getWeightsTotal();

    unsigned int getHeight();

    unsigned int getLength();

    void growthBranch();

    void fadeBranch();

    void harvestBranch(unsigned int weightLim);

    void cutBranch(unsigned int newLen);
    FRUIT_CLASS* getFruitPointer(unsigned int len);

    TREE_CLASS* getTreePointer();

    // DODATKOWE METODY

    void totalWeightAdd(unsigned int add, bool isNeg);
    void fruitAmountAdd(unsigned int add, bool isNeg);

    BRANCH_CLASS* getNext();

    BRANCH_CLASS* getPrev();

    void setNext(BRANCH_CLASS* nextS);
    void setPrev(BRANCH_CLASS* prevS);

    FRUIT_CLASS *getFirst();

    FRUIT_CLASS *getLast();

    void setFirst(FRUIT_CLASS *first);

    void setLast(FRUIT_CLASS *last);

    void displayMoj();
};