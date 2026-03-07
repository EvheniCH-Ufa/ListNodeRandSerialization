#include "ListNodeSerializator.h"
#include <fstream>


std::pair<ListNode*, int> Serializator::ParceLine(std::string &line, ListNode *prev_node)
{
    int pos = line.find(';', 0);
    std::string data = line.substr(0, pos);
    if (data.empty())
    {
        return {nullptr, -1};
    }

    ListNode* node = new ListNode;

    node->data = std::move(data);
    node->prev = prev_node;
    if (prev_node != nullptr)
    {
        prev_node->next = node;
    }

    std::string number_node_str = line.substr(pos+1, line.size() - (pos+1));
    int number_rand_node = stoi(number_node_str);

    return std::make_pair(node, number_rand_node);
}

void Serializator::LoadData(const std::string &file_name)
{
    std::ifstream in_file(file_name);
    std::string line;

    if (!in_file.is_open())
    {
        return;
    }

    std::vector<NodeWithRandomPosition> links;

    ListNode* curr_node = head_;

    while (getline(in_file, line))
    {
        auto res_parce = ParceLine(line, curr_node);

        curr_node = res_parce.first;
        if(head_ == nullptr)
        {
            head_ = curr_node;
        }

        links.push_back(res_parce);
    }
    in_file.close();

    MakeLinks(links);
}

void Serializator::MakeLinks(const std::vector<NodeWithRandomPosition> links)
{
    for(const auto [node, rand_pos] : links)
    {
        if (rand_pos < 0)
        {
            continue;
        }

        node->rand = links[rand_pos].first;
    }
}

ListNode *Serializator::GetRoot() const
{
    return head_;
}

Serializator::Serializator(const std::string &in_file_name, const std::string &out_file_name)
{
    LoadData(in_file_name);
    SaveData(out_file_name);
    // запуск load
    // сохранить
}

Serializator::~Serializator()
{
    // удаление списка
    while (head_ != nullptr)
    {
        ListNode* tmp = head_->next;
        delete head_;
        head_ = tmp;
    }
}

bool Serializator::SaveData(const std::string &file_name) const
{
    // сохранить
}

