#include "iostream"
#include "vector"

using  namespace std;

struct BTnode
{
    int value;
    BTnode* leftnode = nullptr;
    BTnode* rightnode = nullptr;
};

void OutputTree(BTnode* root)
{
    if (root == nullptr)
    {
        return;
    }
    cout <<  root->value << " -> ";
    OutputTree(root->leftnode);
    OutputTree(root->rightnode);
}

int main()
{
    BTnode* fa = new BTnode;
    BTnode* fa_l = new BTnode;
    BTnode* fa_r = new BTnode;
    fa_l->value = 1;
    fa_r->value = 2;
    //
    fa->value = 3;
    fa->leftnode = fa_l;
    fa->rightnode = fa_r;
    OutputTree(fa);
    cout<< "end" << endl;
    return 0;
}
