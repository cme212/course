/* Given an n-ary tree, return the preorder traversal of its nodes' values.

   Nary-Tree input serialization is represented in their level order traversal, 
   each group of children is separated by the null value (See examples).
 

   Example 1:
       1
      /|\
     3 2 4
    / \
   5   6
   Input: root = [1,null,3,2,4,null,5,6]
   Output: [1,3,5,6,2,4]
   
   Example 2:
          1
      / /   \   \
     2 3    4   5
      / \   |  / \
     6   7  8 9  10
         |  | | 
        11 12 13
         |
        14 
   Input: root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
   Output: [1,2,3,6,7,11,14,4,8,12,5,9,13,10]


   // Definition for a Node.
   struct Node {
     int val;
     vector<Node*> children;

     Node() {}

     Node(int _val) {
         val = _val;
     }

     Node(int _val, vector<Node*> _children) {
         val = _val;
         children = _children;
     }
   };
*/

vector<int> helper(Node* root, vector<int> &vals);
