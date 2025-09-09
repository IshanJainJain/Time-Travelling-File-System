#ifndef TREENODE_HPP
#define TREENODE_HPP
#include <string>
#include <ctime>
#include <vector>

class TreeNode {
private:
    int version_id;
    std::string content;
    std::string message;
    std::time_t created_timestamp;
    std::time_t snapshot_timestamp;
    TreeNode* parent;
    std::vector<TreeNode*> children;
    bool varsnapshot;

public:    
    TreeNode(int vid, std::time_t time, TreeNode* parent);
    int get_id();
    std::string read_content();
    std::string read_message();
    std::time_t get_time();
    std::time_t get_snaptime();
    TreeNode* get_parent();
    bool is_snapshot();
    void append(std::string c);
    void replace(std::string c);
    void snapshot(std::string mess, std::time_t time);
    void add_child(TreeNode* child);

};

class Tree {
private:
    TreeNode* root;
    TreeNode* active_version;
    std::vector<TreeNode*> version_map;
    int total_versions;

public:
    Tree();
    void create(std::string initial_message, std::time_t time);
    std::string read();
    void insert(const std::string &c);
    void update(const std::string &c);
    void snapshot(const std::string &mess);
    void rollback(int vid = -1); 
    int get_version_count();
    std::string history();
};

#endif