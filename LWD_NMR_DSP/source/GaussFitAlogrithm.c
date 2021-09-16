#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#pragma CODE_SECTION(GaussFit, "secureRamFuncs");

/*
 * GaussFit 高斯拟合函数
 * Arguments    : const float x[9]
 *                const float y[9]
 *                float *a
 *                float *b
 *                float *c
 * Return Type  : void
 */
void GaussFit(const float x[9], const float y[9], float* a, float* b, float* c)
{
    int k;
    float X[27];
    int p2;
    float Y[9];
    float b_x[9];
    float b_c[9];
    int p3;
    float absx11;
    float absx21;
    float absx31;
    int itmp;
    float B[3];
    float b_y[27];
    for (k = 0; k < 9; k++) {
        X[k] = x[k] * x[k];
        X[9 + k] = x[k];
        X[18 + k] = 1.0F;
        Y[k] = (float)log(y[k]);
    }

    for (k = 0; k < 3; k++) {
        for (p2 = 0; p2 < 3; p2++) {
            b_c[k + 3 * p2] = 0.0F;
            for (p3 = 0; p3 < 9; p3++) {
                b_c[k + 3 * p2] += X[p3 + 9 * k] * X[p3 + 9 * p2];
            }
        }
    }

    for (k = 0; k < 9; k++) {
        b_x[k] = b_c[k];
    }

    k = 0;
    p2 = 3;
    p3 = 6;
    absx11 = (float)fabs(b_c[0]);
    absx21 = (float)fabs(b_c[1]);
    absx31 = (float)fabs(b_c[2]);
    if ((absx21 > absx11) && (absx21 > absx31)) {
        k = 3;
        p2 = 0;
        b_x[0] = b_c[1];
        b_x[1] = b_c[0];
        b_x[3] = b_c[4];
        b_x[4] = b_c[3];
        b_x[6] = b_c[7];
        b_x[7] = b_c[6];
    }
    else {
        if (absx31 > absx11) {
            k = 6;
            p3 = 0;
            b_x[0] = b_c[2];
            b_x[2] = b_c[0];
            b_x[3] = b_c[5];
            b_x[5] = b_c[3];
            b_x[6] = b_c[8];
            b_x[8] = b_c[6];
        }
    }

    absx11 = b_x[1] / b_x[0];
    b_x[1] /= b_x[0];
    absx21 = b_x[2] / b_x[0];
    b_x[2] /= b_x[0];
    b_x[4] -= absx11 * b_x[3];
    b_x[5] -= absx21 * b_x[3];
    b_x[7] -= absx11 * b_x[6];
    b_x[8] -= absx21 * b_x[6];
    if ((float)fabs(b_x[5]) > (float)fabs(b_x[4])) {
        itmp = p2;
        p2 = p3;
        p3 = itmp;
        b_x[1] = absx21;
        b_x[2] = absx11;
        absx11 = b_x[4];
        b_x[4] = b_x[5];
        b_x[5] = absx11;
        absx11 = b_x[7];
        b_x[7] = b_x[8];
        b_x[8] = absx11;
    }

    absx11 = b_x[5] / b_x[4];
    b_x[5] /= b_x[4];
    b_x[8] -= absx11 * b_x[7];
    absx11 = (b_x[5] * b_x[1] - b_x[2]) / b_x[8];
    absx21 = -(b_x[1] + b_x[7] * absx11) / b_x[4];
    b_c[k] = ((1.0F - b_x[3] * absx21) - b_x[6] * absx11) / b_x[0];
    b_c[k + 1] = absx21;
    b_c[k + 2] = absx11;
    absx11 = -b_x[5] / b_x[8];
    absx21 = (1.0F - b_x[7] * absx11) / b_x[4];
    b_c[p2] = -(b_x[3] * absx21 + b_x[6] * absx11) / b_x[0];
    b_c[p2 + 1] = absx21;
    b_c[p2 + 2] = absx11;
    absx11 = 1.0F / b_x[8];
    absx21 = -b_x[7] * absx11 / b_x[4];
    b_c[p3] = -(b_x[3] * absx21 + b_x[6] * absx11) / b_x[0];
    b_c[p3 + 1] = absx21;
    b_c[p3 + 2] = absx11;
    for (k = 0; k < 3; k++) {
        B[k] = 0.0F;
        for (p2 = 0; p2 < 9; p2++) {
            b_y[k + 3 * p2] = 0.0F;
            for (p3 = 0; p3 < 3; p3++) {
                b_y[k + 3 * p2] += b_c[k + 3 * p3] * X[p2 + 9 * p3];
            }

            B[k] += b_y[k + 3 * p2] * Y[p2];
        }
    }

    *a = (float)exp(B[2] - B[1] * B[1] / (4.0F * B[0]));

    /*  拟合得到的参数a */
    *b = -B[1] / (2.0F * B[0]);

    /*  拟合得到的参数b */
    *c = 1.0F / (float)sqrt(-B[0]);

    /*  拟合得到的参数c */
}
