#include "pch.h"
#include "AlgorithmUtils.h"
#include "World.h"
#include "Level.h"
#include "Tilemap.h"

bool AlgorithmUtils::FindPathAStar(const Vector2D& src, Vector2D dest, std::vector<Vector2D>& path, int32 maxDepth)
{
    // ���� �ʹ� Ŀ�� �ָ� ������ ��� ��귮�� �ް��� �þ�⿡ maxDepth�� ����
    int32 depth = MathUtils::Manhattan(src, dest); // �뷫������ ���ߵǴ� �Ÿ�
    if (depth >= maxDepth)
        return false;

    static Vector2D front[4] = {
        {0, -1},
        {0, 1},
        {-1, 0},
        {1, 0}
    };

    std::priority_queue<PQNode, std::vector<PQNode>, std::greater<PQNode>> pq;
    std::map<Vector2D, int32> best; // �湮�� ���� ��� üũ�� ���ÿ� �ϴ°Ͱ� ����.
    std::map<Vector2D, Vector2D> parent;

    // �ʱⰪ
    {
        int32 cost = MathUtils::Manhattan(src, dest);
        pq.push({ cost, src});
        best[src] = cost;
        parent[src] = src;
    }

    bool found = false;
    while (pq.empty() == false) {
        // ���� ���� �ĺ� ã��
        PQNode node = pq.top();
        pq.pop();

        // �� ª�� ��θ� ã�Ҵٸ� ��ŵ
        if (best[node.pos] < node.cost)
            continue;

        // �������� ���������� �ٷ� ����
        if (node.pos == dest)
        {
            found = true;
            break;
        }

        // �湮
        for (int32 dir = 0; dir < 4; ++dir) {
            Vector2D nextPos = node.pos + front[dir];

            // �����ִ��� Ȯ��
            std::shared_ptr<Tilemap> tilemap = World::GetCurrentLevel()->GetCurTilemap();
            if (tilemap && tilemap->CanGo(nextPos) == false) 
                continue;
            
            // �� �� ������ �ʹ� �ָ� ���� �ʴ´�.
            int32 depth = MathUtils::Manhattan(src, nextPos); // ���±��� �� �Ÿ� (AStar �˰��򿡼� G��)
            if (depth >= maxDepth)
                continue;

            int32 cost = MathUtils::Manhattan(nextPos, dest); // ������ ���ߵ� ���� ���
            int32 bestCost = best[nextPos];
            
            // �̹� �湮�߾��ٸ�
            if (bestCost != 0) {
                // �ٸ� ��ο��� �� ���� ���� ã������ ��ŵ
                if (bestCost <= cost)
                    continue;
            }

            // ���� ����
            best[nextPos] = cost;
            pq.push({ cost, nextPos });
            parent[nextPos] = node.pos;

        }
    }

    // ���������� �� ���� ������ �ִ��� ����� ��ġ�� �̵�
    if (found == false) {
        // ������ ��ó�� ���� ���� cost�� ���� ���� ��ó ��ġ ã��
        int32 bestCost = INT32_MAX;
        for (auto& [pos, cost] : best) {
            // �����̶��, ���� ��ġ���� ���� �� �̵��ϴ� ������ 
            if (bestCost == cost) {
                // �� ��ġ �� �� ����� ��ġ ã��
                int32 dist1 = MathUtils::Manhattan(src, dest);
                int32 dist2 = MathUtils::Manhattan(src, pos);
                
                if (dist1 > dist2)
                    dest = pos;
            }
            // �� ���� cost
            else if (cost < bestCost) {
                dest = pos;
                bestCost = cost;
            }
        }
    }

    path.clear();
    Vector2D pos = dest;

    // ���������� ������ ���� ��ġ�� �Ųٷ� �ö󰣴�.
    while (true) {
        path.push_back(pos);

        // ������
        if (pos == parent[pos])
            break;

        pos = parent[pos];
    }

    std::reverse(path.begin(), path.end());

    return true;
}
