#include "bili.h"

// 全局链表头指针定义
CardNode* cardListHead = nullptr;

// 从CSV加载卡片到链表
void loadCardsFromCSV() {
    // 先清空链表
    CardNode* current = cardListHead;
    while (current != nullptr) {
        CardNode* temp = current;
        current = current->next;
        delete temp;
    }
    cardListHead = nullptr;

    vector<vector<string>> data = readCSV("card.csv");
    for (size_t i = 1; i < data.size(); ++i) {  // 跳过标题行
        if (data[i].size() >= 10) {
            card newCard;
            newCard.name = data[i][0];
            newCard.password = data[i][1];
            newCard.state = atoi(data[i][2].c_str());
            newCard.tstart = atol(data[i][3].c_str());
            newCard.tend = atol(data[i][4].c_str());
            newCard.tmoney = atof(data[i][5].c_str());
            newCard.tlast = atol(data[i][6].c_str());
            newCard.nuse = atoi(data[i][7].c_str());
            newCard.rest = atof(data[i][8].c_str());
            newCard.del = atoi(data[i][9].c_str());

            addCardToList(newCard);
        }
    }
}

// 保存链表到CSV
void saveCardsToCSV() {
    vector<vector<string>> data;
    // 添加标题行
    data.push_back({"卡号", "密码", "状态", "开卡时间", "截止时间", "累计金额", "最后使用时间", "使用次数", "余额", "删除"});

    CardNode* current = cardListHead;
    while (current != nullptr) {
        vector<string> row;
        row.push_back(current->data.name);
        row.push_back(current->data.password);
        row.push_back(to_string(current->data.state));
        row.push_back(to_string(current->data.tstart));
        row.push_back(to_string(current->data.tend));
        row.push_back(to_string(current->data.tmoney));
        row.push_back(to_string(current->data.tlast));
        row.push_back(to_string(current->data.nuse));
        row.push_back(to_string(current->data.rest));
        row.push_back(to_string(current->data.del));
        data.push_back(row);
        current = current->next;
    }

    writeCSV("card.csv", data);
}

// 添加卡片到链表
void addCardToList(card newCard) {
    CardNode* newNode = new CardNode(newCard);
    if (cardListHead == nullptr) {
        cardListHead = newNode;
    } else {
        CardNode* current = cardListHead;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// 从链表删除卡片
void deleteCardFromList(string cardNumber) {
    if (cardListHead == nullptr) return;

    if (cardListHead->data.name == cardNumber) {
        CardNode* temp = cardListHead;
        cardListHead = cardListHead->next;
        delete temp;
        return;
    }

    CardNode* current = cardListHead;
    while (current->next != nullptr && current->next->data.name != cardNumber) {
        current = current->next;
    }

    if (current->next != nullptr) {
        CardNode* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

// 在链表中查找卡片
CardNode* findCardInList(string cardNumber) {
    CardNode* current = cardListHead;
    while (current != nullptr) {
        if (current->data.name == cardNumber) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}