//Filip Jarzyna
bool Disjoint(int conv1, int conv2)
{
    return ((conv1 & conv2) == 0);
}

bool Conjunctive(int conv1, int conv2)
{
    return ((conv1 & conv2) != 0);
}