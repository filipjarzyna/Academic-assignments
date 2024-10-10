// Filip Jarzyna
class GARDEN_CLASS;
class BRANCH_CLASS;

class TREE_CLASS {
private:
    unsigned int id;
    unsigned int height;

    unsigned int branchesTotal;
    unsigned int fruitsTotal;
    unsigned int weightsTotal;

    TREE_CLASS* next;
    TREE_CLASS* prev;

    BRANCH_CLASS* first;
    BRANCH_CLASS* last;

    GARDEN_CLASS* garden;

public:

    TREE_CLASS();
    TREE_CLASS(const TREE_CLASS& copy);
    TREE_CLASS(unsigned int idS, GARDEN_CLASS* mother, TREE_CLASS* nextS, TREE_CLASS* prevS);
    TREE_CLASS(const TREE_CLASS& copy, TREE_CLASS* nextS, TREE_CLASS* prevS, unsigned int idS, GARDEN_CLASS* gardenS);
    ~TREE_CLASS();

    unsigned int getBranchesTotal();
    unsigned int getFruitsTotal();

    unsigned int getWeightsTotal();
    unsigned int getNumber();

    unsigned int getHeight();

    void growthTree();
    void fadeTree();

    void harvestTree(unsigned int weightLim);

    void cutTree(unsigned int hLim);

    void cloneBranch(BRANCH_CLASS* branch);

    GARDEN_CLASS* getGardenPointer();
    BRANCH_CLASS* getBranchPointer(unsigned int h);

    // METODY DODATKOWE
    void totalWeightAdd(unsigned int add, bool isNeg);

    void fruitAmountAdd(unsigned int add, bool isNeg);

    void branchAmountAdd(unsigned int add, bool isNeg);

    void setNext(TREE_CLASS* nextS);

    void setPrev(TREE_CLASS* prevS);

    TREE_CLASS* getNext();

    TREE_CLASS* getPrev();

    BRANCH_CLASS *getFirst();

    void setFirst(BRANCH_CLASS *first);

    BRANCH_CLASS *getLast();

    void setLast(BRANCH_CLASS *last);

    void displayMoj();
};