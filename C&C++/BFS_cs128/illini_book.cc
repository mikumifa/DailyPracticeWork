#include "illini_book.hpp"
#include "utilities.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
// Your code here!
IlliniBook::IlliniBook(const std::string &people_fpath, const std::string &relations_fpath) {
    std::ifstream ifs(people_fpath, std::ios_base::in);
    if(!ifs.is_open()) {
        std::cerr << "File cannot be opened"<<std::endl;
        return;
    }
    std::string buffer;
    while (getline(ifs, buffer)) {
        points.push_back(stoi(buffer));
        adjacency_list[points.back()]=std::vector<Edge>();
    }
    ifs.close();
    ifs.open(relations_fpath, std::ios_base::in);
    while (getline(ifs, buffer)) {
        auto inputs = utilities::Split(buffer, ',');
        for (const auto &input: inputs) {
            auto uin_1 = stoi(inputs[0]);
            auto uin_2 = stoi(inputs[1]);
            auto relationship = inputs[2];
            adjacency_list[uin_1].push_back({uin_2, relationship});
            adjacency_list[uin_2].push_back({uin_1, relationship});
        }
    }
}
IlliniBook::~IlliniBook() = default;
bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
    std::set<int> visited;
    std::queue<int> to_visit;
    to_visit.push(uin_1);
    while (!to_visit.empty()) {
        auto current = to_visit.front();
        to_visit.pop();
        if (current == uin_2) {
            return true;
        }
        if (visited.find(current) != visited.end()) {
            continue;
        }
        visited.insert(current);
        for (const auto &neighbor : adjacency_list.at(current)) {
            to_visit.push(neighbor.to);
        }
    }
    return false;
}
bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const {
    std::set<int> visited;
    std::queue<int> to_visit;
    to_visit.push(uin_1);
    while (!to_visit.empty()) {
        auto current = to_visit.front();
        to_visit.pop();
        if (current == uin_2) {
            return true;
        }
        if (visited.find(current) != visited.end()) {
            continue;
        }
        visited.insert(current);
        for (const auto &neighbor : adjacency_list.at(current)) {
            if(neighbor.relationship!=relationship) {
                continue;
            }
            to_visit.push(neighbor.to);
        }
    }
    return false;
}
int IlliniBook::GetRelated(int uin_1, int uin_2) const {
    if (adjacency_list.find(uin_1) == adjacency_list.end() || adjacency_list.find(uin_2) == adjacency_list.end()) {
        return -1;
    }
    std::queue<int> q;
    std::map<int, int> dist;
    q.push(uin_1);
    dist[uin_1] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const auto &neighbor : adjacency_list.at(u)) {

            int v = neighbor.to;
            if (dist.find(v) == dist.end()) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    if (dist.find(uin_2) != dist.end()) {
        return dist[uin_2];
    } else {
        return -1;
    }
}

int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const {
    if (adjacency_list.find(uin_1) == adjacency_list.end() || adjacency_list.find(uin_2) == adjacency_list.end()) {
        return -1;
    }
    std::queue<int> q;
    std::map<int, int> dist;
    q.push(uin_1);
    dist[uin_1] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const auto &neighbor : adjacency_list.at(u)) {
            int v = neighbor.to;
            if (dist.find(v) == dist.end()) {
                if(neighbor.relationship!=relationship) {
                    continue;
                }
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    if (dist.find(uin_2) != dist.end()) {
        return dist[uin_2];
    } else {
        return -1;
    }
}
std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
    std::vector<int>ans;
    if (adjacency_list.find(uin) == adjacency_list.end() ) {
        return ans;
    }
    std::queue<int> q;
    std::map<int, int> dist;
    q.push(uin);
    dist[uin] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const auto &neighbor : adjacency_list.at(u)) {
            int v = neighbor.to;
            if (dist.find(v) == dist.end()) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    for(auto &d:dist){
        if(d.second==n){
            ans.push_back(d.first);
        }
    }
    return ans;

}
size_t IlliniBook::CountGroups() const {
    std::map<int, bool> visited;
    size_t count = 0;
    for (const auto &u : points) {
        if (!visited[u]) {
            count++;
            visited[u] = true;
            std::queue<int> q;
            q.push(u);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (const auto &neighbor : adjacency_list.at(v)) {
                    int w = neighbor.to;
                    if (!visited[w]) {
                        visited[w] = true;
                        q.push(w);
                    }
                }
            }
        }
    }
    return count;
}
size_t IlliniBook::CountGroups(const std::string &relationship) const {
    std::map<int, bool> visited;
    size_t count = 0;
    for (const auto &u : points) {
        if (!visited[u]) {
            count++;
            visited[u] = true;
            std::queue<int> q;
            q.push(u);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (const auto &neighbor : adjacency_list.at(v)) {
                    if(neighbor.relationship != relationship){
                        continue;
                    }
                    int w = neighbor.to;
                    if (!visited[w]) {
                        visited[w] = true;
                        q.push(w);
                    }
                }
            }
        }
    }
    return count;
}
size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
    std::map<int, bool> visited;
    size_t count = 0;
    for (const auto &u : points) {
        if (!visited[u]) {
            count++;
            visited[u] = true;
            std::queue<int> q;
            q.push(u);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (const auto &neighbor : adjacency_list.at(v)) {
                    for(auto &relationship : relationships) {
                        if(neighbor.relationship == relationship){
                            int w = neighbor.to;
                            if (!visited[w]) {
                                visited[w] = true;
                                q.push(w);
                            }
                            break ;
                        }
                    }

                }
            }
        }
    }
    return count;
}
