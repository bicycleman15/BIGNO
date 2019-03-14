#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
#define vi vector<int>
#define pb push_back

//need to add clean function to remove leading zeroes
//everything else working fine till now
//also make division function and mod funcion
//add operator overloading


int Complement(int a){
    return 10-a;
}

bool IfLeftBigOrEqualTo(vi A,vi B)
{
    int a=A.size(),b=B.size();
    if(a>b) return true;
    if(a<b) return false;
    for(int i=0;i<a;i++)
    {
        if(A[i]>=B[i]) continue;
        return false;
    }
    return true;
}

vi ADD(vi A,vi B)
{
    vi C;
    int a=A.size(),b=B.size();
    int i=a-1,j=b-1;int c=0;
    
    while(j>=0 and i>=0)
    {
        int t=A[i]+B[j]+c;
        c=0;
        C.pb(t%10);
        c=t/10;
        i--,j--;
    }
    
    while(i>=0)
    {
        int t=A[i]+c;
        c=0;
        C.pb(t%10);
        c=t/10;
        i--;
    }
    
    while(j>=0)
    {
        int t=B[j]+c;
        c=0;
        C.pb(t%10);
        c=t/10;
        j--;
    }
    
     while(c>0){
        C.pb(c%10);
        c /= 10;
    }
    
    for(i=0,j=C.size()-1;i<=j;i++,j--) swap(C[i],C[j]);
    return C;
    
}

vi SUB(vi A,vi B) //A >= B always
{
    vi C;
    int a=A.size(),b=B.size();
    int i=a-1,j=b-1;int c=0;
    
    while(j>=0)
    {
        if(A[i]>=B[j]+c){
            C.pb(A[i]-B[j]-c);
            c=0;
        }
        else
        {
            
            C.pb(A[i]+Complement(B[j]+c));
            c=1;
        }
        i--,j--;
    }
    
    while(i>=0)
    {   
        C.pb(A[i]-c);
        c=0;
        i--;
    }
    
    for(i=0,j=C.size()-1;i<=j;i++,j--) swap(C[i],C[j]);
    return C;
    
}


vi MUL(vi A,int x)
{
    int a=A.size(); vi C; 
    int c=0;
    
    for(int i=a-1;i>=0;i--)
    {
        int t=A[i]*x;
        t += c; 
        c=0;
        if(t>=10) c=t/10;
        C.pb(t%10);
    }
    
    while(c>0){
        C.pb(c%10);
        c /= 10;
    }
    
    
    
    for(int i=0,j=C.size()-1;i<=j;i++,j--) swap(C[i],C[j]);
    return C;
}

vi MUL2(vi A,vi B)
{
    vi C;
    int a=A.size(),b=B.size();
    for(int i=a-1,j=0;i>=0;i--,j++)
    {
        vi T=MUL(B,A[i]);
        
        for(int x=0;x<j;x++) T.pb(0);
        
        C=ADD(C,T);
    }
    
    return C;
    
}

class BigNo //class used to define big nos using vector
{   public:
    vi v;
    bool IsPos;
    
    BigNo()
    {
        
    }
    
    BigNo(string s,bool sign)
    {
        IsPos=sign;
        for(int i=0;i<s.length();i++) v.pb(s[i]-'0');
    }
    void print()
    {   if(!IsPos)cout<<"-";
        for(int i=0;i<v.size();i++) cout<<v[i];
    }
};

BigNo ADDF(BigNo N,BigNo M)
{
    vi A=N.v;
    vi B=M.v;
    
    if(N.IsPos and M.IsPos)
    {
        BigNo C;
        C.v=ADD(A,B);
        C.IsPos=true;
        return C;
    }
    
    if(!N.IsPos and !M.IsPos)
    {
        BigNo C;
        C.v=ADD(A,B);
        C.IsPos=false;
        return C;
    }
    
    if(N.IsPos and M.IsPos==false)
    {   
        BigNo C;
        if(IfLeftBigOrEqualTo(A,B))
        {
            C.v=SUB(A,B);
            C.IsPos=true;
            return C;
        }
        else
        {
            C.v=SUB(B,A);
            C.IsPos=false;
            return C;
        }
    }
    else
    {
        BigNo C;
        if(IfLeftBigOrEqualTo(A,B))
        {
            C.v=SUB(A,B);
            C.IsPos=false;
            return C;
        }
        else
        {
            C.v=SUB(B,A);
            C.IsPos=true;
            return C;
        }
    }
}

BigNo SUBF(BigNo N,BigNo M)
{
    vi A=N.v;
    vi B=M.v;
    
    if(N.IsPos and M.IsPos)
    {
       BigNo C;
        if(IfLeftBigOrEqualTo(A,B))
        {
            C.v=SUB(A,B);
            C.IsPos=true;
            return C;
        }
        else
        {
            C.v=SUB(B,A);
            C.IsPos=false;
            return C;
        }
    }
    
    if(!N.IsPos and !M.IsPos)
    {
       BigNo C;
        if(IfLeftBigOrEqualTo(A,B))
        {
            C.v=SUB(A,B);
            C.IsPos=false;
            return C;
        }
        else
        {
            C.v=SUB(B,A);
            C.IsPos=true;
            return C;
        }
    }
    
    if(N.IsPos and M.IsPos==false)
    {   
      	BigNo C;
        C.v=ADD(A,B);
        C.IsPos=true;
        return C;
    }
    else
    {
       	BigNo C;
        C.v=ADD(A,B);
        C.IsPos=false;
        return C;
    }
}

BigNo MULF(BigNo N,BigNo M)
{
    vi A=N.v;
    vi B=M.v;
    
    if((N.IsPos and M.IsPos) or (!N.IsPos and !M.IsPos))
    {
        BigNo C;
        C.v=MUL2(A,B);
        C.IsPos=true;
        return C;
    }
    else
    {
       BigNo C;
        C.v=MUL2(A,B);
        C.IsPos=false;
        return C; 
    }
}

int main() {

	BigNo A("2545000786803324234",true);  	//enter the two nos here, first argument is for the string of the number and the second is to 
				//handle positive or negative,true for positive and false for negative
	BigNo B("2342343453453459234",false);   //MULF is for the multiplication,ADDF is for the addition,SUBF(A,B)=A-B is for subtraction
	BigNo C=MULF(A,B);
	C.print();
	cout<<endl;
	return 0;
}


