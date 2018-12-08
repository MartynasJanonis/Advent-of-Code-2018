#include <fstream>
#include <stack>
#include <vector>
#include <iostream>

// TODO: find an iterative solution

struct Node {
    std::vector<int> metadata;
    std::vector<Node> children;
};

Node buildTree(std::ifstream& input)
{
    Node n;
    int children, metadata_count;
    input >> children >> metadata_count;
    while (children--) {
        n.children.push_back(buildTree(input));
    }
    while (metadata_count--) {
        int val;
        input >> val;
        n.metadata.push_back(val);
    }
    return n;
}

int get_value(Node n){
    int val = 0;
    if(n.children.size()==0){
        for(int x : n.metadata){
            val += x;
        }
        return val;
    }
    else{
        for(int x : n.metadata){
            if(x<=n.children.size()){
                val += get_value(n.children[x-1]);
            }
        }
    }
    return val;
}

int main()
{
    std::ifstream input{"day8.in"};
    std::ofstream output{"day8-2.out"};
    int result = 0;
    Node root = buildTree(input);
    result = get_value(root);
    output << result;

}