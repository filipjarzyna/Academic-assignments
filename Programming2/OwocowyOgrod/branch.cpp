// Filip Jarzyna
#include "branch.hpp"
#include "fruit.hpp"
#include "tree.hpp"
#include <cstdio>

BRANCH_CLASS::BRANCH_CLASS(const BRANCH_CLASS& copy) {
    lenght = copy.lenght;
    height = 0;
    fruitsTotal = 0;
    weightsTotal = 0;
    first = NULL;
    last = NULL;
    next = NULL;
    prev = NULL;
    tree = NULL;

    if (copy.fruitsTotal > 0) {
        FRUIT_CLASS* tempCpy = copy.first;
        while (tempCpy != NULL) {
            new FRUIT_CLASS(*tempCpy, NULL, last, this);
            tempCpy = tempCpy->getNext();
        }
    }

}

BRANCH_CLASS::BRANCH_CLASS(TREE_CLASS* treeSet, BRANCH_CLASS* nextSet, BRANCH_CLASS* prevSet, unsigned int h)
        : last(NULL)
        , lenght(0)
        , first(NULL)
        , weightsTotal(0)
        , fruitsTotal(0)
{
    tree = treeSet;
    height = h;
    next = nextSet;
    prev = prevSet;
    if (prev != NULL) {
        prev->setNext(this);
    } else {
        if (tree != NULL)
            tree->setFirst(this);
    }

    if (next != NULL) {
        next->setPrev(this);
    } else {
        if (tree != NULL)
            tree->setLast(this);
    }


    tree->branchAmountAdd(1, false);
}

BRANCH_CLASS::BRANCH_CLASS() {
    lenght = 0;
    height = 0;
    fruitsTotal = 0;
    weightsTotal = 0;
    first = NULL;
    last = NULL;
    next = NULL;
    prev = NULL;
    tree = NULL;
}

BRANCH_CLASS::~BRANCH_CLASS()
{

    // usuwa z listy
    if (next != NULL) {
        next->prev = prev;
    } else {
        if (tree != NULL)
            tree->setLast(prev);
    }

    if (prev != NULL) {
        prev->next = next;
    } else {
        if (tree != NULL)
            tree->setFirst(next);
    }


    // usuwa owoce
    FRUIT_CLASS* temp = first;
    FRUIT_CLASS* tempDel;
    while (temp != NULL) {
        tempDel = temp;
        temp = temp->getNext();
        delete tempDel;
    }
    if (tree != NULL)
        tree->branchAmountAdd(1, true);
}

// DO KOPIOWANIA (NP JAK DRZEWO KOPIUJE I W LOOPIE GALEZIE)

BRANCH_CLASS::BRANCH_CLASS(const BRANCH_CLASS& copy, BRANCH_CLASS* nextS, BRANCH_CLASS* prevS, TREE_CLASS* treeS) {
    lenght = copy.lenght;
    height = copy.height;
    weightsTotal = 0;
    fruitsTotal = 0;
    tree = treeS;
    next = nextS;
    prev = prevS;

    if (next != NULL) {
        next->setPrev(this);
    } else {
        if (tree !=NULL){
            tree->setLast(this);
        }
    }
    if (prev != NULL) {
        prev->setNext(this);
    } else {
        if(tree != NULL)
            tree->setFirst(this);
    }

    first = NULL;
    prev = NULL;
    if (copy.fruitsTotal > 0) {
        FRUIT_CLASS* tempCpy = copy.first;

        while (tempCpy != NULL) {
            new FRUIT_CLASS(*tempCpy, NULL, last, this);
            tempCpy = tempCpy->getNext();
        }
    }

    if (tree != NULL)
        tree->branchAmountAdd(1,false);
}

// DO SWAPA
BRANCH_CLASS::BRANCH_CLASS(const BRANCH_CLASS& copy, BRANCH_CLASS* swaped, TREE_CLASS* treeS)
{
    lenght = copy.lenght;
    weightsTotal = 0;
    fruitsTotal = 0;
    height = swaped->getHeight();
    tree = treeS;
    next = swaped->getNext();
    prev = swaped->getPrev();
    first = NULL;
    delete swaped;
    if (prev != NULL) {
        prev->setNext(this);
    } else {
        tree->setFirst(this);
    }

    if (next != NULL) {
        next->setPrev(this);
    } else {
        tree->setLast(this);
    }

    if (copy.fruitsTotal > 0) {
        FRUIT_CLASS* tempCpy = copy.first;
        if (tempCpy != NULL) {
            new FRUIT_CLASS(*tempCpy, NULL, NULL, this);
            tempCpy = tempCpy->getNext();
        }
        FRUIT_CLASS* prevOne = first;

        while (tempCpy != NULL) {
            new FRUIT_CLASS(*tempCpy, NULL, prevOne, this);

            prevOne = prevOne->getNext();
            tempCpy = tempCpy->getNext();
        }

        last = prevOne;
    }
    tree->branchAmountAdd(1,false);
}

unsigned int BRANCH_CLASS::getFruitsTotal()
{
    return fruitsTotal;
}

unsigned int BRANCH_CLASS::getWeightsTotal()
{
    return weightsTotal;
}

unsigned int BRANCH_CLASS::getHeight()
{
    return height;
}

unsigned int BRANCH_CLASS::getLength()
{
    return lenght;
}

void BRANCH_CLASS::growthBranch()
{
    lenght++;
    FRUIT_CLASS* temp = first;
    while (temp != NULL) {
        temp->growthFruit();
        temp = temp->getNext();
    }

    if (lenght % 2 == 0) {
        new FRUIT_CLASS(lenght, this, NULL, last);
    }
}

void BRANCH_CLASS::fadeBranch()
{
    if (lenght == 0) {
        return;
    }
    lenght--;
    FRUIT_CLASS* temp = first;
    while (temp != NULL) {
        if (temp->getLength() > lenght) {
            FRUIT_CLASS* tempDel = temp;
            temp = temp->getNext();
            if(tempDel == last) {
                last = last->getPrev();
            }
            if (tempDel == first) {
                first = first->getNext();
            }
            delete tempDel;
        } else {
            temp->fadeFruit();
            temp = temp->getNext();
        }
    }
}

void BRANCH_CLASS::harvestBranch(unsigned int weightLim)
{
    unsigned int oldWeight = weightsTotal;
    FRUIT_CLASS* temp = first;
    while (temp != NULL) {
        if (temp->getWeight() >= weightLim) {
            temp->pluckFruit();
        }

        temp = temp->getNext();
    }
}

void BRANCH_CLASS::cutBranch(unsigned int newLen)
{
    if (newLen >= lenght) {
        return;
    }

    lenght = newLen;

    FRUIT_CLASS* temp = first;
    while (temp != NULL) {
        if (temp->getLength() > lenght) {
            // usuwa owoce rosnace dalej niz nowy len
            FRUIT_CLASS* tempDel = temp;
            temp = temp->getNext();
            delete tempDel;
        } else {
            temp = temp->getNext();
        }
    }
}

FRUIT_CLASS* BRANCH_CLASS::getFruitPointer(unsigned int len)
{
    if (len > lenght) { //? na 0 len nie ma owocu
        return NULL;
    }

    FRUIT_CLASS* temp = first;
    while (temp != NULL) {
        if (temp->getLength() == len) {
            return temp;
        }
        temp = temp->getNext();
    }

    return NULL;
}

TREE_CLASS* BRANCH_CLASS::getTreePointer()
{
    return tree;
}

// DODATKOWE METODY

void BRANCH_CLASS::totalWeightAdd(unsigned int add, bool isNeg)
{
    if (isNeg) {
        weightsTotal -= add;
    } else {
        weightsTotal += add;
    }
    if (tree != NULL)
        tree->totalWeightAdd(add, isNeg);
}

void BRANCH_CLASS::fruitAmountAdd(unsigned int add, bool isNeg)
{
    if (isNeg) {
        fruitsTotal -= add;
    } else {
        fruitsTotal += add;
    }

    if(tree != NULL)
        tree->fruitAmountAdd(add, isNeg);
}

BRANCH_CLASS* BRANCH_CLASS::getNext()
{
    return next;
}

BRANCH_CLASS* BRANCH_CLASS::getPrev()
{
    return prev;
}

void BRANCH_CLASS::setNext(BRANCH_CLASS* nextS)
{
    next = nextS;
}

void BRANCH_CLASS::setPrev(BRANCH_CLASS* prevS)
{
    prev = prevS;
}

void BRANCH_CLASS::displayMoj()
{
    TREE_CLASS* tree = (*this).getTreePointer();
    FRUIT_CLASS* fruit;
    unsigned int i = 0;
    unsigned int j = 2;
    unsigned int quantity = (*this).getFruitsTotal();

    printf("        Branch at the height of %u\n", (*this).getHeight());
    printf("            Length of a Branch: %u\n", (*this).getLength());
    printf("            Number of Fruits: %u\n", quantity);
    printf("            Total Weight: %u\n", (*this).getWeightsTotal());
    printf("            All Fruits:\n");

    while (i < quantity) {
        fruit = (*this).getFruitPointer(j);
        if (fruit != NULL) {
            (*fruit).displayMoj();
            i += 1;
        }
        j += 2;
    }
    printf("            Successful Display all of %u Fruits\n", quantity);
}

void BRANCH_CLASS::setFirst(FRUIT_CLASS* firstS) {
    first = firstS;
}

void BRANCH_CLASS::setLast(FRUIT_CLASS* lastS) {
    last = lastS;
}

FRUIT_CLASS* BRANCH_CLASS::getFirst() {
    return first;
}

FRUIT_CLASS* BRANCH_CLASS::getLast() {
    return last;
}
