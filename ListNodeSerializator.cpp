#include "ListNodeSerializator.h"
#include <fstream>


bool Serializator::LoadData(const std::string &filename)
{
    std::ifstream inFile(filename);
    std::string line;
    if (inFile.is_open())
    {
        ListNode *prev_node(nullptr), *next_node(nullptr);

        while (getline(inFile, line))
        {
            int pos = line.find(';', 0);
            std::string data = line.substr(0, pos);
            if (data.empty())
            {
                continue;
            }
            ListNode* node = new ListNode;
            if(head_ == nullptr)
            {
                head_ = node;
            }

            node->data = std::move(data);





            cout << line << endl;
        }
        inFile.close();
    }

}
