//Filip Jarzyna
void Emplace2(char* str, int* converted)
{
    if (*str == ' ') {
        Emplace2((str + 1), converted);
    } else if (*str != 0) {
        int charConversion = 0; // 000...0000
        int setBit = 1; // 000...0001

        if (*str == '1')
            charConversion += 16;
        if (*(str + 1) == '1')
            charConversion += 8;
        if (*(str + 2) == '1')
            charConversion += 4;
        if (*(str + 3) == '1')
            charConversion += 2;
        if (*(str + 4) == '1')
            charConversion += 1;

        setBit <<= charConversion;

        *converted = (*converted | setBit);

        Emplace2(str + 5, converted);
    }
}

void Emplace(char* str, int* converted)
{
    *converted = 0;
    Emplace2(str, converted);
}