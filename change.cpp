#include"bili.h"

void addmoney()
{
    string cardNumber;
    cout << "请输入要充值的卡号: ";
    cin >> cardNumber;
    cout<<"请输入密码:"<<endl;
    string password;
    cin >> password;

    CardNode* cardNode = findCardInList(cardNumber);
    if (cardNode == nullptr) {
        cout << "未找到卡号 " << cardNumber << "。" << endl;
        system("pause");
        return;
    }

    if (cardNode->data.password != password) {
        cout << "密码错误，无法充值。" << endl;
        system("pause");
        return;
    }

    if (cardNode->data.del == 1) {
        cout << "卡号 " << cardNumber << " 已注销，无法充值。" << endl;
        system("pause");
        return;
    }

    double currentBalance = cardNode->data.rest;
    double rechargeAmount;
    cout << "当前余额: " << currentBalance << "元" << endl;
    cout << "请输入充值金额: ";
    cin >> rechargeAmount;
    
    while(rechargeAmount >= 10000) {
        cout << "充值数过大,请输入小于10000的数: ";
        cin >> rechargeAmount;
    }
    
    cardNode->data.rest += rechargeAmount;
    cout << "充值成功！新余额: " << cardNode->data.rest << "元" << endl;
    saveCardsToCSV();
    system("pause");
}

void payback()// 退费功能
{
    string cardNumber;
    cout << "请输入要退费的卡号: ";
    cin >> cardNumber;

    CardNode* cardNode = findCardInList(cardNumber);
    if (cardNode == nullptr) {
        cout << "未找到卡号 " << cardNumber << "。" << endl;
        system("pause");
        return;
    }

    if (cardNode->data.del == 1) {
        cout << "卡号 " << cardNumber << " 已注销，无法退费。" << endl;
        system("pause");
        return;
    }

    double currentBalance = cardNode->data.rest;
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

    cardNode->data.rest -= refundAmount;
    cout << "退费成功！新余额: " << cardNode->data.rest << "元" << endl;
    saveCardsToCSV();
    system("pause");
}

