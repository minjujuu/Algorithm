#include <iostream>
#include <cstdio>

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

int main()
{
    TRI s[100] = {
        {1, 2, 3},
        {4, 5, 6},
        {2, 2, 4},
        {4, 2, 1},
        {4, 2, 2},
        {4, 6, 8}
    };

    TRI t;
    Q.Insert(s[0]);
    Q.Insert(s[1]);
    Q.Insert(s[2]);
    Q.Insert(s[3]);
    Q.Insert(s[4]);
    Q.Insert(s[5]);
    t = Q.Delete(); // weight�� ���� ���� (4, 2, 1)�� �����Ǿ�� �� 
    printf("Deleted (%d %d %d)\n", t.a, t.b, t.w);
    return 0;
}