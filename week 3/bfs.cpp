//  g++ bfs.cpp -lsfml-graphics -lsfml-window -lsfml-system - command to run
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <map>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;
using namespace sf;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int NODE_RADIUS = 20;
const Color NODE_COLOR(11, 0, 59);
const Color VISITED_COLOR(59, 54, 0);
const Color CURRENT_LEVEL_COLOR(52, 0, 59);
const Color EDGE_COLOR(255, 255, 255);


const int DELAY = 1500;

struct Node {
    int id;
    float x, y;
    Node(int id, int x, int y): id(id), x(x), y(y) {}
};

class Graph {
public:

    map<int, vector<int>> adj;
    vector<Node> nodes;

    void add_node(int id, float x, float y) {
        nodes.push_back(Node(id, x, y));
    }

    void add_edge(int source, int destination) {
        adj[source].push_back(destination);
        adj[destination].push_back(source);
    }

    void draw(RenderWindow& window, map<int, int> &state, Font&font) {
        for (auto &node: nodes) {
            for (int neighbor: adj[node.id]) {
                Vertex line[] = {
                    Vertex(Vector2f(node.x, node.y), EDGE_COLOR),
                    Vertex(Vector2f(nodes[neighbor].x, nodes[neighbor].y), EDGE_COLOR)
                };
                window.draw(line, 2, Lines);
            }
        }
        for (auto &node: nodes) {
            CircleShape circle(NODE_RADIUS);
            circle.setOrigin(NODE_RADIUS, NODE_RADIUS);
            circle.setPosition(node.x, node.y);

            int id = node.id;
            if (state[id] == 0) {
                circle.setFillColor(NODE_COLOR);
            } else if (state[id] == 1) {
                circle.setFillColor(CURRENT_LEVEL_COLOR);
            } else if (state[id] == 2) {
                circle.setFillColor(VISITED_COLOR);
            }

            window.draw(circle);

            Text text;
            text.setFont(font);
            text.setString(to_string(node.id));
            text.setCharacterSize(20);
            text.setFillColor(Color::White);
            text.setPosition(node.x- NODE_RADIUS/2, node.y - NODE_RADIUS/2);
            window.draw(text);
        }

    }

};


void bfs(Graph &graph, int start_node, RenderWindow& window, Font& font) {
    while (1) {
        queue<int> q;
        q.push(start_node);

        map<int, int> state;
        state[start_node] = 1;

        while (!q.empty()) {
            int cur_size = q.size();

            for (int i = 0; i < cur_size; i++) {
                int node = q.front();
                q.pop();

                state[node] = 1;

                window.clear(Color::Black);
                graph.draw(window, state, font);
                window.display();
                this_thread::sleep_for(chrono::milliseconds(DELAY));

                for (int neighbor: graph.adj[node]) {
                    if (state[neighbor] == 0) {
                        q.push(neighbor);
                        state[neighbor] = 1;
                    }
                }

                state[node] = 2;
            }
        }
    }
}


int main() {

    Font font;
    font.loadFromFile("Arial.ttf");

    Graph graph;

    int vertices, edges;
    cout << "Enter the number of vertices" << endl;
    cin >> vertices;

    int x = 100;
    for (int i = 0; i < vertices; i++) {
        graph.add_node(i, x, i & 1 ? 200: 100);
        x += 100;
    }

    cout << "Enter the number of edges" << endl;
    cin >> edges;

    for (int i = 0; i < edges; i++) {
        int source, destination;
        cout << "enter source, destination" << endl;
        cin >> source >> destination;
        graph.add_edge(source, destination);
    }

    cout << "enter starting node" << endl;
    int start;
    cin >> start;

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BFS LAB PROGRAM");
    bfs(graph, start, window, font);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) 
                window.close();
        }
    }

    return 0;


}


