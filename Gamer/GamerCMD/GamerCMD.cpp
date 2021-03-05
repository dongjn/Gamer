// GamerCMD.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<Windows.h>
#include"GamerHandler.h"
using namespace seraphim;

void CreateGamerProcess() {

}




int main()
{
    //CreateProcess()
    GamerHandler gh;
    gh.startProcess();
    gh.print();
    gh.inject();
    printf("Begin------\n");
    int code = 0;
    bool run = true;
    for (;run;) {
        std::cin >> code;
        switch (code) {
        case 0:
            run = false;
            break;
        case 1:
            gh.resume();
            break;
        case 2:
            gh.pause();
            break;
        }
    }
    gh.termindate();
    std::cout << "Hello World!\n";
}

