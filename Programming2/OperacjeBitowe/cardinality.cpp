//Filip Jarzyna

void CountCard(int conv1, int* count)
{
    if (conv1 != 0) {
        int temp = 1;
        temp <<= 31;
        if ((conv1 & temp) == temp) {
            (*count)++;
        }
        CountCard((conv1 << 1), count);
    }
}

int Cardinality(int conv1)
{
    int count = 0;
    CountCard(conv1, &count);
    return count;
}