#include<stdlib.h>
#include<iostream>

void output(bool i){
    static unsigned char character=0;
    static char len=0;
    character = (character<<1)+i;
    len+=1;
    if (len==8){
        len=0;
        std::cout<<character;
        character=0;
    }
}

template<typename T>
class stackBody{
    public:
    T* value;
    stackBody<T>* next;
};

template<typename T>
class stack{
    stackBody<T>* body;

    public:
    T* pop(){
        T* val = body->value;
        stackBody<T>* oldBody = body;
        body=body->next;
        free(oldBody);
        return val;
    };

    void push(T* newt){
        stackBody<T>* newBody=(stackBody<T>*)malloc(sizeof(stackBody<T>));
        newBody->value=newt;
        newBody->next=body;
        body=newBody;
    };
};

class codeBody{
    char type;
    union{
        void (*orig)(void);
        codeBody *wrapped;
        struct {
            codeBody* orig1;
            codeBody* orig2;
        };
    };

    public:
    static codeBody* concat(codeBody* obj1, codeBody* obj2){
        codeBody* out = (codeBody*)malloc(sizeof(codeBody));
        out->type=2;
        out->orig1=obj1;
        out->orig2=obj2;
        return out;
    }

    static codeBody* wrap(codeBody* obj){
        codeBody* out = (codeBody*)malloc(sizeof(codeBody));
        out->type=1;
        out->wrapped=obj;
        return out;
    }

    static codeBody* copy(codeBody* obj){
        codeBody* out = (codeBody*)malloc(sizeof(codeBody));
        if (obj->type==0){
            out->type=0;
            out->orig=obj->orig;
        } else if (obj->type==1){
            out->type=1;
            out->wrapped=copy(obj->wrapped);
        } else if (obj->type==2){
            out->type=2;
            out->orig1=copy(obj->orig1);
            out->orig2=copy(obj->orig2);
        }
    }
};

stack<codeBody> codestack;

void dup(){
    codeBody* temp=codestack.pop();
    codestack.push(temp);
    codestack.push(codeBody::copy(temp));
}



int main(){

}
