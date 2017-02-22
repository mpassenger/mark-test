//---------------------------------------------------------------------------

#ifndef ClientH
#define ClientH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdTelnet.hpp>
#include <ExtCtrls.hpp>
#include <IdHTTP.hpp>
//---------------------------------------------------------------------------
class TTelnetForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *lblServer;
        TLabel *lblPort;
        TEdit *edtServer;
        TButton *btnDisconnect;
        TIdTelnet *IdTelnetDemo;
        TEdit *spnedtPort;
        TUpDown *UpDown1;
        TRichEdit *Memo1;
        TStatusBar *sbrStatus;
        TButton *PingFunction;
        TEdit *PingIP;
        TLabel *Ping;
        TButton *SDcard;
        TButton *BuzzerON;
        TButton *ShowPDUStatus;
        TButton *Result;
        TLabel *Label1;
        TButton *FW;
        TLabel *Label2;
        TButton *Model;
        TLabel *Label5;
        TLabel *Label6;
        TButton *Frequency;
        TLabel *Label7;
        TButton *Current;
        TLabel *lABEL8;
        TButton *Result2;
        TEdit *IP;
        TCheckBox *EU;
        TCheckBox *US;
        TCheckBox *CheckBox85;
        TCheckBox *CheckBox89;
        TCheckBox *CheckBoxSDCard;
        TCheckBox *CheckBoxBuzzer;
        TCheckBox *CheckBoxPing;
        TCheckBox *CheckBoxDeviceInfo;
        TCheckBox *CheckBoxPDUStatus;
        TCheckBox *CheckBoxOutlet;
        TCheckBox *CheckBoxLEDLuminance;
        TCheckBox *CheckBoxStaticIP;
        TCheckBox *CheckBoxSDRAM;
        TLabel *Label9;
        TButton *Tem;
        TLabel *Label10;
        TButton *Hum;
        TButton *Power;
        TLabel *Label11;
        TCheckBox *CheckBoxPowerCycle;
        TTimer *Timer1;
        TCheckBox *CheckBoxOledFill;
        TButton *QuitCmd;
        TRadioGroup *RadioGroup2;
        TRadioButton *RadioCOM22;
        TRadioButton *RadioCOM11;
        TLabel *Label14;
        TButton *Voltage;
        TButton *START;
        TButton *Connect;
        TButton *SDcar;
        TButton *RAM;
        TButton *Buzzer;
        TButton *Pingt;
        TButton *InfoFW;
        TButton *Infos;
        TButton *Outlett;
        TButton *PowerC;
        TButton *OLED;
        TButton *LED;
        TButton *Staticip;
        TButton *Button4;
        TShape *Shape1;
        TShape *Shape2;
        TShape *Shape3;
        TShape *Shape4;
        TShape *Shape5;
        TShape *Shape6;
        TShape *Shape7;
        TShape *Shape8;
        TShape *Shape9;
        TShape *Shape10;
        TShape *Shape11;
        TIdHTTP *IdHTTP1;
        TButton *Button1;
        TEdit *URL;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label12;
        TEdit *PCBASN;
        TLabel *Label13;
        TLabel *Label15;
        TLabel *Label16;
        TEdit *Station1;
        TEdit *EMP1;
        TEdit *SDCard1;
        TEdit *SDRAM1;
        TEdit *Buzzer1;
        TEdit *ping1;
        TEdit *FW1;
        TEdit *model1;
        TEdit *voltage1;
        TEdit *frequency1;
        TEdit *temp1;
        TEdit *humidity1;
        TEdit *OLED1;
        TEdit *LED1;
        TEdit *staticsip1;
        TEdit *outlettest1;
        TEdit *powercycle1;
        TEdit *aMAC;
        TEdit *aSN;
        void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall btnConnectClick(TObject *Sender);
        void __fastcall btnDisconnectClick(TObject *Sender);
        void __fastcall Memo1KeyPress(TObject *Sender, char &Key);
        void __fastcall IdTelnetDemoDataAvailable(AnsiString Buffer);
        void __fastcall IdTelnetDemoConnected(TObject *Sender);
        void __fastcall IdTelnetDemoConnect();
        void __fastcall LoginClick(TObject *Sender);
        void __fastcall PasswordClick(TObject *Sender);
        void __fastcall SendCommand(AnsiString CMD);
        void __fastcall Memo1Display();
        void __fastcall Delay(unsigned int Time);
        void __fastcall STARTClick(TObject *Sender);
        void __fastcall QuitCmdClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall SDcarClick(TObject *Sender);
        void __fastcall RAMClick(TObject *Sender);
        void __fastcall BuzzerClick(TObject *Sender);
        void __fastcall PingtClick(TObject *Sender);
        void __fastcall InfoFWClick(TObject *Sender);
        void __fastcall InfosClick(TObject *Sender);
        void __fastcall OutlettClick(TObject *Sender);
        void __fastcall PowerCClick(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall OLEDClick(TObject *Sender);
        void __fastcall LEDClick(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall ConnectClick(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button17Click(TObject *Sender);
        void __fastcall StaticipClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TTelnetForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTelnetForm *TelnetForm;
//---------------------------------------------------------------------------
#endif
