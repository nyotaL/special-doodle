#include <iostream>
#include <vector>
#include <unordered_map>

const int ALPHABET_SIZE = 26;

struct Vertex {
    std::vector<Vertex *> edges;
    Vertex *parent;
    int symb; // цифра в этой вершине
    bool leaf;
    std::vector<int> strings; //íîìåðà ñòðîê, çà êîòîðûå îòâå÷àåò òåðìèíàë
};

class Bor {
private:
    Vertex root;
    std::vector<std::string> patterns;
public:
    explicit Bor();
    void Add_string(const std::string &s, int pos);
    Vertex *FindVertex(const std::string &tel);
};

Vertex *move(Vertex *u, int c); // шагаем по бору

class TelephoneBook {
private:
    Bor bor;
    std::unordered_map<std::string, std::string> nameByNum; // мап поиска номера по имени
    std::unordered_map<std::string, std::string> numByName; // мап поиска имени по номеру
    std::vector<std::string> names; // массив имен
public:
    explicit TelephoneBook();
    void GetName(std::string &tel); // найти фамилию по номеру
    void GetNum(std::string &name); // найти номер по фамилии
    void FittingNames(std::string &tel);
    void AddPair(std::string &tel, std::string &name);
};

int main() {
    TelephoneBook t;
    std::string field = "";
    std::cout << "Type commands\n - add\n - find_num\n - find_name\n - find_possible_names\n - finish\n";
    while (field != "finish") {
        std::cin >> field;
        if (field == "add") {
            std::cout << "type name" << '\n';
            std::string name;
            std::cin >> name;
            std::cout << "type phone number" << '\n';
            std::string tel;
            std::cin >> tel;
            t.AddPair(tel, name);
            std::cout << "done\n";
        } else if (field == "find_num") {
            std::cout << "type name\n";
            std::string name;
            std::cin >> name;
            t.GetNum(name);
        } else if (field == "find_name") {
            std::cout << "type phone number\n";
            std::string num;
            std::cin >> num;
            t.GetName(num);
        } else if (field == "find_possible_names") {
            std::cout << "type the beginning of a phone number\n";
            std::string num;
            std::cin >> num;
            t.FittingNames(num);
        } else if (field != "finish") {
            std::cout << "wrong command\n";
        }
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////
Bor::Bor() {
    std::vector<Vertex *> rootedges(ALPHABET_SIZE, nullptr);
    std::vector<Vertex *> roottravels(ALPHABET_SIZE, nullptr);
    std::vector<int> strings;
    std::vector<std::string> patterns;
    root.parent = nullptr;
    root.symb = -1;
    root.edges = rootedges;
    root.leaf = false;
    root.strings = strings;
}

void Bor::Add_string(const std::string &s, int pos) {
    Vertex *cur = &(this->root);
    for (int i = 0; i < s.length(); i++) {
        const int symb = s[i] - '0';
        if ((cur->edges)[symb] == nullptr) {
            auto *nova = new Vertex();
            std::vector<Vertex *> edges(ALPHABET_SIZE, nullptr);
            std::vector<Vertex *> travels(ALPHABET_SIZE, nullptr);
            std::vector<int> strings;
            nova->strings = strings;
            nova->edges = edges;
            nova->parent = cur;
            nova->symb = symb;
            (nova->strings).push_back(pos); // запишем индекс имени, чей номер тут прошел
            if (i == s.length() - 1) {
                nova->leaf = true;
            } else {
                nova->leaf = false;
            }
            (cur->edges)[symb] = nova;
            cur = nova;
        } else {
            cur = (cur->edges)[symb];
            (cur->strings).push_back(pos); // запишем индекс имени, чей номер тут прошел
            if (i == s.length() - 1) {
                cur->leaf = true;
            }
        }
    }
}

Vertex * Bor::FindVertex(const std::string &tel) {
    Vertex *cur = &(this->root);
    for (int i = 0; i < tel.size(); ++i) {
        const int symb = tel[i] - '0';
        cur = move(cur, symb);
        if (cur == nullptr) {
            return nullptr;
        }
    }
    return cur;
}

Vertex *move(Vertex *u, int c) {
    if ((u->edges)[c] == nullptr) {
        return nullptr;
    } else {
        return (u->edges)[c];
    }
}

void TelephoneBook::GetName(std::string &tel) {
    int q = (this->nameByNum).count(tel);
    if (q != 0) {
        std::cout << (this->nameByNum)[tel] << '\n';
    } else {
        std::cout << "no such number\n";
    }
}

void TelephoneBook::GetNum(std::string &name) {
    int q = (this->numByName).count(name);
    if (q != 0) {
        std::cout << (this->numByName)[name] << '\n';
    } else {
        std::cout << "no such pearson\n";
    }
}

void TelephoneBook::FittingNames(std::string &tel) {
    Vertex *num = (this->bor).FindVertex(tel);
    if (num == nullptr) {
        std::cout << "no such numbers\n";
    } else {
        for (auto i:(num->strings)) {
            std::cout << (this->names)[i] << '\n';
        }
    }
}

TelephoneBook::TelephoneBook() {
    Bor b;
    this->bor = b;
    std::unordered_map<std::string, std::string> a;
    std::unordered_map<std::string, std::string> c;
    this->nameByNum = a;
    this->numByName = c;
    std::vector<std::string> n;
    this->names = n;
}

void TelephoneBook::AddPair(std::string &tel, std::string &name) {
    (this->numByName)[name] = tel;
    (this->nameByNum)[tel] = name;
    (this->names).push_back(name);
    (this->bor).Add_string(tel, (this->names).size() - 1);
}

