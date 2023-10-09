#include "Unit1.h"

#define PATT_QTY 60
#define OUT_N_LEN 10
String imgFiles[PATT_QTY];
float P1_goal[PATT_QTY][OUT_N_LEN] = {
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
 
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
 
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
 
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
 
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
 
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
 
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
 
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
 
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
 
};

void TForm1::initNnParameters()
{
    G_sigmoidTilt = 5;
    Form1->edSigmod->Text = "5";

    G_alfa = 0.0001;
    Form1->edAlfa->Text = "0,0001";

    imgFiles[0]  = "img/d1_1.png";
    imgFiles[1]  = "img/d1_2.png";
    imgFiles[2]  = "img/d1_3.png";
    imgFiles[3]  = "img/d1_4.png";
    imgFiles[4]  = "img/d1_5.png";
    imgFiles[5]  = "img/d1_6.png";
    imgFiles[6]  = "img/d2_1.png";
    imgFiles[7]  = "img/d2_2.png";
    imgFiles[8]  = "img/d2_3.png";
    imgFiles[9]  = "img/d2_4.png";
    imgFiles[10] = "img/d2_5.png";
    imgFiles[11] = "img/d2_6.png";
    imgFiles[12] = "img/d3_1.png";
    imgFiles[13] = "img/d3_2.png";
    imgFiles[14] = "img/d3_3.png";
    imgFiles[15] = "img/d3_4.png";
    imgFiles[16] = "img/d3_5.png";
    imgFiles[17] = "img/d3_6.png";
    imgFiles[18] = "img/d4_1.png";
    imgFiles[19] = "img/d4_2.png";
    imgFiles[20] = "img/d4_3.png";
    imgFiles[21] = "img/d4_4.png";
    imgFiles[22] = "img/d4_5.png";
    imgFiles[23] = "img/d4_6.png";
    imgFiles[24] = "img/d5_1.png";
    imgFiles[25] = "img/d5_2.png";
    imgFiles[26] = "img/d5_3.png";
    imgFiles[27] = "img/d5_4.png";
    imgFiles[28] = "img/d5_5.png";
    imgFiles[29] = "img/d5_6.png";
    imgFiles[30] = "img/d6_1.png";
    imgFiles[31] = "img/d6_2.png";
    imgFiles[32] = "img/d6_3.png";
    imgFiles[33] = "img/d6_4.png";
    imgFiles[34] = "img/d6_5.png";
    imgFiles[35] = "img/d6_6.png";
    imgFiles[36] = "img/d7_1.png";
    imgFiles[37] = "img/d7_2.png";
    imgFiles[38] = "img/d7_3.png";
    imgFiles[39] = "img/d7_4.png";
    imgFiles[40] = "img/d7_5.png";
    imgFiles[41] = "img/d7_6.png";
    imgFiles[42] = "img/d8_1.png";
    imgFiles[43] = "img/d8_2.png";
    imgFiles[44] = "img/d8_3.png";
    imgFiles[45] = "img/d8_4.png";
    imgFiles[46] = "img/d8_5.png";
    imgFiles[47] = "img/d8_6.png";
    imgFiles[48] = "img/d9_1.png";
    imgFiles[49] = "img/d9_2.png";
    imgFiles[50] = "img/d9_3.png";
    imgFiles[51] = "img/d9_4.png";
    imgFiles[52] = "img/d9_5.png";
    imgFiles[53] = "img/d9_6.png";
    imgFiles[54] = "img/d0_1.png";
    imgFiles[55] = "img/d0_2.png";
    imgFiles[56] = "img/d0_3.png";
    imgFiles[57] = "img/d0_4.png";
    imgFiles[58] = "img/d0_5.png";
    imgFiles[59] = "img/d0_6.png";
}


void TForm1::showResult(float *nGoal){
    edOut1->Text = FormatFloat("0.00000000", nGoal[0]);
    edOut2->Text = FormatFloat("0.00000000", nGoal[1]);
    edOut3->Text = FormatFloat("0.00000000", nGoal[2]);
    edOut4->Text = FormatFloat("0.00000000", nGoal[3]);
    edOut5->Text = FormatFloat("0.00000000", nGoal[4]);
    edOut6->Text = FormatFloat("0.00000000", nGoal[5]);
	edOut7->Text = FormatFloat("0.00000000", nGoal[6]);  
    edOut8->Text = FormatFloat("0.00000000", nGoal[7]);
	edOut9->Text = FormatFloat("0.00000000", nGoal[8]);
	edOut10->Text = FormatFloat("0.00000000",nGoal[9]);  
}












