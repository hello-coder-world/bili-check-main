#include "bili.h"
#include <sstream>

void delcard()
{
    string cardNumber;
    cout << "请输入要注销的卡号: ";
    cin >> cardNumber;

    CardNode* cardNode = findCardInList(cardNumber);
    if (cardNode == nullptr) {
        cout << "未找到卡号 " << cardNumber << "。" << endl;
        system("pause");
        return;
    }

    int attempts = 3;
    string password;
    bool success = false;
    while (attempts > 0)
    {
        cout << "请输入密码: ";
        cin >> password;

        if (cardNode->data.password == password)
        {
            cardNode->data.state = 2; // 将状态设置为已注销
            cardNode->data.del = 1;   // 设置删除标记
            success = true;
            break;
        }
        attempts--;
        if (attempts > 0)
            cout << "密码错误，请重新输入，您还有 " << attempts << " 次机会" << endl;
    }

    if (success)
    {
        saveCardsToCSV();
        cout << "卡号 " << cardNumber << " 已成功注销。" << endl;
    }
    else
    {
        cout << "密码验证失败，注销操作取消。" << endl;
    }

    system("pause"); // 暂停显示结果
}