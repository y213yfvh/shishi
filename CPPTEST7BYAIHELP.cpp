#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <climits>  // for INT_MAX

using namespace std;

// ==================== 原有类（略作修改） ====================

class Node {
public:
    int data;      // 字符的ASCII值（叶子节点）或内部节点标记（-1）
    int weight;    // 频率
    Node* left;
    Node* right;
    Node(int d, int w, Node* l, Node* r) : data(d), weight(w), left(l), right(r) {}
};

class Tree {
public:
    Node* root;
    Tree(int data, int weight) {
        root = new Node(data, weight, nullptr, nullptr);
    }
    Tree(Node* r) : root(r) {}   // 新增构造函数，用于合并时直接使用已有根节点
    // 不定义析构函数，避免重复释放（root 由外部统一管理）
};

// 链表节点（存储 Tree*）
class lNode {
public:
    Tree* data;
    lNode* next;
    lNode(Tree* dat, lNode* ptr) : data(dat), next(ptr) {}  // 补充构造函数实现
};

// 循环链表（带哨兵头，tail指向最后一个实际节点）
class List {
public:
    lNode* tail;   // 指向最后一个实际节点，其next指向哨兵头
    int length;    // 实际节点个数
    List();
    ~List();
    void appendNode(Tree* data);   // 在尾部追加
    // 以下函数在本程序中未使用，但保留原声明（可忽略）
    void joinNode(int num, Tree* data);
    void deleteNode(int num);
    void changeNode(int num, Tree* data);
    void printNode(int num);
    void printEveryNode();
    int listLength();
    int findData(Tree* dat);
    void connectList(List* list2);
};

List::List() {
    tail = new lNode(nullptr, nullptr);  // 哨兵节点，data 为 nullptr
    tail->next = tail;   // 自环
    length = 0;
}

List::~List() {
    if (tail == nullptr) return;
    lNode* head = tail->next;        // 哨兵头
    lNode* cur = head->next;         // 第一个实际节点
    while (cur != head) {
        lNode* next = cur->next;
        delete cur;
        cur = next;
    }
    delete head;   // 删除哨兵节点
    tail = nullptr;
    length = 0;
}

void List::appendNode(Tree* data) {
    lNode* newNode = new lNode(data, tail->next);  // 新节点的 next 指向哨兵头
    tail->next = newNode;   // 原来的尾节点指向新节点
    tail = newNode;         // 更新尾指针
    length++;
}

// 以下未使用的函数保留空实现或原样，但为了编译通过，简单实现为输出（避免链接错误）
void List::joinNode(int num, Tree* data) { cout << "unused" << endl; }
void List::deleteNode(int num) { cout << "unused" << endl; }
void List::changeNode(int num, Tree* data) { cout << "unused" << endl; }
void List::printNode(int num) { cout << "unused" << endl; }
void List::printEveryNode() { cout << "unused" << endl; }
int List::listLength() { return length; }
int List::findData(Tree* dat) { return -1; }
void List::connectList(List* list2) { cout << "unused" << endl; }

// 森林类，继承自 List
class forest : public List {
public:
    forest() : List() {}   // 正确调用基类构造函数，避免重复分配
    void buildHuffmanTree();
};

// ==================== 新增辅助函数 ====================

// 递归生成哈夫曼编码表
void generateCodes(Node* node, string& current, map<unsigned char, string>& codes) {
    if (!node) return;
    if (!node->left && !node->right) { // 叶子节点
        codes[(unsigned char)node->data] = current;
        return;
    }
    if (node->left) {
        current.push_back('0');
        generateCodes(node->left, current, codes);
        current.pop_back();
    }
    if (node->right) {
        current.push_back('1');
        generateCodes(node->right, current, codes);
        current.pop_back();
    }
}

// 递归释放哈夫曼树节点
void deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// 位写入器（用于将01串写入二进制文件）
class BitWriter {
    ofstream& out;
    unsigned char buffer;   // 当前待写入的字节
    int bitsCount;          // buffer 中已填充的位数（0~7）
public:
    BitWriter(ofstream& os) : out(os), buffer(0), bitsCount(0) {}
    void writeBit(int bit) {
        buffer = (buffer << 1) | (bit & 1);
        bitsCount++;
        if (bitsCount == 8) {
            out.write(reinterpret_cast<char*>(&buffer), 1);
            buffer = 0;
            bitsCount = 0;
        }
    }
    void flush() {
        if (bitsCount > 0) {
            buffer <<= (8 - bitsCount);  // 低位补0
            out.write(reinterpret_cast<char*>(&buffer), 1);
        }
    }
};

// ==================== 核心修改：构建哈夫曼树 ====================

void forest::buildHuffmanTree() {
    while (length > 1) {
        // 1. 找到权重最小的节点及其前驱
        lNode* head = tail->next;          // 哨兵头
        lNode* prev = head;                 // 遍历时的前一个节点
        lNode* cur = head->next;             // 当前节点
        lNode* minPrev = nullptr;            // 最小节点的前驱
        lNode* minNode = nullptr;             // 最小节点
        int minWeight = INT_MAX;

        while (cur != head) {
            if (cur->data->root->weight < minWeight) {
                minWeight = cur->data->root->weight;
                minPrev = prev;
                minNode = cur;
            }
            prev = cur;
            cur = cur->next;
        }

        // 2. 移除最小节点，保存其树
        Tree* tree1 = minNode->data;
        minPrev->next = minNode->next;       // 从链表中删除
        if (minNode == tail) tail = minPrev; // 如果删除的是尾节点，更新tail
        delete minNode;
        length--;

        // 3. 在剩下的节点中找次小节点
        prev = head;
        cur = head->next;
        lNode* min2Prev = nullptr;
        lNode* min2Node = nullptr;
        int min2Weight = INT_MAX;

        while (cur != head) {
            if (cur->data->root->weight < min2Weight) {
                min2Weight = cur->data->root->weight;
                min2Prev = prev;
                min2Node = cur;
            }
            prev = cur;
            cur = cur->next;
        }

        // 4. 移除次小节点，保存其树
        Tree* tree2 = min2Node->data;
        min2Prev->next = min2Node->next;
        if (min2Node == tail) tail = min2Prev;
        delete min2Node;
        length--;

        // 5. 合并两棵树：创建新节点，左右子树分别为 tree1->root 和 tree2->root
        Node* newNode = new Node(-1, tree1->root->weight + tree2->root->weight,
                                  tree1->root, tree2->root);
        Tree* newTree = new Tree(newNode);   // 使用新增的构造函数

        // 6. 删除原来的 Tree 包装（注意：不删除其 root，因为 root 已被合并）
        delete tree1;
        delete tree2;

        // 7. 将新树加入森林（尾部追加）
        appendNode(newTree);
    }
}

// ==================== 原有但未使用的类（可保留） ====================
// 为了完整性，保留但不使用
class to01Node {
public:
    int data;
    char to01[64];
    to01Node* next;
    to01Node(int d, char code[64], to01Node* nxt);
};

to01Node::to01Node(int d, char code[64], to01Node* nxt) {
    data = d;
    next = nxt;
    for (int i = 0; i < 64; i++) to01[i] = code[i];
}

class to01List {
public:
    to01Node* head;
    to01Node* tail;
    to01List() : head(nullptr), tail(nullptr) {}
};

// ==================== main 函数 ====================

int main() {
    // 1. 读取源文件，统计字符频率
    ifstream in("test.txt", ios::binary);
    if (!in) {
        cerr << "Cannot open input file test.txt" << endl;
        return 1;
    }

    map<unsigned char, int> freq;
    char ch;
    while (in.get(ch)) {
        freq[(unsigned char)ch]++;
    }
    in.close();

    if (freq.empty()) {
        cerr << "File is empty" << endl;
        return 1;
    }

    // 2. 构建森林：每个字符创建一个单节点树
    forest f;
    for (auto& p : freq) {
        Tree* t = new Tree(p.first, p.second);  // data 存字符，weight 存频率
        f.appendNode(t);
    }

    // 3. 构建哈夫曼树
    f.buildHuffmanTree();

    // 4. 获取哈夫曼树根节点
    // 森林中只剩一棵树，位于哨兵头之后
    Node* root = f.tail->next->next->data->root;

    // 5. 生成编码表
    map<unsigned char, string> codes;
    string current;
    generateCodes(root, current, codes);

    // 6. 写入压缩文件
    ofstream out("test.huf", ios::binary);
    if (!out) {
        cerr << "Cannot create output file test.huf" << endl;
        return 1;
    }

    // 写入头部：频率表大小
    int tableSize = freq.size();
    out.write(reinterpret_cast<char*>(&tableSize), sizeof(tableSize));
    // 写入每个字符及其频率
    for (auto& p : freq) {
        unsigned char c = p.first;
        int w = p.second;
        out.write(reinterpret_cast<char*>(&c), sizeof(c));
        out.write(reinterpret_cast<char*>(&w), sizeof(w));
    }

    // 重新打开输入文件，进行编码写入
    in.open("test.txt", ios::binary);
    BitWriter bitOut(out);
    while (in.get(ch)) {
        string& code = codes[(unsigned char)ch];
        for (char bit : code) {
            bitOut.writeBit(bit == '1' ? 1 : 0);
        }
    }
    bitOut.flush();

    in.close();
    out.close();

    // 7. 释放内存
    deleteTree(root);
    // forest 的析构函数会自动释放剩余的 lNode 和 Tree 对象，
    // 但 Tree 对象内部的 root 已被 deleteTree 释放，所以不会重复释放。

    cout << "Compression completed. Output file: test.huf" << endl;
    return 0;
}
