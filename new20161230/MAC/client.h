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
        TButton *Clear;
        TButton *START;
        TLabel *Label3;
        TLabel *Label4;
        TButton *RSN;
        TButton *RMAC;
        TButton *StartCmd;
        TButton *Button5;
        TButton *Result3;
        TTimer *Timer1;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *SN;
        TEdit *MAC;
        TButton *Button6;
        TLabel *Label5;
        TLabel *Label6;
        TCheckBox *EU;
        TCheckBox *US;
        TLabel *Label7;
        TLabel *Label13;
        TLabel *Label15;
        TLabel *Label16;
        TEdit *URL;
        TEdit *PCBASN;
        TEdit *Station1;
        TEdit *EMP1;
        TButton *Button1;
        void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall btnConnectClick(TObject *Sender);
        void __fastcall btnDisconnectClick(TObject *Sender);
        void __fastcall Memo1KeyPress(TObject *Sender, char &Key);
        void __fastcall IdTelnetDemoDataAvailable(AnsiString Buffer);
        void __fastcall IdTelnetDemoConnected(TObject *Sender);
        void __fastcall IdTelnetDemoConnect();
        void __fastcall SendCommand(AnsiString CMD);
        void __fastcall Memo1Display();
        void __fastcall Delay(unsigned int Time);
        void __fastcall STARTClick(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall StartCmdClick(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall ClearClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TTelnetForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTelnetForm *TelnetForm;
//---------------------------------------------------------------------------
#endif
