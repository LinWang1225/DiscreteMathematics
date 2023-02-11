#include <iostream>
#include<queue>
using namespace std;
const int DefaultSize = 40; // 默认个数
const int DefaultVertices = 30;

template<class T,class E>
class Graphlnk;
//template<class T, class E>
//class Graphlnk;
struct Node { // 并查集结点类
    int data; // 保存数据
    int parent; // 保存父结点
};

class UnionFindSets {
public:
    UnionFindSets(int n); // 构造函数
    ~UnionFindSets(); // 析构函数
    void Union(int a, int b); // 并
    int Find(int x); // 查找x，并返回x的根结点
private:
    Node* s; // 数组
    int currentSize; // 实际存储的个数
};

// 构造函数
UnionFindSets::UnionFindSets(int n) {
    // 初始化
    currentSize = n;
    s = new Node[n];
    for (int i = 0; i < n; i++) {
        s[i].data = i;
        s[i].parent = -1;
    }
}

// 析构函数
UnionFindSets::~UnionFindSets() {
    delete[]s; // 释放空间
}

// 并
void UnionFindSets::Union(int a, int b) {
    int root1, root2;

    root1 = Find(a); // 找到a的根结点
    root2 = Find(b); // 找到b的根结点
    if (root1 == root2 || root1 == -1 || root2 == -1) // 根结点相同,或者其中一个数不在集合中
        return;
    if (s[root1].parent < s[root2].parent) // 说明root1的树高比root2的树高大
        s[root2].parent = root1;
    else if (s[root1].parent == s[root2].parent) { // 树高相等
        s[root2].parent = root1;
        s[root1].parent = s[root1].parent - 1; // root1的树高变高，因为是负数，所以减1
    }
    else { // root2的树高比root1的树高大
        s[root1].parent = root2;
    }
}

// 查找x，并返回x的根结点
int UnionFindSets::Find(int x) {
    int i;

    for (i = 0; i < currentSize && s[i].data != x; i++); // 在数组中查找
    if (i >= currentSize) // 没找到
        return -1;
    for (; s[i].parent >= 0; i = s[i].parent); //  找根结点
    return i;
}
template <class T, class E>
struct MSTEdgeNode { // 最小生成树边结点的类声明
    int head, tail; // 两顶点位置
    E weight; // 边上权值
    MSTEdgeNode() :tail(-1), head(-1), weight(0) {}; // 构造函数
};

template <class T, class E>
bool operator<(const MSTEdgeNode<T, E>& a, const MSTEdgeNode<T, E>& b) {
    if (a.weight > b.weight)
        return true;
    return false;
}

template <class T, class E>
class MinSpanTree { // 最小生成树的类定义
public:
    MinSpanTree(int sz = DefaultSize - 1) { // 构造函数
        maxSize = sz;
        currentSize = 0;
        edgeValue = new MSTEdgeNode<T, E>[sz];
    }
    ~MinSpanTree() { // 析构函数
        delete[]edgeValue; // 释放空间
    }
    bool Insert(MSTEdgeNode<T, E>& item); // 插入
    bool Kruscal(Graphlnk<T, E>& G); // Kruscal算法
    void printMST(Graphlnk<T, E>& G); // 打印最小生成树
private:
    int maxSize, currentSize; // 数组的最大元素个数和当前个数
    MSTEdgeNode<T, E>* edgeValue; // 用边值数组表示树
};

// 插入
template <class T, class E>
bool MinSpanTree<T, E>::Insert(MSTEdgeNode<T, E>& item) {
    if (currentSize == maxSize - 1) {
        cout << "已超出数组的存储范围！" << endl;
        return false;
    }

    edgeValue[currentSize] = item;
    currentSize++;
    return true;
}

// Kruscal算法
template <class T, class E>
bool MinSpanTree<T, E>::Kruscal(Graphlnk<T, E>& G) {
    MSTEdgeNode<T, E> ed; // 边结点辅助单元
    int u, v, count;
    int n = G.numberOfVertices(); // 图的顶点数
    E weight; // 权值
    priority_queue<MSTEdgeNode<T, E>> H; // 最小堆，关键码类型为E
    UnionFindSets F(n); // 并查集


    // 1.把边全部存到最小堆中
    for (u = 0; u < n; u++) {
        for (v = u + 1; v < n; v++) {
            weight = G.getWeight(u, v);
            if (weight > 0 && weight < G.maxWeight) { // 两个顶点存在边
                ed.tail = u;
                ed.head = v;
                ed.weight = weight;
                H.push(ed); // 插入最小堆
            }
        }
    }
    count = 1; // 最小生成树加入边数计数
    while (count < n && H.empty() == false) { // n个顶点，反复执行，取n-1条边;并且最小堆不为空，即还有边时
        ed = H.top(); // 从最小堆中退出具最小权值的边ed
        H.pop();
        u = F.Find(ed.tail); // 取两顶点所在集合的根u和v
        v = F.Find(ed.head);
        if (u != v) { // 不是同一集合，说明不连通
            F.Union(u, v); // 合并，连通它们
            Insert(ed); // 该边存入最小生成树
            count++;
        }
    }
    if (count < n) {
        cout << "不是最小生成树" << endl;
        return false;
    }
    return true; // 是最小生成树
}

// 打印最小生成树
template <class T, class E>
void MinSpanTree<T, E>::printMST(Graphlnk<T, E>& G) {
    int tail, head; // 顶点所在位置
    int total = 0;//总权值
    T e1, e2; // 两顶点
    E weight; //  权值

    for (int i = 0; i < currentSize; i++) {
        tail = edgeValue[i].tail; // 顶点所在位置
        head = edgeValue[i].head;
        e1 = G.getValue(tail); // 根据位置，取顶点对应的值
        e2 = G.getValue(head);
        weight = G.getWeight(tail, head); // 取权值
        cout << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
        total += weight;
    }
    cout << "此方案总造价最小，且最小值为：";
    cout << total << "万元" << endl;
}


template <class T, class E>
struct Edge { // 边结点的定义
    int dest; // 边的另一顶点位置
    E cost; // 表上的权值
    Edge<T, E>* link; // 下一条边链指针
};

template <class T, class E>
struct Vertex { // 顶点的定义
    T data; // 顶点的名字
    Edge<T, E>* adj; // 边链表的头指针
};

template <class T, class E>
class Graphlnk {
public:
    const E maxWeight = 100000; // 代表无穷大的值（=∞）
    Graphlnk(int sz = DefaultVertices); // 构造函数
    ~Graphlnk(); // 析构函数
    void inputGraph(); // 建立邻接表表示的图
    void outputGraph(); // 输出图中的所有顶点和边信息
    T getValue(int i); // 取位置为i的顶点中的值
    E getWeight(int v1, int v2); // 返回边（v1， v2）上的权值
    bool insertVertex(const T& vertex); // 插入顶点
    bool insertEdge(int v1, int v2, E weight); // 插入边
    bool removeVertex(int v); // 删除顶点
    bool removeEdge(int v1, int v2); // 删除边
    int getFirstNeighbor(int v); // 取顶点v的第一个邻接顶点
    int getNextNeighbor(int v, int w); // 取顶点v的邻接顶点w的下一邻接顶点
    int getVertexPos(const T vertex); // 给出顶点vertex在图中的位置
    int numberOfVertices(); // 当前顶点数
private:
    int maxVertices; // 图中最大的顶点数
    int numEdges; // 当前边数
    int numVertices; // 当前顶点数
    Vertex<T, E>* nodeTable; // 顶点表(各边链表的头结点)
};

// 构造函数:建立一个空的邻接表
template <class T, class E>
Graphlnk<T, E>::Graphlnk(int sz) {
    maxVertices = sz;
    numVertices = 0;
    numEdges = 0;
    nodeTable = new Vertex<T, E>[maxVertices]; // 创建顶点表数组
    if (nodeTable == NULL) {
        cerr << "存储空间分配错误！" << endl;
        exit(1);
    }
    for (int i = 0; i < maxVertices; i++)
        nodeTable[i].adj = NULL;
}

// 析构函数
template <class T, class E>
Graphlnk<T, E>::~Graphlnk() {
    // 删除各边链表中的结点
    for (int i = 0; i < numVertices; i++) {
        Edge<T, E>* p = nodeTable[i].adj; // 找到其对应链表的首结点
        while (p != NULL) { // 不断地删除第一个结点
            nodeTable[i].adj = p->link;
            delete p;
            p = nodeTable[i].adj;
        }
    }
    delete[]nodeTable; // 删除顶点表数组
}

// 建立邻接表表示的图
template <class T, class E>
void Graphlnk<T, E>::inputGraph() {
    int n, m; // 存储顶点数和边数
    int i, j, k;
    T e1, e2; // 顶点
    E weight; // 边的权值

    cout << "请输入顶点数和边数：" << endl;
    cin >> n >> m;
    cout << "请输入各顶点：" << endl;
    for (i = 0; i < n; i++) {
        cin >> e1;
        insertVertex(e1); // 插入顶点
    }

    cout << "请输入图的各边的信息：" << endl;
    i = 0;
    while (i < m) {
        cin >> e1 >> e2 >> weight;
        j = getVertexPos(e1);
        k = getVertexPos(e2);
        if (j == -1 || k == -1)
            cout << "边两端点信息有误，请重新输入！" << endl;
        else {
            insertEdge(j, k, weight); // 插入边
            i++;
        }
    } // while
}

// 输出图中的所有顶点和边信息
template <class T, class E>
void Graphlnk<T, E>::outputGraph() {
    int n, m, i, j;
    T e1, e2; // 顶点
    E weight; // 权值

    n = numVertices;
    m = numEdges;
    cout << "图中的顶点数为" << n << ",边数为" << m << endl;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            weight = getWeight(i, j); // 取边的权值
            if (weight > 0 && weight < maxWeight) { // 有效
                e1 = getValue(i); // 顶点
                e2 = getValue(j);
                cout << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
            }
        } // 内循环for
    } // 外循环for
}

// 取位置为i的顶点中的值
template <class T, class E>
T Graphlnk<T, E>::getValue(int i) {
    if (i >= 0 && i < numVertices)
        return nodeTable[i].data;
    return NULL;
}

// 返回边（v1， v2）上的权值
template <class T, class E>
E Graphlnk<T, E>::getWeight(int v1, int v2) {
    if (v1 != -1 && v2 != -1) {
        Edge<T, E>* p = nodeTable[v1].adj; // v1的第一条关联的边
        while (p != NULL && p->dest != v2) { // 寻找邻接顶点v2
            p = p->link;
        }
        if (p != NULL)
            return p->cost;
    }
    return 0; // 边(v1, v2)不存在
}

// 插入顶点
template <class T, class E>
bool Graphlnk<T, E>::insertVertex(const T& vertex) {
    if (numVertices == maxVertices) // 顶点表满，不能插入
        return false;
    nodeTable[numVertices].data = vertex; // 插入在表的最后
    numVertices++;
    return true;
}

// 插入边
template <class T, class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight) {
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
        Edge<T, E>* q, * p = nodeTable[v1].adj; // v1对应的边链表头指针
        while (p != NULL && p->dest != v2) // 寻找邻接顶点v2
            p = p->link;
        if (p != NULL) // 已存在该边，不插入
            return false;
        p = new Edge<T, E>; // 创建新结点
        p->dest = v2;
        p->cost = weight;
        p->link = nodeTable[v1].adj; // 链入v1边链表
        nodeTable[v1].adj = p;

        q = new Edge<T, E>;
        q->dest = v1;
        q->cost = weight;
        q->link = nodeTable[v2].adj; // 链入v2边链表
        nodeTable[v2].adj = q;
        numEdges++;
        return true;
    }
    return false;
}

// 删除顶点
template <class T, class E>
bool Graphlnk<T, E>::removeVertex(int v) {
    if (numVertices == 1 || v < 0 || v > numVertices)
        return false; // 表空或顶点号超出范围

    Edge<T, E>* p, * s, * t;
    int k; // 存储邻接顶点
    while (nodeTable[v].adj != NULL) {
        p = nodeTable[v].adj;
        k = p->dest; // 取邻接顶点k
        s = nodeTable[k].adj; // 找对称存放的边结点
        t = NULL;
        while (s != NULL && s->dest != v) {
            t = s;
            s = s->link;
        }
        if (s != NULL) { // 删除对称存放的边结点
            if (t == NULL) // 删除的是第一个邻接顶点
                nodeTable[k].adj = s->link;
            else
                t->link = s->link;
            delete s;
        }
        nodeTable[v].adj = p->link; // 清除顶点v的边链表结点
        delete p;
        numEdges--; // 与顶点v相关联的边数减1
    } // while结束
    numVertices--; // 图的顶点个数减1
    nodeTable[v].data = nodeTable[numVertices].data; // 填补
    p = nodeTable[v].adj = nodeTable[numVertices].adj;
    // 要将填补的顶点对应的位置改写
    while (p != NULL) {
        s = nodeTable[p->dest].adj; // 对称边链表结点
        while (s != NULL) {
            if (s->dest == numVertices) { // 找到对称边
                s->dest = v; // 修改指向v
                break;
            }
            s = s->link;
        }
        p = p->link; // 指向下一个邻接顶点
    }
    return true;
}

// 删除边
template <class T, class E>
bool Graphlnk<T, E>::removeEdge(int v1, int v2) {
    if (v1 != -1 && v2 != -1) {
        Edge<T, E>* p = nodeTable[v1].adj, * q = NULL, * s = p;
        while (p != NULL && p->dest != v2) { // v1对应边链表中找被删除边
            q = p;
            p = p->link;
        }
        if (p != NULL) { // 找到被删除边结点
            if (p == s) // 该结点是边链表的首结点
                nodeTable[v1].adj = p->link;
            else
                q->link = p->link; // 不是，重新链接
            delete p;
        }
        else // 没找到
            return false;

        // v2对应边链表中删除
        p = nodeTable[v2].adj;
        q = NULL;
        s = p; // 保存首结点
        while (p != NULL && p->dest != v1) { // 寻找边链表中要删除的结点
            q = p;
            p = p->link;
        }
        if (p == s) // 删除的该结点是边链表的首结点
            nodeTable[v2].adj = p->link;
        else
            q->link = p->link; // 不是，重新链接
        delete p;
        return true;
    }
    return false; // 没有找到结点
}

// 取顶点v的第一个邻接顶点
template <class T, class E>
int Graphlnk<T, E>::getFirstNeighbor(int v) {
    if (v != -1) {
        Edge<T, E>* p = nodeTable[v].adj; // 对应链表第一个边结点
        if (p != NULL) // 存在，返回第一个邻接顶点
            return p->dest;
    }
    return -1; // 第一个邻接顶点不存在
}

// 取顶点v的邻接顶点w的下一邻接顶点
template <class T, class E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w) {
    if (v != -1) {
        Edge<T, E>* p = nodeTable[v].adj; // 对应链表第一个边结点
        while (p != NULL && p->dest != w) // 寻找邻接顶点w
            p = p->link;
        if (p != NULL && p->link != NULL)
            return p->link->dest;  // 返回下一个邻接顶点
    }
    return -1; // 下一个邻接顶点不存在
}

// 给出顶点vertex在图中的位置
template <class T, class E>
int Graphlnk<T, E>::getVertexPos(const T vertex) {
    for (int i = 0; i < numVertices; i++)
        if (nodeTable[i].data == vertex)
            return i;
    return -1;
}

// 当前顶点数
template <class T, class E>
int Graphlnk<T, E>::numberOfVertices() {
    return numVertices;
}


int main() {
    Graphlnk<char, int> G; // 声明图对象
    MinSpanTree<char, int> MST; //声明最小生成树对象

    // 创建图
    G.inputGraph();

    if (MST.Kruscal(G)) { // 调用Kruscal函数
        cout << "根据Kruscal算法找出的最小生成树如下：" << endl;
        // 打印最小生成树
        MST.printMST(G);
    }
    return 0;
}