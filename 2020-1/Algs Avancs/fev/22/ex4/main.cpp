#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

int getMaior(vector<set<unsigned short>>* combs) {
    vector<unsigned> jafoi;

    map<int, int> pessoasPorPopu;

    int maiorPopularidade = 0;

    for (unsigned i = 0; i < combs->size(); i++)
    {
        if (find(jafoi.begin(), jafoi.end(), i) != jafoi.end()) continue;

        int popularid = 1;
        auto *a = &(*combs)[i];
        for (unsigned u = i+1; u < combs->size(); u++)
        {
            if (find(jafoi.begin(), jafoi.end(), u) != jafoi.end()) continue;

            auto *b = &(*combs)[u];
            if (*a == *b){
                popularid++;
                jafoi.push_back(u);
            } 
        }
        if (popularid > maiorPopularidade) maiorPopularidade = popularid;
        jafoi.push_back(i);
        pessoasPorPopu[popularid] += popularid;   
    }

    return pessoasPorPopu[maiorPopularidade];
}

int main(int argc, char const *argv[])
{
    vector<unsigned short> output;
    vector<set<unsigned short>> allCombinations;
    unsigned short n;
    do {
        cin >> n;
        if (n == 0) break;

        for (unsigned short i = 0; i < n; i++)
        {
            set<unsigned short>combinations; //= new set<unsigned short>();
            unsigned short temp;
            for (char u = 0; u < 5; u++)
            {
                cin >> temp;
                combinations.insert(temp);
            }
            allCombinations.push_back(combinations);
        }
        output.push_back(getMaior(&allCombinations));
        allCombinations.clear();
    } while (true);

    for (unsigned i = 0; i < output.size(); i++)
    {
        cout << output[i] << endl;
    }
   
    

    //TODO: del combinations

    return 0;
}
