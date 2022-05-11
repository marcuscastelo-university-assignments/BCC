#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;

unique_ptr<vector<bool>> sieve;

typedef uint32_t Number;


const int MAX_N = 200;

void generateSieve(Number size) {
    if (sieve == nullptr) {
        sieve.reset(new vector<bool>(2, false));
    }

    Number sizeSqrt = (Number) ceil(sqrt(size));
    Number oldSize = sieve->size();

    if (oldSize >= size) return;

    sieve->resize(size, true);

    //Propagate old siege to new 

    for (Number primeCandidate = oldSize; primeCandidate <= sizeSqrt; primeCandidate++)
    {
        if (sieve->at(primeCandidate) == false) continue;
        
        for (Number cancelledNumber = primeCandidate*primeCandidate; cancelledNumber < size; cancelledNumber += primeCandidate) {
            
            (*sieve)[cancelledNumber] = false;
        }
    }
}

vector<Number> calcPrimeDecomp(Number number) {
    vector<Number> decompVec;

    for (Number primeNumber = 2; primeNumber <= number; primeNumber++)
    {
        if ((*sieve)[primeNumber] == false) //If not prime
            continue; 

        int currPrimeOccurrences = 0;
        for (Number factorialCompound = 2; factorialCompound <= number; factorialCompound++)
        {

            Number compoundCopy = factorialCompound;
            while (compoundCopy % primeNumber == 0) {
                currPrimeOccurrences++;
                compoundCopy /= primeNumber;
            }

        }
        decompVec.push_back(currPrimeOccurrences);

    }

    return decompVec;
}

void prettyPrint(int N, const vector<Number>& decompVec) {
    std::printf("%3d! =", N);
    
    int _15counter = 1;
    for (auto primeComp : decompVec) {
        if (_15counter++%16 == 0) {
            std::printf("\n      ");
            _15counter = 1;
        }
        std::printf("%3u", primeComp);
    }
    std::printf("\n");
}

int main(void)
{
    Number N;
    generateSieve(MAX_N);
    while (true) {
        cin >> N;
        if (N == 0) break;

        auto decompVec = calcPrimeDecomp(N);

        prettyPrint(N, decompVec);
    }
    return 0;
}
