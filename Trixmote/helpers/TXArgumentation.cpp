#include "TXArgumentation.h"
#include <iostream>
#include <cstring>

using namespace std;

TXArgumentation::TXArgumentation(int c, const char **a) {
    count = c;
    args = (char **) a;
}

bool TXArgumentation::hasArg(char *find, int &index) {
    for (int i = 0; i < count; ++i) {

        if (strcmp(args[i], find) == 0) {
            index = i;
            return true;
        }
    }

    return false;
}

bool TXArgumentation::hasArg(char *find) {
    int index;
    return hasArg(find, index);
}

void TXArgumentation::printArgs() {
    cout << "Arguments: ";

    for (int i = 0; i < count; ++i) {
        cout << args[i] << " ";
    }

    cout << endl;
}

char *TXArgumentation::value(char *find) {
    int index;

    if (hasArg(find, index)) {
        char *vl = args[index + 1];

        if (vl[0] != '-' && vl[1] != '-') {
            return vl;
        }

    }

    return nullptr;
}
