// Filip Jarzyna
/*
*/
void Insert(char* str, int* converted)
{
    if (*str == ' ') {
        Insert((str + 1), converted);
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

        setBit = (setBit << charConversion);

        *converted = (*converted | setBit);

        Insert(str + 5, converted);
    }
}
