#include "NTRU.h"


void NTRU::generateKeys()
{
    ZZ_pX tmp_F_q;

	  // 随机选择截尾多项式f(私钥)
    this->f = this->getRandomPolynomial(this->d_f, this->d_f - 1);


	  // 计算多项式f在模p时的逆元
    ZZ_p::init(conv<ZZ>(this->p));
    this->f_p = conv<ZZ_pX>(this->f);
    this->F_p = InvMod(this->f_p, conv<ZZ_pX>(this->P));


  	// 计算多项式f在模q时的逆元
    ZZ_p::init(conv<ZZ>(2));
    this->f_q = conv<ZZ_pX>(this->f);
    tmp_F_q = InvMod(this->f_q, conv<ZZ_pX>(this->P));

    long n = 2;
    while(n <= this->e)
    {

	  // 生成公钥
    this->h = MulMod(this->F_q,conv<ZZ_pX>(this->g), conv<ZZ_pX>(this->P));

}

ZZX NTRU::getRandomPolynomial(long d1, long d2)
{
    ZZX f;

    vector<long> pos;
    pos.resize(this->N - 2);
    for (int i = 0; i < this->N - 2; ++i)
    {
        pos[i] = i;
    }
	          //shuffle()对pos里的元素进行随机排列,mt19937_64（seed）产生一个随机数
	          /*void shuffle(RandomAccessIterator first, RandomAccessIterator last, URNG&& g)
	           {
		          for (auto i = (last - first) - 1; i > 0; --i) {
			           std::uniform_int_distribution<decltype(i)> d(0, i);
			           swap(first[i], first[d(g)]);
		          }
	           }*/
    unsigned long long seed = std::chrono::system_clock::now().time_since_epoch().count();//生成随机数种子
    shuffle(pos.begin(),pos.end(),std::mt19937_64(seed));

    uniform_int_distribution<int> dist(0,1);
    int a = 0;
    if(dist(this->rgen) == 0)
    {
        SetCoeff(f, N - 1,1);
        a = -1;
    }
    else
    {
        SetCoeff(f, N - 1,-1);
    }

    for (int j = 0; j < d1 + a; ++j)
    {
        SetCoeff(f,pos[j],1);
    }

    for (long j = d1 + a; j < d1 + d2 - 1; ++j)
    {
        SetCoeff(f,pos[j],-1);
    }

    return f;
}

ZZX NTRU::encrypt(ZZX m)
{
    ZZ_p::init(conv<ZZ>(this->q));

    ZZX phi = this->getRandomPolynomial(this->d,this->d);
    ZZ_pX e = (this->p * conv<ZZ_pX>(phi) * this->h+conv<ZZ_pX>(m)) % conv<ZZ_pX>(this->P);
    ZZX result = conv<ZZX>(e);
    return result;
}

ZZX NTRU::decrypt(ZZX e)
{
    ZZX a = (this->f * conv<ZZX>(e)) % this->P;

    this->shift_coeff(a, conv<ZZ>(this->q));

    ZZ_p::init(conv<ZZ>(this->p));
    ZZ_pX m2 = (this->F_p * conv<ZZ_pX>(a)) % conv<ZZ_pX>(this->P);

    ZZX m = conv<ZZX>(m2);
    this->shift_coeff(m,conv<ZZ>(this->p));

    return m;
}

void NTRU::shift_coeff(ZZX &P, ZZ q)
{
    ZZ tmp;

    for (int i = 0; i <= deg(P); ++i)
    {
        tmp = coeff(P,i) % q;
        if(tmp > q/2)
            SetCoeff(P,i,tmp - q);
        else
            SetCoeff(P,i,tmp);
    }
}







        ZZ_p::init(conv<ZZ>(1 << n));   // 1 << n = 2^n
        tmp_F_q = (2 * tmp_F_q - conv<ZZ_pX>(this->f) * sqr(tmp_F_q)) % conv<ZZ_pX>(this->P);
        n++;
    }

    ZZ_p::init(conv<ZZ>(this->q));
    this->F_q = tmp_F_q % conv<ZZ_pX>(this->P);

	  // 随机选择截尾多项式g
    this->g = this->getRandomPolynomial(this->d_g, this->d_g);
