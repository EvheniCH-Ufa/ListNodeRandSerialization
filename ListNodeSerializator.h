#include <iostream>
#include <string>
#include <vector>


struct ListNode
{ // ListNode модифицировать нельзя
    ListNode* prev = nullptr; // указатель на предыдущий элемент или nullptr
    ListNode* next = nullptr;
    ListNode* rand = nullptr; // указатель на произвольный элемент данного списка, либо `nullptr`
    std::string data; // произвольные пользовательские данные
};

using NodeWithRandomPosition = std::pair<ListNode*, int>;

class Serializator
{
public:
    explicit Serializator(const std::string& in_file_name, const std::string& out_file_name);
    ~Serializator();
    ListNode* GetRoot() const;

private:
    NodeWithRandomPosition ParceLine(std::string &line, ListNode* prev_node);

    bool LoadData(const std::string& file_name);
    bool SaveData(const std::string& file_name) const;

    void MakeLinks(const std::vector<NodeWithRandomPosition> links);

    ListNode* head_ = nullptr;
};
