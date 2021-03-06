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
char Station[8];
char EMP[8];
char Serveradder[23];
char Firmware[7];
char Model_number[6];
int InputCurrent1 = 1;
int InputCurrent5 = 5;
int InputCurrent10 = 10;
int InputCurrent15 = 15;
int j=0;
int i=0;
float I=0;
float V=0;
float P=0;
float a=0;
float b=0;
float n=0;
float m=0;
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
char *val = "";
char *val1 = "1";
char *val2 = "2";
char *val3 = "3";
char *val4 = "4";
char *val5 = "5";
char *val6 = "6";
char *val7 = "7";
char *val8 = "8";
char *val9 = "9";
String outlet11 = " ";

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
   PingIP->Text = "ping -i 192.168.1.111\r";
   //TelnetForm->Button4->Enabled = true;
   TelnetForm->Button30->Enabled = false;
   TelnetForm->Button4->Enabled = false;
   Open_File();

   URL->Text = Serveradder;
  // Station1->Text = Station;
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
   if(PE_08I_test == 1)
   {
        EU->Checked = true;
        CheckBox1->Checked = true;
        CheckBox2->Checked = true;
        CheckBox3->Checked = true;
        CheckBox7->Checked = true;
        CheckBox8->Checked = true;
   }
   if(PE_09N_test == 1)
   {
        US->Checked = true;
        CheckBox4->Checked = true;
        CheckBox5->Checked = true;
        CheckBox6->Checked = true;
        CheckBox9->Checked = true;
        CheckBox10->Checked = true;
        CheckBox11->Checked = true;
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

bool ifu_rs232_open()
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

        if (TelnetForm->RadioCOM1->Checked )
        {  PortID = "Com1";  }
        if (TelnetForm->RadioCOM2->Checked )
        {  PortID = "Com2";  }

        if (!BuildCommDCB("19200, n, 8, 1", &dcb))                  //(!BuildCommDCB("38400, n, 8, 1", &dcb))
        {
                sprintf(TxdBuffer, "Unable to BUild CommDCB\n");
                w_result = false;
        }

        COM1=CreateFile(PortID.c_str(),
                     GENERIC_READ | GENERIC_WRITE,
                     0,
                     0,
                     OPEN_EXISTING,
                     FILE_ATTRIBUTE_NORMAL,
                     0);

        if (!SetCommState(COM1, &dcb))
        {
                strcat(TxdBuffer, "Unable to initial serial Port\n");
                w_result = false;
        }

        if (!SetupComm(COM1, 512, 512))
        {
                strcat(TxdBuffer, "Unable to Setup serial port Buffer\n");
                w_result = false;
        }

        if (!SetCommTimeouts(COM1, &TimeOut))
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

int get_login_prompt(int flag, char *pattern)
{
        char sz_cmd[] = {0x2A,0x49,0x44,0x4E,0x3F,0x0A, '\r'};//{0x1B,'\r'};//0x2A 0x49 0x44 0x4E 0x3F 0x0A, '\r'};

        while (timeout)
        {
                if (flag == 1)
                WriteFile(COM1, sz_cmd, 7, &dw_Write, 0);
                ReadFile(COM1, &RxdBuffer, 1024, &dw_Read, NULL);
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

void SetBootLoaderIPAddress()
{
        IPStr[strlen(IPStr)-1] = IPStr[strlen(IPStr)-1] + 1;

        sprintf(TxdBuffer, "ipconfig %s\r", IPStr);
        WriteFile(COM1, TxdBuffer, strlen(TxdBuffer), &dw_Write, 0);
        ::Sleep(2000);
}

int GetPCNetWorkAddress()
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
         Label15->Caption = "MODE ERROR";
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
    /*    //打開com port 選擇机型的command為*IDN?
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

        //選擇模式的command為MODECURR
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

void __fastcall TTelnetForm::Button9Click(TObject *Sender)
{
        //打開com port 選擇机型的command為*IDN?
        char Ver_cmd[] = {0x2A,0x49,0x44,0x4E,0x3F,0x0A, '\r'};//{0x1B,'\r'};//0x2A 0x49 0x44 0x4E 0x3F 0x0A, '\r'};
        int timeout = 1;
    //    int flag = 1;

        // Label1->Caption = "";

        if (!ifu_rs232_open())
        {
                sprintf(MsgBuffer, "failed to open COM port for DUT");
                strcat(TxdBuffer, MsgBuffer);
                Application->MessageBox(TxdBuffer, "Error");
                //goto EXIT;
        }
        Timer1->Interval = 0;
        memset(RxdBuffer, NULL, sizeof(RxdBuffer));

        WriteFile(COM1, Ver_cmd, 8, &dw_Write, 0);
        ReadFile(COM1, &RxdBuffer, 1024, &dw_Read, NULL);
        if (dw_Read)
        {
                //Form1->Memo1->Lines->Add(RxdBuffer);
                Label16->Caption = RxdBuffer;
                Label17->Caption = "Com port open successful";
        }
        else Label17->Caption = "Com port error!";
        ::Sleep(2000);

        //CloseHandle(COM1);
        //選擇模式的command為MODECURR
        char mode_cmd[] = {0x4D,0x4F,0x44,0x45,0x43,0x55,0x52,0x52,0x0A,'\r'};
        WriteFile(COM1, mode_cmd, 10, &dw_Write, 0);
        ::Sleep(1000);

//EXIT:
  //  Timer1->Enabled = False;
    //StartCmd->Enabled = True;
    //RadioCOM1->Enabled = True;
    //RadioCOM2->Enabled = True;
    //CloseHandle(COM1);
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
       // Application->MessageBox(Buffer.c_str(),"show");
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
//----------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button6Click(TObject *Sender)
{
        TelnetForm->Button4->Enabled = false;
        IdTelnetDemo->Disconnect();
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button4Click(TObject *Sender)
{
        if((EU->Checked == true && US->Checked != true)
         ||(US->Checked == true && EU->Checked != true))
        {

        }
        else
        {
                Application->MessageBox("Check the config.ini！！","show");
                return;
        }
       //  TelnetForm->Button30->Enabled = true;
        Edit1->Text = "";
        Edit2->Text = "";
        Edit3->Text = "";
        Edit4->Text = "";
        Edit5->Text = "";
        Edit6->Text = "";
        Edit7->Text = "";
        Edit8->Text = "";
        Edit9->Text = "";

        Edit10->Text = "";
        Edit11->Text = "";
        Edit12->Text = "";
        Edit13->Text = "";
        Edit14->Text = "";
        Edit15->Text = "";
        Edit16->Text = "";
        Edit17->Text = "";
        Edit18->Text = "";

        Edit19->Text = "";
        Edit20->Text = "";
        Edit21->Text = "";
        Edit22->Text = "";
        Edit23->Text = "";
        Edit24->Text = "";
        Edit25->Text = "";
        Edit26->Text = "";
        Edit27->Text = "";

        Edit28->Text = "";
        Edit29->Text = "";
        Edit30->Text = "";
        Edit31->Text = "";

        Edit32->Text = "";
        Edit33->Text = "";
        Edit34->Text = "";
        Edit35->Text = "";
        Edit36->Text = "";
        Edit37->Text = "";
        Edit38->Text = "";
        Edit39->Text = "";
        Edit40->Text = "";

        Edit41->Text = "";
        Edit42->Text = "";
        Edit43->Text = "";
        Edit44->Text = "";
        Edit45->Text = "";
        Edit46->Text = "";
        Edit47->Text = "";
        Edit48->Text = "";
        Edit49->Text = "";

        Edit50->Text = "";
        Edit51->Text = "";
        Edit52->Text = "";
        Edit53->Text = "";
        Edit54->Text = "";
        Edit55->Text = "";
        Edit56->Text = "";
        Edit57->Text = "";
        Edit58->Text = "";

        Edit61->Text = "";
        Edit62->Text = "";
        Edit63->Text = "";
        Edit64->Text = "";
        Edit65->Text = "";
        Edit66->Text = "";
        Edit67->Text = "";
        Edit68->Text = "";
        Edit69->Text = "";

        Edit71->Text = "";
        Edit72->Text = "";
        Edit73->Text = "";
        Edit74->Text = "";
        Edit75->Text = "";
        Edit76->Text = "";
        Edit77->Text = "";
        Edit78->Text = "";
        Edit79->Text = "";

        Edit81->Text = "";
        Edit82->Text = "";
        Edit83->Text = "";
        Edit84->Text = "";
        Edit85->Text = "";
        Edit86->Text = "";
        Edit87->Text = "";
        Edit88->Text = "";
        Edit89->Text = "";

        Edit91->Text = "";
        Edit92->Text = "";
        Edit93->Text = "";
        Edit94->Text = "";
        Edit95->Text = "";
        Edit96->Text = "";
        Edit97->Text = "";
        Edit98->Text = "";
        Edit99->Text = "";

        Edit101->Text = "";
        Edit102->Text = "";
        Edit103->Text = "";
        Edit104->Text = "";
        Edit105->Text = "";
        Edit106->Text = "";
        Edit107->Text = "";
        Edit108->Text = "";
        Edit109->Text = "";

        Edit111->Text = "";
        Edit112->Text = "";
        Edit113->Text = "";
        Edit114->Text = "";
        Edit115->Text = "";
        Edit116->Text = "";
        Edit117->Text = "";
        Edit118->Text = "";
        Edit119->Text = "";

        z11->Caption = "";
        z12->Caption = "";
        z13->Caption = "";
        z14->Caption = "";
        z15->Caption = "";
        z16->Caption = "";
        z17->Caption = "";
        z18->Caption = "";
        z19->Caption = "";

        z21->Caption = "";
        z22->Caption = "";
        z23->Caption = "";
        z24->Caption = "";
        z25->Caption = "";
        z26->Caption = "";
        z27->Caption = "";
        z28->Caption = "";
        z29->Caption = "";

        z31->Caption = "";
        z32->Caption = "";
        z33->Caption = "";
        z34->Caption = "";
        z35->Caption = "";
        z36->Caption = "";
        z37->Caption = "";
        z38->Caption = "";
        z39->Caption = "";

        z41->Caption = "";
        z42->Caption = "";
        z43->Caption = "";
        z44->Caption = "";
        z45->Caption = "";
        z46->Caption = "";
        z47->Caption = "";
        z48->Caption = "";
        z49->Caption = "";

        z51->Caption = "";
        z52->Caption = "";
        z53->Caption = "";
        z54->Caption = "";
        z55->Caption = "";
        z56->Caption = "";
        z57->Caption = "";
        z58->Caption = "";
        z59->Caption = "";

        z61->Caption = "";
        z62->Caption = "";
        z63->Caption = "";
        z64->Caption = "";
        z65->Caption = "";
        z66->Caption = "";
        z67->Caption = "";
        z68->Caption = "";
        z69->Caption = "";

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
        Shape12->Brush->Color = clWhite;
        Shape13->Brush->Color = clWhite;
        Shape14->Brush->Color = clWhite;
        Shape15->Brush->Color = clWhite;
        Shape16->Brush->Color = clWhite;
        Shape17->Brush->Color = clWhite;


        String str,str1;
        IdTelnetDemo->Host = edtServer->Text;
        str = edtServer->Text;
        IdTelnetDemo->Port = StrToInt(spnedtPort->Text);
        str1 = spnedtPort->Text;
      //  IdTelnetDemo->Connect();
        Result3->Caption = "";
        Result20->Caption = "";

        Current->Caption = "";
        Frequency->Caption = "";
        Voltage->Caption = "";
        Power->Caption = "";

        //Memo1->Clear();
        Application->ProcessMessages();
        ::Sleep(500);
        Application->ProcessMessages();

      /*  String login = "pakedge\r";
        SendCommand(login);
        Memo1->Lines->Add("Pakedge-PDU$ login: pakedge");
        Memo1->Lines->Add("");
        Application->ProcessMessages();
        ::Sleep(500);
        Application->ProcessMessages();

        String password = "pakedgep\r";
        SendCommand(password);
        Memo1->Lines->Add("password: pakedgep");
        Memo1->Lines->Add("");        */
        IdTelnetDemo->SendCh('\n');
        Application->ProcessMessages();
        ::Sleep(500);
        Application->ProcessMessages();
        IdTelnetDemo->SendCh('\r');
        String ShowDeviceInfo = "show device-info";
        SendCommand(ShowDeviceInfo);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ show device-info");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        ::Sleep(1000);
        Application->ProcessMessages();
        Memo1Display();

        int num5=Memo1->Lines->Count;
        ::Sleep(2000);
        Application->ProcessMessages();
        String yyy5=Memo1->Lines->Strings[num5]+Memo1->Lines->Strings[num5-1]+Memo1->Lines->Strings[num5-2]+Memo1->Lines->Strings[num5+1];
        char *p5 = yyy5.c_str();
      //  Application->MessageBox(yyy5.c_str(),"show");
        String right50 =  yyy5.SubString((yyy5.Pos("firmware_version")+19),28);
        String left50 = right50.SubString(0,(right50.Pos("model")-4));
      /*  char *a100 =left50.c_str();
        if(strcmp(a100,val)==0)
        {
                ::Sleep(500);
                Application->ProcessMessages();
                yyy5=Memo1->Lines->Strings[num5-1];
                right50 = yyy5.SubString(yyy5.Pos("power")+8,10);
                left50 = right50.SubString(0,right50.Pos("W")-2);
                a100 =left50.c_str();
                FW->Caption = left50;
                Application->MessageBox(left50.c_str(),"show");
        }    */
        FW->Caption = left50;
        char *left501 =left50.c_str();
        if(strcmp(left501,Firmware)!=0)
        {
                Result3->Caption = "FAIL";
                Application->MessageBox("PDU FW Error!\nFW版本不匹配，請確認配置檔","Error",MB_ICONASTERISK);

        }
        Edit28->Text = left50;


        String right51 =  yyy5.SubString((yyy5.Pos("model")+8),28);
        String left51 = right51.SubString(0,(right51.Pos("serial_number")-4));
        Model->Caption = left51;
        if(EU->Checked == true)
        {
                char *left511 =left51.c_str();
                char *left510 = "PE-08I";
                if(strcmp(left511,left510)!=0)
                {
                        Result3->Caption ="FAIL";
                        Application->MessageBox("PDU Model Error!\n機型不匹配，請確認配置檔","Error",MB_ICONASTERISK);
                      //  IdTelnetDemo->Disconnect();
                      //  return;
                }
        }
        if(US->Checked == true)
        {
                char *left511 =left51.c_str();
                char *left510 = "PE-09N";
                if(strcmp(left511,left510)!=0)
                {
                        Result3->Caption = "FAIL";
                        Application->MessageBox("PDU Model Error!\n機型不匹配，請確認配置檔","Error",MB_ICONASTERISK);
                       // IdTelnetDemo->Disconnect();
                       // return;
                }
        }
        Edit29->Text = left51;
//-------------@jack to add end test ShowDeviceInfo test-------------------//

//-------------@jack to add start test ShowPDUStatus test-------------------//

        IdTelnetDemo->SendCh('\r');
        ::Sleep(1000);
        Application->ProcessMessages();
        String ShowPDUStatus = "show pdu-status";
        SendCommand(ShowPDUStatus);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ show pdu-status");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
         ::Sleep(1000);
        Application->ProcessMessages();
        Memo1Display();

        int num6=Memo1->Lines->Count;
        ::Sleep(2000);
        Application->ProcessMessages();
        String yyy6=Memo1->Lines->Strings[num6]+Memo1->Lines->Strings[num6-1]+Memo1->Lines->Strings[num6-2]+Memo1->Lines->Strings[num6+1];
        char *p6 = yyy6.c_str();
       // Application->MessageBox(yyy6.c_str(),"show");
        String right60 = yyy6.SubString((yyy6.Pos("pdu_voltage")+14),15);
        String left60 = right60.SubString(0,right60.Pos("V")-2);
       // Application->MessageBox(left60.c_str(),"show");
        int left600 = StrToInt(left60);
        Voltage->Caption = left60+outlet11+left601;
        if(EU->Checked == true)
        {

                      if(left600>242||left600<218)
                      {
                           Result3->Caption = "FAIL";
                           Application->MessageBox("Voltage is not within the extent!\n電壓不再範圍內","Error",MB_ICONASTERISK);
                      }
                else  Edit30->Text = left60;
        }
       if(US->Checked == true)
                {
                      if(left600>126||left600<114)
                      {
                           Result3->Caption = "FAIL";
                           Application->MessageBox("Voltage is not within the extent!\n電壓不再範圍內","Error",MB_ICONASTERISK);
                      }
                else  Edit30->Text = left60;
        }

        String right61 = yyy6.SubString((yyy6.Pos("pdu_frequency")+16),15);
        String left61 = right61.SubString(0,(right61.Pos("Hz")+1)-3);
        int left610 = StrToInt(left61);
        Frequency->Caption = left61+outlet11+left602;

        if(EU->Checked == true)
        {
                if(left610>52||left610<48)
                {
                        Result3->Caption = "FAIL";
                        Application->MessageBox("Frequency is not within the extent!\n頻率不在範圍內","Error",MB_ICONASTERISK);
                      //  IdTelnetDemo->Disconnect();
                       // return;
                 }
                 else  Edit31->Text = left61;
        }
        if(US->Checked == true)
        {
                if(left610>62||left610<58)
                {
                        Result3->Caption = "FAIL";
                        Application->MessageBox("Frequency is not within the extent!\n頻率不在範圍內","Error",MB_ICONASTERISK);
                      //  IdTelnetDemo->Disconnect();
                     //   return;
                }
                else  Edit31->Text = left61;
        }


//------------------@jack to add outlet power off--------------------------------

        ::Sleep(1000);
        Application->ProcessMessages();

        for(i=0;i<6;i++)
        {
                if(i==0)
                {
                        if((CheckBox7->Checked == true&&EU->Checked == true)|| (CheckBox4->Checked == true&&US->Checked == true))
                        {
                                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                if(EU->Checked == true)
                                {
                                        I=0.2;
                                        n=I*(1+0.3);
                                        m=I*(1-0.4);
                                        V=left600;
                                        P=V*I;
                                        a=P*(1+0.3);
                                        b=P*(1-0.3);
                                }
                                if(US->Checked == true)
                                {
                                        I=0.2;
                                        n=I*(1+0.3);
                                        m=I*(1-0.4);
                                        V=left600;
                                        P=V*I;
                                        a=P*(1+0.3);
                                        b=P*(1-0.3);
                                }
                        }
                        else i =1;
                }
                 if(i==1)
                {
                        if((CheckBox8->Checked == true&&EU->Checked == true)|| (CheckBox9->Checked == true&&US->Checked == true))
                        {
                                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                if(EU->Checked == true)
                                {
                                        I=0.7;
                                        n=I*(1+0.1);
                                        m=I*(1-0.1);
                                        V=left600;
                                        P=V*I;
                                        a=P*(1+0.08);
                                        b=P*(1-0.08);
                                }
                                if(US->Checked == true)
                                {
                                        I=0.7;
                                        n=I*(1+0.1);
                                        m=I*(1-0.1);
                                        V=left600;
                                        P=V*I;
                                        a=P*(1+0.08);
                                        b=P*(1-0.08);
                                }
                        }
                        else i =2;
                }
                if(i==2)
                {
                        if((CheckBox1->Checked == true&&EU->Checked == true)|| (CheckBox5->Checked == true&&US->Checked == true))
                        {
                                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x2E,0x30,0x0A,'\r'};
                                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                if(EU->Checked == true)
                                {
                                        I=2;
                                        n=I*(1+0.05);
                                        m=I*(1-0.05);
                                        V=left600;
                                        P=V*I;
                                        a=P*(1+0.08);
                                        b=P*(1-0.08);
                                }
                                if(US->Checked == true)
                                {
                                        I=2;
                                        n=I*(1+0.05);
                                        m=I*(1-0.05);
                                        V=left600;
                                        P=V*I;
                                        a=P*(1+0.08);
                                        b=P*(1-0.08);
                                }
                        }
                        else i =3;
                }

                if(i==3)
                {
                        if((CheckBox2->Checked == true&&EU->Checked == true) || (CheckBox6->Checked == true&&US->Checked == true))
                        {
                                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                if(EU->Checked == true)
                                {
                                        I=7.7;
                                        n=I*(1+0.05);
                                        m=I*(1-0.05);
                                        V=left600;
                                        P=V*I;
                                        a=P*(1+0.08);
                                        b=P*(1-0.08);
                                }
                                if(US->Checked == true)
                                {
                                        I=7.7;
                                        n=I*(1+0.05);
                                        m=I*(1-0.05);
                                        V=left600;
                                        P=V*I;
                                        a=P*(1+0.08);
                                        b=P*(1-0.08);
                                }

                        }
                        else i=4;
                }

                if(i==4)
                {
                        if((CheckBox3->Checked == true&&EU->Checked == true) || (CheckBox10->Checked == true&&US->Checked == true))
                        {
                                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x2E,0x30,0x0A,'\r'};
                                WriteFile(COM1, curr1_cmd, 11, &dw_Write, 0);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                if(EU->Checked == true)
                                {
                                        I=10;
                                        n=I*(1+0.05);
                                        m=I*(1-0.05);
                                        V=left600;
                                        P=V*I;
                                        a=P*(1+0.08);
                                        b=P*(1-0.08);
                                }
                                if(US->Checked == true)
                                {
                                        I=10;
                                        n=I*(1+0.05);
                                        m=I*(1-0.05);
                                        V=left600;
                                        P=V*I;
                                        a=P*(1+0.08);
                                        b=P*(1-0.08);
                                }

                        }
                        else i=5;
                }
                if(i==5)
                {
                        if(EU->Checked == true)
                        {
                              IdTelnetDemo->Disconnect();
                              return;
                        }
                        if(CheckBox11->Checked == true&&US->Checked == true)
                        {
                                char eucurr3_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x34,0x2E,0x37,0x0A,'\r'};
                                WriteFile(COM1, eucurr3_cmd, 11, &dw_Write, 0);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                if(US->Checked == true)
                                {
                                        I=14.7;
                                        n=I*(1+0.05);
                                        m=I*(1-0.05);
                                        V=left600;
                                        P=V*I;
                                        a=P*(1+0.08);
                                        b=P*(1-0.08);
                                }

                        }
                        else
                        {
                                IdTelnetDemo->Disconnect();
                                return;
                        }
                }
        String set_outlet_1_off = "set outlet-power -o 1 -v 0";
        String set_outlet_2_off = "set outlet-power -o 2 -v 0";
        String set_outlet_3_off = "set outlet-power -o 3 -v 0";
        String set_outlet_4_off = "set outlet-power -o 4 -v 0";
        String set_outlet_5_off = "set outlet-power -o 5 -v 0";
        String set_outlet_6_off = "set outlet-power -o 6 -v 0";
        String set_outlet_7_off = "set outlet-power -o 7 -v 0";
        String set_outlet_8_off = "set outlet-power -o 8 -v 0";
        String set_outlet_9_off = "set outlet-power -o 9 -v 0";

        String set_outlet_1_on = "set outlet-power -o 1 -v 1";
        String set_outlet_2_on = "set outlet-power -o 2 -v 1";
        String set_outlet_3_on = "set outlet-power -o 3 -v 1";
        String set_outlet_4_on = "set outlet-power -o 4 -v 1";
        String set_outlet_5_on = "set outlet-power -o 5 -v 1";
        String set_outlet_6_on = "set outlet-power -o 6 -v 1";
        String set_outlet_7_on = "set outlet-power -o 7 -v 1";
        String set_outlet_8_on = "set outlet-power -o 8 -v 1";
        String set_outlet_9_on = "set outlet-power -o 9 -v 1";

        String show_outlet_1_status = "show outlet-status -o 1";
        String show_outlet_2_status = "show outlet-status -o 2";
        String show_outlet_3_status = "show outlet-status -o 3";
        String show_outlet_4_status = "show outlet-status -o 4";
        String show_outlet_5_status = "show outlet-status -o 5";
        String show_outlet_6_status = "show outlet-status -o 6";
        String show_outlet_7_status = "show outlet-status -o 7";
        String show_outlet_8_status = "show outlet-status -o 8";
        String show_outlet_9_status = "show outlet-status -o 9";
//----------------------start outlet1 power test---------mark change- 0413-------------------------

        Power->Caption = "";
        Current->Caption = "";
        Result3->Caption = "Testing";
        Result3->Caption = "";


        IdTelnetDemo->SendCh('\r');
        if(EU->Checked == true&&Shape1->Brush->Color != clRed)
        {
                Shape1->Brush->Color = clYellow;
        }
        if(US->Checked == true&&Shape9->Brush->Color != clRed)
        {
                Shape9->Brush->Color = clYellow;
        }
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
       // Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 1 -v 1");
       // Memo1->Lines->Add("");
       // IdTelnetDemo->SendCh('\n');
        Memo1Display();

     /*  ::Sleep(2000);
        Application->ProcessMessages();

        ::Sleep(1000);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(show_outlet_1_status);
        Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 1");
        Memo1->Lines->Add("");
        IdTelnetDemo->SendCh('\n');
        Memo1Display();       */

        for(j=0;j<3;j++)
        {
                if(j==0)
                {//Application->MessageBox("1","show");
                ::Sleep(3000);
                Application->ProcessMessages(); }
                if(j==1)
                {//Application->MessageBox("1","show");
                ::Sleep(2000);
                Application->ProcessMessages(); }
                if(j==2)
                {
                        IdTelnetDemo->SendCh('\r');
                        SendCommand(show_outlet_1_status);
                        ::Sleep(500);
                        Application->ProcessMessages();
                        SendCommand(Enter);
                        //Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 1");
                        //Memo1->Lines->Add("");
                        //IdTelnetDemo->SendCh('\n');
                        ::Sleep(1000);
                        Application->ProcessMessages();
                        Memo1Display();
                }
         }

        int num30=Memo1->Lines->Count;
        ::Sleep(1500);
        Application->ProcessMessages();
        String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
        //Application->MessageBox(yyy30.c_str(),"show");
        String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
        String left300 = right300.SubString(0,right300.Pos("W")-2);
        String left001 = left300+outlet11+left250;
        Power->Caption = left001;
        float left301 = StrToFloat(left300);
        if(i==0)
        {
             if(EU->Checked == true)
             {
                  if(left301<b || left301>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button13->Enabled = true;
                  }
                  else  Edit32->Text = left300;
             }
             if(US->Checked == true)
             {
                 if(left301<b || left301>a)
                  {
                       Result3->Caption = "FAIL";
                       Result20->Caption = "FAIL";
                       TelnetForm->Button21->Enabled = true;

                  }
                  else  Edit32->Text = left300;
             }

        }
        if(i==1)
        {
             if(EU->Checked == true)
             {
                  if(left301<b || left301>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button13->Enabled = true;
                  }
                  else  Edit41->Text = left300;
             }
             if(US->Checked == true)
             {
                 if(left301<b || left301>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button21->Enabled = true;
                  }
                  else  Edit41->Text = left300;
             }
        }
        if(i==2)
        {
             if(EU->Checked == true)
             {
                  if(left301<b || left301>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button13->Enabled = true;
                  }
                  else Edit50->Text = left300;
             }
             if(US->Checked == true)
             {
                 if(left301<b || left301>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button21->Enabled = true;
                  }
                  else Edit50->Text = left300;
             }

        }
        if(i==3)
        {
             if(EU->Checked == true)
             {
                  if(left301<b || left301>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button13->Enabled = true;
                  }
                  else Edit91->Text = left300;
             }
             if(US->Checked == true)
             {
                 if(left301<b || left301>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button21->Enabled = true;
                  }
                  else Edit91->Text = left300;
             }

        }
        if(i==4)
        {
             if(EU->Checked == true)
             {
                  if(left301<b || left301>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button13->Enabled = true;
                  }
                  else Edit101->Text = left300;
             }
             if(US->Checked == true)
             {
                 if(left301<b || left301>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button21->Enabled = true;
                  }
                  else Edit101->Text = left300;
             }

        }
        if(i==5)
        {
             if(US->Checked == true)
             {
                 if(left301<b || left301>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button21->Enabled = true;
                  }
                  else Edit111->Text = left300;
             }

        }

        String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
        String left302 = right302.SubString(0,right302.Pos("A")-2);
        String left0011 = left302+outlet11+left251;
        Current->Caption = left0011;
        float left303 = StrToFloat(left302);
        if(i==0)
        {
             if(left303<m || left303>n)
             {
                Result3->Caption = "FAIL";
                Result20->Caption = "FAIL";
                TelnetForm->Button13->Enabled = true;
                TelnetForm->Button21->Enabled = true;
             }
             else  Edit1->Text = left302;
        }
        if(i==1)
        {
             if(EU->Checked == true)
             {
                  if(left303<m || left303>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button13->Enabled = true;
                  }
                  else  Edit10->Text = left302;
             }
             if(US->Checked == true)
             {
                 if(left303<m || left303>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button21->Enabled = true;
                  }
                  else  Edit10->Text = left302;
             }
        }
        if(i==2)
        {
             if(EU->Checked == true)
             {
                  if(left303<m || left303>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button13->Enabled = true;
                  }
                  else  Edit19->Text = left302;
             }
              if(US->Checked == true)
             {
                 if(left303<m || left303>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button21->Enabled = true;
                  }
                  else  Edit19->Text = left302;
             }

        }
        if(i==3)
        {
             if(EU->Checked == true)
             {
                  if(left303<m || left303>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button13->Enabled = true;
                  }
                  else  Edit61->Text = left302;
             }
              if(US->Checked == true)
             {
                 if(left303<m || left303>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button21->Enabled = true;
                  }
                  else  Edit61->Text = left302;
             }

        }
        if(i==4)
        {
             if(EU->Checked == true)
             {
                  if(left303<m || left303>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button13->Enabled = true;
                  }
                  else  Edit71->Text = left302;
             }
              if(US->Checked == true)
             {
                 if(left303<m || left303>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button21->Enabled = true;
                  }
                  else  Edit71->Text = left302;
             }

        }
        if(i==5)
        {
              if(US->Checked == true)
             {
                 if(left303<m || left303>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button21->Enabled = true;
                  }
                  else  Edit81->Text = left302;
             }

        }

        //Application->MessageBox("Outlet 1 Current","show");
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 1 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(500);
        Application->ProcessMessages();

   //     if (Application->MessageBox("Outlet 1 Current is OK?","Check Outlet 1 Current",MB_OKCANCEL) == IDCANCEL)  //Check the Outlet 1 Current is OK again?
        if(Result3->Caption == "FAIL")
        {
               // Result3->Caption = "FAIL";
                if(EU->Checked == true)
                {
                        Shape1->Brush->Color = clRed;
                }
                if(US->Checked == true)
                {
                        Shape9->Brush->Color = clRed;
                }
                Memo1->Lines->Add("Outlet 1 Current is Wrong");
                if(US->Checked == true)
                {
                        updateLogFile("Fail-US-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                }
                 if(EU->Checked == true)
                {
                        updateLogFile("Fail-EU-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                }

        }
        else
        {
               if(i==0)
               {
                   z11->Caption = "1";
               }
               if(i==1)
               {
                   z21->Caption = "1";
               }
               if(i==2)
               {
                   z31->Caption = "1";
               }
               if(i==3)
               {
                   z41->Caption = "1";
               }
               if(i==4)
               {
                   z51->Caption = "1";
               }
               if(i==5)
               {
                   z61->Caption = "1";
               }
                if(EU->Checked == true && Shape1->Brush->Color != clRed)
                {
                        Shape1->Brush->Color = clLime;
                        TelnetForm->Button13->Enabled = false;
                }
                if(US->Checked == true && Shape9->Brush->Color != clRed)
                {
                        Shape9->Brush->Color = clLime;
                        TelnetForm->Button21->Enabled = false;
                }
        }
//----------------------end outlet1 power test-----------------------------------

//----------------------start outlet2 power test-----------------------------------
        Power->Caption = "";
        Current->Caption = "";
        Result3->Caption = "";

        IdTelnetDemo->SendCh('\r');
        if(EU->Checked == true&&Shape2->Brush->Color != clRed)
        {
                Shape2->Brush->Color = clYellow;
        }
        if(US->Checked == true&&Shape10->Brush->Color != clRed)
        {
                Shape10->Brush->Color = clYellow;
        }
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(set_outlet_2_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 2 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        /*::Sleep(2000);
        Application->ProcessMessages();

        ::Sleep(1000);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(show_outlet_2_status);
        Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 2");
        Memo1->Lines->Add("");
        IdTelnetDemo->SendCh('\n');
        Memo1Display();  */

        for(j=0;j<3;j++)
        {
                if(j==0)
                {//Application->MessageBox("1","show");
                ::Sleep(3000);
                Application->ProcessMessages(); }
                if(j==1)
                {//Application->MessageBox("1","show");
                ::Sleep(2000);
                Application->ProcessMessages(); }
                if(j==2)
                {
                        IdTelnetDemo->SendCh('\r');
                        SendCommand(show_outlet_2_status);
                        ::Sleep(500);
                        Application->ProcessMessages();
                        SendCommand(Enter);
                        //Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 2");
                        //Memo1->Lines->Add("");
                       //IdTelnetDemo->SendCh('\n');
                       ::Sleep(1000);
                        Application->ProcessMessages();
                        Memo1Display();
                }
         }

        int num31=Memo1->Lines->Count;
        ::Sleep(1500);
        Application->ProcessMessages();
        String yyy31=Memo1->Lines->Strings[num31-1]+Memo1->Lines->Strings[num31]+Memo1->Lines->Strings[num31-2]+Memo1->Lines->Strings[num31+1];
        char *p31 = yyy31.c_str();
       // Application->MessageBox(yyy31.c_str(),"show");
        String right310 = yyy31.SubString(yyy31.Pos("power")+8,10);
        String left310 = right310.SubString(0,right310.Pos("W")-2);
        //Application->MessageBox(left310.c_str(),"show");
        String left002 = left310+outlet11+left250;
        Power->Caption = left002;
        float left311 = StrToFloat(left310);
        if(i==0)
        {
             if(EU->Checked == true)
             {
                  if(left311<b || left311>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button14->Enabled = true;
                  }
                  else  Edit33->Text = left310;
             }
             if(US->Checked == true)
             {
                  if(left311<b|| left311>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button22->Enabled = true;
                  }
                  else  Edit33->Text = left310;
             }

        }
        if(i==1)
        {
             if(EU->Checked == true)
             {
                  if(left311<b || left311>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button14->Enabled = true;
                  }
                  else  Edit42->Text = left310;
             }
             if(US->Checked == true)
             {
                 if(left311<b || left311>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button22->Enabled = true;
                  }
                  else  Edit42->Text = left310;
             }
        }
        if(i==2)
        {
             if(EU->Checked == true)
             {
                  if(left311<b || left311>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button14->Enabled = true;
                  }
                  else  Edit51->Text = left310;
             }
             if(US->Checked == true)
             {
                 if(left311<b || left311>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button22->Enabled = true;
                  }
                  else  Edit51->Text = left310;
             }

        }
        if(i==3)
        {
             if(EU->Checked == true)
             {
                  if(left311<b || left311>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button14->Enabled = true;
                  }
                  else  Edit92->Text = left310;
             }
             if(US->Checked == true)
             {
                 if(left311<b || left311>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button22->Enabled = true;
                  }
                  else  Edit92->Text = left310;
             }

        }
        if(i==4)
        {
             if(EU->Checked == true)
             {
                  if(left311<b || left311>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button14->Enabled = true;
                  }
                  else  Edit102->Text = left310;
             }
             if(US->Checked == true)
             {
                 if(left311<b || left311>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button22->Enabled = true;
                  }
                  else  Edit102->Text = left310;
             }

        }
        if(i==5)
        {
             if(US->Checked == true)
             {
                 if(left311<b || left311>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button22->Enabled = true;
                  }
                  else  Edit112->Text = left310;
             }

        }

        String right312 =  yyy31.SubString(yyy31.Pos("current")+10,10);
        String left312 = right312.SubString(0,right312.Pos("A")-2);
        String left0012 = left312+outlet11+left251;
        Current->Caption = left0012;
        float left313 = StrToFloat(left312);
        if(i==0)
        {
             if(left313<m || left313>n)
             {
                Result3->Caption = "FAIL";
                Result20->Caption = "FAIL";
                TelnetForm->Button14->Enabled = true;
                TelnetForm->Button22->Enabled = true;
             }
             else  Edit2->Text = left312;
        }
        if(i==1)
        {
             if(EU->Checked == true)
             {
                  if(left313<m || left313>n)
                  {
                     Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button14->Enabled = true;
                  }
                 else  Edit11->Text = left312;
             }
             if(US->Checked == true)
             {
                 if(left313<m || left313>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button22->Enabled = true;
                  }
                  else  Edit11->Text = left312;
             }
        }
        if(i==2)
        {
             if(EU->Checked == true)
             {
                  if(left313<m || left313>n)
                  {
                     Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button14->Enabled = true;
                  }
                  else  Edit20->Text = left312;
             }
             if(US->Checked == true)
             {
                 if(left313<m || left313>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button22->Enabled = true;
                  }
                  else  Edit20->Text = left312;
             }

        }
        if(i==3)
        {
             if(EU->Checked == true)
             {
                  if(left313<m || left313>n)
                  {
                     Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button14->Enabled = true;
                  }
                  else  Edit62->Text = left312;
             }
             if(US->Checked == true)
             {
                 if(left313<m || left313>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button22->Enabled = true;
                  }
                  else  Edit62->Text = left312;
             }

        }
        if(i==4)
        {
             if(EU->Checked == true)
             {
                  if(left313<m || left313>n)
                  {
                     Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button14->Enabled = true;
                  }
                  else  Edit72->Text = left312;
             }
             if(US->Checked == true)
             {
                 if(left313<m || left313>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button22->Enabled = true;
                  }
                  else  Edit72->Text = left312;
             }

        }
        if(i==5)
        {
             if(US->Checked == true)
             {
                 if(left313<m || left313>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button22->Enabled = true;
                  }
                  else  Edit82->Text = left312;
             }

        }

        //Application->MessageBox("輸出端口2電流","顯示");
        //Application->MessageBox("Outlet 2 Current","show");
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_2_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 2 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(500);
        Application->ProcessMessages();

    //    if (Application->MessageBox("Outlet 2 Current is OK?","Check Outlet 2 Current",MB_OKCANCEL) == IDCANCEL)  //Check the Outlet 2 Current is OK again?
        if(Result3->Caption == "FAIL")
        {
               // Result3->Caption = "FAIL";
                if(EU->Checked == true)
                {
                        Shape2->Brush->Color = clRed;
                }
                if(US->Checked == true)
                {
                        Shape10->Brush->Color = clRed;
                }
                Memo1->Lines->Add("Outlet 2 Current is Wrong");
                if(US->Checked == true)
                {
                        updateLogFile("Fail-US-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                }
                else if(EU->Checked == true)
                {
                        updateLogFile("Fail-EU-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                }

        }
        else
        {
               if(i==0)
               {
                      z12->Caption = "2";
               }
               if(i==1)
               {
                   z22->Caption = "2";
               }
               if(i==2)
               {
                   z32->Caption = "2";
               }
               if(i==3)
               {
                      z42->Caption = "2";
               }
               if(i==4)
               {
                   z52->Caption = "2";
               }
               if(i==5)
               {
                   z62->Caption = "2";
               }
                if(EU->Checked == true && Shape2->Brush->Color != clRed)
                {
                        Shape2->Brush->Color = clLime;
                        TelnetForm->Button14->Enabled = false;
                }
                if(US->Checked == true && Shape10->Brush->Color != clRed)
                {
                        Shape10->Brush->Color = clLime;
                        TelnetForm->Button22->Enabled = false;
                }
        }
//----------------------end outlet2 power test-----------------------------------

//----------------------start outlet3 power test-----------------------------------
        Power->Caption = "";
        Current->Caption = "";
        Result3->Caption = "";

        IdTelnetDemo->SendCh('\r');
        if(EU->Checked == true&&Shape3->Brush->Color != clRed)
        {
                Shape3->Brush->Color = clYellow;
        }
        if(US->Checked == true&&Shape11->Brush->Color != clRed)
        {
                Shape11->Brush->Color = clYellow;
        }
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(set_outlet_3_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 3 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        /*::Sleep(2000);
        Application->ProcessMessages();

        ::Sleep(1000);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(show_outlet_3_status);
        Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 3");
        Memo1->Lines->Add("");
        IdTelnetDemo->SendCh('\n');
        Memo1Display(); */

        for(j=0;j<3;j++)
        {
                if(j==0)
                {//Application->MessageBox("1","show");
                ::Sleep(3000);
                Application->ProcessMessages(); }
                if(j==1)
                {//Application->MessageBox("1","show");
                ::Sleep(2000);
                Application->ProcessMessages(); }
                if(j==2)
                {
                        IdTelnetDemo->SendCh('\r');
                        SendCommand(show_outlet_3_status);
                        ::Sleep(500);
                        Application->ProcessMessages();
                        SendCommand(Enter);
                        //Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 3");
                        //Memo1->Lines->Add("");
                        //IdTelnetDemo->SendCh('\n');
                        ::Sleep(1000);
                        Application->ProcessMessages();
                        Memo1Display();
                }
         }

        int num32=Memo1->Lines->Count;
        ::Sleep(1500);
        Application->ProcessMessages();

        String yyy32=Memo1->Lines->Strings[num32-1]+Memo1->Lines->Strings[num32]+Memo1->Lines->Strings[num32-2]+Memo1->Lines->Strings[num32+1];
        char *p32 = yyy32.c_str();
       // Application->MessageBox(yyy32.c_str(),"show");
        String right320 = yyy32.SubString(yyy32.Pos("power")+8,10);
        String left320 = right320.SubString(0,right320.Pos("W")-2);
        //Application->MessageBox(left320.c_str(),"show");
        String left003 = left320+outlet11+left250;
        Power->Caption = left003;
        float left321 = StrToFloat(left320);
        if(i==0)
        {
             if(EU->Checked == true)
             {
                  if(left321<b || left321>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button15->Enabled = true;
                  }
                  else  Edit34->Text = left320;
             }
             if(US->Checked == true)
             {
                 if(left321<b || left321>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button23->Enabled = true;
                  }
                  else  Edit34->Text = left320;
             }

        }
        if(i==1)
        {
             if(EU->Checked == true)
             {
                  if(left321<b || left321>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button15->Enabled = true;
                  }
                  else  Edit43->Text = left320;
             }
             if(US->Checked == true)
             {
                 if(left321<b || left321>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button23->Enabled = true;
                  }
                  else  Edit43->Text = left320;
             }
        }
        if(i==2)
        {
             if(EU->Checked == true)
             {
                  if(left321<b || left321>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button15->Enabled = true;
                  }
                  else  Edit52->Text = left320;
             }
             if(US->Checked == true)
             {
                 if(left321<b || left321>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button23->Enabled = true;
                  }
                  else  Edit52->Text = left320;
             }

        }
        if(i==3)
        {
             if(EU->Checked == true)
             {
                  if(left321<b || left321>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button15->Enabled = true;
                  }
                  else  Edit93->Text = left320;
             }
             if(US->Checked == true)
             {
                 if(left321<b || left321>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button23->Enabled = true;
                  }
                  else  Edit93->Text = left320;
             }

        }
        if(i==4)
        {
             if(EU->Checked == true)
             {
                  if(left321<b || left321>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button15->Enabled = true;
                  }
                  else  Edit103->Text = left320;
             }
             if(US->Checked == true)
             {
                 if(left321<b || left321>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button23->Enabled = true;
                  }
                  else  Edit103->Text = left320;
             }

        }
        if(i==5)
        {
             if(US->Checked == true)
             {
                 if(left321<b || left321>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button23->Enabled = true;
                  }
                  else  Edit113->Text = left320;
             }

        }
        String right322 =  yyy32.SubString(yyy32.Pos("current")+10,10);
        String left322 = right322.SubString(0,right322.Pos("A")-2);
        String left0013 = left322+outlet11+left251;
        Current->Caption = left0013;
        float left323 = StrToFloat(left322);
        if(i==0)
        {
             if(left323<m || left323>n)
             {
                Result3->Caption = "FAIL";
                Result20->Caption = "FAIL";
                TelnetForm->Button15->Enabled = true;
                TelnetForm->Button23->Enabled = true;
             }
             else  Edit3->Text = left322;
        }
        if(i==1)
        {
             if(EU->Checked == true)
             {
                  if(left323<m || left323>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button15->Enabled = true;
                  }
                  else  Edit12->Text = left322;
             }
             if(US->Checked == true)
             {
                 if(left323<m || left323>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button23->Enabled = true;
                  }
                  else  Edit12->Text = left322;
             }
        }
        if(i==2)
        {
             if(EU->Checked == true)
             {
                  if(left323<m || left323>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button15->Enabled = true;
                  }
                  else  Edit21->Text = left322;
             }
             if(US->Checked == true)
             {
                 if(left323<m || left323>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button23->Enabled = true;
                  }
                  else  Edit21->Text = left322;
             }

        }
        if(i==3)
        {
             if(EU->Checked == true)
             {
                  if(left323<m || left323>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button15->Enabled = true;
                  }
                  else  Edit63->Text = left322;
             }
             if(US->Checked == true)
             {
                 if(left323<m || left323>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button23->Enabled = true;
                  }
                  else  Edit63->Text = left322;
             }
        }
        if(i==4)
        {
             if(EU->Checked == true)
             {
                  if(left323<m || left323>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button15->Enabled = true;
                  }
                  else  Edit73->Text = left322;
             }
             if(US->Checked == true)
             {
                 if(left323<m || left323>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button23->Enabled = true;
                  }
                  else  Edit73->Text = left322;
             }
        }
        if(i==5)
        {
             if(US->Checked == true)
             {
                 if(left323<m || left323>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button23->Enabled = true;
                  }
                  else  Edit83->Text = left322;
             }
        }

        //Application->MessageBox("輸出端口3電流","顯示");
        //Application->MessageBox("Outlet 3 Current","show");
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_3_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 3 -v 0");
       // Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(500);
        Application->ProcessMessages();

   //     if (Application->MessageBox("Outlet 3 Current is OK?","Check Outlet 3 Current",MB_OKCANCEL) == IDCANCEL)  //Check the Outlet 3 Current is OK again?
        if(Result3->Caption == "FAIL")
        {
               // Result3->Caption = "FAIL";
                if(EU->Checked == true)
                {
                        Shape3->Brush->Color = clRed;
                }
                if(US->Checked == true)
                {
                        Shape11->Brush->Color = clRed;
                }
                Memo1->Lines->Add("Outlet 3 Current is Wrong");
                if(US->Checked == true)
                {
                        updateLogFile("Fail-US-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                }
                else if(EU->Checked == true)
                {
                        updateLogFile("Fail-EU-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                }

        }
        else
        {
                if(i==0)
               {
                      z13->Caption = "3";
               }
               if(i==1)
               {
                   z23->Caption = "3";
               }
               if(i==2)
               {
                   z33->Caption = "3";
               }
               if(i==3)
               {
                   z43->Caption = "3";
               }
               if(i==4)
               {
                   z53->Caption = "3";
               }
               if(i==5)
               {
                   z63->Caption = "3";
               }
                if(EU->Checked == true && Shape3->Brush->Color != clRed)
                {
                        Shape3->Brush->Color = clLime;
                        TelnetForm->Button15->Enabled = false;
                }
                if(US->Checked == true && Shape11->Brush->Color != clRed)
                {
                        Shape11->Brush->Color = clLime;
                        TelnetForm->Button23->Enabled = false;
                }
        }
//----------------------end outlet3 power test-----------------------------------

//----------------------start outlet4 power test-----------------------------------
        Power->Caption = "";
        Current->Caption = "";
        Result3->Caption = "";

        IdTelnetDemo->SendCh('\r');
        if(EU->Checked == true&&Shape4->Brush->Color != clRed)
        {
                Shape4->Brush->Color = clYellow;
        }
        if(US->Checked == true&&Shape12->Brush->Color != clRed)
        {
                Shape12->Brush->Color = clYellow;
        }
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(set_outlet_4_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 4 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

      /*  ::Sleep(2000);
        Application->ProcessMessages();

        ::Sleep(1000);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(show_outlet_4_status);
        Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 4");
        Memo1->Lines->Add("");
        IdTelnetDemo->SendCh('\n');
        Memo1Display();  */

        for(j=0;j<3;j++)
        {
                if(j==0)
                {//Application->MessageBox("1","show");
                ::Sleep(3000);
                Application->ProcessMessages(); }
                if(j==1)
                {//Application->MessageBox("1","show");
                ::Sleep(2000);
                Application->ProcessMessages(); }
                if(j==2)
                {
                        IdTelnetDemo->SendCh('\r');
                        SendCommand(show_outlet_4_status);
                        ::Sleep(500);
                        Application->ProcessMessages();
                        SendCommand(Enter);
                        //Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 4");
                        //Memo1->Lines->Add("");
                        //IdTelnetDemo->SendCh('\n');
                        ::Sleep(1000);
                        Application->ProcessMessages();
                        Memo1Display();
                }
         }

        int num33=Memo1->Lines->Count;
        ::Sleep(1500);
        Application->ProcessMessages();

        String yyy33=Memo1->Lines->Strings[num33-1]+Memo1->Lines->Strings[num33]+Memo1->Lines->Strings[num33-2]+Memo1->Lines->Strings[num33+1];
        char *p33 = yyy33.c_str();
        // Application->MessageBox(yyy32.c_str(),"show");
        String right330 = yyy33.SubString(yyy33.Pos("power")+8,10);
        String left330 = right330.SubString(0,right330.Pos("W")-2);
        char *a3 =left330.c_str();
       // Application->MessageBox(left330.c_str(),"show");
        String left004 = left330+outlet11+left250;
        Power->Caption = left004;
        float left331 = StrToFloat(left330);
        if(i==0)
        {
             if(EU->Checked == true)
             {
                  if(left331<b || left331>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button16->Enabled = true;
                  }
                   else  Edit35->Text = left330;
             }
             if(US->Checked == true)
             {
                 if(left331<b || left331>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button24->Enabled = true;
                  }
                  else  Edit35->Text = left330;
             }

        }
        if(i==1)
        {
             if(EU->Checked == true)
             {
                  if(left331<b || left331>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button16->Enabled = true;
                  }
                  else  Edit44->Text = left330;
             }
             if(US->Checked == true)
             {
                 if(left331<b || left331>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button24->Enabled = true;
                  }
                  else  Edit44->Text = left330;
             }
        }
        if(i==2)
        {
             if(EU->Checked == true)
             {
                  if(left331<b || left331>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button16->Enabled = true;
                  }
                   else  Edit53->Text = left330;
             }
             if(US->Checked == true)
             {
                 if(left331<b || left331>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button24->Enabled = true;
                  }
                  else  Edit53->Text = left330;
             }

        }
         if(i==3)
        {
             if(EU->Checked == true)
             {
                  if(left331<b || left331>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button16->Enabled = true;
                  }
                  else  Edit94->Text = left330;
             }
             if(US->Checked == true)
             {
                 if(left331<b || left331>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button24->Enabled = true;
                  }
                  else  Edit94->Text = left330;
             }
        }
         if(i==4)
        {
             if(EU->Checked == true)
             {
                  if(left331<b || left331>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button16->Enabled = true;
                  }
                  else  Edit104->Text = left330;
             }
             if(US->Checked == true)
             {
                 if(left331<b || left331>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button24->Enabled = true;
                  }
                  else  Edit104->Text = left330;
             }
        }
         if(i==5)
        {
             if(US->Checked == true)
             {
                 if(left331<b || left331>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button24->Enabled = true;
                  }
                  else  Edit114->Text = left330;
             }
        }
        String right332 =  yyy33.SubString(yyy33.Pos("current")+10,10);
        String left332 = right332.SubString(0,right332.Pos("A")-2);
        String left0014 = left332+outlet11+left251;
        Current->Caption = left0014;
        float left333 = StrToFloat(left332);
        if(i==0)
        {
             if(left333<m || left333>n)
             {
                Result3->Caption = "FAIL";
                Result20->Caption = "FAIL";
                TelnetForm->Button16->Enabled = true;
                TelnetForm->Button24->Enabled = true;
             }
             else  Edit4->Text = left332;
        }
        if(i==1)
        {
             if(EU->Checked == true)
             {
                  if(left333<m|| left333>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button16->Enabled = true;
                  }
                  else  Edit13->Text = left332;
             }
             if(US->Checked == true)
             {
                 if(left333<m || left333>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button24->Enabled = true;
                  }
                   else  Edit13->Text = left332;
             }
        }
        if(i==2)
        {
             if(EU->Checked == true)
             {
                  if(left333<m || left333>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button16->Enabled = true;
                  }
                  else  Edit22->Text = left332;
             }
             if(US->Checked == true)
             {
                 if(left333<m || left333>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button24->Enabled = true;
                  }
                  else  Edit22->Text = left332;
             }

        }
        if(i==3)
        {
             if(EU->Checked == true)
             {
                  if(left333<m|| left333>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button16->Enabled = true;
                  }
                  else  Edit64->Text = left332;
             }
             if(US->Checked == true)
             {
                 if(left333<m || left333>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button24->Enabled = true;
                  }
                   else  Edit64->Text = left332;
             }
        }
        if(i==4)
        {
             if(EU->Checked == true)
             {
                  if(left333<m|| left333>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button16->Enabled = true;
                  }
                  else  Edit74->Text = left332;
             }
             if(US->Checked == true)
             {
                 if(left333<m || left333>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button24->Enabled = true;
                  }
                   else  Edit74->Text = left332;
             }
        }
        if(i==5)
        {
             if(US->Checked == true)
             {
                 if(left333<m || left333>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button24->Enabled = true;
                  }
                   else  Edit84->Text = left332;
             }
        }

        //Application->MessageBox("輸出端口4電流","顯示");
        //Application->MessageBox("Outlet 4 Current","show");
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_4_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 4 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(500);
        Application->ProcessMessages();

     //   if (Application->MessageBox("Outlet 4 Current is OK?","Check Outlet 4 Current",MB_OKCANCEL) == IDCANCEL)  //Check the Outlet 4 Current is OK again?
        if(Result3->Caption == "FAIL")
        {
             //   Result3->Caption = "FAIL";
                if(EU->Checked == true)
                {
                        Shape4->Brush->Color = clRed;
                }
                if(US->Checked == true)
                {
                        Shape12->Brush->Color = clRed;
                }
                Memo1->Lines->Add("Outlet 4 Current is Wrong");
                if(US->Checked == true)
                {
                        updateLogFile("Fail-US-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                }
                else if(EU->Checked == true)
                {
                        updateLogFile("Fail-EU-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                }

        }
        else
        {
               if(i==0)
               {
                      z14->Caption = "4";
               }
               if(i==1)
               {
                   z24->Caption = "4";
               }
               if(i==2)
               {
                   z34->Caption = "4";
               }
               if(i==3)
               {
                      z44->Caption = "4";
               }
               if(i==4)
               {
                   z54->Caption = "4";
               }
               if(i==5)
               {
                   z64->Caption = "4";
               }
                if(EU->Checked == true && Shape4->Brush->Color != clRed)
                {
                        Shape4->Brush->Color = clLime;
                        TelnetForm->Button16->Enabled = false;
                }
                if(US->Checked == true && Shape12->Brush->Color != clRed)
                {
                        Shape12->Brush->Color = clLime;
                        TelnetForm->Button24->Enabled = false;
                }
        }
//----------------------end outlet4 power test-----------------------------------

//----------------------start outlet5 power test-----------------------------------
        Power->Caption = "";
        Current->Caption = "";
        Result3->Caption = "";

        IdTelnetDemo->SendCh('\r');
        if(EU->Checked == true&&Shape5->Brush->Color != clRed)
        {
                Shape5->Brush->Color = clYellow;
        }
        if(US->Checked == true&&Shape13->Brush->Color != clRed)
        {
                Shape13->Brush->Color = clYellow;
        }
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(set_outlet_5_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 5 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

      /*  ::Sleep(2000);
        Application->ProcessMessages();

        ::Sleep(1000);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(show_outlet_5_status);
        Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 5");
        Memo1->Lines->Add("");
        IdTelnetDemo->SendCh('\n');
        Memo1Display();   */

        for(j=0;j<3;j++)
        {
                if(j==0)
                {//Application->MessageBox("1","show");
                ::Sleep(3000);
                Application->ProcessMessages(); }
                if(j==1)
                {//Application->MessageBox("1","show");
                ::Sleep(2000);
                Application->ProcessMessages(); }
                if(j==2)
                {
                        IdTelnetDemo->SendCh('\r');
                        SendCommand(show_outlet_5_status);
                        ::Sleep(500);
                        Application->ProcessMessages();
                        SendCommand(Enter);
                        //Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 5");
                        //Memo1->Lines->Add("");
                        //IdTelnetDemo->SendCh('\n');
                        ::Sleep(1000);
                        Application->ProcessMessages();
                        Memo1Display();
                }
         }

        int num34=Memo1->Lines->Count;
        ::Sleep(1500);
        Application->ProcessMessages();

        String yyy34=Memo1->Lines->Strings[num34-1]+Memo1->Lines->Strings[num34]+Memo1->Lines->Strings[num34-2]+Memo1->Lines->Strings[num34+1];
        //char *p34 = yyy34.c_str();

        String right340 = yyy34.SubString(yyy34.Pos("power")+8,10);
        String left340 = right340.SubString(0,right340.Pos("W")-2);
        String left005 = left340+outlet11+left250;
        Power->Caption = left005;
        float left341 = StrToFloat(left340);
        if(i==0)
        {
             if(EU->Checked == true)
             {
                  if(left341<b || left341>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button17->Enabled = true;
                  }
                  else  Edit36->Text = left340;
             }
             if(US->Checked == true)
             {
                 if(left341<b || left341>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button25->Enabled = true;
                  }
                  else  Edit36->Text = left340;
             }

        }
        if(i==1)
        {
             if(EU->Checked == true)
             {
                  if(left341<b || left341>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button17->Enabled = true;
                  }
                  else  Edit45->Text = left340;
             }
             if(US->Checked == true)
             {
                 if(left341<b || left341>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button25->Enabled = true;
                  }
                  else  Edit45->Text = left340;
             }
        }
        if(i==2)
        {
             if(EU->Checked == true)
             {
                  if(left341<b || left341>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button17->Enabled = true;
                  }
                   else  Edit54->Text = left340;
             }

             if(US->Checked == true)
             {
                 if(left341<b || left341>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button25->Enabled = true;
                  }
                  else  Edit54->Text = left340;
             }

        }
        if(i==3)
        {
             if(EU->Checked == true)
             {
                  if(left341<b || left341>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button17->Enabled = true;
                  }
                   else  Edit95->Text = left340;
             }

             if(US->Checked == true)
             {
                 if(left341<b || left341>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button25->Enabled = true;
                  }
                  else  Edit95->Text = left340;
             }

        }if(i==4)
        {
             if(EU->Checked == true)
             {
                  if(left341<b || left341>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button17->Enabled = true;
                  }
                   else  Edit105->Text = left340;
             }

             if(US->Checked == true)
             {
                 if(left341<b || left341>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button25->Enabled = true;
                  }
                  else  Edit105->Text = left340;
             }

        }if(i==5)
        {
             if(US->Checked == true)
             {
                 if(left341<b || left341>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button25->Enabled = true;
                  }
                  else  Edit115->Text = left340;
             }

        }
        String right342 =  yyy34.SubString(yyy34.Pos("current")+10,10);
        String left342 = right342.SubString(0,right342.Pos("A")-2);
        String left0015 = left342+outlet11+left251;
        Current->Caption = left0015;
        float left343 = StrToFloat(left342);
        if(i==0)
        {
             if(left343<m || left343>n)
             {
                Result3->Caption = "FAIL";
                Result20->Caption = "FAIL";
                TelnetForm->Button17->Enabled = true;
                TelnetForm->Button25->Enabled = true;
             }
             else  Edit5->Text = left342;
        }
        if(i==1)
        {
             if(EU->Checked == true)
             {
                  if(left343<m || left343>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button17->Enabled = true;
                  }
                  else  Edit14->Text = left342;
             }
             if(US->Checked == true)
             {
                 if(left343<m || left343>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button25->Enabled = true;
                  }
                  else  Edit14->Text = left342;
             }
        }
        if(i==2)
        {
             if(EU->Checked == true)
             {
                  if(left343<m || left343>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button17->Enabled = true;
                  }
                  else  Edit23->Text = left342;
             }
             if(US->Checked == true)
             {
                 if(left343<m || left343>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button25->Enabled = true;
                  }
                  else  Edit23->Text = left342;
             }

        }
        if(i==3)
        {
             if(EU->Checked == true)
             {
                  if(left343<m || left343>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button17->Enabled = true;
                  }
                  else  Edit65->Text = left342;
             }
             if(US->Checked == true)
             {
                 if(left343<m || left343>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button25->Enabled = true;
                  }
                  else  Edit65->Text = left342;
             }
        }
        if(i==4)
        {
             if(EU->Checked == true)
             {
                  if(left343<m || left343>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button17->Enabled = true;
                  }
                  else  Edit75->Text = left342;
             }
             if(US->Checked == true)
             {
                 if(left343<m || left343>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button25->Enabled = true;
                  }
                  else  Edit75->Text = left342;
             }
        }
        if(i==5)
        {
             if(US->Checked == true)
             {
                 if(left343<m || left343>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button25->Enabled = true;
                  }
                  else  Edit85->Text = left342;
             }
        }

        //Application->MessageBox("輸出端口5電流","顯示");
        //Application->MessageBox("Outlet 5 Current","show");
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_5_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 5 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(500);
        Application->ProcessMessages();

      //  if (Application->MessageBox("Outlet 5 Current is OK?","Check Outlet 5 Current",MB_OKCANCEL) == IDCANCEL)  //Check the Outlet 5 Current is OK again?
        if(Result3->Caption == "FAIL")
        {
              //  Result3->Caption = "FAIL";
                Memo1->Lines->Add("Outlet 5 Current is Wrong");
                if(EU->Checked == true)
                {
                        Shape5->Brush->Color = clRed;
                }
                if(US->Checked == true)
                {
                        Shape13->Brush->Color = clRed;
                }
                if(US->Checked == true)
                {
                        updateLogFile("Fail-US-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                }
                else if(EU->Checked == true)
                {
                        updateLogFile("Fail-EU-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                }

        }
        else
        {
               if(i==0)
               {
                   z15->Caption = "5";
               }
               if(i==1)
               {
                   z25->Caption = "5";
               }
               if(i==2)
               {
                   z35->Caption = "5";
               }
               if(i==3)
               {
                   z45->Caption = "5";
               }
               if(i==4)
               {
                   z55->Caption = "5";
               }
               if(i==5)
               {
                   z65->Caption = "5";
               }
                if(EU->Checked == true && Shape5->Brush->Color != clRed)
                {
                        Shape5->Brush->Color = clLime;
                        TelnetForm->Button17->Enabled = false;
                }
                if(US->Checked == true && Shape13->Brush->Color != clRed)
                {
                        Shape13->Brush->Color = clLime;
                        TelnetForm->Button25->Enabled = false;
                }
        }
//----------------------end outlet5 power test-----------------------------------

//----------------------start outlet6 power test-----------------------------------
        Power->Caption = "";
        Current->Caption = "";
        Result3->Caption = "";

        IdTelnetDemo->SendCh('\r');
        if(EU->Checked == true&&Shape6->Brush->Color != clRed)
        {
                Shape6->Brush->Color = clYellow;
        }
        if(US->Checked == true&&Shape14->Brush->Color != clRed)
        {
                Shape14->Brush->Color = clYellow;
        }
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(set_outlet_6_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 6 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

      /*  ::Sleep(2000);
        Application->ProcessMessages();

        ::Sleep(1000);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(show_outlet_6_status);
        Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 6");
        Memo1->Lines->Add("");
        IdTelnetDemo->SendCh('\n');
        Memo1Display();    */

        for(j=0;j<3;j++)
        {
                if(j==0)
                {//Application->MessageBox("1","show");
                ::Sleep(3000);
                Application->ProcessMessages(); }
                if(j==1)
                {//Application->MessageBox("1","show");
                ::Sleep(2000);
                Application->ProcessMessages(); }
                if(j==2)
                {
                        IdTelnetDemo->SendCh('\r');
                        SendCommand(show_outlet_6_status);
                        ::Sleep(500);
                        Application->ProcessMessages();
                        SendCommand(Enter);
                        //Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 6");
                        //Memo1->Lines->Add("");
                        //IdTelnetDemo->SendCh('\n');
                        ::Sleep(1000);
                        Application->ProcessMessages();
                        Memo1Display();
                }
         }

        int num35=Memo1->Lines->Count;
        ::Sleep(1500);
        Application->ProcessMessages();

        String yyy35=Memo1->Lines->Strings[num35-1]+Memo1->Lines->Strings[num35]+Memo1->Lines->Strings[num35-2]+Memo1->Lines->Strings[num35+1];
        //char *p35 = yyy35.c_str();

        String right350 = yyy35.SubString(yyy35.Pos("power")+8,10);
        String left350 = right350.SubString(0,right350.Pos("W")-2);
        String left006 = left350+outlet11+left250;
        Power->Caption = left006;
        float left351 = StrToFloat(left350);
        if(i==0)
        {
             if(EU->Checked == true)
             {
                  if(left351<b || left351>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button18->Enabled = true;
                  }
                  else  Edit37->Text = left350;
             }
             if(US->Checked == true)
             {
                 if(left351<b || left351>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button26->Enabled = true;
                  }
                  else  Edit37->Text = left350;
             }
        }
        if(i==1)
        {
             if(EU->Checked == true)
             {
                  if(left351<b || left351>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button18->Enabled = true;
                  }
                   else  Edit46->Text = left350;
             }
             if(US->Checked == true)
             {
                 if(left351<b || left351>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button26->Enabled = true;
                  }
                  else  Edit46->Text = left350;
             }
        }
        if(i==2)
        {
             if(EU->Checked == true)
             {
                  if(left351<b || left351>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button18->Enabled = true;
                  }
                  else  Edit55->Text = left350;
             }
             if(US->Checked == true)
             {
                 if(left351<b || left351>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button26->Enabled = true;
                  }
                  else  Edit55->Text = left350;
             }
        }
        if(i==3)
        {
             if(EU->Checked == true)
             {
                  if(left351<b || left351>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button18->Enabled = true;
                  }
                  else  Edit96->Text = left350;
             }
             if(US->Checked == true)
             {
                 if(left351<b || left351>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button26->Enabled = true;
                  }
                  else  Edit96->Text = left350;
             }
        }
        if(i==4)
        {
             if(EU->Checked == true)
             {
                  if(left351<b || left351>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button18->Enabled = true;
                  }
                  else  Edit106->Text = left350;
             }
             if(US->Checked == true)
             {
                 if(left351<b || left351>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button26->Enabled = true;
                  }
                  else  Edit106->Text = left350;
             }
        }
        if(i==5)
        {
             if(US->Checked == true)
             {
                 if(left351<b || left351>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button26->Enabled = true;
                  }
                  else  Edit116->Text = left350;
             }
        }
        String right352 =  yyy35.SubString(yyy35.Pos("current")+10,10);
        String left352 = right352.SubString(0,right352.Pos("A")-2);
        String left0016 = left352+outlet11+left251;
        Current->Caption = left0016;
        float left353 = StrToFloat(left352);
        if(i==0)
        {
             if(left353<m || left353>n)
             {
                Result3->Caption = "FAIL";
                Result20->Caption = "FAIL";
                TelnetForm->Button18->Enabled = true;
                TelnetForm->Button26->Enabled = true;
             }
             else  Edit6->Text = left352;
        }
        if(i==1)
        {
             if(EU->Checked == true)
             {
                  if(left353<m || left353>n)
                  {
                       Result3->Caption = "FAIL";
                       Result20->Caption = "FAIL";
                       TelnetForm->Button18->Enabled = true;
                  }
                   else  Edit15->Text = left352;
             }
             if(US->Checked == true)
             {
                 if(left353<m || left353>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button26->Enabled = true;
                  }
                 else  Edit15->Text = left352;
             }
        }
        if(i==2)
        {
             if(EU->Checked == true)
             {
                  if(left353<m || left353>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button18->Enabled = true;
                  }
                  else  Edit24->Text = left352;
             }
             if(US->Checked == true)
             {
                 if(left353<m || left353>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button26->Enabled = true;
                  }
                  else  Edit24->Text = left352;
             }
        }
        if(i==3)
        {
             if(EU->Checked == true)
             {
                  if(left353<m || left353>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button18->Enabled = true;
                  }
                  else  Edit66->Text = left352;
             }
             if(US->Checked == true)
             {
                 if(left353<m || left353>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button26->Enabled = true;
                  }
                  else  Edit66->Text = left352;
             }
        }
        if(i==4)
        {
             if(EU->Checked == true)
             {
                  if(left353<m || left353>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button18->Enabled = true;
                  }
                  else  Edit76->Text = left352;
             }
             if(US->Checked == true)
             {
                 if(left353<m || left353>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button26->Enabled = true;
                  }
                  else  Edit76->Text = left352;
             }
        }
        if(i==5)
        {
             if(US->Checked == true)
             {
                 if(left353<m || left353>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button26->Enabled = true;
                  }
                  else  Edit86->Text = left352;
             }
        }
        //Application->MessageBox("輸出端口6電流","顯示");
        //Application->MessageBox("Outlet 6 Current","show");
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_6_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 6 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(500);
        Application->ProcessMessages();

   //     if (Application->MessageBox("Outlet 6 Current is OK?","Check Outlet 6 Current",MB_OKCANCEL) == IDCANCEL)  //Check the Outlet 6 Current is OK again?
        if(Result3->Caption == "FAIL")
        {
             //   Result3->Caption = "FAIL";
                Memo1->Lines->Add("Outlet 6 Current is Wrong");
                if(EU->Checked == true)
                {
                        Shape6->Brush->Color = clRed;
                }
                if(US->Checked == true)
                {
                        Shape14->Brush->Color = clRed;
                }
                if(US->Checked == true)
                {
                        updateLogFile("Fail-US-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                }
                else if(EU->Checked == true)
                {
                        updateLogFile("Fail-EU-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                }

        }
        else
        {
               if(i==0)
               {
                   z16->Caption = "6";
               }
               if(i==1)
               {
                   z26->Caption = "6";
               }
               if(i==2)
               {
                   z36->Caption = "6";
               }
               if(i==3)
               {
                   z46->Caption = "6";
               }
               if(i==4)
               {
                   z56->Caption = "6";
               }
               if(i==5)
               {
                   z66->Caption = "6";
               }
                if(EU->Checked == true && Shape6->Brush->Color != clRed)
                {
                        Shape6->Brush->Color = clLime;
                        TelnetForm->Button18->Enabled = false;
                }
                if(US->Checked == true && Shape14->Brush->Color != clRed)
                {
                        Shape14->Brush->Color = clLime;
                        TelnetForm->Button26->Enabled = false;
                }
        }
//----------------------end outlet6 power test-----------------------------------

//----------------------start outlet7 power test-----------------------------------
        Power->Caption = "";
        Current->Caption = "";
        Result3->Caption = "";

        IdTelnetDemo->SendCh('\r');
        if(EU->Checked == true&&Shape7->Brush->Color != clRed)
        {
                Shape7->Brush->Color = clYellow;
        }
        if(US->Checked == true&&Shape15->Brush->Color != clRed)
        {
                Shape15->Brush->Color = clYellow;
        }
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(set_outlet_7_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 7 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

       /* ::Sleep(2000);
        Application->ProcessMessages();

        ::Sleep(1000);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(show_outlet_7_status);
        Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 7");
        Memo1->Lines->Add("");
        IdTelnetDemo->SendCh('\n');
        Memo1Display();    */

        for(j=0;j<3;j++)
        {
                if(j==0)
                {//Application->MessageBox("1","show");
                ::Sleep(3000);
                Application->ProcessMessages(); }
                if(j==1)
                {//Application->MessageBox("1","show");
                ::Sleep(2000);
                Application->ProcessMessages(); }
                if(j==2)
                {
                        IdTelnetDemo->SendCh('\r');
                        SendCommand(show_outlet_7_status);
                        ::Sleep(500);
                        Application->ProcessMessages();
                        SendCommand(Enter);
                        //Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 7");
                        //Memo1->Lines->Add("");
                        //IdTelnetDemo->SendCh('\n');
                        ::Sleep(1000);
                        Application->ProcessMessages();
                        Memo1Display();
                }
         }

        int num36=Memo1->Lines->Count;
        ::Sleep(1500);
        Application->ProcessMessages();

        String yyy36=Memo1->Lines->Strings[num36-1]+Memo1->Lines->Strings[num36]+Memo1->Lines->Strings[num36-2]+Memo1->Lines->Strings[num36+1];
        //char *p36 = yyy36.c_str();

        String right360 = yyy36.SubString(yyy36.Pos("power")+8,10);
        String left360 = right360.SubString(0,right360.Pos("W")-2);
        String left007 = left360+outlet11+left250;
        Power->Caption = left007;
        float left361 = StrToFloat(left360);
        if(i==0)
        {
             if(EU->Checked == true)
             {
                  if(left361<b || left361>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button19->Enabled = true;
                  }
                  else  Edit38->Text = left360;
             }
             if(US->Checked == true)
             {
                 if(left361<b || left361>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button27->Enabled = true;
                  }
                  else  Edit38->Text = left360;
             }

        }
        if(i==1)
        {
             if(EU->Checked == true)
             {
                  if(left361<b || left361>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button19->Enabled = true;
                  }
                  else  Edit47->Text = left360;
             }
             if(US->Checked == true)
             {
                 if(left361<b || left361>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button27->Enabled = true;
                  }
                  else  Edit47->Text = left360;
             }
        }
        if(i==2)
        {
             if(EU->Checked == true)
             {
                  if(left361<b || left361>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button19->Enabled = true;
                  }
                  else  Edit56->Text = left360;
             }
             if(US->Checked == true)
             {
                 if(left361<b || left361>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button27->Enabled = true;
                  }
                  else  Edit56->Text = left360;
             }
        }
        if(i==3)
        {
             if(EU->Checked == true)
             {
                  if(left361<b || left361>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button19->Enabled = true;
                  }
                  else  Edit97->Text = left360;
             }
             if(US->Checked == true)
             {
                 if(left361<b || left361>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button27->Enabled = true;
                  }
                  else  Edit97->Text = left360;
             }
        }
        if(i==4)
        {
             if(EU->Checked == true)
             {
                  if(left361<b || left361>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button19->Enabled = true;
                  }
                  else  Edit107->Text = left360;
             }
             if(US->Checked == true)
             {
                 if(left361<b || left361>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button27->Enabled = true;
                  }
                  else  Edit107->Text = left360;
             }
        }
        if(i==5)
        {
             if(US->Checked == true)
             {
                 if(left361<b || left361>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button27->Enabled = true;
                  }
                  else  Edit117->Text = left360;
             }
        }
        String right362 =  yyy36.SubString(yyy36.Pos("current")+10,10);
        String left362 = right362.SubString(0,right362.Pos("A")-2);
        String left0017 = left362+outlet11+left251;
        Current->Caption = left0017;
        float left363 = StrToFloat(left362);
        if(i==0)
        {
             if(left363<m || left363>n)
             {
                Result3->Caption = "FAIL";
                Result20->Caption = "FAIL";
                TelnetForm->Button19->Enabled = true;
                TelnetForm->Button27->Enabled = true;
                }
               else  Edit7->Text = left362;
        }
        if(i==1)
        {
             if(EU->Checked == true)
             {
                  if(left363<m || left363>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button19->Enabled = true;
                  }
                  else  Edit16->Text = left362;
             }
             if(US->Checked == true)
             {
                 if(left363<m || left363>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button27->Enabled = true;
                  }
                  else  Edit16->Text = left362;
             }
        }
        if(i==2)
        {
             if(EU->Checked == true)
             {
                  if(left363<m || left363>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button19->Enabled = true;
                  }
                  else  Edit25->Text = left362;
             }
             if(US->Checked == true)
             {
                 if(left363<m || left363>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button27->Enabled = true;
                  }
                   else  Edit25->Text = left362;
             }
        }
        if(i==3)
        {
             if(EU->Checked == true)
             {
                  if(left363<m || left363>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button19->Enabled = true;
                  }
                  else  Edit67->Text = left362;
             }
             if(US->Checked == true)
             {
                 if(left363<m || left363>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button27->Enabled = true;
                  }
                   else  Edit67->Text = left362;
             }
        }
        if(i==4)
        {
             if(EU->Checked == true)
             {
                  if(left363<m || left363>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button19->Enabled = true;
                  }
                  else  Edit77->Text = left362;
             }
             if(US->Checked == true)
             {
                 if(left363<m || left363>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button27->Enabled = true;
                  }
                   else  Edit77->Text = left362;
             }
        }
        if(i==5)
        {
             if(US->Checked == true)
             {
                 if(left363<m || left363>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button27->Enabled = true;
                  }
                   else  Edit87->Text = left362;
             }
        }

        //Application->MessageBox("輸出端口7電流","顯示");
        //Application->MessageBox("Outlet 7 Current","show");
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_7_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 7 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(500);
        Application->ProcessMessages();

    //    if (Application->MessageBox("Outlet 7 Current is OK?","Check Outlet 7 Current",MB_OKCANCEL) == IDCANCEL)  //Check the Outlet 7 Current is OK again?
        if(Result3->Caption == "FAIL")
        {
             //   Result3->Caption = "FAIL";
                if(EU->Checked == true)
                {
                        Shape7->Brush->Color = clRed;
                }
                if(US->Checked == true)
                {
                        Shape15->Brush->Color = clRed;
                }
                Memo1->Lines->Add("Outlet 7 Current is Wrong");
                if(US->Checked == true)
                {
                        updateLogFile("Fail-US-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                }
                else if(EU->Checked == true)
                {
                        updateLogFile("Fail-EU-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                }

        }
        
        else
        {
                if(i==0)
               {
                   z17->Caption = "7";
               }
               if(i==1)
               {
                   z27->Caption = "7";
               }
               if(i==2)
               {
                   z37->Caption = "7";
               }
               if(i==3)
               {
                   z47->Caption = "7";
               }
               if(i==4)
               {
                   z57->Caption = "7";
               }
               if(i==5)
               {
                   z67->Caption = "7";
               }
                if(EU->Checked == true && Shape7->Brush->Color != clRed)
                {
                        Shape7->Brush->Color = clLime;
                        TelnetForm->Button19->Enabled = false;
                }
                if(US->Checked == true && Shape15->Brush->Color != clRed)
                {
                        Shape15->Brush->Color = clLime;
                        TelnetForm->Button27->Enabled = false;
                }
        }

//----------------------end outlet7 power test-----------------------------------

//----------------------start outlet8 power test-----------------------------------
        Power->Caption = "";
        Current->Caption = "";
        Result3->Caption = "";

        IdTelnetDemo->SendCh('\r');
        if(EU->Checked == true&&Shape8->Brush->Color != clRed)
        {
                Shape8->Brush->Color = clYellow;
        }
        if(US->Checked == true&&Shape16->Brush->Color != clRed)
        {
                Shape16->Brush->Color = clYellow;
        }
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(set_outlet_8_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 8 -v 1");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

       /* ::Sleep(2000);
        Application->ProcessMessages();

        ::Sleep(1000);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(show_outlet_8_status);
        Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 8");
        Memo1->Lines->Add("");
        IdTelnetDemo->SendCh('\n');
        Memo1Display();    */

        for(j=0;j<3;j++)
        {
                if(j==0)
                {//Application->MessageBox("1","show");
                ::Sleep(3000);
                Application->ProcessMessages(); }
                if(j==1)
                {//Application->MessageBox("1","show");
                ::Sleep(2000);
                Application->ProcessMessages(); }
                if(j==2)
                {
                        IdTelnetDemo->SendCh('\r');
                        SendCommand(show_outlet_8_status);
                        ::Sleep(500);
                        Application->ProcessMessages();
                        SendCommand(Enter);
                        //Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 8");
                        //Memo1->Lines->Add("");
                        //IdTelnetDemo->SendCh('\n');
                        ::Sleep(1000);
                        Application->ProcessMessages();
                        Memo1Display();
                }
         }
        int num37=Memo1->Lines->Count;
        ::Sleep(1500);
        Application->ProcessMessages();

        String yyy37=Memo1->Lines->Strings[num37-1]+Memo1->Lines->Strings[num37]+Memo1->Lines->Strings[num37-2]+Memo1->Lines->Strings[num37+1];
        //char *p37 = yyy37.c_str();

        String right370 = yyy37.SubString(yyy37.Pos("power")+8,10);
        String left370 = right370.SubString(0,right370.Pos("W")-2);
        String left008 = left370+outlet11+left250;
        Power->Caption = left008;
        float left371 = StrToFloat(left370);
        if(i==0)
        {
             if(EU->Checked == true)
             {
                  if(left371<b || left371>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button20->Enabled = true;
                  }
                   else  Edit39->Text = left370;
             }
             if(US->Checked == true)
             {
                 if(left371<b || left371>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button28->Enabled = true;
                  }
                  else  Edit39->Text = left370;
             }

        }
        if(i==1)
        {
             if(EU->Checked == true)
             {
                  if(left371<b || left371>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button20->Enabled = true;
                  }
                  else  Edit48->Text = left370;
             }
             if(US->Checked == true)
             {
                 if(left371<b || left371>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button28->Enabled = true;
                  }
                  else  Edit48->Text = left370;
             }
        }
        if(i==2)
        {
             if(EU->Checked == true)
             {
                  if(left371<b || left371>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button20->Enabled = true;
                  }
                  else  Edit57->Text = left370;
             }
             if(US->Checked == true)
             {
                 if(left371<b || left371>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button28->Enabled = true;
                  }
                   else  Edit57->Text = left370;
             }
        }
        if(i==3)
        {
             if(EU->Checked == true)
             {
                  if(left371<b || left371>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button20->Enabled = true;
                  }
                  else  Edit98->Text = left370;
             }
             if(US->Checked == true)
             {
                 if(left371<b || left371>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button28->Enabled = true;
                  }
                  else  Edit98->Text = left370;
             }
        }
        if(i==4)
        {
             if(EU->Checked == true)
             {
                  if(left371<b || left371>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button20->Enabled = true;
                  }
                  else  Edit108->Text = left370;
             }
             if(US->Checked == true)
             {
                 if(left371<b || left371>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button28->Enabled = true;
                  }
                  else  Edit108->Text = left370;
             }
        }
        if(i==5)
        {
             if(US->Checked == true)
             {
                 if(left371<b || left371>a)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button28->Enabled = true;
                  }
                  else  Edit118->Text = left370;
             }
        }
        String right372 =  yyy37.SubString(yyy37.Pos("current")+10,10);
        String left372 = right372.SubString(0,right372.Pos("A")-2);
        String left0018 = left372+outlet11+left251;
        Current->Caption = left0018;
        float left373 = StrToFloat(left372);
        if(i==0)
        {
             if(left373<m || left373>n)
             {
                Result3->Caption = "FAIL";
                Result20->Caption = "FAIL";
                TelnetForm->Button20->Enabled = true;
                TelnetForm->Button28->Enabled = true;
                }
               else  Edit8->Text = left372;
        }
        if(i==1)
        {
             if(EU->Checked == true)
             {
                  if(left373<m || left373>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button20->Enabled = true;
                  }
                  else  Edit17->Text = left372;
             }
             if(US->Checked == true)
             {
                 if(left373<m || left373>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button28->Enabled = true;
                  }
                  else  Edit17->Text = left372;
             }
        }
        if(i==2)
        {
             if(EU->Checked == true)
             {
                  if(left373<m || left373>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button20->Enabled = true;
                  }
                  else  Edit26->Text = left372;
             }
             if(US->Checked == true)
             {
                 if(left373<m || left373>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button28->Enabled = true;
                  }
                 else  Edit26->Text = left372;
             }
        }
        if(i==3)
        {
             if(EU->Checked == true)
             {
                  if(left373<m || left373>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button20->Enabled = true;
                  }
                  else  Edit68->Text = left372;
             }
             if(US->Checked == true)
             {
                 if(left373<m || left373>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button28->Enabled = true;
                  }
                 else  Edit68->Text = left372;
             }
        }
        if(i==4)
        {
             if(EU->Checked == true)
             {
                  if(left373<m || left373>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button20->Enabled = true;
                  }
                  else  Edit78->Text = left372;
             }
             if(US->Checked == true)
             {
                 if(left373<m || left373>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button28->Enabled = true;
                  }
                 else  Edit78->Text = left372;
             }
        }
        if(i==5)
        {
             if(US->Checked == true)
             {
                 if(left373<m || left373>n)
                  {
                      Result3->Caption = "FAIL";
                      Result20->Caption = "FAIL";
                      TelnetForm->Button28->Enabled = true;
                  }
                 else  Edit88->Text = left372;
             }
        }

        //Application->MessageBox("輸出端口8電流","顯示");
        //Application->MessageBox("Outlet 8 Current","show");
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_8_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 8 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(500);
        Application->ProcessMessages();

     //   if (Application->MessageBox("Outlet 8 Current is OK?","Check Outlet 8 Current",MB_OKCANCEL) == IDCANCEL)  //Check the Outlet 8 Current is OK again?
        if(Result3->Caption == "FAIL")
        {
              //  Result3->Caption = "FAIL";
                if(EU->Checked == true)
                {
                        Shape8->Brush->Color = clRed;
                }
                if(US->Checked == true)
                {
                        Shape16->Brush->Color = clRed;
                }
                Memo1->Lines->Add("Outlet 8 Current is Wrong");
                if(US->Checked == true)
                {
                        updateLogFile("Fail-US-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                }
                else if(EU->Checked == true)
                {
                        updateLogFile("Fail-EU-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                }
        }
        else
        {
               if(i==0)
               {
                   z18->Caption = "8";
               }
               if(i==1)
               {
                   z28->Caption = "8";
               }
               if(i==2)
               {
                   z38->Caption = "8";
               }
               if(i==3)
               {
                   z48->Caption = "8";
               }
               if(i==4)
               {
                   z58->Caption = "8";
               }
               if(i==5)
               {
                   z68->Caption = "8";
               }
                if(EU->Checked == true && Shape8->Brush->Color != clRed)
                {
                        Shape8->Brush->Color = clLime;
                        TelnetForm->Button20->Enabled = false;
                }
                if(US->Checked == true && Shape16->Brush->Color != clRed)
                {
                        Shape16->Brush->Color = clLime;
                        TelnetForm->Button28->Enabled = false;
                }
        }
        if(EU->Checked == true)
        {       if(i==4)
                {
                        if(Result20->Caption == "FAIL")
                        {
                                Result3->Caption = "FAIL";
                                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                                IdTelnetDemo->Disconnect();
                                return;
                        }
                        else
                        {
                                Result3->Caption = "PASS";
                                TelnetForm->Button30->Enabled = true;
                                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                        }
                        TelnetForm->Button4->Enabled = false;
                        IdTelnetDemo->Disconnect();
                        return;
                }
        }
      /*  if(EU->Checked == true)
        {
           if(i==0)
           {
                if (Result3->Caption == "FAIL")
                {
                        TelnetForm->Button4->Enabled = true;
                        IdTelnetDemo->Disconnect();
                        return;
                }
           }
           if(i==1)
           {
                if (Result3->Caption == "FAIL")
                {
                        TelnetForm->Button4->Enabled = true;
                        IdTelnetDemo->Disconnect();
                        return;
                }
           }
           if(i==2)
           {
                if (Result3->Caption == "FAIL")
                {
                        TelnetForm->Button4->Enabled = true;
                        IdTelnetDemo->Disconnect();
                        return;
                }
                Result3->Caption = "PASS";
                IdTelnetDemo->Disconnect();
                return;
           }     */

//----------------------end outlet8 power test-----------------------------------

//----------------------start outlet9 power test-----------------------------------
    if(US->Checked == true)
    {
         Power->Caption = "";
         Current->Caption = "";
         Result3->Caption = "";

         IdTelnetDemo->SendCh('\r');
         if(Shape17->Brush->Color != clRed)
         {
             Shape17->Brush->Color = clYellow;
         }

         ::Sleep(500);
         Application->ProcessMessages();
         SendCommand(set_outlet_9_on);
         ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
         //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 9 -v 1");
         //Memo1->Lines->Add("");
         //IdTelnetDemo->SendCh('\n');
         Memo1Display();

         /*  ::Sleep(2000);
         Application->ProcessMessages();

         ::Sleep(1000);
         Application->ProcessMessages();

         IdTelnetDemo->SendCh('\r');
         SendCommand(show_outlet_9_status);
         Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 9");
         Memo1->Lines->Add("");
         IdTelnetDemo->SendCh('\n');
         Memo1Display();   */

        for(j=0;j<3;j++)
        {
                if(j==0)
                {//Application->MessageBox("1","show");
                ::Sleep(3000);
                Application->ProcessMessages(); }
                if(j==1)
                {//Application->MessageBox("1","show");
                ::Sleep(2000);
                Application->ProcessMessages(); }
                if(j==2)
                {
                        IdTelnetDemo->SendCh('\r');
                        SendCommand(show_outlet_9_status);
                        ::Sleep(500);
                        Application->ProcessMessages();
                        SendCommand(Enter);
                        //Memo1->Lines->Add("Pakedge-PDU$ show outlet-status -o 9");
                        //Memo1->Lines->Add("");
                        //IdTelnetDemo->SendCh('\n');
                        ::Sleep(1000);
                        Application->ProcessMessages();
                        Memo1Display();
                }
        }
        int num38=Memo1->Lines->Count;
        ::Sleep(1500);
        Application->ProcessMessages();
        String yyy38=Memo1->Lines->Strings[num38-1]+Memo1->Lines->Strings[num38]+Memo1->Lines->Strings[num38-2]+Memo1->Lines->Strings[num38+1];
        //char *p38 = yyy38.c_str();

        String right380 = yyy38.SubString(yyy38.Pos("power")+8,10);
        String left380 = right380.SubString(0,right380.Pos("W")-2);
        String left009 = left380+outlet11+left250;
        Power->Caption = left009;
        float left381 = StrToFloat(left380);
        if(i==0)
        {
                if(left381<b || left381>a)
                {
                        Result3->Caption = "FAIL";
                        Result20->Caption = "FAIL";
                        TelnetForm->Button29->Enabled = true;
                }
                else  Edit40->Text = left380;
        }
        if(i==1)
        {
                if(left381<b || left381>a)
                {
                        Result3->Caption = "FAIL";
                        Result20->Caption = "FAIL";
                        TelnetForm->Button29->Enabled = true;
                }
                else  Edit49->Text = left380;
        }
        if(i==2)
        {
                if(left381<b || left381>a)
                {
                        Result3->Caption = "FAIL";
                        Result20->Caption = "FAIL";
                        TelnetForm->Button29->Enabled = true;
                }
                else  Edit58->Text = left380;
        }
        if(i==3)
        {
                if(left381<b || left381>a)
                {
                        Result3->Caption = "FAIL";
                        Result20->Caption = "FAIL";
                        TelnetForm->Button29->Enabled = true;
                }
                else  Edit99->Text = left380;
        }
        if(i==4)
        {
                if(left381<b || left381>a)
                {
                        Result3->Caption = "FAIL";
                        Result20->Caption = "FAIL";
                        TelnetForm->Button29->Enabled = true;
                }
                else  Edit109->Text = left380;
        }
        if(i==5)
        {
                if(left381<b || left381>a)
                {
                        Result3->Caption = "FAIL";
                        Result20->Caption = "FAIL";
                        TelnetForm->Button29->Enabled = true;
                }
                else  Edit119->Text = left380;
        }

        String right382 =  yyy38.SubString(yyy38.Pos("current")+10,10);
        String left382 = right382.SubString(0,right382.Pos("A")-2);
        String left0019 = left382+outlet11+left251;
        Current->Caption = left0019;
        float left383 = StrToFloat(left382);
        if(i==0)
        {
                if(left383<m || left383>n)
                {
                        Result3->Caption = "FAIL";
                        Result20->Caption = "FAIL";
                        TelnetForm->Button29->Enabled = true;
                }
                else  Edit9->Text = left382;
        }
        if(i==1)
        {
                if(left383<m || left383>n)
                {
                        Result3->Caption = "FAIL";
                        Result20->Caption = "FAIL";
                        TelnetForm->Button29->Enabled = true;
                }
                else  Edit18->Text = left382;
        }
        if(i==2)
        {
                if(left383<m || left383>n)
                {
                        Result3->Caption = "FAIL";
                        Result20->Caption = "FAIL";
                        TelnetForm->Button29->Enabled = true;
                }
                else  Edit27->Text = left382;
        }
        if(i==3)
        {
                if(left383<m || left383>n)
                {
                        Result3->Caption = "FAIL";
                        Result20->Caption = "FAIL";
                        TelnetForm->Button29->Enabled = true;
                }
                else  Edit69->Text = left382;
        }
        if(i==4)
        {
                if(left383<m || left383>n)
                {
                        Result3->Caption = "FAIL";
                        Result20->Caption = "FAIL";
                        TelnetForm->Button29->Enabled = true;
                }
                else  Edit79->Text = left382;
        }
        if(i==5)
        {
                if(left383<m || left383>n)
                {
                        Result3->Caption = "FAIL";
                        Result20->Caption = "FAIL";
                        TelnetForm->Button29->Enabled = true;
                }
                else  Edit89->Text = left382;
        }
       //Application->MessageBox("輸出端口9電流","顯示");
       //Application->MessageBox("Outlet 9 Current","show");
       ::Sleep(500);
       Application->ProcessMessages();

       IdTelnetDemo->SendCh('\r');
       SendCommand(set_outlet_9_off);
       ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
       //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 9 -v 0");
       //Memo1->Lines->Add("");
       //IdTelnetDemo->SendCh('\n');
       Memo1Display();

       ::Sleep(500);
       Application->ProcessMessages();
       //    if (Application->MessageBox("Outlet 9 Current is OK?","Check Outlet 9 Current",MB_OKCANCEL) == IDCANCEL)  //Check the Outlet 9 Current is OK again?
       if(Result3->Caption == "FAIL")
       {
             //   Result3->Caption = "FAIL";
                Shape17->Brush->Color = clRed;
                Memo1->Lines->Add("Outlet 9 Current is Wrong");
                updateLogFile("Fail-US-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
                TelnetForm->Button4->Enabled = true;
       }
       else
       {
                if(i==0)
               {
                    z19->Caption = "9";
               }
               if(i==1)
               {
                   z29->Caption = "9";
               }
               if(i==2)
               {
                   z39->Caption = "9";
               }
               if(i==3)
               {
                    z49->Caption = "9";
               }
               if(i==4)
               {
                   z59->Caption = "9";
               }
               if(i==5)
               {
                   z69->Caption = "9";
               }
               if(Shape17->Brush->Color != clRed)
               {
                   Shape17->Brush->Color = clLime;
               }
                TelnetForm->Button29->Enabled = false;
       }


     /*  if(i==0)
       {
                if (Result3->Caption == "FAIL")
                {
                        TelnetForm->Button4->Enabled = true;
                        IdTelnetDemo->Disconnect();
                        return;
                }
       }
       if(i==1)
       {
                if (Result3->Caption == "FAIL")
                {
                        TelnetForm->Button4->Enabled = true;
                        IdTelnetDemo->Disconnect();
                        return;
                }
       }    */

       if(i==5)
       {
                if (Result20->Caption == "FAIL")
                {
                        Result20->Caption = "FAIL";
                        char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                        WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                        IdTelnetDemo->Disconnect();
                        return;
                }
                else
                {
                        Result3->Caption = "PASS";
                        TelnetForm->Button30->Enabled = true;
                        char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                        WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                }
                TelnetForm->Button4->Enabled = false;
                IdTelnetDemo->Disconnect();
                return;
       }
    }
  }

//----------------------end outlet9 power test-----------------------------------
     //   Result3->Caption = "PASS";

        if(US->Checked == true)
        {
                updateLogFile("Pass-US-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
        }
        else if(EU->Checked == true)
        {
                updateLogFile("Pass-EU-AC Load Test.txt", Memo1->Lines->Text, Result3->Caption);
        }

}
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



void __fastcall TTelnetForm::Button13Click(TObject *Sender)
{
        char *x=z11->Caption.c_str();
        char *y=z21->Caption.c_str();
        char *z=z31->Caption.c_str();
        char *u=z41->Caption.c_str();
        char *v=z51->Caption.c_str();
        Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape1->Brush->Color = clYellow;
        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 1 -v 0";
        String set_outlet_1_on = "set outlet-power -o 1 -v 1";
        String show_outlet_1_status = "show outlet-status -o 1";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        if(strcmp(val1,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                 WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape1->Brush->Color = clRed;
                }
                else Edit32->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape1->Brush->Color = clRed;
                }
                else Edit1->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape1->Brush->Color = clRed;
                        z11->Caption = "1";
                        TelnetForm->Button13->Enabled = true;
                }
                else
                {
                        Shape1->Brush->Color = clLime;
                        z11->Caption = "";
                        TelnetForm->Button30->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val1,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape1->Brush->Color = clRed;
                }
                else Edit41->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape1->Brush->Color = clRed;
                }
                else Edit10->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z21->Caption = "1";
                        Shape1->Brush->Color = clRed;
                        TelnetForm->Button13->Enabled = true;
                }
                else
                {
                        if(Shape1->Brush->Color != clRed)
                        {
                              Shape1->Brush->Color = clLime;
                              TelnetForm->Button13->Enabled = false;
                        }
                        z21->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val1,z)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape1->Brush->Color = clRed;
                }
                else Edit50->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape1->Brush->Color = clRed;
                }
                else Edit19->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z31->Caption = "1";
                        Shape1->Brush->Color = clRed;
                        TelnetForm->Button13->Enabled = true;
                }
                else
                {
                        if(Shape1->Brush->Color != clRed)
                        {
                              Shape1->Brush->Color = clLime;
                              TelnetForm->Button13->Enabled = false;
                        }
                        z31->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val1,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape1->Brush->Color = clRed;
                }
                else Edit91->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape1->Brush->Color = clRed;
                }
                else Edit61->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z41->Caption = "1";
                        Shape1->Brush->Color = clRed;
                        TelnetForm->Button13->Enabled = true;
                }
                else
                {
                        if(Shape1->Brush->Color != clRed)
                        {
                              Shape1->Brush->Color = clLime;
                              TelnetForm->Button13->Enabled = false;
                        }
                        z41->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val1,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape1->Brush->Color = clRed;
                }
                else Edit101->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape1->Brush->Color = clRed;
                }
                else Edit71->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z51->Caption = "1";
                        Shape1->Brush->Color = clRed;
                        TelnetForm->Button13->Enabled = true;
                }
                else
                {
                        if(Shape1->Brush->Color != clRed)
                        {
                              Shape1->Brush->Color = clLime;
                              TelnetForm->Button13->Enabled = false;
                        }
                        z51->Caption = "";
                }
                Result20->Caption = "";
        }
        if(Shape1->Brush->Color == clLime && Shape2->Brush->Color == clLime &&Shape3->Brush->Color == clLime &&Shape4->Brush->Color == clLime &&Shape5->Brush->Color == clLime &&Shape6->Brush->Color == clLime &&Shape7->Brush->Color == clLime &&Shape8->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button14Click(TObject *Sender)
{
        char *x=z12->Caption.c_str();
        char *y=z22->Caption.c_str();
        char *z=z32->Caption.c_str();
        char *u=z42->Caption.c_str();
        char *v=z52->Caption.c_str();
        Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape2->Brush->Color = clYellow;
        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 2 -v 0";
        String set_outlet_1_on = "set outlet-power -o 2 -v 1";
        String show_outlet_1_status = "show outlet-status -o 2";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        if(strcmp(val2,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape2->Brush->Color = clRed;
                }
                else Edit33->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape2->Brush->Color = clRed;
                }
                else Edit2->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape2->Brush->Color = clRed;
                        z12->Caption = "2";
                        TelnetForm->Button14->Enabled = true;
                }
                else
                {
                        Shape2->Brush->Color = clLime;
                        z12->Caption = "";
                        TelnetForm->Button14->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val2,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape2->Brush->Color = clRed;
                }
                else Edit42->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape2->Brush->Color = clRed;
                }
                else Edit11->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z22->Caption = "2";
                        Shape2->Brush->Color = clRed;
                        TelnetForm->Button14->Enabled = true;
                }
                else
                {
                        if(Shape2->Brush->Color != clRed)
                        {
                              Shape2->Brush->Color = clLime;
                              TelnetForm->Button14->Enabled = false;
                        }
                        z22->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val2,z)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=115;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape2->Brush->Color = clRed;
                }
                else Edit51->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape2->Brush->Color = clRed;
                }
                else Edit20->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z32->Caption = "2";
                        Shape2->Brush->Color = clRed;
                        TelnetForm->Button14->Enabled = true;
                }
                else
                {
                        if(Shape2->Brush->Color != clRed)
                        {
                              Shape2->Brush->Color = clLime;
                              TelnetForm->Button14->Enabled = false;
                        }
                        z32->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val2,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=115;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape2->Brush->Color = clRed;
                }
               else Edit92->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape2->Brush->Color = clRed;
                }
                else Edit62->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z42->Caption = "2";
                        Shape2->Brush->Color = clRed;
                        TelnetForm->Button14->Enabled = true;
                }
                else
                {
                        if(Shape2->Brush->Color != clRed)
                        {
                              Shape2->Brush->Color = clLime;
                              TelnetForm->Button14->Enabled = false;
                        }
                        z42->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val2,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=115;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape2->Brush->Color = clRed;
                }
                else Edit102->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape2->Brush->Color = clRed;
                }
                else Edit72->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z52->Caption = "2";
                        Shape2->Brush->Color = clRed;
                        TelnetForm->Button14->Enabled = true;
                }
                else
                {
                        if(Shape2->Brush->Color != clRed)
                        {
                              Shape2->Brush->Color = clLime;
                              TelnetForm->Button14->Enabled = false;
                        }
                        z52->Caption = "";
                }
                Result20->Caption = "";
        }
        if(Shape1->Brush->Color == clLime && Shape2->Brush->Color == clLime &&Shape3->Brush->Color == clLime &&Shape4->Brush->Color == clLime &&Shape5->Brush->Color == clLime &&Shape6->Brush->Color == clLime &&Shape7->Brush->Color == clLime &&Shape8->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button15Click(TObject *Sender)
{
        char *x=z13->Caption.c_str();
        char *y=z23->Caption.c_str();
        char *z=z33->Caption.c_str();
        char *u=z43->Caption.c_str();
        char *v=z53->Caption.c_str();
        Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape3->Brush->Color = clYellow;
        ::Sleep(1000);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 3 -v 0";
        String set_outlet_1_on = "set outlet-power -o 3 -v 1";
        String show_outlet_1_status = "show outlet-status -o 3";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        IdTelnetDemo->SendCh('\n');
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();
        if(strcmp(val3,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                 WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape3->Brush->Color = clRed;
                }
                else Edit34->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape3->Brush->Color = clRed;
                }
                else Edit3->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape3->Brush->Color = clRed;
                        z13->Caption = "3";
                        TelnetForm->Button15->Enabled = true;
                }
                else
                {
                        Shape3->Brush->Color = clLime;
                        z13->Caption = "";
                        TelnetForm->Button15->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val3,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=115;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape3->Brush->Color = clRed;
                }
               else Edit43->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape3->Brush->Color = clRed;
                }
                else Edit12->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z23->Caption = "3";
                        Shape3->Brush->Color = clRed;
                        TelnetForm->Button15->Enabled = true;
                }
                else
                {
                        if(Shape3->Brush->Color != clRed)
                        {
                              Shape3->Brush->Color = clLime;
                              TelnetForm->Button15->Enabled = false;
                        }
                        z23->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val3,z)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=115;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape3->Brush->Color = clRed;
                }
                else Edit52->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape3->Brush->Color = clRed;
                }
                else Edit21->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z33->Caption = "3";
                        Shape3->Brush->Color = clRed;
                        TelnetForm->Button15->Enabled = true;
                }
                else
                {
                        if(Shape3->Brush->Color != clRed)
                        {
                              Shape1->Brush->Color = clLime;
                              TelnetForm->Button15->Enabled = false;
                        }
                        z33->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val3,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=115;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape3->Brush->Color = clRed;
                }
                else Edit93->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape3->Brush->Color = clRed;
                }
                else Edit63->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z43->Caption = "3";
                        Shape3->Brush->Color = clRed;
                        TelnetForm->Button15->Enabled = true;
                }
                else
                {
                        if(Shape3->Brush->Color != clRed)
                        {
                              Shape1->Brush->Color = clLime;
                              TelnetForm->Button15->Enabled = false;
                        }
                        z43->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val3,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=115;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape3->Brush->Color = clRed;
                }
                else Edit103->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape3->Brush->Color = clRed;
                }
                else Edit73->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z53->Caption = "3";
                        Shape3->Brush->Color = clRed;
                        TelnetForm->Button15->Enabled = true;
                }
                else
                {
                        if(Shape3->Brush->Color != clRed)
                        {
                              Shape1->Brush->Color = clLime;
                              TelnetForm->Button15->Enabled = false;
                        }
                        z53->Caption = "";
                }
                Result20->Caption = "";
        }
        if(Shape1->Brush->Color == clLime && Shape2->Brush->Color == clLime &&Shape3->Brush->Color == clLime &&Shape4->Brush->Color == clLime &&Shape5->Brush->Color == clLime &&Shape6->Brush->Color == clLime &&Shape7->Brush->Color == clLime &&Shape8->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button16Click(TObject *Sender)
{
        char *x=z14->Caption.c_str();
        char *y=z24->Caption.c_str();
        char *z=z34->Caption.c_str();
        char *u=z44->Caption.c_str();
        char *v=z54->Caption.c_str();
         Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape4->Brush->Color = clYellow;
        ::Sleep(1000);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 4 -v 0";
        String set_outlet_1_on = "set outlet-power -o 4 -v 1";
        String show_outlet_1_status = "show outlet-status -o 4";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();
        if(strcmp(val4,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape4->Brush->Color = clRed;
                }
                else Edit35->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape4->Brush->Color = clRed;
                }
                else Edit4->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape4->Brush->Color = clRed;
                        z14->Caption = "4";
                        TelnetForm->Button16->Enabled = true;
                }
                else
                {
                        Shape4->Brush->Color = clLime;
                        z14->Caption = "";
                        TelnetForm->Button16->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val4,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape4->Brush->Color = clRed;
                }
                else Edit44->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape4->Brush->Color = clRed;
                }
                else Edit13->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z24->Caption = "4";
                        Shape4->Brush->Color = clRed;
                        TelnetForm->Button16->Enabled = true;
                }
                else
                {
                        if(Shape4->Brush->Color != clRed)
                        {
                              Shape4->Brush->Color = clLime;
                              TelnetForm->Button16->Enabled = false;
                        }
                        z24->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val4,z)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape4->Brush->Color = clRed;
                }
               else Edit53->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape4->Brush->Color = clRed;
                }
                else Edit22->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z34->Caption = "4";
                        Shape4->Brush->Color = clRed;
                        TelnetForm->Button16->Enabled = true;
                }
                else
                {
                        if(Shape4->Brush->Color != clRed)
                        {
                              Shape4->Brush->Color = clLime;
                              TelnetForm->Button16->Enabled = false;
                        }
                        z34->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val4,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape4->Brush->Color = clRed;
                }
               else Edit94->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape4->Brush->Color = clRed;
                }
                else Edit64->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z44->Caption = "4";
                        Shape4->Brush->Color = clRed;
                        TelnetForm->Button16->Enabled = true;
                }
                else
                {
                        if(Shape4->Brush->Color != clRed)
                        {
                              Shape4->Brush->Color = clLime;
                              TelnetForm->Button16->Enabled = false;
                        }
                        z44->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val4,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape4->Brush->Color = clRed;
                }
                else Edit104->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape4->Brush->Color = clRed;
                }
                else Edit74->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z54->Caption = "4";
                        Shape4->Brush->Color = clRed;
                        TelnetForm->Button16->Enabled = true;
                }
                else
                {
                        if(Shape4->Brush->Color != clRed)
                        {
                              Shape4->Brush->Color = clLime;
                              TelnetForm->Button16->Enabled = false;
                        }
                        z54->Caption = "";
                }
                Result20->Caption = "";
        }
        if(Shape1->Brush->Color == clLime && Shape2->Brush->Color == clLime &&Shape3->Brush->Color == clLime &&Shape4->Brush->Color == clLime &&Shape5->Brush->Color == clLime &&Shape6->Brush->Color == clLime &&Shape7->Brush->Color == clLime &&Shape8->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button17Click(TObject *Sender)
{
        char *x=z15->Caption.c_str();
        char *y=z25->Caption.c_str();
        char *z=z35->Caption.c_str();
        char *u=z45->Caption.c_str();
        char *v=z55->Caption.c_str();
        Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape5->Brush->Color = clYellow;
        ::Sleep(1000);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 5 -v 0";
        String set_outlet_1_on = "set outlet-power -o 5 -v 1";
        String show_outlet_1_status = "show outlet-status -o 5";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);;
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();
        if(strcmp(val5,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                 WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape5->Brush->Color = clRed;
                }
                else Edit36->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape5->Brush->Color = clRed;
                }
                else Edit5->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape5->Brush->Color = clRed;
                        z15->Caption = "5";
                        TelnetForm->Button17->Enabled = true;
                }
                else
                {
                        Shape5->Brush->Color = clLime;
                        z15->Caption = "";
                        TelnetForm->Button17->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val5,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape5->Brush->Color = clRed;
                }
                else Edit45->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape5->Brush->Color = clRed;
                }
                else Edit14->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z25->Caption = "5";
                        Shape5->Brush->Color = clRed;
                        TelnetForm->Button17->Enabled = true;
                }
                else
                {
                        if(Shape5->Brush->Color != clRed)
                        {
                              Shape5->Brush->Color = clLime;
                              TelnetForm->Button17->Enabled = false;
                        }
                        z25->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val5,z)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape5->Brush->Color = clRed;
                }
                else Edit54->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape5->Brush->Color = clRed;
                }
                else Edit23->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z35->Caption = "5";
                        Shape5->Brush->Color = clRed;
                        TelnetForm->Button17->Enabled = true;
                }
                else
                {
                        if(Shape5->Brush->Color != clRed)
                        {
                              Shape5->Brush->Color = clLime;
                              TelnetForm->Button17->Enabled = false;
                        }
                        z35->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val5,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape5->Brush->Color = clRed;
                }
                else Edit95->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape5->Brush->Color = clRed;
                }
                else Edit65->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape5->Brush->Color = clRed;
                        z45->Caption = "5";
                        TelnetForm->Button17->Enabled = true;
                }
                else
                {
                        Shape5->Brush->Color = clLime;
                        z45->Caption = "";
                        TelnetForm->Button17->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val5,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape5->Brush->Color = clRed;
                }
                else Edit105->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape5->Brush->Color = clRed;
                }
                else Edit75->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape5->Brush->Color = clRed;
                        z55->Caption = "5";
                        TelnetForm->Button17->Enabled = true;
                }
                else
                {
                        Shape5->Brush->Color = clLime;
                        z55->Caption = "";
                        TelnetForm->Button17->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(Shape1->Brush->Color == clLime && Shape2->Brush->Color == clLime &&Shape3->Brush->Color == clLime &&Shape4->Brush->Color == clLime &&Shape5->Brush->Color == clLime &&Shape6->Brush->Color == clLime &&Shape7->Brush->Color == clLime &&Shape8->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button18Click(TObject *Sender)
{
        char *x=z16->Caption.c_str();
        char *y=z26->Caption.c_str();
        char *z=z36->Caption.c_str();
        char *u=z46->Caption.c_str();
        char *v=z56->Caption.c_str();
         Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape6->Brush->Color = clYellow;
        ::Sleep(1000);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 6 -v 0";
        String set_outlet_1_on = "set outlet-power -o 6 -v 1";
        String show_outlet_1_status = "show outlet-status -o 6";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();
        if(strcmp(val6,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                 WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape6->Brush->Color = clRed;
                }
                else Edit37->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape6->Brush->Color = clRed;
                }
                else Edit6->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape6->Brush->Color = clRed;
                        z16->Caption = "6";
                        TelnetForm->Button18->Enabled = true;
                }
                else
                {
                        Shape6->Brush->Color = clLime;
                        z16->Caption = "";
                        TelnetForm->Button18->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val6,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape6->Brush->Color = clRed;
                }
                else Edit46->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape6->Brush->Color = clRed;
                }
                else Edit15->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z26->Caption = "6";
                        Shape6->Brush->Color = clRed;
                        TelnetForm->Button18->Enabled = true;
                }
                else
                {
                        if(Shape6->Brush->Color != clRed)
                        {
                              Shape6->Brush->Color = clLime;
                              TelnetForm->Button18->Enabled = false;
                        }
                        z26->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val6,z)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape6->Brush->Color = clRed;
                }
                else Edit55->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape6->Brush->Color = clRed;
                }
                else Edit24->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z36->Caption = "6";
                        Shape6->Brush->Color = clRed;
                        TelnetForm->Button18->Enabled = true;
                }
                else
                {
                        if(Shape6->Brush->Color != clRed)
                        {
                              Shape6->Brush->Color = clLime;
                              TelnetForm->Button18->Enabled = false;
                        }
                        z36->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val6,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape6->Brush->Color = clRed;
                }
                else Edit96->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape6->Brush->Color = clRed;
                }
                else Edit66->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape6->Brush->Color = clRed;
                        z46->Caption = "6";
                        TelnetForm->Button18->Enabled = true;
                }
                else
                {
                        Shape6->Brush->Color = clLime;
                        z46->Caption = "";
                        TelnetForm->Button18->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val6,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape6->Brush->Color = clRed;
                }
                else Edit106->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape6->Brush->Color = clRed;
                }
                else Edit76->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape6->Brush->Color = clRed;
                        z56->Caption = "6";
                        TelnetForm->Button18->Enabled = true;
                }
                else
                {
                        Shape6->Brush->Color = clLime;
                        z56->Caption = "";
                        TelnetForm->Button18->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(Shape1->Brush->Color == clLime && Shape2->Brush->Color == clLime &&Shape3->Brush->Color == clLime &&Shape4->Brush->Color == clLime &&Shape5->Brush->Color == clLime &&Shape6->Brush->Color == clLime &&Shape7->Brush->Color == clLime &&Shape8->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button19Click(TObject *Sender)
{
        char *x=z17->Caption.c_str();
        char *y=z27->Caption.c_str();
        char *z=z37->Caption.c_str();
        char *u=z47->Caption.c_str();
        char *v=z57->Caption.c_str();
         Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape7->Brush->Color = clYellow;
        ::Sleep(1000);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 7 -v 0";
        String set_outlet_1_on = "set outlet-power -o 7 -v 1";
        String show_outlet_1_status = "show outlet-status -o 7";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();
        if(strcmp(val7,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                 WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape7->Brush->Color = clRed;
                }
                else Edit38->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape7->Brush->Color = clRed;
                }
                else Edit7->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape7->Brush->Color = clRed;
                        z17->Caption = "7";
                        TelnetForm->Button19->Enabled = true;
                }
                else
                {
                        Shape7->Brush->Color = clLime;
                        z17->Caption = "";
                        TelnetForm->Button19->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val7,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape7->Brush->Color = clRed;
                }
                else Edit47->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape7->Brush->Color = clRed;
                }
                else Edit16->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z27->Caption = "7";
                        Shape7->Brush->Color = clRed;
                        TelnetForm->Button19->Enabled = true;
                }
                else
                {
                        if(Shape7->Brush->Color != clRed)
                        {
                              Shape7->Brush->Color = clLime;
                              TelnetForm->Button19->Enabled = false;
                        }
                        z27->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val7,z)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape7->Brush->Color = clRed;
                }
                else Edit56->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape7->Brush->Color = clRed;
                }
                else Edit25->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z37->Caption = "7";
                        Shape7->Brush->Color = clRed;
                        TelnetForm->Button19->Enabled = true;
                }
                else
                {
                        if(Shape7->Brush->Color != clRed)
                        {
                              Shape7->Brush->Color = clLime;
                              TelnetForm->Button19->Enabled = false;
                        }
                        z37->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val7,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape7->Brush->Color = clRed;
                }
                else Edit97->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape7->Brush->Color = clRed;
                }
                else Edit67->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape7->Brush->Color = clRed;
                        z47->Caption = "7";
                        TelnetForm->Button19->Enabled = true;
                }
                else
                {
                        Shape7->Brush->Color = clLime;
                        z47->Caption = "";
                        TelnetForm->Button19->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val7,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape7->Brush->Color = clRed;
                }
                else Edit107->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape7->Brush->Color = clRed;
                }
                else Edit77->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape7->Brush->Color = clRed;
                        z57->Caption = "7";
                        TelnetForm->Button19->Enabled = true;
                }
                else
                {
                        Shape7->Brush->Color = clLime;
                        z57->Caption = "";
                        TelnetForm->Button19->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(Shape1->Brush->Color == clLime && Shape2->Brush->Color == clLime &&Shape3->Brush->Color == clLime &&Shape4->Brush->Color == clLime &&Shape5->Brush->Color == clLime &&Shape6->Brush->Color == clLime &&Shape7->Brush->Color == clLime &&Shape8->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button20Click(TObject *Sender)
{
        char *x=z18->Caption.c_str();
        char *y=z28->Caption.c_str();
        char *z=z38->Caption.c_str();
        char *u=z48->Caption.c_str();
        char *v=z58->Caption.c_str();
        Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape8->Brush->Color = clYellow;
        ::Sleep(1000);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 8 -v 0";
        String set_outlet_1_on = "set outlet-power -o 8 -v 1";
        String show_outlet_1_status = "show outlet-status -o 8";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();
        if(strcmp(val8,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape8->Brush->Color = clRed;
                }
                else Edit39->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape8->Brush->Color = clRed;
                }
                else Edit8->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape8->Brush->Color = clRed;
                        z18->Caption = "8";
                        TelnetForm->Button20->Enabled = true;
                }
                else
                {
                        Shape8->Brush->Color = clLime;
                        z18->Caption = "";
                        TelnetForm->Button20->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val8,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape8->Brush->Color = clRed;
                }
                else Edit48->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape8->Brush->Color = clRed;
                }
                else Edit17->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z28->Caption = "8";
                        Shape8->Brush->Color = clRed;
                        TelnetForm->Button20->Enabled = true;
                }
                else
                {
                        if(Shape8->Brush->Color != clRed)
                        {
                              Shape8->Brush->Color = clLime;
                              TelnetForm->Button20->Enabled = false;
                        }
                        z28->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val8,z)!=0)
        {
                
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape8->Brush->Color = clRed;
                }
                else Edit57->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape8->Brush->Color = clRed;
                }
                else Edit26->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z38->Caption = "8";
                        Shape8->Brush->Color = clRed;
                        TelnetForm->Button20->Enabled = true;
                }
                else
                {
                        if(Shape8->Brush->Color != clRed)
                        {
                              Shape8->Brush->Color = clLime;
                              TelnetForm->Button20->Enabled = false;
                        }
                        z38->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val8,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape8->Brush->Color = clRed;
                }
                else Edit98->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape8->Brush->Color = clRed;
                }
                else Edit68->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape8->Brush->Color = clRed;
                        z48->Caption = "8";
                        TelnetForm->Button20->Enabled = true;
                }
                else
                {
                        Shape8->Brush->Color = clLime;
                        z48->Caption = "";
                        TelnetForm->Button20->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val8,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=230;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape8->Brush->Color = clRed;
                }
                else Edit108->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape8->Brush->Color = clRed;
                }
                else Edit78->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape8->Brush->Color = clRed;
                        z58->Caption = "8";
                        TelnetForm->Button20->Enabled = true;
                }
                else
                {
                        Shape8->Brush->Color = clLime;
                        z58->Caption = "";
                        TelnetForm->Button20->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(Shape1->Brush->Color == clLime && Shape2->Brush->Color == clLime &&Shape3->Brush->Color == clLime &&Shape4->Brush->Color == clLime &&Shape5->Brush->Color == clLime &&Shape6->Brush->Color == clLime &&Shape7->Brush->Color == clLime &&Shape8->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button21Click(TObject *Sender)
{
        char *x=z11->Caption.c_str();
        char *y=z21->Caption.c_str();
        char *z=z31->Caption.c_str();
        char *u=z41->Caption.c_str();
        char *v=z51->Caption.c_str();
        char *w=z61->Caption.c_str();
        Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape9->Brush->Color = clYellow;
        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 1 -v 0";
        String set_outlet_1_on = "set outlet-power -o 1 -v 1";
        String show_outlet_1_status = "show outlet-status -o 1";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();
        if(strcmp(val1,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);

                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape9->Brush->Color = clRed;
                }
                else Edit32->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape9->Brush->Color = clRed;
                }
                else Edit1->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape9->Brush->Color = clRed;
                        z11->Caption = "1";
                        TelnetForm->Button21->Enabled = true;
                }
                else
                {
                        Shape9->Brush->Color = clLime;
                        z11->Caption = "";
                        TelnetForm->Button21->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val1,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape9->Brush->Color = clRed;
                }
                else Edit41->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape9->Brush->Color = clRed;
                }
                else Edit10->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z21->Caption = "1";
                        Shape9->Brush->Color = clRed;
                        TelnetForm->Button21->Enabled = true;
                }
                else
                {
                        if(Shape9->Brush->Color != clRed)
                        {
                              Shape9->Brush->Color = clLime;
                              TelnetForm->Button21->Enabled = false;
                        }
                        z21->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val1,z)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape9->Brush->Color = clRed;
                }
                else Edit50->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape9->Brush->Color = clRed;
                }
                else Edit19->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z31->Caption = "1";
                        Shape9->Brush->Color = clRed;
                        TelnetForm->Button21->Enabled = true;
                }
                else
                {
                        if(Shape9->Brush->Color != clRed)
                        {
                              Shape9->Brush->Color = clLime;
                              TelnetForm->Button21->Enabled = false;
                        }
                        z31->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val1,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape9->Brush->Color = clRed;
                }
                else Edit91->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape9->Brush->Color = clRed;
                }
                else Edit61->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z41->Caption = "1";
                        Shape9->Brush->Color = clRed;
                        TelnetForm->Button21->Enabled = true;
                }
                else
                {
                        if(Shape9->Brush->Color != clRed)
                        {
                              Shape9->Brush->Color = clLime;
                              TelnetForm->Button21->Enabled = false;
                        }
                        z41->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val1,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape9->Brush->Color = clRed;
                }
                else Edit101->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape9->Brush->Color = clRed;
                }
                else Edit71->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z51->Caption = "1";
                        Shape9->Brush->Color = clRed;
                        TelnetForm->Button21->Enabled = true;
                }
                else
                {
                        if(Shape9->Brush->Color != clRed)
                        {
                              Shape9->Brush->Color = clLime;
                              TelnetForm->Button21->Enabled = false;
                        }
                        z51->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val1,w)!=0)
        {
                char eucurr3_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x34,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, eucurr3_cmd, 11, &dw_Write, 0);
                I=14.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape9->Brush->Color = clRed;
                }
                else Edit111->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape9->Brush->Color = clRed;
                }
                else Edit81->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z61->Caption = "1";
                        Shape9->Brush->Color = clRed;
                        TelnetForm->Button21->Enabled = true;
                }
                else
                {
                        if(Shape9->Brush->Color != clRed)
                        {
                              Shape9->Brush->Color = clLime;
                              TelnetForm->Button21->Enabled = false;
                        }
                        z61->Caption = "";
                }
                Result20->Caption = "";
        }
        if(Shape9->Brush->Color == clLime && Shape10->Brush->Color == clLime &&Shape11->Brush->Color == clLime &&Shape12->Brush->Color == clLime &&Shape13->Brush->Color == clLime &&Shape14->Brush->Color == clLime &&Shape15->Brush->Color == clLime &&Shape16->Brush->Color == clLime &&Shape17->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button22Click(TObject *Sender)
{
        char *x=z12->Caption.c_str();
        char *y=z22->Caption.c_str();
        char *z=z32->Caption.c_str();
        char *u=z42->Caption.c_str();
        char *v=z52->Caption.c_str();
        char *w=z62->Caption.c_str();
        Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape10->Brush->Color = clYellow;
        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 2 -v 0";
        String set_outlet_1_on = "set outlet-power -o 2 -v 1";
        String show_outlet_1_status = "show outlet-status -o 2";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();
        if(strcmp(val2,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape10->Brush->Color = clRed;
                }
                else Edit33->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape10->Brush->Color = clRed;
                }
                else Edit2->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape10->Brush->Color = clRed;
                        z12->Caption = "2";
                        TelnetForm->Button22->Enabled = true;
                }
                else
                {
                        Shape10->Brush->Color = clLime;
                        z12->Caption = "";
                        TelnetForm->Button22->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val2,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape10->Brush->Color = clRed;
                }
                else Edit42->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape10->Brush->Color = clRed;
                }
                else Edit11->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z22->Caption = "2";
                        Shape10->Brush->Color = clRed;
                        TelnetForm->Button22->Enabled = true;
                }
                else
                {
                        if(Shape10->Brush->Color != clRed)
                        {
                              Shape10->Brush->Color = clLime;
                              TelnetForm->Button22->Enabled = false;
                        }
                        z22->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val2,z)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape10->Brush->Color = clRed;
                }
                else Edit51->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape10->Brush->Color = clRed;
                }
                else Edit20->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z32->Caption = "2";
                        Shape10->Brush->Color = clRed;
                        TelnetForm->Button22->Enabled = true;
                }
                else
                {
                        if(Shape10->Brush->Color != clRed)
                        {
                              Shape10->Brush->Color = clLime;
                              TelnetForm->Button22->Enabled = false;
                        }
                        z32->Caption = "";
                }
                Result20->Caption = "";
        }
         if(strcmp(val2,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape10->Brush->Color = clRed;
                }
                else Edit92->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape10->Brush->Color = clRed;
                }
                else Edit62->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z42->Caption = "2";
                        Shape10->Brush->Color = clRed;
                        TelnetForm->Button22->Enabled = true;
                }
                else
                {
                        if(Shape10->Brush->Color != clRed)
                        {
                              Shape10->Brush->Color = clLime;
                              TelnetForm->Button22->Enabled = false;
                        }
                        z42->Caption = "";
                }
                Result20->Caption = "";
        }
         if(strcmp(val2,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape10->Brush->Color = clRed;
                }
                else Edit102->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape10->Brush->Color = clRed;
                }
                else Edit72->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z52->Caption = "2";
                        Shape10->Brush->Color = clRed;
                        TelnetForm->Button22->Enabled = true;
                }
                else
                {
                        if(Shape10->Brush->Color != clRed)
                        {
                              Shape10->Brush->Color = clLime;
                              TelnetForm->Button22->Enabled = false;
                        }
                        z52->Caption = "";
                }
                Result20->Caption = "";
        }
         if(strcmp(val2,w)!=0)
        {
                char eucurr3_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x34,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, eucurr3_cmd, 11, &dw_Write, 0);
                I=14.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape10->Brush->Color = clRed;
                }
                else Edit112->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape10->Brush->Color = clRed;
                }
                else Edit82->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z62->Caption = "2";
                        Shape10->Brush->Color = clRed;
                        TelnetForm->Button22->Enabled = true;
                }
                else
                {
                        if(Shape10->Brush->Color != clRed)
                        {
                              Shape10->Brush->Color = clLime;
                              TelnetForm->Button22->Enabled = false;
                        }
                        z62->Caption = "";
                }
                Result20->Caption = "";
        }
       if(Shape9->Brush->Color == clLime && Shape10->Brush->Color == clLime &&Shape11->Brush->Color == clLime &&Shape12->Brush->Color == clLime &&Shape13->Brush->Color == clLime &&Shape14->Brush->Color == clLime &&Shape15->Brush->Color == clLime &&Shape16->Brush->Color == clLime &&Shape17->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button23Click(TObject *Sender)
{
        char *x=z13->Caption.c_str();
        char *y=z23->Caption.c_str();
        char *z=z33->Caption.c_str();
        char *u=z43->Caption.c_str();
        char *v=z53->Caption.c_str();
        char *w=z63->Caption.c_str();
         Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape11->Brush->Color = clYellow;
        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 3 -v 0";
        String set_outlet_1_on = "set outlet-power -o 3 -v 1";
        String show_outlet_1_status = "show outlet-status -o 3";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();
        if(strcmp(val3,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape11->Brush->Color = clRed;
                }
                else Edit34->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape11->Brush->Color = clRed;
                }
                else Edit3->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape11->Brush->Color = clRed;
                        z13->Caption = "3";
                        TelnetForm->Button23->Enabled = true;
                }
                else
                {
                        Shape11->Brush->Color = clLime;
                        z13->Caption = "";
                        TelnetForm->Button23->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val3,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape11->Brush->Color = clRed;
                }
                else Edit43->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape11->Brush->Color = clRed;
                }
                else Edit12->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z23->Caption = "3";
                        Shape11->Brush->Color = clRed;
                        TelnetForm->Button23->Enabled = true;
                }
                else
                {
                        if(Shape11->Brush->Color != clRed)
                        {
                              Shape11->Brush->Color = clLime;
                              TelnetForm->Button23->Enabled = false;
                        }
                        z23->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val3,z)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape11->Brush->Color = clRed;
                }
                else Edit52->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape11->Brush->Color = clRed;
                }
                else Edit21->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z33->Caption = "3";
                        Shape11->Brush->Color = clRed;
                        TelnetForm->Button23->Enabled = true;
                }
                else
                {
                        if(Shape11->Brush->Color != clRed)
                        {
                              Shape11->Brush->Color = clLime;
                              TelnetForm->Button23->Enabled = false;
                        }
                        z33->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val3,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape11->Brush->Color = clRed;
                }
                else Edit93->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape11->Brush->Color = clRed;
                }
                else Edit63->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z43->Caption = "3";
                        Shape11->Brush->Color = clRed;
                        TelnetForm->Button23->Enabled = true;
                }
                else
                {
                        if(Shape11->Brush->Color != clRed)
                        {
                              Shape11->Brush->Color = clLime;
                              TelnetForm->Button23->Enabled = false;
                        }
                        z43->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val3,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape11->Brush->Color = clRed;
                }
                else Edit103->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape11->Brush->Color = clRed;
                }
                else Edit73->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z53->Caption = "3";
                        Shape11->Brush->Color = clRed;
                        TelnetForm->Button23->Enabled = true;
                }
                else
                {
                        if(Shape11->Brush->Color != clRed)
                        {
                              Shape11->Brush->Color = clLime;
                              TelnetForm->Button23->Enabled = false;
                        }
                        z53->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val3,w)!=0)
        {
                char eucurr3_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x34,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, eucurr3_cmd, 11, &dw_Write, 0);
                I=14.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape11->Brush->Color = clRed;
                }
                else Edit113->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape11->Brush->Color = clRed;
                }
                else Edit83->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z63->Caption = "1";
                        Shape11->Brush->Color = clRed;
                        TelnetForm->Button23->Enabled = true;
                }
                else
                {
                        if(Shape11->Brush->Color != clRed)
                        {
                              Shape11->Brush->Color = clLime;
                              TelnetForm->Button23->Enabled = false;
                        }
                        z63->Caption = "";
                }
                Result20->Caption = "";
        }
        if(Shape9->Brush->Color == clLime && Shape10->Brush->Color == clLime &&Shape11->Brush->Color == clLime &&Shape12->Brush->Color == clLime &&Shape13->Brush->Color == clLime &&Shape14->Brush->Color == clLime &&Shape15->Brush->Color == clLime &&Shape16->Brush->Color == clLime &&Shape17->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button24Click(TObject *Sender)
{
        char *x=z14->Caption.c_str();
        char *y=z24->Caption.c_str();
        char *z=z34->Caption.c_str();
        char *u=z44->Caption.c_str();
        char *v=z54->Caption.c_str();
        char *w=z64->Caption.c_str();
         Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape12->Brush->Color = clYellow;
        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 4 -v 0";
        String set_outlet_1_on = "set outlet-power -o 4 -v 1";
        String show_outlet_1_status = "show outlet-status -o 4";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();
        if(strcmp(val4,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape12->Brush->Color = clRed;
                }
                else Edit35->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape12->Brush->Color = clRed;
                }
                else Edit4->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape12->Brush->Color = clRed;
                        z14->Caption = "4";
                        TelnetForm->Button24->Enabled = true;
                }
                else
                {
                        Shape12->Brush->Color = clLime;
                        z14->Caption = "";
                        TelnetForm->Button24->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val4,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape12->Brush->Color = clRed;
                }
                else Edit44->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape12->Brush->Color = clRed;
                }
                else Edit13->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z24->Caption = "4";
                        Shape12->Brush->Color = clRed;
                        TelnetForm->Button24->Enabled = true;
                }
                else
                {
                        if(Shape12->Brush->Color != clRed)
                        {
                              Shape12->Brush->Color = clLime;
                              TelnetForm->Button24->Enabled = false;
                        }
                        z24->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val4,z)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape12->Brush->Color = clRed;
                }
                else Edit53->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape12->Brush->Color = clRed;
                }
                else Edit22->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z34->Caption = "4";
                        Shape12->Brush->Color = clRed;
                        TelnetForm->Button24->Enabled = true;
                }
                else
                {
                        if(Shape12->Brush->Color != clRed)
                        {
                              Shape12->Brush->Color = clLime;
                              TelnetForm->Button24->Enabled = false;
                        }
                        z34->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val4,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape12->Brush->Color = clRed;
                }
                else Edit94->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape12->Brush->Color = clRed;
                }
                else Edit64->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z44->Caption = "4";
                        Shape12->Brush->Color = clRed;
                        TelnetForm->Button24->Enabled = true;
                }
                else
                {
                        if(Shape12->Brush->Color != clRed)
                        {
                              Shape12->Brush->Color = clLime;
                              TelnetForm->Button24->Enabled = false;
                        }
                        z44->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val4,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape12->Brush->Color = clRed;
                }
                else Edit104->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape12->Brush->Color = clRed;
                }
                else Edit74->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z54->Caption = "4";
                        Shape12->Brush->Color = clRed;
                        TelnetForm->Button24->Enabled = true;
                }
                else
                {
                        if(Shape12->Brush->Color != clRed)
                        {
                              Shape12->Brush->Color = clLime;
                              TelnetForm->Button24->Enabled = false;
                        }
                        z54->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val4,w)!=0)
        {
                char eucurr3_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x34,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, eucurr3_cmd, 11, &dw_Write, 0);
                I=14.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape12->Brush->Color = clRed;
                }
                else Edit114->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape12->Brush->Color = clRed;
                }
                else Edit84->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z64->Caption = "4";
                        Shape12->Brush->Color = clRed;
                        TelnetForm->Button24->Enabled = true;
                }
                else
                {
                        if(Shape12->Brush->Color != clRed)
                        {
                              Shape12->Brush->Color = clLime;
                              TelnetForm->Button24->Enabled = false;
                        }
                        z64->Caption = "";
                }
                Result20->Caption = "";
        }
        if(Shape9->Brush->Color == clLime && Shape10->Brush->Color == clLime &&Shape11->Brush->Color == clLime &&Shape12->Brush->Color == clLime &&Shape13->Brush->Color == clLime &&Shape14->Brush->Color == clLime &&Shape15->Brush->Color == clLime &&Shape16->Brush->Color == clLime &&Shape17->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button25Click(TObject *Sender)
{
        char *x=z15->Caption.c_str();
        char *y=z25->Caption.c_str();
        char *z=z35->Caption.c_str();
        char *u=z45->Caption.c_str();
        char *v=z55->Caption.c_str();
        char *w=z65->Caption.c_str();
        Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape13->Brush->Color = clYellow;
        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 5 -v 0";
        String set_outlet_1_on = "set outlet-power -o 5 -v 1";
        String show_outlet_1_status = "show outlet-status -o 5";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();
        if(strcmp(val5,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape13->Brush->Color = clRed;
                }
                else Edit36->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape13->Brush->Color = clRed;
                }
                else Edit5->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape13->Brush->Color = clRed;
                        z15->Caption = "5";
                        TelnetForm->Button25->Enabled = true;
                }
                else
                {
                        Shape13->Brush->Color = clLime;
                        z15->Caption = "";
                        TelnetForm->Button25->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val5,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape13->Brush->Color = clRed;
                }
                else Edit45->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape13->Brush->Color = clRed;
                }
                else Edit14->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z25->Caption = "5";
                        Shape13->Brush->Color = clRed;
                        TelnetForm->Button25->Enabled = true;
                }
                else
                {
                        if(Shape13->Brush->Color != clRed)
                        {
                              Shape13->Brush->Color = clLime;
                              TelnetForm->Button25->Enabled = false;
                        }
                        z25->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val5,z)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape13->Brush->Color = clRed;
                }
                else Edit54->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape13->Brush->Color = clRed;
                }
                else Edit23->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z35->Caption = "5";
                        Shape13->Brush->Color = clRed;
                        TelnetForm->Button25->Enabled = true;
                }
                else
                {
                        if(Shape13->Brush->Color != clRed)
                        {
                              Shape13->Brush->Color = clLime;
                              TelnetForm->Button25->Enabled = false;
                        }
                        z35->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val5,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape13->Brush->Color = clRed;
                }
                else Edit95->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape13->Brush->Color = clRed;
                }
                else Edit65->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z45->Caption = "5";
                        Shape13->Brush->Color = clRed;
                        TelnetForm->Button25->Enabled = true;
                }
                else
                {
                        if(Shape13->Brush->Color != clRed)
                        {
                              Shape13->Brush->Color = clLime;
                              TelnetForm->Button25->Enabled = false;
                        }
                        z45->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val5,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape13->Brush->Color = clRed;
                }
                else Edit105->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape13->Brush->Color = clRed;
                }
                else Edit75->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z55->Caption = "5";
                        Shape13->Brush->Color = clRed;
                        TelnetForm->Button25->Enabled = true;
                }
                else
                {
                        if(Shape13->Brush->Color != clRed)
                        {
                              Shape13->Brush->Color = clLime;
                              TelnetForm->Button25->Enabled = false;
                        }
                        z55->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val5,w)!=0)
        {
                char eucurr3_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x34,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, eucurr3_cmd, 11, &dw_Write, 0);
                I=14.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape13->Brush->Color = clRed;
                }
                else Edit115->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape13->Brush->Color = clRed;
                }
                else Edit85->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z65->Caption = "5";
                        Shape13->Brush->Color = clRed;
                        TelnetForm->Button25->Enabled = true;
                }
                else
                {
                        if(Shape13->Brush->Color != clRed)
                        {
                              Shape13->Brush->Color = clLime;
                              TelnetForm->Button25->Enabled = false;
                        }
                        z65->Caption = "";
                }
                Result20->Caption = "";
        }
        if(Shape9->Brush->Color == clLime && Shape10->Brush->Color == clLime &&Shape11->Brush->Color == clLime &&Shape12->Brush->Color == clLime &&Shape13->Brush->Color == clLime &&Shape14->Brush->Color == clLime &&Shape15->Brush->Color == clLime &&Shape16->Brush->Color == clLime &&Shape17->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button26Click(TObject *Sender)
{
        char *x=z16->Caption.c_str();
        char *y=z26->Caption.c_str();
        char *z=z36->Caption.c_str();
        char *u=z46->Caption.c_str();
        char *v=z56->Caption.c_str();
        char *w=z66->Caption.c_str();
         Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape14->Brush->Color = clYellow;
        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 6 -v 0";
        String set_outlet_1_on = "set outlet-power -o 6 -v 1";
        String show_outlet_1_status = "show outlet-status -o 6";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();
        if(strcmp(val6,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape14->Brush->Color = clRed;
                }
                else Edit37->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape14->Brush->Color = clRed;
                }
                else Edit6->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape14->Brush->Color = clRed;
                        z16->Caption = "6";
                        TelnetForm->Button26->Enabled = true;
                }
                else
                {
                        Shape14->Brush->Color = clLime;
                        z16->Caption = "";
                        TelnetForm->Button26->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val6,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape14->Brush->Color = clRed;
                }
                else Edit46->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape14->Brush->Color = clRed;
                }
                else Edit15->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z26->Caption = "6";
                        Shape14->Brush->Color = clRed;
                        TelnetForm->Button26->Enabled = true;
                }
                else
                {
                        if(Shape14->Brush->Color != clRed)
                        {
                              Shape14->Brush->Color = clLime;
                              TelnetForm->Button26->Enabled = false;
                        }
                        z26->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val6,z)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape14->Brush->Color = clRed;
                }
                else Edit55->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape14->Brush->Color = clRed;
                }
                else Edit24->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z36->Caption = "6";
                        Shape14->Brush->Color = clRed;
                        TelnetForm->Button26->Enabled = true;
                }
                else
                {
                        if(Shape14->Brush->Color != clRed)
                        {
                              Shape14->Brush->Color = clLime;
                              TelnetForm->Button26->Enabled = false;
                        }
                        z36->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val6,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape14->Brush->Color = clRed;
                }
                else Edit96->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape14->Brush->Color = clRed;
                }
                else Edit66->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z46->Caption = "6";
                        Shape14->Brush->Color = clRed;
                        TelnetForm->Button26->Enabled = true;
                }
                else
                {
                        if(Shape14->Brush->Color != clRed)
                        {
                              Shape14->Brush->Color = clLime;
                              TelnetForm->Button26->Enabled = false;
                        }
                        z46->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val6,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape14->Brush->Color = clRed;
                }
                else Edit106->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape14->Brush->Color = clRed;
                }
                else Edit76->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z56->Caption = "6";
                        Shape14->Brush->Color = clRed;
                        TelnetForm->Button26->Enabled = true;
                }
                else
                {
                        if(Shape14->Brush->Color != clRed)
                        {
                              Shape14->Brush->Color = clLime;
                              TelnetForm->Button26->Enabled = false;
                        }
                        z56->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val6,w)!=0)
        {
                char eucurr3_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x34,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, eucurr3_cmd, 11, &dw_Write, 0);
                I=14.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape14->Brush->Color = clRed;
                }
                else Edit116->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape14->Brush->Color = clRed;
                }
                else Edit86->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z66->Caption = "6";
                        Shape14->Brush->Color = clRed;
                        TelnetForm->Button26->Enabled = true;
                }
                else
                {
                        if(Shape14->Brush->Color != clRed)
                        {
                              Shape14->Brush->Color = clLime;
                              TelnetForm->Button26->Enabled = false;
                        }
                        z66->Caption = "";
                }
                Result20->Caption = "";
        }
        if(Shape9->Brush->Color == clLime && Shape10->Brush->Color == clLime &&Shape11->Brush->Color == clLime &&Shape12->Brush->Color == clLime &&Shape13->Brush->Color == clLime &&Shape14->Brush->Color == clLime &&Shape15->Brush->Color == clLime &&Shape16->Brush->Color == clLime &&Shape17->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button27Click(TObject *Sender)
{
        char *x=z17->Caption.c_str();
        char *y=z27->Caption.c_str();
        char *z=z37->Caption.c_str();
        char *u=z47->Caption.c_str();
        char *v=z57->Caption.c_str();
        char *w=z67->Caption.c_str();
         Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape15->Brush->Color = clYellow;
        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 7 -v 0";
        String set_outlet_1_on = "set outlet-power -o 7 -v 1";
        String show_outlet_1_status = "show outlet-status -o 7";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();
        if(strcmp(val7,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape15->Brush->Color = clRed;
                }
                else Edit38->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape15->Brush->Color = clRed;
                }
                else Edit7->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape15->Brush->Color = clRed;
                        z17->Caption = "7";
                        TelnetForm->Button27->Enabled = true;
                }
                else
                {
                        Shape15->Brush->Color = clLime;
                        z17->Caption = "";
                        TelnetForm->Button27->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val7,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape15->Brush->Color = clRed;
                }
                else Edit47->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape15->Brush->Color = clRed;
                }
                else Edit16->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z27->Caption = "7";
                        Shape15->Brush->Color = clRed;
                        TelnetForm->Button27->Enabled = true;
                }
                else
                {
                        if(Shape15->Brush->Color != clRed)
                        {
                              Shape15->Brush->Color = clLime;
                              TelnetForm->Button27->Enabled = false;
                        }
                        z27->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val7,z)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape15->Brush->Color = clRed;
                }
                else Edit56->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape15->Brush->Color = clRed;
                }
                else Edit25->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z37->Caption = "7";
                        Shape15->Brush->Color = clRed;
                        TelnetForm->Button27->Enabled = true;
                }
                else
                {
                        if(Shape15->Brush->Color != clRed)
                        {
                              Shape15->Brush->Color = clLime;
                              TelnetForm->Button27->Enabled = false;
                        }
                        z37->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val7,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape15->Brush->Color = clRed;
                }
                else Edit97->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape15->Brush->Color = clRed;
                }
                else Edit67->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z47->Caption = "7";
                        Shape15->Brush->Color = clRed;
                        TelnetForm->Button27->Enabled = true;
                }
                else
                {
                        if(Shape15->Brush->Color != clRed)
                        {
                              Shape15->Brush->Color = clLime;
                              TelnetForm->Button27->Enabled = false;
                        }
                        z47->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val7,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape15->Brush->Color = clRed;
                }
                else Edit107->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape15->Brush->Color = clRed;
                }
                else Edit77->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z57->Caption = "7";
                        Shape15->Brush->Color = clRed;
                        TelnetForm->Button27->Enabled = true;
                }
                else
                {
                        if(Shape15->Brush->Color != clRed)
                        {
                              Shape15->Brush->Color = clLime;
                              TelnetForm->Button27->Enabled = false;
                        }
                        z57->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val7,w)!=0)
        {
                char eucurr3_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x34,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, eucurr3_cmd, 11, &dw_Write, 0);
                I=14.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape15->Brush->Color = clRed;
                }
                else Edit117->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape15->Brush->Color = clRed;
                }
                else Edit87->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z67->Caption = "7";
                        Shape15->Brush->Color = clRed;
                        TelnetForm->Button27->Enabled = true;
                }
                else
                {
                        if(Shape15->Brush->Color != clRed)
                        {
                              Shape15->Brush->Color = clLime;
                              TelnetForm->Button27->Enabled = false;
                        }
                        z67->Caption = "";
                }
                Result20->Caption = "";
        }
        if(Shape9->Brush->Color == clLime && Shape10->Brush->Color == clLime &&Shape11->Brush->Color == clLime &&Shape12->Brush->Color == clLime &&Shape13->Brush->Color == clLime &&Shape14->Brush->Color == clLime &&Shape15->Brush->Color == clLime &&Shape16->Brush->Color == clLime &&Shape17->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button28Click(TObject *Sender)
{
        char *x=z18->Caption.c_str();
        char *y=z28->Caption.c_str();
        char *z=z38->Caption.c_str();
        char *u=z48->Caption.c_str();
        char *v=z58->Caption.c_str();
        char *w=z68->Caption.c_str();
         Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape16->Brush->Color = clYellow;
        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 8 -v 0";
        String set_outlet_1_on = "set outlet-power -o 8 -v 1";
        String show_outlet_1_status = "show outlet-status -o 8";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();
        if(strcmp(val8,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape16->Brush->Color = clRed;
                }
                else Edit39->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape16->Brush->Color = clRed;
                }
                else Edit8->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape16->Brush->Color = clRed;
                        z18->Caption = "8";
                        TelnetForm->Button28->Enabled = true;
                }
                else
                {
                        Shape16->Brush->Color = clLime;
                        z18->Caption = "";
                        TelnetForm->Button28->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val8,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape16->Brush->Color = clRed;
                }
                else Edit48->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape16->Brush->Color = clRed;
                }
                else Edit17->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z28->Caption = "8";
                        Shape16->Brush->Color = clRed;
                        TelnetForm->Button28->Enabled = true;
                }
                else
                {
                        if(Shape16->Brush->Color != clRed)
                        {
                              Shape16->Brush->Color = clLime;
                              TelnetForm->Button28->Enabled = false;
                        }
                        z28->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val8,z)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape16->Brush->Color = clRed;
                }
                else Edit57->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape16->Brush->Color = clRed;
                }
                else Edit26->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z38->Caption = "8";
                        Shape16->Brush->Color = clRed;
                        TelnetForm->Button28->Enabled = true;
                }
                else
                {
                        if(Shape16->Brush->Color != clRed)
                        {
                              Shape16->Brush->Color = clLime;
                              TelnetForm->Button28->Enabled = false;
                        }
                        z38->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val8,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape16->Brush->Color = clRed;
                }
                else Edit98->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape16->Brush->Color = clRed;
                }
                else Edit68->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z48->Caption = "8";
                        Shape16->Brush->Color = clRed;
                        TelnetForm->Button28->Enabled = true;
                }
                else
                {
                        if(Shape16->Brush->Color != clRed)
                        {
                              Shape16->Brush->Color = clLime;
                              TelnetForm->Button28->Enabled = false;
                        }
                        z48->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val8,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape16->Brush->Color = clRed;
                }
                else Edit108->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape16->Brush->Color = clRed;
                }
                else Edit78->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z58->Caption = "8";
                        Shape16->Brush->Color = clRed;
                        TelnetForm->Button28->Enabled = true;
                }
                else
                {
                        if(Shape16->Brush->Color != clRed)
                        {
                              Shape16->Brush->Color = clLime;
                              TelnetForm->Button28->Enabled = false;
                        }
                        z58->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val8,w)!=0)
        {
                char eucurr3_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x34,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, eucurr3_cmd, 11, &dw_Write, 0);
                I=14.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape16->Brush->Color = clRed;
                }
                else Edit118->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape16->Brush->Color = clRed;
                }
                else Edit88->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z68->Caption = "8";
                        Shape16->Brush->Color = clRed;
                        TelnetForm->Button28->Enabled = true;
                }
                else
                {
                        if(Shape16->Brush->Color != clRed)
                        {
                              Shape16->Brush->Color = clLime;
                              TelnetForm->Button28->Enabled = false;
                        }
                        z68->Caption = "";
                }
                Result20->Caption = "";
        }
        if(Shape9->Brush->Color == clLime && Shape10->Brush->Color == clLime &&Shape11->Brush->Color == clLime &&Shape12->Brush->Color == clLime &&Shape13->Brush->Color == clLime &&Shape14->Brush->Color == clLime &&Shape15->Brush->Color == clLime &&Shape16->Brush->Color == clLime &&Shape17->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button29Click(TObject *Sender)
{
        char *x=z19->Caption.c_str();
        char *y=z29->Caption.c_str();
        char *z=z39->Caption.c_str();
        char *u=z49->Caption.c_str();
        char *v=z59->Caption.c_str();
        char *w=z69->Caption.c_str();
         Power->Caption = "";
        Current->Caption = "";
        Result20->Caption = "";

        Shape17->Brush->Color = clYellow;
        IdTelnetDemo->SendCh('\r');
        String set_outlet_1_off = "set outlet-power -o 9 -v 0";
        String set_outlet_1_on = "set outlet-power -o 9 -v 1";
        String show_outlet_1_status = "show outlet-status -o 9";

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        SendCommand(set_outlet_1_on);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        Memo1Display();
        ::Sleep(500);
        Application->ProcessMessages();
        if(strcmp(val9,x)!=0)
        {
                char curr1_cmd[] ={0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.2;
                n=I*(1+0.3);
                m=I*(1-0.3);
                V=230;
                P=V*I;
                a=P*(1+0.3);
                b=P*(1-0.3);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape17->Brush->Color = clRed;
                }
                else Edit40->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape17->Brush->Color = clRed;
                }
                else Edit9->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        Shape17->Brush->Color = clRed;
                        z19->Caption = "9";
                        TelnetForm->Button29->Enabled = true;
                }
                else
                {
                        Shape17->Brush->Color = clLime;
                        z19->Caption = "";
                        TelnetForm->Button29->Enabled = false;
                }
                Result20->Caption = "";
        }
        if(strcmp(val9,y)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x30,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=0.7;
                n=I*(1+0.1);
                m=I*(1-0.1);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape17->Brush->Color = clRed;
                }
                else Edit49->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape17->Brush->Color = clRed;
                }
                else Edit18->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z29->Caption = "9";
                        Shape17->Brush->Color = clRed;
                        TelnetForm->Button29->Enabled = true;
                }
                else
                {
                        if(Shape17->Brush->Color != clRed)
                        {
                              Shape17->Brush->Color = clLime;
                              TelnetForm->Button29->Enabled = false;
                        }
                        z29->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val9,z)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x32,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=2;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape17->Brush->Color = clRed;
                }
                else Edit58->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape17->Brush->Color = clRed;
                }
                else Edit27->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z39->Caption = "9";
                        Shape17->Brush->Color = clRed;
                        TelnetForm->Button29->Enabled = true;
                }
                else
                {
                        if(Shape17->Brush->Color != clRed)
                        {
                              Shape17->Brush->Color = clLime;
                              TelnetForm->Button29->Enabled = false;
                        }
                        z39->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val9,u)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x37,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=7.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape17->Brush->Color = clRed;
                }
                else Edit99->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape17->Brush->Color = clRed;
                }
                else Edit69->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z49->Caption = "9";
                        Shape17->Brush->Color = clRed;
                        TelnetForm->Button29->Enabled = true;
                }
                else
                {
                        if(Shape17->Brush->Color != clRed)
                        {
                              Shape17->Brush->Color = clLime;
                              TelnetForm->Button29->Enabled = false;
                        }
                        z49->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val9,v)!=0)
        {
                char curr1_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x30,0x0A,'\r'};
                WriteFile(COM1, curr1_cmd, 10, &dw_Write, 0);
                I=10;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape17->Brush->Color = clRed;
                }
                else Edit109->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape17->Brush->Color = clRed;
                }
                else Edit79->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z59->Caption = "9";
                        Shape17->Brush->Color = clRed;
                        TelnetForm->Button29->Enabled = true;
                }
                else
                {
                        if(Shape17->Brush->Color != clRed)
                        {
                              Shape17->Brush->Color = clLime;
                              TelnetForm->Button29->Enabled = false;
                        }
                        z59->Caption = "";
                }
                Result20->Caption = "";
        }
        if(strcmp(val9,w)!=0)
        {
                char eucurr3_cmd[] = {0x63,0x75,0x72,0x72,0x20,0x31,0x34,0x2E,0x37,0x0A,'\r'};
                WriteFile(COM1, eucurr3_cmd, 11, &dw_Write, 0);
                I=14.7;
                n=I*(1+0.05);
                m=I*(1-0.05);
                V=120;
                P=V*I;
                a=P*(1+0.08);
                b=P*(1-0.08);
                for(j=0;j<3;j++)
                {
                        if(j==0)
                        {
                                ::Sleep(3000);
                                Application->ProcessMessages();
                        }
                        if(j==1)
                        {
                                ::Sleep(2000);
                                Application->ProcessMessages();
                        }
                        if(j==2)
                        {
                                IdTelnetDemo->SendCh('\r');
                                SendCommand(show_outlet_1_status);
                                ::Sleep(500);
                                Application->ProcessMessages();
                                SendCommand(Enter);
                                ::Sleep(1000);
                                Application->ProcessMessages();
                                Memo1Display();
                        }
                }

                int num30=Memo1->Lines->Count;
                ::Sleep(1500);
                Application->ProcessMessages();
                String yyy30=Memo1->Lines->Strings[num30-1]+Memo1->Lines->Strings[num30]+Memo1->Lines->Strings[num30-2]+Memo1->Lines->Strings[num30+1];
                String right300 = yyy30.SubString(yyy30.Pos("power")+8,10);
                String left300 = right300.SubString(0,right300.Pos("W")-2);
                String left001 = left300+left250;
                Power->Caption = left001;
                float left301 = StrToFloat(left300);
                if(left301<b || left301>a)
                {
                        Result20->Caption = "FAIL";
                        Shape17->Brush->Color = clRed;
                }
                else Edit119->Text = left300;
                String right302 =  yyy30.SubString(yyy30.Pos("current")+10,10);
                String left302 = right302.SubString(0,right302.Pos("A")-2);
                String left0011 = left302+left251;
                Current->Caption = left0011;
                float left303 = StrToFloat(left302);
                if(left303<m || left303>n)
                {
                        Result20->Caption = "FAIL";
                        Shape17->Brush->Color = clRed;
                }
                else Edit89->Text = left302;
                IdTelnetDemo->SendCh('\r');
                SendCommand(set_outlet_1_off);
                ::Sleep(500);
                Application->ProcessMessages();
                SendCommand(Enter);
                Memo1Display();
                ::Sleep(500);
                Application->ProcessMessages();
                if(Result20->Caption == "FAIL")
                {
                        z69->Caption = "9";
                        Shape17->Brush->Color = clRed;
                        TelnetForm->Button29->Enabled = true;
                }
                else
                {
                        if(Shape17->Brush->Color != clRed)
                        {
                              Shape17->Brush->Color = clLime;
                              TelnetForm->Button29->Enabled = false;
                        }
                        z69->Caption = "";
                }
                Result20->Caption = "";
        }
        if(Shape9->Brush->Color == clLime && Shape10->Brush->Color == clLime &&Shape11->Brush->Color == clLime &&Shape12->Brush->Color == clLime &&Shape13->Brush->Color == clLime &&Shape14->Brush->Color == clLime &&Shape15->Brush->Color == clLime &&Shape16->Brush->Color == clLime &&Shape17->Brush->Color == clLime)
        {
             TelnetForm->Button30->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button5Click(TObject *Sender)
{
      if((EU->Checked == true && US->Checked != true)
         ||(US->Checked == true && EU->Checked != true))
        {

        }
        else
        {
                Application->MessageBox("Check the config.ini","show");
                return;
        }

        String str,str1;
        IdTelnetDemo->Host = edtServer->Text;
        str = edtServer->Text;
        IdTelnetDemo->Port = StrToInt(spnedtPort->Text);
        str1 = spnedtPort->Text;
        IdTelnetDemo->Connect();
        Result3->Caption = "";
        Result20->Caption = "";

        Current->Caption = "";
        Power->Caption = "";

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
       // Memo1->Lines->Add("password: pakedgep");
       // Memo1->Lines->Add("");
        IdTelnetDemo->SendCh('\n');
        Application->ProcessMessages();
        ::Sleep(500);
        Application->ProcessMessages();
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

        SendCommand(set_outlet_1_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 1 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(700);
        Application->ProcessMessages();

        SendCommand(set_outlet_2_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 2 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(700);
        Application->ProcessMessages();

        SendCommand(set_outlet_3_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 3 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(700);
        Application->ProcessMessages();

        SendCommand(set_outlet_4_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 4 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(700);
        Application->ProcessMessages();

        SendCommand(set_outlet_5_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 5 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(700);
        Application->ProcessMessages();

        SendCommand(set_outlet_6_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 6 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(700);
        Application->ProcessMessages();

        SendCommand(set_outlet_7_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 7 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();

        ::Sleep(700);
        Application->ProcessMessages();

        SendCommand(set_outlet_8_off);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 8 -v 0");
        //Memo1->Lines->Add("");
        //IdTelnetDemo->SendCh('\n');
        Memo1Display();
        ::Sleep(700);
        Application->ProcessMessages();
        if(US->Checked == true)
        {
                SendCommand(set_outlet_9_off);
                ::Sleep(700);
                Application->ProcessMessages();
                SendCommand(Enter);
                //Memo1->Lines->Add("Pakedge-PDU$ set outlet-power -o 9 -v 0");
                //Memo1->Lines->Add("");
                //IdTelnetDemo->SendCh('\n');
                Memo1Display();
        }
        TelnetForm->Button4->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button30Click(TObject *Sender)
{
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
                String  AC_LOAD_TEST = "AC_LOAD_TEST";
                String serveraddress = URL->Text.c_str();
             //   Application->MessageBox(serveraddress.c_str(),"show");
                String SERIAL_NUMBER = PCBASN->Text.c_str();
                String STATION_NUMBER = Station;
               // Application->MessageBox(STATION_NUMBER.c_str(),"show");
                String c1 = Edit1->Text.c_str();
                String c2 = Edit2->Text.c_str();
                String c3 = Edit3->Text.c_str();
                String c4 = Edit4->Text.c_str();
                String c5 = Edit5->Text.c_str();
                String c6 = Edit6->Text.c_str();
                String c7 = Edit7->Text.c_str();
                String c8 = Edit8->Text.c_str();
                String c9 = Edit9->Text.c_str();
               // Application->MessageBox(Edit1->Text.c_str(),"show");
                //Application->MessageBox(Edit2->Text.c_str(),"show");
                //Application->MessageBox(Edit3->Text.c_str(),"show");
               // Application->MessageBox(Edit4->Text.c_str(),"show");
              //  Application->MessageBox(Edit5->Text.c_str(),"show");
               // Application->MessageBox(Edit6->Text.c_str(),"show");
               // Application->MessageBox(Edit7->Text.c_str(),"show");
               // Application->MessageBox(Edit8->Text.c_str(),"show");
               // Application->MessageBox(Edit9->Text.c_str(),"show");

                String c10 = Edit10->Text.c_str();
                String c11 = Edit11->Text.c_str();
                String c12 = Edit12->Text.c_str();
                String c13 = Edit13->Text.c_str();
                String c14 = Edit14->Text.c_str();
                String c15 = Edit15->Text.c_str();
                String c16 = Edit16->Text.c_str();
                String c17 = Edit17->Text.c_str();
                String c18 = Edit18->Text.c_str();
              //  Application->MessageBox(Edit10->Text.c_str(),"show");
             //   Application->MessageBox(Edit11->Text.c_str(),"show");
             //   Application->MessageBox(Edit12->Text.c_str(),"show");
             //   Application->MessageBox(Edit13->Text.c_str(),"show");
             //   Application->MessageBox(Edit14->Text.c_str(),"show");
             //   Application->MessageBox(Edit15->Text.c_str(),"show");
             //   Application->MessageBox(Edit16->Text.c_str(),"show");
             //   Application->MessageBox(Edit17->Text.c_str(),"show");
             //   Application->MessageBox(Edit18->Text.c_str(),"show");

                String c19 = Edit19->Text.c_str();
                String c20 = Edit20->Text.c_str();
                String c21 = Edit21->Text.c_str();
                String c22 = Edit22->Text.c_str();
                String c23 = Edit23->Text.c_str();
                String c24 = Edit24->Text.c_str();
                String c25 = Edit25->Text.c_str();
                String c26 = Edit26->Text.c_str();
                String c27 = Edit27->Text.c_str();
             // Application->MessageBox(Edit19->Text.c_str(),"show");
               // Application->MessageBox(Edit20->Text.c_str(),"show");
               // Application->MessageBox(Edit21->Text.c_str(),"show");
               // Application->MessageBox(Edit22->Text.c_str(),"show");
               // Application->MessageBox(Edit23->Text.c_str(),"show");
              //  Application->MessageBox(Edit24->Text.c_str(),"show");
              //  Application->MessageBox(Edit25->Text.c_str(),"show");
              //  Application->MessageBox(Edit26->Text.c_str(),"show");
              //  Application->MessageBox(Edit27->Text.c_str(),"show");

                String c28 = Edit61->Text.c_str();
                String c29 = Edit62->Text.c_str();
                String c30 = Edit63->Text.c_str();
                String c31 = Edit64->Text.c_str();
                String c32 = Edit65->Text.c_str();
                String c33 = Edit66->Text.c_str();
                String c34 = Edit67->Text.c_str();
                String c35 = Edit68->Text.c_str();
                String c36 = Edit69->Text.c_str();
              //  Application->MessageBox(Edit61->Text.c_str(),"show");
             //   Application->MessageBox(Edit62->Text.c_str(),"show");
            //    Application->MessageBox(Edit63->Text.c_str(),"show");
             //   Application->MessageBox(Edit64->Text.c_str(),"show");
             //   Application->MessageBox(Edit65->Text.c_str(),"show");
             //   Application->MessageBox(Edit66->Text.c_str(),"show");
            //    Application->MessageBox(Edit67->Text.c_str(),"show");
            //    Application->MessageBox(Edit68->Text.c_str(),"show");
            //    Application->MessageBox(Edit69->Text.c_str(),"show");

                String c37 = Edit71->Text.c_str();
                String c38 = Edit72->Text.c_str();
                String c39 = Edit73->Text.c_str();
                String c40 = Edit74->Text.c_str();
                String c41 = Edit75->Text.c_str();
                String c42 = Edit76->Text.c_str();
                String c43 = Edit77->Text.c_str();
                String c44 = Edit78->Text.c_str();
                String c45 = Edit79->Text.c_str();
              //  Application->MessageBox(Edit71->Text.c_str(),"show");
              //  Application->MessageBox(Edit72->Text.c_str(),"show");
             //   Application->MessageBox(Edit73->Text.c_str(),"show");
             //   Application->MessageBox(Edit74->Text.c_str(),"show");
             //   Application->MessageBox(Edit75->Text.c_str(),"show");
            //    Application->MessageBox(Edit76->Text.c_str(),"show");
            //    Application->MessageBox(Edit77->Text.c_str(),"show");
            //    Application->MessageBox(Edit78->Text.c_str(),"show");
            //    Application->MessageBox(Edit79->Text.c_str(),"show");

                String c46 = Edit81->Text.c_str();
                String c47 = Edit82->Text.c_str();
                String c48 = Edit83->Text.c_str();
                String c49 = Edit84->Text.c_str();
                String c50 = Edit85->Text.c_str();
                String c51 = Edit86->Text.c_str();
                String c52 = Edit87->Text.c_str();
                String c53 = Edit88->Text.c_str();
                String c54 = Edit89->Text.c_str();
                //Application->MessageBox(Edit81->Text.c_str(),"show");
                //Application->MessageBox(Edit82->Text.c_str(),"show");
                //Application->MessageBox(Edit83->Text.c_str(),"show");
                //Application->MessageBox(Edit84->Text.c_str(),"show");
                //Application->MessageBox(Edit85->Text.c_str(),"show");
                //Application->MessageBox(Edit86->Text.c_str(),"show");
                //Application->MessageBox(Edit87->Text.c_str(),"show");
                //Application->MessageBox(Edit88->Text.c_str(),"show");
                //Application->MessageBox(Edit89->Text.c_str(),"show");

                String p1 = Edit32->Text.c_str();
                String p2 = Edit33->Text.c_str();
                String p3 = Edit34->Text.c_str();
                String p4 = Edit35->Text.c_str();
                String p5 = Edit36->Text.c_str();
                String p6 = Edit37->Text.c_str();
                String p7 = Edit38->Text.c_str();
                String p8 = Edit39->Text.c_str();
                String p9 = Edit40->Text.c_str();
                //Application->MessageBox(Edit32->Text.c_str(),"show");
                //Application->MessageBox(Edit33->Text.c_str(),"show");
                //Application->MessageBox(Edit34->Text.c_str(),"show");
                //Application->MessageBox(Edit35->Text.c_str(),"show");
                //Application->MessageBox(Edit36->Text.c_str(),"show");
                //Application->MessageBox(Edit37->Text.c_str(),"show");
                //Application->MessageBox(Edit38->Text.c_str(),"show");
                //Application->MessageBox(Edit39->Text.c_str(),"show");
                //Application->MessageBox(Edit40->Text.c_str(),"show");

                String p10 = Edit41->Text.c_str();
                String p11 = Edit42->Text.c_str();
                String p12 = Edit43->Text.c_str();
                String p13 = Edit44->Text.c_str();
                String p14 = Edit45->Text.c_str();
                String p15 = Edit46->Text.c_str();
                String p16 = Edit47->Text.c_str();
                String p17 = Edit48->Text.c_str();
                String p18 = Edit49->Text.c_str();
               //Application->MessageBox(Edit41->Text.c_str(),"show");
               // Application->MessageBox(Edit42->Text.c_str(),"show");
               // Application->MessageBox(Edit43->Text.c_str(),"show");
               // Application->MessageBox(Edit44->Text.c_str(),"show");
               // Application->MessageBox(Edit45->Text.c_str(),"show");
               // Application->MessageBox(Edit46->Text.c_str(),"show");
               // Application->MessageBox(Edit47->Text.c_str(),"show");
               // Application->MessageBox(Edit48->Text.c_str(),"show");
               // Application->MessageBox(Edit49->Text.c_str(),"show");

                String p19 = Edit50->Text.c_str();
                String p20 = Edit51->Text.c_str();
                String p21 = Edit52->Text.c_str();
                String p22 = Edit53->Text.c_str();
                String p23 = Edit54->Text.c_str();
                String p24 = Edit55->Text.c_str();
                String p25 = Edit56->Text.c_str();
                String p26 = Edit57->Text.c_str();
                String p27 = Edit58->Text.c_str();
               //Application->MessageBox(Edit50->Text.c_str(),"show");
              //  Application->MessageBox(Edit51->Text.c_str(),"show");
               // Application->MessageBox(Edit52->Text.c_str(),"show");
               /// Application->MessageBox(Edit53->Text.c_str(),"show");
             //   Application->MessageBox(Edit54->Text.c_str(),"show");
             //   Application->MessageBox(Edit55->Text.c_str(),"show");
            //    Application->MessageBox(Edit57->Text.c_str(),"show");
            // Application->MessageBox(Edit58->Text.c_str(),"show");

                String p28 = Edit91->Text.c_str();
                String p29 = Edit92->Text.c_str();
                String p30 = Edit93->Text.c_str();
                String p31 = Edit94->Text.c_str();
                String p32 = Edit95->Text.c_str();
                String p33 = Edit96->Text.c_str();
                String p34 = Edit97->Text.c_str();
                String p35 = Edit98->Text.c_str();
                String p36 = Edit99->Text.c_str();
                //Application->MessageBox(Edit91->Text.c_str(),"show");
                //Application->MessageBox(Edit92->Text.c_str(),"show");
                //Application->MessageBox(Edit93->Text.c_str(),"show");
                //Application->MessageBox(Edit94->Text.c_str(),"show");
                //Application->MessageBox(Edit95->Text.c_str(),"show");
                //Application->MessageBox(Edit96->Text.c_str(),"show");
                //Application->MessageBox(Edit97->Text.c_str(),"show");
                //Application->MessageBox(Edit98->Text.c_str(),"show");
                //Application->MessageBox(Edit99->Text.c_str(),"show");

                String p37 = Edit101->Text.c_str();
                String p38 = Edit102->Text.c_str();
                String p39 = Edit103->Text.c_str();
                String p40 = Edit104->Text.c_str();
                String p41 = Edit105->Text.c_str();
                String p42 = Edit106->Text.c_str();
                String p43 = Edit107->Text.c_str();
                String p44 = Edit108->Text.c_str();
                String p45 = Edit109->Text.c_str();
                //Application->MessageBox(Edit101->Text.c_str(),"show");
                //Application->MessageBox(Edit102->Text.c_str(),"show");
                //Application->MessageBox(Edit103->Text.c_str(),"show");
                //Application->MessageBox(Edit104->Text.c_str(),"show");
                //Application->MessageBox(Edit105->Text.c_str(),"show");
                //Application->MessageBox(Edit106->Text.c_str(),"show");
                //Application->MessageBox(Edit107->Text.c_str(),"show");
                //Application->MessageBox(Edit108->Text.c_str(),"show");
                //Application->MessageBox(Edit109->Text.c_str(),"show");

                String p46 = Edit111->Text.c_str();
                String p47 = Edit112->Text.c_str();
                String p48 = Edit113->Text.c_str();
                String p49 = Edit114->Text.c_str();
                String p50 = Edit115->Text.c_str();
                String p51 = Edit116->Text.c_str();
                String p52 = Edit117->Text.c_str();
                String p53 = Edit118->Text.c_str();
                String p54 = Edit119->Text.c_str();
                //Application->MessageBox(Edit111->Text.c_str(),"show");
                //Application->MessageBox(Edit112->Text.c_str(),"show");
                //Application->MessageBox(Edit113->Text.c_str(),"show");
                //Application->MessageBox(Edit114->Text.c_str(),"show");
                //Application->MessageBox(Edit115->Text.c_str(),"show");
                //Application->MessageBox(Edit116->Text.c_str(),"show");
                //Application->MessageBox(Edit117->Text.c_str(),"show");
                //Application->MessageBox(Edit118->Text.c_str(),"show");
                //Application->MessageBox(Edit119->Text.c_str(),"show");

                String FW2  = Edit28->Text.c_str();
                String model2 = Edit29->Text.c_str();
                String voltage2 = Edit30->Text.c_str();
                String frequency2 = Edit31->Text.c_str();
                //Application->MessageBox(Edit28->Text.c_str(),"show");
                //Application->MessageBox(Edit29->Text.c_str(),"show");
                //Application->MessageBox(Edit30->Text.c_str(),"show");
                //Application->MessageBox(Edit31->Text.c_str(),"show");


             /*  String SDRAM2 = SDRAM1->Text.c_str();
                String Buzzer2 = Buzzer1->Text.c_str();
                String ping2 = ping1->Text.c_str();
                String FW2 = FW1->Text.c_str();
                String model2 = model1->Text.c_str();
                String voltage2 = voltage1->Text.c_str();
                String frequency2 = frequency1->Text.c_str();
                String temp2 = temp1->Text.c_str();
                String humidity2 = humidity1->Text.c_str();
                String outlettest2 = outlettest1-> Text.c_str();
                String powercycle2 =  powercycle1-> Text.c_str();
                String OLED2 = OLED1->Text.c_str();
                String LED2 = LED1->Text.c_str();
                String staticsip2 = staticsip1->Text.c_str();     */

                char *f = "";
               // char *f100 = URL->Text.c_str();
               // char *f101 = PCBASN->Text.c_str();
               // char *f102 = Station1->Text.c_str();
               // char *f103 = EMP1->Text.c_str();
                char *f1 = Edit1->Text.c_str();
                char *f2 = Edit2->Text.c_str();
                char *f3 = Edit3->Text.c_str();
                char *f4 = Edit4->Text.c_str();
                char *f5 = Edit5->Text.c_str();
                char *f6 = Edit6->Text.c_str();
                char *f7 = Edit7->Text.c_str();
                char *f8 = Edit8->Text.c_str();
                char *f9 = Edit9->Text.c_str();

                char *f10 = Edit10->Text.c_str();
                char *f11 = Edit11->Text.c_str();
                char *f12 = Edit12->Text.c_str();
                char *f13 = Edit13->Text.c_str();
                char *f14 = Edit14->Text.c_str();
                char *f15 = Edit15->Text.c_str();
                char *f16 = Edit16->Text.c_str();
                char *f17 = Edit17->Text.c_str();
                char *f18 = Edit18->Text.c_str();

                char *f19 = Edit19->Text.c_str();
                char *f20 = Edit20->Text.c_str();
                char *f21 = Edit21->Text.c_str();
                char *f22 = Edit22->Text.c_str();
                char *f23 = Edit23->Text.c_str();
                char *f24 = Edit24->Text.c_str();
                char *f25 = Edit25->Text.c_str();
                char *f26 = Edit26->Text.c_str();
                char *f27 = Edit27->Text.c_str();

                char *f28 = Edit28->Text.c_str();
                char *f29 = model2.c_str();
                char *f30 = Edit30->Text.c_str();
                char *f31 = Edit31->Text.c_str();

                char *f32 = Edit32->Text.c_str();
                char *f33 = Edit33->Text.c_str();
                char *f34 = Edit34->Text.c_str();
                char *f35 = Edit35->Text.c_str();
                char *f36 = Edit36->Text.c_str();
                char *f37 = Edit37->Text.c_str();
                char *f38 = Edit38->Text.c_str();
                char *f39 = Edit39->Text.c_str();
                char *f40 = Edit40->Text.c_str();

                char *f41 = Edit41->Text.c_str();
                char *f42 = Edit42->Text.c_str();
                char *f43 = Edit43->Text.c_str();
                char *f44 = Edit44->Text.c_str();
                char *f45 = Edit45->Text.c_str();
                char *f46 = Edit46->Text.c_str();
                char *f47 = Edit47->Text.c_str();
                char *f48 = Edit48->Text.c_str();
                char *f49 = Edit49->Text.c_str();

                char *f50 = Edit50->Text.c_str();
                char *f51 = Edit51->Text.c_str();
                char *f52 = Edit52->Text.c_str();
                char *f53 = Edit53->Text.c_str();
                char *f54 = Edit54->Text.c_str();
                char *f55 = Edit55->Text.c_str();
                char *f56 = Edit56->Text.c_str();
                char *f57 = Edit57->Text.c_str();
                char *f58 = Edit58->Text.c_str();

                char *f61 = Edit61->Text.c_str();
                char *f62 = Edit62->Text.c_str();
                char *f63 = Edit63->Text.c_str();
                char *f64 = Edit64->Text.c_str();
                char *f65 = Edit65->Text.c_str();
                char *f66 = Edit66->Text.c_str();
                char *f67 = Edit67->Text.c_str();
                char *f68 = Edit68->Text.c_str();
                char *f69 = Edit69->Text.c_str();

                char *f71 = Edit71->Text.c_str();
                char *f72 = Edit72->Text.c_str();
                char *f73 = Edit73->Text.c_str();
                char *f74 = Edit74->Text.c_str();
                char *f75 = Edit75->Text.c_str();
                char *f76 = Edit76->Text.c_str();
                char *f77 = Edit77->Text.c_str();
                char *f78 = Edit78->Text.c_str();
                char *f79 = Edit79->Text.c_str();

                char *f81 = Edit81->Text.c_str();
                char *f82 = Edit82->Text.c_str();
                char *f83 = Edit83->Text.c_str();
                char *f84 = Edit84->Text.c_str();
                char *f85 = Edit85->Text.c_str();
                char *f86 = Edit86->Text.c_str();
                char *f87 = Edit87->Text.c_str();
                char *f88 = Edit88->Text.c_str();
                char *f89 = Edit89->Text.c_str();

                char *f91 = Edit91->Text.c_str();
                char *f92 = Edit92->Text.c_str();
                char *f93 = Edit93->Text.c_str();
                char *f94 = Edit94->Text.c_str();
                char *f95 = Edit95->Text.c_str();
                char *f96 = Edit96->Text.c_str();
                char *f97 = Edit97->Text.c_str();
                char *f98 = Edit98->Text.c_str();
                char *f99 = Edit99->Text.c_str();

                char *f101 = Edit101->Text.c_str();
                char *f102 = Edit102->Text.c_str();
                char *f103 = Edit103->Text.c_str();
                char *f104 = Edit104->Text.c_str();
                char *f105 = Edit105->Text.c_str();
                char *f106 = Edit106->Text.c_str();
                char *f107 = Edit107->Text.c_str();
                char *f108 = Edit108->Text.c_str();
                char *f109 = Edit109->Text.c_str();

                char *f111 = Edit111->Text.c_str();
                char *f112 = Edit112->Text.c_str();
                char *f113 = Edit113->Text.c_str();
                char *f114 = Edit114->Text.c_str();
                char *f115 = Edit115->Text.c_str();
                char *f116 = Edit116->Text.c_str();
                char *f117 = Edit117->Text.c_str();
                char *f118 = Edit118->Text.c_str();
                char *f119 = Edit119->Text.c_str();

                char *s = "PE-08I";
                char *s1 = "PE-09N";
               /* if(strcmp(f29,s)==0)
                {
                        Application->MessageBox("PE-08I模式匹配","show");
                }
                 if(strcmp(f29,s1)==0)
                {
                        Application->MessageBox("PE-09N模式匹配","show");
                }     */

                AnsiString Url=serveraddress+":8080/or2mac/pdu/log_info";
                if(strcmp(f29,s)==0&&strcmp(f,f1)!=0&&strcmp(f,f2)!=0&&strcmp(f,f3)!=0&&strcmp(f,f4)!=0&&strcmp(f,f5)!=0&&strcmp(f,f6)!=0&&strcmp(f,f7)!=0&&strcmp(f,f8)!=0
                   &&strcmp(f,f10)!=0&&strcmp(f,f11)!=0&&strcmp(f,f12)!=0&&strcmp(f,f13)!=0&&strcmp(f,f14)!=0&&strcmp(f,f15)!=0&&strcmp(f,f16)!=0&&strcmp(f,f17)!=0
                   &&strcmp(f,f19)!=0&&strcmp(f,f20)!=0&&strcmp(f,f21)!=0&&strcmp(f,f22)!=0&&strcmp(f,f23)!=0&&strcmp(f,f24)!=0&&strcmp(f,f25)!=0&&strcmp(f,f26)!=0
                   &&strcmp(f,f32)!=0&&strcmp(f,f33)!=0&&strcmp(f,f34)!=0&&strcmp(f,f35)!=0&&strcmp(f,f36)!=0&&strcmp(f,f37)!=0&&strcmp(f,f38)!=0&&strcmp(f,f39)!=0
                   &&strcmp(f,f41)!=0&&strcmp(f,f42)!=0&&strcmp(f,f43)!=0&&strcmp(f,f44)!=0&&strcmp(f,f45)!=0&&strcmp(f,f46)!=0&&strcmp(f,f47)!=0&&strcmp(f,f48)!=0
                   &&strcmp(f,f50)!=0&&strcmp(f,f51)!=0&&strcmp(f,f52)!=0&&strcmp(f,f53)!=0&&strcmp(f,f54)!=0&&strcmp(f,f55)!=0&&strcmp(f,f56)!=0&&strcmp(f,f57)!=0
                   &&strcmp(f,f61)!=0&&strcmp(f,f62)!=0&&strcmp(f,f63)!=0&&strcmp(f,f64)!=0&&strcmp(f,f65)!=0&&strcmp(f,f66)!=0&&strcmp(f,f67)!=0&&strcmp(f,f68)!=0
                   &&strcmp(f,f71)!=0&&strcmp(f,f72)!=0&&strcmp(f,f73)!=0&&strcmp(f,f74)!=0&&strcmp(f,f75)!=0&&strcmp(f,f76)!=0&&strcmp(f,f77)!=0&&strcmp(f,f78)!=0
                   &&strcmp(f,f91)!=0&&strcmp(f,f92)!=0&&strcmp(f,f93)!=0&&strcmp(f,f94)!=0&&strcmp(f,f95)!=0&&strcmp(f,f96)!=0&&strcmp(f,f97)!=0&&strcmp(f,f98)!=0
                   &&strcmp(f,f101)!=0&&strcmp(f,f102)!=0&&strcmp(f,f103)!=0&&strcmp(f,f104)!=0&&strcmp(f,f105)!=0&&strcmp(f,f106)!=0&&strcmp(f,f107)!=0&&strcmp(f,f108)!=0
                   &&strcmp(f,f28)!=0&&strcmp(f,f29)!=0&&strcmp(f,f30)!=0&&strcmp(f,f31)!=0)
                   {
                       /* AnsiString Url=serveraddress+":8080/or2mac/log_info_versatile?SERIAL_NUMBER="+SERIAL_NUMBER+
                        "&STATION_NUMBER="+STATION_NUMBER+
                        "&EMP="+EMP+
                        "&INFO=FW;model;voltage;frequency;current1;power1;current2;power2;current3;power3;current4;power4;current5;power5;current6;power6;current7;power7;current8;power8;"+
                        "current10;power10;current11;power11;current12;power12;current13;power13;current14;power14;current15;power15;current16;power16;current17;power17;"+
                        "current19;power19;current20;power20;current21;power21;current22;power22;current23;power23;current24;power24;current25;power25;current26;power26;"+
                        "&VALUE="+FW2+";"+model2+";"+voltage2+";"+frequency2+";"+current1+";"+power1+";"+current2+";"+power2+";"+current3+";"+power3+";"+current4+";"+power4+";"+current5+";"+power5+";"+current6+";"+power6+";"+current7+";"+power7+";"+current8+";"+power8
                        +";"+current10+";"+power10+";"+current11+";"+power11+";"+current12+";"+power12+";"+current13+";"+power13+";"+current14+";"+power14+";"+current15+";"+power15+";"+current16+";"+power16+";"+current17+";"+power17
                        +";"+current19+";"+power19+";"+current20+";"+power20+";"+current21+";"+power21+";"+current22+";"+power22+";"+current23+";"+power23+";"+current24+";"+power24+";"+current25+";"+power25+";"+current26+";"+power26+";";
                        IdHttp1->Get(Url,stream);    */
                       // Application->MessageBox(Url.c_str(),"show");
                        Source->Add("SERIAL_NUMBER="+SERIAL_NUMBER+"&STATION_NUMBER="+STATION_NUMBER+"&EMP="+EMP+"&INFO=AC_LOAD_TEST;FW;model;voltage;frequency;"+
                        "c1;p1;c2;p2;c3;p3;c4;p4;c5;p5;c6;p6;c7;p7;c8;p8;"+
                        "c10;p10;c11;p11;c12;p12;c13;p13;c14;p14;c15;p15;c16;p16;c17;p17;"+
                        "c19;p19;c20;p20;c21;p21;c22;p22;c23;p23;c24;p24;c25;p25;c26;p26;"+
                        "c28;p28;c29;p29;c30;p30;c31;p31;c32;p32;c33;p33;c34;p34;c35;p35;"+
                        "c37;p37;c38;p38;c39;p39;c40;p40;c41;p41;c42;p42;c43;p43;c44;p44;"+
                        "&VALUE="+AC_LOAD_TEST+";"+FW2+";"+model2+";"+voltage2+";"+frequency2
                        +";"+c1+";"+p1+";"+c2+";"+p2+";"+c3+";"+p3+";"+c4+";"+p4+";"+c5+";"+p5+";"+c6+";"+p6+";"+c7+";"+p7+";"+c8+";"+p8
                        +";"+c10+";"+p10+";"+c11+";"+p11+";"+c12+";"+p12+";"+c13+";"+p13+";"+c14+";"+p14+";"+c15+";"+p15+";"+c16+";"+p16+";"+c17+";"+p17
                        +";"+c19+";"+p19+";"+c20+";"+p20+";"+c21+";"+p21+";"+c22+";"+p22+";"+c23+";"+p23+";"+c24+";"+p24+";"+c25+";"+p25+";"+c26+";"+p26
                        +";"+c28+";"+p28+";"+c29+";"+p29+";"+c30+";"+p30+";"+c31+";"+p31+";"+c32+";"+p32+";"+c33+";"+p33+";"+c34+";"+p34+";"+c35+";"+p35
                        +";"+c37+";"+p37+";"+c38+";"+p38+";"+c39+";"+p39+";"+c40+";"+p40+";"+c41+";"+p41+";"+c42+";"+p42+";"+c43+";"+p43+";"+c44+";"+p44+";");
                        IdHttp1->Post(Url,Source,stream);
                        stream->Position = 0;
                        String result = stream->DataString;
                     //   Application->MessageBox(result.c_str(),"show");
                        char *retur1n = "log_info_ok";
                        char *result1 =result.c_str();
                        if(strcmp(result1,retur1n)!=0)
                        {
                                Application->MessageBox("PE-08Ilog Upload FAIL","show");
                                TelnetForm->Button30->Enabled = true;
                        }
                        else
                        {
                                TelnetForm->Button30->Enabled = false;
                                Application->MessageBox("PE-8INlog Upload PASS","show");
                        }
                       // Application->MessageBox(Url.c_str(),"show");

               // else  Application->MessageBox("log奻�鼳���","show");
               // Application->MessageBox(result.c_str(),"show");
                // strmsg = ss->DataString.Trim();
                }
                if(strcmp(f29,s1)==0&&strcmp(f,f1)!=0&&strcmp(f,f2)!=0&&strcmp(f,f3)!=0&&strcmp(f,f4)!=0&&strcmp(f,f5)!=0&&strcmp(f,f6)!=0&&strcmp(f,f7)!=0&&strcmp(f,f8)!=0&&strcmp(f,f9)!=0
                   &&strcmp(f,f10)!=0&&strcmp(f,f11)!=0&&strcmp(f,f12)!=0&&strcmp(f,f13)!=0&&strcmp(f,f14)!=0&&strcmp(f,f15)!=0&&strcmp(f,f16)!=0&&strcmp(f,f17)!=0&&strcmp(f,f18)!=0
                   &&strcmp(f,f19)!=0&&strcmp(f,f20)!=0&&strcmp(f,f21)!=0&&strcmp(f,f22)!=0&&strcmp(f,f23)!=0&&strcmp(f,f24)!=0&&strcmp(f,f25)!=0&&strcmp(f,f26)!=0&&strcmp(f,f27)!=0
                   &&strcmp(f,f32)!=0&&strcmp(f,f33)!=0&&strcmp(f,f34)!=0&&strcmp(f,f35)!=0&&strcmp(f,f36)!=0&&strcmp(f,f37)!=0&&strcmp(f,f38)!=0&&strcmp(f,f39)!=0&&strcmp(f,f40)!=0
                   &&strcmp(f,f41)!=0&&strcmp(f,f42)!=0&&strcmp(f,f43)!=0&&strcmp(f,f44)!=0&&strcmp(f,f45)!=0&&strcmp(f,f46)!=0&&strcmp(f,f47)!=0&&strcmp(f,f48)!=0&&strcmp(f,f49)!=0
                   &&strcmp(f,f50)!=0&&strcmp(f,f51)!=0&&strcmp(f,f52)!=0&&strcmp(f,f53)!=0&&strcmp(f,f54)!=0&&strcmp(f,f55)!=0&&strcmp(f,f56)!=0&&strcmp(f,f57)!=0&&strcmp(f,f58)!=0
                   &&strcmp(f,f61)!=0&&strcmp(f,f62)!=0&&strcmp(f,f63)!=0&&strcmp(f,f64)!=0&&strcmp(f,f65)!=0&&strcmp(f,f66)!=0&&strcmp(f,f67)!=0&&strcmp(f,f68)!=0&&strcmp(f,f69)!=0
                   &&strcmp(f,f71)!=0&&strcmp(f,f72)!=0&&strcmp(f,f73)!=0&&strcmp(f,f74)!=0&&strcmp(f,f75)!=0&&strcmp(f,f76)!=0&&strcmp(f,f77)!=0&&strcmp(f,f78)!=0&&strcmp(f,f79)!=0
                   &&strcmp(f,f81)!=0&&strcmp(f,f82)!=0&&strcmp(f,f83)!=0&&strcmp(f,f84)!=0&&strcmp(f,f85)!=0&&strcmp(f,f86)!=0&&strcmp(f,f87)!=0&&strcmp(f,f88)!=0&&strcmp(f,f89)!=0
                   &&strcmp(f,f91)!=0&&strcmp(f,f92)!=0&&strcmp(f,f93)!=0&&strcmp(f,f94)!=0&&strcmp(f,f95)!=0&&strcmp(f,f96)!=0&&strcmp(f,f97)!=0&&strcmp(f,f98)!=0&&strcmp(f,f99)!=0
                   &&strcmp(f,f101)!=0&&strcmp(f,f102)!=0&&strcmp(f,f103)!=0&&strcmp(f,f104)!=0&&strcmp(f,f105)!=0&&strcmp(f,f106)!=0&&strcmp(f,f107)!=0&&strcmp(f,f108)!=0&&strcmp(f,f109)!=0
                   &&strcmp(f,f111)!=0&&strcmp(f,f112)!=0&&strcmp(f,f113)!=0&&strcmp(f,f114)!=0&&strcmp(f,f115)!=0&&strcmp(f,f116)!=0&&strcmp(f,f117)!=0&&strcmp(f,f118)!=0&&strcmp(f,f119)!=0
                   &&strcmp(f,f28)!=0&&strcmp(f,f29)!=0&&strcmp(f,f30)!=0&&strcmp(f,f31)!=0)
                {
                        /*AnsiString Url=serveraddress+":8080/or2mac/log_info_versatile?SERIAL_NUMBER="+SERIAL_NUMBER+
                        "&STATION_NUMBER="+STATION_NUMBER+
                        "&EMP="+EMP+
                        "&INFO=FW;model;voltage;frequency;current1;power1;current2;power2;current3;power3;current4;power4;current5;power5;current6;power6;current7;power7;current8;power8;current9;power9;"+
                        "current10;power10;current11;power11;current12;power12;current13;power13;current14;power14;current15;power15;current16;power16;current17;power17;current18;power18;"+
                        "current19;power19;current20;power20;current21;power21;current22;power22;current23;power23;current24;power24;current25;power25;current26;power26;current19;power19;"+
                        "&VALUE="+FW2+";"+model2+";"+voltage2+";"+frequency2+";"+current1+";"+power1+";"+current2+";"+power2+";"+current3+";"+power3+";"+current4+";"+power4+";"+current5+";"+power5+";"+current6+";"+power6+";"+current7+";"+power7+";"+current8+";"+power8+";"+current9+";"+power9
                        +";"+current10+";"+power10+";"+current11+";"+power11+";"+current12+";"+power12+";"+current13+";"+power13+";"+current14+";"+power14+";"+current15+";"+power15+";"+current16+";"+power16+";"+current17+";"+power17+";"+current18+";"+power18
                        +";"+current19+";"+power19+";"+current20+";"+power20+";"+current21+";"+power21+";"+current22+";"+power22+";"+current23+";"+power23+";"+current24+";"+power24+";"+current25+";"+power25+";"+current26+";"+power26+";"+current27+";"+power27+";";
                        IdHttp1->Get(Url,stream);     */
                         Source->Add("SERIAL_NUMBER="+SERIAL_NUMBER+"&STATION_NUMBER="+STATION_NUMBER+"&EMP="+EMP+"&INFO=AC_LOAD_TEST;FW;model;voltage;frequency;"+
                                     "c1;p1;c2;p2;c3;p3;c4;p4;c5;p5;c6;p6;c7;p7;c8;p8;c9;p9;"+
                                     "c10;p10;c11;p11;c12;p12;c13;p13;c14;p14;c15;p15;c16;p16;c17;p17;c18;p18;"+
                                     "c19;p19;c20;p20;c21;p21;c22;p22;c23;p23;c24;p24;c25;p25;c26;p26;c27;p27;"+
                                     "c28;p28;c29;p29;c30;p30;c31;p31;c32;p32;c33;p33;c34;p34;c35;p35;c36;p36;"+
                                     "c37;p37;c38;p38;c39;p39;c40;p40;c41;p41;c42;p42;c43;p43;c44;p44;c45;p45;"+
                                     "c46;p46;c47;p47;c48;p48;c49;p49;c50;p50;c51;p51;c52;p52;c53;p53;c54;p54;"+
                                     "&VALUE="+AC_LOAD_TEST+";"+FW2+";"+model2+";"+voltage2+";"+frequency2
                                     +";"+c1+";"+p1+";"+c2+";"+p2+";"+c3+";"+p3+";"+c4+";"+p4+";"+c5+";"+p5+";"+c6+";"+p6+";"+c7+";"+p7+";"+c8+";"+p8+";"+c9+";"+p9
                                     +";"+c10+";"+p10+";"+c11+";"+p11+";"+c12+";"+p12+";"+c13+";"+p13+";"+c14+";"+p14+";"+c15+";"+p15+";"+c16+";"+p16+";"+c17+";"+p17+";"+c18+";"+p18
                                     +";"+c19+";"+p19+";"+c20+";"+p20+";"+c21+";"+p21+";"+c22+";"+p22+";"+c23+";"+p23+";"+c24+";"+p24+";"+c25+";"+p25+";"+c26+";"+p26+";"+c27+";"+p27
                                     +";"+c28+";"+p28+";"+c29+";"+p29+";"+c30+";"+p30+";"+c31+";"+p31+";"+c32+";"+p32+";"+c33+";"+p33+";"+c34+";"+p34+";"+c35+";"+p35+";"+c36+";"+p36
                                     +";"+c37+";"+p37+";"+c38+";"+p38+";"+c39+";"+p39+";"+c40+";"+p40+";"+c41+";"+p41+";"+c42+";"+p42+";"+c43+";"+p43+";"+c44+";"+p44+";"+c45+";"+p45
                                     +";"+c46+";"+p46+";"+c47+";"+p47+";"+c48+";"+p48+";"+c49+";"+p49+";"+c50+";"+p50+";"+c51+";"+p51+";"+c52+";"+p52+";"+c53+";"+p53+";"+c54+";"+p54+";");
                        IdHttp1->Post(Url,Source,stream);
                       // Application->MessageBox(Url.c_str(),"show");
                        stream->Position = 0;
                        String result = stream->DataString;
                        char *retur1n = "log_info_ok";
                        char *result1 =result.c_str();
                        //Application->MessageBox(result.c_str(),"show");
                        if(strcmp(result1,retur1n)!=0)
                        {
                                Application->MessageBox("PE-09Nlog Upload FAIL","show");
                                TelnetForm->Button30->Enabled = true;
                        }
                        else
                        {
                                Application->MessageBox("PE-09Nlog Upload PASS","show");
                                TelnetForm->Button30->Enabled = false;
                        }
                }       
               // else  Application->MessageBox("log奻�鼳���","show");
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

