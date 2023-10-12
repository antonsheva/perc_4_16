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

#define IMG_BIG_H   140
#define IMG_BIG_W   140
#define IMG_SMALL_H 28
#define IMG_SMALL_W 28
#define SYM_SIZE    50

#define LAYER_QTY   4

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



#define PATT_FIGURES_7 0
#define PATT_DIGITS_10 0
#define PATT_ABVGD_33  1

#if     PATT_DIGITS_10
#include "patterns/PATT_DIGITS_10.cpp"
#elif   PATT_FIGURES_7
#include "patterns/PATT_FIGURES_7.cpp"
#elif   PATT_ABVGD_33
#include "patterns/PATT_ABVGD_33.cpp"
#endif

#define SHEET_H 400
#define SHEET_W 400
 

float P1_patt[PATT_QTY][IN_N_LEN];
// float **P1_patt;


float P1_inN[IN_N_LEN];
float P1_mN1[MN1_LEN];
float P1_mN2[MN2_LEN];
float P1_outN[OUT_N_LEN];

// float P1_W1[IN_N_LEN][MN1_LEN];
// float P1_W2[MN1_LEN][MN2_LEN];
// float P1_W3[MN2_LEN][OUT_N_LEN];
float **P1_W1;
float **P1_W2;
float **P1_W3;

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

float **G_imgSheetArr;
float **G_symbolMx;

AFuncs *mf;
FILE *fl;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent *Owner)
    : TForm(Owner)
{
    G_alfa = 0.0001;
    G_cycleQty = 10000;
    G_sigmoidTilt = 5;
	G_stop = false;
	G_scaleImg = 1;
	G_spaceBtwnSymX = 3;
    G_spaceBtwnSymY = 3;

    G_extBoardLeft = 2;
    G_extBoardRight = 2;
    G_extBoardTop = 2;
    G_extBoardBottom = 2;

    initNnParameters();

    initArrays();
    initWeights();
}

void TForm1::initArrays()
{
       P1_W1 = new float* [IN_N_LEN];
       for (int i = 0; i < IN_N_LEN; i++){
    	   P1_W1[i] = new float[MN1_LEN];
       }
       P1_W2 = new float* [MN1_LEN];
       for (int i = 0; i < MN1_LEN; i++){
    	   P1_W2[i] = new float[MN2_LEN];
       }
       P1_W3 = new float* [MN2_LEN];
       for (int i = 0; i < MN2_LEN; i++){
           P1_W3[i] = new float[OUT_N_LEN];
       }

    //    P1_patt = new double* [PATT_QTY];
    //    for (int i = 0; i < PATT_QTY; i++){
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

    G_imgSheetArr = new float *[SHEET_W];
    for (int i = 0; i < SHEET_H; i++){
        G_imgSheetArr[i] = new float[SHEET_H];
    } 

    G_symbolMx = new float *[SYM_SIZE];
    for(int i = 0; i < SYM_SIZE; i++){
        G_symbolMx[i] = new float[SYM_SIZE];
    }

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
            P1_W1[i][k] = val / 100.0;
        }
    }
    for (i = 0; i < MN1_LEN; i++)
    {
        for (k = 0; k < MN2_LEN; k++)
        {
            srand((cnt++ << 2) ^ 0x145BF369);
            val = rand() % 100;
            P1_W2[i][k] = val / 100.0;
        }
    }
    for (i = 0; i < MN2_LEN; i++)
    {
        for (k = 0; k < OUT_N_LEN; k++)
        {
            srand((cnt++ << 4) ^ 0x619BF269);
            val = rand() % 100;
            P1_W3[i][k] = val / 100.0;
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

void TForm1::moveImgInArray(float **mxImg, int mxSide, int position, S_imgPos *imgParam)
{
    struct S_imgPos pos;
    int startX, startY;
    float **tmpArr = new float *[mxSide];
    for(int i = 0; i < mxSide; i++){
        tmpArr[i] = new float[mxSide];
    }

    M_SET_MATRIX(tmpArr,-1,mxSide,mxSide)
    srchSnglImgPos(mxImg, &pos, mxSide, mxSide);

	// img set to center
    if(position == IMG_POS_CENTER){
        startX = (mxSide-pos.width)/2;
        startY = (mxSide-pos.height)/2;
    }
    // img set to left-top position
    if(position == IMG_POS_LEFT_TOP){
        startX = 1;
        startY = 1;
    }

	for (int x = 0; x < pos.width; x++){
		for (int y = 0; y < pos.height; y++){
			tmpArr[x+startX][y+startY] = mxImg[x+pos.xLetf][y+pos.yTop];
		}
	}
    *imgParam = pos;
 
	for (int x = 0; x < mxSide; x++){
		for (int y = 0; y < mxSide; y++){
			mxImg[x][y] = tmpArr[x][y];
		}
	}   

    delete tmpArr; 
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

        if (!(cnt % 100)){
            lbl1->Caption = IntToStr(cnt);
            lb1->Items->Add("------------------------------------");
            for (int i = 0; i < OUT_N_LEN; i++){
                lb1->Items->Add(P1_deltaOutN[i]);}

            Application->ProcessMessages();
        }

        if (G_stop){
            G_stop = false;
            break;
        }
        for (int pattCnt = 0; pattCnt < PATT_QTY; ++pattCnt){
			mf->matrixMul(P1_patt[pattCnt], IN_N_LEN, MN1_LEN, P1_W1, P1_mN1);
            normalizationData(P1_mN1, MN1_LEN);
			if (chk1->Checked)
				mf->getSigmoid(P1_mN1, MN1_LEN, G_sigmoidTilt);

			mf->matrixMul(P1_mN1, MN1_LEN, MN2_LEN, P1_W2, P1_mN2);
//			 normalizationData(P1_mN2, MN2_LEN);
			if (chk2->Checked)
				mf->getSigmoid(P1_mN2, MN2_LEN, G_sigmoidTilt);

			mf->matrixMul(P1_mN2, MN2_LEN, OUT_N_LEN, P1_W3, P1_outN);
//			normalizationData(P1_outN, OUT_N_LEN);
			if (chk3->Checked)
				mf->getSigmoid(P1_outN, OUT_N_LEN, G_sigmoidTilt);

			// delta last layer
			for (int i = 0; i < OUT_N_LEN; ++i){
				P1_deltaOutN[i] = (P1_outN[i] - P1_goal[pattCnt][i]);}

			// delta prep;
			mf->matrixMul(MN2_LEN, OUT_N_LEN, P1_W3, P1_deltaOutN, P1_deltaMN2);
//            normalizationData(P1_deltaMN2, MN2_LEN);
			mf->matrixMul(MN1_LEN, MN2_LEN, P1_W2, P1_deltaMN2, P1_deltaMN1);
//			normalizationData(P1_deltaMN1, MN1_LEN);

			for (int k = 0; k < IN_N_LEN; ++k){
                for (int l = 0; l < MN1_LEN; ++l){
                    P1_deltaW1[k][l] = P1_patt[pattCnt][k] * P1_deltaMN1[l];
                }
                // normalizationData(P1_deltaW1[k], MN1_LEN);
            }


            for (int k = 0; k < MN1_LEN; ++k){
                for (int l = 0; l < MN2_LEN; ++l){
                    P1_deltaW2[k][l] = P1_mN1[k] * P1_deltaMN2[l];
                }
                // normalizationData(P1_deltaW2[k], MN2_LEN);        
            }

            for (int k = 0; k < MN2_LEN; ++k){
                for (int l = 0; l < OUT_N_LEN; ++l){
                    P1_deltaW3[k][l] = P1_mN2[k] * P1_deltaOutN[l];
                }
                // normalizationData(P1_deltaW3[k], OUT_N_LEN);
            }

            for (int i = 0; i < IN_N_LEN; ++i){
                for (int k = 0; k < MN1_LEN; ++k){
                    P1_W1[i][k] -= P1_deltaW1[i][k] * G_alfa;}}

            for (int i = 0; i < MN1_LEN; ++i){
                for (int k = 0; k < MN2_LEN; ++k){
                    P1_W2[i][k] -= P1_deltaW2[i][k] * G_alfa;}}

            for (int i = 0; i < MN2_LEN; ++i){
                for (int k = 0; k < OUT_N_LEN; ++k){
                    P1_W3[i][k] -= P1_deltaW3[i][k] * G_alfa;}}
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

    mf->matrixMul(in, IN_N_LEN, MN1_LEN, P1_W1, n1);
    normalizationData(n1, MN1_LEN);
    if (chk1->Checked)
        mf->getSigmoid(n1, MN1_LEN, G_sigmoidTilt);

    mf->matrixMul(n1, MN1_LEN, MN2_LEN, P1_W2, n2);
//	normalizationData(n2, MN2_LEN);
	if (chk2->Checked)
		mf->getSigmoid(n2, MN2_LEN, G_sigmoidTilt);

	mf->matrixMul(n2, MN2_LEN, OUT_N_LEN, P1_W3, nGoal);
//	normalizationData(nGoal, OUT_N_LEN);
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

void __fastcall TForm1::trimArray(float **mx1, float **mx2, int w, int h, int startX, int startY)
{
    for(int y=0; y < h; y++){
        for(int x = 0; x < w; x++){
            mx2[y][x] = mx1[y+startY][x+startX];
        }
    }
}


void __fastcall TForm1::Button15Click(TObject *Sender)
{
    #define PATT_SIZE 24
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
        scale = getScale(&pos, PATT_SIZE);
        scaleImg(G_tmpImgArr1, PATT_SIZE, scale, pos.width, pos.height);
        
        trimArray(G_tmpImgArr1, G_smallTmpImgArr1, PATT_SIZE,PATT_SIZE);
        moveImgInArray(G_smallTmpImgArr1, IMG_SMALL_H, IMG_POS_CENTER, &pos); 
         
		M_COPY_MX_TO_ARR(G_smallTmpImgArr1,IMG_SMALL_H,IMG_SMALL_W,P1_patt[i])
		lbl1->Caption = i;
		Application->ProcessMessages();
    }
    if (!err)
        edInfo->Text = "images was loaded to patterns";
    return;
    #undef PATT_SIZE
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
#define PATT_SIZE 24
    
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
    scale = getScale(&pos, PATT_SIZE);
    scaleImg(G_tmpImgArr1, PATT_SIZE, scale, pos.width, pos.height);
    
    trimArray(G_tmpImgArr1, G_smallTmpImgArr1, PATT_SIZE,PATT_SIZE);
    moveImgInArray(G_smallTmpImgArr1, IMG_SMALL_H, IMG_POS_CENTER, &pos); 
    showImgFromArray(img1,G_smallTmpImgArr1, IMG_SMALL_H, IMG_SMALL_W);
    
    M_COPY_MX_TO_ARR(G_smallTmpImgArr1,IMG_SMALL_H,IMG_SMALL_W,in)

    mf->matrixMul(in, IN_N_LEN, MN1_LEN, P1_W1, n1);
    normalizationData(n1, MN1_LEN);
    if (chk1->Checked)
        mf->getSigmoid(n1, MN1_LEN, G_sigmoidTilt);

    mf->matrixMul(n1, MN1_LEN, MN2_LEN, P1_W2, n2);
    if (chk2->Checked)
        mf->getSigmoid(n2, MN2_LEN, G_sigmoidTilt);

    mf->matrixMul(n2, MN2_LEN, OUT_N_LEN, P1_W3, nGoal);
    if (chk3->Checked)
        mf->getSigmoid(nGoal, OUT_N_LEN, G_sigmoidTilt);

	showResult(nGoal);

#undef PATT_SIZE
}
//---------------------------------------------------------------------------

void __fastcall TForm1::normalizationData(float *dataArr, int len, float minRange, float maxRange)
{
    float min = 3.4e+38, max = -3.4e+38;
    float range = maxRange - minRange;
    float tmpArr[MX_ARR_LEN];
    for(int i=0; i<len; i++){
        if(dataArr[i]<min)min = dataArr[i];
        if(dataArr[i]>max)max = dataArr[i];
    }

    for(int i=0; i<len; i++){
        tmpArr[i] = ((dataArr[i]-min)/(max-min))*range + minRange;
    }
    for(int i=0; i<len; i++){
        dataArr[i] = tmpArr[i];
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btLoadDataSheetClick(TObject *Sender)
{
	loadImgToBitmap("dataSheet.png", imgSht, SHEET_H, SHEET_W);
    loadBitmapToArray(imgSht, G_imgSheetArr, SHEET_H,SHEET_W);
}
//---------------------------------------------------------------------------

int TForm1::checkNewSymbol(int x, int y, S_coords *crd, int len)
{
    for(int i=0; i<len; i++){
		if((crd[i].xLeft < x)&&(crd[i].xRight > x)&&(crd[i].yTop < y)&&(crd[i].yBottom > y)){
			return crd[i].xRight;
		}
    }
    return -1; 
}
//---------------------------------------------------------------------------

int TForm1::searchSymbols(float **arr, S_coords *crd)
{
    int x1=0,x2=-1,y1=-1,y2=-1;
    int zeroCnt = 0;

    int tmp;
    int symQty=0;
    struct S_coords tmpCrd;
 
	bool stop = false;
	for(int y=0; y<SHEET_W; y++){
		for(int x=0; x<SHEET_H; x++){
			if(arr[x][y] > -0.5){
                tmp = checkNewSymbol(x,y, crd, symQty);
                if(tmp != -1){
					x = tmp;
                }else{
				    getSymbolCoords(x, y, arr, &tmpCrd);
                    crd[symQty] = tmpCrd;
                    symQty++;

                    imgSht->Canvas->MoveTo(tmpCrd.xLeft,tmpCrd.yTop);
                    imgSht->Canvas->LineTo(tmpCrd.xRight,tmpCrd.yTop);
                    imgSht->Canvas->LineTo(tmpCrd.xRight,tmpCrd.yBottom);
                    imgSht->Canvas->LineTo(tmpCrd.xLeft,tmpCrd.yBottom);
                    imgSht->Canvas->LineTo(tmpCrd.xLeft,tmpCrd.yTop);
                    Application->ProcessMessages();                   
                }
			}
			if(stop)break;
		}
		if(stop)break;
	}
    return symQty;
}

void TForm1::getSymbolCoords(int x, int y, float **arr, S_coords *crd)
{
    int x1=x,x2=x,y1=y,y2=y;
	int zeroX=0, zeroY=0;
	int cntX=0, cntY=0;
	int tmpX, tmpY;
	while(zeroY < G_spaceBtwnSymY){
		zeroX=0;
        cntX=0;
		while (zeroX < G_spaceBtwnSymX)
		{
			if(arr[x1 - cntX++][y + cntY] > -0.5){
                zeroY=0;
                zeroX=0;
            }else zeroX++;
        }
        x1 = x1 - cntX + G_spaceBtwnSymX;

        cntX  = 0;
        zeroX = 0;
        while (zeroX < G_spaceBtwnSymX)
		{
			if(arr[x2 + cntX++][y+cntY] > -0.5){
				zeroY=0;
                zeroX=0;
            }else zeroX++;
        }
        x2 = x2 + cntX - G_spaceBtwnSymX;     
        for(int i = x1; i <= x2; i++)if(arr[i][y+cntY] > -0.5)zeroY=0;
        zeroY++;
		cntY++;
	}
	 
	x1 -= G_extBoardLeft;
	x2 += G_extBoardRight;
	y1 -= G_extBoardTop;
	y2 =  cntY+y-G_spaceBtwnSymY+G_extBoardBottom;

	crd->xLeft=x1;
	crd->xRight=x2;
	crd->yTop=y1;
	crd->yBottom=y2;


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
    #define PATT_SIZE 24
    float scale;
    int x;
    int y;
    int xSize;
    int ySize;
	int symQty = searchSymbols(G_imgSheetArr, G_crds);
    S_imgPos pos;

    for(int i=0; i< symQty; i++){
        M_SET_ARR(P1_patt[i], -1, IN_N_LEN)
        M_SET_MATRIX(G_symbolMx,-1,SYM_SIZE,SYM_SIZE)
        M_SET_MATRIX(G_smallTmpImgArr1, -1, IMG_SMALL_H, IMG_SMALL_W)
		y = G_crds[i].xLeft;
        x = G_crds[i].yTop;
		ySize = G_crds[i].xRight - G_crds[i].xLeft;
        xSize = G_crds[i].yBottom - G_crds[i].yTop;
        trimArray(G_imgSheetArr,G_symbolMx, xSize,ySize, x,y);
        moveImgInArray(G_symbolMx,SYM_SIZE,IMG_POS_LEFT_TOP,&pos);
        scale = getScale(&pos, PATT_SIZE);
        scaleImg(G_symbolMx, PATT_SIZE, scale, pos.width, pos.height);

        trimArray(G_symbolMx, G_smallTmpImgArr1, PATT_SIZE,PATT_SIZE);
        moveImgInArray(G_smallTmpImgArr1, IMG_SMALL_H, IMG_POS_CENTER, &pos); 

        M_COPY_MX_TO_ARR(G_smallTmpImgArr1,IMG_SMALL_H,IMG_SMALL_W,P1_patt[i])
		lbl1->Caption = i;
		Application->ProcessMessages();
    }


    #undef PATT_SIZE
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edSpaceXChange(TObject *Sender)
{
	G_spaceBtwnSymX = StrToInt(edSpaceX->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edSpaceYChange(TObject *Sender)
{
	G_spaceBtwnSymY = StrToInt(edSpaceY->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edExtLeftChange(TObject *Sender)
{
  G_extBoardLeft = StrToInt(edExtLeft->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edExtRightChange(TObject *Sender)
{
  G_extBoardRight = StrToInt(edExtRight->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edExtTopChange(TObject *Sender)
{
  G_extBoardTop = StrToInt(edExtTop->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edExtBottomChange(TObject *Sender)
{
  G_extBoardBottom = StrToInt(edExtBottom->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
    int symNumber = StrToInt(edSymNum->Text);
    int x = G_crds[symNumber].xLeft;
    int y = G_crds[symNumber].yTop;
    int xSize = G_crds[symNumber].xRight - G_crds[symNumber].xLeft;
    int ySize = G_crds[symNumber].yBottom - G_crds[symNumber].yTop;

    M_SET_MATRIX(G_symbolMx,-1,SYM_SIZE,SYM_SIZE)

    trimArray(G_imgSheetArr,G_symbolMx, ySize,xSize, y,x);
    showImgFromArray(bigImg,G_symbolMx, SYM_SIZE,SYM_SIZE);
}
//---------------------------------------------------------------------------


















