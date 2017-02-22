//---------------------------------------------------------------------------

#include <vcl.h>
#include "windows.h"
#include "stdio.h"
#include <stdlib.h>
#include <math.h>
#include <io.h>
#include <Setupapi.h>
#include <Iphlpapi.h>
#include <iptypes.h>
#include "string.h"
#include "time.h"
#include <idhttp.hpp>

#pragma hdrstop

#include "Client.h"
#define SIZEOFARRAY
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

int  updateLogFile(String LogFile, String Data, String Result);
double Data;
int sign;

bool ifu_rs232_open();
bool ifu_rs232_open1();
bool ifu_load_cfg_data();
void SetBootLoaderIPAddress();
int upgrade_codes();
int GetPCNetWorkAddress();
int GetPCNetWorkAddress1();
int get_login_prompt(int flag, char *pattern);
int get_login_prompt1(int flag, char *pattern);
HANDLE COM1;
HANDLE COM3;
int Com_Port_DUT;
char TxdBuffer[SIZEOFARRAY + 1];
char RxdBuffer[SIZEOFARRAY + 1];
char MsgBuffer[80];
char IPStr[32];
int tSerialTimeOut=500;
int GetAdaptersInfoFlag = 0;
DWORD dw_Read;
DWORD dw_Write;
DCB dcb;
bool timeout = 1;

void Open_File();
int PE_08I_test;
int PE_09N_test;
int PDU_89_test;
int PDU_85_test;
int SDCard_test;
int SDRAM_test;
int Buzzer_test;
int Ping_test;
int DeviceInfo_test;
int PDUStatus_test;
int OutletPower_test;
int PowerCycle_test;
int OledFill_test;
int LEDLuminance_test;
int StaticIP_test;
char Firmware[7];
char Station[8];
char EMP[8];
char Serveradder[23];
char Model_number[6];
int V=0;
int InputCurrent1 = 1;
int InputCurrent5 = 5;
int InputCurrent10 = 10;
int InputCurrent15 = 15;
String Enter = "\r";
String left250 = "W";
String left251 = "A";
String left601 = "V";
String left602 = "Hz";
String outlet1 = "1";
String outlet2 = "2";
String outlet3 = "3";
String outlet4 = "4";
String outlet5 = "5";
String outlet6 = "6";
String outlet7 = "7";
String outlet8 = "8";
String outlet9 = "9";
String outlet10 = " ";
String test1 = "o";
String test2 = "x";

TTelnetForm *TelnetForm;
//---------------------------------------------------------------------------
__fastcall TTelnetForm::TTelnetForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTelnetForm::UpDown1Click(TObject *Sender, TUDBtnType Button)
{
   int PortNumber = StrToInt(spnedtPort->Text);
   


   if(Button == btNext){
        PortNumber++;
   }
   if(Button == btPrev){
        PortNumber--;
   }

   spnedtPort->Text = IntToStr(PortNumber);
}
//---------------------------------------------------------------------------
void __fastcall TTelnetForm::FormCreate(TObject *Sender)
{
   spnedtPort->Text = "23";
   edtServer->Text = "192.168.1.210";
   IP->Text = "192.168.1.252";
   PingIP->Text = "ping -i 192.168.1.111";
   TelnetForm->START->Enabled = true;
   TelnetForm->Button1->Enabled = false;
   TelnetForm->SDcar->Font->Color = clRed;
   Shape1->Brush->Color = clWhite;
   Shape2->Brush->Color = clWhite;
   Shape3->Brush->Color = clWhite;
   Shape4->Brush->Color = clWhite;
   Shape5->Brush->Color = clWhite;
   Shape6->Brush->Color = clWhite;
   Shape7->Brush->Color = clWhite;
   Shape8->Brush->Color = clWhite;
   Shape9->Brush->Color = clWhite;
   Shape10->Brush->Color = clWhite;
   Shape11->Brush->Color = clWhite;
   TelnetForm->Button4->Enabled = false;
   Open_File();

   URL->Text = Serveradder;
 //  Station1->Text = Station;
  // Application->MessageBox(Station, "show");
   EMP1->Text =EMP;
   char *S=Station;
   char *S1="100019";
   char *S2="100020";
   char *S3="100021";
   char *S4="100022";
   char *S6="100025";
   char *S7="100026";
   char *S8="100027";
   char *S9="100031";
   char *S10="100032";
   char *S11="100036";
   char *S12="100037";
   if(strcmp(S1,S) == 0)
   {
      Station1->Text = "T1-1";
   }
   if(strcmp(S,S2) == 0)
   {
      Station1->Text = "T1-2";
   }
   if(strcmp(S,S3) == 0)
   {
      Station1->Text = "T1-3";
   }
   if(strcmp(S,S4) == 0)
   {
      Station1->Text = "T1-4";
   }
   if(strcmp(S,S12) == 0)
   {
      Station1->Text = "T4-2";
   }
   if(strcmp(S,S6) == 0)
   {
      Station1->Text = "T2-1";
   }
   if(strcmp(S,S7) == 0)
   {
      Station1->Text = "T2-2";
   }
   if(strcmp(S,S8) == 0)
   {
      Station1->Text = "T2-3";
   }
   if(strcmp(S,S9) == 0)
   {
      Station1->Text = "T3-1";
   }
   if(strcmp(S,S10) == 0)
   {
      Station1->Text = "T3-2";
   }
   if(strcmp(S,S11) == 0)
   {
      Station1->Text = "T4-1";
   }
   if(strcmp(S,S12) == 0)
   {
      Station1->Text = "T4-2";
   }
  // Application->MessageBox(Serveradder,"show");
   if(PE_08I_test == 1)
   {
        EU->Checked = true;
   }
   if(PE_09N_test == 1)
   {
        US->Checked = true;
   }
   if(PDU_85_test == 1)
   {
        CheckBox85->Checked = true;
   }
   if(PDU_89_test == 1)
   {
        CheckBox89->Checked = true;
   }
   if(SDCard_test == 1)
   {
        CheckBoxSDCard->Checked = true;
   }
   if(SDRAM_test == 1)
   {
        CheckBoxSDRAM->Checked = true;
   }
   if(PDUStatus_test == 1)
   {
        CheckBoxPDUStatus->Checked = true;
   }
   if(Buzzer_test == 1)
   {
        CheckBoxBuzzer->Checked = true;
   }
   if(DeviceInfo_test == 1)
   {
        CheckBoxDeviceInfo->Checked = true;
   }
   if(OledFill_test == 1)
   {
        CheckBoxOledFill->Checked = true;
   }
   if(OutletPower_test == 1)
   {
        CheckBoxOutlet->Checked = true;
   }
   if(PowerCycle_test == 1)
   {
        CheckBoxPowerCycle->Checked = true;
   }
   if(Ping_test == 1)
   {
        CheckBoxPing->Checked = true;
   }
   if(LEDLuminance_test == 1)
   {
        CheckBoxLEDLuminance->Checked = true;
   }
   if(StaticIP_test == 1)
   {
        CheckBoxStaticIP->Checked = true;
   }
}
//-----------------------mark add com port----------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TTelnetForm::QuitCmdClick(TObject *Sender)
{
        exit(0);
}
//---------------------------------------------------------------------------
void __fastcall TTelnetForm::Timer1Timer(TObject *Sender)
{
        timeout = 0;
}
//---------------------------------------------------------------------------

bool ifu_rs232_open1()
{
        bool w_result = true;
        String PortID;
        int sid;

        COMMTIMEOUTS TimeOut;
        TimeOut.ReadIntervalTimeout = 0;
        TimeOut.ReadTotalTimeoutMultiplier = 0;
        TimeOut.ReadTotalTimeoutConstant = tSerialTimeOut;
        TimeOut.WriteTotalTimeoutMultiplier = 0;
        TimeOut.WriteTotalTimeoutConstant = tSerialTimeOut;

        if (TelnetForm->RadioCOM11->Checked )
        {  PortID = "Com3";  }

        if (!BuildCommDCB("19200, n, 8, 1", &dcb))                  //(!BuildCommDCB("38400, n, 8, 1", &dcb))
        {
                sprintf(TxdBuffer, "Unable to BUild CommDCB\n");
                w_result = false;
        }

        COM3=CreateFile(PortID.c_str(),
                     GENERIC_READ | GENERIC_WRITE,
                     0,
                     0,
                     OPEN_EXISTING,
                     FILE_ATTRIBUTE_NORMAL,
                     0);

        if (!SetCommState(COM3, &dcb))
        {
                strcat(TxdBuffer, "Unable to initial serial Port\n");
                w_result = false;
        }

        if (!SetupComm(COM3, 512, 512))
        {
                strcat(TxdBuffer, "Unable to Setup serial port Buffer\n");
                w_result = false;
        }

        if (!SetCommTimeouts(COM3, &TimeOut))
        {
                strcat(TxdBuffer, "Unable to Setup serial Port Timeouts\n");
                w_result = false;
        }

    return (w_result);
}

//---------------------------------------------------------------------------

/*void show_result(int flag)
{
    switch(flag) {
      case 0:
        //TelnetForm->Shape1->Brush->Color = clGreen;
        TelnetForm->Button4->Font->Color = clBlue;
        TelnetForm->Button4->Caption = "PASS";
        CloseHandle(COM1);
        break;
      case 1:
        //Form1->Shape1->Brush->Color = clRed;
        TelnetForm->Button4->Font->Color = clRed;
        TelnetForm->Button4->Caption = "FAIL";
        CloseHandle(COM1);
        break;
      case 2:
        //TelnetForm->Shape1->Brush->Color = clYellow;
        TelnetForm->Button4->Font->Color = clRed;
        TelnetForm->Button4->Caption = "FAIL";
        break;
    }
}     */

int upgrade_codes()
{
        char *ptr;
        char length[10];

        TelnetForm->Timer1->Enabled = False;
        memset(RxdBuffer, NULL, sizeof(RxdBuffer));

        sprintf(TxdBuffer, "arp -d %s", IPStr);
        WinExec(TxdBuffer, NULL);

        //    Form1->Timer1->Interval = tLoadCmd;
        sprintf(TxdBuffer, "tftp -i 192.168.1.6 PUT nfjrom");    //@jack delete to 20150813
        //WinExec(TxdBuffer, SW_SHOWNORMAL);
        WinExec(TxdBuffer, NULL);                                //@jack delete to 20150813

        //Application->MessageBox(TxdBuffer, "TxdBuffer");

        //Application->MessageBox("Load_Image_Bat_Start", "Load_Start");
        // ShellExecute(NULL,"open","LoadImage.bat",NULL,NULL,SW_SHOWNORMAL);
        //Application->MessageBox("Load_Image_Bat_End", "Load_End");

        if (!get_login_prompt(0, "Success") || !get_login_prompt1(0, "Success") )
        return 1;

        //    TelnetForm->Timer1->Enabled = False;
        return 0;
}
//----------------------ACSuose-----------------------------------------------------

int get_login_prompt1(int flag, char *pattern)
{
        char sz_cmd[] = {0x2A,0x49,0x44,0x4E,0x3F,0x0A, '\r'};//{0x1B,'\r'};//0x2A 0x49 0x44 0x4E 0x3F 0x0A, '\r'};

        while (timeout)
        {
                if (flag == 1)
                WriteFile(COM3, sz_cmd, 7, &dw_Write, 0);
                ReadFile(COM3, &RxdBuffer, 1024, &dw_Read, NULL);
                if (dw_Read)
                {
                        TelnetForm->Memo1->Lines->Add(RxdBuffer);
                        if (NULL != strstr(RxdBuffer, pattern))
                        {
                                break;
                        }
                } // end of if (dw_Read)
                memset(RxdBuffer, NULL, strlen(RxdBuffer));
                Application->ProcessMessages();
        }   // end of while{}

        return (timeout);
}

void SetBootLoaderIPAddress1()
{
        IPStr[strlen(IPStr)-1] = IPStr[strlen(IPStr)-1] + 1;

        sprintf(TxdBuffer, "ipconfig %s\r", IPStr);
        WriteFile(COM3, TxdBuffer, strlen(TxdBuffer), &dw_Write, 0);
        ::Sleep(2000);
}

int GetPCNetWorkAddress1()
{
        PIP_ADAPTER_INFO pAdapterInfo;
        PIP_ADAPTER_INFO pAdapter = NULL;
        DWORD dwRetVal = 0;
        char *TmpPoint;
        int i;

        pAdapterInfo = (IP_ADAPTER_INFO *) malloc( sizeof(IP_ADAPTER_INFO) );
        ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);

        // Make an initial call to GetAdaptersInfo to get
        // the necessary size into the ulOutBufLen variable
        if (GetAdaptersInfo( pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
        {
                free(pAdapterInfo);
                pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen);
        }

        if ((dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
        {
                pAdapter = pAdapterInfo;
                while (pAdapter)
                {
                        if (strcmp(pAdapter->IpAddressList.IpAddress.String, "0.0.0.0") != 0)
                        {
                                strcpy(IPStr, pAdapter->IpAddressList.IpAddress.String);
                                GetAdaptersInfoFlag = 0;
                                return 0;
                        }
                        pAdapter = pAdapter->Next;
                }
                MessageBox(NULL, "Can not find network connection.", "Error", MB_OK);
                GetAdaptersInfoFlag = 1;
                exit(0);
        }
        else
        {
                MessageBox(NULL, "Can not find network adapter.", "Error", MB_OK);
                GetAdaptersInfoFlag = 2;
                exit(0);
        }
        return 1;
}
//---------------------------------------------------------------------------
void __fastcall TTelnetForm::Button8Click(TObject *Sender)
{
        if(EU->Checked == true)
   {
       /* if (!ifu_rs232_open1())
        {
                sprintf(MsgBuffer, "Open Com Port Error!");
                strcat(TxdBuffer, MsgBuffer);
                Application->MessageBox(TxdBuffer, "Error");
        }
        else
        {
                Label14->Caption = "Com port open successful";
        }
        char Test_220V_cmd[] = {0x56,0x4F,0x4C,0x54,0x61,0x67,0x65,0x3A,0x41,0x43,0x32,0x32,0x30,0x0A,'\r'};
        Timer1->Interval = 1;
        WriteFile(COM3, Test_220V_cmd, 20, &dw_Write, 0);
        ::Sleep(2000);
        Application->ProcessMessages();
        char Test_50Hz_cmd[] = {0x66,0x72,0x65,0x71,0x75,0x65,0x6E,0x63,0x79,0x35,0x30,0x0A,'\r'};
        Timer1->Interval = 1;
        WriteFile(COM3, Test_50Hz_cmd, 20, &dw_Write, 0);
        ::Sleep(2000);
        Application->ProcessMessages();
        char read_Vol_cmd[]={0x56,0x4F,0x4C,0x54,0x61,0x67,0x65,0x3A,0x61,0x63,0x3F,0x0A,'\r'};
        memset(RxdBuffer, NULL, sizeof(RxdBuffer));
        WriteFile(COM3, read_Vol_cmd, 20, &dw_Write, 0);
        ReadFile(COM3, &RxdBuffer, 1024, &dw_Read, NULL);
        if (dw_Read)
        {
                Label15->Caption = RxdBuffer;
        }  */
         Label14->Caption = "MODE ERROR";
   }
   if(US->Checked == true)
   {
        if (!ifu_rs232_open1())
        {
                sprintf(MsgBuffer, "Open Com Port Error!");
                strcat(TxdBuffer, MsgBuffer);
                Application->MessageBox(TxdBuffer, "Error");
        }
        else
        {
                Label14->Caption = "Com port open successful";
        }
        Application->ProcessMessages();
        char Test_110V_cmd[] = {0x56,0x4F,0x4C,0x54,0x61,0x67,0x65,0x3A,0x41,0x43,0x31,0x31,0x30,0x0A,'\r'};
        Timer1->Interval = 1;
        WriteFile(COM3, Test_110V_cmd, 20, &dw_Write, 0);
        ::Sleep(1500);
        Application->ProcessMessages();
        char Test_60Hz_cmd[] = {0x66,0x72,0x65,0x71,0x75,0x65,0x6E,0x63,0x79,0x36,0x30,0x0A,'\r'};
        Timer1->Interval = 1;
        WriteFile(COM3, Test_60Hz_cmd, 20, &dw_Write, 0);
        ::Sleep(1000);
        Application->ProcessMessages();

   }
    /*    //¥´¶}com port ¿ï¾ÜÉó«¬ªºcommand¬°*IDN?
        char Ver_cmd[] = {0x2A,0x49,0x44,0x4E,0x3F,0x0A, '\r'};//{0x1B,'\r'};//0x2A 0x49 0x44 0x4E 0x3F 0x0A, '\r'};
        int timeout = 1;
    //    int flag = 1;

        // Label1->Caption = "";

        if (!ifu_rs232_open1())
        {
                sprintf(MsgBuffer, "failed to open COM port for DUT1");
                strcat(TxdBuffer, MsgBuffer);
                Application->MessageBox(TxdBuffer, "Error");
                //goto EXIT;
        }
        Timer1->Interval = 0;
        memset(RxdBuffer, NULL, sizeof(RxdBuffer));

        WriteFile(COM3, Ver_cmd, 8, &dw_Write, 0);
        ReadFile(COM3, &RxdBuffer, 1024, &dw_Read, NULL);
        if (dw_Read)
        {
                //Form1->Memo1->Lines->Add(RxdBuffer);
                Label14->Caption = RxdBuffer;
                Label15->Caption = "Com port open successful";
        }
        else
        {
                Label15->Caption = "Com port error!";
                Button8->Enabled = True;
                CloseHandle(COM3);
         }

        ::Sleep(15000);
        char Test_220V_cmd[] = {0x56,0x4F,0x4C,0x54,0x61,0x67,0x65,0x3A,0x41,0x43,0x32,0x32,0x30,0x0A,'\r'};
        if (!ifu_rs232_open1())
                {
                        sprintf(MsgBuffer, "failed to open COM port for DUT2");
                        strcat(TxdBuffer, MsgBuffer);
                        Application->MessageBox(TxdBuffer, "Error");
                        //goto EXIT;
                }
                Timer1->Interval = 1;
                WriteFile(COM3, Test_220V_cmd, 20, &dw_Write, 0);
                ::Sleep(1000);

        //¿ï¾Ü¼Ò¦¡ªºcommand¬°MODECURR
     /*   char mode_cmd[] = {0x4D,0x4F,0x44,0x45,0x43,0x55,0x52,0x52,0x0A, '\r'};
        Timer1->Interval = 1;
        WriteFile(COM1, mode_cmd, 15, &dw_Write, 0);
        ::Sleep(1000);

//EXIT:
  //  Timer1->Enabled = False;
    //StartCmd->Enabled = True;
    //RadioCOM1->Enabled = True;
    //RadioCOM2->Enabled = True;
    //CloseHandle(COM1);  */
}

//---------------------------------------------------------------------------
//-----------------------mark end com port-----------------------------------
//---------------------------------------------------------------------------
void __fastcall TTelnetForm::btnConnectClick(TObject *Sender)
{
        String str,str1;
        IdTelnetDemo->Host = edtServer->Text;
        str = edtServer->Text;
        IdTelnetDemo->Port = StrToInt(spnedtPort->Text);
        str1 = spnedtPort->Text;
        //Application->MessageBox(str.c_str(),"IPShow");
        //Application->MessageBox(str1.c_str(),"PortShow");
        IdTelnetDemo->Connect();
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::btnDisconnectClick(TObject *Sender)
{
        IdTelnetDemo->Disconnect();
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Memo1KeyPress(TObject *Sender, char &Key)
{
        if(IdTelnetDemo->Connected())
        {
           IdTelnetDemo->SendCh(Key);
           Key = 0;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::IdTelnetDemoDataAvailable(AnsiString Buffer)
{
        int Start, Stop;
        String str;
        Memo1->Lines->Strings[Memo1->Lines->Count-1] =Memo1->Lines->Strings[Memo1->Lines->Count-1]+Buffer.c_str();
      /*  str=IntToStr(Memo1->Lines->Count);

        if(Memo1->Lines->Count == 0)
                Memo1->Lines->Add("");


        Start = 1;
        Stop = Buffer.Pos(IntToStr('\n')); //the character count to a CR in the buffer

        if(Stop == 0)
           Stop = Buffer.Length() + 1;

        while(Start <= Buffer.Length())
        {
                Memo1->Lines->Strings[Memo1->Lines->Count -1] =
                Memo1->Lines->Strings[Memo1->Lines->Count -1] +
                Buffer.SubString(Start,Stop-Start);

                if(Buffer.SubString(Stop,1)=='\n')
                {
                        Memo1->Lines->Add("");
                        SendMessage(Memo1->Handle,WM_KEYDOWN, VK_UP,1);
                }
                Start = Stop + 1;
                if(Start > Buffer.Length())
                {
                        break;
                }

                if(Buffer.SubString(Start,1)=='\n')
                {
                        Start++;
                }
                Stop = Start;

                while((Buffer.SubString(Stop, 1)!= '\n')&&(Stop <= Buffer.Length()))
                {
                        Stop++;
                }
        }        */

}
//---------------------------------------------------------------------------
void __fastcall TTelnetForm::IdTelnetDemoConnected(TObject *Sender)
{
        sbrStatus->SimpleText = "Connected";
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::IdTelnetDemoConnect()
{
        sbrStatus->SimpleText = "Connect";
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::LoginClick(TObject *Sender)
{
        String login = "pakedge\r";
        SendCommand(login);
        Memo1->Lines->Add("");

}
//---------------------------------------------------------------------------


void __fastcall TTelnetForm::PasswordClick(TObject *Sender)
{
        String passwork = "pakedgep\r";
        SendCommand(passwork);
        Memo1->Lines->Add("");
        IdTelnetDemo->SendCh('\n');
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TTelnetForm::SDcarClick(TObject *Sender)
{
        
        SDCard1->Text = "";
        Shape1->Brush->Color = clYellow;
        ::Sleep(500);
        Application->ProcessMessages();
        IdTelnetDemo->SendCh('\r');
        String SDcard = "test SD-card";
        SendCommand(SDcard);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
       // Memo1->Lines->Add("Pakedge-PDU$ test SD-card");
       // Memo1->Lines->Add("");
       // IdTelnetDemo->SendCh('\n');
        ::Sleep(1000);
        Application->ProcessMessages();
        Memo1Display();
        int num=Memo1->Lines->Count;
        ::Sleep(1500);
        Application->ProcessMessages();
        String yyy=Memo1->Lines->Strings[num-1]+Memo1->Lines->Strings[num-2]+Memo1->Lines->Strings[num]+Memo1->Lines->Strings[num+1];
        char *p = yyy.c_str();
        //Application->MessageBox(yyy.c_str(),"Show");
        char *cmd = "success";
        if(strstr(p,cmd) == NULL)
        {
                Result->Caption = "FAIL";
                Shape1->Brush->Color = clRed;
                Application->MessageBox("SDRAM test Fail,SDRAM is Bad\nSDœyÔ‡Ê§”¡£¬Õˆ´_ÕJSD¿¨£¡","show");
        }
        else
        {
                 Result->Caption = "PASS";
                 TelnetForm->SDcar->Enabled = false;
                 Shape1->Brush->Color = clLime;
                 SDCard1->Text =  test1;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::RAMClick(TObject *Sender)
{
        SDRAM1->Text =  "";
        IdTelnetDemo->SendCh('\r');
        Shape2->Brush->Color = clYellow;
        ::Sleep(1000);
        Application->ProcessMessages();
        String SDcard = "test SDRAM";
        SendCommand(SDcard);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
      //  Memo1->Lines->Add("Pakedge-PDU$ test SDRAM");
      //  Memo1->Lines->Add("");
      //  IdTelnetDemo->SendCh('\n');
      ::Sleep(1000);
        Application->ProcessMessages();
        Memo1Display();

        int num1=Memo1->Lines->Count;
        ::Sleep(1500);
        Application->ProcessMessages();
        String yyy1=Memo1->Lines->Strings[num1-1]+Memo1->Lines->Strings[num1-2]+Memo1->Lines->Strings[num1]+Memo1->Lines->Strings[num1+1];
        char *p1 = yyy1.c_str();
        //Application->MessageBox(yyy1.c_str(),"Show");
        char *cmd1 = "success";
        if(strstr(p1,cmd1) == NULL)
        {
                Result->Caption = "FAIL";
                Shape2->Brush->Color = clRed;
                if(CheckBox89->Checked == true)
                {
                        updateLogFile("89repeattestFAIL.txt", Memo1->Lines->Text, Result->Caption);
                }
                else if(CheckBox85->Checked == true)
                {
                        updateLogFile("85repeattestFAIL.txt", Memo1->Lines->Text, Result->Caption);
                }
                Application->MessageBox("SDRAM test Fail,SDRAM is Bad\nRAM¤º¦s¤£¨}","show");
        }
        else
        {
                 Result->Caption = "PASS";
                 TelnetForm->RAM->Enabled = false;
                 Shape2->Brush->Color = clLime;
                 SDRAM1->Text =  test1;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::BuzzerClick(TObject *Sender)
{
                Buzzer1->Text = "";
                Shape3->Brush->Color = clYellow;
                ::Sleep(1000);
                Application->ProcessMessages();
                IdTelnetDemo->SendCh('\r');
                String BuzzerON = "buzzer -v 1";   //BuzzerON
                SendCommand(BuzzerON);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
             //   Memo1->Lines->Add("Pakedge-PDU$ buzzer -v 1");
              //  Memo1->Lines->Add("");
               // IdTelnetDemo->SendCh('\n');
               ::Sleep(1000);
                Application->ProcessMessages();
                Memo1Display();

                int num2=Memo1->Lines->Count;
                ::Sleep(2000);
                Application->ProcessMessages();
                String yyy2=Memo1->Lines->Strings[num2]+Memo1->Lines->Strings[num2-1]+Memo1->Lines->Strings[num2-2]+Memo1->Lines->Strings[num2+1];
                char *p2 = yyy2.c_str();
                //Application->MessageBox(yyy2.c_str(),"Show");
                char *cmd2 = "success";
                if(strstr(p2,cmd2) == NULL)
                {
                        Result->Caption = "FAIL";
                        Shape3->Brush->Color = clRed;
                        //updateLogFile("Fail.txt", Memo1->Lines->Text, Result->Caption);
                        if(CheckBox89->Checked == true)
                        {
                                updateLogFile("89repeattestFAIL.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        else if(CheckBox85->Checked == true)
                        {
                                updateLogFile("85repeattestFAIL.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        Application->MessageBox("Buzzer test Fail","show");
                }

                ::Sleep(1000);
                Application->ProcessMessages();

                IdTelnetDemo->SendCh('\r');
                String BuzzerOFF = "buzzer -v 0";   //BuzzerOFF
                SendCommand(BuzzerOFF);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
              //  Memo1->Lines->Add("Pakedge-PDU$ buzzer -v 0");
              //  Memo1->Lines->Add("");
              //  IdTelnetDemo->SendCh('\n');
              ::Sleep(1000);
                Application->ProcessMessages();
                Memo1Display();

                int num3=Memo1->Lines->Count;
                ::Sleep(2000);
                Application->ProcessMessages();
                String yyy3=Memo1->Lines->Strings[num3]+Memo1->Lines->Strings[num3-1]+Memo1->Lines->Strings[num3-2]+Memo1->Lines->Strings[num3+1];
                char *p3 = yyy3.c_str();
                //Application->MessageBox(yyy3.c_str(),"Show");
                char *cmd3 = "success";
                if(strstr(p3,cmd3) == NULL)
                {
                        Result->Caption = "FAIL";
                        Shape3->Brush->Color = clRed;
                        //updateLogFile("Fail.txt", Memo1->Lines->Text, Result->Caption);
                        Application->MessageBox("Buzzer shut test Fail\n¸Á»ï¾¹´ú¸Õ¥¢±Ñ”¡","show");
                }
                 else
                {
                        Result->Caption = "PASS";
                        TelnetForm->Buzzer->Enabled = false;
                        Shape3->Brush->Color = clLime;
                        Buzzer1->Text = test1;
                }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::PingtClick(TObject *Sender)
{

       ping1->Text = "";
       Shape4->Brush->Color = clYellow;
       ::Sleep(1000);
       Application->ProcessMessages();
       IdTelnetDemo->SendCh('\r');
       String ping = PingIP->Text;
       SendCommand(ping);
       ::Sleep(500);
       Application->ProcessMessages();
       SendCommand(Enter);
      // Memo1->Lines->Add("Pakedge-PDU$ ping -i 192.168.1.111");
      // Memo1->Lines->Add("");
      // IdTelnetDemo->SendCh('\n');
       Memo1Display();

       int num4=Memo1->Lines->Count;
       ::Sleep(8500);
       Application->ProcessMessages();
       String yyy4=Memo1->Lines->Strings[num4];
       char *p4 = yyy4.c_str();
       //Application->MessageBox(yyy4.c_str(),"Show");
       char *cmd4 = "success";
       if(strstr(p4,cmd4) == NULL)
       {
                Result->Caption = "FAIL";
                Shape4->Brush->Color = clRed;
                if(CheckBox89->Checked == true)
                {
                        updateLogFile("89repeattestFAIL.txt", Memo1->Lines->Text, Result->Caption);
                }
                else if(CheckBox85->Checked == true)
                {
                        updateLogFile("85repeattestFAIL.txt", Memo1->Lines->Text, Result->Caption);
                }
                Application->MessageBox("Ping test Fail,Check the PC IP\nPing´ú¸Õ¤£¨}¡A½Ð½T»{¨Ã­«·s´ú¸Õ","show");
       }
       else
       {
                Result->Caption = "PASS";
                TelnetForm->Pingt->Enabled = false;
                Shape4->Brush->Color = clLime;
                ping1->Text = test1;
       }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::InfoFWClick(TObject *Sender)
{
               FW1->Text = "";
                model1->Text = "";
                aMAC->Text = "";
                aSN->Text = "";
                Shape5->Brush->Color = clYellow;
                ::Sleep(1000);
                Application->ProcessMessages();
                IdTelnetDemo->SendCh('\r');
                String ShowDeviceInfo = "show device-info";
                SendCommand(ShowDeviceInfo);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
               // Memo1->Lines->Add("Pakedge-PDU$ show device-info");
               // Memo1->Lines->Add("");
               // IdTelnetDemo->SendCh('\n');
                Memo1Display();

                int num5=Memo1->Lines->Count;
                ::Sleep(3000);
                Application->ProcessMessages();
                String yyy5=Memo1->Lines->Strings[num5];
                char *p5 = yyy5.c_str();

                String right50 =  yyy5.SubString((yyy5.Pos("firmware_version")+19),28);
                String left50 = right50.SubString(0,(right50.Pos("model")-4));
                FW->Caption = left50;
                char *left501 =left50.c_str();
                if(strcmp(left501,Firmware)!=0)
                {
                      Result->Caption = "Fail";
                      Shape5->Brush->Color = clRed;
                      Application->MessageBox("PDU FW Error!\nFW¤£¤Ç°t¡A½Ð½T»{°t¸mÀÉ¬O§_¥¿½T","Error",MB_ICONASTERISK);
                }
                else FW1->Text = left50;
                String right51 =  yyy5.SubString((yyy5.Pos("model")+8),28);
                String left51 = right51.SubString(0,(right51.Pos("serial_number")-4));
                Model->Caption = left51;
          /*    strcpy(&Model_number[0],Model->Caption.c_str());
                String Model_number0 =Model_number[0];
                String Model_number1 = Model_number[1];
                String Model_number2 = Model_number[2];
                String Model_number3 = Model_number[3];
                String Model_number4 = Model_number[4];
                String Model_number5 = Model_number[5];  */
                if(EU->Checked == true)
                {
                      char *left511 =left51.c_str();
                      char *left510 = "PE-08I";
                      if(strcmp(left511,left510)!=0)
                      {
                            Result->Caption = "Fail";
                            Shape5->Brush->Color = clRed;
                            Application->MessageBox("PDU Model Error!\n¾÷«¬¤£¤Ç°t¡A½Ð½T»{°t¸mÀÉ¬O§_¥¿½T","Error",MB_ICONASTERISK);
                      }
                      else model1->Text = left51;
                }
                if(US->Checked == true)
                {
                      char *left511 =left51.c_str();
                      char *left510 = "PE-09N";
                      if(strcmp(left511,left510)!=0)
                      {
                            Result->Caption = "Fail";
                            Shape5->Brush->Color = clRed;
                            Application->MessageBox("PDU Model Error!\n¾÷«¬¤£¤Ç°t¡A½Ð½T»{°t¸mÀÉ¬O§_¥¿½T","Error",MB_ICONASTERISK);
                      }
                      else model1->Text = left51;
                }

                String right52 =  yyy5.SubString((yyy5.Pos("serial_number")+16),28);
                String left52 = right52.SubString(0,(right52.Pos("MAC")-4));
                if(CheckBox89->Checked ==true)
                {
                    aSN->Text = left52;
                }
                else aSN->Text = "";
                //SN->Caption = left52;

                String right53 =  yyy5.SubString((yyy5.Pos("MAC")+6),28);
                String left53 = right53.SubString(0,(right53.Pos("hostname")-4));
                //MAC->Caption = left53;
                 if(CheckBox89->Checked ==true)
                {
                    aMAC->Text = left53;
                }
                else aMAC->Text = "";
                char *cmd5 = "success";
                if(strstr(p5,cmd5) == NULL)
                {
                        Result->Caption = "FAIL";
                        Shape5->Brush->Color = clRed;
                        Application->MessageBox("Device info test Fail\n³]³Æ«H®§´ú¸Õ¥¢±Ñ","show");
                }
                else
                {
                        Result->Caption = "PASS";
                        TelnetForm->InfoFW->Enabled = false;
                        Shape5->Brush->Color = clLime;

                }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::InfosClick(TObject *Sender)
{
                voltage1->Text = "";
                frequency1->Text = "";
                temp1->Text = "";
                humidity1->Text = "";
                Shape6->Brush->Color = clYellow;
                ::Sleep(1000);
                Application->ProcessMessages();
                IdTelnetDemo->SendCh('\r');
                String ShowPDUStatus = "show pdu-status";
                SendCommand(ShowPDUStatus);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
               // Memo1->Lines->Add("Pakedge-PDU$ show pdu-status");
               // Memo1->Lines->Add("");
               // IdTelnetDemo->SendCh('\n');
                Memo1Display();

                int num6=Memo1->Lines->Count;
                ::Sleep(2500);
                Application->ProcessMessages();
                String yyy6=Memo1->Lines->Strings[num6];
                char *p6 = yyy6.c_str();

                String right60 = yyy6.SubString((yyy6.Pos("pdu_voltage")+14),15);
                String left60 = right60.SubString(0,right60.Pos("V")-2);
                String left600 = StrToInt(left60);
                Voltage->Caption = left60+outlet10+left601;
                if(CheckBox85->Checked == true)
                {
                        if(EU->Checked == true)
                        {

                                if(left600>242||left600<218)
                                {
                                        Result->Caption = "Fail";
                                        Shape6->Brush->Color = clRed;
                                        Application->MessageBox("Voltage is not within the extent!\n¹qÀ£¤£¤Ç°t","Error",MB_ICONASTERISK);
                                        IdTelnetDemo->Disconnect();
                                        return;
                                }
                                else  voltage1->Text = left60;
                        }
                        if(US->Checked == true)
                        {
                                if(left600>126||left600<114)
                                {
                                        Result->Caption = "Fail";
                                        Shape6->Brush->Color = clRed;
                                        Application->MessageBox("Voltage is not within the extent!\n¹qÀ£¤£¤Ç°t","Error",MB_ICONASTERISK);
                                }
                                else  voltage1->Text = left60;
                         }
                         String right61 = yyy6.SubString((yyy6.Pos("pdu_frequency")+16),15);
                        String left61 = right61.SubString(0,(right61.Pos("Hz")+1)-3);
                        String left610 = StrToInt(left61);
                        Frequency->Caption = left61 + left602;

                        if(EU->Checked == true)
                        {
                                if(left610>=52||left610<=48)
                                 {
                                        Result->Caption = "Fail";
                                        Shape6->Brush->Color = clRed;
                                        Application->MessageBox("Frequency is not within the extent!\nÀW²v¤£¤Ç°t","Error",MB_ICONASTERISK);
                                }
                                else  frequency1->Text = left61;
                        }
                        if(US->Checked == true)
                        {
                                if(left610>=62||left610<=58)
                                {
                                        Result->Caption = "Fail";
                                        Shape6->Brush->Color = clRed;
                                        Application->MessageBox("Frequency is not within the extent!\nÀW²v¤£¤Ç°t","Error",MB_ICONASTERISK);
                                }
                                else  frequency1->Text = left61;
                        }

                }

                String right62 =  yyy6.SubString((yyy6.Pos("pdu_current")+14),15);
                String left62 = right62.SubString(0,right62.Pos("A"));
                Current->Caption = left62;

                String right63 =  yyy6.SubString((yyy6.Pos("pdu_temp")+11),15);
                String left63 = right63.SubString(0,right63.Pos("\"")-1);
                String left634 = "C";
                String left636 = "F";
                if(EU->Checked == true)
                {
                         String left635 = left63 + outlet10 +left634;
                         Tem->Caption =left635;
                         temp1->Text = left63+left634;
                }
                if(US->Checked == true)
                {
                         String left635 = left63 + outlet10 +left636;
                         Tem->Caption =left635;
                         temp1->Text = left63+left636;
                }

                String right64 =  yyy6.SubString((yyy6.Pos("pdu_humidity")+15),15);
                String left64 = right64.SubString(0,right64.Pos("%"));
                String left640 = "%";
                Hum->Caption = left64+outlet10+left640;
                humidity1->Text = left64;

                char *cmd6 = "success";
                if(strstr(p6,cmd6) == NULL)
                {
                        Result->Caption = "FAIL";
                        Shape6->Brush->Color = clRed;
                }
                else
                {
                        Result->Caption = "PASS";
                        TelnetForm->Infos->Enabled = false;
                        Shape6->Brush->Color = clLime;
                }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::OutlettClick(TObject *Sender)
{
        IdTelnetDemo->SendCh('\r');
        outlettest1->Text = "";
        String set_outlet_1_off = "set outlet-power -o 1 -v 0";
        String set_outlet_2_off = "set outlet-power -o 2 -v 0";
        String set_outlet_3_off = "set outlet-power -o 3 -v 0";
        String set_outlet_4_off = "set outlet-power -o 4 -v 0";
        String set_outlet_5_off = "set outlet-power -o 5 -v 0";
        String set_outlet_6_off = "set outlet-power -o 6 -v 0";
        String set_outlet_7_off = "set outlet-power -o 7 -v 0";
        String set_outlet_8_off = "set outlet-power -o 8 -v 0";
        String set_outlet_9_off = "set outlet-power -o 9 -v 0";

        Application->MessageBox("Observe each LED light is put out status\nÆ[¹îLED¨Ì¦¸º¶·À","show");
        Shape7->Brush->Color = clYellow;
        ::Sleep(1000);
        Application->ProcessMessages();
        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
      //  Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 1 -v 0");
      //  Memo1->Lines->Add("");
      //  IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_2_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
       // Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 2 -v 0");
       // Memo1->Lines->Add("");
       // IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_3_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
       // Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 3 -v 0");
       // Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_4_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
       // Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 4 -v 0");
       // Memo1->Lines->Add("");
       // IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_5_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
       // Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 5 -v 0");
       // Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_6_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 6 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_7_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 7 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_8_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 8 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();
        ::Sleep(1000);
        Application->ProcessMessages();
        if(US->Checked == true)
        {
                SendCommand(set_outlet_9_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 9 -v 0");
                //Memo1->Lines->Add("");
                //IdTelnetDemo->SendCh('\n');
                Memo1Display();
        }
        ::Sleep(1000);
        Application->ProcessMessages();
//--------------------------------------------------------------------------//

//-------------------outlet-power set on-----------------------------------//
        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_on = "set outlet-power -o 1 -v 1\r";
        String set_outlet_2_on = "set outlet-power -o 2 -v 1\r";
        String set_outlet_3_on = "set outlet-power -o 3 -v 1\r";
        String set_outlet_4_on = "set outlet-power -o 4 -v 1\r";
        String set_outlet_5_on = "set outlet-power -o 5 -v 1\r";
        String set_outlet_6_on = "set outlet-power -o 6 -v 1\r";
        String set_outlet_7_on = "set outlet-power -o 7 -v 1\r";
        String set_outlet_8_on = "set outlet-power -o 8 -v 1\r";
        String set_outlet_9_on = "set outlet-power -o 9 -v 1\r";

        Application->MessageBox("Observe each LED light up status\nÆ[¹îLED¿O¨Ì¦¸«G°_","show");
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
       // Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 1 -v 1");
       // Memo1->Lines->Add("");
       // IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(2000);
        Application->ProcessMessages();

        SendCommand(set_outlet_2_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 2 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(2000);
        Application->ProcessMessages();

        SendCommand(set_outlet_3_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
       // Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 3 -v 1");
       // Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(2000);
        Application->ProcessMessages();

        SendCommand(set_outlet_4_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
       // Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 4 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(2000);
        Application->ProcessMessages();

        SendCommand(set_outlet_5_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
       // Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 5 -v 1");
       // Memo1->Lines->Add("");
       // IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(2000);
        Application->ProcessMessages();

        SendCommand(set_outlet_6_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 6 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(2000);
        Application->ProcessMessages();

        SendCommand(set_outlet_7_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 7 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(2000);
        Application->ProcessMessages();

        SendCommand(set_outlet_8_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 8 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(2000);
        Application->ProcessMessages();
        if(US->Checked == true)
        {
                SendCommand(set_outlet_9_on);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 9 -v 1");
                //Memo1->Lines->Add("");
                //IdTelnetDemo->SendCh('\n');
                Memo1Display();
        }

        if (Application->MessageBox("LEDs are all light up?\n½Ð½T»{LED¿O¬O§_¥þ³¡«G°_¡A¨Ã½T»{¿é¥XºÝ¤f´ú¸Õ¬O§_OK","heck LEDs light up",MB_OKCANCEL) == IDCANCEL)  //Check the LEDs are all light up again?
        {
                Result->Caption = "FAIL";
                Shape7->Brush->Color = clYellow;
                Memo1->Lines->Add("LEDs are not all light up");
        }
        else
        {
                Result->Caption = "PASS";
                TelnetForm->Outlett->Enabled = false;
                Shape7->Brush->Color = clLime;
                outlettest1->Text = test1;
        }
}
//---------------------------------------------------------------------------
void __fastcall TTelnetForm::PowerCClick(TObject *Sender)
{
        powercycle1->Text = "";
       IdTelnetDemo->SendCh('\r');
        String power_cycle_1_on = "power-cycle -o 1";
        String power_cycle_2_on = "power-cycle -o 2";
        String power_cycle_3_on = "power-cycle -o 3";
        String power_cycle_4_on = "power-cycle -o 4";
        String power_cycle_5_on = "power-cycle -o 5";
        String power_cycle_6_on = "power-cycle -o 6";
        String power_cycle_7_on = "power-cycle -o 7";
        String power_cycle_8_on = "power-cycle -o 8";
        String power_cycle_9_on = "power-cycle -o 9";

        Application->MessageBox("check each LED light up after put out\n½ÐÆ[¹îLED¿O¥ýº¶·À«á«G°_","show");
        Shape8->Brush->Color = clYellow;
        ::Sleep(1000);
        Application->ProcessMessages();
        SendCommand(power_cycle_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        int num20=Memo1->Lines->Count;
        ::Sleep(3000);
         Application->ProcessMessages();
         String yyy20=Memo1->Lines->Strings[num20];
         char *p20 = yyy20.c_str();

        ::Sleep(3000);
        Application->ProcessMessages();

        SendCommand(power_cycle_2_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 2");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(3000);
        Application->ProcessMessages();

        SendCommand(power_cycle_3_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 3");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(3000);
        Application->ProcessMessages();

        SendCommand(power_cycle_4_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 4");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(3000);
        Application->ProcessMessages();

        SendCommand(power_cycle_5_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 5");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(3000);
        Application->ProcessMessages();

        SendCommand(power_cycle_6_on);
        //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 6");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();

        ::Sleep(3000);
        Application->ProcessMessages();

        SendCommand(power_cycle_7_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 7");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(3000);
        Application->ProcessMessages();

        SendCommand(power_cycle_8_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 8");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(3000);
        Application->ProcessMessages();
        if(US->Checked == true)
        {
                SendCommand(power_cycle_9_on);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 9");
                //Memo1->Lines->Add("");
                //IdTelnetDemo->SendCh('\n');
                Memo1Display();
        }
        if (Application->MessageBox("Power Cycle test is ok?\n½Ð½T»{Power Cycle´ú¸Õ¬O§_OK","Check",MB_OKCANCEL) == IDCANCEL)  //Check the PDU Status is Right again?
        {
                Result->Caption = "FAIL";
                Shape8->Brush->Color = clRed;
                Memo1->Lines->Add("PDU power cycle is Wrong");
         }
         else
         {
                Result->Caption = "PASS";
                TelnetForm->PowerC->Enabled = false;
                Shape8->Brush->Color = clLime;
                outlettest1->Text = test1;
        }
}
//---------------------------------------------------------------------------
void __fastcall TTelnetForm::OLEDClick(TObject *Sender)
{
        OLED1->Text = "";
      Shape9->Brush->Color = clYellow;
      ::Sleep(1000);
      Application->ProcessMessages();
      IdTelnetDemo->SendCh('\r');
      String oled_fill_1 = "test oled-fill 1";
      SendCommand(oled_fill_1);
      ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
     // Memo1->Lines->Add("Pakedge-PDU$ test oled-fill 1");
      //Memo1->Lines->Add("");
      //IdTelnetDemo->SendCh('\n');
      ::Sleep(1000);
      Application->ProcessMessages();
      Memo1Display();

      int num11=Memo1->Lines->Count;
      ::Sleep(2000);
      Application->ProcessMessages();
      String yyy11=Memo1->Lines->Strings[num11]+Memo1->Lines->Strings[num11-1]+Memo1->Lines->Strings[num11-2]+Memo1->Lines->Strings[num11+1];
      char *p11 = yyy11.c_str();
      Application->MessageBox(yyy11.c_str(),"Show");
      char *cmd11 = "success";
      if(strstr(p11,cmd11) == NULL)
      {
                Result->Caption = "FAIL";
                Shape9->Brush->Color = clRed;
                if(CheckBox89->Checked == true)
                {
                        updateLogFile("89repeattestFAIL.txt", Memo1->Lines->Text, Result->Caption);
                }
                else if(CheckBox85->Checked == true)
                {
                        updateLogFile("85repeattestFAIL.txt", Memo1->Lines->Text, Result->Caption);
                }
                Application->MessageBox("Oled test","show");
      }
      if (Application->MessageBox("OLED have not Dark spot and Light spot?\n½ÐÆ[¹î¥Õ¦â«Ì¹õ¤W¬O§_¦³«GÂI©Î·tÂI¡A¨Ó§PÂ_OLED¬O§_OK","Check OLED",MB_OKCANCEL) == IDCANCEL)  //Check the OLED have not Dark spot and Light spot again?
      {
        Result->Caption = "FAIL";
        Shape9->Brush->Color = clRed;
        Memo1->Lines->Add("OLED have Dark spot or Light spot");

        if(CheckBox89->Checked == true)
        {
                updateLogFile("89repeattestFAIL.txt", Memo1->Lines->Text, Result->Caption);
        }
        else if(CheckBox85->Checked == true)
        {
                updateLogFile("85repeattestFAIL.txt", Memo1->Lines->Text, Result->Caption);
        }
      }

      ::Sleep(2000);
      Application->ProcessMessages();
      IdTelnetDemo->SendCh('\r');
      String oled_fill_0 = "test oled-fill 0";   //¶Â«Ì´ú¸Õ
      SendCommand(oled_fill_0);
      ::Sleep(500);
      Application->ProcessMessages();
      SendCommand(Enter);
     // Memo1->Lines->Add("Pakedge-PDU$ test oled-fill 0");
     // Memo1->Lines->Add("");
     // IdTelnetDemo->SendCh('\n');
     ::Sleep(1000);
      Application->ProcessMessages();
      Memo1Display();

      int num12=Memo1->Lines->Count;
      ::Sleep(2000);
      Application->ProcessMessages();
      String yyy12=Memo1->Lines->Strings[num12]+Memo1->Lines->Strings[num12-1]+Memo1->Lines->Strings[num12-2]+Memo1->Lines->Strings[num12+1];
      char *p12 = yyy12.c_str();
      Application->MessageBox(yyy12.c_str(),"Show");
      char *cmd12 = "success";
      if(strstr(p12,cmd12) == NULL)
      {
                        Result->Caption = "FAIL";
                        Shape9->Brush->Color = clRed;

      }
      if (Application->MessageBox("OLED have not Dark spot and Light spot?\n\n½ÐÆ[¹î¶Â¦â¦â«Ì¹õ¤W¬O§_¦³«GÂI©Î·tÂI¡A¨Ó§PÂ_OLED¬O§_OK","Check OLED",MB_OKCANCEL) == IDCANCEL)  //Check the OLED have not Dark spot and Light spot again?
      {
                Result->Caption = "FAIL";
                Shape9->Brush->Color = clRed;
                Memo1->Lines->Add("OLED have Dark spot or Light spot");
      }
      else
      {
                Result->Caption = "PASS";
                TelnetForm->OLED->Enabled = false;
                Shape9->Brush->Color = clLime;
                OLED1->Text = test1;
      }
}

//---------------------------------------------------------------------------

void __fastcall TTelnetForm::LEDClick(TObject *Sender)
{
        LED1->Text = "";
        IdTelnetDemo->SendCh('\r');
        String LEDLuminace_0_on = "test leddim 0";
        String LEDLuminace_10_on = "test leddim 10";

        Application->MessageBox("please check the LED brightness is changes\n½ÐÆ[¹î©Ò¦³ªºLED«G«×¬O§_¦³ÅÜ¤Æ","show");
        Shape10->Brush->Color = clYellow;
        ::Sleep(1000);
        Application->ProcessMessages();
        SendCommand(LEDLuminace_0_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
       // Memo1->Lines->Add("Pakedge-PDU$ test leddim 0");
      //  Memo1->Lines->Add("");
      //  IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(2000);
        Application->ProcessMessages();

        ::Sleep(2000);
        Application->ProcessMessages();

        SendCommand(LEDLuminace_10_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
      //  Memo1->Lines->Add("Pakedge-PDU$ test leddim 10");
       // Memo1->Lines->Add("");
       // IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(3000);
        Application->ProcessMessages();
        if (Application->MessageBox("LEDLuminance test is ok?\nLED«G«×´ú¸Õ¬O§_OK","Check",MB_OKCANCEL) == IDCANCEL)  //Check the PDU Status is Right again?
        {
                Result->Caption = "FAIL";
                Shape10->Brush->Color = clRed;
                Memo1->Lines->Add("LEDLuminance is Wrong");
        }
        else
        {
                Result->Caption = "PASS";
                TelnetForm->LED->Enabled = false;
                Shape10->Brush->Color = clLime;
                LED1->Text = test1;
        }
}
//---------------------------------------------------------------------------
void __fastcall TTelnetForm::StaticipClick(TObject *Sender)
{
        staticsip1->Text = "";
        Shape11->Brush->Color = clYellow;
        ::Sleep(1000);
        Application->ProcessMessages();
        IdTelnetDemo->SendCh('\r');
        String SetNet = "set net -t static -i 192.168.1.252 -m 255.255.255.0 -g 192.168.1.99 -d 8.8.8.8";
        SendCommand(SetNet);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        // Memo1->Lines->Add("Pakedge-PDU$ set net -t Static -i 192.168.1.252 -m 255.255.255.0 -g 192.168.1.1 -d 8.8.8.8");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();
        int num8=Memo1->Lines->Count;
        ::Sleep(5000);
        Application->ProcessMessages();
        String yyy8=Memo1->Lines->Strings[num8];
        char *p8 = yyy8.c_str();
        char *cmd8 = "success";
        if(strstr(p8,cmd8) == NULL)
        {
                Result->Caption = "FAIL";
        }
        String Reboot = "reboot";
        SendCommand(Reboot);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);

       /* Application->ProcessMessages();
        ::Sleep(2000);
        Application->ProcessMessages();
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        String str2,str3;
        IdTelnetDemo->Host = IP->Text;
        str2 = IP->Text;
        IdTelnetDemo->Port = StrToInt(spnedtPort->Text);
        str3 = spnedtPort->Text;

        IdTelnetDemo->Connect();

        Application->ProcessMessages();
        ::Sleep(500);
        Application->ProcessMessages();

       Memo1->Lines->Add("");
        String login = "pakedge\r";
        SendCommand(login);
      //  Memo1->Lines->Add("Pakedge-PDU$ login: pakedge");
     //   Memo1->Lines->Add("");
        Application->ProcessMessages();
        ::Sleep(600);
        Application->ProcessMessages();

        String password = "pakedgep\r";
        SendCommand(password);
      //  Memo1->Lines->Add("password: pakedgep");
      //  Memo1->Lines->Add("");
       // IdTelnetDemo->SendCh('\n');
        Application->ProcessMessages();
        ::Sleep(600);
        Application->ProcessMessages();
        Result2->Caption = "Testing";
        IdTelnetDemo->SendCh('\r');
        String ShowNet = "show net";
        SendCommand(ShowNet);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1->Lines->Add("Pakedge-PDU$ show net");
        Memo1->Lines->Add("");
        IdTelnetDemo->SendCh('\n');
        Memo1Display();

        int num9=Memo1->Lines->Count;
        ::Sleep(2000);
        Application->ProcessMessages();
        String yyy9=Memo1->Lines->Strings[num9-1];
       //Application->MessageBox(yyy9.c_str(),"Show");
        char *p9 = yyy9.c_str();
        char *cmd9 = "success";
        if(strstr(p9,cmd9) == NULL)
        {
                Result2->Caption = "FAIL";
                if(CheckBox89->Checked == true)
                {
                        updateLogFile("89-Fail.txt", Memo1->Lines->Text, Result->Caption);
                }
                else if(CheckBox85->Checked == true)
                {
                        updateLogFile("85-Fail.txt", Memo1->Lines->Text, Result->Caption);
                }
                Application->MessageBox("Set static IP address function Fail","show");
               // TelnetForm->Button1->Enabled = true;
        }
        else
        {
                staticsip1->Text = test1;
        }
        Application->MessageBox("Factory Default\n»ÖÍ³öSÔOÖÃ","show");
        IdTelnetDemo->SendCh('\r');
        String Reset = "factory-default\r";
        SendCommand(Reset);
        Memo1->Lines->Add("Pakedge-PDU$ factory-default");
        Memo1->Lines->Add("");
        IdTelnetDemo->SendCh('\n');
        Memo1Display();     */
}

//---------------------------------------------------------------------------


void __fastcall TTelnetForm::SendCommand(AnsiString CMD)
{
        for(int i=0;i<CMD.Length();i++)
        {
                IdTelnetDemo->SendCh(CMD.c_str()[i]);
        }
}

void __fastcall TTelnetForm::Memo1Display()
{
        for(int i=6;i>0;i--)
        {
                SendMessage(Memo1->Handle,EM_SCROLL,SB_LINEDOWN,0);
        }
}

void __fastcall TTelnetForm::Delay(unsigned int Time)
{
        int t0 = ::GetTickCount();
        while(::GetTickCount()-t0<Time)
        {
                Application->ProcessMessages();
        }

}

void __fastcall TTelnetForm::STARTClick(TObject *Sender)
{
        if((CheckBox85->Checked == true && EU->Checked == true && CheckBox89->Checked != true && US->Checked != true)
         ||(CheckBox85->Checked == true && US->Checked == true && CheckBox89->Checked != true && EU->Checked != true)
         ||(CheckBox89->Checked == true && EU->Checked == true && CheckBox85->Checked != true && US->Checked != true)
         ||(CheckBox89->Checked == true && US->Checked == true && CheckBox85->Checked != true && EU->Checked != true))
        {

        }
        else
        {
                //Application->MessageBox("½Ð¤Ä¿ï¬ÛÃö´ú¸Õ¶µ¥Ø","Åã¥Ü");
                Application->MessageBox("Check the config.ini¡I¡I","show");
                return;
        }

        Shape1->Brush->Color = clWhite;
        Shape2->Brush->Color = clWhite;
        Shape3->Brush->Color = clWhite;
        Shape4->Brush->Color = clWhite;
        Shape5->Brush->Color = clWhite;
        Shape6->Brush->Color = clWhite;
        Shape7->Brush->Color = clWhite;
        Shape8->Brush->Color = clWhite;
        Shape9->Brush->Color = clWhite;
        Shape10->Brush->Color = clWhite;
        Shape11->Brush->Color = clWhite;

        SDCard1->Text = "";
        SDRAM1->Text =  "";
        Buzzer1->Text = "";
        ping1->Text = "";
        FW1->Text = "";
        model1->Text = "";
        aMAC->Text = "";
        aSN->Text = "";
        voltage1->Text = "";
        frequency1->Text = "";
        temp1->Text = "";
        humidity1->Text = "";
        outlettest1->Text = "";
        powercycle1->Text = "";
        OLED1->Text = "";
        LED1->Text = "";
        staticsip1->Text = "";

        Result2->Caption = "";
        Result2->Caption = "";
        TelnetForm->START->Enabled = false;

        String str,str1;
        IdTelnetDemo->Host = edtServer->Text;
        str = edtServer->Text;
        IdTelnetDemo->Port = StrToInt(spnedtPort->Text);
        str1 = spnedtPort->Text;
        IdTelnetDemo->Connect();

        Current->Caption = "";
        Frequency->Caption = "";
        FW->Caption = "";
        Model->Caption = "";
        Voltage->Caption = "";
        Result->Caption = "";
        Tem->Caption = "";
        Hum->Caption = "";

        Memo1->Clear();
        Application->ProcessMessages();
        ::Sleep(600);
        Application->ProcessMessages();

        Memo1->Lines->Add("");
        int num100=Memo1->Lines->Count;
        ::Sleep(1500);
        Application->ProcessMessages();
        String yyy100=Memo1->Lines->Strings[num100]+Memo1->Lines->Strings[num100-1]+Memo1->Lines->Strings[num100+1];
        char *p100 = yyy100.c_str();
        String login = "pakedge\r";
        char *a = "1ogin as";
        if(strcmp(p100,a)==0){
     //   Memo1->Lines->Add("");
        //String login = "pakedge";
        SendCommand(login);
        }else
        {
             ::Sleep(1000);
             Application->ProcessMessages();
             SendCommand(login);
        }
       /* String login = "pakedge\r";
        SendCommand(login);     */
     //   Memo1->Lines->Add("Pakedge-PDU$ login: pakedge");
        Application->ProcessMessages();
        ::Sleep(1000);
        Application->ProcessMessages();

        int num210=Memo1->Lines->Count;
        String password = "pakedgep\r";
        String yyy210=Memo1->Lines->Strings[num210]+Memo1->Lines->Strings[num210-1]+Memo1->Lines->Strings[num210+1];
        char *p210 = yyy210.c_str();
        char *a2 = "password";
        if(strstr(p210,a2) != NULL)
        {
             SendCommand(password);
        }
        else
        {
             ::Sleep(1000);
             Application->ProcessMessages();
             SendCommand(password);
        }
     //   Memo1->Lines->Add("password: pakedgep");
      //  Memo1->Lines->Add("");
      //  IdTelnetDemo->SendCh('\n');
        Application->ProcessMessages();
        ::Sleep(600);
        Application->ProcessMessages();

        Result->Caption = "Testing";
//-------------@jack to add start test the SD-card test-------------------//
        if(CheckBoxSDCard->Checked == true)//(CheckBox89->Checked == true) && (CheckBoxSDCard->Checked == true))
        {
                Shape1->Brush->Color = clYellow;
                ::Sleep(1000);
                Application->ProcessMessages();
                IdTelnetDemo->SendCh('\r');
                String SDcard = "test SD-card";
                SendCommand(SDcard);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
               // Memo1->Lines->Add("Pakedge-PDU$ test SD-card");
               // Memo1->Lines->Add("");
               // IdTelnetDemo->SendCh('\n');
               ::Sleep(1000);
                Application->ProcessMessages();
                Memo1Display();

                int num1=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();

                String yyy1=Memo1->Lines->Strings[num1]+Memo1->Lines->Strings[num1-1]+Memo1->Lines->Strings[num1-2]+Memo1->Lines->Strings[num1+1];
                char *p1 = yyy1.c_str();
                //Application->MessageBox(yyy1.c_str(),"Show");
                char *cmd1 = "success";
                if(strstr(p1,cmd1) == NULL)
                {
                        Result->Caption = "FAIL";
                        Shape1->Brush->Color = clRed;
                        if(CheckBox89->Checked == true)
                        {
                                updateLogFile("89-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        else if(CheckBox85->Checked == true)
                        {
                                updateLogFile("85-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        Application->MessageBox("SD-Card test Fail,Check the SD-Card\nSD¥d´ú¸Õ¥¢±Ñ","show");
                }
                 else
                 {
                        TelnetForm->SDcar->Enabled = false;
                        Shape1->Brush->Color = clLime;
                        SDCard1->Text = test1;
                 }
        }

//-------------@jack to add end test the SD-card test-------------------//


//-------------@jack to add start test the SDRAM test-------------------//
        if(CheckBoxSDRAM->Checked == true)
        {
               // Application->MessageBox("SDRAM Test","show");
                Shape2->Brush->Color = clYellow;
                ::Sleep(1000);
                Application->ProcessMessages();
                IdTelnetDemo->SendCh('\r');
                String SDcard = "test SDRAM";
                SendCommand(SDcard);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
               // Memo1->Lines->Add("Pakedge-PDU$ test SDRAM");
               // Memo1->Lines->Add("");
               // IdTelnetDemo->SendCh('\n');
               ::Sleep(1000);
                Application->ProcessMessages();
                Memo1Display();

                int num1=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy1=Memo1->Lines->Strings[num1]+Memo1->Lines->Strings[num1-1]+Memo1->Lines->Strings[num1-2]+Memo1->Lines->Strings[num1+1];
                char *p1 = yyy1.c_str();
                //Application->MessageBox(yyy1.c_str(),"Show");
                char *cmd1 = "success";
                if(strstr(p1,cmd1) == NULL)
                {
                        Result->Caption = "FAIL";
                        Shape2->Brush->Color = clRed;
                        if(CheckBox89->Checked == true)
                        {
                                updateLogFile("89-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        else if(CheckBox85->Checked == true)
                        {
                                updateLogFile("85-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        Application->MessageBox("SDRAM test Fail,SDRAM is Bad\nRAM¤º¦s¤£¨}","show");
                }
                else
                {
                        TelnetForm->RAM->Enabled = false;
                        Shape2->Brush->Color = clLime;
                        SDRAM1->Text =  test1;
                }
        }

//-------------@jack to add end test the SDRAM test-------------------//

//-------------@jack to add start test the Buzzer test-------------------//
        if(CheckBoxBuzzer->Checked == true)
        {
                Shape3->Brush->Color = clYellow;
                ::Sleep(1000);
                Application->ProcessMessages();
                IdTelnetDemo->SendCh('\r');
                String BuzzerON = "buzzer -v 1";   //BuzzerON
                SendCommand(BuzzerON);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
               // Memo1->Lines->Add("Pakedge-PDU$ buzzer -v 1");
               // Memo1->Lines->Add("");
               // IdTelnetDemo->SendCh('\n');
               ::Sleep(1000);
                Application->ProcessMessages();
                Memo1Display();

                int num2=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy2=Memo1->Lines->Strings[num2]+Memo1->Lines->Strings[num2-1]+Memo1->Lines->Strings[num2-2]+Memo1->Lines->Strings[num2+1];
                char *p2 = yyy2.c_str();
                //Application->MessageBox(yyy2.c_str(),"Show");
                char *cmd2 = "success";
                if(strstr(p2,cmd2) == NULL)
                {
                        Result->Caption = "FAIL";
                        Shape3->Brush->Color = clRed;
                        //updateLogFile("Fail.txt", Memo1->Lines->Text, Result->Caption);
                        if(CheckBox89->Checked == true)
                        {
                                updateLogFile("89-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        else if(CheckBox85->Checked == true)
                        {
                                updateLogFile("85-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        Application->MessageBox("Buzzer test Fail","show");
                }

                ::Sleep(1000);
                Application->ProcessMessages();

                IdTelnetDemo->SendCh('\r');
                String BuzzerOFF = "buzzer -v 0";   //BuzzerOFF
                SendCommand(BuzzerOFF);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
               // Memo1->Lines->Add("Pakedge-PDU$ buzzer -v 0");
               // Memo1->Lines->Add("");
               // IdTelnetDemo->SendCh('\n');
               ::Sleep(1000);
                Application->ProcessMessages();
                Memo1Display();

                int num3=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy3=Memo1->Lines->Strings[num3]+Memo1->Lines->Strings[num3-1]+Memo1->Lines->Strings[num3-2]+Memo1->Lines->Strings[num3+1];
                char *p3 = yyy3.c_str();
                //Application->MessageBox(yyy3.c_str(),"Show");
                char *cmd3 = "success";
                if(strstr(p3,cmd3) == NULL)
                {
                        Result->Caption = "FAIL";
                        Shape3->Brush->Color = clRed;
                        //updateLogFile("Fail.txt", Memo1->Lines->Text, Result->Caption);
                        Application->MessageBox("Buzzer shut test Fail","show");
                        if(CheckBox89->Checked == true)
                        {
                                updateLogFile("89-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        else if(CheckBox85->Checked == true)
                        {
                                updateLogFile("85-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                }

                if (Application->MessageBox("Buzzer is OK?\n¸Á»ï¾¹´ú¸Õ¬O§_OK","Check",MB_OKCANCEL) == IDCANCEL)  //Check the Buzzer is OK again?
                {
                        Result->Caption = "FAIL";
                        Shape3->Brush->Color = clRed;
                        Memo1->Lines->Add("Buzzer is Wrong\n¸Á»ï¾¹¤£¨}");

                        if(CheckBox89->Checked == true)
                        {
                                updateLogFile("89-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        else if(CheckBox85->Checked == true)
                        {
                                updateLogFile("85-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                }
                else
                {
                        TelnetForm->Buzzer->Enabled = false;
                        Shape3->Brush->Color = clLime;
                        Buzzer1->Text = test1;
                }
        }
//-------------@jack to add end test the Buzzer test-----------------------//

//-------------@jack to add start test PingFunction test-------------------//
        if(CheckBoxPing->Checked == true)
        {
                //Application->MessageBox("Ping test\né_Ê¼pingœyÔ‡","show");
                Shape4->Brush->Color = clYellow;
                ::Sleep(1000);
                Application->ProcessMessages();
                IdTelnetDemo->SendCh('\r');
                String ping = PingIP->Text;
                SendCommand(ping);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
               // Memo1->Lines->Add("Pakedge-PDU$ ping -i 192.168.1.111");
              //  Memo1->Lines->Add("");
               // IdTelnetDemo->SendCh('\n');
                Memo1Display();

                int num4=Memo1->Lines->Count;
                ::Sleep(8500);
                Application->ProcessMessages();
                String yyy4=Memo1->Lines->Strings[num4];
                char *p4 = yyy4.c_str();
                //Application->MessageBox(yyy4.c_str(),"Show");
                char *cmd4 = "success";
                if(strstr(p4,cmd4) == NULL)
                {
                        Result->Caption = "FAIL";
                        Shape4->Brush->Color = clRed;
                        if(CheckBox89->Checked == true)
                        {
                                updateLogFile("89-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        else if(CheckBox85->Checked == true)
                        {
                                updateLogFile("85-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        Application->MessageBox("Ping test Fail,Check the PC IP\nPing´ú¸Õ¤£¨},½Ð½T»{IP«á­«·s¶i¦æ´ú¸Õ","show");
                }
                else
                {
                        TelnetForm->Pingt->Enabled = false;
                        Shape4->Brush->Color = clLime;
                        ping1->Text = test1;
                }
        }
//-------------@jack to add end test PingFunction test-------------------//

//-------------@jack to add start test the ShowDeviceInfo test----------------//
        if(CheckBoxDeviceInfo->Checked == true)
        {
             //   Application->MessageBox("Device info test\né_Ê¼×xÈ¡ÔOÅäÐÅÏ¢","show");
                Shape5->Brush->Color = clYellow;
                ::Sleep(1000);
                Application->ProcessMessages();
                IdTelnetDemo->SendCh('\r');
                String ShowDeviceInfo = "show device-info";
                SendCommand(ShowDeviceInfo);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
               // Memo1->Lines->Add("Pakedge-PDU$ show device-info");
               // Memo1->Lines->Add("");
               //IdTelnetDemo->SendCh('\n');
               ::Sleep(1000);
                Application->ProcessMessages();
                Memo1Display();

                int num5=Memo1->Lines->Count;
                ::Sleep(2000);
                Application->ProcessMessages();
                String yyy5=Memo1->Lines->Strings[num5]+Memo1->Lines->Strings[num5-1]+Memo1->Lines->Strings[num5-2]+Memo1->Lines->Strings[num5+1];
                char *p5 = yyy5.c_str();

                String right50 =  yyy5.SubString((yyy5.Pos("firmware_version")+19),28);
                String left50 = right50.SubString(0,(right50.Pos("model")-4));
                FW->Caption = left50;
                char *left501 =left50.c_str();
                if(strcmp(left501,Firmware)!=0)
                {
                      Result->Caption = "Fail";
                      Shape5->Brush->Color = clRed;
                      Application->MessageBox("PDU FW Error!\nFW¤£¤Ç°t,½Ð½T»{°t¸mÀÉ«H®§¬O§_¥¿½T","Error",MB_ICONASTERISK);
                }
                else FW1->Text = left50;
                String right51 =  yyy5.SubString((yyy5.Pos("model")+8),28);
                String left51 = right51.SubString(0,(right51.Pos("serial_number")-4));
                Model->Caption = left51;
          /*    strcpy(&Model_number[0],Model->Caption.c_str());
                String Model_number0 =Model_number[0];
                String Model_number1 = Model_number[1];
                String Model_number2 = Model_number[2];
                String Model_number3 = Model_number[3];
                String Model_number4 = Model_number[4];
                String Model_number5 = Model_number[5];  */
                if(EU->Checked == true)
                {
                      char *left511 =left51.c_str();
                      char *left510 = "PE-08I";
                      if(strcmp(left511,left510)!=0)
                      {
                            Result->Caption = "Fail";
                            Shape5->Brush->Color = clRed;
                            Application->MessageBox("PDU Model Error!\n¾÷«¬¤£¤Ç°t,½Ð½T»{°t¸mÀÉ«H®§¬O§_¥¿½T","Error",MB_ICONASTERISK);
                      }
                      else model1->Text = left51;
                }
                if(US->Checked == true)
                {
                      char *left511 =left51.c_str();
                      char *left510 = "PE-09N";
                      if(strcmp(left511,left510)!=0)
                      {
                            Result->Caption = "Fail";
                            Shape5->Brush->Color = clRed;
                            Application->MessageBox("PDU Model Error!\n¾÷«¬¤£¤Ç°t,½Ð½T»{°t¸mÀÉ«H®§¬O§_¥¿½T","Error",MB_ICONASTERISK);
                      }
                      else model1->Text = left51;
                }

                String right52 =  yyy5.SubString((yyy5.Pos("serial_number")+16),28);
                String left52 = right52.SubString(0,(right52.Pos("MAC")-4));
                //SN->Caption = left52;
                if(CheckBox89->Checked ==true)
                {
                    aSN->Text = left52;
                }
                else  aSN->Text = "";
                String right53 =  yyy5.SubString((yyy5.Pos("MAC")+6),28);
                String left53 = right53.SubString(0,(right53.Pos("hostname")-4));
              //  MAC->Caption = left53;
                if(CheckBox89->Checked ==true)
                {
                    aMAC->Text = left53;
                }
                else  aMAC->Text = "";

                char *cmd5 = "success";
                if(strstr(p5,cmd5) == NULL)
                {
                        Result->Caption = "FAIL";
                        Shape5->Brush->Color = clRed;
                        if(CheckBox89->Checked == true)
                        {
                                updateLogFile("89-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        else if(CheckBox85->Checked == true)
                        {
                                updateLogFile("85-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        Application->MessageBox("Device info test Fail\n³]³Æ«H®§´ú¸Õ¥¢±Ñ","show");
                        TelnetForm->START->Enabled = true;
                        IdTelnetDemo->Disconnect();
                        return;
                }
                else
                {
                        Shape5->Brush->Color = clLime;
                        TelnetForm->InfoFW->Enabled = false;
                }
        }
//-------------@jack to add end test ShowDeviceInfo test-------------------//

//-------------@jack to add start test ShowPDUStatus test-------------------//
        if(CheckBoxPDUStatus->Checked == true)
        {
              //  Application->MessageBox("PDU Status test\nPDU î‘BœyÔ‡","show");
                Shape6->Brush->Color = clYellow;
                ::Sleep(1000);
                Application->ProcessMessages();
                IdTelnetDemo->SendCh('\r');
                String ShowPDUStatus = "show pdu-status";
                SendCommand(ShowPDUStatus);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
               // Memo1->Lines->Add("Pakedge-PDU$ show pdu-status");
               // Memo1->Lines->Add("");
               // IdTelnetDemo->SendCh('\n');
               ::Sleep(1000);
                Application->ProcessMessages();
                Memo1Display();

                int num6=Memo1->Lines->Count;
                ::Sleep(2000);
                Application->ProcessMessages();
                String yyy6=Memo1->Lines->Strings[num6-1]+Memo1->Lines->Strings[num6-2]+Memo1->Lines->Strings[num6]+Memo1->Lines->Strings[num6+1];
                char *p6 = yyy6.c_str();

                String right60 = yyy6.SubString((yyy6.Pos("pdu_voltage")+14),15);
                String left60 = right60.SubString(0,right60.Pos("V")-2);
                String left600 = StrToInt(left60);
                Voltage->Caption = left60+outlet10+left601;
                if(CheckBox89->Checked == true)
                {
                        if(EU->Checked == true)
                        {

                                if(left600>242||left600<218)
                                 {
                                         Result->Caption = "Fail";
                                        Shape6->Brush->Color = clRed;
                                        Application->MessageBox("Voltage is not within the extent!\n¹qÀ£­È¤£¦b½d³ò¤§¤º","Error",MB_ICONASTERISK);
                                }
                                 else  voltage1->Text = left60;
                         }
                         if(US->Checked == true)
                        {
                                if(left600>126||left600<114)
                                {
                                        Result->Caption = "Fail";
                                        Shape6->Brush->Color = clRed;
                                         Application->MessageBox("Voltage is not within the extent!\n¹qÀ£­È¤£¦b½d³ò¤§¤º","Error",MB_ICONASTERISK);
                                }
                                else  voltage1->Text = left60;
                        }
                }
                String right61 = yyy6.SubString((yyy6.Pos("pdu_frequency")+16),15);
                String left61 = right61.SubString(0,(right61.Pos("Hz")+1)-3);
                String left610 = StrToInt(left61);
                Frequency->Caption = left61+outlet10+left602;
                if(CheckBox89->Checked == true)
                {
                        if(EU->Checked == true)
                        {
                                if(left610>=52||left610<=48)
                                {
                                        Result->Caption = "Fail";
                                        Shape6->Brush->Color = clRed;
                                        Application->MessageBox("Frequency is not within the extent!\nÀW²v­È¤£¦b½d³ò¤§¤º","Error",MB_ICONASTERISK);
                                }
                                 else  frequency1->Text = left61;
                        }
                        if(US->Checked == true)
                        {
                                if(left610>=62||left610<=58)
                                {
                                        Result->Caption = "Fail";
                                        Shape6->Brush->Color = clRed;
                                        Application->MessageBox("Frequency is not within the extent!\nÀW²v­È¤£¦b½d³ò¤§¤º","Error",MB_ICONASTERISK);
                                 }
                                else  frequency1->Text = left61;
                        }
                }
                String right62 =  yyy6.SubString((yyy6.Pos("pdu_current")+14),15);
                String left62 = right62.SubString(0,right62.Pos("A"));
                Current->Caption = left62;

               String right63 =  yyy6.SubString((yyy6.Pos("pdu_temp")+11),15);
                String left63 = right63.SubString(0,right63.Pos("\"")-1);
                String left634 = "C";
                String left636 = "F";
                if(EU->Checked == true)
                {
                         String left635 = left63 + outlet10 +left634;
                         Tem->Caption =left635;
                         temp1->Text = left63+left634;
                }
                if(US->Checked == true)
                {
                         String left635 = left63 + outlet10 +left636;
                         Tem->Caption =left635;
                         temp1->Text = left63+left636;
                }

                String right64 =  yyy6.SubString((yyy6.Pos("pdu_humidity")+15),15);
                String left64 = right64.SubString(0,right64.Pos("%")-1);
                String left640 = "%";
                Hum->Caption = left64+outlet10+left640;
                humidity1->Text = left64;

                char *cmd6 = "success";
                if (Application->MessageBox("PDU Status is Right?\nPDUª¬ºA´ú¸Õ¬O§_OK","Check",MB_OKCANCEL) == IDCANCEL)  //Check the PDU Status is Right again?
                {
                        Result->Caption = "FAIL";
                        Shape6->Brush->Color = clRed;
                        Memo1->Lines->Add("PDU Status is Wrong");

                        if(CheckBox89->Checked == true)
                        {
                                updateLogFile("89-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        else if(CheckBox85->Checked == true)
                        {
                                updateLogFile("85-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        TelnetForm->START->Enabled = true;
                }
                else
                {
                        TelnetForm->Infos->Enabled = false;
                        Shape6->Brush->Color = clLime;
                }
}
//-------------@jack to add end test the ShowPDUStatus test----------------//

//-------------------outlet-power set off-------------------------------//
if(CheckBoxOutlet->Checked == true)
{
        IdTelnetDemo->SendCh('\r');

        String set_outlet_1_off = "set outlet-power -o 1 -v 0";
        String set_outlet_2_off = "set outlet-power -o 2 -v 0";
        String set_outlet_3_off = "set outlet-power -o 3 -v 0";
        String set_outlet_4_off = "set outlet-power -o 4 -v 0";
        String set_outlet_5_off = "set outlet-power -o 5 -v 0";
        String set_outlet_6_off = "set outlet-power -o 6 -v 0";
        String set_outlet_7_off = "set outlet-power -o 7 -v 0";
        String set_outlet_8_off = "set outlet-power -o 8 -v 0";
        String set_outlet_9_off = "set outlet-power -o 9 -v 0";

        Application->MessageBox("Observe each LED light is put out status\n½ÐÆ[¹îLED¬O§_³v­Óº¶·À","show");
        Shape7->Brush->Color = clYellow;
        ::Sleep(1000);
        Application->ProcessMessages();
        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
       // Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 1 -v 0");
       // Memo1->Lines->Add("");
       // IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_2_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
       // Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 2 -v 0");
       // Memo1->Lines->Add("");
       // IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_3_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
       // Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 3 -v 0");
       // Memo1->Lines->Add("");
       // IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_4_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 4 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_5_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 5 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_6_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 6 -v 0");
       //Memo1->Lines->Add("");
       // IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_7_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 7 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_8_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 8 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();
        ::Sleep(1000);
        Application->ProcessMessages();
        if(US->Checked == true)
        {
                SendCommand(set_outlet_9_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 9 -v 0");
                //Memo1->Lines->Add("");
                //IdTelnetDemo->SendCh('\n');
                Memo1Display();
        }
        if (Application->MessageBox("Observe each LED light is put out status\n©Ò¦³ªºLED¬O§_³£³B©óº¶·Àª¬ºA","outlet",MB_OKCANCEL) == IDCANCEL)  //Check the PDU Status is Right again?
        {
                        Result->Caption = "FAIL";
                        Shape7->Brush->Color = clRed;
        }
        ::Sleep(2000);
        Application->ProcessMessages();
//--------------------------------------------------------------------------//

//-------------------outlet-power set on-----------------------------------//
        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_on = "set outlet-power -o 1 -v 1";
        String set_outlet_2_on = "set outlet-power -o 2 -v 1";
        String set_outlet_3_on = "set outlet-power -o 3 -v 1";
        String set_outlet_4_on = "set outlet-power -o 4 -v 1";
        String set_outlet_5_on = "set outlet-power -o 5 -v 1";
        String set_outlet_6_on = "set outlet-power -o 6 -v 1";
        String set_outlet_7_on = "set outlet-power -o 7 -v 1";
        String set_outlet_8_on = "set outlet-power -o 8 -v 1";
        String set_outlet_9_on = "set outlet-power -o 9 -v 1";

        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 1 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_2_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 2 -v 1");
       // Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_3_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 3 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_4_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 4 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_5_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 5 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_6_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 6 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_7_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 7 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(set_outlet_8_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 8 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(1000);
        Application->ProcessMessages();
        if(US->Checked == true)
        {
                SendCommand(set_outlet_9_on);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 9 -v 1");
                //Memo1->Lines->Add("");
                //IdTelnetDemo->SendCh('\n');
                Memo1Display();
        }

        if (Application->MessageBox("LEDs are all light up?\nLED¬O§_³£«G°_,¨Ã§PÂ_´ú¸Õ¬O§_OK","outlet",MB_OKCANCEL) == IDCANCEL)  //Check the LEDs are all light up again?
        {
                Result->Caption = "FAIL";
                Shape7->Brush->Color = clRed;
                Memo1->Lines->Add("LEDs are not all light up");

                if(CheckBox89->Checked == true)
                {
                        updateLogFile("89-Fail.txt", Memo1->Lines->Text, Result->Caption);
                }
                else if(CheckBox85->Checked == true)
                {
                        updateLogFile("85-Fail.txt", Memo1->Lines->Text, Result->Caption);
                }
        }
        else
        {
                TelnetForm->Outlett->Enabled = false;
                Shape7->Brush->Color = clLime;
                outlettest1->Text = test1;
        }
}

//----------------@mark add 2016-3-25----------------------------------------------------------//
   if(CheckBoxPowerCycle->Checked == true){
        IdTelnetDemo->SendCh('\r');
        String power_cycle_1_on = "power-cycle -o 1";
        String power_cycle_2_on = "power-cycle -o 2";
        String power_cycle_3_on = "power-cycle -o 3";
        String power_cycle_4_on = "power-cycle -o 4";
        String power_cycle_5_on = "power-cycle -o 5";
        String power_cycle_6_on = "power-cycle -o 6";
        String power_cycle_7_on = "power-cycle -o 7";
        String power_cycle_8_on = "power-cycle -o 8";
        String power_cycle_9_on = "power-cycle -o 9";

        Application->MessageBox("check each LED light up after put out\n½T»{¨C­ÓLED¬O§_¦bº¶·À«á«G°_","show");
        Shape8->Brush->Color = clYellow;
        ::Sleep(1000);
        Application->ProcessMessages();
        SendCommand(power_cycle_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

      /*  int num20=Memo1->Lines->Count;
        ::Sleep(1000);
         Application->ProcessMessages();
         String yyy20=Memo1->Lines->Strings[num20-1];
         char *p20 = yyy20.c_str();
         char *cmd20 = "success";
        if(strstr(p20,cmd20) == NULL)
        {
                Result->Caption = "FAIL";
                Shape8->Brush->Color = clRed;
        }           */

        ::Sleep(1000);
        Application->ProcessMessages();

        SendCommand(power_cycle_2_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 2");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();
        int num20=Memo1->Lines->Count;

        ::Sleep(3000);
        Application->ProcessMessages();

        SendCommand(power_cycle_3_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 3");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(3000);
        Application->ProcessMessages();

        SendCommand(power_cycle_4_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 4");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(3000);
        Application->ProcessMessages();

        SendCommand(power_cycle_5_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 5");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(3000);
        Application->ProcessMessages();

        SendCommand(power_cycle_6_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 6");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(3000);
        Application->ProcessMessages();

        SendCommand(power_cycle_7_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 7");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(3000);
        Application->ProcessMessages();

        SendCommand(power_cycle_8_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 8");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(3000);
        Application->ProcessMessages();
        if(US->Checked == true)
        {
                SendCommand(power_cycle_9_on);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                //Memo1->Lines->Add("Pakedge-PDU$ power-cycle -o 9");
                //Memo1->Lines->Add("");
                //IdTelnetDemo->SendCh('\n');
                Memo1Display();
        }
        char *cmd20 = "success";
       /* if(strstr(p20,cmd20) == NULL)
        {
                Result->Caption = "FAIL";
                Shape8->Brush->Color = clRed;
        }  */
        if (Application->MessageBox("Power Cycle test is ok?\n½Ð½T»{Power Cycle´ú¸Õ¬O§_OK","Check test",MB_OKCANCEL) == IDCANCEL)  //Check the PDU Status is Right again?
        {
                Result->Caption = "FAIL";
                Shape8->Brush->Color = clRed;
                Memo1->Lines->Add("PDU power cycle is Wrong");

                if(CheckBox89->Checked == true)
                {
                       updateLogFile("89-Fail.txt", Memo1->Lines->Text, Result->Caption);
                }
                else if(CheckBox85->Checked == true)
                {
                       updateLogFile("85-Fail.txt", Memo1->Lines->Text, Result->Caption);
                }
         }
         else
         {
                TelnetForm->PowerC->Enabled = false;
                Shape8->Brush->Color = clLime;
                powercycle1->Text = test1;
         }
   }

//------------------------------«Ì¹õ¶Â¥Õ«Ì´ú¸Õ------------------------------//
  if(CheckBoxOledFill->Checked == true)
  {
       // Application->MessageBox("Please begin to observe OLED\n","Show");
        Shape9->Brush->Color = clYellow;
        ::Sleep(1000);
        Application->ProcessMessages();
        IdTelnetDemo->SendCh('\r');
        String oled_fill_1 = "test oled-fill 1";
        SendCommand(oled_fill_1);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
     // Memo1->Lines->Add("Pakedge-PDU$ test oled-fill 1");
      //Memo1->Lines->Add("");
      //IdTelnetDemo->SendCh('\n');
        Memo1Display();

       /* int num11=Memo1->Lines->Count;
        ::Sleep(2000);
        Application->ProcessMessages();
        String yyy11=Memo1->Lines->Strings[num11];
        char *p11 = yyy11.c_str();
        Application->MessageBox(yyy11.c_str(),"Show");
        char *cmd11 = "success";
        if(strstr(p11,cmd11) == NULL)
        {
                Result->Caption = "FAIL";
                Shape9->Brush->Color = clRed;
                if(CheckBox89->Checked == true)
                {
                        updateLogFile("89repeattestFAIL.txt", Memo1->Lines->Text, Result->Caption);
                }
                else if(CheckBox85->Checked == true)
                {
                        updateLogFile("85repeattestFAIL.txt", Memo1->Lines->Text, Result->Caption);
                }
                Application->MessageBox("Oled test","show");
        }      */
        if (Application->MessageBox("OLED have not Dark spot and Light spot?\n½Ð½T»{¥Õ«Ì¤W¬O§_¦³«GÂI©Î·tÂI,¦p¬O¤£¨}½ÐÂIÀ»¨ú®ø","Check OLED",MB_OKCANCEL) == IDCANCEL)  //Check the OLED have not Dark spot and Light spot again?
        {
                Result->Caption = "FAIL";
                Shape9->Brush->Color = clRed;
                Memo1->Lines->Add("OLED have Dark spot or Light spot");

                if(CheckBox89->Checked == true)
                {
                        updateLogFile("89repeattestFAIL.txt", Memo1->Lines->Text, Result->Caption);
                }
                 else if(CheckBox85->Checked == true)
                {
                        updateLogFile("85repeattestFAIL.txt", Memo1->Lines->Text, Result->Caption);
                }
        }

        ::Sleep(2000);
        Application->ProcessMessages();
        IdTelnetDemo->SendCh('\r');
        String oled_fill_0 = "test oled-fill 0";   //¶Â«Ì´ú¸Õ
        SendCommand(oled_fill_0);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
     // Memo1->Lines->Add("Pakedge-PDU$ test oled-fill 0");
     // Memo1->Lines->Add("");
     // IdTelnetDemo->SendCh('\n');
        Memo1Display();

        int num12=Memo1->Lines->Count;
        ::Sleep(2000);
        Application->ProcessMessages();
       /* String yyy12=Memo1->Lines->Strings[num12];
        char *p12 = yyy12.c_str();
        Application->MessageBox(yyy12.c_str(),"Show");
        char *cmd12 = "success";
        if(strstr(p12,cmd12) == NULL)
        {
                        Result->Caption = "FAIL";
                        Shape9->Brush->Color = clRed;

        }        */
        if (Application->MessageBox("OLED have not Dark spot and Light spot?\n½Ð½T»{OLED´ú¸Õ¬O§_oK","Check OLED",MB_OKCANCEL) == IDCANCEL)  //Check the OLED have not Dark spot and Light spot again?
        {
                Result->Caption = "FAIL";
                Shape9->Brush->Color = clRed;
                Memo1->Lines->Add("OLED have Dark spot or Light spot");
        }

        else
        {
                 TelnetForm->OLED->Enabled = false;
                Shape9->Brush->Color = clLime;
                OLED1->Text = test1;
        }
  }
//----------------@mark add 2016-4-13 LEDLuminace----------------------------------------------------------//
  if(CheckBoxLEDLuminance->Checked == true){
        IdTelnetDemo->SendCh('\r');
        String LEDLuminace_0_on = "test leddim 0";
        String LEDLuminace_10_on = "test leddim 10";

        Application->MessageBox("please check the LED brightness is changes\n½Ð¶}©lÆ[¹îLED«G«×¬O§_¦³ÅÜ¤Æ","show");
        Shape10->Brush->Color = clYellow;
        ::Sleep(1000);
        Application->ProcessMessages();
        SendCommand(LEDLuminace_0_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ test leddim 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(2000);
        Application->ProcessMessages();

        ::Sleep(2000);
        Application->ProcessMessages();

        ::Sleep(2000);
        Application->ProcessMessages();
        SendCommand(LEDLuminace_10_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ test leddim 10");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(3000);
        Application->ProcessMessages();
        if (Application->MessageBox("LEDLuminance test is ok?\n¦pLED«G«×¨S¦³ÅÜ¤Æ½ÐÂIÀ»¨ú®ø","Check",MB_OKCANCEL) == IDCANCEL)  //Check the PDU Status is Right again?
        {
                Result->Caption = "FAIL";
                Shape10->Brush->Color = clRed;
                Memo1->Lines->Add("LEDLuminance is Wrong");
                if(CheckBox89->Checked == true)
                {
                        updateLogFile("89-Fail.txt", Memo1->Lines->Text, Result->Caption);
                }
                else if(CheckBox85->Checked == true)
                {
                        updateLogFile("85-Fail.txt", Memo1->Lines->Text, Result->Caption);
                }
               // TelnetForm->START->Enabled = true;
        }
        else
        {
                TelnetForm->LED->Enabled = false;
                Shape10->Brush->Color = clLime;
                LED1->Text = test1;
        }

   }
//--------------------------------------------------------------------------//
        if(CheckBoxStaticIP->Checked == true)
        {
                //Application->MessageBox("Set a static IP address to test\né_Ê¼ìo‘BIPœyÔ‡","show");
                Shape11->Brush->Color = clYellow;
                ::Sleep(1000);
                Application->ProcessMessages();
                IdTelnetDemo->SendCh('\r');
                String SetNet = "set net -t static -i 192.168.1.252 -m 255.255.255.0 -g 192.168.1.99 -d 8.8.8.8";
                SendCommand(SetNet);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                //Memo1->Lines->Add("Pakedge-PDU$ set net -t Static -i 192.168.1.252 -m 255.255.255.0 -g 192.168.1.1 -d 8.8.8.8");
                //Memo1->Lines->Add("");
                //IdTelnetDemo->SendCh('\n');
                Memo1Display();

                int num8=Memo1->Lines->Count;
                ::Sleep(6000);
                Application->ProcessMessages();
                String yyy8=Memo1->Lines->Strings[num8];
                char *p8 = yyy8.c_str();
                char *cmd8 = "success";
                if(strstr(p8,cmd8) == NULL)
                {
                        Result->Caption = "FAIL";
                        Shape11->Brush->Color = clRed;
                        if(CheckBox89->Checked == true)
                        {
                                updateLogFile("89-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        else if(CheckBox85->Checked == true)
                        {
                                updateLogFile("85-Fail.txt", Memo1->Lines->Text, Result->Caption);
                        }
                        Application->MessageBox("Set a static IP address to test Fail","show");
                        TelnetForm->START->Enabled = true;
                }
               // else   Shape11->Brush->Color = clLime;
                ::Sleep(1000);
                Application->ProcessMessages();
                //TelnetForm->Button4->Enabled = true;
        }

//-------------------------------------------------------------------------//
      //  Application->MessageBox("Reboot\nÖØ†¢","show");
        String Reboot = "reboot";
        SendCommand(Reboot);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ Reboot");
        //::Sleep(1000);
       // Application->ProcessMessages();
        if(CheckBoxStaticIP->Checked == false)
        {
                TelnetForm->START->Enabled = true;
        }
        
        if(CheckBoxStaticIP->Checked == true)
        {
                ::Sleep(5000);
                Application->ProcessMessages();
                TelnetForm->Button4->Enabled = true;
        }
       if(Result->Caption == "FAIL")
        {
              Result->Caption = "FAIL";
        }
        else
        {
                Result->Caption = "PASS";
                TelnetForm->Button4->Enabled = true;
        }
}
//---------------------------------------------------------------------------
 void __fastcall TTelnetForm::Button4Click(TObject *Sender)
{
        if((CheckBox85->Checked == true && EU->Checked == true && CheckBox89->Checked != true && US->Checked != true)
         ||(CheckBox85->Checked == true && US->Checked == true && CheckBox89->Checked != true && EU->Checked != true)
         ||(CheckBox89->Checked == true && EU->Checked == true && CheckBox85->Checked != true && US->Checked != true)
         ||(CheckBox89->Checked == true && US->Checked == true && CheckBox85->Checked != true && EU->Checked != true))
        {

        }
        else
        {
                //Application->MessageBox("½Ð¤Ä¿ï¬ÛÃö´ú¸Õ¶µ¥Ø","Åã¥Ü");
                Application->MessageBox("Check the config.ini","show");
                return;
        }

        IdTelnetDemo->Disconnect();
        TelnetForm->Button4->Enabled = false;

        //Application->MessageBox("ÀË´ú³]©wªºÀRºAIP¬O§_¦¨¥\­×§ï¬°192.168.1.252","Åã¥Ü");

        String str2,str3;
        IdTelnetDemo->Host = IP->Text;
        str2 = IP->Text;
        IdTelnetDemo->Port = StrToInt(spnedtPort->Text);
        str3 = spnedtPort->Text;

        IdTelnetDemo->Connect();
        Memo1->Clear();
        Application->ProcessMessages();
        ::Sleep(500);
        Application->ProcessMessages();

        Memo1->Lines->Add("");
        int num100=Memo1->Lines->Count;
        ::Sleep(1500);
        Application->ProcessMessages();
        String yyy100=Memo1->Lines->Strings[num100]+Memo1->Lines->Strings[num100-1]+Memo1->Lines->Strings[num100+1];
        char *p100 = yyy100.c_str();
        String login = "pakedge\r";
        char *a = "1ogin as";
        if(strcmp(p100,a)==0){
     //   Memo1->Lines->Add("");
        //String login = "pakedge";
        SendCommand(login);
        }else
        {
             ::Sleep(1000);
             Application->ProcessMessages();
             SendCommand(login);
        }
       /* String login = "pakedge\r";
        SendCommand(login);     */
      //  Memo1->Lines->Add("Pakedge-PDU$ login: pakedge");
     //   Memo1->Lines->Add("");
        Application->ProcessMessages();
        ::Sleep(600);
        Application->ProcessMessages();

        int num210=Memo1->Lines->Count;
        String password = "pakedgep";
        String yyy210=Memo1->Lines->Strings[num210]+Memo1->Lines->Strings[num210-1]+Memo1->Lines->Strings[num210+1];
        char *p210 = yyy210.c_str();
        char *a2 = "password";
        if(strstr(p210,a2) != NULL)
        {
             SendCommand(password);
        }
        else
        {
             ::Sleep(1000);
             Application->ProcessMessages();
             SendCommand(password);
        }
        /*Memo1->Lines->Add("");
        String password = "pakedgep\r";
        SendCommand(password);    */
      //  Memo1->Lines->Add("password: pakedgep");
      //  Memo1->Lines->Add("");
       // IdTelnetDemo->SendCh('\n');
        Application->ProcessMessages();
        ::Sleep(600);
        Application->ProcessMessages();
        Result2->Caption = "Testing";
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
      //  Application->ProcessMessages();
        ::Sleep(3000);
        Application->ProcessMessages();

//-----------------show net--------------------------------------------//
        Application->MessageBox("Test the static IP of the change is normal\n´ú¸ÕÀRºAIP³]¸m¬O§_OK","show");
        IdTelnetDemo->SendCh('\r');
        String ShowNet = "show net";
        SendCommand(ShowNet);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ show net");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        ::Sleep(1000);
        Application->ProcessMessages();
        Memo1Display();

        int num9=Memo1->Lines->Count;
        ::Sleep(1500);
        Application->ProcessMessages();
        String yyy9=Memo1->Lines->Strings[num9]+Memo1->Lines->Strings[num9-1]+Memo1->Lines->Strings[num9-2]+Memo1->Lines->Strings[num9+1];
       //Application->MessageBox(yyy9.c_str(),"Show");
        char *p9 = yyy9.c_str();
        char *cmd9 = "success";
        if(strstr(p9,cmd9) == NULL)
        {
                Result2->Caption = "FAIL";
                if(CheckBox89->Checked == true)
                {
                        updateLogFile("89-Fail.txt", Memo1->Lines->Text, Result->Caption);
                }
                else if(CheckBox85->Checked == true)
                {
                        updateLogFile("85-Fail.txt", Memo1->Lines->Text, Result->Caption);
                }
                Application->MessageBox("Set static IP address function Fail","show");
               // TelnetForm->Button1->Enabled = true;
        }
        else
        {
                Shape11->Brush->Color = clLime;
                TelnetForm->Staticip->Enabled = false;
                staticsip1->Text = test1;
        }

//--------------------------------------------------------------------//

//-------------------Reset function-----------------------------------------//
        Application->MessageBox("Factory Default\n«ì´_¥X¼t³]¸m","show");
        ::Sleep(1000);
        Application->ProcessMessages();
        IdTelnetDemo->SendCh('\r');
        String Reset = "factory-default";
        SendCommand(Reset);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ factory-default");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

//--------------------------------------------------------------------------//
        TelnetForm->START->Enabled = true;
        if(Result2->Caption == "FAIL")
        {
              Result2->Caption = "FAIL";
        }
        else Result2->Caption = "PASS";
        //updateLogFile("Pass.txt", Memo1->Lines->Text, Result2->Caption);
        if(CheckBox89->Checked == true)
        {
                updateLogFile("89-Pass.txt", Memo1->Lines->Text, Result->Caption);
        }
        else if(CheckBox85->Checked == true)
        {
                updateLogFile("85-Pass.txt", Memo1->Lines->Text, Result->Caption);
        }
        if(Result->Caption =="PASS"&&Result2->Caption =="PASS")
        {
               TelnetForm->Button1->Enabled = true;
        }
}
//---------------------------------------------------------------------------

 void __fastcall TTelnetForm::Button2Click(TObject *Sender)
{
        TelnetForm->START->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button3Click(TObject *Sender)
{
        TelnetForm->Button4->Enabled = true;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int  updateLogFile(String LogFile, String Data , String Result)
{
    FILE *fp;
    if ((fp = fopen(LogFile.c_str(), "a+")) == NULL) {
        MessageBox(NULL, "Can not open log.txt file.", "Error", MB_OK);
        fclose(fp);
        return -1;
    }
    char date[9];
    char time[9];

    fprintf(fp, "%s \n", "------------------------New Pdu Test--------------------------\n");
    fprintf(fp,"%s ", _strdate(date));
    fprintf(fp,"%s \n", _strtime(time));
    fprintf(fp, "%s \n", Data.c_str());
    fprintf(fp, "%s \n", "------------------------Test  Result--------------------------\n");
    fprintf(fp, "%s \n\n", Result.c_str());

    fclose(fp);
    return 0;
}

//---------------------------------------------------------------------------
/* int saverepeatPASSLog()
{
      if(CheckBox89->Checked == true)
      {
                updateLogFile("89repeattestPASS.txt", Memo1->Lines->Text, Result->Caption);
      }
      else if(CheckBox85->Checked == true)
      {
                updateLogFile("85repeattestPASS.txt", Memo1->Lines->Text, Result->Caption);
      }
}
//---------------------------------------------------------------------------
int saverepeatFAILLog()
{
      if(CheckBox89->Checked == true)
      {
                updateLogFile("89repeattestPASS.txt", Memo1->Lines->Text, Result->Caption);
      }
      else if(CheckBox85->Checked == true)
      {
                updateLogFile("85repeattestPASS.txt", Memo1->Lines->Text, Result->Caption);
      }
}
//---------------------------------------------------------------------------
int saveTestFAILLog()
{
      if(CheckBox89->Checked == true)
      {
                updateLogFile("89-Fail.txt", Memo1->Lines->Text, Result->Caption);
      }
      else if(CheckBox85->Checked == true)
      {
                updateLogFile("85-Fail.txt", Memo1->Lines->Text, Result->Caption);
      }
}
//---------------------------------------------------------------------------
int saveTestPASSLog()
{
      if(CheckBox89->Checked == true)
        {
                updateLogFile("89-Pass.txt", Memo1->Lines->Text, Result->Caption);
        }
        else if(CheckBox85->Checked == true)
        {
                updateLogFile("85-Pass.txt", Memo1->Lines->Text, Result->Caption);
        }
}       */
//---------------------------------------------------------------------------


void Open_File()
{
        String filepath;
        TCHAR   currentpath[200];
        char PE_08I[2];
        char PE_09N[2];
        char PDU_89[2];
        char PDU_85[2];
        char SDCard[2];
        char SDRAM[2];
        char Buzzer[2];
        char Ping[2];
        char DeviceInfo[2];
        char PDUStatus[2];
        char OutletPower[2];
        char PowerCycle[2];
        char OledFill[2];
        char LEDLuminance[2];
        char StaticIP[2];

        GetCurrentDirectory(255,currentpath);
        filepath=String(currentpath);
        filepath +="\\config.ini";

        memset(Serveradder,0,24);
        GetPrivateProfileString("PDU-TEST","Serveradder"," ",Serveradder,24,filepath.c_str());

        memset(Station,0,8);
        GetPrivateProfileString("PDU-TEST","Station"," ",Station,8,filepath.c_str());

        memset(EMP,0,8);
        GetPrivateProfileString("PDU-TEST","EMP"," ",EMP,8,filepath.c_str());

        memset(Firmware,0,7);
        GetPrivateProfileString("PDU-TEST","Firmware"," ",Firmware,7,filepath.c_str());
        memset(PE_08I,0,2);
        GetPrivateProfileString("PDU-TEST","PE-08I"," ",PE_08I,2,filepath.c_str());        PE_08I_test = atoi(PE_08I);        memset(PE_09N,0,2);        GetPrivateProfileString("PDU-TEST","PE-09N"," ",PE_09N,2,filepath.c_str());        PE_09N_test = atoi(PE_09N);        memset(PDU_89,0,2);
        GetPrivateProfileString("PDU-TEST","PDU-89"," ",PDU_89,2,filepath.c_str());        PDU_89_test = atoi(PDU_89);        memset(PDU_85,0,2);
        GetPrivateProfileString("PDU-TEST","PDU-85"," ",PDU_85,2,filepath.c_str());        PDU_85_test = atoi(PDU_85);        memset(SDCard,0,2);        GetPrivateProfileString("PDU-TEST","SDCard"," ",SDCard,2,filepath.c_str());        SDCard_test = atoi(SDCard);        memset(SDRAM,0,2);        GetPrivateProfileString("PDU-TEST","SDRAM"," ",SDRAM,2,filepath.c_str());        SDRAM_test = atoi(SDRAM);        memset(Buzzer,0,2);        GetPrivateProfileString("PDU-TEST","Buzzer"," ",Buzzer,2,filepath.c_str());        Buzzer_test = atoi(Buzzer);        memset(Ping,0,2);
        GetPrivateProfileString("PDU-TEST","Ping"," ",Ping,2,filepath.c_str());        Ping_test = atoi(Ping);        memset(DeviceInfo,0,2);        GetPrivateProfileString("PDU-TEST","DeviceInfo"," ",DeviceInfo,2,filepath.c_str());        DeviceInfo_test = atoi(DeviceInfo);        memset(PDUStatus,0,2);        GetPrivateProfileString("PDU-TEST","PDUStatus"," ",PDUStatus,2,filepath.c_str());        PDUStatus_test = atoi(PDUStatus);        memset(OutletPower,0,2);        GetPrivateProfileString("PDU-TEST","OutletPower"," ",OutletPower,2,filepath.c_str());        OutletPower_test = atoi(OutletPower);        memset(PowerCycle,0,2);        GetPrivateProfileString("PDU-TEST","PowerCycle"," ",PowerCycle,2,filepath.c_str());        PowerCycle_test = atoi(PowerCycle);        memset(OledFill,0,2);        GetPrivateProfileString("PDU-TEST","OledFill"," ",OledFill,2,filepath.c_str());        OledFill_test = atoi(OledFill);        memset(LEDLuminance,0,2);        GetPrivateProfileString("PDU-TEST","LEDLuminance"," ",LEDLuminance,2,filepath.c_str());        LEDLuminance_test = atoi(LEDLuminance);                                                                  memset(StaticIP,0,2);        GetPrivateProfileString("PDU-TEST","StaticIP"," ",StaticIP,2,filepath.c_str());        StaticIP_test = atoi(StaticIP);
}
//---------------------------------------------------------------------------



void __fastcall TTelnetForm::ConnectClick(TObject *Sender)
{
        Result2->Caption = "";
        Result2->Caption = "";
        TelnetForm->START->Enabled = false;

        String str,str1;
        IdTelnetDemo->Host = edtServer->Text;
        str = edtServer->Text;
        IdTelnetDemo->Port = StrToInt(spnedtPort->Text);
        str1 = spnedtPort->Text;
        IdTelnetDemo->Connect();
        Memo1->Clear();



        Current->Caption = "";
        Frequency->Caption = "";
        FW->Caption = "";
        Model->Caption = "";
        Voltage->Caption = "";
        Result->Caption = "";
        Tem->Caption = "";
        Hum->Caption = "";

         Memo1->Clear();
        Application->ProcessMessages();
        ::Sleep(600);
        Application->ProcessMessages();

        Memo1->Lines->Add("");
        int num100=Memo1->Lines->Count;
        ::Sleep(1500);
        Application->ProcessMessages();
        String yyy100=Memo1->Lines->Strings[num100]+Memo1->Lines->Strings[num100-1]+Memo1->Lines->Strings[num100+1];
        char *p100 = yyy100.c_str();
        String login = "pakedge\r";
        char *a = "1ogin as";
        if(strcmp(p100,a)==0){
     //   Memo1->Lines->Add("");
        //String login = "pakedge";
        SendCommand(login);
        }else
        {
             ::Sleep(1000);
             Application->ProcessMessages();
             SendCommand(login);
        }
       /* String login = "pakedge\r";
        SendCommand(login);     */
     //   Memo1->Lines->Add("Pakedge-PDU$ login: pakedge");
        Application->ProcessMessages();
        ::Sleep(1000);
        Application->ProcessMessages();

        int num210=Memo1->Lines->Count;
        String password = "pakedgep\r";
        String yyy210=Memo1->Lines->Strings[num210]+Memo1->Lines->Strings[num210-1]+Memo1->Lines->Strings[num210+1];
        char *p210 = yyy210.c_str();
        char *a2 = "password";
        if(strstr(p210,a2) != NULL)
        {
             SendCommand(password);
        }
        else
        {
             ::Sleep(1000);
             Application->ProcessMessages();
             SendCommand(password);
        }
      //  Memo1->Lines->Add("password: pakedgep");
      //  Memo1->Lines->Add("");
       // IdTelnetDemo->SendCh('\n');
        Application->ProcessMessages();
        ::Sleep(600);
        Application->ProcessMessages();

}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button1Click(TObject *Sender)
{
      //  Application->MessageBox("","show");
        TIdHTTP *IdHttp1;
        try{
                IdHttp1=new TIdHTTP(Application);
                TStringList  *Source=new  TStringList();
                TStringStream  *stream=new  TStringStream("");
                IdHttp1->Request->ContentType="application/x-www-form-urlencoded;charset=UTF-8";
                //     Source->Add("testetss");
                if(IdHttp1==NULL)
                {
                        return;
                }
                String str = "";
                String FUNCTION_TEST = "FUNCTION_TEST";
                String PCBA_TEST = "PCBA_TEST";
               String serveraddress = URL->Text.c_str();
            //    Application->MessageBox(serveraddress.c_str(),"show");
                String SERIAL_NUMBER = PCBASN->Text.c_str();
             //   Application->MessageBox(PCBASN->Text.c_str(),"show");
               // String STATION_NUMBER = Station1->Text.c_str();
               String STATION_NUMBER = Station;
              //  Application->MessageBox(STATION_NUMBER.c_str(),"show");
              //  Application->MessageBox(Station1->Text.c_str(),"show");
                String EMP = EMP1->Text.c_str();
              //  Application->MessageBox(EMP1->Text.c_str(),"show");
                String SDCard2 = SDCard1->Text.c_str();
             //   Application->MessageBox(SDCard1->Text.c_str(),"show");
                String SDRAM2 = SDRAM1->Text.c_str();
              //  Application->MessageBox(SDRAM1->Text.c_str(),"show");
                String Buzzer2 = Buzzer1->Text.c_str();
              //  Application->MessageBox(Buzzer1->Text.c_str(),"show");
                String ping2 = ping1->Text.c_str();
              //  Application->MessageBox(ping1->Text.c_str(),"show");
                String FW2 = FW1->Text.c_str();
              //  Application->MessageBox(FW1->Text.c_str(),"show");
                String model2 = model1->Text.c_str();
                //Application->MessageBox(model1->Text.c_str(),"show");
                String aSN2 = aSN->Text.c_str();
               // Application->MessageBox(aSN->Text.c_str(),"show");
                String aMAC2 = aMAC->Text.c_str();
               // Application->MessageBox(aMAC->Text.c_str(),"show");
               String voltage2 = voltage1->Text.c_str();
                    // Application->MessageBox(voltage1->Text.c_str(),"show");
               String frequency2 = frequency1->Text.c_str();
                    //  Application->MessageBox(frequency1->Text.c_str(),"show");           
                String temp2 = temp1->Text.c_str();
               // Application->MessageBox(temp1->Text.c_str(),"show");
                String humidity2 = humidity1->Text.c_str();
               // Application->MessageBox(humidity1->Text.c_str(),"show");
                String outlettest2 = outlettest1-> Text.c_str();
              //  Application->MessageBox(outlettest1-> Text.c_str(),"show");
                String powercycle2 =  powercycle1-> Text.c_str();
               // Application->MessageBox(powercycle1-> Text.c_str(),"show");
                String OLED2 = OLED1->Text.c_str();
               // Application->MessageBox(OLED1->Text.c_str(),"show");
                String LED2 = LED1->Text.c_str();
               // Application->MessageBox(LED1->Text.c_str(),"show");
                String staticsip2 = staticsip1->Text.c_str();
                //Application->MessageBox(staticsip1->Text.c_str(),"show");

                char *f = "";
                char *f1 = URL->Text.c_str();
                char *f2 = PCBASN->Text.c_str();
                char *f3 = Station1->Text.c_str();
                char *f4 = EMP1->Text.c_str();
                char *f5 = SDCard1->Text.c_str();
                char *f6 = SDRAM1->Text.c_str();
                char *f7 = Buzzer1->Text.c_str();
                char *f8 = ping1->Text.c_str();
                char *f9 = FW1->Text.c_str();
                char *f10 = model1->Text.c_str();
                char *f11 = voltage1->Text.c_str();
                char *f12 = frequency1->Text.c_str();
                char *f13 = temp1->Text.c_str();
                char *f14 = humidity1->Text.c_str();
                char *f15 = outlettest1-> Text.c_str();
                char *f16 = powercycle1-> Text.c_str();
                char *f17 = OLED1->Text.c_str();
                char *f18 = LED1->Text.c_str();
                char *f19 = staticsip1->Text.c_str();
                char *f20 = aSN->Text.c_str();
                char *f21 = aMAC->Text.c_str();
              //  char *f20 = "";
             //   char *f21 = "";
             //   Application->MessageBox(aSN->Text.c_str(),"show");
             //   Application->MessageBox(aMAC->Text.c_str(),"show");
                AnsiString Url=serveraddress+":8080/or2mac/pdu/log_info";
               // Application->MessageBox(Url.c_str(),"show");
               if(strcmp(f,f20)==0&&strcmp(f,f21)==0&&strcmp(f,f1)!=0&&strcmp(f,f2)!=0&&strcmp(f,f3)!=0&&strcmp(f,f4)!=0&&strcmp(f,f6)!=0
                   &&strcmp(f,f7)!=0&&strcmp(f,f8)!=0&&strcmp(f,f9)!=0&&strcmp(f,f10)!=0
                   &&strcmp(f,f13)!=0&&strcmp(f,f14)!=0&&strcmp(f,f17)!=0&&strcmp(f,f18)!=0&&strcmp(f,f19)!=0)
                   {
                     /*  AnsiString Url=serveraddress+":8080/or2mac/log_info_versatile?SERIAL_NUMBER="+SERIAL_NUMBER+
                        "&STATION_NUMBER="+STATION_NUMBER+
                        "&EMP="+EMP+
                        "&INFO=SDRAM;Buzzer;ping;FW;model;voltage;frequency;temp;humidity;OLED;LED;staticsip;&VALUE="+SDRAM2+
                        ";"+Buzzer2+";"+ping2+";"+FW2+";"+model2+";"+voltage2+";"+frequency2+";"+temp2+";"+humidity2+";"+OLED2+";"+LED2+";"+staticsip2+";";
                        Application->MessageBox(Url.c_str(),"show");
                        IdHttp1->Get(Url,stream);        */
                        Source->Add("SERIAL_NUMBER="+SERIAL_NUMBER+"&STATION_NUMBER="+STATION_NUMBER+"&EMP="+EMP+"&INFO=PCBA_TEST;SDRAM;Buzzer;ping;FW;model;temp;humidity;OLED;LED;staticsip;"+
                        "&VALUE="+PCBA_TEST+";"+SDRAM2+";"+Buzzer2+";"+ping2+";"+FW2+";"+model2+";"+temp2+";"+humidity2+";"+OLED2+";"+LED2+";"+staticsip2+";");
                        IdHttp1->Post(Url,Source,stream);
                        stream->Position = 0;
                        String result = stream->DataString;
                       // Application->MessageBox(result.c_str(),"show");
                        char *retur1n = "log_info_ok";
                        char *result1 =result.c_str();
                        if(strcmp(result1,retur1n)!=0)
                        {
                                Application->MessageBox(result.c_str(),"show");
                                TelnetForm->Button1->Enabled = true;
                        }
                        else
                        {
                                PCBASN->Text = "";
                                TelnetForm->Button1->Enabled = false;
                                Application->MessageBox("85log Upload PASS","show");
                        }
               // else  Application->MessageBox("logÉÏ‚÷Ê§”¡","show");
               // Application->MessageBox(result.c_str(),"show");
                // strmsg = ss->DataString.Trim();
                }
                if(strcmp(f,f20)!=0&&strcmp(f,f21)!=0&&strcmp(f,f1)!=0&&strcmp(f,f2)!=0&&strcmp(f,f3)!=0&&strcmp(f,f4)!=0&&strcmp(f,f5)!=0&&strcmp(f,f6)!=0
                   &&strcmp(f,f7)!=0&&strcmp(f,f8)!=0&&strcmp(f,f9)!=0&&strcmp(f,f10)!=0&&strcmp(f,f11)!=0&&strcmp(f,f12)!=0
                   &&strcmp(f,f13)!=0&&strcmp(f,f14)!=0&&strcmp(f,f17)!=0&&strcmp(f,f18)!=0&&strcmp(f,f19)!=0)
                   {
                         Source->Add("SERIAL_NUMBER="+SERIAL_NUMBER+"&STATION_NUMBER="+STATION_NUMBER+"&EMP="+EMP+"&INFO=FUNCTION_TEST;SDCARD;SDRAM;Buzzer;ping;FW;model;MAC;SN;voltage;frequency;temp;humidity;outlettest;powercycle;OLED;LED;staticsip;"+
                        "&VALUE="+FUNCTION_TEST+";"+SDCard2+";"+SDRAM2+";"+Buzzer2+";"+ping2+";"+FW2+";"+model2+";"+aMAC2+";"+aSN2+";"+voltage2+";"+frequency2+";"+temp2+";"+humidity2+";"+outlettest2+";"+powercycle2+";"+OLED2+";"+LED2+";"+staticsip2+";");
                        IdHttp1->Post(Url,Source,stream);
                        stream->Position = 0;
                        String result = stream->DataString;
                      //  Application->MessageBox(result.c_str(),"show");
                        char *retur1n = "log_info_ok";
                        char *result1 =result.c_str();
                        if(strcmp(result1,retur1n)!=0)
                        {
                                Application->MessageBox(result.c_str(),"show");
                                TelnetForm->Button1->Enabled = true;
                        }
                        else
                        {
                                PCBASN->Text ="";
                                Application->MessageBox("89log Upload PASS","show");
                                TelnetForm->Button1->Enabled = false;
                        }
                   }
               // else  Application->MessageBox("logÉÏ‚÷Ê§”¡","show");
               // Application->MessageBox(result.c_str(),"show");
                // strmsg = ss->DataString.Trim();
                delete   IdHttp1;
                delete   stream;
                delete   Source;

             } catch(Exception &e)
                {
                        if(IdHttp1!=NULL)
                        delete IdHttp1;
                }



}
//---------------------------------------------------------------------------


void __fastcall TTelnetForm::Button17Click(TObject *Sender)
{
         TelnetForm->Button4->Enabled = false;
        IdTelnetDemo->Disconnect();
}
//---------------------------------------------------------------------------



