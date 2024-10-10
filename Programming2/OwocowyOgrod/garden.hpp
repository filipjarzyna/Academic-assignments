// Filip Jarzyna
class TREE_CLASS;

class GARDEN_CLASS {
private:
    unsigned int treesTotal;
    unsigned int branchesTotal;
    unsigned int fruitsTotal;
    unsigned int weightsTotal;
    
    TREE_CLASS* first;
    TREE_CLASS* last;

public:
    GARDEN_CLASS();

    ~GARDEN_CLASS();

    unsigned int getTreesTotal();

    unsigned int getBranchesTotal();

    unsigned int getFruitsTotal();

    unsigned int getWeightsTotal();

    TREE_CLASS* getTreePointer(unsigned int id);

    void plantTree();

    void extractTree(unsigned int id);

    void growthGarden();

    void fadeGarden();

    void harvestGarden(unsigned int lim);
    void cloneTree(unsigned int id);

    // METODY DODATKOWE


    void totalWeightAdd(unsigned int add, bool isNeg);
    void fruitAmountAdd(unsigned int add, bool isNeg);
    void branchAmountAdd(unsigned int add, bool isNeg);
    void treeAmountAdd(unsigned int add, bool isNeg);

    TREE_CLASS *getFirst();

    void setFirst(TREE_CLASS *first);

    TREE_CLASS *getLast();

    void setLast(TREE_CLASS *last);

    void displayMoj();
};