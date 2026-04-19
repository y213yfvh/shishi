#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <climits>

using namespace std;

// 哈夫曼树节点
struct Node {
    int data;       // 字符（叶子）或 -1（内部）
    int weight;     // 频率
    Node* left;
    Node* right;
    Node(int d, int w, Node* l, Node* r) : data(d), weight(w), left(l), right(r) {}
};

// Tree 类（与压缩程序一致）
class Tree {
public:
    Node* root;
    Tree(int data, int weight) {
        root = new Node(data, weight, nullptr, nullptr);
    }
    Tree(Node* r) : root(r) {}
};

// 构建哈夫曼树（完全模拟压缩程序中的 forest::buildHuffmanTree）
void buildHuffmanTree(vector<Tree*>& forest) {
    while (forest.size() > 1) {
        // 1. 找到最小节点及其索引
        int minIdx1 = -1;
        int minWeight1 = INT_MAX;
        for (size_t i = 0; i < forest.size(); ++i) {
            int w = forest[i]->root->weight;
            if (w < minWeight1) {
                minWeight1 = w;
                minIdx1 = i;
            }
        }
        Tree* tree1 = forest[minIdx1];
        forest.erase(forest.begin() + minIdx1);

        // 2. 在剩余节点中找次小节点
        int minIdx2 = -1;
        int minWeight2 = INT_MAX;
        for (size_t i = 0; i < forest.size(); ++i) {
            int w = forest[i]->root->weight;
            if (w < minWeight2) {
                minWeight2 = w;
                minIdx2 = i;
            }
        }
        Tree* tree2 = forest[minIdx2];
        forest.erase(forest.begin() + minIdx2);

        // 3. 合并：左子树为 tree1，右子树为 tree2（保持与压缩程序相同的顺序）
        Node* newNode = new Node(-1, tree1->root->weight + tree2->root->weight,
                                  tree1->root, tree2->root);
        Tree* newTree = new Tree(newNode);

        // 4. 删除旧的 Tree 包装（注意：不删除其 root，因为 root 已被合并）
        delete tree1;
        delete tree2;

        // 5. 将新树加入尾部
        forest.push_back(newTree);
    }
}

// 递归释放节点
void deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// 位读取器
class BitReader {
    ifstream& in;
    unsigned char buffer;
    int bitsLeft;
public:
    BitReader(ifstream& is) : in(is), buffer(0), bitsLeft(0) {}

    int readBit() {
        if (bitsLeft == 0) {
            if (!in.get(reinterpret_cast<char&>(buffer))) return -1;
            bitsLeft = 8;
        }
        int bit = (buffer >> 7) & 1;   // 取最高位
        buffer <<= 1;
        bitsLeft--;
        return bit;
    }
};

int main() {
    // 打开压缩文件
    ifstream in("test.huf", ios::binary);
    if (!in) {
        cerr << "Cannot open input file test.huf" << endl;
        return 1;
    }

    // 1. 读取频率表大小
    int tableSize;
    in.read(reinterpret_cast<char*>(&tableSize), sizeof(tableSize));
    if (!in) {
        cerr << "Failed to read tableSize" << endl;
        return 1;
    }
    cout << "Table size: " << tableSize << endl;

    // 2. 读取每个字符及其频率
    map<unsigned char, int> freq;
    unsigned char ch;
    int weight;
    int totalChars = 0;
    for (int i = 0; i < tableSize; ++i) {
        in.read(reinterpret_cast<char*>(&ch), sizeof(ch));
        if (!in) {
            cerr << "Failed to read character at index " << i << endl;
            return 1;
        }
        in.read(reinterpret_cast<char*>(&weight), sizeof(weight));
        if (!in) {
            cerr << "Failed to read weight for character " << (int)ch << endl;
            return 1;
        }
        freq[ch] = weight;
        totalChars += weight;
        cout << "  char: " << (int)ch << " (ASCII " << (int)ch << ") weight: " << weight << endl;
    }
    cout << "Total characters in original file: " << totalChars << endl;

    // 3. 构建森林（按字符升序插入，与压缩程序一致）
    vector<Tree*> forest;
    for (auto& p : freq) {
        forest.push_back(new Tree(p.first, p.second));
    }

    // 4. 构建哈夫曼树
    buildHuffmanTree(forest);

    // 此时森林中只剩一棵树
    if (forest.empty()) {
        cerr << "Forest empty after building tree" << endl;
        return 1;
    }
    Node* root = forest[0]->root;

    // 5. 解码
    ofstream out("test_decoded.txt", ios::binary);
    if (!out) {
        cerr << "Cannot create output file test_decoded.txt" << endl;
        deleteTree(root);
        delete forest[0];
        return 1;
    }

    BitReader bitReader(in);
    Node* current = root;
    int charsDecoded = 0;

    while (charsDecoded < totalChars) {
        int bit = bitReader.readBit();
        if (bit == -1) {
            cerr << "Unexpected EOF after decoding " << charsDecoded << " characters" << endl;
            break;
        }

        if (bit == 0)
            current = current->left;
        else
            current = current->right;

        if (!current) {
            cerr << "Error: Reached null node" << endl;
            break;
        }

        if (!current->left && !current->right) { // 叶子
            out.put(static_cast<char>(current->data));
            charsDecoded++;
            current = root;
        }
    }

    in.close();
    out.close();

    // 释放内存
    deleteTree(root);
    delete forest[0];  // 删除最后一个 Tree 包装

    if (charsDecoded == totalChars) {
        cout << "Decompression completed successfully. Output file: test_decoded.txt" << endl;
    } else {
        cerr << "Decompression incomplete. Decoded " << charsDecoded << " out of " << totalChars << " characters." << endl;
        return 1;
    }
    return 0;
}
