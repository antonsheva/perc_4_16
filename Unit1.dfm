object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 516
  ClientWidth = 875
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lbl1: TLabel
    Left = 336
    Top = 12
    Width = 26
    Height = 19
    Caption = 'lbl1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label1: TLabel
    Left = 252
    Top = 123
    Width = 19
    Height = 13
    Caption = 'Alfa'
  end
  object Label2: TLabel
    Left = 246
    Top = 175
    Width = 36
    Height = 13
    Caption = 'Sigmoid'
  end
  object Label3: TLabel
    Left = 243
    Top = 227
    Width = 45
    Height = 13
    Caption = 'Cycle qty'
  end
  object img1: TImage
    Left = 706
    Top = 8
    Width = 28
    Height = 28
  end
  object Label4: TLabel
    Left = 296
    Top = 178
    Width = 12
    Height = 13
    Caption = 'n1'
  end
  object Label5: TLabel
    Left = 324
    Top = 178
    Width = 12
    Height = 13
    Caption = 'n2'
  end
  object Label6: TLabel
    Left = 350
    Top = 178
    Width = 12
    Height = 13
    Caption = 'n3'
  end
  object bigImg: TImage
    Left = 706
    Top = 61
    Width = 140
    Height = 140
  end
  object Label7: TLabel
    Left = 397
    Top = 70
    Width = 43
    Height = 13
    Caption = 'scale img'
  end
  object edIn1: TEdit
    Left = 32
    Top = 8
    Width = 49
    Height = 21
    TabOrder = 0
    Text = '0'
  end
  object edIn2: TEdit
    Left = 32
    Top = 34
    Width = 49
    Height = 21
    TabOrder = 1
    Text = '0'
  end
  object edIn3: TEdit
    Left = 32
    Top = 61
    Width = 49
    Height = 21
    TabOrder = 2
    Text = '0'
  end
  object edIn4: TEdit
    Left = 32
    Top = 88
    Width = 49
    Height = 21
    TabOrder = 3
    Text = '1'
  end
  object edOut1: TEdit
    Left = 112
    Top = 8
    Width = 97
    Height = 21
    TabOrder = 4
    Text = 'Edit1'
  end
  object edOut2: TEdit
    Left = 112
    Top = 34
    Width = 97
    Height = 21
    TabOrder = 5
    Text = 'Edit1'
  end
  object edOut3: TEdit
    Left = 112
    Top = 60
    Width = 97
    Height = 21
    TabOrder = 6
    Text = 'Edit1'
  end
  object edOut4: TEdit
    Left = 112
    Top = 85
    Width = 97
    Height = 21
    TabOrder = 7
    Text = 'Edit1'
  end
  object edOut5: TEdit
    Left = 112
    Top = 112
    Width = 97
    Height = 21
    TabOrder = 8
    Text = 'Edit1'
  end
  object edOut6: TEdit
    Left = 112
    Top = 138
    Width = 97
    Height = 21
    TabOrder = 9
    Text = 'Edit1'
  end
  object edOut7: TEdit
    Left = 112
    Top = 164
    Width = 97
    Height = 21
    TabOrder = 10
    Text = 'Edit1'
  end
  object edOut8: TEdit
    Left = 112
    Top = 190
    Width = 97
    Height = 21
    TabOrder = 11
    Text = 'Edit1'
  end
  object edOut9: TEdit
    Left = 112
    Top = 216
    Width = 97
    Height = 21
    TabOrder = 12
    Text = 'Edit1'
  end
  object Button1: TButton
    Left = 240
    Top = 8
    Width = 75
    Height = 25
    Caption = 'lern'
    TabOrder = 13
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 240
    Top = 39
    Width = 75
    Height = 25
    Caption = 'test'
    TabOrder = 14
    OnClick = Button2Click
  end
  object edOut10: TEdit
    Left = 112
    Top = 242
    Width = 97
    Height = 21
    TabOrder = 15
    Text = 'edOut10'
  end
  object edAlfa: TEdit
    Left = 240
    Top = 142
    Width = 48
    Height = 21
    TabOrder = 16
    Text = '0,001'
    OnChange = edAlfaChange
  end
  object edSigmod: TEdit
    Left = 240
    Top = 190
    Width = 48
    Height = 21
    MaxLength = 2
    NumbersOnly = True
    TabOrder = 17
    Text = '25'
    OnChange = edSigmodChange
  end
  object edCycleQty: TEdit
    Left = 240
    Top = 242
    Width = 48
    Height = 21
    MaxLength = 7
    NumbersOnly = True
    TabOrder = 18
    Text = '10000'
    OnChange = edCycleQtyChange
  end
  object Button3: TButton
    Left = 240
    Top = 70
    Width = 75
    Height = 25
    Caption = 'Init weights'
    TabOrder = 19
    OnClick = Button3Click
  end
  object edInfo: TEdit
    Left = 336
    Top = 240
    Width = 436
    Height = 21
    Enabled = False
    TabOrder = 20
    Text = 'edInfo'
  end
  object lb1: TListBox
    Left = 8
    Top = 269
    Width = 764
    Height = 236
    ItemHeight = 13
    TabOrder = 21
  end
  object GroupBox1: TGroupBox
    Left = 512
    Top = 16
    Width = 168
    Height = 48
    Caption = #1055#1072#1088#1089#1080#1085#1075' '#1073#1080#1073#1083#1080#1086#1090#1077#1082#1080
    TabOrder = 22
    object Button5: TButton
      Left = 3
      Top = 16
      Width = 75
      Height = 25
      Caption = 'split data'
      TabOrder = 0
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 84
      Top = 16
      Width = 75
      Height = 25
      Caption = 'Stop'
      TabOrder = 1
      OnClick = Button6Click
    end
  end
  object Button4: TButton
    Left = 397
    Top = 8
    Width = 75
    Height = 25
    Caption = 'load img'
    TabOrder = 23
    OnClick = Button4Click
  end
  object Button8: TButton
    Left = 397
    Top = 39
    Width = 75
    Height = 25
    Caption = 'show img'
    TabOrder = 24
    OnClick = Button8Click
  end
  object Button10: TButton
    Left = 515
    Top = 83
    Width = 75
    Height = 25
    Caption = 'load imgs'
    TabOrder = 25
    OnClick = Button10Click
  end
  object Button7: TButton
    Left = 515
    Top = 114
    Width = 75
    Height = 25
    Caption = 'lern'
    TabOrder = 26
    OnClick = Button7Click
  end
  object Button11: TButton
    Left = 611
    Top = 83
    Width = 75
    Height = 25
    Caption = 'test 1'
    TabOrder = 27
    OnClick = Button11Click
  end
  object Button12: TButton
    Left = 611
    Top = 114
    Width = 75
    Height = 25
    Caption = 'test 2'
    TabOrder = 28
    OnClick = Button12Click
  end
  object Button13: TButton
    Left = 611
    Top = 145
    Width = 75
    Height = 25
    Caption = 'test 3'
    TabOrder = 29
    OnClick = Button13Click
  end
  object Button14: TButton
    Left = 611
    Top = 176
    Width = 75
    Height = 25
    Caption = 'test 4'
    TabOrder = 30
    OnClick = Button14Click
  end
  object chk1: TCheckBox
    Left = 293
    Top = 192
    Width = 16
    Height = 17
    Checked = True
    State = cbChecked
    TabOrder = 31
  end
  object chk2: TCheckBox
    Left = 323
    Top = 192
    Width = 16
    Height = 17
    Checked = True
    State = cbChecked
    TabOrder = 32
  end
  object chk3: TCheckBox
    Left = 348
    Top = 192
    Width = 16
    Height = 17
    Checked = True
    State = cbChecked
    TabOrder = 33
  end
  object edScaleImg: TEdit
    Left = 397
    Top = 89
    Width = 75
    Height = 21
    TabOrder = 34
    Text = '1,0'
    OnChange = edScaleImgChange
  end
  object Button9: TButton
    Left = 397
    Top = 116
    Width = 75
    Height = 25
    Caption = 'show tmp img'
    TabOrder = 35
    OnClick = Button9Click
  end
  object btSearchChar: TButton
    Left = 397
    Top = 162
    Width = 75
    Height = 25
    Caption = 'search char'
    TabOrder = 36
    OnClick = btSearchCharClick
  end
end