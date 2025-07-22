#include "string.h"

std::ostream& operator<<(std::ostream& flux,const string& st)
{
    for(int i = 0; i < st.length; i++) flux << st.String[i];
    return flux;
}

std::istream& operator>>(std::istream& flux, string& st)
{
    int bufferCap = 20;
    int bufferlength = 0;
    char * buffer = (char*) malloc(sizeof(char) * bufferCap);
    char c;
    auto lambda = [&c]() 
    {
        if(c == '\n' || c == '\t' || c == '\r' || c == EOF || c == '\0') return false;
        else return true;
    };

    while(flux.get(c) && lambda())
    {
        if(bufferlength + 1 >= bufferCap)
        {
            bufferCap *= 2;
            char* Nbuffer = (char*) malloc(sizeof(char) * bufferCap);
            for(int i = 0; i < bufferlength; i++) Nbuffer[i] = buffer[i];
            free(buffer);
            buffer = Nbuffer;
            free(Nbuffer);
        }
        buffer[bufferlength++] = c;
    }
    buffer[bufferlength] = '\0';
    // if(st.String != nullptr) free(st.String);
    st.~string();
    st.copy(buffer);
    free(buffer);

    return flux;
}

void string::copy(const char * st)
{
    int len;

    if(this->String != nullptr) this->~string();

    for(len = 0; st[len] != '\0'; len++);
    this->String = nullptr;
    this->String = (char*) malloc(sizeof(char) * (len+1));
    this->length = len;

    for(int i = 0; st[i] != '\0'; i++)
    {
        if(st[i] != '/') this->String[i] = st[i];
        else this->String[i] = ' ';
    }
    this->String[len] = '\0';
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
    if(init.length != other.length) {std::cout << "merde" << std::endl;same = true;}
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