// Filip Jarzyna
int Cardinality(int conv1);

bool EqualCheckGreater(int conv1, int conv2, int count)
{
    // setBit 100000....00
    if (count < 32) {
        int setBit = 1;
        setBit <<= 31;
        // check every bit from left to right
        int check1 = (conv1 & setBit);
        int check2 = (conv2 & setBit);

        if (check1 == setBit) {
            if (check2 != setBit) {
                return true; // conv1 > conv2
            }
        } else {
            if (check2 == setBit) {
                return false; // conv1 < conv2
            }
        }
        return EqualCheckGreater((conv1 << 1), (conv2 << 1), count + 1);
    }
    return false;
}

bool LessThen(int conv1, int conv2)
{
    if (conv1 == conv2)
        return false;

    int temp1 = Cardinality(conv1);
    int temp2 = Cardinality(conv2);

    if (temp1 < temp2) {
        return true;
    } else if (temp1 == temp2) {
        int count = 0;
        return !(EqualCheckGreater(conv1, conv2, count));
    }
    return false;
}

bool GreatThen(int conv1, int conv2)
{
    if (conv1 == conv2)
        return false;

    int temp1 = Cardinality(conv1);
    int temp2 = Cardinality(conv2);

    if (temp1 > temp2) {
        return true;
    } else if (temp1 == temp2) {
        int count = 0;
        return EqualCheckGreater(conv1, conv2, count);
    }
    return false;
}

bool LessEqual(int conv1, int conv2)
{
    return !(GreatThen(conv1, conv2));
}

bool GreatEqual(int conv1, int conv2)
{
    return !(LessThen(conv1, conv2));
}