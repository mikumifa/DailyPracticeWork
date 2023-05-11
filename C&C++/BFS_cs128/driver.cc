#include "illini_book.hpp"
#include <cassert>
int main() {
    IlliniBook book("./example/persons.csv", "./example/relations.csv");
    assert(book.AreRelated(1, 2));
    assert(book.AreRelated(3, 2));
    assert(book.AreRelated(1, 9)==false);
    assert(book.AreRelated(1, 2, "128"));
    assert(book.AreRelated(1, 2, "124")==false);
    assert(book.GetRelated(1, 2) == 1);
    assert(book.GetRelated(3, 2) == 2);
    assert(book.GetRelated(1, 9) == -1);
    assert(book.GetRelated(1, 2, "128") == 1);
    assert(book.GetRelated(1, 2, "124") == -1);
    assert(book.GetRelated(1, 6, "128") == 2);
    assert(book.GetRelated(1, 6, "124") == 1);
    auto a=book.GetSteps(1, 1);
    auto b=book.GetSteps(1, 2);
    assert(book.GetSteps(1, 3).empty());
    assert(book.GetSteps(9, 1).empty());
    assert(book.CountGroups() == 3);
    assert(book.CountGroups("128") == 6);
    assert(book.CountGroups("124") == 6);
    assert(book.CountGroups("173") == 10);
    assert(book.CountGroups(std::vector<std::string>{"128", "127"}) == 6);
    return 0;
}
