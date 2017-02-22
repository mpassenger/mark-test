object TelnetForm: TTelnetForm
  Left = 298
  Top = 241
  BorderStyle = bsDialog
  Caption = 'Burn MAC and SN V1.2  20160816'
  ClientHeight = 726
  ClientWidth = 1248
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object lblServer: TLabel
    Left = 16
    Top = 16
    Width = 85
    Height = 29
    HelpType = htKeyword
    Caption = '&Server:'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblPort: TLabel
    Left = 704
    Top = 16
    Width = 56
    Height = 29
    HelpType = htKeyword
    Caption = '&Port:'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Ping: TLabel
    Left = 344
    Top = 16
    Width = 61
    Height = 29
    Caption = 'Ping:'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 24
    Top = 264
    Width = 78
    Height = 37
    Caption = 'S  N:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 16
    Top = 328
    Width = 95
    Height = 37
    Caption = 'MAC: '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label1: TLabel
    Left = 16
    Top = 200
    Width = 85
    Height = 37
    Caption = 'MAC:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 24
    Top = 144
    Width = 78
    Height = 37
    Caption = 'S  N:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label5: TLabel
    Left = 135
    Top = 64
    Width = 306
    Height = 17
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label6: TLabel
    Left = 131
    Top = 96
    Width = 310
    Height = 25
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label7: TLabel
    Left = 16
    Top = 504
    Width = 101
    Height = 24
    Caption = 'MESServer:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label13: TLabel
    Left = 24
    Top = 408
    Width = 51
    Height = 24
    Caption = 'S     N'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label15: TLabel
    Left = 216
    Top = 456
    Width = 105
    Height = 24
    AutoSize = False
    Caption = #21729#24037#32232#34399
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label16: TLabel
    Left = 16
    Top = 456
    Width = 61
    Height = 24
    Caption = ' Station'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object edtServer: TEdit
    Left = 112
    Top = 16
    Width = 209
    Height = 33
    AutoSize = False
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ImeName = #20013#25991'(?'#20307') - '#25628#29399#25340#38899'?'#20837#27861
    ParentFont = False
    TabOrder = 0
  end
  object btnDisconnect: TButton
    Left = 0
    Top = 120
    Width = 1
    Height = 17
    Caption = '&Disconnect'
    Enabled = False
    TabOrder = 1
    OnClick = btnDisconnectClick
  end
  object spnedtPort: TEdit
    Left = 776
    Top = 16
    Width = 97
    Height = 33
    AutoSize = False
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ImeName = #20013#25991'(?'#20307') - '#25628#29399#25340#38899'?'#20837#27861
    ParentFont = False
    TabOrder = 2
  end
  object UpDown1: TUpDown
    Left = 874
    Top = 19
    Width = 16
    Height = 24
    Enabled = False
    Min = 0
    Position = 0
    TabOrder = 3
    Wrap = False
    OnClick = UpDown1Click
  end
  object Memo1: TRichEdit
    Left = 0
    Top = 614
    Width = 1248
    Height = 93
    Align = alBottom
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ImeName = #20013#25991'(?'#20307') - '#25628#29399#25340#38899'?'#20837#27861
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 4
    WordWrap = False
    OnKeyPress = Memo1KeyPress
  end
  object sbrStatus: TStatusBar
    Left = 0
    Top = 707
    Width = 1248
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object PingFunction: TButton
    Left = 0
    Top = 120
    Width = 1
    Height = 9
    Caption = 'PingFunction'
    Enabled = False
    TabOrder = 6
  end
  object PingIP: TEdit
    Left = 424
    Top = 16
    Width = 257
    Height = 33
    AutoSize = False
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ImeName = #20013#25991'(?'#20307') - '#25628#29399#25340#38899'?'#20837#27861
    ParentFont = False
    TabOrder = 7
  end
  object SDcard: TButton
    Left = 0
    Top = 152
    Width = 9
    Height = 0
    Caption = 'SD-carrd TEST'
    TabOrder = 8
  end
  object BuzzerON: TButton
    Left = 9
    Top = 184
    Width = 0
    Height = 1
    Caption = 'BuzzerON'
    Enabled = False
    TabOrder = 9
  end
  object ShowPDUStatus: TButton
    Left = 0
    Top = 104
    Width = 1
    Height = 1
    Caption = 'Show PDU-Status'
    TabOrder = 10
  end
  object Clear: TButton
    Left = 784
    Top = 264
    Width = 121
    Height = 105
    Caption = 'Clear'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 11
    OnClick = ClearClick
  end
  object START: TButton
    Left = 480
    Top = 264
    Width = 209
    Height = 105
    Caption = 'Read MAC and SN '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 12
    OnClick = STARTClick
  end
  object RSN: TButton
    Left = 120
    Top = 264
    Width = 321
    Height = 41
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 13
  end
  object RMAC: TButton
    Left = 120
    Top = 328
    Width = 321
    Height = 41
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 14
  end
  object StartCmd: TButton
    Left = 480
    Top = 136
    Width = 209
    Height = 105
    Caption = 'Burn MAC and SN'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 15
    OnClick = StartCmdClick
  end
  object Button5: TButton
    Left = 480
    Top = 72
    Width = 81
    Height = 49
    Caption = #36899#32218
    TabOrder = 16
    OnClick = Button5Click
  end
  object Result3: TButton
    Left = 784
    Top = 144
    Width = 121
    Height = 97
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 17
  end
  object MAC: TEdit
    Left = 120
    Top = 200
    Width = 321
    Height = 41
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ImeName = #20013#25991'(?'#20307') - '#25628#29399#25340#38899'?'#20837#27861
    MaxLength = 12
    ParentFont = False
    TabOrder = 18
    OnChange = FormCreate
  end
  object SN: TEdit
    Left = 120
    Top = 136
    Width = 321
    Height = 41
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ImeName = #20013#25991'(?'#20307') - '#25628#29399#25340#38899'?'#20837#27861
    MaxLength = 17
    ParentFont = False
    TabOrder = 19
    OnChange = FormCreate
  end
  object Button6: TButton
    Left = 608
    Top = 72
    Width = 81
    Height = 49
    Caption = #26039#32218
    TabOrder = 20
    OnClick = Button6Click
  end
  object EU: TCheckBox
    Left = 16
    Top = 64
    Width = 97
    Height = 17
    Caption = 'PE-08I'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 21
  end
  object US: TCheckBox
    Left = 16
    Top = 104
    Width = 97
    Height = 17
    Caption = 'PE-09N'
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clFuchsia
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 22
  end
  object URL: TEdit
    Left = 144
    Top = 504
    Width = 313
    Height = 33
    AutoSize = False
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ImeName = #20013#25991'(?'#20307') - '#25628#29399#25340#38899'?'#20837#27861
    ParentFont = False
    TabOrder = 23
  end
  object PCBASN: TEdit
    Left = 96
    Top = 408
    Width = 361
    Height = 25
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ImeName = #20013#25991'(?'#20307') - '#25628#29399#25340#38899'?'#20837#27861
    MaxLength = 17
    ParentFont = False
    TabOrder = 24
  end
  object Station1: TEdit
    Left = 96
    Top = 456
    Width = 113
    Height = 25
    AutoSize = False
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ImeName = #20013#25991'(?'#20307') - '#25628#29399#25340#38899'?'#20837#27861
    ParentFont = False
    TabOrder = 25
  end
  object EMP1: TEdit
    Left = 336
    Top = 456
    Width = 121
    Height = 25
    AutoSize = False
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ImeName = #20013#25991'(?'#20307') - '#25628#29399#25340#38899'?'#20837#27861
    ParentFont = False
    TabOrder = 26
  end
  object Button1: TButton
    Left = 520
    Top = 408
    Width = 129
    Height = 129
    Caption = #19978#20659'Log'
    TabOrder = 27
    OnClick = Button1Click
  end
  object IdTelnetDemo: TIdTelnet
    RecvBufferSize = 8192
    OnConnected = IdTelnetDemoConnected
    Port = 23
    OnDataAvailable = IdTelnetDemoDataAvailable
    Terminal = 'dumb'
    OnConnect = IdTelnetDemoConnect
    Left = 1184
    Top = 16
  end
  object Timer1: TTimer
    Left = 1136
    Top = 16
  end
end
