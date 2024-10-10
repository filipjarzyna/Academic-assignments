//Filip Jarzyna
void Union (int conv1, int conv2, int* uni) {
    (*uni) = (conv1 | conv2);
}

void Intersection(int conv1, int conv2, int* inter) {
    (*inter) = (conv1 & conv2);
}

void Symmetric(int conv1, int conv2, int* symm) {
    (*symm) = (conv1 ^ conv2);
}

void Difference(int conv1, int conv2, int* diff) {
    (*diff) = (conv1 & (~conv2));
}

void Complement(int conv1, int* comp) {
    (*comp) = (~conv1);
}