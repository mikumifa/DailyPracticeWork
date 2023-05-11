#include "shoppinglist.hpp"
#include <vector>
#include <sstream>
#include "iostream"
#include "fstream"
std::vector<Item> LoadItemsToVector(std::string fileName) {
    std::vector<Item> items;
    std::ifstream input;
    input.open(fileName,std::ios::in);
    if(!input.is_open())
        throw std::exception();
    std::string buffer;
    while (getline(input,buffer)) {
        std::stringstream ss(buffer);
        Item temp;
        ss>>temp.itemName>>temp.quantity>>temp.price;
        if(ss.fail())
            throw std::exception();
        items.push_back(temp);
    }
    return items;
}
