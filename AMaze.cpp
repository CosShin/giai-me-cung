#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct Node {
    int x, y;
    int g, h, f;
    Node* parent;

    Node(int x, int y) : x(x), y(y), g(0), h(0), f(0), parent(nullptr) {}
};

int manhattanDistance(const Node& a, const Node& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

bool isValid(int x, int y, int mazeSizeX, int mazeSizeY, const vector<vector<int>>& maze) {
    return x >= 0 && y >= 0 && x < mazeSizeX && y < mazeSizeY && maze[x][y] == 0;
}

vector<Node*> getNeighbors(const Node& node, int mazeSizeX, int mazeSizeY, const vector<vector<int>>& maze) {
    vector<Node*> neighbors;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        int newX = node.x + dx[i];
        int newY = node.y + dy[i];

        if (isValid(newX, newY, mazeSizeX, mazeSizeY, maze)) {
            neighbors.push_back(new Node(newX, newY));
        }
    }

    return neighbors;
}

vector<Node*> aStar(const Node& start, const Node& goal, int mazeSizeX, int mazeSizeY, const vector<vector<int>>& maze) {
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> openSet;
    vector<vector<bool>> closedSet(mazeSizeX, vector<bool>(mazeSizeY, false));

    openSet.push(make_pair(0, new Node(start.x, start.y)));
    while (!openSet.empty()) {
        Node* current = openSet.top().second;
        openSet.pop();

        if (current->x == goal.x && current->y == goal.y) {
            vector<Node*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            return path;
        }

        closedSet[current->x][current->y] = true;

        vector<Node*> neighbors = getNeighbors(*current, mazeSizeX, mazeSizeY, maze);
        for (Node* neighbor : neighbors) {
            if (!closedSet[neighbor->x][neighbor->y]) {
                int tentativeG = current->g + 1;
                if (tentativeG < neighbor->g || !neighbor->parent) {
                    neighbor->parent = current;
                    neighbor->g = tentativeG;
                    neighbor->h = manhattanDistance(*neighbor, goal);
                    neighbor->f = neighbor->g + neighbor->h;
                    openSet.push(make_pair(neighbor->f, neighbor));
                }
            }
        }
    }

    return vector<Node*>(); // No path found
}

int main() {
    int mazeSizeX = 6;
    int mazeSizeY = 6;
    vector<vector<int>> maze = {
        {0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 1},
        {0, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}
    };

    Node start(0, 0);
    Node goal(5, 5);

    vector<Node*> path = aStar(start, goal, mazeSizeX, mazeSizeY, maze);

    if (!path.empty()) {
        cout << "Path found:" << endl;
        for (Node* node : path) {
            cout << "(" << node->x << ", " << node->y << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
