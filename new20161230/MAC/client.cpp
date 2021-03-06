//---------------------------------------------------------------------------

#include <vcl.h>
#include "windows.h"
#include "stdio.h"
#include <stdlib.h>
#include <math.h>
#include <io.h>
#include <Setupapi.h>
#include "string.h"
#include "time.h"
#include <idhttp.hpp>

#pragma hdrstop

#include "Client.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
int  updateLogFile(String LogFile, String Data, String burnmac ,String burnsn);
double Data;
int sign;
char currentmac_start[17];
char currentmac_start1[17];
char sn_number[24];
String mac;
String mac1;
String sn;
void Open_File();
int PE_08I_test;
int PE_09N_test;
int CreateLogFile = 0;
char line[255];
FILE *fp_log;
FILE *fp1;
char Station[8];
char EMP[8];
char Serveradder[23];
int i;
String Enter = "\r";

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
   int number1=0;
   int number2=0;
   spnedtPort->Text = "23";
   edtServer->Text = "192.168.1.210";
 //  IP->Text = "192.168.1.252";
   PingIP->Text = "ping -i 192.168.1.111";
   TelnetForm->START->Enabled = false;
   TelnetForm->StartCmd->Enabled = false;
   TelnetForm->Button1->Enabled = false;
   Open_File();

   URL->Text = Serveradder;
  // Station1->Text = Station;
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
   }
   if(PE_09N_test == 1)
   {
        US->Checked = true;
   }
   if(SN->Text.Length()>0)
   {
       if(17 == SN->Text.Length())
       {
           Label5->Caption="";
           MAC->SetFocus();
           if(MAC->Text.Length()>0)
           {
                if(12 != MAC->Text.Length())
                {
                      MAC->SetFocus();
                      Label5->Caption = "MAC length is not correct!";
                }
                if(12 == MAC->Text.Length())
                {
                      Label5->Caption="";
                }
           }
       }
       if(17 != SN->Text.Length())
       {
            Label5->Caption = "SN length is not correct!";
       }
       if((12 != MAC->Text.Length())&&(17 != SN->Text.Length()))
       {
            Label5->Caption = " MAC and SN length is not correct!";
       }
   }
       strcpy(&sn_number[0],SN->Text.c_str());
       String sn_number0 =sn_number[0];
       String sn_number1 = sn_number[1];
       String sn_number2 = sn_number[2];
       String sn_number3 = sn_number[3];
       String sn_number4 = sn_number[4];
       String sn_number5 = sn_number[5];
       String sn_number6 = sn_number[6];
       String sn_number7 = sn_number[7];
       String sn_number8 = sn_number[8];
       String sn_number9 = sn_number[9];
       String sn_number10 = sn_number[10];
       String sn_number11 = sn_number[11];
       String sn_number12 = sn_number[12];
       String sn_number13 = sn_number[13];
       String sn_number14 = sn_number[14];
       String sn_number15 = sn_number[15];
       String sn_number16 = sn_number[16];
   //    String sn_number17 = sn_number[17];
    //   sn = SN->Text.c_str();
    if(SN->Text.Length()>0)
    {
       if(EU->Checked == true)
       {
          if(sn_number0=="P"&&sn_number1=="E"&&sn_number2=="-"&&sn_number3=="0"&&sn_number4=="8"&&sn_number5=="I"&&sn_number6=="C")
          {
              Label6->Caption = "";
              sn=sn_number0+sn_number1+sn_number2+sn_number3+sn_number4+sn_number5+sn_number6+sn_number7+sn_number8+sn_number9+sn_number10+sn_number11+sn_number12+sn_number13+sn_number14+sn_number15+sn_number16;
          }
          else
          {
              TelnetForm->StartCmd->Enabled = false;
              Label6->Caption = "SN inconsistent with models!";
          }
       }
       else if(US->Checked == true)
       {
            if(sn_number0=="P"&&sn_number1=="E"&&sn_number2=="-"&&sn_number3=="0"&&sn_number4=="9"&&sn_number5=="N"&&sn_number6=="C")
            {
                Label6->Caption = "";
                sn=sn_number0+sn_number1+sn_number2+sn_number3+sn_number4+sn_number5+sn_number6+sn_number7+sn_number8+sn_number9+sn_number10+sn_number11+sn_number12+sn_number13+sn_number14+sn_number15+sn_number16;
            }
            else
            {
              TelnetForm->StartCmd->Enabled = false;
              Label6->Caption = "SN inconsistent with models!";
            }
       }
    }
}
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
        Memo1->Lines->Strings[Memo1->Lines->Count-1] =Memo1->Lines->Strings[Memo1->Lines->Count-1]+Buffer.c_str();
        //Application->MessageBox(Buffer.c_str(),"Show");

       /* str=IntToStr(Memo1->Lines->Count);

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
        }                 */

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
        RMAC->Caption = "";
        RSN->Caption = "";

        Application->ProcessMessages();
        ::Sleep(600);
        Application->ProcessMessages();

        IdTelnetDemo->SendCh('\r');
        String ShowDeviceInfo = "show device-info";
        SendCommand(ShowDeviceInfo);
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        ::Sleep(1000);
        Application->ProcessMessages();
        Memo1Display();

        int num5=Memo1->Lines->Count;
        ::Sleep(2500);
        Application->ProcessMessages();
        String yyy5=Memo1->Lines->Strings[num5]+Memo1->Lines->Strings[num5-1]+Memo1->Lines->Strings[num5-2]+Memo1->Lines->Strings[num5+1];
        char *p5 = yyy5.c_str();

        String right52 =  yyy5.SubString((yyy5.Pos("serial_number")+16),28);
        String left52 = right52.SubString(0,(right52.Pos("MAC")-4));
        RSN->Caption = left52;

        String right53 =  yyy5.SubString((yyy5.Pos("MAC")+6),28);
        String left53 = right53.SubString(0,(right53.Pos("hostname")-4));
        RMAC->Caption = left53;
        TelnetForm->START->Enabled = false;

 }
//---------------------------------------------------------------------------
int  updateLogFile(String LogFile, String burnmac, String burnsn)
{
    FILE *fp;
    if ((fp = fopen(LogFile.c_str(), "a+")) == NULL) {
        MessageBox(NULL, "Can not open log.txt file.", "Error", MB_OK);
        fclose(fp);
        return -1;
    }
    char date[9];
    char time[9];

     fprintf(fp,"%s ", _strdate(date));
    fprintf(fp,"%s \n", _strtime(time));
    fprintf(fp, "%s \n", mac1.c_str());
    fprintf(fp, "%s \n", sn.c_str());

    fclose(fp);
    return 0;
}
//----------------------------------------------------------------------------

void __fastcall TTelnetForm::Button5Click(TObject *Sender)
{
        String str,str1;
        IdTelnetDemo->Host = edtServer->Text;
        str = edtServer->Text;
        IdTelnetDemo->Port = StrToInt(spnedtPort->Text);
        str1 = spnedtPort->Text;
        Memo1->Clear();
        IdTelnetDemo->Connect();
        Result3->Caption = "";
        Application->ProcessMessages();
        ::Sleep(1000);
        Application->ProcessMessages();
        Memo1Display();

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
      //  Memo1->Lines->Add("");
       // IdTelnetDemo->SendCh('\n');
        Application->ProcessMessages();
        ::Sleep(500);
        Application->ProcessMessages();
        TelnetForm->StartCmd->Enabled = true;
        TelnetForm->START->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TTelnetForm::StartCmdClick(TObject *Sender)
{
       Label5->Caption = "";
       String a = ":";
       mac1 = MAC->Text.c_str();

       strcpy(&currentmac_start[0],MAC->Text.c_str());
       String currentmac_start0 =currentmac_start[0];
       String currentmac_start1 = currentmac_start[1];
       String currentmac_start2 = currentmac_start[2];
       String currentmac_start3 = currentmac_start[3];
       String currentmac_start4 = currentmac_start[4];
       String currentmac_start5 = currentmac_start[5];
       String currentmac_start6 = currentmac_start[6];
       String currentmac_start7 = currentmac_start[7];
       String currentmac_start8 = currentmac_start[8];
       String currentmac_start9 = currentmac_start[9];
       String currentmac_start10 = currentmac_start[10];
       String currentmac_start11 = currentmac_start[11];

        mac = currentmac_start0+ currentmac_start1+ a +currentmac_start2+ currentmac_start3+ a + currentmac_start4+ currentmac_start5+ a +currentmac_start6+ currentmac_start7+ a +currentmac_start8+ currentmac_start9+ a +currentmac_start10+ currentmac_start11;
      // RMAC->Caption = mac;
    /*   strcpy(&sn_number[0],SN->Text.c_str());
       String sn_number0 =sn_number[0];
       String sn_number1 = sn_number[1];
       String sn_number2 = sn_number[2];
       String sn_number3 = sn_number[3];
       String sn_number4 = sn_number[4];
       String sn_number5 = sn_number[5];
       String sn_number6 = sn_number[6];
       String sn_number7 = sn_number[7];
       String sn_number8 = sn_number[8];
       String sn_number9 = sn_number[9];
       String sn_number10 = sn_number[10];
       String sn_number11 = sn_number[11];
       String sn_number12 = sn_number[12];
       String sn_number13 = sn_number[13];
       String sn_number14 = sn_number[14];
       String sn_number15 = sn_number[15];
       String sn_number16 = sn_number[16];
   //    String sn_number17 = sn_number[17];
    //   sn = SN->Text.c_str();
       if(EU->Checked == true)
       {
          if(sn_number0=="P"&&sn_number1=="E"&&sn_number2=="-"&&sn_number3=="0"&&sn_number4=="8"&&sn_number5=="I"&&sn_number6=="C")
          {
              sn=sn_number0+sn_number1+sn_number2+sn_number3+sn_number4+sn_number5+sn_number6+sn_number7+sn_number8+sn_number9+sn_number10+sn_number11+sn_number12+sn_number13+sn_number14+sn_number15+sn_number16;
          }
          else
          {
              Label6->Caption = "SN inconsistent with models!";
          }
       }
       else if(US->Checked == true)
       {
            if(sn_number0=="P"&&sn_number1=="E"&&sn_number2=="-"&&sn_number3=="0"&&sn_number4=="9"&&sn_number5=="N"&&sn_number6=="C")
            {
                sn=sn_number0+sn_number1+sn_number2+sn_number3+sn_number4+sn_number5+sn_number6+sn_number7+sn_number8+sn_number9+sn_number10+sn_number11+sn_number12+sn_number13+sn_number14+sn_number15+sn_number16;
            }
            else
            {
              Label6->Caption = "SN inconsistent with models!";
            }
       }   */
      //  RSN->Caption = sn;
////--------------------@mark to add read log.txt info and comparison  start_mac & end_mac & SN start-------------------
    if(EU->Checked == true)
    {
        if((CreateLogFile == 0)&&(fopen("08Ilog.txt","r")==NULL))
	{
		fp1 = fopen("08Ilog.txt", "a+");
		fclose(fp1);
		CreateLogFile=1;
	}

	if ( (fp_log=fopen("08Ilog.txt","r")) == NULL )
	{
                MessageBox(NULL, "Not have 08Ilog.txt! Check 08Ilog.txt", "Error", MB_OK);
		return;
	}
           {
		while(fgets(line,255,fp_log))
		{
                        if(strstr(line,currentmac_start) != NULL)
			{
                                Application->MessageBox("MAC Repeat","show");
                                Application->MessageBox(currentmac_start,"show");
                                Application->MessageBox("Check 08Ilog.txt and MAC","show");
                                TelnetForm->StartCmd->Enabled = false;
                                IdTelnetDemo->Disconnect();
				return;
			}
                        if(strstr(line,sn_number) != NULL)
			{
                                Application->MessageBox("SN Repeat","show");
                                Application->MessageBox(sn_number,"show");
                                Application->MessageBox("Check 08Ilog.txt and SN","show");
				TelnetForm->StartCmd->Enabled = false;
                                IdTelnetDemo->Disconnect();
                                return;
			}
		}
		fclose(fp_log);
            }
    }
    if(US->Checked == true)
    {
        if((CreateLogFile == 0)&&(fopen("09Nlog.txt","r")==NULL))
	{
		fp1 = fopen("09Nlog.txt", "a+");
		fclose(fp1);
		CreateLogFile=1;
	}

	if ( (fp_log=fopen("09Nlog.txt","r")) == NULL )
	{
                MessageBox(NULL, "Not have 09Nlog.txt! Check 09Nlog.txt", "Error", MB_OK);
		return;
	}
           {
		while(fgets(line,255,fp_log))
		{
                        if(strstr(line,currentmac_start) != NULL)
			{
                                Application->MessageBox("MAC Repeat","show");
                                Application->MessageBox(currentmac_start,"show");
                                Application->MessageBox("Check 09Nlog.txt and MAC","show");
                                TelnetForm->StartCmd->Enabled = false;
                                IdTelnetDemo->Disconnect();
				return;
			}
                        if(strstr(line,sn_number) != NULL)
			{
                                Application->MessageBox("SN Repeat","show");
                                Application->MessageBox(sn_number,"show");
                                Application->MessageBox("Check 09Nlog.txt and SN","show");
				TelnetForm->StartCmd->Enabled = false;
                                IdTelnetDemo->Disconnect();
                                return;
			}
		}
		fclose(fp_log);
            }
    }
        IdTelnetDemo->SendCh('\r');
        String BurnMACandSN = "set pdu-conf -m "+ mac + " -s " +sn;
        SendCommand(BurnMACandSN);
      //  Memo1->Lines->Add("Pakedge-PDU$ set pdu-conf -m  mac -s sn ");
      //  Memo1->Lines->Add("");
     //   IdTelnetDemo->SendCh('\n');
        ::Sleep(500);
        Application->ProcessMessages();
        SendCommand(Enter);
        ::Sleep(1000);
        Application->ProcessMessages();
        Memo1Display();

        int num1=Memo1->Lines->Count;
        ::Sleep(2000);
        Application->ProcessMessages();

        String yyy1=Memo1->Lines->Strings[num1-1]+Memo1->Lines->Strings[num1]+Memo1->Lines->Strings[num1-2]+Memo1->Lines->Strings[num1+1];
        char *p1 = yyy1.c_str();
        //Application->MessageBox(yyy1.c_str(),"Show");
        char *cmd1 = "success";
        if(strstr(p1,cmd1) != NULL)
        {
            Result3->Caption = "PASS";
            TelnetForm->StartCmd->Enabled = false;
            TelnetForm->Button1->Enabled = true;
           if(EU->Checked == true)
           {
                updateLogFile("08Ilog.txt",mac1,sn);
           }
           else if(US->Checked == true)
           {
                updateLogFile("09Nlog.txt",mac1,sn);
           }
        }
        else
        {
                Result3->Caption = "FAIl";
                TelnetForm->StartCmd->Enabled = true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::Button6Click(TObject *Sender)
{
        TelnetForm->StartCmd->Enabled = false;
        TelnetForm->START->Enabled = false;
        IdTelnetDemo->Disconnect();
}
//---------------------------------------------------------------------------

void __fastcall TTelnetForm::ClearClick(TObject *Sender)
{
        MAC->Text = "";
        SN->Text = "";
        Label6->Caption = "";
        Label5->Caption = "";
        RMAC->Caption = "";
        RSN->Caption = "";
        SN->SetFocus();
        
        TelnetForm->StartCmd->Enabled = false;
}
//---------------------------------------------------------------------------

void Open_File()
{
        String filepath;
        TCHAR   currentpath[200];
        char PE_08I[2];
        char PE_09N[2];

        GetCurrentDirectory(255,currentpath);
        filepath=String(currentpath);
        filepath +="\\config.ini";

        memset(Serveradder,0,24);
        GetPrivateProfileString("PDU-TEST","Serveradder"," ",Serveradder,24,filepath.c_str());

        memset(Station,0,8);
        GetPrivateProfileString("PDU-TEST","Station"," ",Station,8,filepath.c_str());

        memset(EMP,0,8);
        GetPrivateProfileString("PDU-TEST","EMP"," ",EMP,8,filepath.c_str());

        memset(PE_08I,0,2);
        GetPrivateProfileString("PDU-TEST","PE-08I"," ",PE_08I,2,filepath.c_str());        PE_08I_test = atoi(PE_08I);        memset(PE_09N,0,2);        GetPrivateProfileString("PDU-TEST","PE-09N"," ",PE_09N,2,filepath.c_str());        PE_09N_test = atoi(PE_09N);
}
//---------------------------------------------------------------------------


void __fastcall TTelnetForm::Button1Click(TObject *Sender)
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
                String MAC_SN_TEST = "MAC_SN_TEST";
                String serveraddress = URL->Text.c_str();
                String SERIAL_NUMBER = PCBASN->Text.c_str();
               // String STATION_NUMBER = Station1->Text.c_str();
                String STATION_NUMBER = Station;
                //Application->MessageBox(STATION_NUMBER.c_str(),"show");
                String EMP = EMP1->Text.c_str();
                String aSN = SN->Text.c_str();
                String aMAC = MAC->Text.c_str();
                AnsiString Url=serveraddress+":8080/or2mac/pdu/log_info";
                if(Result3->Caption == "PASS")
                {
                        Source->Add("SERIAL_NUMBER="+SERIAL_NUMBER+"&STATION_NUMBER="+STATION_NUMBER+"&EMP="+EMP+"&INFO=MAC_SN_TEST;MAC;SN;&VALUE="+MAC_SN_TEST+";"+aMAC+";"+aSN+";");
                        IdHttp1->Post(Url,Source,stream);
                        stream->Position = 0;
                        String result = stream->DataString;
                      //  Application->MessageBox(result.c_str(),"show");
                        char *retur1n = "log_info_ok";
                        char *result1 =result.c_str();
                        if(strcmp(result1,retur1n)!=0)
                        {
                                Application->MessageBox("log上傳失敗","show");
                                TelnetForm->Button1->Enabled = true;
                        }
                        else
                        {
                                Application->MessageBox("log上傳成功","show");
                                TelnetForm->Button1->Enabled = false;
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
//---------------------------------------------------------------------------

