#pragma once
struct flood {
	int x, y;
	flood(int sx, int sy) : x(sx), y(sy) {}
};

std::vector<flood>vec;

bool bennevane(std::vector<flood>& vec, int sx, int sy)
{
	bool val = false;
	for (auto i : vec)
	{
		if (i.x == sx && i.y == sy) {
			val = true;
			// std::cout << "HERE\n";
			break;
		}
	}

	return val;
}

