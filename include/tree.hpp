
#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>

namespace tree {

#define TREE_ITEM_TYPE_VALUE     (0)
#define TREE_ITEM_TYPE_CONTAINER (1)
#define TREE_ITEM_TYPE_POINTER   (2)

class TreeValue {
 public:

};

class TreeItem {
 protected:
  TreeItem *parent;
  TreeItem *root;
  
  std::string name;

  int type;

  union {
    TreeValue value;                 // TREE_ITEM_VALUE
    TreeItem *target;                // TREE_ITEM_POINTER
  } data;

  std::vector<TreeItem> children;  // TREE_ITEM_CONTAINER
  
  std::vector<TreeItem> pointed;     // TREE_ITEM_POINTER

 public:
  TreeItem(std::string name);
  TreeItem find(std::string path);
};

class TreePath {
 protected:
  std::vector<std::string> path;
  
 public:
  TreePath(std::string string);
  void normalize(TreeItem relative);
};

// utility functions

std::vector<std::string> stringToVector(std::string string);
  
}

#endif
