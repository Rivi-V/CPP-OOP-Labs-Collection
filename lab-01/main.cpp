#include <iostream>
#include "include/height.h"

int main()
{
  int UpSpeed, DownSpeed, desiredHeight;
  std::cout << "enter UpSpeed:";
  std::cin  >> UpSpeed;
  std::cout << "enter DownSpeed:";
  std::cin  >> DownSpeed;
  std::cout << "enter desiredHeight:";
  std::cin  >> desiredHeight;


  std::cout << "result: " << height(UpSpeed,DownSpeed,desiredHeight) << std::endl;

  return 0;
}