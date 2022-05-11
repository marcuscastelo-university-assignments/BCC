#include <iostream>
#include <unordered_map>
#include <string.h>
#include <stdio.h>
#include <string>

using namespace std;

unordered_map<int, string> nameOfIntIp;

struct IP
{
    union
    {
        unsigned char iparr[4];
        struct
        {
            unsigned char a, b, c, d;
        } ipparts;
    } ip;
};

IP parseIPText(string ipText, bool hasSemicolon)
{
    IP ip;

    char ipPartChars[5] = {0};
    int j = 0, k = 0;
    for (size_t i = 0; i < ipText.length(); i++)
    {
        if (ipText[i] == '.' || ipText[i] == ';')
        {
            ip.ip.iparr[k] = atoi(ipPartChars);
            memset(ipPartChars, 0, 5);
            j = 0;
            k++;
            continue;
        }

        ipPartChars[j++] = ipText[i];
    }

    if (!hasSemicolon) {
        ip.ip.iparr[k] = atoi(ipPartChars);
    }

    return ip;
}

int IPToInt(IP ip)
{
    int hash = 0;
    for (int i = 0; i < 4; i++)
        hash = (256 * hash) + ip.ip.iparr[i];
    return hash;
}

int main(int argc, char const *argv[])
{

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        string name;
        cin >> name;
        getchar();

        string line;
        getline(cin, line);

        IP ip = parseIPText(line, false);
        nameOfIntIp[IPToInt(ip)] = name;
    }

    for (int i = 0; i < m; i++)
    {
        string command;
        cin >> command;
        getchar();

        string line;
        getline(cin, line);

        IP ip = parseIPText(line, true);
        cout << command << " " << line << " #" << nameOfIntIp[IPToInt(ip)] << endl;
    }
    
    return 0;
}
