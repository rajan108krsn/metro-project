#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Metro {
    unordered_map<string, vector<pair<string, int>>> graph;

public:
    void addConnection(string u, string v, int wt) {
        graph[u].push_back({v, wt});
        graph[v].push_back({u, wt});
    }

    void dijkstra(string source, string dest) {
        unordered_map<string, int> dist;
        unordered_map<string, string> parent;
        for (auto& pair : graph)
            dist[pair.first] = INT_MAX;

        dist[source] = 0;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        pq.push({0, source});

        while (!pq.empty()) {
            auto [d, node] = pq.top(); pq.pop();
            for (auto [nbr, wt] : graph[node]) {
                if (d + wt < dist[nbr]) {
                    dist[nbr] = d + wt;
                    parent[nbr] = node;
                    pq.push({dist[nbr], nbr});
                }
            }
        }

        if (dist[dest] == INT_MAX) {
            cout << "No route exists from " << source << " to " << dest << ".\n";
            return;
        }

        vector<string> path;
        string temp = dest;
        while (temp != source) {
            path.push_back(temp);
            temp = parent[temp];
        }
        path.push_back(source);

        cout << "\nShortest route from " << source << " to " << dest << ":\n";
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i];
            if (i > 0) cout << " -> ";
        }
        cout << "\nTotal time: " << dist[dest] << " min\n";
    }

    void showStations() {
        cout << "\nAvailable Metro Stations:\n";
        for (auto& station : graph) {
            cout << "- " << station.first << "\n";
        }
    }
};

int main() {
    Metro metro;

    metro.addConnection("CCS Airport", "Krishna Nagar", 4);
    metro.addConnection("Krishna Nagar", "Transport Nagar", 3);
    metro.addConnection("Transport Nagar", "Alambagh", 5);
    metro.addConnection("Alambagh", "Alambagh Bus Stand", 2);
    metro.addConnection("Alambagh Bus Stand", "Charbagh", 4);
    metro.addConnection("Charbagh", "Hussainganj", 2);
    metro.addConnection("Hussainganj", "Sachivalaya", 3);
    metro.addConnection("Sachivalaya", "Hazratganj", 2);
    metro.addConnection("Hazratganj", "KD Singh Babu Stadium", 3);
    metro.addConnection("KD Singh Babu Stadium", "Vishwavidyalaya", 4);
    metro.addConnection("Vishwavidyalaya", "IT College", 3);
    metro.addConnection("IT College", "Badshah Nagar", 4);
    metro.addConnection("Badshah Nagar", "Lekhraj Market", 3);
    metro.addConnection("Lekhraj Market", "Indira Nagar", 2);
    metro.addConnection("Indira Nagar", "Munshipulia", 3);
    metro.addConnection("BBD", "Indira Nagar", 5);
    metro.addConnection("BBD", "Munshipulia", 3);

    string source, dest;

    while (true) {
        cout << "\nCommands:\n";
        cout << "1. show  - Show all stations\n";
        cout << "2. route - Find shortest route\n";
        cout << "3. exit  - Exit\n";
        cout << "Enter command: ";
        string cmd;
        cin >> cmd;

        if (cmd == "show") {
            metro.showStations();
        } else if (cmd == "route") {
            cin.ignore();
            cout << "Enter source station: ";
            getline(cin, source);
            cout << "Enter destination station: ";
            getline(cin, dest);
            metro.dijkstra(source, dest);
        } else if (cmd == "exit") {
            cout << "Thank you for using Lucknow Metro Route Planner!\n";
            break;
        } else {
            cout << "Invalid command!\n";
        }
    }

    return 0;
}
