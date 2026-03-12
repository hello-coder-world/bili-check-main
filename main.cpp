#include "bili.h"

#include "addcard.cpp"
#include "checkcard.cpp"
#include "change.cpp"
#include "delcard.cpp"
#include "menu.cpp"
#include "headers/rw.cpp"
#include"play.cpp"
#include"chaxun.cpp"



int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int i = -1;
    ifstream checkFile("card.csv");
    if (!checkFile.good()) {
        ofstream createFile("card.csv");
        createFile << "卡号,密码,状态,开卡时间,截止时间,累计金额,最后使用时间,使用次数,余额,删除" << endl;
        createFile.close();
    }
    checkFile.close();
    

     ifstream checkManagerFile("manager.csv");
    if (!checkManagerFile.good()) {
        ofstream createManagerFile("manager.csv");
        createManagerFile << "000000" << endl; // 默认管理员密码
        createManagerFile.close();
    }
    checkManagerFile.close();

    ifstream checkPriceFile("price.csv");
    if (!checkPriceFile.good()) {
        ofstream createPriceFile("price.csv");
        createPriceFile << "全天价格,夜间价格,每小时价格" << endl;
        createPriceFile << "50,30,5" << endl; // 默认价格 
    }
    checkPriceFile.close();
    do
    {
        switch (i)
        {
        case -1:
            cout << "欢迎使用网吧管理系统！" << endl;
            break;
        case 1:
            addcard();
            system("cls");  
            break;
        case 2:
            querycard();
            system("cls");
            break;
        case 3:
            start();
            system("cls");
            break;
        case 4:
            stop();
            system("cls");
            break;
        case 5:
            addmoney();
            system("cls");
            break;
        case 6:
            payback();
            system("cls");
            break;
        case 7:
            manage();
            system("cls");
            break;
        case 8:
            delcard();
            system("cls");
            break;
        default:
            cout << "该编号不存在，请输入正确的编号！" << endl;
            system("pause");
            system("cls");
            break;
        }
        i = OutputMnue();

    } while (i != 0);
    cout<<"谢谢您的使用，欢迎下次光临"<<endl;
    return 0;
}