/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
ExprTreeNode::ExprTreeNode()
{
    val=nullptr;
    left = nullptr;
    right= nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v)// Can be "ADD", "SUB", "MUL", "DIV", "MOD", "VAL" or "VAR" (for variable)
{
    val=nullptr;
    left = nullptr;
    right= nullptr;
    if(t=="+")  type="ADD";
    else if(t=="-") type="SUB";
    else if(t=="*") type="MUL";
    else if(t=="/") type="DIV";
    else if(t=="%") type="MOD";
    else if(t[0]=='-' || isdigit(t[0])) 
    {
        type="VAL";
        UnlimitedInt* cnst = new UnlimitedInt("1");
        val=new UnlimitedRational(v,cnst);
    }
    else
    {
        type="VAR";
        UnlimitedInt* cnst = new UnlimitedInt("1");
        val=new UnlimitedRational(v,cnst);
        id=t;
    }
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v)
{
    val=nullptr;
    left = nullptr;
    right= nullptr;
    if(t=="+")  type="ADD";
    else if(t=="-") type="SUB";
    else if(t=="*") type="MUL";
    else if(t=="/") type="DIV";
    else if(t=="%") type="MOD";
    else if(t[0]=='-' || isdigit(t[0])) 
    {
        type="VAL";
        val = v;
    }
    else
    {
        type="VAR";
        val = v;
        id=t;
    }
}

ExprTreeNode::~ExprTreeNode()
{
    if(val!=nullptr)
    {
        delete val;
    }
}
