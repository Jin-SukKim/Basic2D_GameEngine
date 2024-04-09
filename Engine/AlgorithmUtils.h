#pragma once

struct PQNode {
	PQNode(int32 cost, Vector2D pos) : cost(cost), pos(pos) {}

	bool operator<(const PQNode& other) const {
		return cost < other.cost;
	}
	bool operator>(const PQNode& other) const {
		return cost > other.cost;
	}

	int32 cost; // ���� ���
	Vector2D pos;
};

struct AlgorithmUtils
{
	// MaxDepth�� default���� ������ �ʹ� �ָ� �� �̻� ã�� �ʾ� ��귮�� �Ƴ���.
	// Pos ���� Tilemap ��ǥ�� ������� �޴´�.
	static bool FindPathAStar(const Vector2D& src, Vector2D dest, std::vector<Vector2D>& path, int32 maxDepth = 10);
};

