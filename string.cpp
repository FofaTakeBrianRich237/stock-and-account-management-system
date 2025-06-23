#include "string.h"

std::ostream& operator<<(std::ostream& flux,const string& st)
{
    for(int i = 0; i < st.length; i++) flux << st.String[i];
    return flux;
}

void string::copy(const char * st)
{
    int len;

    if(this->String != nullptr) this->~string();

    for(len = 0; st[len] != '\0'; len++);
    this->String = nullptr;
    this->String = (char*) malloc(sizeof(char) * len);
    this->length = len;

    for(int i = 0; st[i] != '\0'; i++)
    {
        this->String[i] = st[i];
    }
}

bool operator==(const string& init, const string& other)
{
    bool same  = true;
    if(init.length != other.length) same = false;
    else 
    {
        for(int i = 0; i < init.length; i++) 
        {
            if(init.String[i] != other.String[i]) 
            { 
                same = false; 
                break;
            }
        }
    }

    return same;
}

bool operator!=(const string& init, const string& other)
{
    bool same  = false;
    if(init.length != other.length) same = true;
    else 
    {
        for(int i = 0; i < init.length; i++) 
        {
            if(init.String[i] != other.String[i]) 
            { 
                same = true; 
                break;
            }
        }
    }

    return same;
}

bool operator==(const string& init, const char* st)
{
    bool same  = true;
    int len;
    for(len = 0; st[len] != '\0'; len++);
    if(init.length != len) same = false;
    else 
    {
        for(int i = 0; i < init.length; i++) 
        {
            if(init.String[i] != st[i]) 
            { 
                same = false; 
                break;
            }
        }
    }

    return same;
}

bool operator!=(const string& init, const char* st)
{
    bool same  = false;
    int len;
    for(len = 0; st[len] != '\0'; len++);
    if(init.length != len) same = true;
    else 
    {
        for(int i = 0; i < init.length; i++) 
        {
            if(init.String[i] != st[i]) 
            { 
                same = true; 
                break;
            }
        }
    }

    return same;
}