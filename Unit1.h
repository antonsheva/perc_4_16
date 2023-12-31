//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TEdit *edIn1;
	TEdit *edIn2;
	TEdit *edIn3;
	TEdit *edIn4;
	TEdit *edOut1;
	TEdit *edOut2;
	TEdit *edOut3;
	TEdit *edOut4;
	TEdit *edOut5;
	TEdit *edOut6;
	TEdit *edOut7;
	TEdit *edOut8;
	TEdit *edOut9;
	TButton *Button1;
	TButton *Button2;
	TEdit *edOut10;
	TLabel *lbl1;
	TEdit *edAlfa;
	TLabel *Label1;
	TEdit *edSigmod;
	TLabel *Label2;
	TEdit *edCycleQty;
	TLabel *Label3;
	TButton *Button3;
	TImage *img1;
	TEdit *edInfo;
	TListBox *lb1;
	TGroupBox *GroupBox1;
	TButton *Button5;
	TButton *Button6;
	TButton *Button4;
	TButton *Button8;
	TButton *Button7;
	TButton *Button11;
	TButton *Button12;
	TButton *Button13;
	TButton *Button14;
	TImage *bigImg;
	TCheckBox *chk1;
	TCheckBox *chk2;
	TCheckBox *chk3;
	TEdit *edScaleImg;
	TLabel *Label7;
	TButton *Button15;
	TEdit *edPattNum;
	TButton *Button16;
	TLabel *Label8;
	TButton *btTest;
	TImage *imgSht;
	TButton *btLoadDataSheet;
	TButton *Button9;
	TEdit *edSpaceX;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *edSpaceY;
	TLabel *Label11;
	TLabel *Label12;
	TEdit *edExtLeft;
	TEdit *edExtRight;
	TLabel *Label13;
	TLabel *Label14;
	TEdit *edExtTop;
	TEdit *edExtBottom;
	TLabel *Label15;
	TButton *Button10;
	TEdit *edSymNum;
	TListBox *lb2;
	TButton *Button17;
	TImage *bigImg1;
	TEdit *edTurnCoef;
	TEdit *edTurnDiv;
	TLabel *Label16;
	TLabel *Label17;
	TEdit *edShftX;
	TEdit *edShftY;
	TLabel *Label18;
	TLabel *Label19;
	TEdit *edAngle;
	TEdit *edWidth;
	TEdit *edHeight;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TEdit *edTmp;
	TButton *Button18;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall edAlfaChange(TObject *Sender);
	void __fastcall edSigmodChange(TObject *Sender);
	void __fastcall edCycleQtyChange(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    
    void __fastcall Button7Click(TObject *Sender);
    void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall edScaleImgChange(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);
	void __fastcall btTestClick(TObject *Sender);
	void __fastcall btLoadDataSheetClick(TObject *Sender);
    void __fastcall Button9Click(TObject *Sender);
	void __fastcall edSpaceXChange(TObject *Sender);
	void __fastcall edSpaceYChange(TObject *Sender);
	void __fastcall edExtLeftChange(TObject *Sender);
	void __fastcall edExtRightChange(TObject *Sender);
	void __fastcall edExtTopChange(TObject *Sender);
	void __fastcall edExtBottomChange(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall edAngleChange(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);


private:    // User declarations
    __fastcall ~TForm1();
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

	struct S_imgPos
	{
		int xLetf;
		int yTop;
		int xRight;
		int yBottom;
		int width;
		int height;
	};
	
    struct S_coords
    {
       int xLeft;
       int xRight;
       int yTop;
       int yBottom; 
    };
    S_coords G_crds[100];

    
	

    void __fastcall turnImg(float **imgArr, double hw, int prevAngle);
    void TForm1::initGoalArray();

	int checkNewSymbol(int x, int y, S_coords *crd, int len);
    int searchSymbols(float **arr, S_coords *crd);
    void getSymbolCoords(int x, int y, float **arr, S_coords *crd);
    void __fastcall normalizationData(float *dataArr, int len, float minRange = -1, float maxRange = 1);
    void __fastcall trimArray(float **mx1, float **mx2, int w, int h, int startX=0, int startY=0);
    float __fastcall getScale(S_imgPos *pos, float size);

	
    void TForm1::scaleArray(float *arr, int len);
	void initArrays();
    void testFunc(String flName);
    void initNnParameters();
	void showResult(float *nGoal);
    void showImgFromArray(TImage *img, float **arr, int w=140, int h=140);
    void TForm1::loadPattFromFiles();
    void TForm1::getValFromFile(BYTE *val, int *meta, int pos = -1);
	void TForm1::initWeights();
	void TForm1::loadInputsGoalsData();
	void loadImgToSmallBitmap(String flName, TImage *bimap);
	void loadImgToBitmap(String flName, TImage * bitmap, int h, int w);
    void loadBitmapToArray(TImage *bitmap, float **arr, int h, int w, DWORD *trueColorArr=NULL);
    void srchSnglImgPos(float **G_tmpImgArr1, S_imgPos *pos, int h, int w);
    void loadSmallImgToArray(float *arr);
	void scaleImg(float **imgArr, int maxSize, float scale, int w, int h);
	void moveImgInArray(float **mxImg, int mxSide, int position, S_imgPos *imgParam);
 
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

