#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class CsvFile
{
private:
    string filePath;

public:
    int row;
    int col;

private:
    vector<string> *readFile()
    {
        ifstream ifs;
        ifs.open(filePath, ios::in);
        vector<string> *v=NULL;
        v = new vector<string>;
        // vector<string> k;
        if (ifs.is_open())
        {
            string buf;
            while (getline(ifs, buf)) // ansi����
            {
                // cout<<buf<<endl;
                stringstream ss;
                ss << buf;
                string buff;
                while (getline(ss, buff, ','))
                {
                    // cout << buff <<endl;
                    v->push_back(buff); //����ָ����ö�����->
                }
            }
        }
        return v;
    }

public:
    CsvFile(string filePath_) : filePath(filePath_)
    {
        ifstream ifs;
        ifs.open(filePath, ios::in);
        if (ifs.is_open())
        {
            string buf;
            row = 0;
            col = 0;
            while (getline(ifs, buf)) // ansi����
            {
                // cout<<buf<<endl;
                if (row == 1) //�Ե�һ��Ϊ׼
                {
                    stringstream ss;
                    ss << buf;
                    string buff;
                    while (getline(ss, buff, ','))
                    {
                        col++;
                    }
                }
                row++;
            }
        }
    }

    vector<string> *getRow(int r)
    {
        vector<string> *vr=NULL;
        vr = new vector<string>;
        vector<string> *v=NULL;
        v = readFile();
        for (int j = 0; j < col; j++)
        {
            vr->push_back((*v)[r * col + j]);
        }
        return vr;
    }

    vector<string> *getCol(int c)
    {
        vector<string> *vc=NULL;
        vc = new vector<string>;
        vector<string> *v=NULL;
        v = readFile();
        for (int i = 0; i < row; i++)
        {
            vc->push_back((*v)[i * col + c]);
        }
        return vc;
    }
    

    ~CsvFile()
    {
         //delete[] v;
    }
};