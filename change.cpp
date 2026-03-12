#include"bili.h"
#include"opencsv.h"

void addmoney()
{
    string cardNumber;
    cout << "请输入要充值的卡号: ";
    cin >> cardNumber;
    cout<<"请输入密码:"<<endl;
    string password;
    cin >> password;
    vector<vector<string>> allData = readCSV("card.csv");

    bool found = false;
    for (size_t i = 1; i < allData.size(); ++i) {
        if (allData[i].empty()) continue;
        if (allData[i][0] == cardNumber) {
            if (allData[i][1] != password) {
                cout << "密码错误，无法充值。" << endl;
                system("pause");
                return;
            }
            if (allData[i].size() < 10) {
                cerr << "数据格式不正确，无法充值。" << endl;
                system("pause");
                return;
            }
            if(allData[i][9] == "1") {
                cout << "卡号 " << cardNumber << " 已注销，无法充值。" << endl;
                system("pause");
                return;
            }
            double currentBalance = atof(allData[i][8].c_str());
            double rechargeAmount;
            cout << "当前余额: " << currentBalance << "元" << endl;
            cout << "请输入充值金额: ";
            cin >> rechargeAmount;
            
            while(rechargeAmount >= 10000) {
                cout << "充值数过大,请输入小于10000的数: ";
                cin >> rechargeAmount;
            }
            
            double newBalance = currentBalance + rechargeAmount;
            allData[i][8] = to_string(newBalance); // 更新余额
            cout << "充值成功！新余额: " << newBalance << "元" << endl;
            found = true;
            break;
            
        }
    }
    if(found) {
        writeCSV("card.csv", allData);
        cout << "卡号 " << cardNumber << " 已成功充值。" << endl;
        system("pause");
    } else {
        cout << "未找到卡号 " << cardNumber << "。" << endl;
        system("pause");
    }
    
}

void payback()// 退费功能
{
    string cardNumber;
    cout << "请输入要退费的卡号: ";
    cin >> cardNumber;

    vector<vector<string>> allData = readCSV("card.csv");

    bool found = false;
    for (size_t i = 1; i < allData.size(); ++i) {
        if (allData[i].empty()) continue;
        if (allData[i][0] == cardNumber) {
            if (allData[i].size() < 10) {
                cerr << "数据格式不正确，无法退费。" << endl;
                system("pause");
                return;
            }
            if (allData[i][9] == "1") {
                cout << "卡号 " << cardNumber << " 已注销，无法退费。" << endl;
                system("pause");
                return;
            }
            double currentBalance = atof(allData[i][8].c_str());
            double refundAmount;
            cout << "当前余额: " << currentBalance << "元" << endl;
            cout << "请输入退费金额: ";
            cin >> refundAmount;

            if (refundAmount <= 0) {
                cout << "退费金额必须大于0。" << endl;
                system("pause");
                return;
            }

            if (refundAmount > currentBalance) {
                cout << "退费金额不能超过当前余额。" << endl;
                system("pause");
                return;
            }

            double newBalance = currentBalance - refundAmount;
            allData[i][8] = to_string(newBalance); // 更新余额
            cout << "退费成功！新余额: " << newBalance << "元" << endl;
            found = true;
            break;
        }
    }

    if (found) {
        writeCSV("card.csv", allData);
        cout << "卡号 " << cardNumber << " 已成功退费。" << endl;
    } else {
        cout << "未找到卡号 " << cardNumber << "。" << endl;
    }

    system("pause");
}

