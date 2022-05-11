#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include <string>


using namespace std;


typedef uint32_t Number;


const Number MAX_N = 100000;

vector<Number> primes;

void generateSieve(Number size) {
    unique_ptr<vector<bool>> sieve;

    sieve.reset(new vector<bool>(size, true));
    (*sieve)[0] = (*sieve)[1] = false;
    //Propagate old siege to new 

    for (Number primeCandidate = 2; primeCandidate < size; primeCandidate++)
    {
        if (sieve->at(primeCandidate) == false) continue;

        primes.push_back(primeCandidate);
        
        for (Number cancelledNumber = primeCandidate*primeCandidate; cancelledNumber < size; cancelledNumber += primeCandidate) {
            
            (*sieve)[cancelledNumber] = false;
        }
    }
}

vector<Number> calcPrimeDecomp(Number number, bool &canBeDescribed) {
    vector<Number> decompVec;

    canBeDescribed = false;
    for (Number primeIdx = 0; primeIdx < primes.size(); primeIdx++)
    {
        Number currPrime = primes[primeIdx];
        if (currPrime > number) break;

        int currPrimeOccurrences = 0;
        while (number % currPrime == 0) {
            currPrimeOccurrences++;
            number /= currPrime;
        }
        
        decompVec.push_back(currPrimeOccurrences);
        if (currPrimeOccurrences > 0) canBeDescribed = true;
    }

    return decompVec;
}

int assertBounds(Number fn, Number m) {

    int accum = fn-fn/10*10 + 9;
    int i = 1;
    while (fn > 1) {
        int d = fn-fn/10*10;
        accum += (1 - ( ( (i-1) % 4) / 2) * 2) * d;
        fn/=10;
        i++;
    }

    return m * accum;
}

bool dividesFact(Number factNumber, Number m) {
    if (!assertBounds(factNumber, m)) return false;

    if (factNumber == 0 || factNumber == 1) return m == 1;

    if ((m == 1) || (m <= factNumber)) return true;

    bool mDescribable = false;
    auto mDecompVec = calcPrimeDecomp(m, mDescribable);

    if (!mDescribable) return false;

    for (size_t currPrimeIdx = 0; currPrimeIdx < mDecompVec.size(); currPrimeIdx++)
    {
        Number currPrime = primes[currPrimeIdx];

        Number pot = currPrime;
        Number factCopy = factNumber;
        Number accum = 0;
        while (pot <= factCopy) {
            accum += factCopy / pot;
            pot *= currPrime;
        }

        if (accum < mDecompVec[currPrimeIdx]) return false;
    }


    return true;
}


int main(void)
{
    Number N, M;
    generateSieve(MAX_N);

    while (true) {
        if (scanf("%u %u", &N, &M) == EOF) break;
        string divideStr = dividesFact(N, M) ? " divides " : " does not divide ";
        cout << M << divideStr << N << "!" << endl;
    }
    return 0;
}
