#include "bili.h"


void addcard()
{
    card anew;
    
    cout << "请输入卡号:" << endl;
    cin >> anew.name;  
    while(anew.name.empty()) {
        cout << "卡号不能为空，请重新输入:" << endl;
        cin >> anew.name;
    }
    while(std::any_of(anew.name.begin(), anew.name.end(), ::isalpha)) {
        cout << "卡号不能包含字母，请重新输入:" << endl;
        cin >> anew.name;
    }
    while(anew.name.length() > 20) {
        cout << "卡号过长，请输入不超过20个字符的卡号:" << endl;
        cin >> anew.name;
    }
    cout << "请输入密码:" << endl;
    cin >> anew.password;
    while(anew.password.empty()) {
        cout << "密码不能为空，请重新输入:" << endl;
        cin >> anew.password;
    }
    while(anew.password.length() > 20) {
        cout << "密码过长，请输入不超过20个字符的密码:" << endl;
        cin >> anew.password;
    }
    
      
    
    cout << "请输入充值金额:" << endl;
    cin >> anew.rest;
    while(anew.rest>=10000)
    {
        cout<<"充值数过大,请输入小于10000的数"<<endl;
        cin>>anew.rest;
    }
    while(anew.rest<0)
    {
        cout<<"充值数不能为负数,请重新输入"<<endl;
        cin>>anew.rest;
    }
    while(cin.fail()) {
        cout << "输入无效，请输入一个数字:" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> anew.rest;
    }
    anew.tstart = time(NULL);
    
    
    // 添加到链表
    addCardToList(anew);
    // 保存到CSV
    saveCardsToCSV();
    
    cout << "账号创建完毕！卡号：" << anew.name << "，余额：" << anew.rest << "元" << endl;
    system("pause");  // 暂停显示结果
}