#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <map>

using namespace std;

struct Point {
    int x, y, z;
};

struct Edge {
    int u, v;
    double distance;

    bool operator<(const Edge& other) const {
        return distance < other.distance;
    }
};

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) {
            return false;
        }

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }

        return true;
    }

    map<int, int> getComponentSizes() {
        map<int, int> sizes;
        for (int i = 0; i < parent.size(); i++) {
            sizes[find(i)]++;
        }
        return sizes;
    }

    int countComponents() {
        return getComponentSizes().size();
    }
};

double calculateDistance(const Point& a, const Point& b) {
    long long dx = (long long)a.x - b.x;
    long long dy = (long long)a.y - b.y;
    long long dz = (long long)a.z - b.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

vector<Point> readInput(const string& filename) {
    vector<Point> points;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        Point p;
        char comma;
        stringstream ss(line);
        ss >> p.x >> comma >> p.y >> comma >> p.z;
        points.push_back(p);
    }

    return points;
}

int solve(const vector<Point>& points, int numConnections) {
    int n = points.size();

    vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Edge e;
            e.u = i;
            e.v = j;
            e.distance = calculateDistance(points[i], points[j]);
            edges.push_back(e);
        }
    }

    sort(edges.begin(), edges.end());

    UnionFind uf(n);
    int connectionsAttempted = 0;

    for (const Edge& e : edges) {
        if (connectionsAttempted >= numConnections) {
            break;
        }

        uf.unite(e.u, e.v);
        connectionsAttempted++;
    }

    map<int, int> componentSizes = uf.getComponentSizes();

    vector<int> sizes;
    for (const auto& p : componentSizes) {
        sizes.push_back(p.second);
    }
    sort(sizes.rbegin(), sizes.rend());

    if (sizes.size() >= 3) {
        return sizes[0] * sizes[1] * sizes[2];
    } else if (sizes.size() == 2) {
        return sizes[0] * sizes[1];
    } else if (sizes.size() == 1) {
        return sizes[0];
    }

    return 0;
}

long long solvePart2(const vector<Point>& points) {
    int n = points.size();

    vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Edge e;
            e.u = i;
            e.v = j;
            e.distance = calculateDistance(points[i], points[j]);
            edges.push_back(e);
        }
    }

    sort(edges.begin(), edges.end());

    UnionFind uf(n);
    int lastU = -1, lastV = -1;

    for (const Edge& e : edges) {
        if (uf.unite(e.u, e.v)) {
            lastU = e.u;
            lastV = e.v;

            if (uf.countComponents() == 1) {
                break;
            }
        }
    }

    if (lastU != -1 && lastV != -1) {
        long long result = (long long)points[lastU].x * points[lastV].x;
        cout << "Last connection: (" << points[lastU].x << "," << points[lastU].y << "," << points[lastU].z << ") <-> ";
        cout << "(" << points[lastV].x << "," << points[lastV].y << "," << points[lastV].z << ")" << endl;
        return result;
    }

    return 0;
}

int main() {
    vector<Point> points = readInput("input.txt");

    cout << "Number of junction boxes: " << points.size() << endl;
    cout << endl;

    cout << "Part 1:" << endl;
    int result1 = solve(points, 1000);
    cout << "Product of three largest circuits: " << result1 << endl;
    cout << endl;

    cout << "Part 2:" << endl;
    long long result2 = solvePart2(points);
    cout << "Product of X coordinates: " << result2 << endl;

    return 0;
}
