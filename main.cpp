/*======================================================
    > File Name: main.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月17日 星期四 22时26分42秒
 =======================================================*/

#include <iostream>
#include <vector>
#include <string>
#include "fcgi.h"
#include <stdio.h>

int main(int argc,char **argv)
{
  ::FastCgi fc;
  fc.setRequestId(1);

  fc.startConnect();
  fc.sendStartRequestRecord();
  fc.sendParams("SCRIPT_FILENAME","/home/shreck/index.php");
  fc.sendParams("REQUEST_METHOD","GET");
  fc.sendEndRequestRecord();
  fc.readFromPhp();
  return 0;
}
