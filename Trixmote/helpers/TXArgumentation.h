#ifndef TRIX_ARGUMENTATION_H
#define TRIX_ARGUMENTATION_H

class TXArgumentation {

private:
    char **args;
    int count;

public:
    TXArgumentation(int c, const char *a[]);

    ~TXArgumentation() { }

    bool hasArg(char *find, int &index);
    bool hasArg(char *find);

    void printArgs();

    char *value(char *find);

};

#endif //TRIX_ARGUMENTATION_H
