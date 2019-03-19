#include "iostream"
#include "vector"

using  namespace std;

struct BTnode
{
    int value;
    BTnode* leftnode = nullptr;
    BTnode* rightnode = nullptr;
};

BTnode* ReverseTree(BTnode* root)
{
    if (root == nullptr)
    {
        return root;
    }
    root->leftnode = ReverseTree(root->leftnode);
    root->rightnode = ReverseTree(root->rightnode);
    swap(root->leftnode, root->rightnode);
    return root;
}

void OutputTree(BTnode* root, int mode)
{
    if (root == nullptr)
    {
        return;
    }
    switch (mode)
    {
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
        case 3://reverse tree
        {
            root = ReverseTree(root);
            OutputTree(root, 1);
            break;
        }
    }

}

int main()
{
    BTnode* fa = new BTnode;
    BTnode* fa_l = new BTnode;
    BTnode* fa_r = new BTnode;
    BTnode* fa_l_l = new BTnode;
    BTnode* fa_l_r = new BTnode;
    BTnode* fa_r_l = new BTnode;
    BTnode* fa_r_r = new BTnode;

    fa_l->value = 2;
    fa_r->value = 3;
    fa_l_l->value = 4;
    fa_l_r->value = 5;
    fa_r_l->value = 6;
    fa_r_r->value = 7;
    //
    fa->value = 1;
    fa->leftnode = fa_l;
    fa->rightnode = fa_r;
    fa_l->leftnode = fa_l_l;
    fa_l->rightnode = fa_l_r;
    fa_r->leftnode = fa_r_l;
    fa_r->rightnode = fa_r_r;

    cout<<"inorder:"<<endl;
    OutputTree(fa, 0);
    cout<< "end\n" << endl;
    cout<<"preorder:"<<endl;
    OutputTree(fa, 1);
    cout<< "end\n" << endl;
    cout<<"postorder:"<<endl;
    OutputTree(fa, 2);
    cout<< "end\n" << endl;
    cout<<"reverseorder:"<<endl;
    OutputTree(fa, 3);
    cout<< "end\n" << endl;
    cout<< endl;
    return 0;
}
