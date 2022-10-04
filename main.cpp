#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>
#include <list>
#include <queue>

std::unordered_map<std::string, std::set<std::string>> edges;


int BFS(std::string nodeStart, std::string nodeEnd)
{  // BFS -  breadth-first search, BFS
   std::queue<std::string > toCheckBasic;
   std::queue<std::pair<std::string, int > > toCheck;

   std::set<std::string> vis; // odwiedzone

    // 0. inicjalizacja
    toCheck.push(make_pair(nodeStart, 0));

    while (!toCheck.empty()) {
        // 1. wez nastepny z kolejki
        auto cur = toCheck.front();
        toCheck.pop();
        // 2. wez jego sasiadow
        auto neighbours = edges[cur.first];
        for (auto it = neighbours.begin(); it != neighbours.end(); ++it) {
            if (!vis.contains(*it))
            { // jesli ten sasiad nie byl jeszcze odwiedzony
                toCheck.push(make_pair(*it, cur.second + 1));
            }
        }
        // 3. czy to jest ten ktorego szukamy?
        if (cur.first == nodeEnd) {
            return cur.second;
        }
        vis.insert(cur.first);
    }

    return -1;
}

std::vector<std::string> BFS(std::string nodeStart, int n)
{  // BFS -  breadth-first search, BFS

    std::vector<std::string> friends;
    std::queue<std::string> toCheckBasic;
    std::queue<std::pair<std::string, int>> toCheck;

    std::set<std::string> vis; // odwiedzone

    // 0. inicjalizacja
    toCheck.push(std::make_pair(nodeStart, 0));

    while (!toCheck.empty()) {
        // 1. wez nastepny z kolejki
        auto cur = toCheck.front();
        toCheck.pop();
        // 2. wez jego sasiadow
        auto neighbours = edges[cur.first];
        for (auto it = neighbours.begin(); it != neighbours.end(); ++it) {
            if (!vis.contains(*it))
            { // jesli ten sasiad nie byl jeszcze odwiedzony
                toCheck.push(make_pair(*it, cur.second + 1));
            }
        }
        // 3. czy to jest ten ktorego szukamy?
        if (cur.second == n && !std::count(friends.begin(), friends.end(), cur.first)) {
            friends.push_back(cur.first);
        }
        vis.insert(cur.first);
    }
    return friends;
}

void show(std::unordered_map<std::string, std::set<std::string> >& mapOfSet) {
   
    for (auto it = mapOfSet.begin();
        it != mapOfSet.end();
        it++) {

        std::cout << it->first << "=>";

        
        std::set<std::string> st = it->second;

      
        for (auto it = st.begin();
            it != st.end(); it++) {
            std::cout << (*it);
        }
        std::cout << '\n';
    }
}

bool ifConnected(std::string a, std::string b) {
    if (a > b) return ifConnected(b, a);
    if (edges[a].count(b)) return true;
    return false;
}
class Person {
public:
    int ID;
    std::string name;
    std::vector<std::string> friends;
    Person(int ID, std::string name, std::vector<std::string> friends) {
        this->ID = ID;
        this->name = name;
        this->friends = friends;
    }
};

void addEdge(Person person) {
    for (int i = 0; i < person.friends.size(); i++) {
        edges[person.name].insert(person.friends[i]);
    }
}
void createGraph(std::vector<Person> people) {
    for (int i = 0; i < people.size(); i++) {
        addEdge(people[i]);
    }
}


int main() {
    std::vector<Person> people;
    int counter = 0;
    std::string givenName;
    std::vector < std::string > row;
    std::string line, word;
    std::fstream file("myFile.csv", std::ios::in);
    if (file.is_open()) {
        while (getline(file, line)) {
            int i = 0;
            counter++;
            row.clear();
            givenName.clear();

            std::stringstream str(line);

            while (getline(str, word, ',')) {
                if (i != 0) {
                    word.erase(0, 1);
                }
                row.push_back(word);
                i++;
            }
            givenName = row[0];
            row.erase(row.begin());
            Person person(counter, givenName, row);
            people.push_back(person);        
        }
        file.close();
    }
    else
        std::cout << "Could not open the file\n";
    createGraph(people); 
    std::cout << BFS("Arden Lucian", "Karleigh Prescott");
    
    
   
	return 0;
}
