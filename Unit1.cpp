//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "GlobalVar.h"
#include "afuncs.h"
#include "a_macro.cpp"
#include <iostream.h>
#include "pngimage.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

#define N0_LEN 4
#define N1_LEN 10
#define N2_LEN 10
#define N_GOAL_LEN 10

#define IMG_BIG_H 140
#define IMG_BIG_W 140
#define IMG_SMALL_H 28
#define IMG_SMALL_W 28

#define LAYER_QTY 4

#define IMG_POS_LEFT_TOP 1
#define IMG_POS_CENTER   2


float arrN0[N0_LEN];
float arrN1[N1_LEN];
float arrN2[N2_LEN];
float arrGoal[N_GOAL_LEN];

float arrW1[N0_LEN][N1_LEN];
float arrW2[N1_LEN][N2_LEN];
float arrW3[N2_LEN][N_GOAL_LEN];

float arrDeltaN0[N0_LEN];
float arrDeltaN1[N1_LEN];
float arrDeltaN2[N2_LEN];
float arrDeltaGoal[N_GOAL_LEN];

float arrDeltaW1[N0_LEN][N1_LEN];
float arrDeltaW2[N1_LEN][N2_LEN];
float arrDeltaW3[N2_LEN][N_GOAL_LEN];

#define IN_N_LEN 784
#define MN1_LEN 16
#define MN2_LEN 16
#define OUT_N_LEN 7
#define PATT_QTY 42

#define DIG_PATT_QTY 60

float P1_goal[PATT_QTY][OUT_N_LEN] = {
    {1, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0},

    {0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0},

    {0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0},

    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0},

    {0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0},

    {0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0},

    {0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 1}

};

String imgFiles[PATT_QTY];
String imgDigitFiles[DIG_PATT_QTY];

float P1_patt[PATT_QTY][IN_N_LEN];
// float **P1_patt;

float P1_inN[IN_N_LEN];
float P1_mN1[MN1_LEN];
float P1_mN2[MN2_LEN];
float P1_outN[OUT_N_LEN];

float P1_W1[IN_N_LEN][MN1_LEN];
float P1_W2[MN1_LEN][MN2_LEN];
float P1_W3[MN2_LEN][OUT_N_LEN];
// float **P1_W1;
// float **P1_W2;
// float **P1_W3;

float P1_deltaIn[IN_N_LEN];
float P1_deltaMN1[MN1_LEN];
float P1_deltaMN2[MN2_LEN];
float P1_deltaOutN[OUT_N_LEN];

float P1_deltaW1[IN_N_LEN][MN1_LEN];
float P1_deltaW2[MN1_LEN][MN2_LEN];
float P1_deltaW3[MN2_LEN][OUT_N_LEN];

float P1_tmp[784];


float **G_tmpImgArr1;
float **G_tmpImgArr2;
float **G_smallTmpImgArr1;
float **G_smallTmpImgArr2;




AFuncs *mf;
FILE *fl;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent *Owner)
    : TForm(Owner)
{
    G_alfa = 0.001;
    G_cycleQty = 10000;
    G_sigmoidTilt = 25;
	G_stop = false;
	G_scaleImg = 1;

    initImgNameArray();
    initArrays();
    initWeights();
}

void TForm1::initArrays()
{
    //    P1_W1 = new float* [IN_N_LEN];
    //    for (int i = 0; i < IN_N_LEN; i++)
    //    {
    // 	   P1_W1[i] = new float[MN1_LEN];
    //    }

    //    P1_W2 = new float* [MN1_LEN];
    //    for (int i = 0; i < MN1_LEN; i++)
    //    {
    // 	   P1_W2[i] = new float[MN2_LEN];
    //    }
    //    P1_W3 = new float* [MN2_LEN];
    //    for (int i = 0; i < MN2_LEN; i++)
    //    {
    //        P1_W3[i] = new float[OUT_N_LEN];
    //    }

    //    P1_patt = new double* [PATT_QTY];

    //    for (int i = 0; i < PATT_QTY; i++)
    //    {
    //        P1_patt[i] = new double[IN_N_LEN];
    //    }

    G_tmpImgArr1 = new float *[IMG_BIG_H];
    for (int i = 0; i < IMG_BIG_H; i++){
        G_tmpImgArr1[i] = new float[IMG_BIG_W];
    }

    G_tmpImgArr2 = new float *[IMG_BIG_H];
    for (int i = 0; i < IMG_BIG_H; i++){
        G_tmpImgArr2[i] = new float[IMG_BIG_W];
    }

    G_smallTmpImgArr1 = new float *[IMG_SMALL_H];
    for (int i = 0; i < IMG_SMALL_H; i++){
        G_smallTmpImgArr1[i] = new float[IMG_SMALL_H];
    }
    G_smallTmpImgArr2 = new float *[IMG_SMALL_H];
    for (int i = 0; i < IMG_SMALL_H; i++){
        G_smallTmpImgArr2[i] = new float[IMG_SMALL_H];
    }

    
}

void TForm1::initImgNameArray()
{
    imgFiles[0] = "img/cross_1.png";
    imgFiles[1] = "img/cross_2.png";
    imgFiles[2] = "img/cross_3.png";
    imgFiles[3] = "img/cross_4.png";
    imgFiles[4] = "img/cross_5.png";
    imgFiles[5] = "img/cross_6.png";

    imgFiles[6] = "img/circle_1.png";
    imgFiles[7] = "img/circle_2.png";
    imgFiles[8] = "img/circle_3.png";
    imgFiles[9] = "img/circle_4.png";
    imgFiles[10] = "img/circle_5.png";
    imgFiles[11] = "img/circle_6.png";

    imgFiles[12] = "img/rctngl_1.png";
    imgFiles[13] = "img/rctngl_2.png";
    imgFiles[14] = "img/rctngl_3.png";
    imgFiles[15] = "img/rctngl_4.png";
    imgFiles[16] = "img/rctngl_5.png";
    imgFiles[17] = "img/rctngl_6.png";

    imgFiles[18] = "img/trngl1_1.png";
    imgFiles[19] = "img/trngl1_2.png";
    imgFiles[20] = "img/trngl1_3.png";
    imgFiles[21] = "img/trngl1_4.png";
    imgFiles[22] = "img/trngl1_5.png";
    imgFiles[23] = "img/trngl1_6.png";

    imgFiles[24] = "img/trngl2_1.png";
    imgFiles[25] = "img/trngl2_2.png";
    imgFiles[26] = "img/trngl2_3.png";
    imgFiles[27] = "img/trngl2_4.png";
    imgFiles[28] = "img/trngl2_5.png";
    imgFiles[29] = "img/trngl2_6.png";

    imgFiles[30] = "img/trngl3_1.png";
    imgFiles[31] = "img/trngl3_2.png";
    imgFiles[32] = "img/trngl3_3.png";
    imgFiles[33] = "img/trngl3_4.png";
    imgFiles[34] = "img/trngl3_5.png";
    imgFiles[35] = "img/trngl3_6.png";

    imgFiles[36] = "img/trngl4_1.png";
    imgFiles[37] = "img/trngl4_2.png";
    imgFiles[38] = "img/trngl4_3.png";
    imgFiles[39] = "img/trngl4_4.png";
    imgFiles[40] = "img/trngl4_5.png";
    imgFiles[41] = "img/trngl4_6.png";
}

void TForm1::initImgDigits()
{
    imgDigitFiles[0] = "img/d1_1";
    imgDigitFiles[1] = "img/d1_2";
    imgDigitFiles[2] = "img/d1_3";
    imgDigitFiles[3] = "img/d1_4";
    imgDigitFiles[4] = "img/d1_5";
    imgDigitFiles[5] = "img/d1_6";
    imgDigitFiles[6] = "img/d2_1";
    imgDigitFiles[7] = "img/d2_2";
    imgDigitFiles[8] = "img/d2_3";
    imgDigitFiles[9] = "img/d2_4";
    imgDigitFiles[10] = "img/d2_5";
    imgDigitFiles[11] = "img/d2_6";
    imgDigitFiles[12] = "img/d3_1";
    imgDigitFiles[13] = "img/d3_2";
    imgDigitFiles[14] = "img/d3_3";
    imgDigitFiles[15] = "img/d3_4";
    imgDigitFiles[16] = "img/d3_5";
    imgDigitFiles[17] = "img/d3_6";
    imgDigitFiles[18] = "img/d4_1";
    imgDigitFiles[19] = "img/d4_2";
    imgDigitFiles[20] = "img/d4_3";
    imgDigitFiles[21] = "img/d4_4";
    imgDigitFiles[22] = "img/d4_5";
    imgDigitFiles[23] = "img/d4_6";
    imgDigitFiles[24] = "img/d5_1";
    imgDigitFiles[25] = "img/d5_2";
    imgDigitFiles[26] = "img/d5_3";
    imgDigitFiles[27] = "img/d5_4";
    imgDigitFiles[28] = "img/d5_5";
    imgDigitFiles[29] = "img/d5_6";
    imgDigitFiles[30] = "img/d6_1";
    imgDigitFiles[31] = "img/d6_2";
    imgDigitFiles[32] = "img/d6_3";
    imgDigitFiles[33] = "img/d6_4";
    imgDigitFiles[34] = "img/d6_5";
    imgDigitFiles[35] = "img/d6_6";
    imgDigitFiles[36] = "img/d7_1";
    imgDigitFiles[37] = "img/d7_2";
    imgDigitFiles[38] = "img/d7_3";
    imgDigitFiles[39] = "img/d7_4";
    imgDigitFiles[40] = "img/d7_5";
    imgDigitFiles[41] = "img/d7_6";
    imgDigitFiles[42] = "img/d8_1";
    imgDigitFiles[43] = "img/d8_2";
    imgDigitFiles[44] = "img/d8_3";
    imgDigitFiles[45] = "img/d8_4";
    imgDigitFiles[46] = "img/d8_5";
    imgDigitFiles[47] = "img/d8_6";
    imgDigitFiles[48] = "img/d9_1";
    imgDigitFiles[49] = "img/d9_2";
    imgDigitFiles[50] = "img/d9_3";
    imgDigitFiles[51] = "img/d9_4";
    imgDigitFiles[52] = "img/d9_5";
    imgDigitFiles[53] = "img/d9_6";
    imgDigitFiles[54] = "img/d0_1";
    imgDigitFiles[55] = "img/d0_2";
    imgDigitFiles[56] = "img/d0_3";
    imgDigitFiles[57] = "img/d0_4";
    imgDigitFiles[58] = "img/d0_5";
    imgDigitFiles[59] = "img/d0_6";
}

void TForm1::initWeights()
{
    float val;
    int i, k, cnt = 0;

    for (i = 0; i < N0_LEN; i++)
    {
        for (k = 0; k < N1_LEN; k++)
        {
            srand((cnt++ << 3) ^ 0x148BF269);
            val = rand() % 100;
            arrW1[i][k] = val / 100.0;
        }
    }
    for (i = 0; i < N1_LEN; i++)
    {
        for (k = 0; k < N2_LEN; k++)
        {
            srand((cnt++ << 2) ^ 0x145BF369);
            val = rand() % 100;
            arrW2[i][k] = val / 100.0;
        }
    }
    for (i = 0; i < N2_LEN; i++)
    {
        for (k = 0; k < N_GOAL_LEN; k++)
        {
            srand((cnt++ << 4) ^ 0x619BF269);
            val = rand() % 100;
            arrW3[i][k] = val / 100.0;
        }
    }

    for (i = 0; i < IN_N_LEN; i++)
    {
        for (k = 0; k < MN1_LEN; k++)
        {
            srand((cnt++ << 3) ^ 0x148BF269);
            val = rand() % 100;
            P1_W1[i][k] = val / 10000.0;
        }
    }
    for (i = 0; i < MN1_LEN; i++)
    {
        for (k = 0; k < MN2_LEN; k++)
        {
            srand((cnt++ << 2) ^ 0x145BF369);
            val = rand() % 100;
            P1_W2[i][k] = val / 10000.0;
        }
    }
    for (i = 0; i < MN2_LEN; i++)
    {
        for (k = 0; k < OUT_N_LEN; k++)
        {
            srand((cnt++ << 4) ^ 0x619BF269);
            val = rand() % 100;
            P1_W3[i][k] = val / 10000.0;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    String errStr, resStr, tmp;

#define IN_LEN 4
#define IN_QTY 10

#define GOAL_LEN 10
#define GOAL_QTY 10

    float inp[IN_QTY][IN_LEN] = {
        {0, 0, 0, 1},
        {0, 0, 1, 0},
        {0, 0, 1, 1},
        {0, 1, 0, 0},
        {0, 1, 0, 1},
        {0, 1, 1, 0},
        {0, 1, 1, 1},
        {1, 0, 0, 0},
        {1, 0, 0, 1},
        {1, 0, 1, 0}};

    float goal[GOAL_QTY][GOAL_LEN] = {
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},

    };

    for (int i = 0; i < IN_QTY; ++i)
    {
        for (int k = 0; k < IN_LEN; ++k)
        {
            if (!inp[i][k])
                inp[i][k] = -1.0;
        }
    }

    String err[10];
    for (int cnt = 0; cnt < G_cycleQty; cnt++)
    {

        if (!(cnt % 100))
        {
            lbl1->Caption = IntToStr(cnt);
            Application->ProcessMessages();
        }

        for (int inCnt = 0; inCnt < IN_QTY; ++inCnt)
        {
            mf->matrixMul(inp[inCnt], M_ARR(N0_LEN, N1_LEN, arrW1), arrN1);
            mf->getSigmoid(arrN1, N1_LEN, G_sigmoidTilt);

            mf->matrixMul(arrN1, M_ARR(N1_LEN, N2_LEN, arrW2), arrN2);
            mf->getSigmoid(arrN2, N2_LEN, G_sigmoidTilt);

            mf->matrixMul(arrN2, M_ARR(N2_LEN, N_GOAL_LEN, arrW3), arrGoal);
            mf->getSigmoid(arrGoal, N_GOAL_LEN, G_sigmoidTilt);

            // delta last layer
            for (int i = 0; i < N_GOAL_LEN; ++i)
            {
                arrDeltaGoal[i] = arrGoal[i] - goal[inCnt][i];
            }

            // delta prep;
            mf->matrixMul(M_ARR(N2_LEN, N_GOAL_LEN, arrW3), arrDeltaGoal, arrDeltaN2);
            mf->matrixMul(M_ARR(N1_LEN, N2_LEN, arrW2), arrDeltaN2, arrDeltaN1);

            for (int k = 0; k < N0_LEN; ++k)
            {
                for (int l = 0; l < N1_LEN; ++l)
                {
                    arrDeltaW1[k][l] = inp[inCnt][k] * arrDeltaN1[l];
                }
            }
            for (int k = 0; k < N1_LEN; ++k)
            {
                for (int l = 0; l < N2_LEN; ++l)
                {
                    arrDeltaW2[k][l] = arrN1[k] * arrDeltaN2[l];
                }
            }
            for (int k = 0; k < N2_LEN; ++k)
            {
                for (int l = 0; l < N_GOAL_LEN; ++l)
                {
                    arrDeltaW3[k][l] = arrN2[k] * arrDeltaGoal[l];
                }
            }

            for (int i = 0; i < N0_LEN; ++i)
            {
                for (int k = 0; k < N1_LEN; ++k)
                {
                    arrW1[i][k] -= arrDeltaW1[i][k] * G_alfa;
                }
            }

            for (int i = 0; i < N1_LEN; ++i)
            {
                for (int k = 0; k < N2_LEN; ++k)
                {
                    arrW2[i][k] -= arrDeltaW2[i][k] * G_alfa;
                }
            }
            for (int i = 0; i < N2_LEN; ++i)
            {
                for (int k = 0; k < N_GOAL_LEN; ++k)
                {
                    arrW3[i][k] -= arrDeltaW3[i][k] * G_alfa;
                }
            }
        }
    }
    edOut1->Text = FormatFloat("0.00000000", arrN2[1]);
    edOut2->Text = FormatFloat("0.00000000", arrN2[2]);
    edOut3->Text = FormatFloat("0.00000000", arrN2[3]);
    edOut4->Text = FormatFloat("0.00000000", arrN2[4]);
    edOut5->Text = FormatFloat("0.00000000", arrN2[5]);
    edOut6->Text = FormatFloat("0.00000000", arrN2[6]);
    edOut7->Text = FormatFloat("0.00000000", arrN2[7]);
    edOut8->Text = FormatFloat("0.00000000", arrN2[8]);
    edOut9->Text = FormatFloat("0.00000000", arrN2[9]);
    edOut10->Text = FormatFloat("0.00000000", arrN2[10]);

#undef IN_LEN
#undef IN_QTY
#undef GOAL_LEN
#undef GOAL_QTY
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edAlfaChange(TObject *Sender)
{
    if (TryStrToFloat(edAlfa->Text, G_alfa))
    {
        edAlfa->Color = clWindow;
    }
    else
    {
        edAlfa->Color = clRed;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edSigmodChange(TObject *Sender)
{
    G_sigmoidTilt = StrToInt(edSigmod->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edCycleQtyChange(TObject *Sender)
{
    G_cycleQty = StrToInt(edCycleQty->Text);
}
//---------------------------------------------------------------------------

void TForm1::loadInputsGoalsData()
{
    arrN0[0] = StrToFloat(edIn1->Text);
    arrN0[1] = StrToFloat(edIn2->Text);
    arrN0[2] = StrToFloat(edIn3->Text);
    arrN0[3] = StrToFloat(edIn4->Text);
    if (!arrN0[0])
        arrN0[0] = -1;
    if (!arrN0[1])
        arrN0[1] = -1;
    if (!arrN0[2])
        arrN0[2] = -1;
    if (!arrN0[3])
        arrN0[3] = -1;
}

void __fastcall TForm1::Button2Click(TObject *Sender)
{
    loadInputsGoalsData();

    float n1[N1_LEN];
    float n2[N2_LEN];
    float nGoal[N_GOAL_LEN];

    M_RESET_ARR(n1, N1_LEN)
    M_RESET_ARR(n2, N2_LEN)
    M_RESET_ARR(nGoal, N_GOAL_LEN)

    mf->matrixMul(arrN0, M_ARR(N0_LEN, N1_LEN, arrW1), n1);
    mf->getSigmoid(n1, N1_LEN, G_sigmoidTilt);
    mf->matrixMul(n1, M_ARR(N1_LEN, N2_LEN, arrW2), n2);
    mf->getSigmoid(n2, N2_LEN, G_sigmoidTilt);
    mf->matrixMul(n2, M_ARR(N2_LEN, N_GOAL_LEN, arrW3), nGoal);
    mf->getSigmoid(nGoal, N_GOAL_LEN, G_sigmoidTilt);

    edOut1->Text = FormatFloat("0.00000000", nGoal[0]);
    edOut2->Text = FormatFloat("0.00000000", nGoal[1]);
    edOut3->Text = FormatFloat("0.00000000", nGoal[2]);
    edOut4->Text = FormatFloat("0.00000000", nGoal[3]);
    edOut5->Text = FormatFloat("0.00000000", nGoal[4]);
    edOut6->Text = FormatFloat("0.00000000", nGoal[5]);
    edOut7->Text = FormatFloat("0.00000000", nGoal[6]);
    edOut8->Text = FormatFloat("0.00000000", nGoal[7]);
    edOut9->Text = FormatFloat("0.00000000", nGoal[8]);
    edOut10->Text = FormatFloat("0.00000000", nGoal[9]);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
    initWeights();
}
//---------------------------------------------------------------------------

void TForm1::getValFromFile(BYTE *val, int *meta, int pos)
{
    String s = "";
    int cnt = 0;
    char c;
    *meta = 0;
    *val = 0;
    int tmpVal;

    while (1)
    {
        if ((c = fgetc(fl)) == '\n')
        {
            *meta = 1;
            return;
        }
        if (c == 0x2C)
            break;

        s += c;
        cnt++;
        if (cnt > 5)
            break;
    }

    TryStrToInt(s, tmpVal);
    *val = (BYTE)tmpVal;
    return;
}

void __fastcall TForm1::Button5Click(TObject *Sender)
{
    FILE *tmpFl;
    int flCnt = 0, valCnt = 0;
    String pattFlName = "data/char_";
    String flName;
    string str;
    BYTE val;
    int meta;
    G_stop = false;
    char tmpChar;
    fl = fopen("train.csv", "r");
    if (!fl)
    {
        edInfo->Text = "Open \"train.csv\" file error";
        return;
    }

    while (!feof(fl))
    {
        if (G_stop)
            break;
        flName = pattFlName + IntToStr(flCnt++) + ".dat";
        str = flName.t_str();
        tmpFl = fopen(str.c_str(), "w");
        if (!(flCnt % 100))
            lbl1->Caption = IntToStr(flCnt);
        Application->ProcessMessages();
        while (1)
        {
            if (G_stop)
                break;
            getValFromFile(&val, &meta);
            if (!meta)
            {
                fputc(val, tmpFl);
            }
            else
            {
                break;
            }
        }

        fclose(tmpFl);
        if (meta == 2)
            break;
        //   if(flCnt==1000)break;
    }
    fclose(fl);
    edInfo->Text = "ok";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
    G_stop = true;
}
//---------------------------------------------------------------------------

void TForm1::scaleImg(float **imgArr, int maxSize, float scale, int w, int h)
{
	int prevX = 1, prevY = 1;
    float **tmpArr = new float* [maxSize];
    for (int i = 0; i < maxSize; i++){
        tmpArr[i] = new float[maxSize];
    }
    M_SET_MATRIX(tmpArr,-1,maxSize,maxSize)

    int newPixelPosX, newPixelPosY = 0;
    int maxX = w*scale <= maxSize ? w*scale : maxSize;
    int maxY = h*scale <= maxSize ? h*scale : maxSize;
    
    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){
			newPixelPosX = x * scale+1;
			if(newPixelPosX >= maxSize){
                break;
            }
			tmpArr[newPixelPosX][newPixelPosY] = imgArr[x][y];
			for(int subX = prevX+1; subX < newPixelPosX; subX++){
			   tmpArr[subX][newPixelPosY] = imgArr[x][y];
			}
			prevX = newPixelPosX;
        }

		newPixelPosY = y * scale+1;
        if(newPixelPosY >= maxY)break;
		if(newPixelPosY >= maxSize)break;

        for(int subY = prevY+1; subY < newPixelPosY; subY++){
			for(int subX = 0; subX < maxX; subX++){
			   tmpArr[subX][subY] = tmpArr[subX][subY-1];
			}
        }
		prevY = newPixelPosY;
    }

    for (int y = 0; y < maxSize; y++){
        for (int x = 0; x < maxSize; x++){
            imgArr[x][y] = tmpArr[x][y]; 
        }
    }  

    delete tmpArr; 
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	struct S_imgPos pos;
	loadImgToBitmap("testImg.png", bigImg, IMG_BIG_H, IMG_BIG_W);
	loadBitmapToArray(bigImg, G_tmpImgArr1, IMG_BIG_H, IMG_BIG_W);
	moveImgInArray(G_tmpImgArr1, IMG_BIG_H, IMG_POS_LEFT_TOP, &pos);	 
	scaleImg(G_tmpImgArr1, IMG_BIG_H, G_scaleImg, pos.width, pos.height);
}
//---------------------------------------------------------------------------

void TForm1::showImgFromArray(TImage *img, float **arr, int w, int h)
{

    img->Canvas->Rectangle(0,0,w,h);
	Application->ProcessMessages();

	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			if(arr[x][y] > -0.2)
				img->Canvas->Pixels[x][y] = clBlack;
		}
	}
}

void TForm1::moveImgInArray(float **imgArr, int maxSize, int position, S_imgPos *imgParam)
{
    struct S_imgPos pos;
    int startX, startY;
    float **tmpArr = new float *[maxSize];
    for(int i = 0; i < maxSize; i++){
        tmpArr[i] = new float[maxSize];
    }

    M_SET_MATRIX(tmpArr,-1,maxSize,maxSize)
    srchSnglImgPos(imgArr, &pos, maxSize, maxSize);

	// img set to center
    if(position == IMG_POS_CENTER){
        startX = (maxSize-pos.width)/2;
        startY = (maxSize-pos.height)/2;
    }
    // img set to left-top position
    if(position == IMG_POS_LEFT_TOP){
        startX = 1;
        startY = 1;
    }

	for (int x = 0; x < pos.width; x++){
		for (int y = 0; y < pos.height; y++){
			tmpArr[x+startX][y+startY] = imgArr[x+pos.xLetf][y+pos.yTop];
		}
	}
    *imgParam = pos;
 
	for (int x = 0; x < maxSize; x++){
		for (int y = 0; y < maxSize; y++){
			imgArr[x][y] = tmpArr[x][y];
		}
	}    
}


void TForm1::loadPattFromFiles()
{
    bool err = false;

    for (int i = 0; i < PATT_QTY; i++)
    {
        loadImgToSmallBitmap(imgFiles[i], img1);
        loadSmallImgToArray(P1_patt[i]);
    }
    if (!err)
        edInfo->Text = "images was loaded to patterns";
    return;
}
//---------------------------------------------------------------------------

void TForm1::loadImgToSmallBitmap(String flName, TImage *bitmap)
{
    TRect rct;
    rct.Left = 0;
    rct.Top = 0;
    rct.Right = 28;
    rct.Bottom = 28;

    string mFlName = flName.t_str();

    TPngImage *img = new TPngImage();
    img->LoadFromFile(mFlName.c_str());
    bitmap->Stretch = true;
    bitmap->Picture->Bitmap->Height = 28;
    bitmap->Picture->Bitmap->Width = 28;
    bitmap->Picture->Bitmap->Canvas->StretchDraw(rct, img);
    delete img;
}
//---------------------------------------------------------------------------

void TForm1::loadImgToBitmap(String flName, TImage *bitmap, int h, int w)
{
    TRect rct;
    rct.Left = 0;
    rct.Top = 0;
    rct.Right = w;
    rct.Bottom = h;

    string mFlName = flName.t_str();

    TPngImage *img = new TPngImage();
    img->LoadFromFile(mFlName.c_str());
    bitmap->Stretch = true;
    bitmap->Picture->Bitmap->Height = h;
    bitmap->Picture->Bitmap->Width = w;
    bitmap->Picture->Bitmap->Canvas->StretchDraw(rct, img);
    delete img;
}
//---------------------------------------------------------------------------

void TForm1::loadBitmapToArray(TImage *bitmap, float **arr, int h, int w)
{
    TColor color;
    BYTE a, b, c;
    WORD tmpVal, cnt = 0;

    for (int i = 0; i < w; i++)
    {
        for (int k = 0; k < h; k++)
        {
            color = bitmap->Canvas->Pixels[i][k];
            a = GetRValue(color);
            b = GetGValue(color);
            c = GetBValue(color);
            tmpVal = ~((a + b + c) / 3);
            arr[i][k] = (BYTE)tmpVal / 127.5 - 1;
        }
    }
}
//---------------------------------------------------------------------------

void TForm1::srchSnglImgPos(float **G_tmpImgArr1, S_imgPos *pos, int h, int w)
{

    bool stop = false;
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
			if (G_tmpImgArr1[x][y] > -0.8)
            {
                stop = true;
				pos->yTop = y-1;
				break;
			}
		}
		if (stop)
			break;
	}

	stop = false;
	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			if (G_tmpImgArr1[x][y] > -0.8)
			{
				stop = true;
				pos->xLetf = x;
                break;
            }
        }
        if (stop)
            break;
    }

    stop = false;
    for (int y = h - 1; y >= 0; y--)
    {
        for (int x = w - 1; x >= 0; x--)
        {
			if (G_tmpImgArr1[x][y] > -0.8)
            {
                stop = true;
				pos->yBottom = y+1;
                break;
            }
        }
        if (stop)
            break;
    }

    stop = false;
    for (int x = w - 1; x >= 0; x--)
    {
        for (int y = h - 1; y >= 0; y--)
        {
            if (G_tmpImgArr1[x][y] > -0.8)
            {
                stop = true;
                pos->xRight = x+1;
                break;
            }
        }
        if (stop)
            break;
    }
	pos->width  = pos->xRight  - pos->xLetf;
	pos->height = pos->yBottom - pos->yTop;
    
}

void TForm1::loadSmallImgToArray(float *arr)
{
    TColor color;
    BYTE a, b, c;
    WORD tmpVal, cnt = 0;

    for (int i = 0; i < 28; i++)
    {

        for (int k = 0; k < 28; k++)
        {
            color = img1->Canvas->Pixels[i][k];
            a = GetRValue(color);
            b = GetGValue(color);
            c = GetBValue(color);

            tmpVal = ~((a + b + c) / 3);

            arr[cnt++] = (BYTE)tmpVal / 127.5 - 1;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
    loadPattFromFiles();
}
//---------------------------------------------------------------------------

void TForm1::scaleArray(float *arr, int len)
{
    float max = 0;
    int order;
    float tmp;
    for (int i = 0; i < len; i++)
    {
        if (max < (abs(arr[i])))
            max = (abs(arr[i]));
    }
    order = log10(max) + 1;
    tmp = pow(10, (float)order);
    for (int i = 0; i < len; i++)
    {
        arr[i] = arr[i] / tmp;
    }
}

void __fastcall TForm1::Button7Click(TObject *Sender)
{
    String errStr, resStr, tmp;
    G_stop = false;
    float tmpVals[MN1_LEN];
    lb1->Clear();
    Application->ProcessMessages();
    for (int cnt = 0; cnt < G_cycleQty; cnt++)
    {

        if (!(cnt % 100))
        {
            lbl1->Caption = IntToStr(cnt);
            lb1->Items->Add("------------------------------------");
            for (int i = 0; i < OUT_N_LEN; i++)
            {
                lb1->Items->Add(P1_deltaOutN[i]);
            }
            Application->ProcessMessages();
        }

        if (G_stop)
            break;
        for (int pattCnt = 0; pattCnt < PATT_QTY; ++pattCnt)
        {
            mf->matrixMul(P1_patt[pattCnt], M_ARR(IN_N_LEN, MN1_LEN, P1_W1), P1_mN1);
            //    scaleArray(P1_mN1, MN1_LEN);
            if (chk1->Checked)
                mf->getSigmoid(P1_mN1, MN1_LEN, G_sigmoidTilt);

            mf->matrixMul(P1_mN1, M_ARR(MN1_LEN, MN2_LEN, P1_W2), P1_mN2);
            //    scaleArray(P1_mN2, MN2_LEN);
            if (chk2->Checked)
                mf->getSigmoid(P1_mN2, MN2_LEN, G_sigmoidTilt);

            mf->matrixMul(P1_mN2, M_ARR(MN2_LEN, OUT_N_LEN, P1_W3), P1_outN);
            //    scaleArray(P1_outN, OUT_N_LEN);
            if (chk3->Checked)
                mf->getSigmoid(P1_outN, OUT_N_LEN, G_sigmoidTilt);

            // delta last layer
            for (int i = 0; i < OUT_N_LEN; ++i)
            {
                P1_deltaOutN[i] = (P1_outN[i] - P1_goal[pattCnt][i]);
            }

            // delta prep;
            mf->matrixMul(M_ARR(MN2_LEN, OUT_N_LEN, P1_W3), P1_deltaOutN, P1_deltaMN2);
            mf->matrixMul(M_ARR(MN1_LEN, MN2_LEN, P1_W2), P1_deltaMN2, P1_deltaMN1);

            for (int k = 0; k < IN_N_LEN; ++k)
            {
                for (int l = 0; l < MN1_LEN; ++l)
                {
                    P1_deltaW1[k][l] = P1_patt[pattCnt][k] * P1_deltaMN1[l];
                }
            }
            for (int k = 0; k < MN1_LEN; ++k)
            {
                for (int l = 0; l < MN2_LEN; ++l)
                {
                    P1_deltaW2[k][l] = P1_mN1[k] * P1_deltaMN2[l];
                }
            }
            for (int k = 0; k < MN2_LEN; ++k)
            {
                for (int l = 0; l < OUT_N_LEN; ++l)
                {
                    P1_deltaW3[k][l] = P1_mN2[k] * P1_deltaOutN[l];
                }
            }

            for (int i = 0; i < IN_N_LEN; ++i)
            {
                for (int k = 0; k < MN1_LEN; ++k)
                {
                    P1_W1[i][k] -= P1_deltaW1[i][k] * G_alfa;
                }
            }

            for (int i = 0; i < MN1_LEN; ++i)
            {
                for (int k = 0; k < MN2_LEN; ++k)
                {
                    P1_W2[i][k] -= P1_deltaW2[i][k] * G_alfa;
                }
            }
            for (int i = 0; i < MN2_LEN; ++i)
            {
                for (int k = 0; k < OUT_N_LEN; ++k)
                {
                    P1_W3[i][k] -= P1_deltaW3[i][k] * G_alfa;
                }
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender)
{

    testFunc("test_img1.png");
}
//---------------------------------------------------------------------------

void TForm1::testFunc(String flName)
{
    float in[IN_N_LEN];

    float n1[MN1_LEN];
    float n2[MN2_LEN];
    float nGoal[OUT_N_LEN];

    M_RESET_ARR(n1, MN1_LEN)
    M_RESET_ARR(n2, MN2_LEN)
    M_RESET_ARR(nGoal, OUT_N_LEN)

    loadImgToSmallBitmap(flName, img1);
    loadSmallImgToArray(in);

    mf->matrixMul(in, M_ARR(IN_N_LEN, MN1_LEN, P1_W1), n1);
    if (chk1->Checked)
        mf->getSigmoid(n1, MN1_LEN, G_sigmoidTilt);

    mf->matrixMul(n1, M_ARR(MN1_LEN, MN2_LEN, P1_W2), n2);
    if (chk2->Checked)
        mf->getSigmoid(n2, MN2_LEN, G_sigmoidTilt);

    mf->matrixMul(n2, M_ARR(MN2_LEN, OUT_N_LEN, P1_W3), nGoal);
    if (chk3->Checked)
        mf->getSigmoid(nGoal, OUT_N_LEN, G_sigmoidTilt);

    edOut1->Text = FormatFloat("0.00000000", nGoal[0]);
    edOut2->Text = FormatFloat("0.00000000", nGoal[1]);
    edOut3->Text = FormatFloat("0.00000000", nGoal[2]);
    edOut4->Text = FormatFloat("0.00000000", nGoal[3]);
    edOut5->Text = FormatFloat("0.00000000", nGoal[4]);
    edOut6->Text = FormatFloat("0.00000000", nGoal[5]);
    edOut7->Text = FormatFloat("0.00000000", nGoal[6]);
    edOut8->Text = FormatFloat("0.00000000", -11);
    edOut9->Text = FormatFloat("0.00000000", -11);
    edOut10->Text = FormatFloat("0.00000000", -11);
}

void __fastcall TForm1::Button12Click(TObject *Sender)
{
    testFunc("test_img2.png");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button13Click(TObject *Sender)
{
    testFunc("test_img3.png");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button14Click(TObject *Sender)

{
    testFunc("test_img4.png");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button8Click(TObject *Sender)
{
 struct S_imgPos pos;
 
 moveImgInArray(G_tmpImgArr1, IMG_BIG_H, IMG_POS_CENTER, &pos); 
 showImgFromArray(bigImg, G_tmpImgArr1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edScaleImgChange(TObject *Sender)
{
	if (TryStrToFloat(edScaleImg->Text, G_scaleImg))
    {
		edScaleImg->Color = clWindow;
    }
    else
    {
		edScaleImg->Color = clRed;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
 showImgFromArray(bigImg, G_tmpImgArr1);
}
//---------------------------------------------------------------------------

float __fastcall TForm1::getScale(S_imgPos *pos, float size)
{
    float scale;

    if (pos->height > pos->width){
        scale = size / (float)pos->height;
	}else{
		scale = size / (float)pos->width;
    }

    return scale;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::trimArray(float **mx1, float **mx2, int w, int h)
{
    for(int y=0; y < h; y++){
        for(int x = 0; x < w; x++){
            mx2[y][x] = mx1[y][x];
        }
    }
}

void __fastcall TForm1::btSearchCharClick(TObject *Sender)
{
	struct S_imgPos pos;
    float scale;
    int w,h;

    float tmpArr[IMG_SMALL_H][IMG_SMALL_W];

    M_SET_MATRIX(G_smallTmpImgArr1,-1,IMG_SMALL_W, IMG_SMALL_H)
	loadImgToBitmap("testImg.png", bigImg, IMG_BIG_H, IMG_BIG_W);
	loadBitmapToArray(bigImg, G_tmpImgArr1, IMG_BIG_H, IMG_BIG_W);
	moveImgInArray(G_tmpImgArr1, IMG_BIG_H, IMG_POS_LEFT_TOP, &pos);	
	scale = getScale(&pos, 24.0);
	scaleImg(G_tmpImgArr1, 24, scale, pos.width, pos.height);
     
    trimArray(G_tmpImgArr1, G_smallTmpImgArr1, 24,24);
    
    moveImgInArray(G_smallTmpImgArr1, IMG_SMALL_H, IMG_POS_CENTER, &pos); 
    showImgFromArray(img1, G_smallTmpImgArr1, IMG_SMALL_W, IMG_SMALL_H);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button15Click(TObject *Sender)
{
    #define MAX_IMG_SIZE 24
    bool err = false;
	struct S_imgPos pos;
    float scale;
    int w,h;

    for (int i = 0; i < PATT_QTY; i++)
    {
        M_SET_ARR(P1_patt[i], -1, IN_N_LEN) 
        M_SET_MATRIX(G_smallTmpImgArr1, -1, IMG_SMALL_H, IMG_SMALL_W)
        
        loadImgToBitmap(imgFiles[i], bigImg, IMG_BIG_H, IMG_BIG_W);
        loadBitmapToArray(bigImg, G_tmpImgArr1, IMG_BIG_H, IMG_BIG_W); 
        moveImgInArray(G_tmpImgArr1, IMG_BIG_H, IMG_POS_LEFT_TOP, &pos);	
        scale = getScale(&pos, MAX_IMG_SIZE);
        scaleImg(G_tmpImgArr1, MAX_IMG_SIZE, scale, pos.width, pos.height);
        
        trimArray(G_tmpImgArr1, G_smallTmpImgArr1, MAX_IMG_SIZE,MAX_IMG_SIZE);
        moveImgInArray(G_smallTmpImgArr1, IMG_SMALL_H, IMG_POS_CENTER, &pos); 
         
		M_COPY_MX_TO_ARR(G_smallTmpImgArr1,IMG_SMALL_H,IMG_SMALL_W,P1_patt[i])
		lbl1->Caption = i;
		Application->ProcessMessages();
    }
    if (!err)
        edInfo->Text = "images was loaded to patterns";
    return;
    #undef MAX_IMG_SIZE
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button16Click(TObject *Sender)
{
  int pattNum = StrToInt(edPattNum->Text);

  M_GET_MATRIX(IMG_SMALL_H,IMG_SMALL_W,P1_patt[pattNum],G_smallTmpImgArr1);
  showImgFromArray(img1,G_smallTmpImgArr1, IMG_SMALL_H, IMG_SMALL_W);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btTestClick(TObject *Sender)
{
#define MAX_IMG_SIZE 24
    
    struct S_imgPos pos;
    float scale;

    float in[IN_N_LEN];
    float n1[MN1_LEN];
    float n2[MN2_LEN];
    float nGoal[OUT_N_LEN];

    M_RESET_ARR(n1, MN1_LEN)
    M_RESET_ARR(n2, MN2_LEN)
    M_RESET_ARR(nGoal, OUT_N_LEN)

    M_SET_MATRIX(G_smallTmpImgArr1, -1, IMG_SMALL_H, IMG_SMALL_W)

    loadImgToBitmap("testImg1.png", bigImg, IMG_BIG_H, IMG_BIG_W);
    loadBitmapToArray(bigImg, G_tmpImgArr1, IMG_BIG_H, IMG_BIG_W); 
    moveImgInArray(G_tmpImgArr1, IMG_BIG_H, IMG_POS_LEFT_TOP, &pos);	
    scale = getScale(&pos, MAX_IMG_SIZE);
    scaleImg(G_tmpImgArr1, MAX_IMG_SIZE, scale, pos.width, pos.height);
    
    trimArray(G_tmpImgArr1, G_smallTmpImgArr1, MAX_IMG_SIZE,MAX_IMG_SIZE);
    moveImgInArray(G_smallTmpImgArr1, IMG_SMALL_H, IMG_POS_CENTER, &pos); 
    showImgFromArray(img1,G_smallTmpImgArr1, IMG_SMALL_H, IMG_SMALL_W);
    
    M_COPY_MX_TO_ARR(G_smallTmpImgArr1,IMG_SMALL_H,IMG_SMALL_W,in)

    mf->matrixMul(in, M_ARR(IN_N_LEN, MN1_LEN, P1_W1), n1);
    if (chk1->Checked)
        mf->getSigmoid(n1, MN1_LEN, G_sigmoidTilt);

    mf->matrixMul(n1, M_ARR(MN1_LEN, MN2_LEN, P1_W2), n2);
    if (chk2->Checked)
        mf->getSigmoid(n2, MN2_LEN, G_sigmoidTilt);

    mf->matrixMul(n2, M_ARR(MN2_LEN, OUT_N_LEN, P1_W3), nGoal);
    if (chk3->Checked)
        mf->getSigmoid(nGoal, OUT_N_LEN, G_sigmoidTilt);

    edOut1->Text = FormatFloat("0.00000000", nGoal[0]);
    edOut2->Text = FormatFloat("0.00000000", nGoal[1]);
    edOut3->Text = FormatFloat("0.00000000", nGoal[2]);
    edOut4->Text = FormatFloat("0.00000000", nGoal[3]);
    edOut5->Text = FormatFloat("0.00000000", nGoal[4]);
    edOut6->Text = FormatFloat("0.00000000", nGoal[5]);
    edOut7->Text = FormatFloat("0.00000000", nGoal[6]);
    edOut8->Text = FormatFloat("0.00000000", -11);
    edOut9->Text = FormatFloat("0.00000000", -11);
    edOut10->Text = FormatFloat("0.00000000", -11);

#undef MAX_IMG_SIZE
}
//---------------------------------------------------------------------------

