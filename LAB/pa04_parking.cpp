#include <bits/stdc++.h>
#define X first
#define Y second
using namespace std;

int dx[] = {0,-1,1,0};
int dy[] = {-1,0,0,1};
int N, size, ans, cnt, board[20][20], dist[20][20];
queue<pair<int, int> >  Q;

void init() {
    fill(&dist[0][0], &dist[19][20], -1);
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
            if (board[i][j] == 9) {Q.push(make_pair(i,j)); dist[i][j] = 0;}
        }
    }
    size = 2;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();

    while (!Q.empty()) {
        pair<int, int> cur = Q.front(); Q.pop();
        if (0 < board[cur.X][cur.Y] && board[cur.X][cur.Y] < size) {
            board[cur.X][cur.Y] = 0;
            ans += dist[cur.X][cur.Y];
            cnt++;
            if (cnt >= size) {size++; cnt = 0;}
            fill(&dist[0][0], &dist[19][20], -1);
            dist[cur.X][cur.Y] = 0;
        }

        for (int dir = 0; dir < 4; dir++) {
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];

            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (dist[nx][ny] >= 0 || board[nx][ny] > size) continue;

            dist[nx][ny] = dist[cur.X][cur.Y] + 1;
            Q.push(make_pair(nx, ny));
        }
    }

    cout << ans;
}