//Filip Jarzyna
bool Inclusion(int conv1, int conv2) {
    return ((conv1 | conv2) == conv2);
}

bool Equality(int conv1, int conv2) {
    return (conv1 == conv2);
}