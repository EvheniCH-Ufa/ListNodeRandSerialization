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

bool Serializator::LoadData(const std::string &file_name)
{
    std::ifstream in_file(file_name);
    std::string line;

    if (!in_file.is_open())
    {
        return false;
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

    return true;
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
    if (in_file_name.empty() || out_file_name.empty())
    {
        std::cout << "Imena failov ne dolgny byt' pusty!";
        return;
    }

    if (!LoadData(in_file_name))
    {
        std::cout << "Oshibka otkrytiya vhodnogo faila!";
        return;
    }

    if (!    SaveData(out_file_name))
    {
        std::cout << "Oshibka otkrytiya vyhodnogo faila!";
        return;
    }
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
    std::ofstream out_file(file_name, std::ios::binary);

    if (!out_file.is_open())
    {
        return false;
    }

    auto curr_node = head_;

    while (curr_node != nullptr)
    {
        // честно признаться, с точки зрения логики и восстановления списка
        // я не вижу смысла писать в файл ...->prev и ...->next, а rand это должен быть
        // тот же номер элемента в списке, как и во входном файле
        out_file.write(reinterpret_cast<char*>(curr_node->prev), sizeof(curr_node->prev));
        out_file.write(reinterpret_cast<char*>(curr_node->next), sizeof(curr_node->next));
        out_file.write(reinterpret_cast<char*>(curr_node->rand), sizeof(curr_node->rand));

        // определяем и пишем длину строки для восстановления, чтобы не писать везеде одинаково 1000 символов, но можно и так, заполнив сдачу "нулями"
        size_t length = curr_node->data.size();
        out_file.write(reinterpret_cast<char*>(&length), sizeof(length));
        out_file.write((char*)curr_node->data.c_str(), length);
    }
    out_file.close();
    return true;
}

