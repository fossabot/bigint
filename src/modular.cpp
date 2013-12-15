#include "config.h"
#include "base.h"
#include "boolean.h"
#include "mul.h"
#include "div.h"
#include "exceptions.h"
#include "modular.h"

void pow_mod(t_bint* a,
             t_bint* b,
             t_bint* n,
             t_size sizeA,
             t_size sizeB,
             t_size sizeN) {
    if (!sizeB || sizeB > sizeA) {
        sizeB = sizeA;
    }
    if (!sizeN) {
        sizeN = sizeA;
    }

    mod(a,n,sizeA,sizeN);
    
    if (isNull(a,sizeA) && isNull(b,sizeB)) {
        throw URException();
    }
    else if (isNull(a,sizeA) || cmp(a,1,sizeA) == CMP_EQUAL) {
    }
    else if (isNull(b,sizeB)) {
        setNull(a,sizeA);
        a[0] = 1;
        return;
    }
    else {
        t_size sizeT = sizeN * 2;
        t_size sizeR = sizeN * 2;
        t_bint* tmp = new t_bint[sizeT];
        t_bint* result = new t_bint[sizeR];
        t_size sizeP = sizeB;
        t_bint* p = new t_bint[sizeP];

        setNull(p,sizeP);
        setNull(tmp,sizeT);
        setNull(result,sizeR);

        result[0] = 1;
        mov(p,b,sizeP);
        mov(tmp,a,sizeA);

        t_bint i = 0;
        while (!isNull(p,sizeP)) {
            if (p[0] & 1) {
                mulMod(result,tmp,n,sizeR,sizeT,sizeN);
            }
            sqrMod(tmp,n,sizeT,sizeN);
            if (isNull(tmp,sizeT)) {
                break;
            }
            else if(cmp(tmp,1,sizeT) == CMP_EQUAL) {
                break;
            }
            shr(p,1,sizeP);
            i++;
        }
        mov(a,result,sizeA);
        mod(a,n,sizeA,sizeN);

        delete[] tmp;
        delete[] result;
        delete[] p;
    }
}

void mulMod(t_bint* a,
            t_bint* b,
            t_bint* n,
            t_size sizeA,
            t_size sizeB,
            t_size sizeN) {
    if (!sizeB) {
        sizeB = sizeA;
    }
    if (!sizeN) {
        sizeN = sizeA;
    }
    if (isNull(a,sizeA)) {
    }
    else if (cmp(a,1,sizeA) == CMP_EQUAL) {
        // TODO: test for bug of incorrect output (mod forgotten)
        setNull(a);
        mov(a,b,sizeA < sizeB ? sizeA : sizeB);
        mod(a,n,sizeA,sizeN);
    }
    else if (isNull(b,sizeB)) {
        setNull(a,sizeA);
    }
    else {
        mod(a,n,sizeA,sizeN);
        t_size sizeT = sizeA + sizeB + 1;
        t_bint* tmp = new t_bint[sizeT];
        setNull(tmp,sizeT);
        mov(tmp,a,sizeA);
        mul(tmp,b,sizeT,sizeB);
        mod(tmp,n,sizeT,sizeN);
        setNull(a,sizeA);
        mov(a,tmp,sizeA);
        delete[] tmp;
    }
}

void sqrMod(t_bint* a, t_bint* n, t_size sizeA, t_size sizeN) {
    sqr(a,sizeA);
    mod(a,n,sizeA,sizeN);
}
