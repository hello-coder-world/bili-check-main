#ifndef HEADER_H
#define HEADER_H

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<windows.h>
#include<ctime>
#include<fstream>
#include<vector>

using namespace std;


int OutputMnue();
void addcard();
void querycard();
void displayCardInfo(vector<string>* rowData);
vector<vector<string>> readCSV(const string& filename);
void writeCSV(const string& filename, const vector<vector<string>>& data);
void delcard();
void addmoney();
void payback();
void start();
void stop();
void manage();
void pr();
void tongji();
void change_password();


class card
{
public:
    string name;        // 卡号
    string password;    // 密码
    int state;          // 状态：0-未上机，1-已上机，2-已注销,3-失效
    time_t tstart;      // 开卡时间
    time_t tend;        // 截止时间
    double tmoney;      // 累计金额
    time_t tlast;       // 最后使用时间
    int nuse;           // 使用次数
    double rest;        // 余额
    int del;            // 删除标记：0-正常，1-已注销
    
    // 构造函数
    card() {
        state = 0;
        tstart = time(NULL);  // 默认当前时间
        tend = 0;
        tmoney = 0;
        tlast = 0;
        nuse = 0;
        rest = 0;
        del = 0;
    }
};




#endif