#ifndef NTRU_NTRU_H
#define NTRU_NTRU_H

#include "NTL/ZZ_pE.h"
#include "NTL/ZZX.h"
#include <random>       // std::mt19937_64
#include <algorithm>    // std::shuffle
#include <vector>
#include <chrono>       // std::chrono::system_clock

using namespace NTL;
using namespace std;

class NTRU
{
private:

    const unsigned long N, p, q, e, d_f, d_g, d;

    ZZX P, f, g;
    ZZ_pX f_p, f_q, F_p, F_q;

    mt19937_64 rgen;

    void generateKeys();

    ZZX getRandomPolynomial(long d1, long d2);

    /**
     * Shifts the coefficients into the interval [-q/2,q/2]
     */
    void shift_coeff(ZZX& P, ZZ q);

public:

    ZZ_pX h;

    NTRU(unsigned long N, unsigned long p, unsigned long e, unsigned long d_f, unsigned long d_g, unsigned long d)
            : N(N), p(p), q((unsigned)1 << e), e(e), d_f(d_f), d_g(d_g), d(d)
    {
        unsigned long long seed = std::chrono::system_clock::now().time_since_epoch().count();
        this->rgen = mt19937_64(seed);

        SetCoeff(this->P,0,-1);
        SetCoeff(this->P,N,1);

        this->generateKeys();

        return;
    }

    ZZX encrypt(ZZX m);

    ZZX decrypt(ZZX e);

};


#endif //NTRU_NTRU_H
