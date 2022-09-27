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
vector<int> P[1000];

int main()
{
    // a, b�� ����̰�, w�� weight
    int c, i, a, b, w;
    TREE x, y;
    // �� n x m �� �Է�����
    scanf("%d %d", &n, &m);
    for (i=0; i<m; i++)
    {
        scanf("%d %d %d", &a, &b, &w);

        Edges[a].push_back(make_pair(b, w));
        Edges[b].push_back(make_pair(a, w));
    }

    // 1. Source ��带 V_�ĺ� ���տ� �߰� �� D[S] = 0 ���� , else D[I] = INF
    // 2. V_�ĺ� ������ ���� v �� ���Ͽ� D[v] �� �ּ��� v�� V_�ĺ� ���տ��� �����ϰ� V_��Ȯ ���տ� �߰�
    // 3. v�� direct edge�� �����ϴ� v_another�� ���� v_another�� V_��Ȯ ���տ� �������� ���� ��� V_�ĺ� ���տ� �߰�
    // 4. D[v_another]�� ���� min(D[v_another], D[v] + w(v, v_another)
    // 5.  V_�ĺ� ������ ���Ұ� �������� ���� ������ 2-4 �ݺ�

    for(i=0; i<=n; i++)
    {
        M[i] = 1000000;
    }
    c = 1; M[c] = 0; // ���� ���

    // ���� ����� ��� ������ �ִ� ��
    for (i = 0; i < Edges[c].size(); i++) {
        // ��� ������ ť�� �� �������
        x.a = c;
        x.b = Edges[c][i].first;
        x.w = M[c] + Edges[c][i].second;
        priorityQueue.Insert(x);
    }

    while(priorityQueue.IsEmpty() == 0)
    {
        // ���� ��� �������� ���� ����� ��带 ã��
        x = priorityQueue.Delete();
        // ���� ����� ����� ���� M�� �־�����Ƿ� 1000000 ���� ������ �װ� �ּҶ� �� �� ���� ���� 
        if(M[x.b] < 1000000)
        {
            if(M[x.b] == x.w)
            {
                printf("Edge from Node %d to Node %d of Total Path Length %d added. Previous node %d.\n", x.a, x.b, x.w, x.a);
                // ���� ��带 �־ ��θ� ���
                P[x.b].push_back(x.a);
            }
            else
            {
                printf("IGNORED Edge from Node %d to Node %d of Total Path Length %d selected.\n", x.a, x.b, x.w);
            }
        }
        else
        {            
            printf("Edge from Node %d to Node %d of Total Path Length %d selected. Previous node %d.\n", x.a, x.b, x.w, x.a);
            M[x.b] = x.w;
            // ���� ��忡�� ���� ����� ��带 ã�����Ƿ� �� ���� ����Ǿ��ִ� ������ ��ȸ�ϸ鼭 ����� ���� ������Ʈ ����.
            for (i = 0; i < Edges[x.b].size(); i++)
            {
                y.a = x.b;
                y.b = Edges[x.b][i].first;
                y.w = M[x.b] + Edges[x.b][i].second;

                priorityQueue.Insert(y);
            }
        }
    }

    return 0;
}

/* MST ���� �׷���
5 10
1 2 10
2 3 1
1 5 6
1 4 5
2 4 4
2 4 3
4 5 2
3 4 9
3 5 4
5 3 6
Edge from Node 1 to Node 4 of Total Path Length 5 selected.
Edge from Node 1 to Node 5 of Total Path Length 6 selected.
Edge from Node 4 to Node 2 of Total Path Length 8 selected.
Edge from Node 2 to Node 3 of Total Path Length 9 selected.
*/

/* ���� ��ΰ� �����ϴ� ���� �׷���
5 10
1 2 10
2 3 1
1 5 7
1 4 5
2 4 4
2 4 3
4 5 2
3 4 9
3 5 2
5 3 6
Edge from Node 1 to Node 4 of Total Path Length 5 selected. Previous node 1.
Edge from Node 1 to Node 5 of Total Path Length 7 selected. Previous node 1.
Edge from Node 4 to Node 2 of Total Path Length 8 selected. Previous node 4.
Edge from Node 5 to Node 3 of Total Path Length 9 selected. Previous node 5.
*/