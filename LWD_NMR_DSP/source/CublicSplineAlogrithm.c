/*
 * @Descripttion: 三次样条插值函数
 * @version: 
 * @Author: Yao Liu
 * @Company: HUST.AIA
 * @Date: 2021-09-06 20:43:47
 * @LastEditors: Yao Liu
 * @LastEditTime: 2021-09-07 17:24:34
 */

#pragma CODE_SECTION(TDMA, "secureRamFuncs");
#pragma CODE_SECTION(CublicSplineInterpolation, "secureRamFuncs");

// This is a fast method to solve 
void TDMA(float* X, int n, float* A, float* B, float* C, float* D);

// 参考：https://blog.csdn.net/limingmcu/article/details/91492214
/*
** 自然边界的三次样条插值函数
** Args:
**		x[9]：因变量
**		y[9]: 自变量
**		fre: 输入频率
** Returns:
*	    amp: 对应输入频率的幅值
*/
float CublicSplineInterpolation(float x[9], float y[9], float fre)
{

	float amp = 0;

	// 曲线系数
	// Si(x) = ai+bi(x-xi)+ci(x-xi)^2+di(x-xi)^3
	float ai[8];
	float bi[8];
	float ci[8];
	float di[8];
	float h = x[1] - x[0];		// h为步长，此处为定值

	/* M矩阵的系数
	* [B0, C0, ...
	* [A1, B1, C1, ...
	* [0, A2, B2, C2, ...
	* [0, ...,			An-1, Bn-1]
	*/
	float A[7];
	float B[7];
	float C[7];
	float D[7];		// 等号右边的常数矩阵
	float E[7];		// M矩阵
	float M[9];		// 包含端点的M矩阵

	int i = 0;
	int n = 9;
	// 指定系数
	for (i = 0; i < n - 2; ++i)
	{
		A[i] = h;
		B[i] = 4 * h;
		C[i] = h;
	}

	// 指定常数D
	for (i = 0; i < n - 2; ++i)
	{
		D[i] = (y[i + 2] - 2 * y[i + 1] + y[i]) / h * 6;
	}

	// 求解三对角矩阵，将结果赋给E
	TDMA(E, n - 2, A, B, C, D);
	M[0] = 0;
	M[n - 1] = 0;
	for (i = 1; i < n - 1; ++i)
	{
		M[i] = E[i - 1];
	}

	// 计算三次样条插值的系数
	for (i = 0; i < n - 1; ++i)
	{
		ai[i] = y[i];
		bi[i] = (y[i + 1] - y[i]) / h - h / 6 * (2 * M[i] + M[i + 1]);
		ci[i] = M[i] / 2;
		di[i] = (M[i + 1] - M[i]) / (6 * h);
	}

	// 找到fre所在的区间
	int index = 0;
	for (i = 1; i < n; ++i)
	{
		if (fre < x[i])
		{
			index = i - 1;
			break;
		}
	}
	if (i == 9)
		index = 7;

	// 计算amp
	float temp1 = fre - x[index];
	float temp2 = temp1 * temp1;	// 2次方
	float temp3 = temp2 * temp1;	// 3次方
	amp = ai[index] + bi[index] * temp1 + ci[index] * temp2 + di[index] * temp3;

	return amp;
}

// 求解三对角矩阵
void TDMA(float* X, int n, float* A, float* B, float* C, float* D)
{
	int i;
	float temp;
	
	C[0] = C[0] / B[0];
	D[0] = D[0] / B[0];

	for (i = 1; i < n; ++i)
	{
		temp = (B[i] - A[i] * C[i - 1]);
		C[i] = C[i] / temp;
		D[i] = (D[i] - A[i] * D[i - 1]) / temp;
	}

	X[n - 1] = D[n - 1];

	// 逆向迭代，求出X
	for (i = n - 2; i >= 0; --i)
	{
		X[i] = D[i] - C[i] * X[i + 1];
	}
}
