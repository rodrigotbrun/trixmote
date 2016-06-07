#include "KSVArgumentation.h"
#include <iostream>
#include <cstring>

using namespace std;

Argumentation::Argumentation(int c, const char **a) {
    count = c;
    args = (char **) a;
}

bool Argumentation::hasArg(char *find, int &index) {
    for (int i = 0; i < count; ++i) {

        if (strcmp(args[i], find) == 0) {
            index = i;
            return true;
        }
    }

    return false;
}

bool Argumentation::hasArg(char *find) {
    int index;
    return hasArg(find, index);
}

void Argumentation::printArgs() {
    cout << "Arguments: ";

    for (int i = 0; i < count; ++i) {
        cout << args[i] << " ";
    }

    cout << endl;
}

char *Argumentation::value(char *find) {
    int index;

    if (hasArg(find, index)) {
        char *vl = args[index + 1];

        if (vl[0] != '-' && vl[1] != '-') {
            return vl;
        }

    }

    return nullptr;
}
