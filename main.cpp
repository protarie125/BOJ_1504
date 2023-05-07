#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvii = vector<vii>;

int n, e;
vvii adj;
int v1, v2;

constexpr auto inf = int{ 987'654'321 };

int dijk(int b, int e) {
	auto dist = vi(n + 1, inf);
	dist[b] = 0;

	auto q = priority_queue<pii, vii, greater<pii>>{};
	q.push({ 0, b });

	while (!q.empty()) {
		auto f = q.top();
		q.pop();

		const auto& x = f.second;

		if (e == x) {
			break;
		}

		for (const auto& yw : adj[x]) {
			const auto& y = yw.first;
			const auto& w = yw.second;

			const auto& newDist = dist[x] + w;
			if (newDist < dist[y]) {
				dist[y] = newDist;
				q.push({ newDist, y });
			}
		}
	}

	if (inf == dist[e]) {
		return -1;
	}

	return dist[e];
}

void solve() {
	auto canPath1 = bool{ true };
	auto canPath2 = bool{ true };

	auto pd1 = int{ 0 };
	auto pd2 = int{ 0 };

	const auto& d11 = dijk(1, v1);
	if (d11 < 0) {
		canPath1 = false;
	}
	else {
		pd1 += d11;
	}

	const auto& d12 = dijk(1, v2);
	if (d12 < 0) {
		canPath2 = false;
	}
	else {
		pd2 += d12;
	}

	const auto& d23 = dijk(v1, v2);
	if (d23 < 0) {
		canPath1 = false;
		canPath2 = false;
	}
	else {
		pd1 += d23;
		pd2 += d23;
	}

	const auto& d31 = dijk(v2, n);
	if (d31 < 0) {
		canPath1 = false;
	}
	else {
		pd1 += d31;
	}

	const auto& d32 = dijk(v1, n);
	if (d32 < 0) {
		canPath2 = false;
	}
	else {
		pd2 += d32;
	}

	if (canPath1 && canPath2) {
		const auto& ans = min(pd1, pd2);
		cout << ans;
		return;
	}

	if (canPath1) {
		cout << pd1;
		return;
	}

	if (canPath2) {
		cout << pd2;
		return;
	}

	cout << -1;
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n >> e;
	adj = vvii(n + 1, vii{});

	for (auto i = 0; i < e; ++i) {
		int a, b, c;
		cin >> a >> b >> c;

		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}

	cin >> v1 >> v2;

	solve();

	return 0;
}