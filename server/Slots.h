#include <pthread.h>

struct Slots{
    int ConnectionDescriptor;
    char Nickname[17];
    struct Slots *left;
    struct Slots *right;
    pthread_t ClientThread;
};

void AppendSlots(struct Slots **slots);