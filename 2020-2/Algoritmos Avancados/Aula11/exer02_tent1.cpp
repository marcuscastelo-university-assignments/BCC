#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include <string>


using namespace std;

unique_ptr<vector<bool>> sieve;

typedef uint32_t Number;


const Number MAX_N = 100000;

void generateSieve(Number size) {
    if (sieve == nullptr) {
        sieve.reset(new vector<bool>(2, false));
    } else {
        throw std::logic_error("Calling generateSieve twice");
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

        Number compoundCopy = number;
        while (compoundCopy % primeNumber == 0) {
            currPrimeOccurrences++;
            compoundCopy /= primeNumber;
        }
        decompVec.push_back(currPrimeOccurrences);
    }

    return decompVec;
}

vector<Number> calcPrimeDecompFact(Number factNumber) {
    vector<Number> decompVec;

    for (Number primeNumber = 2; primeNumber <= factNumber; primeNumber++)
    {
        if ((*sieve)[primeNumber] == false) //If not prime
            continue; 

        int currPrimeOccurrences = 0;
        for (Number factorialCompound = 2; factorialCompound <= factNumber; factorialCompound++)
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

bool dividesFact(Number m, Number n) {
    auto decompVecN = calcPrimeDecompFact(n);
    auto decompVecM = calcPrimeDecomp(m);

    for (size_t index = 0; index < decompVecM.size(); index++)
        if (decompVecN[index] < decompVecM[index]) return false;
    return true;
}

int main(void)
{
    Number N, M;
    generateSieve(MAX_N);

    while (true) {
        if (scanf("%u %u", &N, &M) == EOF) break;
        string divideStr = dividesFact(M,N) ? " divides " : " does not divide ";
        cout << M << divideStr << N << "!" << endl;
    }
    return 0;
}
