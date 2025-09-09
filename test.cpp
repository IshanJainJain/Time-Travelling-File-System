#include "HashMap.hpp"
#include "TreeNode.hpp"
#include "Binaryheap.hpp"
#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    HashMap1 files_map;
    BinaryHeap modi_heap;
    BinaryHeap size_heap;
    string command;
    while (getline(cin, command)) {
        istringstream iss(command);
        string cmd;
        iss >> cmd;

        if (cmd == "CREATE") {
            string initial_message = "created version 0";

            string file_name;
            iss >> file_name;

            time_t current_time = time(nullptr);
            int t_int = static_cast<int>(current_time);

            try {
                files_map.get(file_name);
                cout << "FILE ALREADY EXISTS" << endl;
                continue;
            } catch (const std::out_of_range& e) {
                Tree* new_tree = new Tree();
                files_map.insert(file_name, new_tree);
                new_tree->create(initial_message, current_time);
                modi_heap.insert(file_name, t_int);
                size_heap.insert(file_name, 0);
                cout << "FILE CREATED" << endl;
            }

        } else if (cmd == "READ") {
            string file_name;
            iss >> file_name;

            try {
                files_map.get(file_name);
            } catch (const std::out_of_range& e) {
                cout << "FILE NOT FOUND" << endl;
                continue;
            }
            Tree* tree = files_map.get(file_name);
            cout << tree->read() << endl;
        } else if (cmd == "INSERT") {
            string file_name;
            iss >> file_name;
            string content;
            getline(iss, content);
            if (!content.empty() && content[0] == ' ') {
                content.erase(0, 1);
            }
            try {
                files_map.get(file_name);
            } catch (const std::out_of_range& e) {
                cout << "FILE NOT FOUND" << endl;
                continue;
            }

            Tree* tree = files_map.get(file_name);
            tree->insert(content);

            time_t current_time = time(nullptr);
            int t_int = static_cast<int>(current_time);
            modi_heap.update(file_name, t_int);
            size_heap.update(file_name, tree->get_version_count());
            cout << "INSERTED" << endl;
        } else if (cmd == "UPDATE") {
            string file_name;
            iss >> file_name;
            string content;
            getline(iss, content);
            if (!content.empty() && content[0] == ' ') {
                content.erase(0, 1);
            }
            try {
                files_map.get(file_name);
            } catch (const std::out_of_range& e) {
                cout << "FILE NOT FOUND" << endl;
                continue;
            }

            Tree* tree = files_map.get(file_name);
            tree->update(content);

            time_t current_time = time(nullptr);
            int t_int = static_cast<int>(current_time);
            modi_heap.update(file_name, t_int);
            size_heap.update(file_name, tree->get_version_count());
            cout << "UPDATED" << endl;
        } else if (cmd == "SNAPSHOT") {
            string file_name;
            iss >> file_name;
            string message;
            getline(iss, message);
            if (!message.empty() && message[0] == ' ') {
                message.erase(0, 1);
            }
            try {
                files_map.get(file_name);
            } catch (const std::out_of_range& e) {
                cout << "FILE NOT FOUND" << endl;
                continue;
            }
            Tree* tree = files_map.get(file_name);
            tree->snapshot(message);
            cout << "SNAPSHOT CREATED" << endl;
        } else if (cmd == "ROLLBACK") {
            string file_name;
            iss >> file_name;
            int version_id;
            try {
                files_map.get(file_name);
            } catch (const std::out_of_range& e) {
                cout << "FILE NOT FOUND" << endl;
                continue;
            }
            if (iss >> version_id) {
                Tree* tree = files_map.get(file_name);
                tree->rollback(version_id);
            } else {
                Tree* tree = files_map.get(file_name);
                tree->rollback();
            }
            cout << "ROLLED BACK" << endl;
        } else if (cmd == "HISTORY") {
            string file_name;
            iss >> file_name;
            try {
                files_map.get(file_name);
            } catch (const std::out_of_range& e) {
                cout << "FILE NOT FOUND" << endl;
                continue;
            }

            Tree* tree = files_map.get(file_name);
            cout << tree->history();
        } else if (cmd == "RECENT_FILES") {
            int n;
            iss >> n;
            vector<string> recent_files;
            vector<pair<string, int>> temp;
            if (n > modi_heap.get_file_count()) {
                n = modi_heap.get_file_count();
            }
            for (int i = 0; i < n; i++) {

                temp.push_back(modi_heap.get_max());
                recent_files.push_back(modi_heap.get_max().first);
                modi_heap.pop();
            } 
            for (int i = 0; i < n; i++) {
                modi_heap.insert(temp[i].first, temp[i].second);
            }
            for (const string& fname : recent_files) {
                cout << fname << endl;
            }
        } else if (cmd == "BIGGEST_TREES") {
            int n;
            iss >> n;
            vector<string> biggest_trees;
            vector<pair<string, int>> temp;
            if (n > modi_heap.get_file_count()) {
                n = modi_heap.get_file_count();
            }    
            for (int i = 0; i < n; i++) {
                temp.push_back(size_heap.get_max());
                biggest_trees.push_back(size_heap.get_max().first);
                size_heap.pop();
            }
            for (int i = 0; i < n; i++) {
                size_heap.insert(temp[i].first, temp[i].second);
            }
            for (const string& fname : biggest_trees) {
                cout << fname << endl;
            }
        } else if (cmd == "EXIT") {
            break;
        }
    }
            
    return 0;
}
