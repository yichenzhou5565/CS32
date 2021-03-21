#include <iostream>
#include <string>
#include <cassert>
#include <stack>
using namespace std;


bool isStrictlyGreater(char c, char top);
int calculation(string postfix);

int evaluate(string infix, string& postfix, bool& result)
{
    stack<char> trans;
    postfix = "";
    
    if (infix.size()==0)
        return 1;
    
    for (int i=0; i<infix.size(); i++)
    {
        int k=0;
        char c = infix[i];
        
        switch (c)
        {
            case 'T':
            case 'F':
                if (i < infix.size()-1)
                {
                    if (infix[i+1]=='T' || infix[i+1]=='F')
                    {
                        return 1;
                    }
                }
                postfix += c;
                break;
                
            case '(':
                k=i;
                if (k<infix.size()-1)
                {
                    k++; //precede to the character right after '('
                    while (isspace(infix[k]))
                    {
                        k++;
                    }
                    
                    if (k>=infix.size())
                        return 1;
                    
                    if(infix[k]=='&' || infix[k]==')' || infix[k]=='^')
                    {
                        return 1;
                    }
                }
                
                trans.push(c);
                break;
                
            case '!':
                k=i;
                
                if (k<infix.size()-1) //if this is not the last digit
                {
                    k++;
                    while (k<infix.size() && isspace(infix[k]))
                    {
                        k++; //k is the next non space digit of !
                    }
                    
                    
                    if (k==infix.size() ||
                        (infix[k]!='!'&& infix[k]!='T' && infix[k]!='F'&&infix[k]!='('))
                    {
                        return 1;
                    }
                }
                
                
                //if this is the last digit, not valid
                if (k==infix.size()-1 && infix[k]=='!')
                {
                    return 1;
                }
                
                
                
                //cout<<c<<endl;
                while (!trans.empty()
                       && trans.top()!='('
                       && trans.top()!= '!'
                       && !isStrictlyGreater(c, trans.top())
                       )
                {
                    //cout<<"hey";
                    postfix += trans.top();
                    trans.pop();
                }
                //cout<<"hey";
                
                
                
                trans.push(c);
                break;
                
            case '&':
                //if the next digit of & is ), invalid
                //if the previous digit of & is (, invalid
                if (i!=infix.size()-1)
                {
                    k=i+1;
                    while (k<infix.size()-1 && isspace(infix[k]))
                        k++; //k is at next non-space digit of infix
                    if (k==infix.size()-1 && (infix[k]=='^'||infix[k]=='&'))
                        return 1;
                    if (infix[k]==')')
                        return 1;
                }
                
                if (i!=0)
                {
                    k=i-1;
                    while (k>=1 && isspace(infix[k]))
                        k--; //k is at previous non-space digit of infix
                    if (k==0 && (infix[k]=='^'||infix[k]=='&'))
                        return 1;
                    if (infix[k]=='(')
                        return 1;
                }
                
                
                
                while (!trans.empty()
                       && trans.top()!='('
                       && !isStrictlyGreater(c, trans.top()))
                {
                    //cout<<"hey";
                    postfix += trans.top();
                    trans.pop();
                }
                trans.push(c);
                break;
                
                
            case '^':
                if (i!=infix.size()-1)
                {
                    k=i+1;
                    while (k<infix.size()-1 && isspace(infix[k]))
                        k++; //k is at next non-space digit of infix
                    if (k==infix.size()-1 && (infix[k]=='^'||infix[k]=='&'))
                        return 1;
                    if (infix[k]==')')
                        return 1;
                }
                
                if (i!=0)
                {
                    k=i-1;
                    while (k>=1 && isspace(infix[k]))
                        k--; //k is at previous non-space digit of infix
                    if (k==0 && (infix[k]=='^'||infix[k]=='&'))
                        return 1;
                    if (infix[k]=='(')
                        return 1;
                }
                
                while (!trans.empty()
                       && trans.top()!='('
                       && !isStrictlyGreater(c, trans.top())
                       )
                {
                    postfix += trans.top();
                    trans.pop();
                }
                trans.push(c);
                break;
                
            case ')':
                while (!trans.empty() && trans.top()!='(')
                {
                    postfix += trans.top();
                    trans.pop();
                }
                if (trans.empty()==true)
                    return 1;
                trans.pop();
                
                break;
                
            case ' ':
                break;
                
            default:
                return 1;
        }
    }
    
    //cout<<postfix<<endl;
    
    while (trans.empty()==false)
    {
        //cout<<"last push";
        postfix += trans.top();
        trans.pop();
    }
    
    //cout<<postfix<<endl;
    
    int val = calculation(postfix);
    
    if (val==0)
    {
        result = false;
        return 0;
    }
    
    if (val==1)
    {
        result = true;
        return 0;
    }
    
    return 1;
    
}

bool isStrictlyGreater(char c, char top)
//if c is greater, return true
//if top is greater, return false
{
    int numC=0;
    int numTop=0;
    
    switch(c)
    {
        case '!':
            numC = 3;
            break;
        case '&':
            numC = 2;
            break;
        case '^':
            numC = 1;
            break;
    }
    
    switch(top)
    {
        case '!':
            numTop = 3;
            break;
        case '&':
            numTop = 2;
            break;
        case '^':
            numTop = 1;
            break;
    }
    
    if (numC > numTop)
    {
        //cerr<<"greater"<<endl;
        return true;
    }
    
    else
    {
        //cerr<<"not greater"<<endl;
        return false;
    }
    
}




int calculation(string postfix)
//if T: return 1
//if F: resturn 0
//if more than one thing left: return -1
{
    
    stack<char> operand;
    char result;
    char op1, op2, temp;
    
    for (int i=0; i<postfix.size(); i++)
    {
        char d=postfix[i];
        switch (d)
        {
            case 'T':
            case 'F':
                operand.push(d);
                break;
                
            case '!':
                if (operand.empty()==true)
                    return -1;
                op1 = operand.top();
                operand.pop();
                //cout<<"hey";
                if (op1 == 'T')
                {
                    op1 = 'F';
                }
                else if (op1 == 'F')
                    op1 = 'T';
                operand.push(op1);
                break;
                
            case '&':
                if (operand.empty()==true)
                    return -1;
                op1 = operand.top();
                operand.pop();
                if (operand.empty()==true)
                    return -1;
                op2 = operand.top();
                operand.pop();
                if (op1=='T' && op2=='T')
                    temp = 'T';
                else
                    temp = 'F';
                operand.push(temp);
                break;
                
            case '^':
                if (operand.empty()==true)
                    return -1;
                op1 = operand.top();
                operand.pop();
                if (operand.empty()==true)
                    return -1;
                op2 = operand.top();
                operand.pop();
                if (op1 == op2)
                    temp = 'F';
                else
                    temp = 'T';
                operand.push(temp);
                break;
                
            default:
                return -1;
        }
    }
    
    if (operand.empty()==false)
    {
        result = operand.top();
        operand.pop();
        
        if (operand.empty() == false)
            return -1;
        
        if (result=='T')
            return 1;
        else if (result=='F')
            return 0;
        else
            return -1;
    }
    return -1;
    
    
}


int main()
{
    string s;
    bool answer=true;

    //test cases from spec
    assert(evaluate("T^ F", s, answer) == 0  &&  s == "TF^"  &&  answer);
    assert(evaluate("T^", s, answer) == 1);
    assert(evaluate("F F", s, answer) == 1);
    assert(evaluate("TF", s, answer) == 1);
    assert(evaluate("()", s, answer) == 1);
    assert(evaluate("()T", s, answer) == 1);
    assert(evaluate("T(F^T)", s, answer) == 1);
    assert(evaluate("T(&T)", s, answer) == 1);
    assert(evaluate("(T&(F^F)", s, answer) == 1);
    assert(evaluate("T|F", s, answer) == 1);
    assert(evaluate("", s, answer) == 1);
    assert(evaluate("F  ^  !F & (T&F) ", s, answer) == 0
           &&  s == "FF!TF&&^"  &&  !answer);
    assert(evaluate(" F  ", s, answer) == 0 &&  s == "F"  &&  !answer);
    assert(evaluate("((T))", s, answer) == 0 &&  s == "T"  &&  answer);



    //if the given infix string is valid
    assert(evaluate("T^(F^T)", s, answer)==0
           && s=="TFT^^"
           && answer == false);
    assert(evaluate("T ^(F^T)", s, answer)==0
           && s=="TFT^^"
           && answer == false);

    assert(evaluate("F  ^  !F & (T&F)", s, answer)==0
           && s=="FF!TF&&^"
           && answer == false);
    assert(evaluate("T^(F)", s, answer)==0
           && s=="TF^"
           && answer == true);
    assert(evaluate("T^(!F)", s, answer)==0
           && s=="TF!^"
           && answer == false);
    assert(evaluate("T^T", s, answer)==0
           && s=="TT^"
           && answer == false);
    assert(evaluate("F^F", s, answer)==0
           && s=="FF^"
           && answer == false);
    assert(evaluate("(T&F)", s, answer)==0
           && s=="TF&"
           && answer==false);

//    evaluate("!T", s, answer);
//    cout<<s<<endl;

    assert(evaluate("!T", s, answer)==0
           && s=="T!"
           && answer==false);
    assert(evaluate("!  ! !T", s, answer)==0
           && s=="T!!!"
           && answer==false);


    assert(evaluate("  ! T  ", s, answer)==0
           && s=="T!"
           && answer==false);
    assert(evaluate("!(T&F)", s, answer)==0
            && s=="TF&!"
            && answer==true);
    assert(evaluate("!T&F ", s, answer)==0
           && s=="T!F&"
           && answer==false);
    assert(evaluate("      !  T & F ", s, answer)==0
           && s=="T!F&"
           && answer==false);

    assert(evaluate("T ^ !F", s, answer)==0
           && s=="TF!^"
           && answer==false);
    assert(evaluate("T^F&F", s, answer)==0
           && s=="TFF&^"
           && answer==true);
    assert(evaluate("T&!(F^T&T^F)^!!!(F&T&F)   ", s, answer)==0
           && s=="TFTT&^F^!&FT&F&!!!^"
           && answer==true);

    assert(evaluate("!(F&T&F) ", s, answer)==0
           && s=="FT&F&!"
           && answer==true);


    assert(evaluate("!!T ", s, answer)==0
           && s=="T!!"
           && answer==true);
    assert(evaluate(" ! !T ", s, answer)==0
           && s=="T!!"
           && answer==true);
    assert(evaluate("!!!F", s, answer)==0
           && s=="F!!!"
           && answer == true);
    assert(evaluate("T!!", s, answer)==1
           && answer == true);
    assert(evaluate("T! !", s, answer)==1
           && answer == true);
    assert(evaluate("T!!   ", s, answer)==1
           && answer == true);
    assert(evaluate(" T    !!", s, answer)==1
           && answer == true);
    assert(evaluate("T&F&F&F&F", s, answer)==0
           && s == "TF&F&F&F&"
           && answer == false);
    assert(evaluate("!(!(!T))", s, answer)==0
           && s=="T!!!"
           && answer == false);
    assert(evaluate("T^F^F^F^F^T", s, answer)==0
           && s=="TF^F^F^F^T^"
           && answer==false);
    assert(evaluate("T^F^F^F^(F^T)", s, answer)==0
           && s=="TF^F^F^FT^^"
           && answer==false);
    assert(evaluate("T&F&F&F&(F&T)", s, answer)==0
           && s=="TF&F&F&FT&&"
           && answer==false);
    assert(evaluate("T & F & F & F & ( F & T ) ", s, answer)==0
           && s=="TF&F&F&FT&&"
           && answer==false);








    //if the given infix string is invalid
    answer = false;
    assert(evaluate("TF", s, answer)==1
           && answer == false);
    assert(evaluate(" T F ", s, answer)==1
           && answer == false);
    assert(evaluate("", s, answer) == 1
           && answer == false);
    assert(evaluate("    ", s, answer) == 1
           && answer == false);
    answer = true;
    assert(evaluate("T F", s, answer) == 1
           && answer == true);
    assert(evaluate("()", s, answer) == 1
           && answer == true);
    assert(evaluate(" (   ) ", s, answer) == 1
           && answer == true);
    assert(evaluate("T", s, answer) == 0
           && s == "T"
           && answer == true);
    assert(evaluate("(T)", s, answer) == 0
           && s == "T"
           && answer == true);
    assert(evaluate("T|T", s, answer) == 1
           && answer == true);
    assert(evaluate("T|F", s, answer) == 1
           && answer == true);
    assert(evaluate("F  ^  !F & (T&F)*", s, answer) == 1
           && answer == true);
    assert(evaluate("F % ^  !F & (T&F)", s, answer) == 1
           && answer == true);
    assert(evaluate("F  ^^  !F & (T&F)*", s, answer) == 1
           && answer == true);
    assert(evaluate("F  ^  !F & (T&F)&", s, answer) == 1
           && answer == true);
    assert(evaluate("F  ^  !F && (T&F)", s, answer) == 1
           && answer == true);
    assert(evaluate("F  ^  !F & (T&&F)", s, answer) == 1
           && answer == true);
    assert(evaluate("F  ^  !F & (T&F)^", s, answer) == 1
           && answer == true);
    assert(evaluate("^F  ^  !F & (T&F)", s, answer) == 1
           && answer == true);
    assert(evaluate("&F  ^  !F & (T&F)", s, answer) == 1
           && answer == true);
    assert(evaluate("F  ^  !F & (T&^F)", s, answer) == 1
           && answer == true);
    assert(evaluate("F  ^  !F &^ (T&F)", s, answer) == 1
           && answer == true);

    assert(evaluate("F", s, answer) == 0
           && s == "F"
           && answer == false);
    assert(evaluate("(F)", s, answer) == 0
           && s == "F"
           && answer == false);
    assert(evaluate("(T", s, answer) == 1
           && answer == false);
    assert(evaluate("T)", s, answer)==1
           && answer == false);
    assert(evaluate("((T))", s, answer)==0
           && s=="T"
           && answer == true);
    assert(evaluate("((((((F))))))", s, answer)==0
           && s=="F"
           && answer == false);
    assert(evaluate("(F)(", s, answer) == 1
           && answer == false);
    assert(evaluate("(F)(T)", s, answer) == 1
           && answer == false);
    assert(evaluate(")F", s, answer) == 1
           && answer == false);
    assert(evaluate("(F", s, answer) == 1
           && answer == false);
    assert(evaluate("F)", s, answer) == 1
           && answer == false);
    assert(evaluate("F(", s, answer) == 1
           && answer == false);
    assert(evaluate("(F))", s, answer) == 1
           && answer == false);
    assert(evaluate("(F)(", s, answer) == 1
           && answer == false);
    assert(evaluate("(F))", s, answer) == 1
           && answer == false);
    assert(evaluate("(((((F))))", s, answer) == 1
           && answer == false);
    assert(evaluate(")((((F))))", s, answer) == 1
           && answer == false);
    assert(evaluate("&", s, answer)==1
           && answer == false);
    assert(evaluate("^", s, answer)==1
           && answer == false);
    assert(evaluate("!", s, answer)==1
           && answer == false);

    assert(evaluate("!&", s, answer)==1
           && answer == false);
    assert(evaluate(" ! ^ ", s, answer)==1
           && answer == false);
    assert(evaluate("^ !", s, answer)==1
           && answer == false);
    assert(evaluate("   & ! ", s, answer)==1
           && answer == false);
    assert(evaluate("^      & ", s, answer)==1
           && answer == false);
    answer=false;
    assert(evaluate("T!", s, answer)==1
           && answer == false);
    assert(evaluate("(T&F)!", s, answer)==1
           && answer == false);
    assert(evaluate("(T)!", s, answer)==1
           && answer == false);
    assert(evaluate(" ( T ) ! ", s, answer)==1
           && answer == false);
    assert(evaluate("T(^T)", s, answer)==1
           && answer == false);
    assert(evaluate(" T ( ^ T ) ", s, answer)==1
           && answer == false);
    assert(evaluate("^T", s, answer)==1
           && answer==false);
    assert(evaluate("&F", s, answer)==1
           && answer==false);
    assert(evaluate("t&t", s, answer)==1
           && answer==false);
    assert(evaluate("!@#$%^&(())&%*LJSB", s, answer)==1
           && answer==false);




    std::cerr<<"Passed all tests."<<std::endl;

    return (0);
}



