/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"


UnlimitedInt :: UnlimitedInt()
{
    capacity = 10;
    sign=0;
    size=1;
    unlimited_int = new int[capacity];
}

UnlimitedInt :: UnlimitedInt(string s)
{
    if(s[0]=='-')
    {
        s.erase(0,1);
        sign=-1;
    }
    else 
    {
        sign = 1;
    }
        s.erase(0, s.find_first_not_of('0'));
        size= s.size();
        if(!size)
        {
            s="0";
            size=1;
        } 
        // if (size%8==0) capacity=size/8;
        // else capacity=(size/8)+1;
        capacity=size;
        unlimited_int = new int[capacity];
        for(int i=0;i<capacity;i++)
    	{
            unlimited_int[i]=int(s[size-i-1])-48;
		    // m=0;
            // if(i>=8)
            // {
            //     int j=7;
            //     while(j>-1)
            //     {
            //         m=10*m+int(s[i-j-1])-48;
            //         j--;
            //     }
            //     i-=8;
            // }
            // else
            // {
            //     int j=0;
            //     while(i>0)
            //     {
            //         m=10*m+int(s[j])-48;
            //         j++;
            //         i--;
            //     }
            //     unlimited_int[ctr]=m;
            //     if (m==0) zero=(zero && true);
            //     else zero=(zero && false);
            //     break;
            // }
            // unlimited_int[ctr]=m;
            // if (m==0) zero=(zero && true);
            // else zero=(zero && false);
            // ctr++;
	    }
}

UnlimitedInt:: UnlimitedInt(int j)
{
    string s=std::to_string(j);
    if(s[0]=='-')
    {
        s.erase(0,1);
        sign=-1;
    }
    else 
    {
        sign = 1;
    }
        s.erase(0, s.find_first_not_of('0'));
        size= s.size();
        if(!size)
        {
            s="0";
            size=1;
        } 
        // if (size%8==0) capacity=size/8;
        // else capacity=(size/8)+1;
        capacity=size;
        unlimited_int = new int[capacity];
        for(int i=0;i<capacity;i++)
    	{
            unlimited_int[i]=int(s[size-i-1])-48;
		    // m=0;
            // if(i>=8)
            // {
            //     int j=7;
            //     while(j>-1)
            //     {
            //         m=10*m+int(s[i-j-1])-48;
            //         j--;
            //     }
            //     i-=8;
            // }
            // else
            // {
            //     int j=0;
            //     while(i>0)
            //     {
            //         m=10*m+int(s[j])-48;
            //         j++;
            //         i--;
            //     }
            //     unlimited_int[ctr]=m;
            //     if (m==0) zero=(zero && true);
            //     else zero=(zero && false);
            //     break;
            // }
            // unlimited_int[ctr]=m;
            // if (m==0) zero=(zero && true);
            // else zero=(zero && false);
            // ctr++;
	    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz)
{
    unlimited_int=ulimited_int;
    capacity=cap;
    sign=sgn;
    size=sz;
}

UnlimitedInt::~UnlimitedInt()
{
    delete[] unlimited_int;
}

int UnlimitedInt::get_size()
{
    return size;
}

int* UnlimitedInt::get_array()
{
    return unlimited_int;
}

int UnlimitedInt::get_sign()
{
    return sign;
}

int UnlimitedInt::get_capacity()
{
    return capacity;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2)
{
    if(i1->sign==-1 && i2->sign==1)     //-i1+i2
    {
        i1->sign = 1;
        UnlimitedInt* i3=sub(i2,i1);
        i1->sign = -1;
        return i3;
    }
    if(i1->sign ==1 && i2->sign==-1)   //i1+(-i2)
    {
        i2->sign = 1;
        UnlimitedInt* i3=sub(i1,i2);
        i2->sign = -1;
        return i3;
    }

    //this part evaluates => i1+i2 or -i1+(-i2)
    string s="",ss="";
    int idx(0),carry(0);
    while (true)
    {
        if(idx<i1->capacity && idx <i2->capacity)
        {
            int temp=i1->unlimited_int[idx]+i2->unlimited_int[idx]+carry;
            // std::cout<<i1->unlimited_int[idx]<<std::endl;
            // std::cout<<i2->unlimited_int[idx]<<std::endl;
            // std::cout<<carry<<std::endl;
            // std::cout<<temp<<std::endl;
            carry=temp/10;
            temp=temp%10;
            // std::cout<<carry<<std::endl;
            // std::cout<<temp<<std::endl;
            ss=std::to_string(temp);
            //ss.insert(ss.begin(), 8 - ss.size(), '0');
            //std::cout<<ss<<std::endl;
            s=ss+s;
            //std::cout<<s<<std::endl;
            idx++;
        }
        else if (idx>=i1->capacity && idx>=i2->capacity)  //both are of equal length
        {
            // s=std::to_string(carry)+s;
            // std::cout<<s<<std::endl;
            break;
        }
        else if (idx>=i1->capacity)  //i1 is shorter in length
        {
             int temp=carry+i2->unlimited_int[idx];
            carry=temp/10;
            temp=temp%10;
            ss=std::to_string(temp);
            //ss.insert(ss.begin(), 8 - ss.size(), '0');
            s=ss+s;
            idx++;
            while(idx<i2->capacity)
            {
                temp=i2->unlimited_int[idx]+carry;
                carry=temp/10;
                temp=temp%10;
                ss=std::to_string(temp);
                //ss.insert(ss.begin(), 8 - ss.size(), '0');
                s=ss+s;
                idx++;
            }
            break;
        }
        else    //i2 is shorter in length 
        {
            int temp=carry+i1->unlimited_int[idx];
            carry=temp/10;
            temp=temp%10;
            ss=std::to_string(temp);
            //ss.insert(ss.begin(), 8 - ss.size(), '0');
            s=ss+s;
            idx++;
            while(idx<i1->capacity)
            {
                temp=i1->unlimited_int[idx]+carry;
                carry=temp/10;
                temp=temp%10;
                ss=std::to_string(temp);
                //ss.insert(ss.begin(), 8 - ss.size(), '0');
                s=ss+s;
                idx++;
            }
            break;
        }
    }
    s=std::to_string(carry)+s;
    //std::cout<<s<<std::endl;
    if(i1->sign==-1 && i2->sign==-1) s="-"+s;   //add minus sign for -i1+(-i2) 
    UnlimitedInt* i3=new UnlimitedInt(s);
    return i3;
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2)
{
    if(i1->sign==-1 && i2->sign==1)     //-i1-i2
    {
        i2->sign=-1;
        UnlimitedInt* i3= add(i1,i2);
        i2->sign=1;
        return i3;
    }
    if (i1->sign==1 && i2->sign==-1)    // i1-(-i2)
    {
        i2->sign=1;
        UnlimitedInt* i3 = add(i1,i2);
        i2->sign=-1;
        return i3;
    }
    int idx(0),temp(0),carry(0);
    bool greater(true);
    if(i1->size >i2->size) greater=true;
    else if (i1->size < i2->size) greater = false;
    else 
    {
        int idx(i1->size-1);
            while(idx>=0)
            {
                if(i1->unlimited_int[idx] < i2->unlimited_int[idx]) 
                {
                    greater = false;
                    break;
                }
                else if(i1->unlimited_int[idx] > i2->unlimited_int[idx])
                {
                    break;
                }
                idx--;
            }
    }
    if(!greater)
    {
        UnlimitedInt* temp=i1;
        i1=i2;
        i2=temp;
    }
    string s="",ss="";
    while(idx<i1->capacity && idx<i2->capacity)
    {
        temp=(i1->unlimited_int[idx]-i2->unlimited_int[idx])-carry;
        if (temp<0)
        {
            if(idx!=i1->capacity-1)
                {
                    temp=10+temp;
                }
            else temp*=(-1);
            
            carry=1;
        }
        else carry=0;
        ss=std::to_string(temp);
        //ss.insert(ss.begin(), 8 - ss.size(), '0');
        s=ss+s;
        idx++;
    }
    if(idx<i1->capacity)
    {
        temp=(i1->unlimited_int[idx]-carry);
        if (temp<0)
        {
            if(idx!=i1->capacity-1)
                {
                    temp=10+temp;
                }
            else temp*=(-1);
            
            carry=1;
        }
        else 
        {
            carry=0;
        }
        ss=std::to_string(temp);
        //ss.insert(ss.begin(), 8 - ss.size(), '0');
        s=ss+s;
        idx++;   
        while(idx<i1->capacity)
        {
            temp=(i1->unlimited_int[idx]-carry);
            if (temp<0)
            {
                if(idx!=i1->capacity-1)
                    {
                        temp=10+temp;
                    }
                else temp*=(-1);
                
                carry=1;
            }
            else {carry=0;}
            ss=std::to_string(temp);
            //ss.insert(ss.begin(), 8 - ss.size(), '0');
            s=ss+s;
            idx++;
        }
    }
    else if(idx<i2->capacity)
    {
        temp=0-i2->unlimited_int[idx]-carry;
        if (temp<0)
        {
            temp=10+temp;
            carry=1;
        }
        else 
        {
            carry=0;
        }
        ss=std::to_string(temp);
        //ss.insert(ss.begin(), 8 - ss.size(), '0');
        s=ss+s;
        carry=1;
        idx++;   
        while(idx<i2->capacity)
        {
            temp=0-i2->unlimited_int[idx]-carry;
            if (temp<0)
            {
                temp=10+temp;
                carry=1;
            }
            else 
            {
                carry=0;
            }
            ss=std::to_string(temp);
            //ss.insert(ss.begin(), 8 - ss.size(), '0');
            s=ss+s;
            idx++;
        }
    }
    UnlimitedInt* i3=new UnlimitedInt(s);
    // if(!greater)
    // {
    //     UnlimitedInt* temp=i1;
    //     i1=i2;
    //     i2=temp;
    // }
    if(i1->sign==1 && i2->sign==1)  //i1-i2
    {
        if(carry==1 || !greater) i3->sign=-1;
    }
    else    //-i1-(-i2)
    {
        if(carry==0 && greater) i3->sign=-1;   
    }
    return i3;
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2)
{
    UnlimitedInt* big;
    UnlimitedInt* small;
    if  (i1->size>i2->size)
    {
        small = i2;
        big=i1;
    }
    else
    {
        small=i1;
        big=i2;
    }
    int idx(0),ctr(0);
    string m=small->to_string();
    if (m[0]=='-') {m.erase(0,1);}
    UnlimitedInt* i4=new UnlimitedInt("0");
    UnlimitedInt* temp;
    UnlimitedInt* resul;
    string s="",ss="";
    for(idx=m.size()-1;idx>-1;idx--)
    {
        int mul=(int(m[idx])-48),idx2(0),res(0),carry(0);
        s="";
        ss="";
            while(idx2<big->size)
            {
                res=(big->unlimited_int[idx2]*mul)+carry;
                carry=res/10;
                res=res%10;
                ss=std::to_string(res);
                //ss.insert(ss.begin(), 8 - ss.size(), '0');
                s=ss+s;
                idx2++;
            }
            s=std::to_string(carry)+s;
            //std::cout<<s<<std::endl;
        s.append(ctr,'0');
        //std::cout<<s<<std::endl;
        temp = new UnlimitedInt(s);
        resul = add(temp,i4);
        //std::cout<<i3->to_string()<<std::endl;
        ctr++;
        i4->~UnlimitedInt();
        temp->~UnlimitedInt();
        i4=resul;
    }
    if ((big->sign==1 && small->sign==1) || (big->sign==-1 && small->sign==-1)) i4->sign=1;
    else i4->sign=-1;
    return i4;
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2)
{
    int pow(0);
    bool greater(true),terminate(false);
    UnlimitedInt* i3= new UnlimitedInt("0");
    UnlimitedInt* cnst=new UnlimitedInt("2");
    if(i1->size >i2->size) greater=true;
    else if (i1->size < i2->size) greater = false;
    else 
    {
        int idx(i1->size-1);
                while(idx>=0)
                {
                    if(i1->unlimited_int[idx] < i2->unlimited_int[idx]) 
                    {
                        greater = false;
                        break;
                    }
                    else if(i1->unlimited_int[idx] > i2->unlimited_int[idx])
                    {
                        break;
                    }
                    idx--;
                }
    }
    if(!greater) return i3;     //numerator is less than denominator;
    UnlimitedInt* temp1 = new UnlimitedInt(i1->to_string());
    temp1->sign=1;
    do
    {
        pow=0;
        UnlimitedInt* mf=new UnlimitedInt("1");
        UnlimitedInt* temp2 = new UnlimitedInt(i2->to_string());
        UnlimitedInt* temp=temp2;
        temp2->sign=1;
        while(greater)
        {
            if (pow!=0) temp=mul(temp2,cnst);
            // std::cout<<temp->to_string()<<std::endl;
            if(temp1->size >temp->size) greater=true;
            else if (temp1->size < temp->size) greater = false;
            else 
            {
                int idx(temp1->size-1);
                while(idx>=0)
                {
                    if(temp1->unlimited_int[idx] < temp->unlimited_int[idx]) 
                    {
                        greater = false;
                        break;
                    }
                    else if(temp1->unlimited_int[idx] > temp->unlimited_int[idx])
                    {
                        idx=-1;
                        break;
                    }
                    idx--;
                }
                if (idx==0) greater=false;
            }
            if(greater && pow!=0)
            {
                temp2->~UnlimitedInt();
                temp2=temp;
                temp=mul(mf,cnst);
                mf->~UnlimitedInt();
                //std::cout<<temp->to_string()<<std::endl;
                mf=temp;
            }
            else if (!greater)
            {
                if (pow==0)
                {
                    terminate=true;
                    break;
                }
                temp->~UnlimitedInt();
                //std::cout<<temp1->to_string()<<std::endl;
                temp=sub(temp1,temp2);
                //std::cout<<temp2->to_string()<<std::endl;
                temp1->~UnlimitedInt();
                temp1=temp;
                
            }
            pow++;
        }
    
    if(!terminate)
    {
    delete temp2;
    // std::cout<<"terminater"<<std::endl;
    // std::cout<<i3->to_string()<<std::endl;
    // std::cout<<mf->to_string()<<std::endl;
    temp2=add(i3,mf);
    delete i3;
    i3=temp2;
    greater=true;}
    } while (!terminate);
    if(i1->sign==1&&i2->sign==1 || i1->sign==-1 && i2->sign==-1) i3->sign=1;
    else 
    {
        i3->sign=-1;
        UnlimitedInt* ii= new UnlimitedInt("1");
        if(temp1->to_string()!="0")
        {
        UnlimitedInt* ans=sub(i3,ii);
        i3->~UnlimitedInt();
        ii->~UnlimitedInt();
        i3=ans;
        }
    }

    return i3;
    
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2)
{
    int pow(0);
    bool greater(true),terminate(false);
    UnlimitedInt* i3= new UnlimitedInt("0");
    UnlimitedInt* cnst=new UnlimitedInt("2");
    if(i1->size >i2->size) greater=true;
    else if (i1->size < i2->size) greater = false;
    else 
    {
        int idx(i1->size-1);
                while(idx>=0)
                {
                    if(i1->unlimited_int[idx] < i2->unlimited_int[idx]) 
                    {
                        greater = false;
                        break;
                    }
                    else if(i1->unlimited_int[idx] > i2->unlimited_int[idx])
                    {
                        break;
                    }
                    idx--;
                }
    }    //numerator is less than denominator;
    UnlimitedInt* temp1 = new UnlimitedInt(i1->to_string());
    temp1->sign=1;
    do
    {
        pow=0;
        UnlimitedInt* mf=new UnlimitedInt("1");
        UnlimitedInt* temp2 = new UnlimitedInt(i2->to_string());
        UnlimitedInt* temp=temp2;
        temp2->sign=1;
        while(greater)
        {
            if (pow!=0) temp=mul(temp2,cnst);
            //std::cout<<temp->to_string()<<std::endl;
            if(temp1->size >temp->size) greater=true;
            else if (temp1->size < temp->size) greater = false;
            else 
            {
                int idx(temp1->size-1);
                while(idx>=0)
                {
                    if(temp1->unlimited_int[idx] < temp->unlimited_int[idx]) 
                    {
                        greater = false;
                        break;
                    }
                    else if(temp1->unlimited_int[idx] > temp->unlimited_int[idx])
                    {
                        idx++;
                        break;
                    }
                    idx--;
                }
                if (idx==0) greater=false;
            }
            if(greater && pow!=0)
            {
                temp2->~UnlimitedInt();
                temp2=temp;
                temp=mul(mf,cnst);
                mf->~UnlimitedInt();
                //std::cout<<temp->to_string()<<std::endl;
                mf=temp;
            }
            else if (!greater)
            {

                if (pow==0)
                {
                    terminate=true;
                    break;
                }
                temp->~UnlimitedInt();
                //std::cout<<temp2->to_string()<<std::endl;
                temp=sub(temp1,temp2);
                //std::cout<<temp->to_string()<<std::endl;
                temp1->~UnlimitedInt();
                temp1=temp;
            }
            pow++;
        }
    
    if(!terminate)
    {
    delete temp2;
    // std::cout<<"terminater"<<std::endl;
    // std::cout<<i3->to_string()<<std::endl;
    // std::cout<<mf->to_string()<<std::endl;
    //temp2=add(i3,mf);
    //delete i3;
    //i3=temp2;
    greater=true;}
    } while (!terminate);

    i3=temp1;
    if(i1->sign==1&&i2->sign==1 || i1->sign==-1 && i2->sign==-1) i3->sign=1;
    else i3->sign=-1;

    return i3;
    
}

string UnlimitedInt::to_string()
{
    string s="",ss="";
    int idx(0);
    while (idx<capacity)
    {
        ss=std::to_string(unlimited_int[idx]);
        //ss.insert(ss.begin(), 8-ss.size(),'0');
        s=ss+s;
        idx++;
    }
    //s.erase(0, s.find_first_not_of('0'));
    if(s=="0") return "0";
    if (sign==-1) s="-"+s;
    return s;
}

// #include<iostream>
// using namespace std;
// int main()
// {
//     UnlimitedInt* a = new UnlimitedInt("86");
//     UnlimitedInt* b = new UnlimitedInt("1");
//     UnlimitedInt* c = UnlimitedInt:: mul(a,b);
//     delete a;
//     cout<<c->to_string()<<endl;
// }