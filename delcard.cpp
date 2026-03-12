#include "bili.h"
#include "opencsv.h"
#include <sstream>

void delcard()
{
    string cardNumber;
    cout << "请输入要注销的卡号: ";
    cin >> cardNumber;

    vector<vector<string>> allData = readCSV("card.csv");

    bool cardFound = false;
    bool success = false;

    for (size_t i = 1; i < allData.size(); ++i)
    {
        if (allData[i].empty())
            continue; // 防止空行导致越界

        if (allData[i][0] == cardNumber)
        {
            cardFound = true;
            // 行长度检查，避免索引越界
            if (allData[i].size() < 10) {
                cerr << "数据格式不正确，无法注销（列数不足）。" << endl;
                break;
            }

            int attempts = 3;
            string password;
            while (attempts > 0)
            {
                cout << "请输入密码: ";
                cin >> password;

                if (allData[i][1] == password)
                {
                    allData[i][2] = "2"; // 将状态设置为已注销
                    allData[i][9] = "1"; // 设置删除标记
                    success = true;
                    break;
                }
                attempts--;
                if (attempts > 0)
                    cout << "密码错误，请重新输入，您还有 " << attempts << " 次机会" << endl;
            }

            if (!success && cardFound)
                cout << "密码验证失败，注销操作取消。" << endl;

            break; // 无论成功与否，退出循环
        }
    }

    if (success)
    {
        writeCSV("card.csv", allData);
        cout << "卡号 " << cardNumber << " 已成功注销。" << endl;
    }
    else if (cardFound)
    {
        cout << "卡号 " << cardNumber << " 未能注销。可能密码错误。" << endl;
    }
    else
    {
        cout << "未找到卡号 " << cardNumber << "。" << endl;
    }

    system("pause"); // 暂停显示结果
}