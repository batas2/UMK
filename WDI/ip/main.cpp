#include <iostream>
#include <string>

using namespace std;

int strint(string in){
    unsigned int i, w = in[0] - 48;
    for(i = 1; i < in.length(); i++){
        w = w * 10 + (in[i] - 48);}
    return w;
}

int Not(int v){
    int p = 1, w = 0;
    for(int i = 0; i < 8; i++){
        if(v > 0){
            if(v % 2 == 0){
                w = w + p;
            }
            v/=2;
        }else{
            w = w + p;
        }
        p*=2;
    }
    return w;

}
void licz(unsigned int *ip, unsigned int *mask){

    printf("Adres podsieci:\t\t%d.%d.%d.%d\n", ip[0] & mask[0], ip[1] & mask[1], ip[2] & mask[2], ip[3] & mask[3]);
    printf("Adres rozgloszeniowy:\t%d.%d.%d.%d\n", ip[0] | Not(mask[0]), ip[1] | Not(mask[1]), ip[2] | Not(mask[2]), ip[3] | Not(mask[3]));
    switch(*ip){
        case 1-126: cout << "Klasa IP: A" << endl; break;
        case 127: break;
        case 128-191: cout << "Klasa IP: B" << endl; break;
        case 192-223: cout << "Klasa IP: C" << endl; break;
        case 224-239: cout << "Klasa IP: D" << endl; break;
        case 241-255: cout << "Klasa IP: E" << endl; break;
    };
}
bool split(string in, unsigned int *out){
    size_t found;
    int i = 0;

    found = in.find('.');
    if( in[in.length() - 1] == '.'){
        return false;
    }

    while(found != string::npos){
        found = in.find('.');
        string buf = in.substr(0, (int)found);
        *out = strint(buf);
        buf = in.substr((int)found + 1, in.length() - (int)found + 1);
        in = buf;
        *out++;
        i++;
    }

    if(i == 4){
        return true;
    }else{
        return false;
    }

}

int main(int argc, const char* argv[])
{
//    if(argc != 3){
//        cout << "Blad: Bledna liczba parametrow, poprawne wywolanie: ./ip IP MASKA" << endl;
//        return 0;
//    }

    //string ip = argv[1];
    //string maska = argv[2];

    string sip ("158.75.2.0");
    string smask ("255.255.255.0");

    unsigned int iip[3];
    unsigned int imask[3];

    if(split(sip, iip)){
        if(split(smask, imask)){
            cout << "Adres IP:\t\t" << sip << "\nMaska sieci: \t\t" << smask << endl;
            licz(iip, imask);
        }else{
            cout << "Blad: Bledna maska, poprawny format: XXX.XXX.XXX.XXX\n";
            return 0;
        }
    }else{
        cout << "Blad: Bledny adres ip, poprawny format: XXX.XXX.XXX.XXX\n";
        return 0;
    }
    return 0;
}
