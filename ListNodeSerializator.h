#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>


struct ListNode
{ // ListNode модифицировать нельзя
    ListNode* prev = nullptr; // указатель на предыдущий элемент или nullptr
    ListNode* next = nullptr;
    ListNode* rand = nullptr; // указатель на произвольный элемент данного списка, либо `nullptr`
    std::string data; // произвольные пользовательские данные
};

class Serializator
{
public:
    bool LoadData(const std::string& filename);
    bool SaveData(const std::string& filename) const;
    ListNode* GetHead() const;

private:
    std::unordered_map<int, std::vector<ListNode*>> links_;
    ListNode* head_ = nullptr;
};
