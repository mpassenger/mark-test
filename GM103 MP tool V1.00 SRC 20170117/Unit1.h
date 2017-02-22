//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *StartCmd;
        TButton *QuitCmd;
        TRadioGroup *RadioGroup1;
        TRadioButton *RadioCOM1;
        TRadioButton *RadioCOM2;
        TTimer *Timer1;
        TMemo *Memo1;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TRadioButton *RadioButton4;
        TEdit *MAC;
        TLabel *Label2;
        TLabel *Label1;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Start;
        TLabel *Label6;
        TEdit *END_MAC;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label12;
        TLabel *Label9;
        TButton *Button1;
        TLabel *Label13;
        TLabel *Label10;
        TLabel *Label15;
        TLabel *Label18;
        TEdit *URL;
        TEdit *EMP1;
        TEdit *Station1;
        TLabel *Label20;
        TEdit *PCBASN;
        TIdHTTP *IdHTTP1;
        void __fastcall StartCmdClick(TObject *Sender);
        void __fastcall QuitCmdClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
