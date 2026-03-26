#include "bili.h"


void displayCardInfo(const card& c)
{
    cout << "卡号: " << c.name << endl;
    if(c.state == 0)
    cout << "状态: " << "未上机" << endl;
    if(c.state == 1)
    cout << "状态: " << "上机中" << endl;
    if(c.state == 2)
    cout << "状态: " << "已注销" << endl;
    if(c.state == 3)
    cout << "状态: " << "失效" << endl;
    

    if (c.tstart > 0) {
        char timeStr[100];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&c.tstart));
        cout << "开卡时间: " << timeStr << endl;
    }
    

    cout << "累计金额: " << c.tmoney << "元" << endl;
    
    if (c.tlast > 0) {
        char timeStr[100];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&c.tlast));
        cout << "最后使用: " << timeStr << endl;
    }
    
    cout << "使用次数: " << c.nuse << "次" << endl;
    cout << "卡内余额: " << c.rest << "元" << endl;
    
    if (c.del == 1) {
        cout << "【已注销】" << endl;
    }
}

void querycard()
{
    int choice;
    cout << "\n===== 查询方式 =====" << endl;
    cout << "1. 按卡号查询" << endl;
    cout << "2. 查看所有卡" << endl;
    cout << "3. 查看未注销卡" << endl;
    cout << "4. 查看已注销卡" << endl;
    cout << "5. 按余额范围查询" << endl;
    cout << "请选择: ";
    cin >> choice;
    
    if (cardListHead == nullptr) {  
        cout << "没有卡数据！" << endl;
        system("pause");
        return;
    }
    
    switch(choice) {
        case 1: {
            string cardNum;
            cout << "请输入卡号: ";
            cin >> cardNum;
            
            CardNode* current = cardListHead;
            bool found = false;
            while (current != nullptr) {
                if (current->data.name == cardNum) {
                    cout << "\n========== 卡信息 ==========" << endl;
                    displayCardInfo(current->data);
                    cout << "=============================" << endl;
                    found = true;
                    break;
                }
                current = current->next;
            }
            
            if (!found) {
                cout << "未找到卡号: " << cardNum << endl;
            }
            break;
        }
        
        case 2: {
            cout << "\n===== 所有卡信息 =====" << endl;
            CardNode* current = cardListHead;
            int i = 1;
            while (current != nullptr) {
                cout << "--- 卡 " << i << " ---" << endl;
                displayCardInfo(current->data);
                cout << "---------------------" << endl;
                current = current->next;
                i++;
            }
            break;
        }
        
        case 3: {
            cout << "\n===== 未注销卡 =====" << endl;
            CardNode* current = cardListHead;
            int count = 0;
            int i = 1;
            while (current != nullptr) {
                if (current->data.del == 0) {
                    cout << "--- 卡 " << i << " ---" << endl;
                    displayCardInfo(current->data);
                    cout << "---------------------" << endl;
                    count++;
                }
                current = current->next;
                i++;
            }
            if (count == 0) cout << "没有未注销的卡" << endl;
            else cout << "共 " << count << " 张未注销卡" << endl;
            break;
        }
        
        case 4: {
            cout << "\n===== 已注销卡 =====" << endl;
            CardNode* current = cardListHead;
            int count = 0;
            int i = 1;
            while (current != nullptr) {
                if (current->data.del == 1) {
                    cout << "--- 卡 " << i << " ---" << endl;
                    displayCardInfo(current->data);
                    cout << "---------------------" << endl;
                    count++;
                }
                current = current->next;
                i++;
            }
            if (count == 0) cout << "没有已注销的卡" << endl;
            else cout << "共 " << count << " 张已注销卡" << endl;
            break;
        }
        
        case 5: {
            double minBalance, maxBalance;
            cout << "请输入最小余额: ";
            cin >> minBalance;
            cout << "请输入最大余额: ";
            cin >> maxBalance;
            
            cout << "\n===== 余额在 " << minBalance << "-" << maxBalance << " 的卡 =====" << endl;
            CardNode* current = cardListHead;
            int count = 0;
            int i = 1;
            while (current != nullptr) {
                if (current->data.rest >= minBalance && current->data.rest <= maxBalance && current->data.del == 0) {
                    cout << "--- 卡 " << i << " ---" << endl;
                    displayCardInfo(current->data);
                    cout << "---------------------" << endl;
                    count++;
                }
                current = current->next;
                i++;
            }
            if (count == 0) cout << "没有符合条件的卡" << endl;
            else cout << "共 " << count << " 张卡符合条件" << endl;
            break;
        }
        
        default:
            cout << "无效选择" << endl;
    }
    
    system("pause");
}