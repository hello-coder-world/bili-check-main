/*用于统计目前网吧总收入*/
/*同时用于修改价格*/

#include"bili.h"
#include"opencsv.h"

void manage()
{
    cout<<"请输入管理员密码:"<<endl;
    string password;
    cin>>password;
    vector<vector<string>> allData = readCSV("manager.csv");
    if(allData.size() < 1 || allData[0].empty() || allData[0][0] != password) {
        cout << "密码错误，无法进入管理界面。" << endl;
        system("pause");
        return;
    }
    cout << "欢迎进入管理界面！" << endl;
    int i;
    do
    {
        cout << "请选择操作：" << endl;
        cout << "1. 查看/修改价格" << endl;
        cout << "2. 总收入统计" << endl;
        cout << "3. 修改管理员密码" << endl;
        cout << "0. 退出管理界面" << endl;
        cout << "请输入选项: ";
        cin >> i;
        switch(i) {
            case 1:
                pr();
                break;
            case 2:
                tongji();
                break;
            case 3:
                change_password();
                break;
            case 0:
                cout << "退出管理界面。" << endl;
                break;
            default:
                cout << "无效选项，请重新输入。" << endl;
                break;
        }
    } while (i != 0);

    
    
}

void pr()
{
    cout << "当前价格信息：" << endl;
    vector<vector<string>> priceData = readCSV("price.csv");
    if(priceData.size() < 1 || priceData[0].size() < 3) {
        cout << "价格数据不完整。" << endl;
    } else {
        cout << "全天价格: " << priceData[1][0] << "元" << endl;
        cout << "夜间价格: " << priceData[1][1] << "元" << endl;
        cout << "每小时价格: " << priceData[1][2] << "元" << endl;
    }
    cout<<"是否修改价格？(y/n)"<<endl;
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        cout << "请输入新的价格信息（全天价格 夜间价格 每小时价格）: ";
        int allday, allnight, hour;
        cin >> allday >> allnight >> hour;
        // 更新价格数据
        priceData[1][0] = to_string(allday);
        priceData[1][1] = to_string(allnight);
        priceData[1][2] = to_string(hour);
        // 将更新后的数据写回CSV文件
        writeCSV("price.csv", priceData);
        cout<<"价格修改成功！" << endl;
        system("pause");
    }
}
void tongji()
{
    cout << "总收入统计：" << endl;
    vector<vector<string>> cardData = readCSV("card.csv");
    double totalIncome = 0;
    for (size_t i = 1; i < cardData.size(); ++i) {
        if (cardData[i].size() >= 6) {
            totalIncome += atof(cardData[i][5].c_str());
        }
    }
    cout << "当前总收入: " << totalIncome << "元" << endl;
    cout<<"共有 "<<cardData.size()-1<<" 张卡" << endl;
    cout<<"其中未注销的卡有 "<<count_if(cardData.begin()+1, cardData.end(), [](const vector<string>& row){ return row.size() >= 10 && row[9] == "0"; })<<" 张" << endl;
    system("pause");
}

void change_password()
{
    cout << "请输入新的管理员密码: ";
    string newPassword;
    cin >> newPassword;
    vector<vector<string>> managerData = readCSV("manager.csv");
    if (managerData.empty()) {
        managerData.push_back({newPassword});
    } else {
        managerData[0][0] = newPassword;
    }
    writeCSV("manager.csv", managerData);
    cout << "管理员密码修改成功！" << endl;
    system("pause");
}