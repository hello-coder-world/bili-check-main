#include "bili.h"
#include "opencsv.h"


void displayCardInfo(vector<string>* rowData)
{

    cout << "卡号: " << (*rowData)[0] << endl;
    if((*rowData)[2] == "0")
    cout << "状态: " << "未上机" << endl;
    if((*rowData)[2] == "1")
    cout << "状态: " << "上机中" << endl;
    if((*rowData)[2] == "2")
    cout << "状态: " << "已注销" << endl;
    if((*rowData)[2] == "3")
    cout << "状态: " << "失效" << endl;
    


    time_t startTime = atol((*rowData)[3].c_str());
    if (startTime > 0) {
        char timeStr[100];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&startTime));
        cout << "开卡时间: " << timeStr << endl;
    }
    

    
    cout << "累计金额: " << (*rowData)[5] << "元" << endl;
    
    time_t lastTime = atol((*rowData)[6].c_str());
    if (lastTime > 0) {
        char timeStr[100];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&lastTime));
        cout << "最后使用: " << timeStr << endl;
    }
    
    cout << "使用次数: " << (*rowData)[7] << "次" << endl;
    cout << "卡内余额: " << (*rowData)[8] << "元" << endl;
    
    if ((*rowData)[9] == "1") {
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
    
    
    CsvFile csv("card.csv");
    
    
    int rows = csv.row;
    
    if (rows <= 1) {  
        cout << "没有卡数据！" << endl;
        system("pause");
        return;
    }
    
    switch(choice) {
        case 1: {
            string cardNum;
            cout << "请输入卡号: ";
            cin >> cardNum;
            
            bool found = false;
            for (int i = 1; i < rows; i++) {
                vector<string>* rowData = csv.getRow(i);
                if ((*rowData)[0] == cardNum) {
                    cout << "\n========== 卡信息 ==========" << endl;
                    displayCardInfo(rowData);
                    cout << "=============================" << endl;
                    found = true;
                    delete rowData;
                    break;
                }
                delete rowData;
            }
            
            if (!found) {
                cout << "未找到卡号: " << cardNum << endl;
            }
            break;
        }
        
        case 2: {
            cout << "\n===== 所有卡信息 =====" << endl;
            for (int i = 1; i < rows; i++) {
                vector<string>* rowData = csv.getRow(i);
                cout << "--- 卡 " << (i) << " ---" << endl;
                displayCardInfo(rowData);
                cout << "---------------------" << endl;
                delete rowData;
            }
            break;
        }
        
        case 3: {
            cout << "\n===== 未注销卡 =====" << endl;
            int count = 0;
            for (int i = 1; i < rows; i++) {
                vector<string>* rowData = csv.getRow(i);
                if ((*rowData)[9] == "0") {
                    cout << "--- 卡 " << (i) << " ---" << endl;
                    displayCardInfo(rowData);
                    cout << "---------------------" << endl;
                    count++;
                }
                delete rowData;
            }
            if (count == 0) cout << "没有未注销的卡" << endl;
            else cout << "共 " << count << " 张未注销卡" << endl;
            break;
        }
        
        case 4: {
            cout << "\n===== 已注销卡 =====" << endl;
            int count = 0;
            for (int i = 1; i < rows; i++) {
                vector<string>* rowData = csv.getRow(i);
                if ((*rowData)[9] == "1") {
                    cout << "--- 卡 " << (i) << " ---" << endl;
                    displayCardInfo(rowData);
                    cout << "---------------------" << endl;
                    count++;
                }
                delete rowData;
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
            int count = 0;
            for (int i = 1; i < rows; i++) {
                vector<string>* rowData = csv.getRow(i);
                double balance = atof((*rowData)[8].c_str());
                if (balance >= minBalance && balance <= maxBalance && (*rowData)[9] == "0") {
                    cout << "--- 卡 " << (i) << " ---" << endl;
                    displayCardInfo(rowData);
                    cout << "---------------------" << endl;
                    count++;
                }
                delete rowData;
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