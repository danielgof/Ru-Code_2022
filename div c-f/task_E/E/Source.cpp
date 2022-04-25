#include <iostream>
#include <vector>

int main()
{
	int N, M, K;
	std::cin >> N >> M;
	std::cin >> K;
	std::vector<std::vector<int> > arr(N, std::vector<int>(M));
	std::vector<std::pair<char, int>> commands(K);
	
	for (int i = 0; i < K; i++)
	{
		char tmp1;
		int tmp2;
		std::cin >> tmp1;
		std::cin >> tmp2;
		commands[i] = { tmp1, tmp2 };
	}

	int cnt = 0;

	for (int i = 1; i < N + 1; i++)
	{
		for (int j = 1; j < M; j++)
		{
			for (auto it = commands.begin(); it != commands.end(); ++it)
			{
				if (it->first == '+')
				{
					if (i + j == it->second)
					{
						cnt += 1;
					}
				}
				else
				{
					if (i - j == it->second)
					{
						cnt += 1;
					}
				}
			}
		}
	}


	std::cout << cnt;

	return 0;
}
