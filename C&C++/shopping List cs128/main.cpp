#include <iostream>
#include "Shoppinglist.hpp"
int main() {
    std::vector<Item> items=LoadItemsToVector("../data.txt");
    for(const auto& item:items){
        std::cout<<item.itemName<<" "<<item.quantity<<" "<<item.price<<std::endl;
    }
    return 0;
}
