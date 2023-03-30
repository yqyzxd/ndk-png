//
// Created by wind on 2023/3/30.
//

#ifndef NDK_PNG_RUNNABLE_H
#define NDK_PNG_RUNNABLE_H
class Runnable {
public:
    Runnable(void (*run)(void*),void* param):run(run){}

    void (*run)(void*);
    void* params;
};
#endif //NDK_PNG_RUNNABLE_H
