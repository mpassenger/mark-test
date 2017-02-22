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
        TLabel *Label1;
        TButton *FW;
        TLabel *Label2;
        TButton *Model;
        TLabel *Label5;
        TButton *Voltage;
        TLabel *Label6;
        TButton *Frequency;
        TLabel *Label7;
        TButton *Current;
        TLabel *lABEL8;
        TEdit *IP;
        TCheckBox *EU;
        TCheckBox *US;
        TButton *Button4;
        TButton *Button6;
        TButton *Power;
        TLabel *Label11;
        TRadioGroup *RadioGroup1;
        TRadioButton *RadioCOM2;
        TButton *Button9;
        TButton *QuitCmd;
        TLabel *Label15;
        TLabel *Label16;
        TRadioGroup *RadioGroup2;
        TRadioButton *RadioCOM1;
        TRadioButton *RadioCOM22;
        TRadioButton *RadioCOM11;
        TLabel *Label14;
        TLabel *Label17;
        TButton *Button8;
        TButton *Button10;
        TButton *Button3;
        TButton *Button7;
        TButton *Button13;
        TButton *Button14;
        TButton *Button15;
        TButton *Button16;
        TButton *Button17;
        TButton *Button18;
        TButton *Button19;
        TButton *Button20;
        TShape *Shape1;
        TShape *Shape2;
        TShape *Shape3;
        TShape *Shape4;
        TShape *Shape5;
        TShape *Shape6;
        TShape *Shape7;
        TShape *Shape8;
        TButton *Button21;
        TButton *Button22;
        TButton *Button23;
        TButton *Button24;
        TButton *Button25;
        TButton *Button26;
        TButton *Button27;
        TButton *Button28;
        TShape *Shape9;
        TShape *Shape10;
        TShape *Shape11;
        TShape *Shape12;
        TShape *Shape13;
        TShape *Shape14;
        TShape *Shape15;
        TShape *Shape16;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TButton *Button29;
        TShape *Shape17;
        TButton *Result20;
        TButton *Button5;
        TLabel *Label3;
        TLabel *Label13;
        TLabel *Label4;
        TLabel *Label9;
        TButton *Button30;
        TEdit *URL;
        TEdit *PCBASN;
        TEdit *Station1;
        TEdit *EMP1;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TEdit *Edit4;
        TEdit *Edit5;
        TEdit *Edit6;
        TEdit *Edit7;
        TEdit *Edit8;
        TEdit *Edit9;
        TEdit *Edit19;
        TEdit *Edit11;
        TEdit *Edit12;
        TEdit *Edit13;
        TEdit *Edit14;
        TEdit *Edit15;
        TEdit *Edit16;
        TEdit *Edit17;
        TEdit *Edit18;
        TEdit *Edit27;
        TEdit *Edit28;
        TEdit *Edit29;
        TEdit *Edit30;
        TEdit *Edit32;
        TEdit *Edit33;
        TEdit *Edit34;
        TEdit *Edit35;
        TEdit *Edit36;
        TEdit *Edit37;
        TEdit *Edit38;
        TEdit *Edit39;
        TEdit *Edit31;
        TEdit *Edit41;
        TEdit *Edit42;
        TEdit *Edit43;
        TEdit *Edit44;
        TEdit *Edit45;
        TEdit *Edit46;
        TEdit *Edit47;
        TEdit *Edit48;
        TEdit *Edit49;
        TButton *Result3;
        TButton *z11;
        TButton *z12;
        TButton *z13;
        TButton *z14;
        TButton *z15;
        TButton *z16;
        TButton *z17;
        TButton *z18;
        TButton *z19;
        TButton *z21;
        TButton *z22;
        TButton *z23;
        TButton *z24;
        TButton *z25;
        TButton *z26;
        TButton *z27;
        TButton *z28;
        TButton *z29;
        TButton *Button31;
        TCheckBox *CheckBox7;
        TButton *Button35;
        TCheckBox *CheckBox11;
        TTimer *Timer1;
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
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall QuitCmdClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button9Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button13Click(TObject *Sender);
        void __fastcall Button14Click(TObject *Sender);
        void __fastcall Button15Click(TObject *Sender);
        void __fastcall Button16Click(TObject *Sender);
        void __fastcall Button17Click(TObject *Sender);
        void __fastcall Button18Click(TObject *Sender);
        void __fastcall Button19Click(TObject *Sender);
        void __fastcall Button20Click(TObject *Sender);
        void __fastcall Button21Click(TObject *Sender);
        void __fastcall Button22Click(TObject *Sender);
        void __fastcall Button23Click(TObject *Sender);
        void __fastcall Button24Click(TObject *Sender);
        void __fastcall Button25Click(TObject *Sender);
        void __fastcall Button26Click(TObject *Sender);
        void __fastcall Button27Click(TObject *Sender);
        void __fastcall Button28Click(TObject *Sender);
        void __fastcall Button29Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button30Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TTelnetForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTelnetForm *TelnetForm;
//---------------------------------------------------------------------------
#endif
