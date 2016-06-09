#ifndef KSV_ARGUMENTATION_H
#define KSV_ARGUMENTATION_H

class Argumentation {

private:
    char **args;
    int count;

public:
    Argumentation(int c, const char *a[]);

    ~Argumentation() { }

    bool hasArg(char *find, int &index);
    bool hasArg(char *find);

    void printArgs();

    char *value(char *find);

};

#endif //KSV_ARGUMENTATION_H
