/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
#include "ulimitedint.h"
UnlimitedInt* gcd(UnlimitedInt* a, UnlimitedInt* b)
{
    UnlimitedInt* c;
    UnlimitedInt* big;
    UnlimitedInt* small;
    string sa=a->to_string();
    
    if (sa[0]=='-')
    {
        sa.erase(0,1);
    }
    string sb=b->to_string();
    if (sb[0]=='-')
    {
        sb.erase(0,1);
    }
    if(sa.size()>sb.size())
    {
        big=new UnlimitedInt(a->to_string());
        small=new UnlimitedInt(b->to_string());;
    }
    else if (sa.size()<sb.size())
    {
        big=new UnlimitedInt(b->to_string());;
        small=new UnlimitedInt(a->to_string());
    }
    else
    {
        int idx=0;
        while (idx<sa.size())
        {
            if(sa[idx]<sb[idx])
            {
                
                big=new UnlimitedInt(b->to_string());;
                small=new UnlimitedInt(a->to_string());
                break;
            }
            else if(sa[idx]>sb[idx])
            {
                
                big=new UnlimitedInt(a->to_string());;
                small=new UnlimitedInt(b->to_string());
                break;
            }
            else idx++;
        }
        if(idx==sa.size())
        {
            big=new UnlimitedInt(a->to_string());
            small=new UnlimitedInt(b->to_string());;
        }
    }
    c=UnlimitedInt::mod(big,small);
    big=small;
    small=c;
    while(c->to_string()!="0")
    {
        c=UnlimitedInt::mod(big,small);
        big->~UnlimitedInt();
        big=small;
        small=c;
    }
    delete small;
    return big;
}

UnlimitedRational::UnlimitedRational()
{
    p= new UnlimitedInt(0);
    q= new UnlimitedInt(1);
}
UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den)
{
    if(den->to_string()=="1")
    {
        p=num;
        q=den;
    }
    else if(num->to_string()!="0" && den->to_string()!="0")
    {
        UnlimitedInt* GCD=gcd(num,den);
        if (GCD->to_string()=="1" ||GCD->to_string()=="-1" )
        {
            p=num;
            q=den;
        }
        else
        {
            p=UnlimitedInt::div(num,GCD);
            q=UnlimitedInt::div(den,GCD);
            delete num;
            delete den;
        }
    }
    else if(den->to_string()!="0")
    {
        if(num->to_string()!="0")
        {
            p=num;
            q=den;
        }
        else
        {
            p=num;
            q=new UnlimitedInt("1");
        }

    }
    else
    {
        p=new UnlimitedInt("0");
        q=den;
    }
}
UnlimitedRational::~UnlimitedRational()
{
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p()
{
    return p;
}
UnlimitedInt* UnlimitedRational::get_q()
{
    return q;
}
string UnlimitedRational::get_p_str()
{
    return p->to_string();
}
string UnlimitedRational::get_q_str()
{
    return q->to_string();
}
string UnlimitedRational::get_frac_str()
{
    string n=p->to_string();
    n+="/";
    n+= q->to_string();
    return n;
}

bool is_equal(UnlimitedInt* A, UnlimitedInt* B)
{
    string a=A->to_string();
    string b=B->to_string();
    if(a.size()!=b.size())
    {
        return false;
    }
    for (int i=a.size();i>=0;i--)
    {
        if(a[i]!=b[i])
        {
            return false;
        }
    }
    return true;
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2)
{
    if(is_equal(i1->q,i2->q))
    {
        UnlimitedInt* den = new UnlimitedInt(i2->q->to_string());
        UnlimitedRational* i3=new UnlimitedRational(UnlimitedInt::add(i1->p,i2->p),den);
        return i3;
    }
    else
    {
        UnlimitedInt* m_num1=UnlimitedInt::mul(i1->p,i2->q);
        UnlimitedInt* m_num2=UnlimitedInt::mul(i2->p,i1->q);
        UnlimitedInt* m_den=UnlimitedInt::mul(i1->q,i2->q);
        UnlimitedRational* i3=new UnlimitedRational(UnlimitedInt::add(m_num1,m_num2),m_den);
        delete m_num1;
        delete m_num2;
        return i3;
    }
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2)
{
    if(is_equal(i1->q,i2->q))
    {
        UnlimitedInt* den = new UnlimitedInt(i2->q->to_string());
        UnlimitedRational* i3=new UnlimitedRational(UnlimitedInt::sub(i1->p,i2->p),den);
        return i3;
    }
    else
    {
        UnlimitedInt* m_num1=UnlimitedInt::mul(i1->p,i2->q);
        UnlimitedInt* m_num2=UnlimitedInt::mul(i2->p,i1->q);
        UnlimitedInt* m_den=UnlimitedInt::mul(i1->q,i2->q);
        UnlimitedRational* i3=new UnlimitedRational(UnlimitedInt::sub(m_num1,m_num2),m_den);
        delete m_num1;
        delete m_num2;
        return i3;
    }
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2)
{
    UnlimitedRational* i3=new UnlimitedRational(UnlimitedInt::mul(i1->p,i2->p),UnlimitedInt::mul(i1->q,i2->q));
    return i3;
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2)
{
    UnlimitedRational* i3=new UnlimitedRational(UnlimitedInt::mul(i1->p,i2->q),UnlimitedInt::mul(i1->q,i2->p));
    return i3;
}

// #include<iostream>
// using namespace std;
// int main()
// {
//     UnlimitedInt* a = new UnlimitedInt("-1701");
//     UnlimitedInt* b = new UnlimitedInt("86");
//     UnlimitedRational* c = new UnlimitedRational(a,b);

//     UnlimitedInt* e = new UnlimitedInt("39");
//     UnlimitedInt* d = new UnlimitedInt("1");
//     UnlimitedRational* cc = new UnlimitedRational(e,d);

//     cout<<c->get_frac_str()<<endl;
//     cout<<cc->get_frac_str()<<endl;
    
//     UnlimitedRational* ccc = UnlimitedRational::add(c,cc);
//     cout<<ccc->get_frac_str()<<endl;
    
// }
