#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 50;
int g[N][N];
typedef struct node {
	int name;
	int val;
	node* next;
};
node* list[N];
string zhandian[N] = { "a","2","3","44","32","f","m" };
int cnt = 7;

int find(string str) {
	for (int i = 0; i < cnt; i++) {
		if (zhandian[i] == str) {
			return i;
		}
	}
	return -1;
}

void Init() {
	//�����ڽӾ���
	g[0][1] = g[1][0] = 2;
	g[0][2] = g[2][0] = 5;
	g[1][2] = g[2][1] = 2;
	g[1][3] = g[3][1] = 3;
	g[2][5] = g[5][2] = 1;
	g[3][4] = g[4][3] = 6;
	g[5][6] = g[6][5] = 7;

	//�����ڽӱ�
	for (int i = 0; i < N; i++) list[i] = NULL;
	node* n3;
	node* n2;
	node* n1;
	n2 = (node*)malloc(sizeof(node));
	n1 = (node*)malloc(sizeof(node));
	n2->name = 2; n2->val = 5; n2->next = NULL;
	n1->name = 1; n1->val = 2; n1->next = n2;
	list[0] = n1;
	n2 = (node*)malloc(sizeof(node));
	n1 = (node*)malloc(sizeof(node));
	n3 = (node*)malloc(sizeof(node));
	n3->name = 0; n3->val = 2; n3->next = NULL;
	n2->name = 3; n2->val = 3; n2->next = n3;
	n1->name = 2; n1->val = 2; n1->next = n2;
	list[1] = n1;
	n2 = (node*)malloc(sizeof(node));
	n1 = (node*)malloc(sizeof(node));
	n3 = (node*)malloc(sizeof(node));
	n3->name = 0; n3->val = 5; n3->next = NULL;
	n2->name = 5; n2->val = 1; n2->next = n3;
	n1->name = 1; n1->val = 2; n1->next = n2;
	list[2] = n1;
	n2 = (node*)malloc(sizeof(node));
	n1 = (node*)malloc(sizeof(node));
	n2->name = 4; n2->val = 5; n2->next = NULL;
	n1->name = 1; n1->val = 2; n1->next = n2;
	list[3] = n1;
	n2 = (node*)malloc(sizeof(node));
	n2->name = 3; n2->val = 5; n2->next = NULL;
	list[4] = n2;
	n2 = (node*)malloc(sizeof(node));
	n1 = (node*)malloc(sizeof(node));
	n2->name = 2; n2->val = 5; n2->next = NULL;
	n1->name = 6; n1->val = 2; n1->next = n2;
	list[5] = n1;
	n2 = (node*)malloc(sizeof(node));
	n2->name = 5; n2->val = 5; n2->next = NULL;
	list[6] = n2;
}

void addzhan() {
	string z;
	cout << "����������վ���վ��" << endl;
	cin >> z;
	zhandian[cnt] = z;
	int n;
	cout << "������Ҫ��ӵ���·��" << endl;
	cin >> n;
	string z1;
	int a, b;
	for (int i = 0; i < n; i++) {
		cout << "����������վ��ɴ��վ���� ���� ����" << endl;
		cin >> z1 >> a >> b;
		int temp = find(z1);
		g[cnt][temp] = g[temp][cnt] = a;
		node* tmp = (node*)malloc(sizeof(node));
		tmp->next = list[cnt];
		tmp->name = temp;
		tmp->val = b;
		list[cnt] = tmp;
		node* tm = (node*)malloc(sizeof(node));
		tm->next = list[temp];
		tm->name = cnt;
		tm->val = b;
		list[temp] = tm;
	}
	cnt++;
	cout << "���ӳɹ�" << endl;
}

void delzhan() {
	string z;
	cout << "������Ҫɾ��վ���վ��" << endl;
	cin >> z;
	int pos = find(z);
	if (pos == -1) cout << "û�и�վ��" << endl;
	else {
		for (int i = 0; i < cnt; i++) {
			g[i][pos] = g[pos][i] = 0;
			if (pos != i) {
				node* cur = list[i];
				if (cur->name == pos) {
					list[i] = cur->next;
					free(cur);
				}
				else {
					while (cur->next != NULL) {
						if (cur->next->name == pos) {
							cur->next = cur->next->next;
							free(cur->next);
						}
						cur = cur->next;
					}
				}

			}
		}
		list[pos] = NULL;
		cnt--;
		cout << "ɾ���ɹ�" << endl;
	}
}

void foly1() {
	string z1, z2;
	cout << "��������ʼվ���յ�վ" << endl;
	cin >> z1 >> z2;
	int sta = find(z1);
	int des = find(z2);
	if (sta == -1) cout << "û�и���ʼվ��" << endl;
	if (des == -1) cout << "û�и��յ�վ" << endl;

	if (sta != -1 && des != -1) {
		int dis[N][N];
		int path[N][N];
		//��ʼ��
		for (int i = 0; i < cnt; i++) {
			for (int j = 0; j < cnt; j++) {
				if (g[i][j] == 0)dis[i][j] = 999999;//����һ���ϴ��ֵ
				else dis[i][j] = g[i][j];
				path[i][j] = j;
			}
		}
		for (int k = 0; k < cnt; k++) {
			for (int i = 0; i < cnt; i++) {
				for (int j = 0; j < cnt; j++) {
					if (dis[i][k] + dis[k][j] < dis[i][j]) {
						dis[i][j] = dis[i][k] + dis[k][j];
						path[i][j] = path[i][k];
					}
				}
			}
		}
		cout << zhandian[sta] << "->" << zhandian[des] << "��̾���Ϊ" << dis[sta][des] << endl;
		cout << "path: ";
		while (sta != des) {
			cout << zhandian[sta] << "->";
			sta = path[sta][des];
		}
		cout << zhandian[sta] << endl;
	}
}

void foly2() {
	string z1, z2;
	cout << "��������ʼվ���յ�վ" << endl;
	cin >> z1 >> z2;
	int sta = find(z1);
	int des = find(z2);
	if (sta == -1) cout << "û�и���ʼվ��" << endl;
	if (des == -1) cout << "û�и��յ�վ" << endl;
	if (sta != -1 && des != -1) {
		int dis[N][N];
		int path[N][N];
		for (int i = 0; i < cnt; i++) {
			for (int j = 0; j < cnt; j++) {
				dis[i][j] = 999999;//����һ���ϴ��ֵ
				path[i][j] = j;
			}
		}
		node* cur;
		for (int i = 0; i < cnt; i++) {
			cur = list[i];
			while (cur != NULL) {
				dis[i][cur->name] = cur->val;
				cur = cur->next;
			}
		}

		for (int k = 0; k < cnt; k++) {
			for (int i = 0; i < cnt; i++) {
				for (int j = 0; j < cnt; j++) {
					if (dis[i][k] + dis[k][j] < dis[i][j]) {
						dis[i][j] = dis[i][k] + dis[k][j];
						path[i][j] = path[i][k];;
					}
				}
			}
		}
		cout << zhandian[sta] << "->" << zhandian[des] << "��̻���Ϊ" << dis[sta][des] << endl;
		cout << "path: ";
		while (sta != des) {
			cout << zhandian[sta] << "->";
			sta = path[sta][des];
		}
		cout << zhandian[sta] << endl;

	}
}

void bfs() {
	string z1, z2;
	cout << "��������ʼվ���յ�վ" << endl;
	cin >> z1 >> z2;
	int sta = find(z1);
	int des = find(z2);
	if (sta == -1) cout << "û�и���ʼվ��" << endl;
	if (des == -1) cout << "û�и��յ�վ" << endl;
	if (sta != -1 && des != -1) {
		queue<int> q;
		q.push(sta);
		int cur = 0;
		int pre[N];

		memset(pre, -1, sizeof(pre));
		pre[sta] = sta;
		while (!q.empty()) {
			cur = q.front();
			q.pop();
			for (int i = 0; i < N; i++) {
				if (g[cur][i] != 0 && pre[i] == -1) {
					pre[i] = cur;
					q.push(i);
				}
			}
		}
		int count = 0;
		int ans[N];
		//ans[count++] = sta;
		cur = des;
		while (cur != sta) {
			ans[count++] = cur;
			cur = pre[cur];
		}
		cout << zhandian[sta] << "->" << zhandian[des] << "������ת����Ϊ" << count - 1 << endl;
		cout << "path:" << zhandian[sta];
		for (int i = count - 1; i >= 0; i--) {
			cout << "->" << zhandian[ans[i]];
		}
		cout << endl;
	}
}
int main() {
	Init();
	int op = 0;
	do
	{
		printf("1 ����վ��\n");
		printf("2 ɾ��վ��\n");
		printf("3 ��쵽��\n");
		printf("4 ��ʡǮ\n");
		printf("5 ��ת����\n");
		printf("0 �˳�\n");
		cin >> op;
		switch (op)
		{
		case 1:
			addzhan();
			break;
		case 2:
			delzhan();
			break;
		case 3:
			foly1();
			break;
		case 4:
			foly2();
			break;
		case 5:
			bfs();
			break;
		default:
			break;
		}
	} while (op != 0);
}