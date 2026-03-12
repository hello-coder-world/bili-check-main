#include "bili.h"
#include "opencsv.h"

class price
{

public:
    int allday;    //全天价格
    int allnight;  //夜间价格
    int hour;       //每小时价格
    
    price() {
        vector<vector<string>> priceData = readCSV("price.csv");
        if (priceData.size() < 2 || priceData[1].size() < 3) {
            cout << "价格数据不完整，使用默认价格。" << endl;
             allday = 50;
             allnight = 30;
             hour=5;
            return;
        }
        allday = atoi(priceData[1][0].c_str());
        allnight = atoi(priceData[1][1].c_str());
        hour = atoi(priceData[1][2].c_str());
    }
};



void start()
{
    cout << "请输入卡号: ";
    string cardNum;
    cin >> cardNum;
    cout << "请输入密码: ";
    string password;
    cin >> password;
    vector<vector<string>> allData = readCSV("card.csv");

    bool found = false;
    for (size_t i = 1; i < allData.size(); ++i)
    {
        if (allData[i].empty())
            continue;
        if (allData[i][0] == cardNum)
        {
            if (allData[i][1] != password)
            {
                cout << "密码错误，无法上机。" << endl;
                system("pause");
                return;
            }
            if (allData[i].size() < 10)
            {
                cerr << "数据格式不正确，无法上机。" << endl;
                system("pause");
                return;
            }
            if (allData[i][9] == "1")
            {
                cout << "卡号 " << cardNum << " 已注销，无法上机。" << endl;
                system("pause");
                return;
            }
            if (allData[i][2] == "1")
            {
                cout << "卡号 " << cardNum << " 已上机，无法重复上机。" << endl;
                system("pause");
                return;
            }
            // 获取当前时间
            time_t now = time(NULL);
            tm* local = localtime(&now);
            int hour = local->tm_hour;

            if (hour < 8 || hour >= 20)
            {
                cout << "当前时间为夜间，可以选择包夜。" << endl;
                cout << "是否选择包夜？(y/n): ";
                char choice;
                cin >> choice;

                if (choice == 'y' || choice == 'Y')
                {
                    allData[i][2] = "1"; // 更新状态为已上机
                    time_t endTime = time(NULL) + 12 * 3600;
                    allData[i][4] = to_string(endTime); // 设置截止时间为12小时后
                    writeCSV("card.csv", allData);
                    cout << "卡号 " << cardNum << " 包夜上机成功！截止时间: " << ctime(&endTime) << endl;
                    found = true;
                    system("pause");
                    break;
                }
                else
                {
                    allData[i][2] = "1"; // 更新状态为已上机
                    // 设置截止时间为0，表示非包夜
                    allData[i][4] = "0";
                    writeCSV("card.csv", allData);
                    cout << "卡号 " << cardNum << " 上机成功！" << endl;
                    found = true;
                    system("pause");
                    break;
                }
            }
            else
            {
                // 白天上机
                allData[i][2] = "1";
                allData[i][4] = "0";
                writeCSV("card.csv", allData);
                cout << "卡号 " << cardNum << " 上机成功！" << endl;
                found = true;
                break;
            }
        }
        
    }
    if (!found)
    {
        cout << "未找到卡号 " << cardNum << "。" << endl;
        system("pause");
    }
}

void stop()
{
    cout << "请输入卡号: ";
    string cardNum;
    cin >> cardNum;
    vector<vector<string>> allData = readCSV("card.csv");

    bool found = false;
    for (size_t i = 1; i < allData.size(); ++i)
    {
        if (allData[i].empty())
            continue;
        if (allData[i][0] == cardNum)
        {
            if (allData[i][2] != "1")
            {
                cout << "卡号 " << cardNum << " 未上机，无法下机。" << endl;
                system("pause");
                return;
            }
            allData[i][2] = "0"; // 更新状态为未上机
            writeCSV("card.csv", allData);
            cout << "卡号 " << cardNum << " 下机成功！" << endl;
            found = true;
            //计算网费
            int pay = 0;
            time_t startTime = atoi(allData[i][3].c_str());
            time_t endTime = time(NULL);
            int duration = (endTime - startTime)/3600 ; // 上机时长，单位为小时，不足一小时按一小时算
            if (duration <= 0) duration = 1; // 最少按一小时收费
            if (allData[i][4] != "0") // 包夜
            {
                pay = price().allday;
            }
            else
            {
                // 根据上机时间段计算费用
                tm* local = localtime(&startTime);
                int hour = local->tm_hour;
                if (hour < 8 || hour >= 20)
                {
                    pay = duration * price().allnight;
                }
                else
                {
                    pay = duration * price().hour;
                }
            }
            cout << "上机时长: " << duration << "小时，费用: " << pay << "元" << endl;
            int currentMoney = atoi(allData[i][5].c_str());
            currentMoney += pay;
            allData[i][5] = to_string(currentMoney);
            if(allData[i][8] != "0") {
                double currentBalance = atof(allData[i][8].c_str());
                double newBalance = currentBalance - pay;
                if (newBalance < 0) 
                {
                    cout << "余额不足，已扣除剩余余额，需补交差价: " << -newBalance << "元" << endl;
                    newBalance = 0;
                } // 余额不足时扣到0
                allData[i][8] = to_string(newBalance);
                cout << "扣除费用后余额: " << newBalance << "元" << endl;

            }
            writeCSV("card.csv", allData);
            system("pause");
            break;
        }
    }
    if (!found)
    {
        cout << "未找到卡号 " << cardNum << "。" << endl;
        system("pause");
    }
}