
#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>

#define TREE_ITEM_TYPE_VALUE     (0)
#define TREE_ITEM_TYPE_CONTAINER (1)
#define TREE_ITEM_TYPE_POINTER   (2)

class TreeValue {
 public:
  
};

class TreeItem {
 public:
  TreeItem *parent;
  
  std::string name;

  int type;

  union {
    TreeValue value;                 // TREE_ITEM_VALUE
    TreeItem *target;                // TREE_ITEM_POINTER
  } data;

  std::vector<TreeItem> children;  // TREE_ITEM_CONTAINER
  
  std::vector<TreeItem> pointed;     // TREE_ITEM_POINTER
  
  TreeItem(std::string name);
};

#endif
