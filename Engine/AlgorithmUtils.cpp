#include "pch.h"
#include "AlgorithmUtils.h"
#include "World.h"
#include "Level.h"
#include "Tilemap.h"

bool AlgorithmUtils::FindPathAStar(const Vector2D& src, Vector2D dest, std::vector<Vector2D>& path, int32 maxDepth)
{
    // 맵이 너무 커서 멀리 가야할 경우 계산량이 급격히 늘어나기에 maxDepth로 제한
    int32 depth = MathUtils::Manhattan(src, dest); // 대략적으로 가야되는 거리
    if (depth >= maxDepth)
        return false;

    static Vector2D front[4] = {
        {0, -1},
        {0, 1},
        {-1, 0},
        {1, 0}
    };

    std::priority_queue<PQNode, std::vector<PQNode>, std::greater<PQNode>> pq;
    std::map<Vector2D, int32> best; // 방문한 곳과 비용 체크를 동시에 하는것과 같다.
    std::map<Vector2D, Vector2D> parent;

    // 초기값
    {
        int32 cost = MathUtils::Manhattan(src, dest);
        pq.push({ cost, src});
        best[src] = cost;
        parent[src] = src;
    }

    bool found = false;
    while (pq.empty() == false) {
        // 제일 좋은 후보 찾기
        PQNode node = pq.top();
        pq.pop();

        // 더 짧은 경로를 찾았다면 스킵
        if (best[node.pos] < node.cost)
            continue;

        // 목적지에 도착했으면 바로 종료
        if (node.pos == dest)
        {
            found = true;
            break;
        }

        // 방문
        for (int32 dir = 0; dir < 4; ++dir) {
            Vector2D nextPos = node.pos + front[dir];

            // 갈수있는지 확인
            std::shared_ptr<Tilemap> tilemap = World::GetCurrentLevel()->GetCurTilemap();
            if (tilemap && tilemap->CanGo(nextPos) == false) 
                continue;
            
            // 갈 수 있지만 너무 멀면 가지 않는다.
            int32 depth = MathUtils::Manhattan(src, nextPos); // 여태까지 온 거리 (AStar 알고리즘에선 G값)
            if (depth >= maxDepth)
                continue;

            int32 cost = MathUtils::Manhattan(nextPos, dest); // 앞으로 가야될 예상 비용
            int32 bestCost = best[nextPos];
            
            // 이미 방문했었다면
            if (bestCost != 0) {
                // 다른 경로에서 더 빠른 길을 찾았으면 스킵
                if (bestCost <= cost)
                    continue;
            }

            // 예약 진행
            best[nextPos] = cost;
            pq.push({ cost, nextPos });
            parent[nextPos] = node.pos;

        }
    }

    // 목적지까지 갈 길이 없으니 최대한 가까운 위치로 이동
    if (found == false) {
        // 목적지 근처로 가기 위해 cost가 가장 적은 근처 위치 찾기
        int32 bestCost = INT32_MAX;
        for (auto& [pos, cost] : best) {
            // 동점이라면, 최초 위치에서 가장 덜 이동하는 쪽으로 
            if (bestCost == cost) {
                // 두 위치 중 더 가까운 위치 찾기
                int32 dist1 = MathUtils::Manhattan(src, dest);
                int32 dist2 = MathUtils::Manhattan(src, pos);
                
                if (dist1 > dist2)
                    dest = pos;
            }
            // 더 작은 cost
            else if (cost < bestCost) {
                dest = pos;
                bestCost = cost;
            }
        }
    }

    path.clear();
    Vector2D pos = dest;

    // 도착지에서 시작해 시작 위치로 거꾸로 올라간다.
    while (true) {
        path.push_back(pos);

        // 시작점
        if (pos == parent[pos])
            break;

        pos = parent[pos];
    }

    std::reverse(path.begin(), path.end());

    return true;
}
