// Filip Jarzyna
#include <cstdio>
#include "tree.hpp"
#include "branch.hpp"
#include "garden.hpp"

TREE_CLASS::TREE_CLASS() {
    id = 0;
    height = 0;

    branchesTotal = 0;
    fruitsTotal = 0;
    weightsTotal = 0;

    next = NULL;
    prev = NULL;

    first = NULL;
    last = NULL;

    garden = NULL;
}

TREE_CLASS::TREE_CLASS(const TREE_CLASS& copy) {
    id = 0;
    height = copy.height;

    branchesTotal = 0;
    fruitsTotal =  0;
    weightsTotal = 0;

    next = NULL;
    prev = NULL;

    first = NULL;
    last = NULL;
    garden = NULL;

    //copy branches
    if (copy.branchesTotal > 0) {
        BRANCH_CLASS* tempCpy = copy.first;
        while (tempCpy != NULL) {
            new BRANCH_CLASS(*tempCpy, NULL, last, this);
            tempCpy = tempCpy->getNext();
        }

    }
}



TREE_CLASS::TREE_CLASS(unsigned int idS, GARDEN_CLASS* mother, TREE_CLASS* nextS, TREE_CLASS* prevS) :
branchesTotal(0)
, fruitsTotal(0)
, weightsTotal(0)
, height(0)
, id(idS)
, garden(mother)
, next(nextS)
, prev (prevS)
, first(NULL)
, last(NULL)
{
    if (next != NULL) {
        next->setPrev(this);
    } else {
        garden->setLast(this);
    }

    if (prev != NULL) {
        prev->setNext(this);
    } else {
        garden->setFirst(this);
    }

    // garden->treeAmountAdd(1, false);
}

TREE_CLASS::TREE_CLASS(const TREE_CLASS& copy, TREE_CLASS* nextS, TREE_CLASS* prevS, unsigned int idS, GARDEN_CLASS* gardenS) :
branchesTotal(0)
, fruitsTotal(0)
, weightsTotal(0)
{

    id = idS;
    height = copy.height;
    next = nextS;
    prev = prevS;
    garden = gardenS;

    if (next != NULL) {
        next->setPrev(this);
    } else {
        if (garden != NULL)
            garden->setLast(this);
    }

    if (prev != NULL) {
        prev->setNext(this);
    } else {
        if (garden != NULL)
            garden->setFirst(this);
    }

    first = NULL;
    last = NULL;

    //copy branches
    if (copy.branchesTotal > 0) {
        BRANCH_CLASS* tempCpy = copy.first;
//        if (tempCpy != NULL) {
//            new BRANCH_CLASS(*tempCpy, NULL, NULL, this);
//            tempCpy = tempCpy->getNext();

            while (tempCpy != NULL) {
                new BRANCH_CLASS(*tempCpy, NULL, last, this);
                tempCpy = tempCpy->getNext();
            }
//        }

    }

    if(garden != NULL)
        garden->treeAmountAdd(1,false);
}

TREE_CLASS::~TREE_CLASS()
{
    // usuwa z listy
    if (next != NULL) {
        next->setPrev(prev);
    } else {
        if (garden != NULL)
            garden->setLast(prev);
    }

    if (prev != NULL) {
        prev->setNext(next);
    } else {
        if(garden != NULL)
            garden->setFirst(next);
    }

    // usuwa branche
    BRANCH_CLASS* temp = first;
    BRANCH_CLASS* tempDel;
    while (temp != NULL) {
        tempDel = temp;
        temp = temp->getNext();
        delete tempDel;
    }

    if(garden != NULL)
        garden->treeAmountAdd(1, true);
}

unsigned int TREE_CLASS::getBranchesTotal()
{
    return branchesTotal;
}

unsigned int TREE_CLASS::getFruitsTotal()
{
    return fruitsTotal;
}

unsigned int TREE_CLASS::getWeightsTotal()
{
    return weightsTotal;
}

unsigned int TREE_CLASS::getNumber()
{
    return id;
}

unsigned int TREE_CLASS::getHeight()
{
    return height;
}

void TREE_CLASS::growthTree()
{
    height++;
    BRANCH_CLASS* temp = first;

    while (temp != NULL) {
        temp->growthBranch();
        temp = temp->getNext();
    }

    if (height % 3 == 0) {
        new BRANCH_CLASS(this, NULL, last, height);
    }

}

void TREE_CLASS::fadeTree()
{
    if (height == 0) {
        return;
    }

    height--;
    BRANCH_CLASS* temp = first;

    while (temp != NULL) {
        if (temp->getHeight() > height) {
            BRANCH_CLASS* tempDel = temp;
            temp = temp->getNext();
            delete tempDel;
        } else {
            temp->fadeBranch();
            temp = temp->getNext();
        }
    }
}

void TREE_CLASS::harvestTree(unsigned int weightLim)
{
    BRANCH_CLASS* temp = first;
    while (temp != NULL) {
        temp->harvestBranch(weightLim);
        temp = temp->getNext();
    }
}

void TREE_CLASS::cutTree(unsigned int hLim)
{
    if (hLim >= height)
        return;

    height = hLim;

    BRANCH_CLASS* temp = first;
    while (temp != NULL) {
        if (temp->getHeight() > height) {
            BRANCH_CLASS* tempDel = temp;
            if (temp == first) {
                first = first->getNext();
            }

            temp = temp->getNext();
            delete tempDel;
        } else {
            temp = temp->getNext();
        }
    }
}

void TREE_CLASS::cloneBranch(BRANCH_CLASS* copy)
{
    if (copy == NULL) return;

    BRANCH_CLASS* temp = first;
    while (temp != NULL) {
        if (temp->getLength() == 0) {
            new BRANCH_CLASS(*copy, temp, this);
            return;
        }
        temp = temp->getNext();
    }
}

GARDEN_CLASS* TREE_CLASS::getGardenPointer()
{
    return garden;
}

BRANCH_CLASS* TREE_CLASS::getBranchPointer(unsigned int h)
{
    if (h > height) return NULL;

    BRANCH_CLASS* temp = first;

    while (temp != NULL) {
        if (temp->getHeight() == h) {
            break;
        }
        temp = temp->getNext();
    }

    return temp;
}

// METODY DODATKOWE
void TREE_CLASS::totalWeightAdd(unsigned int add, bool isNeg)
{
    if (isNeg) {
        weightsTotal -= add;
    } else {
        weightsTotal += add;
    }
    if (garden != NULL)
        garden->totalWeightAdd(add, isNeg);
}

void TREE_CLASS::fruitAmountAdd(unsigned int add, bool isNeg)
{
    if (isNeg) {
        fruitsTotal -= add;
    } else {
        fruitsTotal += add;
    }
    if(garden != NULL)
        garden->fruitAmountAdd(add, isNeg);
}

void TREE_CLASS::branchAmountAdd(unsigned int add, bool isNeg)
{
    if (isNeg) {
        branchesTotal -= add;
    } else {
        branchesTotal += add;
    }
    if (garden != NULL)
        garden->branchAmountAdd(add, isNeg);
}

void TREE_CLASS::setNext(TREE_CLASS* nextS)
{
    next = nextS;
}

void TREE_CLASS::setPrev(TREE_CLASS* prevS)
{
    prev = prevS;
}

TREE_CLASS* TREE_CLASS::getNext() {
    return next;
}

TREE_CLASS* TREE_CLASS::getPrev() {
    return prev;
}


void TREE_CLASS::displayMoj() {
    GARDEN_CLASS* garden = (*this).getGardenPointer();
    BRANCH_CLASS* branch;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int quantity = (*this).getBranchesTotal();

    printf("    Tree number %u:\n", (*this).getNumber());
    printf("        Height of a Tree: %u\n", (*this).getHeight());
    printf("        Number of Branches: %u\n", quantity);
    printf("        Number of Fruits: %u\n", (*this).getFruitsTotal());
    printf("        Total Weight: %u\n", (*this).getWeightsTotal());
    printf("        All Branches:\n");

    while (i < quantity) {
        branch = (*this).getBranchPointer(3 * j);
        if (branch != NULL) {
            (*branch).displayMoj();
            i += 1;
        }
        j += 1;
    }
    printf("        Successful Display all of %u Branches\n", quantity);
}

BRANCH_CLASS* TREE_CLASS::getFirst() {
    return first;
}

void TREE_CLASS::setFirst(BRANCH_CLASS* firstS) {
    first = firstS;
}

BRANCH_CLASS* TREE_CLASS::getLast() {
    return last;
}

void TREE_CLASS::setLast(BRANCH_CLASS* lastS) {
    last = lastS;
}
