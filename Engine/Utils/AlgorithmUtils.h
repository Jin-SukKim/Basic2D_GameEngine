#pragma once

struct PQNode {
	PQNode(int32 cost, Vector2D pos) : cost(cost), pos(pos) {}

	bool operator<(const PQNode& other) const {
		return cost < other.cost;
	}
	bool operator>(const PQNode& other) const {
		return cost > other.cost;
	}

	int32 cost; // 예상 비용
	Vector2D pos;
};

struct AlgorithmUtils
{
	// MaxDepth의 default값을 설정해 너무 멀면 더 이상 찾지 않아 계산량을 아낀다.
	// Pos 값은 Tilemap 좌표를 기반으로 받는다.
	static bool FindPathAStar(const Vector2D& src, Vector2D dest, std::vector<Vector2D>& path, int32 maxDepth = 10);
};

