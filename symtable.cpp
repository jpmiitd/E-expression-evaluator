/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
SymbolTable::SymbolTable()
{
    size=0;
    root=nullptr;
}

void pot(SymEntry* root)
{
    if (root) 
    {
        pot(root->left);
        if(root->left)    delete root->left;
        pot(root->right);
        if(root->right) delete root->right;
        return;
    }
    else return;
}

SymbolTable::~SymbolTable()
{
    pot(root);
    if(!root)
    {
        delete root;
    }
}

void SymbolTable::insert(string k, UnlimitedRational* v)
{
    if(root==nullptr)   //root is null
    {
        root = new SymEntry(k,v);
        root->left=nullptr;
        root->right=nullptr;
        return;
    }
    else
    {
        SymEntry* temp = root;
        SymEntry* prev = nullptr;
        while(temp!=nullptr)
        {
            if(temp->key>k)
            {
                prev=temp;
                temp=temp->left;
            }
            else
            {
                prev=temp;
                temp=temp->right;
            }
        }
        SymEntry* node = new SymEntry(k,v);
        if(prev->key>k)
        {
            prev->left=node;
        }
        else
        {
            prev->right=node;
        }
    }
}

void SymbolTable::remove(string k)
{
        SymEntry* temp(root);
        SymEntry* temp_prev(nullptr);
        while(temp!=nullptr)
        {
            if(temp->key>k) {temp_prev=temp; temp=temp->left;}
            else if (temp->key<k) {temp_prev=temp; temp=temp->right;}
            else if (temp->key==k)
            {
                if (temp->left==nullptr && temp->right==nullptr)    //leaf node
                {
                    if(temp==root)
                    {
                        root=nullptr;
                        size=0;
                        delete temp;
                        //return nullptr;
                    }
                    else
                    {
                        if(temp_prev->left==temp)    //leaf node + left child
                        {
                            temp_prev->left=nullptr;
                            delete temp;
                            size--;
                            //return root;
                        }
                        else if(temp_prev->right==temp)  //leaf node + right child
                        {
                            temp_prev->right=nullptr;
                            delete temp;
                            size--;
                            //return root;
                        }
                    }
                }
                else if(temp->left!=nullptr)    //left subtree exists
                {
                    SymEntry* scsr(temp->left);
                    SymEntry* scsr_prev(nullptr);
                   while(scsr->right!=nullptr)
                   {
                       scsr_prev=scsr;
                       scsr=scsr->right;
                   } 
                   if(scsr_prev==nullptr)   //subtree has only one node or no right nodes
                   {
                       if(temp_prev==nullptr)   //root node
                       {
                           scsr->right=temp->right;
                           //scsr->left=temp->left;
                           delete temp;
                           size--;
                           //return scsr;
                       }
                       else if(temp_prev->right==temp)
                       {
                           temp_prev->right=scsr;
                           scsr->right=temp->right;
                           delete temp;
                           size--;
                           //return root;
                       }
                       else if(temp_prev->left==temp)
                       {
                           temp_prev->left=scsr;
                           scsr->right=temp->right;
                           delete temp;
                           size--;
                           //return root;
                       }
                   }
                   else     //subtree has more than one right nodes;
                   {
                       scsr_prev->right=scsr->left;
                       //scsr_prev->left=scsr->left;
                       if(temp_prev==nullptr)   //root node
                       {
                           scsr->right=temp->right;
                           scsr->left=temp->left;
                           delete temp;
                           size--;
                           //return scsr;
                       }
                       else if(temp_prev->right==temp)
                       {
                           temp_prev->right=scsr;
                           scsr->right=temp->right;
                           scsr->left=temp->left;
                           delete temp;
                           size--;
                           //return root;
                       }
                       else if(temp_prev->left==temp)
                       {
                           temp_prev->left=scsr;
                           scsr->right=temp->right;
                           scsr->left=temp->left;
                           delete temp;
                           size--;
                           //return root;
                       }
                   }
                }
                else    //right subtree exists
                {
                    SymEntry* scsr(temp->right);
                    SymEntry* scsr_prev(nullptr);
                   while(scsr->left!=nullptr)
                   {
                       scsr_prev=scsr;
                       scsr=scsr->left;
                   } 
                   if(scsr_prev==nullptr)   //subtree has only one node or no left nodes
                   {
                       if(temp_prev==nullptr)   //root node
                       {
                           //scsr->right=temp->right;
                           scsr->left=temp->left;
                           delete temp;
                           size--;
                           //return scsr;
                       }
                       else if(temp_prev->right==temp)
                       {
                           temp_prev->right=scsr;
                           scsr->left=temp->left;
                           delete temp;
                           size--;
                           //return root;
                       }
                       else if(temp_prev->left==temp)
                       {
                           temp_prev->left=scsr;
                           scsr->left=temp->left;
                           delete temp;
                           size--;
                           //return root;
                       }
                   }
                   else     //subtree has more than one left nodes;
                   {
                       scsr_prev->left=scsr->right;
                       //scsr_prev->right=scsr->right;
                       if(temp_prev==nullptr)   //root node
                       {
                           scsr->right=temp->right;
                           scsr->left=temp->left;
                           delete temp;
                           size--;
                           //return scsr;
                       }
                       else if(temp_prev->right==temp)
                       {
                           temp_prev->right=scsr;
                           scsr->right=temp->right;
                           scsr->left=temp->left;
                           delete temp;
                           size--;
                           //return root;
                       }
                       else if(temp_prev->left==temp)
                       {
                           temp_prev->left=scsr;
                           scsr->right=temp->right;
                           scsr->left=temp->left;
                           delete temp;
                           size--;
                           //return root;
                       }
                   }
                }
            }
        }
        //return root;
}

UnlimitedRational* SymbolTable::search(string k)
{
    SymEntry* temp(root);
    while(temp->key!=k)
    {
        if(temp->key>k)
        {
            temp=temp->left;
        }
        else
        {
            temp=temp->right;
        }
    }
    return temp->val;
}

int SymbolTable::get_size()
{
    return size;
}

SymEntry* SymbolTable::get_root()
{
    return root;
}
