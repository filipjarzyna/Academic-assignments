// Filip Jarzyna
#include "garden.hpp"
// #include "branch.hpp"
#include "tree.hpp"
#include <cstdio>

GARDEN_CLASS::GARDEN_CLASS() {
    treesTotal = 0;
    branchesTotal = 0;
    fruitsTotal = 0;
    weightsTotal = 0;
    first = NULL;
    last = NULL;
}

GARDEN_CLASS::~GARDEN_CLASS() {
    TREE_CLASS* temp;
    while(first != NULL) {
        temp = first->getNext();
        delete first;
        first = temp;
    }
}

unsigned int GARDEN_CLASS::getTreesTotal()
{
    return treesTotal;
}

unsigned int GARDEN_CLASS::getBranchesTotal()
{
    return branchesTotal;
}

unsigned int GARDEN_CLASS::getFruitsTotal()
{
    return fruitsTotal;
}

unsigned int GARDEN_CLASS::getWeightsTotal()
{
    return weightsTotal;
}

TREE_CLASS* GARDEN_CLASS::getTreePointer(unsigned int id)
{
    TREE_CLASS* temp = first;
    while (temp != NULL) {
        if (temp->getNumber() == id) {
            return temp;
        }
        temp = temp->getNext();
    }
    return NULL;
}

void GARDEN_CLASS::plantTree()
{

    unsigned int lastId = -1;
    if (last != NULL)
        lastId = last->getNumber();

    if (lastId != treesTotal - 1) {
        TREE_CLASS* temp = first;
        unsigned int freeId = 0;
        while (temp != NULL) {
            if (temp->getNumber() > freeId) {
                // if (freeId == 0) {
                //     first = new TREE_CLASS(freeId, this, temp, temp->getPrev());
                // } else {
                //     new TREE_CLASS(freeId, this, temp, temp->getPrev());
                // }
                new TREE_CLASS(freeId, this, temp, temp->getPrev());
                treesTotal++;
                return;
            }
            freeId++;
            temp = temp->getNext();
        }

        // temp = new TREE_CLASS(freeId, this, NULL, last);
        // if (treesTotal != 0)
        //     last->setNext(temp);
        // last = temp;
        new TREE_CLASS(freeId, this, NULL, last);
        treesTotal++;
    } else {
        new TREE_CLASS(treesTotal, this, NULL, last);
        treesTotal++;
    }
}

void GARDEN_CLASS::extractTree(unsigned int id)
{
    if (id > treesTotal / 2) {
        TREE_CLASS* temp = last;
        while (temp != NULL) {
            if (temp->getNumber() == id) {
                delete temp;
                return;
            }

            temp = temp->getPrev();
        }
    } else {
        TREE_CLASS* temp = first;
        while (temp != NULL) {
            if (temp->getNumber() == id) {
                delete temp;
                return;
            }
            temp = temp->getNext();
        }
    }
}

void GARDEN_CLASS::growthGarden()
{
    TREE_CLASS* temp = first;
    while (temp != NULL) {
        temp->growthTree();
        temp = temp->getNext();
    }
}

void GARDEN_CLASS::fadeGarden()
{
    TREE_CLASS* temp = first;
    while (temp != NULL) {
        temp->fadeTree();
        temp = temp->getNext();
    }
}

void GARDEN_CLASS::harvestGarden(unsigned int lim)
{
    TREE_CLASS* temp = first;
    while (temp != NULL) {
        temp->harvestTree(lim);
        temp = temp->getNext();
    }
}

void GARDEN_CLASS::cloneTree(unsigned int id)
{
    TREE_CLASS* cloned = getTreePointer(id);
    if (cloned == NULL)
        return;
    // plantTree();

    TREE_CLASS* temp = first;
    unsigned int freeId = 0;
    while (temp != NULL) {
        if (temp->getNumber() != freeId) {

//            TREE_CLASS* prevTemp = temp->getPrev();
            new TREE_CLASS(*cloned, temp, temp->getPrev(), freeId, this);
//            temp->setPrev(newTree);
//            if (prevTemp != NULL) {
//                prevTemp->setNext(newTree);
//            }
            return;
        }

        freeId++;
        temp = temp->getNext();
    }

    new TREE_CLASS(*cloned, NULL, last, freeId, this);
}

// METODY DODATKOWE

void GARDEN_CLASS::totalWeightAdd(unsigned int add, bool isNeg)
{
    if (isNeg) {
        weightsTotal -= add;
    } else {
        weightsTotal += add;
    }
}

void GARDEN_CLASS::fruitAmountAdd(unsigned int add, bool isNeg)
{
    if (isNeg) {
        fruitsTotal -= add;
    } else {
        fruitsTotal += add;
    }
}

void GARDEN_CLASS::branchAmountAdd(unsigned int add, bool isNeg) {
    if (isNeg) {
        branchesTotal -= add;
    } else {
        branchesTotal += add;
    }
}

void GARDEN_CLASS::treeAmountAdd(unsigned int add, bool isNeg)
{
    if (isNeg) {
        treesTotal -= add;
    } else {
        treesTotal += add;
    }
}


void GARDEN_CLASS::displayMoj()
{
    TREE_CLASS* tree;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int quantity = (*this).getTreesTotal();

    printf("GARDEN:\n");
    printf("    Number of Trees: %u\n", quantity);
    printf("    Number of Branches: %u\n", (*this).getBranchesTotal());
    printf("    Number of Fruits: %u\n", (*this).getFruitsTotal());
    printf("    Total Weight: %u\n", (*this).getWeightsTotal());
    printf("    All Trees:\n");

    while (i < quantity) {
        tree = (*this).getTreePointer(j);
        if (tree != NULL) {
            (*tree).displayMoj();
            i += 1;
        }
        j += 1;
    }
    printf("    Successful Display all of %u Trees\n", quantity);
}

TREE_CLASS* GARDEN_CLASS::getFirst() {
    return first;
}

void GARDEN_CLASS::setFirst(TREE_CLASS *first) {
    GARDEN_CLASS::first = first;
}

TREE_CLASS* GARDEN_CLASS::getLast() {
    return last;
}

void GARDEN_CLASS::setLast(TREE_CLASS *last) {
    GARDEN_CLASS::last = last;
}
