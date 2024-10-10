// Filip Jarzyna
#include "fruit.hpp"
#include "branch.hpp"
#include <cstdio>

FRUIT_CLASS::FRUIT_CLASS() {
    weight = 0;
    length = 0;
    motherBranch = NULL;
    prev = NULL;
    next = NULL;
}

FRUIT_CLASS::FRUIT_CLASS(const FRUIT_CLASS& copy) {
    weight = copy.weight;
    length = copy.length;
    motherBranch = copy.motherBranch;
    next = NULL;
    prev = NULL;
}

FRUIT_CLASS::FRUIT_CLASS(unsigned int len, BRANCH_CLASS* mother, FRUIT_CLASS* nextS, FRUIT_CLASS* prevS)
{
    prev = prevS;
    next = nextS;
    weight = 0;
    length = len;
    motherBranch = mother;

    if (next != NULL) {
        next->setPrev(this);
    } else {
        if (motherBranch != NULL)
            motherBranch->setLast(this);
    }

    if (prev != NULL) {
        prev->setNext(this);
    } else {
        if (motherBranch != NULL)
            motherBranch->setFirst(this);
    }


    motherBranch->fruitAmountAdd(1, false);
}

FRUIT_CLASS::FRUIT_CLASS(const FRUIT_CLASS& copy, FRUIT_CLASS* nextS, FRUIT_CLASS* prevS, BRANCH_CLASS* mother)
{
    weight = copy.weight;
    length = copy.length;
    motherBranch = mother;
    prev = prevS;
    next = nextS;

    if (prev != NULL) {
        prev->setNext(this);
    } else {
        if (motherBranch != NULL)
            motherBranch->setFirst(this);
    }
    if (next != NULL) {
        next->setPrev(this);
    } else {
        if (motherBranch != NULL)
            motherBranch->setLast(this);
    }

    if(motherBranch != NULL) {
        motherBranch->fruitAmountAdd(1, false);
        motherBranch->totalWeightAdd(weight,false);
    }
}

FRUIT_CLASS::~FRUIT_CLASS()
{
    if (next != NULL) {
        next->prev = prev;
    } else {
        if (motherBranch != NULL)
            motherBranch->setLast(prev);
    }

    if (prev != NULL) {
        prev->next = next;
    } else {
        if (motherBranch != NULL)
            motherBranch->setFirst(next);
    }

    if (motherBranch != NULL) {
        motherBranch->fruitAmountAdd(1, true);
        motherBranch->totalWeightAdd(weight, true);
    }
}

unsigned int FRUIT_CLASS::getWeight()
{
    return weight;
}

unsigned int FRUIT_CLASS::getLength()
{
    return length;
}

void FRUIT_CLASS::growthFruit()
{
    weight++;
    if (motherBranch != NULL) {
        motherBranch->totalWeightAdd(1, false);
    }
}

void FRUIT_CLASS::fadeFruit()
{
    if (weight > 0) {
        weight--;
        if (motherBranch != NULL) {
            motherBranch->totalWeightAdd(1, true);
        }
    }
}

void FRUIT_CLASS::pluckFruit()
{
    if (motherBranch != NULL) {
        motherBranch->totalWeightAdd(weight, true);
    }
    weight = 0;
}

BRANCH_CLASS* FRUIT_CLASS::getBranchPointer()
{
    return motherBranch;
}

// DODATKOWE METODY

FRUIT_CLASS* FRUIT_CLASS::getNext()
{
    return next;
}

FRUIT_CLASS* FRUIT_CLASS::getPrev()
{
    return prev;
}

void FRUIT_CLASS::setNext(FRUIT_CLASS* fruit)
{
    next = fruit;
}

void FRUIT_CLASS::setPrev(FRUIT_CLASS *fruit) {
    prev = fruit;
}

void FRUIT_CLASS::displayMoj()
{
    printf("            Fruit at the length of %u\n", (*this).getLength());
    printf("                Weight: %u\n", (*this).getWeight());
}