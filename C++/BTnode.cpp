#include "iostream"
#include "vector"

using  namespace std;

struct BTnode
{
    int value;
    BTnode* leftnode = nullptr;
    BTnode* rightnode = nullptr;
};

void OutputTree(BTnode* root, int mode)
{
    if (root == nullptr)
    {
        return;
    }
    switch (mode) {
    case 0://inorder traversal
        {
            cout <<  root->value << " -> ";
            OutputTree(root->leftnode, mode);
            OutputTree(root->rightnode, mode);
            break;
        }
    case 1://preorder traversal
        {
            OutputTree(root->leftnode, mode);
            cout <<  root->value << " -> ";
            OutputTree(root->rightnode, mode);
            break;
        }
    case 2://postorder traversal
        {
            OutputTree(root->leftnode, mode);
            OutputTree(root->rightnode, mode);
            cout <<  root->value << " -> ";
            break;
        }
    }

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
    cout<<"inorder\n"<<endl;
    OutputTree(fa, 0);
    cout<< "end" << endl;
    cout<<"preorder\n"<<endl;
    OutputTree(fa, 1);
    cout<< "end" << endl;
    cout<<"postorder\n"<<endl;
    OutputTree(fa, 2);
    cout<< "end" << endl;
    cout<< endl;
    return 0;
}
