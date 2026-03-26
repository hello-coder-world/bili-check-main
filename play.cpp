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

    CardNode* cardNode = findCardInList(cardNum);
    if (cardNode == nullptr) {
        cout << "未找到卡号 " << cardNum << "。" << endl;
        system("pause");
        return;
    }

    if (cardNode->data.password != password) {
        cout << "密码错误，无法上机。" << endl;
        system("pause");
        return;
    }

    if (cardNode->data.del == 1) {
        cout << "卡号 " << cardNum << " 已注销，无法上机。" << endl;
        system("pause");
        return;
    }

    if (cardNode->data.state == 1) {
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
            cardNode->data.state = 1; // 更新状态为已上机
            cardNode->data.tend = time(NULL) + 12 * 3600; // 设置截止时间为12小时后
            saveCardsToCSV();
            cout << "卡号 " << cardNum << " 包夜上机成功！截止时间: " << ctime(&cardNode->data.tend) << endl;
            system("pause");
            return;
        }
    }

    cardNode->data.state = 1; // 更新状态为已上机
    // 设置截止时间为0，表示非包夜
    cardNode->data.tend = 0;
    saveCardsToCSV();
    cout << "卡号 " << cardNum << " 上机成功！" << endl;
    system("pause");
}

void stop()
{
    cout << "请输入卡号: ";
    string cardNum;
    cin >> cardNum;

    CardNode* cardNode = findCardInList(cardNum);
    if (cardNode == nullptr) {
        cout << "未找到卡号 " << cardNum << "。" << endl;
        system("pause");
        return;
    }

    if (cardNode->data.state != 1) {
        cout << "卡号 " << cardNum << " 未上机，无法下机。" << endl;
        system("pause");
        return;
    }

    cardNode->data.state = 0; // 更新状态为未上机
    cardNode->data.tlast = time(NULL); // 更新最后使用时间
    cardNode->data.nuse++; // 使用次数加1
    cout << "卡号 " << cardNum << " 下机成功！" << endl;

    // 计算网费
    double pay = 0;
    time_t startTime = cardNode->data.tstart;
    time_t endTime = time(NULL);
    int duration = (endTime - startTime) / 3600; // 上机时长，单位为小时，不足一小时按一小时算
    if (duration <= 0) duration = 1; // 最少按一小时收费

    price p; // 创建价格对象
    if (cardNode->data.tend != 0) // 包夜
    {
        pay = p.allday;
    }
    else
    {
        // 根据上机时间段计算费用
        tm* local = localtime(&startTime);
        int hour = local->tm_hour;
        if (hour < 8 || hour >= 20)
        {
            pay = duration * p.allnight;
        }
        else
        {
            pay = duration * p.hour;
        }
    }

    cout << "上机时长: " << duration << "小时，费用: " << pay << "元" << endl;
    cardNode->data.tmoney += pay; // 累计金额增加

    if (cardNode->data.rest > 0) {
        double newBalance = cardNode->data.rest - pay;
        if (newBalance < 0)
        {
            cout << "余额不足，已扣除剩余余额，需补交差价: " << -newBalance << "元" << endl;
            newBalance = 0;
        } // 余额不足时扣到0
        cardNode->data.rest = newBalance;
        cout << "扣除费用后余额: " << newBalance << "元" << endl;
    }

    saveCardsToCSV();
    system("pause");
}