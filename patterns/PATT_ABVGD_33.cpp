#include "Unit1.h"

#define PATT_QTY 50
#define OUT_N_LEN 50
String imgFiles[PATT_QTY];
float P1_goal[PATT_QTY][OUT_N_LEN];

void TForm1::initNnParameters()
{
    G_sigmoidTilt = 5;
    Form1->edSigmod->Text = "5";

    G_alfa = 0.0001;
    Form1->edAlfa->Text = "0,0001";
}



void TForm1::initGoalArray()
{
    for(int i=0; i<PATT_QTY; i++){
        for(int k=0; k<PATT_QTY; k++){
            if(k==i)P1_goal[i][k]=1;
            else    P1_goal[i][k]=0;
        }
    }
}

void TForm1::showResult(float *nGoal)
{
    String strArr[50] = {"А",
    "Б","В","Г","Д","Е","Ё","Ж","З","И","Й","К","Л","М","Н",
    "О","П","Р","С","Т","У","Ф","Х","Ц","Ч","Ш","Щ","Ъ","Ы",
    "Ь","Э","Ю","Я","1","2","3","4","5","6","7","8","9","0",
    "-","/","*","+","=",".",","};

    String tmpStr;
    lb2->Clear();
    for(int i=0; i<PATT_QTY; i++){
        tmpStr = FloatToStr(nGoal[i]);
        lb2->Items->Add(strArr[i]+" - "+tmpStr);
    }
}


