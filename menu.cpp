#include "bili.h"

int OutputMnue()
{
    cout<<"=======菜单========"<<endl;
    cout<<"1.添加卡"<<endl;//
    cout<<"2.查询卡"<<endl;//
    cout<<"3.上机"<<endl;
    cout<<"4.下机"<<endl;
    cout<<"5.充值"<<endl;//
    cout<<"6.退费"<<endl;//
    cout<<"7.查询统计"<<endl;
    cout<<"8.注销卡"<<endl;//
    cout<<"0.退出"<<endl;//
    cout<<"选择编号"<<endl;
    int in;
    cin>>in;
    return in;
}

