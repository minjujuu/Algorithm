#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

// a���ٰ� b�� �����ϴ� �Ű�, w�� weight��
class TRI {
public:
    int a, b, w;
};

// Priority Queue
class PQ {
public:
    int n;
    TRI Arr[1000];
    PQ();
    TRI Delete();
    void Insert(TRI x);
    int isEmpty();
};

PQ::PQ()
{
    n = 0;
}

int PQ::isEmpty()
{
    return n == 0;
}

void PQ::Insert(TRI x)
{
    // n���� ������� (1���� n����)
    // ��ġ�� �ʵ��� n���ٰ� �־�� ��
    int i;
    Arr[n + 1] = x; // 1�����̰� 0�� �Ⱦ�
    i = n + 1;
    n = n + 1;
    // w�� Parent���� ������ �ٲ�� �� 
    while(i > 1 && Arr[i].w < Arr[i/2].w) {
        swap(Arr[i], Arr[i/2]);
        i = i/2; // �θ�� �� �� 
    }
}

TRI PQ::Delete()
{
    TRI ret = Arr[1]; // save return value 
    int i, j;
    if(n == 1) { n = 0; return ret; } // special case 
    Arr[1] = Arr[n]; // 1���� n���� ���� �����ϱ� n���� 1�� ����

    i = 1; n = n-1;
    while(1) {
        // ���� child�� n���� ũ�� ���� ��
        if (i*2 > n) {
            break;
        }
        else if(i*2+1 > n) { // Left Child Only
            //���� ���ϵ�� ���ؼ� ���� �� ũ�� �ٲٴ� ��
            if (Arr[i*2].w < Arr[i].w)
            {
                swap(Arr[i*2], Arr[i]);
                i = i*2;
            }
            else {
                break;
            }
        }
        else { // Left and Right Child exists
            // �� �� ���� �Ŷ� ��ȯ�ؾ� ��. ���̽��� ����
            // ���� �� �� ���� ū ���
            if(Arr[i].w > Arr[i*2].w && Arr[i].w > Arr[i*2+1].w) {
                if(Arr[i*2].w < Arr[i*2+1].w) {
                    j = i*2;
                }
                else {
                    j = i*2+1;
                }
                // �� �� ���� �Ŷ� �ٲ� 
                swap(Arr[i], Arr[j]);
                i = j; // �׸��� �� �Ʒ����� ���� ��
            }
            // ������ �����ٴ� �۰ų� ���� 
            else if(Arr[i].w > Arr[i*2].w && Arr[i].w <= Arr[i*2+1].w) {
                // ������ ���� ���� �ٲپ�� ��
                j = i *2;
                swap(Arr[i], Arr[j]);
                i = j; // �׸��� �� �Ʒ����� ���� ��
            }
            // ���� �����ٴ� �۰ų� ���� 
            else if(Arr[i].w <= Arr[i*2].w && Arr[i].w > Arr[i*2+1].w) {
                j = i *2+1;
                swap(Arr[i], Arr[j]);
                i = j; // �׸��� �� �Ʒ����� ���� ��
            }
            // ���� �׳� ���� ���� ��� 
            else {
                break; // �� �� ���� 
            }
        }
    }
    return ret;
}

PQ Q;

int n, m; 
vector<pair<int, int>> Edges[1000];
int M[1000]; // shortest path length
vector<int> P[1000]; // previous node
int main()
{
    // a, b�� ����̰�, w�� weight
    int c, i, a, b, w;
    TRI x, y;
    // �� n x m �� �Է�����
    scanf("%d %d", &n, &m);
    for (i=0; i<m; i++)
    {
        scanf("%d %d %d", &a, &b, &w);
        // '��� ��ȣ'�� '����� ������ weight'�� pair�� ����
        // �� ��忡 �ش��ϴ� �ε����� �����ؼ� 
        // �迭�� �ε��� Ȯ�� �� �ش� ��忡 ����� ���� �� ���� ���ϴ� ������ weight�� �� �� �ֵ��� �� 
        Edges[a].push_back(make_pair(b, w));
        Edges[b].push_back(make_pair(a, w));
    }
    for (i=1; i<=n; i++)
    {
        M[i] = 1000000;
    }
    
    c = 1; M[c] = 0; // �ҽ� ���
    // ���� ����� ��� ������ �ִ� ��
    for (i = 0; i < Edges[c].size(); i++) {
        // ��� ������ ť�� �� �������
        x.a = c;
        x.b = Edges[c][i].first;
        x.w = M[c] + Edges[c][i].second; // ���� �Ÿ��� ������
        Q.Insert(x);
    }

    while (Q.isEmpty() == 0) {
        // ������ ����
        y = Q.Delete();

        // �鸸���� ������ �̹� ���� ª�� �н��� �߰ߵǾ��ٴ� �ǹ��̹Ƿ� �ƹ��͵� ����
        if (M[y.b] < 1000000) {
            // ��� ��θ� ����ϱ� ���� ������ ���
            if(M[y.b] == y.w) {
                printf("Edge from Node %d to Node %d of Total Path Length %d added. Previous node %d.\n", y.a, y.b, y.w, y.a);
                P[y.b].push_back(y.a);
            }
            else {
                printf("IGNORED Edge from Node %d to Node %d of Total Path Length %d selected.\n", y.a, y.b, y.w);
            }
        }
        else {
            printf("Edge from Node %d to Node %d of Total Path Length %d selected. Previous node %d.\n", y.a, y.b, y.w, y.a);
            c = y.b;
            M[c] = y.w;
            P[y.b].push_back(y.a); // ���� ��� ��� 
            // c�� �ִ� �ֺ� ��带 ť�� �߰�
            // ���� ����� ��� ������ �ִ� ��
            for (i = 0; i < Edges[c].size(); i++)
            {
                // ��� ������ ť�� �� �������
                x.a = c;
                x.b = Edges[c][i].first;
                x.w = M[c] + Edges[c][i].second;
                Q.Insert(x);
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

or

Edge from Node 1 to Node 4 of Total Path Length 5 selected. Previous node 1.
Edge from Node 1 to Node 5 of Total Path Length 6 selected. Previous node 1.
IGNORED Edge from Node 4 to Node 5 of Total Path Length 7 selected.
Edge from Node 4 to Node 2 of Total Path Length 8 selected. Previous node 4.
IGNORED Edge from Node 5 to Node 4 of Total Path Length 8 selected.
IGNORED Edge from Node 4 to Node 2 of Total Path Length 9 selected.
Edge from Node 2 to Node 3 of Total Path Length 9 selected. Previous node 2.
IGNORED Edge from Node 4 to Node 1 of Total Path Length 10 selected.
IGNORED Edge from Node 5 to Node 3 of Total Path Length 10 selected.
IGNORED Edge from Node 3 to Node 2 of Total Path Length 10 selected.
IGNORED Edge from Node 1 to Node 2 of Total Path Length 10 selected.
IGNORED Edge from Node 2 to Node 4 of Total Path Length 11 selected.
IGNORED Edge from Node 5 to Node 1 of Total Path Length 12 selected.
IGNORED Edge from Node 5 to Node 3 of Total Path Length 12 selected.
IGNORED Edge from Node 2 to Node 4 of Total Path Length 12 selected.
IGNORED Edge from Node 3 to Node 5 of Total Path Length 13 selected.
IGNORED Edge from Node 4 to Node 3 of Total Path Length 14 selected.
IGNORED Edge from Node 3 to Node 5 of Total Path Length 15 selected.
IGNORED Edge from Node 2 to Node 1 of Total Path Length 18 selected.
IGNORED Edge from Node 3 to Node 4 of Total Path Length 18 selected.
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

or

Edge from Node 1 to Node 4 of Total Path Length 5 selected. Previous node 1.
Edge from Node 1 to Node 5 of Total Path Length 7 selected. Previous node 1.
Edge from Node 4 to Node 5 of Total Path Length 7 added. Previous node 4.
Edge from Node 4 to Node 2 of Total Path Length 8 selected. Previous node 4.
Edge from Node 5 to Node 3 of Total Path Length 9 selected. Previous node 5.
IGNORED Edge from Node 4 to Node 2 of Total Path Length 9 selected.
Edge from Node 2 to Node 3 of Total Path Length 9 added. Previous node 2.
IGNORED Edge from Node 5 to Node 4 of Total Path Length 9 selected.
IGNORED Edge from Node 4 to Node 1 of Total Path Length 10 selected.
IGNORED Edge from Node 3 to Node 2 of Total Path Length 10 selected.
IGNORED Edge from Node 1 to Node 2 of Total Path Length 10 selected.
IGNORED Edge from Node 3 to Node 5 of Total Path Length 11 selected.
IGNORED Edge from Node 2 to Node 4 of Total Path Length 11 selected.
IGNORED Edge from Node 2 to Node 4 of Total Path Length 12 selected.
IGNORED Edge from Node 5 to Node 3 of Total Path Length 13 selected.
IGNORED Edge from Node 4 to Node 3 of Total Path Length 14 selected.
IGNORED Edge from Node 5 to Node 1 of Total Path Length 14 selected.
IGNORED Edge from Node 3 to Node 5 of Total Path Length 15 selected.
IGNORED Edge from Node 2 to Node 1 of Total Path Length 18 selected.
IGNORED Edge from Node 3 to Node 4 of Total Path Length 18 selected.
*/
