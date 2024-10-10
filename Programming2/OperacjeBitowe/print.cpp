// Filip Jarzyna

void Print2(int conv, char* str, int shift)
{
    if (shift >= 0) {
        int setBit = 1;
        setBit <<= shift;
        if (setBit == (setBit & conv)) {
            setBit = 16;
            if (setBit == (setBit & shift)) {
                *str = '1';
            } else
                *str = '0';

            setBit = 8;
            if (setBit == (setBit & shift)) {
                *(str + 1) = '1';
            } else
                *(str + 1) = '0';

            setBit = 4;
            if (setBit == (setBit & shift)) {
                *(str + 2) = '1';
            } else
                *(str + 2) = '0';

            setBit = 2;
            if (setBit == (setBit & shift)) {
                *(str + 3) = '1';
            } else
                *(str + 3) = '0';

            setBit = 1;
            if (setBit == (setBit & shift)) {
                *(str + 4) = '1';
            } else
                *(str + 4) = '0';

            *(str + 5) = ' ';

            Print2(conv, str + 6, shift - 1);
        } else {
            Print2(conv, str, shift - 1);
        }
    } else {
        *str = '\0';
    }
    
}

void Print(int conv, char* str)
{
    if (conv == 0) {
        *(str) = 'e';
        *(str + 1) = 'm';
        *(str + 2) = 'p';
        *(str + 3) = 't';
        *(str + 4) = 'y';
        *(str + 5) = '\0';
    } else {
        int shift = 31;
        Print2(conv, str, shift);
    }
}