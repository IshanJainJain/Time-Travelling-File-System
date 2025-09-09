#include "TreeNode.hpp"

TreeNode::TreeNode(int vid, std::time_t time, TreeNode* parent)
{
    this->version_id = vid;
    this->created_timestamp = time;
    this->parent = parent;
    this->varsnapshot = false;
    this->content = "";
}

int TreeNode::get_id()
{
    return version_id;
}

std::string TreeNode::read_content()
{
    return content;
}

std::string TreeNode::read_message()
{
    return message;
}

std::time_t TreeNode::get_time()
{
    return created_timestamp;
}

std::time_t TreeNode::get_snaptime()
{
    return snapshot_timestamp;
}

TreeNode *TreeNode::get_parent()
{
    return parent;
}

bool TreeNode::is_snapshot()
{
    return varsnapshot;
}

void TreeNode::append(std::string c)
{
    content += c;
}

void TreeNode::replace(std::string c)
{
    content = c;
}

void TreeNode::snapshot(std::string mess, std::time_t time)
{
    varsnapshot = true;
    message = mess;
    snapshot_timestamp = time;
}

void TreeNode::add_child(TreeNode *child)
{
    children.push_back(child);
}

Tree::Tree()
{
    root = nullptr;
    active_version = nullptr;
    total_versions = 0;
}

void Tree::create(std::string initial_message, std::time_t time)
{
    if (root != nullptr) return;

    TreeNode* newnode = new TreeNode(0, time, nullptr);
    root = newnode;
    active_version = root;
    version_map.push_back(root);
    total_versions = 1;
    root->snapshot(initial_message, time);
    return;
}

std::string Tree::read()
{
    if (active_version != nullptr) {
        return active_version->read_content();
    }
    return "";
}

void Tree::insert(const std::string &c)
{
    if (active_version != nullptr) {
        if (active_version->is_snapshot()) {
            TreeNode* newnode = new TreeNode(this->total_versions, std::time(nullptr), active_version);
            active_version->add_child(newnode);
            newnode->replace(active_version->read_content());
            newnode->append(c);
            active_version = newnode;
            version_map.push_back(newnode);
            total_versions++;
        } else {
            active_version->append(c);
        }
        return;
        }
    return;
    }

void Tree::update(const std::string &c)
{
    if (active_version != nullptr) {
        if (active_version->is_snapshot()) {
            TreeNode* newnode = new TreeNode(total_versions, std::time(nullptr), active_version);
            active_version->add_child(newnode);
            newnode->replace(c);
            active_version = newnode;
            version_map.push_back(newnode);
            total_versions++;
        } else {
            active_version->replace(c);
        }
        return;
    }
    return;
}

void Tree::snapshot(const std::string &mess)
{
    if (active_version != nullptr && !active_version->is_snapshot()) {
        active_version->snapshot(mess, std::time(nullptr));
    }
    return;
}

void Tree::rollback(int vid)
{
    if (vid == -1) {
        if (active_version != nullptr && active_version->get_parent() != nullptr) {
            active_version = active_version->get_parent();
        }
        return;
    } else {
        if (vid < 0 || vid >= total_versions) return;
        TreeNode* target = version_map[vid];
        if (target != nullptr) {
            active_version = target;
        }
        return;
    }
}

int Tree::get_version_count()
{
    return total_versions;
}

std::string Tree::history() {
    TreeNode* curr = active_version;
    if (active_version->is_snapshot() == false) {
        curr = active_version->get_parent();
    }
    std::string hist = "";

    while (curr != nullptr) {
        std::time_t snap = curr->get_snaptime();
        std::string timestr = std::ctime(&snap);
        if (!timestr.empty() && timestr.back() == '\n') {
            timestr.pop_back();
        }

        hist += "Version " + std::to_string(curr->get_id()) +
                " (" + timestr + ")" +
                ": " + curr->read_message() + "\n";

        curr = curr->get_parent();
    }

    return hist;
}
