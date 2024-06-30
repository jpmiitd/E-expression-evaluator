/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
Evaluator::Evaluator()
{
    symtable = new SymbolTable();
}

void pot(ExprTreeNode* root)
{
    if (root) 
    {
        pot(root->left);
        if(root->left)  delete root->left;
        pot(root->right);
        if(root->right) delete root->right;
        return;
    }
    else return;
}

void pot3(ExprTreeNode* root)
{
    if (root) 
    {
        pot3(root->left);    //delete root->left;
        pot3(root->right);   //delete root->right;
        //std::cout<<root->type<<std::endl;
        if(root->type=="VAL")
        {
            //std::cout<<root->evaluated_value->get_frac_str()<<std::endl;
        }
        return;
    }
    else return;
}

Evaluator::~Evaluator()
{
    for(auto i:expr_trees)
    {
        pot(i);     //delete the tree corresponding to root i
        if(i)
        {
            delete i;
        }
    }
    delete symtable;
}

void Evaluator::parse(vector<string> code)
{
    std::vector<ExprTreeNode*> stk;
    ExprTreeNode* root = new ExprTreeNode();
    root->type="ASS";
    UnlimitedInt* cnst = new UnlimitedInt("1");
    UnlimitedInt* cnst2 = new UnlimitedInt("1");
    UnlimitedRational* dumy = new UnlimitedRational(cnst,cnst2);
    ExprTreeNode* variable = new ExprTreeNode(code[0],dumy);
    root->left=variable;
    ExprTreeNode* temp=new ExprTreeNode();
    int sze=code.size();
    root->right=temp;
    stk.push_back(root);
    expr_trees.push_back(root);
    for(int i=2;i<sze;i++)
    {
        if(code[i]=="(")
        {
            ExprTreeNode* left = new ExprTreeNode();
            temp->left=left;
            stk.push_back(temp);
            temp=left;
        }
        else if(code[i]=="+" || code[i]=="-" || code[i]=="/" || code[i]=="*")   //operators
        {
            UnlimitedInt* cnst = new UnlimitedInt("1");
            UnlimitedInt* cnst2 = new UnlimitedInt("1");
            UnlimitedRational* dummmy = new UnlimitedRational(cnst,cnst2);
            ExprTreeNode* rt = new ExprTreeNode(code[i],dummmy);    //create node with operator
            rt->left=temp->left;                                    //link the empty current nodes's left ptr with the operator's
            if(stk.back()->right == temp) stk.back()->right=rt;
            else stk.back()->left=rt;
            delete temp;                                            //free the memory by deleting the empty node
            stk.push_back(rt);                                      //push the operator node in the stack
            ExprTreeNode* right= new ExprTreeNode();                //create empty right node
            rt->right=right;                                        //link the empty right node with the operator node
            temp=right;                                             //set the current location to the empty node on right
        }
        else if(code[i]==")")
        {
            temp=stk.back();
            stk.pop_back();
        }
        else if(code[i][0]=='-' || isdigit(code[i][0]))
        {
            UnlimitedInt* cnst = new UnlimitedInt("1");
            UnlimitedInt* value = new UnlimitedInt(code[i]);
            temp->type="VAL";
            temp->val= new UnlimitedRational(value,cnst);
            temp->evaluated_value=temp->val;
            temp=stk.back();
            stk.pop_back();
        }
        else
        {
            UnlimitedRational* value = symtable->search(code[i]);
            UnlimitedRational* inp = new UnlimitedRational(new UnlimitedInt(value->get_p_str()),new UnlimitedInt(value->get_q_str()));
            ExprTreeNode* rt = new ExprTreeNode(code[i], inp);
            rt->evaluated_value=rt->val;
            if(stk.back()->right == temp) stk.back()->right=rt;     //de-link the temp node from its parent and link the new rt node
            else stk.back()->left=rt;
            delete temp;
            temp=stk.back();
            stk.pop_back();
        }
    }

    //pot3(root);

}

UnlimitedRational* modified_pot(ExprTreeNode* root)
{
        if(root->left && root->right)    
        {
            UnlimitedRational* left = modified_pot(root->left);
            UnlimitedRational* right = modified_pot(root->right);
            if(root->type == "ADD")     root->evaluated_value = UnlimitedRational::add(left,right);
            else if(root->type == "SUB")    root->evaluated_value = UnlimitedRational::sub(left,right);
            else if(root->type == "MUL")    root->evaluated_value = UnlimitedRational::mul(left,right);
            else if(root->type == "DIV")    root->evaluated_value = UnlimitedRational::div(left,right);
            else if(root->type == "MOD")    
            {
                UnlimitedInt* cnst = new UnlimitedInt("1");
                UnlimitedInt* n = new UnlimitedInt(left->get_p_str());
                UnlimitedInt* d = new UnlimitedInt(right->get_p_str());
                UnlimitedInt* ans = UnlimitedInt::mod(n,d);
                root->evaluated_value= new UnlimitedRational(ans,cnst);
                n->~UnlimitedInt();
                d->~UnlimitedInt();
            }
            //std::cout<<root->evaluated_value->get_frac_str()<<std::endl;
            //std::cout<<root->evaluated_value->get_frac_str()<<std::endl;
            //std::cout<<root->evaluated_value->get_frac_str()<<std::endl;
            return root->evaluated_value;
        }
        
        else 
        {
            //std::cout<<root->evaluated_value->get_frac_str()<<std::endl;
            //std::cout<<root->evaluated_value->get_frac_str()<<std::endl;
            return root->evaluated_value;
        }
}

void pot2(ExprTreeNode* root)
{
    if (root) 
    {
        pot2(root->left);    //delete root->left;
        pot2(root->right);   //delete root->right;
        //std::cout<<root->evaluated_value->get_frac_str()<<std::endl;
        return;
    }
    else return;
}

void Evaluator::eval()
{
    ExprTreeNode* root = expr_trees.back();
  
    string key= root->left->id;
    UnlimitedRational* value = modified_pot(root->right);
    UnlimitedRational* inp = new UnlimitedRational(new UnlimitedInt(value->get_p_str()),new UnlimitedInt(value->get_q_str()));
    pot2(root->right);
    symtable->insert(key,inp);
   
}
