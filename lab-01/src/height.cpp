#include "../include/height.h"

int height(int UpSpeed,int DownSpeed,int desiredHeight){
    int result = 0;
    int flag = 0;
    while (result != desiredHeight){
        if (flag % 2 == 0){
            result += UpSpeed;
        }
        else {
            result -= DownSpeed;
        }
        ++flag;
    }
    if (flag % 2 != 0){
        ++flag;
    }
    return flag / 2;
}