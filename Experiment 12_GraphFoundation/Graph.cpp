//
// Created by Feng on 2020/12/8.
//

#include <iostream>
#include <queue>

using namespace std;

struct linkedNode {
    int element;
    linkedNode *next;

    linkedNode() {};

    linkedNode(const int &element) {
        this->element = element;
    }

    linkedNode(const int &element, linkedNode *next) {
        this->element = element;
        this->next = next;
    }
};

class graphChain {
public:
    graphChain() {
        listSize = 0;
        firstNode = NULL;
    }

    ~graphChain() {
        linkedNode *nextNode;
        while (firstNode != NULL) {
            nextNode = firstNode->next;
            delete firstNode;
            firstNode = nextNode;
        }
    }
    bool empty() const { return listSize == 0; }

    int chainSize() { return listSize; }

    void insert(int theElement) {
        linkedNode *currentNode = firstNode, *q=NULL;
        if (currentNode == NULL) {
            firstNode = new linkedNode(theElement, NULL);
            listSize++;
            return;
        } else {
            if (theElement < currentNode->element) {
                firstNode = new linkedNode(theElement, currentNode);
            } else {
                while (currentNode != NULL && currentNode->element < theElement) {
                    q = currentNode;
                    currentNode = currentNode->next;
                }
                if (currentNode != NULL)
                    q->next = new linkedNode(theElement, currentNode);
                else
                    q->next = new linkedNode(theElement, NULL);
            }
        }
        listSize++;
    }

    void erase(int theElement) {
        //单独考虑删除第一个节点元素
        linkedNode *currentNode = firstNode;
        linkedNode *nextNode = firstNode->next;
        if (currentNode->element == theElement) {
            firstNode = currentNode->next;
            delete currentNode;
            listSize--;
        }
            //删除其他节点
        else {
            while (nextNode != NULL) {
                if (nextNode->element == theElement) {
                    currentNode->next = nextNode->next; //令前一个节点的next
                    delete nextNode;                    //指向被删除节点的下一个
                    listSize--;
                    break;
                }
                currentNode = currentNode->next;
                nextNode = nextNode->next;
            }
        }
    }

    bool find(int theElement) {
        linkedNode *curentNode = firstNode;
        while (curentNode != NULL) {
            if (curentNode->element == theElement)
                return true;
            curentNode = curentNode->next;
        }
        return false;
    }

    //protected:
    int listSize;
    linkedNode *firstNode;
};

class linkedGraph {
public:
    linkedGraph(int numberOfVertices = 0) {
        n = numberOfVertices;
        e = 0;
        aList = new graphChain[n + 1];
    }

    ~linkedGraph() {
        delete[] aList;
    }

    void insertEdge(int point1, int point2) {
        if (aList[point1].find(point2) != 1) {

            aList[point1].insert(point2);
            aList[point2].insert(point1);
            e++;
        }
    }

    void eraseEdge(int point1, int point2) {
        if (aList[point1].find(point2) == 1) {
            aList[point1].erase(point2);
            aList[point2].erase(point1);
            e--;
        }
    }

    void bfs(int v, int reach[], int label) {
        queue<int> q;
        reach[v] = label;
        q.push(v);

        while (!q.empty()) {
            int w = q.front();
            q.pop();

            for (linkedNode *u = aList[w].firstNode; u != NULL; u = u->next)

                if (reach[u->element] == 0) {
                    reach[u->element] = label;
                    q.push(u->element);
                    reach[u->element] = label;
                }
        }
    }

    void outputBfs(int v) {
        int reach[n + 1], element[n + 1], label = 1, index = 0;
        for (int i = 0; i < n + 1; i++) {
            reach[i] = element[i] = 0;
        }

        queue<int> q;
        reach[v] = label;
        q.push(v);

        while (!q.empty()) {
            int w = q.front();
            q.pop();
            element[++index] = w;
            for (linkedNode *u = aList[w].firstNode; u != NULL; u = u->next)
                if (reach[u->element] == 0) {
                    reach[u->element] = label;
                    q.push(u->element);
                    reach[u->element] = label;

                }
        }
        for (int i = 1; i <= index; i++) {
            cout << element[i] << " ";
        }
        cout << endl;
    }

    void dfs(int v, int reach[], int label) {
        reachs = reach;
        labels = label;
        this->rDfs(v);
    }

    void rDfs(int v) {
        reachs[v] = labels;
        for (linkedNode *u = aList[v].firstNode; u != NULL; u = u->next) {
            if (reachs[u->element] == 0) {
                rDfs(u->element);
            }
        }
    }

    void outputDfs(int v, int reach[], int label) {
        reach[v] = label;
        cout << v << " ";
        linkedNode *p = aList[v].firstNode;
        while (p != NULL) {
            if (reach[p->element] != label)
                outputDfs(p->element, reach, label);
            p = p->next;
        }
    }

    void minPath(int v, int t) {
        int reach[n + 1],label=1;
        for (int i = 0; i < n + 1; i++) {
            reach[i] = 0;
        }
        queue<int> q;
        reach[v] = label;
        q.push(v);
        int path[n+1];
        for(int i=0;i<n+1;i++)
        {
            path[i]=0;
        }
        while (!q.empty()) {
            int w = q.front();
            q.pop();

            for (linkedNode *u = aList[w].firstNode; u != NULL; u = u->next) {
                if (reach[u->element] == 0) {
                    if(u->element==t){
                        cout<<path[w]+1<<endl;
                        return;
                    }
                    path[u->element]=path[w]+1;
                    q.push(u->element);
                    reach[u->element] = label;
                }
            }
        }
        cout<<"-1"<<endl;
    }

    //第一行与第二行输出
    void labelComponents() {
        int label = 0;
        int reach[n + 1], a[n + 1];
        for (int i = 0; i < n + 1; i++) {
            reach[i] = 0;
            a[n + 1] = 0;
        }
        for (int i = 1; i <= n; i++)
            if (reach[i] == 0) {
                label++;
                a[label] = i; //记录每个连通分支最小值
                bfs(i, reach, label);
            }
        cout << label << endl;
        for (int i = 1; i <= label; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }

    //第三行输出
    void numberOfDfs(int v) {
        int reach[n + 1];
        for (int i = 0; i < n + 1; i++) {
            reach[i] = 0;
        }
        dfs(v, reach, 1);
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            if (reach[i] == 1)
                sum++;
        }
        cout << sum << endl;
    }

    //第五行输出
    void numberOfBfs(int v) {
        int reach[n + 1];
        for (int i = 0; i < n + 1; i++) {
            reach[i] = 0;
        }
        bfs(v, reach, 1);
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            if (reach[i] == 1)
                sum++;
        }
        cout << sum << endl;
    }

    void output() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (aList[i].find(j)) {
                    cout << "[" << i << "," << j << "]" << endl;
                }
            }
        }
    }

protected:
    int n; //顶点个数
    int e; //边个数
    graphChain *aList;
    int *reachs;
    int labels;
};

int main() {
    int n, m, s, t;
    int option, point1, point2;
    cin >> n >> m >> s >> t;
    linkedGraph graph(n);

    for (int i = 0; i < m; i++) {
        cin >> option >> point1 >> point2;
        if (option == 0)
            graph.insertEdge(point1, point2);
        else
            graph.eraseEdge(point1, point2);
    }
//    graph.output();
    graph.labelComponents();
    int reach[n + 1];
    for (int i = 0; i < n + 1; i++) {
        reach[i] = 0;
    }
    graph.numberOfDfs(s);
    graph.outputDfs(s, reach, 1);
    cout<<endl;
    graph.numberOfBfs(t);
    graph.outputBfs(t);
    graph.minPath(s,t);
}