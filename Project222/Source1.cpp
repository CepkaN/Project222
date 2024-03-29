#include <iostream>
#include<vector>
#include<bitset>
#include<algorithm>
#include <cstdint>


template <typename Dtype>
int __builtin_popcount(Dtype u)
{
	u = (u & 0x55555555) + ((u >> 1) & 0x55555555);
	u = (u & 0x33333333) + ((u >> 2) & 0x33333333);
	u = (u & 0x0F0F0F0F) + ((u >> 4) & 0x0F0F0F0F);
	u = (u & 0x00FF00FF) + ((u >> 8) & 0x00FF00FF);
	u = (u & 0x0000FFFF) + ((u >> 16) & 0x0000FFFF);
	return u;
}
int main() {
	int tt;
	std::cin >> tt;
	while (tt--) {
		int n;
		std::cin >> n;
		std::vector<std::string>a(n), b(n);
		for (int i = 0; i < n; ++i) {
			std::cin >> a[i] >> b[i];
		}
		std::vector<std::vector<bool>>edge(n, std::vector<bool>(n));
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				edge[i][j] = (a[i] == a[j] || b[i] == b[j]);
			}
		}
		std::vector<std::vector<bool>>dp(1 << n, std::vector<bool>(n, false));
		for (int i = 0; i < n; ++i) {
			dp[1 << i][i] = true;
		}
		int ans = 0;
		for (int t = 1; t < (1 << n); ++t) {
			for (int i = 0; i < n; ++i) {
				if (dp[t][i]) {
					ans = std::max(ans, __builtin_popcount(t));
					for (int j = 0; j < n; ++j) {
						if (!(t & (1 << j))) {
							if (edge[i][j] || edge[j][i]) {
								dp[t | (1 << j)][j] = true;
							}
						}
					}
				}
			}
		}
		std::cout << n - ans << '\n';

	}

	return 0;
}