/*
 * @Descripttion: ����������ֵ����
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

// �ο���https://blog.csdn.net/limingmcu/article/details/91492214
/*
** ��Ȼ�߽������������ֵ����
** Args:
**		x[9]�������
**		y[9]: �Ա���
**		fre: ����Ƶ��
** Returns:
*	    amp: ��Ӧ����Ƶ�ʵķ�ֵ
*/
float CublicSplineInterpolation(float x[9], float y[9], float fre)
{

	float amp = 0;

	// ����ϵ��
	// Si(x) = ai+bi(x-xi)+ci(x-xi)^2+di(x-xi)^3
	float ai[8];
	float bi[8];
	float ci[8];
	float di[8];
	float h = x[1] - x[0];		// hΪ�������˴�Ϊ��ֵ

	/* M�����ϵ��
	* [B0, C0, ...
	* [A1, B1, C1, ...
	* [0, A2, B2, C2, ...
	* [0, ...,			An-1, Bn-1]
	*/
	float A[7];
	float B[7];
	float C[7];
	float D[7];		// �Ⱥ��ұߵĳ�������
	float E[7];		// M����
	float M[9];		// �����˵��M����

	int i = 0;
	int n = 9;
	// ָ��ϵ��
	for (i = 0; i < n - 2; ++i)
	{
		A[i] = h;
		B[i] = 4 * h;
		C[i] = h;
	}

	// ָ������D
	for (i = 0; i < n - 2; ++i)
	{
		D[i] = (y[i + 2] - 2 * y[i + 1] + y[i]) / h * 6;
	}

	// ������ԽǾ��󣬽��������E
	TDMA(E, n - 2, A, B, C, D);
	M[0] = 0;
	M[n - 1] = 0;
	for (i = 1; i < n - 1; ++i)
	{
		M[i] = E[i - 1];
	}

	// ��������������ֵ��ϵ��
	for (i = 0; i < n - 1; ++i)
	{
		ai[i] = y[i];
		bi[i] = (y[i + 1] - y[i]) / h - h / 6 * (2 * M[i] + M[i + 1]);
		ci[i] = M[i] / 2;
		di[i] = (M[i + 1] - M[i]) / (6 * h);
	}

	// �ҵ�fre���ڵ�����
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

	// ����amp
	float temp1 = fre - x[index];
	float temp2 = temp1 * temp1;	// 2�η�
	float temp3 = temp2 * temp1;	// 3�η�
	amp = ai[index] + bi[index] * temp1 + ci[index] * temp2 + di[index] * temp3;

	return amp;
}

// ������ԽǾ���
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

	// ������������X
	for (i = n - 2; i >= 0; --i)
	{
		X[i] = D[i] - C[i] * X[i + 1];
	}
}
