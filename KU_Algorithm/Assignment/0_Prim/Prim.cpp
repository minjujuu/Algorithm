#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

class TREE {
public:
    int a, b, w;
};

// Priority Queue
class PriorityQueue
{
public:
    int n;
    TREE Arr[1000];
    PriorityQueue();
    TREE Delete();
    void Insert(TREE x);
    int IsEmpty();
    inline bool IsNotFirstEdge(int idx) { return idx > 1; }
    inline bool IsSmallerThanParentWeight(int idx) { return Arr[idx].w < Arr[idx/2].w; }
};

PriorityQueue::PriorityQueue()
{
    n = 0;
}

int PriorityQueue::IsEmpty()
{
    return n == 0;
}

void PriorityQueue::Insert(TREE x)
{
    int i;
    Arr[n+1] = x; // ���� ��尡 n���̹Ƿ� ���� ĭ�� �Ҵ�
    i = n+1; // i�� ���� ��带 ����Ű���� ����
    n = n+1; // ���� ������Ʈ
    // ���� ���� ������ weight�� ù ��° ��尡 �ƴϰ�, 
    // weight�� �θ� ��庸�� ������ ��ȯ

    // ���� ���� weight�� ���� ���� ���� �ø��� ���� ����
    while(IsNotFirstEdge(i) && IsSmallerThanParentWeight(i)) {
        swap(Arr[i], Arr[i/2]);
        i = i/2; // i�� �θ� ����� �ε����� ������Ʈ�ؼ� �ٽ� ���� �θ� ���� ���ϵ��� ��
    }
}

TREE PriorityQueue::Delete()
{
    // �켱���� ť�� ���� ���� ��带 �����ϹǷ�, �ε��� 1�� �ִ� ��带 �����ϱ� �� �� ĳ��
    TREE cachedTree = Arr[1]; 
    int curNodeIdx, exchangeNodeIdx;
    // ��尡 �� �� ���� ���
    if (n == 1) {
        n = 0;
        return cachedTree;
    }
    // ���� ���� ��带 �ֻ��� ���� ���� 
    Arr[1] = Arr[n];

    curNodeIdx = 1; // ������ ������ �ڸ��� ã���ֱ� ���� �ε����� ó������ �̵�
    n = n - 1; // ���� ������Ʈ 

    while(1) {

        bool isLastNode = curNodeIdx * 2 > n;
        bool hasOnlyLeftNode = curNodeIdx * 2 + 1 > n;

        int leftNodeIdx = curNodeIdx * 2;
        int rightNodeIdx = curNodeIdx * 2 + 1;

        // ���� �ڽ� ����� �ε����� n���� ū ���� �����Ƿ� ��
        if(isLastNode) {
            break;
        }
        // ���� �ڽĸ� �ִ� ���
        else if(hasOnlyLeftNode) {
            // ���� �ڽĺ��� ���� ��尡 �� ũ�� ��ȯ
            bool isLargerThanLeftNode = Arr[leftNodeIdx].w < Arr[curNodeIdx].w;
            if(isLargerThanLeftNode) {
                swap(Arr[leftNodeIdx], Arr[curNodeIdx]);
                curNodeIdx = leftNodeIdx;
            }
            else {
                break;
            }
        }
        // ���� �ڽİ� ������ �ڽ� ��� �� �� �����ϴ� ���
        else {
            // ���� ��尡 ���� �ڽ�, ������ �ڽĺ��� ū ���
            bool isLargerThanBothNode = Arr[curNodeIdx].w > Arr[leftNodeIdx].w && Arr[curNodeIdx].w > Arr[rightNodeIdx].w;
            bool isLargerThanOnlyLeftNode = Arr[curNodeIdx].w > Arr[leftNodeIdx].w && Arr[curNodeIdx].w <= Arr[rightNodeIdx].w;
            bool isLargerThanOnlyRightNode = Arr[curNodeIdx].w > Arr[rightNodeIdx].w && Arr[curNodeIdx].w <= Arr[leftNodeIdx].w;
            
            if(isLargerThanBothNode) {
                bool isLeftNodeSmallerThanRightNode = Arr[leftNodeIdx].w < Arr[rightNodeIdx].w;
                if(isLeftNodeSmallerThanRightNode) {
                    exchangeNodeIdx = leftNodeIdx;
                }
                else {
                    exchangeNodeIdx = rightNodeIdx;
                }
                // �� �� ���� �Ͱ� ��ȯ
                swap(Arr[curNodeIdx], Arr[exchangeNodeIdx]);
                curNodeIdx = exchangeNodeIdx; // ���� ��� Ȯ��
            }
            // ���� ��庸�ٴ� ũ���� ������ ��庸�ٴ� �۰ų� ���� 
            else if(isLargerThanOnlyLeftNode) {
                exchangeNodeIdx = leftNodeIdx;
                swap(Arr[curNodeIdx], Arr[exchangeNodeIdx]);
                curNodeIdx = exchangeNodeIdx;
            }
            // ������ ��庸�ٴ� ũ���� ���� ��庸�ٴ� �۰ų� ���� 
            else if(isLargerThanOnlyRightNode) {
                exchangeNodeIdx = rightNodeIdx;
                swap(Arr[curNodeIdx], Arr[exchangeNodeIdx]);
                curNodeIdx = exchangeNodeIdx;
            }
            else { // �����尡 ���� ���� ����� �ƹ��͵� ���� ����
                break; 
            }
        }
    }
    return cachedTree;
}

PriorityQueue priorityQueue;

int n, m;
vector<pair<int, int>> Edges[1000];
int M[1000];

int main()
{
    // 1. �Է� �ޱ�
    // 2. �Է¹��� ������ ���� �迭�� �� �ֱ� (����� ��� ��ȣ �� �� ���� ���ϴ� ���� ����Ʈ)
    // 3. ������ ��� (���⿡�� 1�� ���)�� ���� ���� �����ϰ� ��ȴٴ� ��ŷ
    // 4. ���� ����� ��� ������ ť�� �ֱ� (���� weight�� ���� �� �˱� ����)
    // 5. ť�� ��� �� ������ �ٽ� �� �����鼭 ������ Ȯ�� (ť�� ����ٴ� �� �ֺ� ��尡 ���ٴ� �� )
    // - ����Ŭ�� ������� (�� ��尡 �̹� ��ŷ�Ǿ� ������ ����Ŭ�� ����� ������)
    // - ����Ŭ�� ������ ������ ���� ����� �ֺ� ���� �� ������ �ٽ� ť�� ��� �߰� 

    int n, m;
    TREE x, y;
    int a, b, w;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &a, &b, &w);
        Edges[a].push_back(make_pair(b, w));
        Edges[b].push_back(make_pair(a, w));
    }

    int curIdx = 1; 
    M[curIdx] = 1; 

    for(int i = 0; i < Edges[curIdx].size(); i++) 
    {
        x.a = curIdx;
        x.b = Edges[curIdx][i].first;
        x.w = Edges[curIdx][i].second;
        priorityQueue.Insert(x);
    }

    while(priorityQueue.IsEmpty() == 0)
    {
        y = priorityQueue.Delete();

        bool isCycle = M[y.a] == 1 && M[y.b] == 1;
        if(isCycle) {
            continue;
        }
        else {
            printf("Edge from Node %d to Node %d of Weight %d selected.\n", y.a, y.b, y.w);
            curIdx = y.b;
            M[curIdx] = 1;
            
            for(int i = 0; i < Edges[curIdx].size(); i++)
            {
                x.a = curIdx;
                x.b = Edges[curIdx][i].first;
                x.w = Edges[curIdx][i].second;
                priorityQueue.Insert(x);
            }
        }
    }

    return 0;
}