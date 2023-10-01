#ifndef AFUNCS_H
#define AFUNCS_H
#include "a_macro.cpp"
#define MX_ARR_LEN  784





class AFuncs
{
public:



    AFuncs();
    /**
     * @brief AFuncs::getSigmoid for single value
     * @param x         main value
     * @param tilt       tilt of graphic
     * @param bias     bias regarden of start
     */
	double getSigmoid(double x, double tilt, double bias = -0.5);
	float getSigmoid(float x, float tilt, float bias = -0.5);


    /**
     * @brief AFuncs::getSigmoid  for array
     * @param arrX
     * @param len
     * @param tilt
	 * @param bias
	 */
	double getSigmoid(double arrX[], int len, double tilt, double bias = -0.5);
	float getSigmoid(float arrX[], int len, float tilt, float bias = -0.5);

    bool matrixMul(int l1, int r1, int a1[], int l2, int r2, int a2[], int lRes, int rRes, int result[]);
    bool matrixMul(int l1, int r1, float a1[], int l2, int r2, float a2[], int lRes, int rRes, float result[]);
    bool matrixMul(int l1, int r1, double a1[], int l2, int r2, double a2[], int lRes, int rRes, double result[]);

    /**
     * @brief AFuncs::matrixMul    array * mx
     * @param arr         array                    struct
     * @param lns         mx lines                 AAA
     * @param clmns     mx columns            AAA
     * @param serMx     serial mx                AAA
     * @param result                           BBB
     */
    void matrixMul(int arr[], int lns, int clmns, int serMx[], int result[]);
    void matrixMul(float arr[], int lns, int clmns, float serMx[], float result[]);
    void matrixMul(double arr[], int lns, int clmns, double serMx[], double result[]);

    /**
     * @brief matrixMul      mx * array
     * @param lns          mx lines                 A
     * @param clmns      mx columns            A
     * @param serMx      serial mx                A
     * @param arr                               BBB
     * @param result                           BBB
     *                                                 BBB
     *                                                 BBB
     */
    void matrixMul(int lns, int clmns, int serMx[], int arr[], int result[]);
    void matrixMul(int lns, int clmns, float serMx[], float arr[], float result[]);
    void matrixMul(int lns, int clmns, double serMx[], double arr[], double result[]);


    /**
     * @brief arraysMul
     * @param array 1
     * @param array 2
     * @param length
     * @return
     */
    int arraysMul(int *arr1, int *arr2, int len);
    int arraysMul(float *arr1, float *arr2, int len);
	int arraysMul(double *arr1, double *arr2, int len);

    void matrixMul(float arr[], int lns, int clmns, float **mx, float result[]);

    void matrixMul(int lns, int clmns, float **mx, float arr[], float result[]);

    void AFuncs::matrixMul( double arr[], int lns, int clmns, double **mx,  double result[]);

private:

};

#endif // AFUNCS_H
