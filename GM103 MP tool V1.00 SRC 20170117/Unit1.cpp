//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <windows.h>
#include <Iphlpapi.h>

#include "Unit1.h"
#include <Registry.hpp>
#include <idhttp.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

#define SIZEOFARRAY                             1024            // Size of read buffer

bool ifu_rs232_open();
bool ifu_load_cfg_data();

void show_result(int flag);

String MAC_ADD_A(String MAC_ADD_A , int A); //@jack add to add mac by 1  20160306


int upgrade_codes();
int GetPCNetWorkAddress();
int get_login_prompt(int flag, char *pattern);


HANDLE COM1;
int Com_Port_DUT;
char TxdBuffer[SIZEOFARRAY + 1];
char RxdBuffer[SIZEOFARRAY + 1];
char RxdBuffer_ver[SIZEOFARRAY + 1];
char TxdBuffer_ver[SIZEOFARRAY + 1];
char MsgBuffer[80];

char TX_Command[48];

char TX_START_MAC[24];
char TX_END_MAC[24];

char PCBA_SN_Length[3];
char Serveradder[24];
char Station[8];
char EMP[8];

int tSerialTimeOut=500;
int GetAdaptersInfoFlag = 0;

DWORD dw_Read;
DWORD dw_Write;
DCB dcb;

//define read mac address from "MACADDR.ini" file.
void Open_File();
void Open_File_Start_End();
int mac_check( char *lpmac , char *lpstart ,char *lpend);

int mac_more_than(char *lp_addr, char *lp_max);
int mac_equal(char *lpsz_addr_A, char *lpsz_addr_B);
void Save_log(char *p);
String MacAdd(String lbl , int a);

char currentmac_start[13];
char currentmac_end[13];
char readstart[13];
char readend[13];
char passread[7];
int passcount;
void Compare_log();

bool timeout = 1;
//bool COM_flag = 0;

int text_i = 0;
int text_flag = 0;

int check_version(char *p,int i);
char fw_version[16];
char *sys_version;  // sys fw version
int double_check_ver = 0; // result flag.

void double_check(char *str_p);

int double_check_mac_start;
int double_check_mac_end;
int double_check_fw;

typedef void (*EventListRunValues)(const char* key, const char* value);
typedef void (*EventListRunOnceValues)(const char* key, const char* value);

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        Open_File();                              
        String serveradder = Serveradder;
        String emp = EMP;
        #if 1      //for MES
        TIdHTTP *IdHttp1;
        try{
                IdHttp1=new TIdHTTP(Application);
                TStringList  *Source=new  TStringList();
                TStringStream  *stream=new  TStringStream("");
                IdHttp1->Request->ContentType="application/x-www-form-urlencoded;charset=UTF-8";
                //     Source->Add("testetss");
                AnsiString Url=serveradder+":8080/or2mac/check_emp?EMP_NO="+emp;
                //Application->MessageBox(Url.c_str(),"show");
                IdHttp1->Get(Url,stream);
                stream->Position = 0;
                String result = stream->DataString;
               // Application->MessageBox(result.c_str(),"show");
                char *retur1n = "check_emp_failed";
                char *result1 =result.c_str();
                if(strcmp(result1,retur1n)==0)
                {
                        Application->MessageBox("Tester Number is invalid!!check the Tester Number!!","show");
                        exit(0);
                }
                delete   IdHttp1;
                delete   stream;
                delete   Source;
             } catch(Exception &e)
                {
                        Application->MessageBox("出現異常，請確認網絡是否暢通！","Error");
                        if(IdHttp1!=NULL)delete IdHttp1;
                        exit(0);
                }
        #endif
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        Open_File();
        String number = PCBA_SN_Length;
        int number1 = StrToInt(number);
        PCBASN->MaxLength = number1;
        URL->Text = Serveradder;
        String serveradder = Serveradder;
        String emp = EMP;
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
        if ( text_flag == 1 )
        {
               //text_flag 琌耞 pass膥尿縉礛р┮ΤEdit硄硄睲 Ω磅︽ぃ穦秈ㄓ硂.
               MAC->Text = "" ;
               END_MAC->Text = "" ;
               PCBASN->Text = "" ;
        }
        text_flag = 0 ;
        if ( 12 == MAC->Text.Length())
        {
                text_i += 1 ;    //ノㄓ璸衡秈ㄓ耞块篈Ω计┤びΩ穦紇臫笲.
                END_MAC->SetFocus();
                if ( 12 == END_MAC->Text.Length())
                {
                    text_i += 1 ;
                    //Application->MessageBox("END_MAC", "mac", MB_OK);
                    PCBASN->SetFocus();
                    if (PCBASN->MaxLength != PCBASN->Text.Length())
                    {
                        PCBASN->SetFocus();
                    }
                    if(PCBASN->MaxLength == PCBASN->Text.Length())
                    {
                        text_i = 0 ;
                        Form1->StartCmd->SetFocus();
                        Form1->StartCmd->Click();
                    }
                }
         }

        if ( text_i > 200)
        {
             char msg[16];
             wsprintf(msg,"%d:岿粇びΩ祘闽超!!",text_i);
             Application->MessageBox(msg, "mac", MB_OKCANCEL);
             //Save_log("Busy used,please restart the mp tool,thanke.");   //@jack delete to save error info to log.txt  20160306
             //SendMessage(Form1,WM_CLOSE,0,0);
             Close();
             return ;
        }
}


//---------------------------------------------------------------------------
void __fastcall TForm1::StartCmdClick(TObject *Sender)
{
    char line[255];
    FILE *fp_log;
    FILE *fp1;
    int CreateLogFile = 0;
    String add_mac,current_start_mac;
    show_result(2);

    // 璶Τ硂Message Box穦琵 show_result Τ肅︹跑て --2013-04-12 By Hearn--
    #if 0
    if (Application->MessageBox("絋﹚秨﹍盾?","玻代祘Α",MB_OKCANCEL) == IDCANCEL)
    {
        show_result(3);
        Label2->Caption = "";
        Label8->Caption = "";
        Label12->Caption = "";
        goto EXIT;
    }
    #endif
    #if 1    //for MES
    Open_File();
    String serveradder = Serveradder;
    String emp = EMP;
    if(PCBASN->Text.Length()>0)
    {
          TIdHTTP *IdHttp1;
          try{
                String SERIAL_NUMBER = PCBASN->Text.c_str();
                IdHttp1=new TIdHTTP(Application);
                TStringList  *Source=new  TStringList();
                TStringStream  *stream=new  TStringStream("");
                IdHttp1->Request->ContentType="application/x-www-form-urlencoded;charset=UTF-8";
                //     Source->Add("testetss");
                AnsiString Url=serveradder+":8080/or2mac/check_sn?SERIAL_NUMBER="+SERIAL_NUMBER;
                //Application->MessageBox(Url.c_str(),"show");
                IdHttp1->Get(Url,stream);
                stream->Position = 0;
                String result = stream->DataString;
               // Application->MessageBox(result.c_str(),"show");
                char *retur1n = "check_sn_failed";
                char *result1 =result.c_str();
                if(strcmp(result1,retur1n)!=0)
                {
                        Application->MessageBox("MES MAC&SN repeat","show");
                        goto EXIT;
                }
                delete   IdHttp1;
                delete   stream;
                delete   Source;
             } catch(Exception &e)
                {
                        Application->MessageBox("出現異常，請確認網絡是否暢通！","Error");
                        if(IdHttp1!=NULL)delete IdHttp1;
                        goto EXIT;
                }
    }
    #endif
    StartCmd->Enabled = False;
    RadioCOM1->Enabled = False;
    RadioCOM2->Enabled = False;
    RadioButton1->Enabled = False;
    RadioButton2->Enabled = False;
    RadioButton3->Enabled = False;
    RadioButton4->Enabled = False;

    Label2->Caption = "";
    Label12->Caption = "";
    Label8->Caption = "";

    timeout = 1;

    Memo1->Clear();
    
    show_result(2);

        // start check start_mac
        if ( MAC->Text.Length() > 0 )
        {
                Open_File_Start_End();

                //----- check start_mac length -----
                if (12 != MAC->Text.Length())
                {
  	                Label2->Font->Color = clRed;
                        Label2->Caption = "START MAC's length is not correct!!";
                        //Save_log("mac_start's length is not currect.");  //@jack delete to save error info to log.txt  20160306
                        show_result(1);
                        goto EXIT;
                }
                //----- end -----

                //----- check start_mac type -----
                strcpy(&currentmac_start[0],MAC->Text.c_str());

                for ( int i=0;i<12;i++)
                {
  	              if (currentmac_start[i]>='0' &&  currentmac_start[i]<='9')
                      {

                      }
                      else if (currentmac_start[i]>='A' &&  currentmac_start[i]<='F')
                      {

                      }
  	              else
                      {
                        Label2->Font->Color = clRed;
                        Label2->Caption = "START MAC is illegal.";
                        //Save_log("mac_start's type is illegal.");   //@jack delete to save error info to log.txt  20160306
                        show_result(1);
                        goto EXIT;
                      }
                 }
                 //----- end ------

                 //----- check start_mac range -----
                 if(-1 == mac_check(currentmac_start, readstart, readend))
                 {
                        Label2->Font->Color = clRed;
                        Label2->Caption = "START MAC out of the range.";
                        //Save_log("mac_start out of the range.");
                        show_result(1);
                        goto EXIT;
                 }
                 //----- end -----
        }
        else
        {
              Label2->Font->Color = clRed;
              Label2->Caption = "Use the Mac of the MACADDR.ini file.";
              Open_File();
        }
        //----- end start_mac check -----

        //check end_mac length
        if ( END_MAC->Text.Length() > 0 )
        {
                Open_File_Start_End();

                //----- check end_mac length -----
                if (12 != END_MAC->Text.Length())
                {
  	                Label2->Font->Color = clRed;
                        Label2->Caption = "END MAC's length is not correct!!";
                        //Save_log("mac_end's length is not correct.");    //@jack delete to save error info to log.txt  20160306
                        show_result(1);
                        goto EXIT;
                }
                //----- end -----

                //----- check end_mac type -----
                strcpy(&currentmac_end[0],END_MAC->Text.c_str());

                for ( int i=0;i<12;i++)
                {
  	              if (currentmac_end[i]>='0' &&  currentmac_end[i]<='9')
                      {

                      }
                      else if (currentmac_end[i]>='A' &&  currentmac_end[i]<='F')
                      {

                      }
  	              else
                      {
                        Label2->Font->Color = clRed;
                        Label2->Caption = "END MAC is illegal";
                        //Save_log("mac_end's type is illegal.");  //@jack delete to save error info to log.txt  20160306
                        show_result(1);
                        goto EXIT;
                      }
                 }
                 //----- end ------

                 //----- check end_mac range -----
                 if(-1 == mac_check(currentmac_end, readstart, readend))
                 {
                        Label2->Font->Color = clRed;
                        Label2->Caption = "END MAC out of the range.";
                        //Save_log("mac_end out of the range.");   //@jack delete to save error info to log.txt  20160306
                        show_result(1);
                        goto EXIT;
                 }
                 //----- end -----
        }
        else
        {
              Label2->Font->Color = clRed;
              Label2->Caption = "Use the Mac of the MACADDR.ini file.";
              Open_File();
        }
        //----- end end_mac check -----


////--------------------@jack to add read log.txt info and comparison  start_mac & end_mac & SN start-------------------
        if((CreateLogFile == 0)&&(fopen("log.txt","r")==NULL))
	{
		fp1 = fopen("log.txt", "a+");
		fclose(fp1);
		CreateLogFile=1;
	}

	if ( (fp_log=fopen("log.txt","r")) == NULL )
	{
                MessageBox(NULL, "Not have log.txt! Check log.txt", "Error", MB_OK);
		return;
	}

	{	
		while(fgets(line,255,fp_log))
		{
			if(strstr(line,currentmac_start) != NULL)
			{
                                Application->MessageBox("start_mac Repeat","show");
                                Application->MessageBox(currentmac_start,"show");
                                Application->MessageBox("Check log.txt and start_mac","show");
                                show_result(1);
                                show_result(20);
				return;
			}
                        if(strstr(line,currentmac_end) != NULL)
			{
                                Application->MessageBox("end_mac Repeat","show");
                                Application->MessageBox(currentmac_end,"show");
                                Application->MessageBox("Check log.txt and end_mac","show");
                                show_result(1);
                                show_result(20);
				return;
			}
		}
		fclose(fp_log);
	}
        
        current_start_mac = currentmac_start;

        // add_mac = MAC_ADD_A(current_start_mac , 24); //@jack add to 24port(GS1900-24E) mac check
       // add_mac = MAC_ADD_A(current_start_mac , 16); //@jack add to 16port(GS1900-16) mac check
         //add_mac = MAC_ADD_A(current_start_mac , 8); //@jack add to 8port(GS1900-8HP or GS1900-8) mac check
          add_mac = MAC_ADD_A(current_start_mac , 10); //@Mark add to 11port(GM103) mac check

        //Application->MessageBox(current_start_mac.c_str(),"show");
        //Application->MessageBox(add_mac.c_str(),"show");

        if(add_mac != currentmac_end)
        {
                Application->MessageBox("MAC range is not correct","show");
                Application->MessageBox("Check MAC","show");
                show_result(1);
                show_result(22);
                return;
        }

////--------------------@jack to add read log.txt info and comparison  start_mac & end_mac & SN end-------------------

        // show input value on the Edit.
        sprintf(MsgBuffer, "%s ~ %s",readstart,readend);
        Start->Caption = MsgBuffer ;
        MAC->Text = currentmac_start ;
        END_MAC->Text = currentmac_end ;
        //----- end -----

    // access RS232
    #if 1
    if (!ifu_rs232_open()) {
        sprintf(MsgBuffer, "failed to open COM port for DUT");
        strcat(TxdBuffer, MsgBuffer);
        Application->MessageBox(TxdBuffer, "Error");
        show_result(1);
        goto EXIT;
    }
    #endif

    // ----- edn -----
#if 1   //秨﹍縉笆1:秈︽  0:ぃ秈︽
    Timer1->Interval = 0;
    memset(RxdBuffer, NULL, sizeof(RxdBuffer));
    if (get_login_prompt(1, "RTL838x#"))
    {

        if ( upgrade_codes())
        {
            show_result(7);  // Burn successfully.
        }
        else
        {
            //Save_log("Burn mac error.");   //@jack delete to save error info to log.txt  20160306
            show_result(1);  //Fail
            return;
        }
    }
    else
    {
        //Save_log("Can not enter the debug mode.");    //@jack delete to save error info to log.txt  20160306
        show_result(1);      //Fail
        return;
    }


#else if
        ShowMessage("This is a test mode!");
#endif

/////////////////////////////////double check function////////////////////////////////////
                //Compare_log();

                //2013-07-19 Add the fw_version by Hearn.
                Label8->Font->Color = clBlue;
                Label8->Caption = fw_version;

                //show_result(5);

//////////////////////////////////double check mac start/////////////////////////////////////////////

                /* The device be reset into the bootloader.*/
             #if 0
                WriteFile(COM1, "reset", 6, &dw_Write, 0);
                //Sleep(7000);
             #endif

                /* double check the value of burn in.  */
                double_check("printsys dualfname0");
                ::Sleep(2000);

                if( double_check_fw = 0 ) {
                   //Save_log("double check fail."); //@jack delete to save error info to log.txt  20160306
                   ::Sleep(2000);
                   show_result(1);
                   goto EXIT;
                }

#if 1     //@jack add to check burning MAC&SN is OK ?  20160409

                char check_smac[18];
                char check_emac[18];

                memset(check_smac, '\0', sizeof(check_smac));
                memset(check_emac, '\0', sizeof(check_emac));

                memset(check_smac, ':', sizeof(check_smac));
                memset(check_emac, ':', sizeof(check_emac));

                //Application->MessageBox(check_smac,"show");
                //Application->MessageBox(check_emac,"show");

                check_smac[0] = currentmac_start[0];
                check_smac[1] = currentmac_start[1];
                check_smac[3] = currentmac_start[2];
                check_smac[4] = currentmac_start[3];
                check_smac[6] = currentmac_start[4];
                check_smac[7] = currentmac_start[5];
                check_smac[9] = currentmac_start[6];
                check_smac[10] = currentmac_start[7];
                check_smac[12] = currentmac_start[8];
                check_smac[13] = currentmac_start[9];
                check_smac[15] = currentmac_start[10];
                check_smac[16] = currentmac_start[11];
                check_smac[17] = '\0';

                check_emac[0] = currentmac_end[0];
                check_emac[1] = currentmac_end[1];
                check_emac[3] = currentmac_end[2];
                check_emac[4] = currentmac_end[3];
                check_emac[6] = currentmac_end[4];
                check_emac[7] = currentmac_end[5];
                check_emac[9] = currentmac_end[6];
                check_emac[10] = currentmac_end[7];
                check_emac[12] = currentmac_end[8];
                check_emac[13] = currentmac_end[9];
                check_emac[15] = currentmac_end[10];
                check_emac[16] = currentmac_end[11];
                check_emac[17] = '\0';
                ::Sleep(500);

                //Application->MessageBox(check_smac,"show");
               // Application->MessageBox(check_emac,"show");

                double_check("printenv ethaddr");
                ::Sleep(1000);

                //Application->MessageBox(RxdBuffer_ver,"show");

                if( strstr(RxdBuffer_ver , check_smac) == NULL)
                {
                   //Save_log("Differnet MAC Start.");
                   ::Sleep(500);
                   show_result(1);
                   goto EXIT;
                   //return;
                }

                double_check("printsys mac_start");
                ::Sleep(1000);

                //Application->MessageBox(RxdBuffer_ver,"show");

                if( strstr(RxdBuffer_ver , check_smac) == NULL)
                {
                   //Save_log("Differnet MAC Start.");
                   ::Sleep(500);
                   show_result(1);
                   goto EXIT;
                   //return;
                }

                double_check("printsys mac_end");
                ::Sleep(1000);

                //Application->MessageBox(RxdBuffer_ver,"show");

                if( strstr(RxdBuffer_ver , check_emac) == NULL)
                {
                   //Save_log("Differnet MAC End.");
                   ::Sleep(500);
                   show_result(1);
                   goto EXIT;
                   //return;
                }

#endif

#if 1       //Mark add  upload MAC  SN to MES
        TIdHTTP *IdHttp1;
        try{
                IdHttp1=new TIdHTTP(Application);
                TStringList  *Source=new  TStringList();
                TStringStream  *stream=new  TStringStream("");
                IdHttp1->Request->ContentType="application/x-www-form-urlencoded;charset=UTF-8";
                //     Source->Add("testetss");
                if(IdHttp1==NULL)
                {
                         Application->MessageBox("無法進行Http請求，請確認上傳的server地址是否正確！","show");
                         goto EXIT;
                        //return;
                }
                
                //String MAC_SN_TEST = "MAC_SN_TEST";
                String serveraddress = URL->Text.c_str();
                String SERIAL_NUMBER = PCBASN->Text.c_str();
              //  String STATION_NUMBER = Station1->Text.c_str();
                String STATION_NUMBER = Station;
                //Application->MessageBox(STATION_NUMBER.c_str(),"show");
                String EMP = EMP1->Text.c_str();
                String smac = MAC->Text.c_str();
                String emac = END_MAC->Text.c_str();
                char *f = "";
                char *f1 = serveraddress.c_str();
                char *f2 = SERIAL_NUMBER.c_str();
                char *f3 = STATION_NUMBER.c_str();
                char *f4 = EMP.c_str();
                char *f5 = smac.c_str();
                char *f6 = emac.c_str();
                AnsiString Url=serveraddress+":8080/or2mac/log_info";
                if(strcmp(f,f1)!=0&&strcmp(f,f2)!=0&&strcmp(f,f3)!=0&&strcmp(f,f4)!=0&&strcmp(f,f5)!=0&&strcmp(f,f6)!=0)
                {
                        Source->Add("SERIAL_NUMBER="+SERIAL_NUMBER+"&STATION_NUMBER="+STATION_NUMBER+"&EMP="+EMP+"&INFO=STARTMAC;ENDMAC;&VALUE="+smac+";"+emac+";");
                        IdHttp1->Post(Url,Source,stream);
                        stream->Position = 0;
                        String result = stream->DataString;
                        //Application->MessageBox(result.c_str(),"show");
                        char *retur1n = "log_info_ok";
                        char *result1 =result.c_str();
                        if(strcmp(result1,retur1n)!=0)
                        {
                                Application->MessageBox(result.c_str(),"Error");
                                goto EXIT;
                        }
                        else
                        {
                               // Application->MessageBox("LOG上傳成功","show");
                        }

                        delete   IdHttp1;
                        delete   stream;
                        delete   Source;
                }
                else
                {
                      Application->MessageBox("上傳的數據為空，請重新確認","Error");
                      goto EXIT;
                }
             } catch(Exception &e)
                {
                        Application->MessageBox("上傳出現異常，請確認網絡是否暢通！","Error");
                        Form1->Label7->Caption = "Fail"   ;
                        Form1->Label7->Font->Size = 48;
                        Form1->Label7->Font->Color = clRed ;
                        if(IdHttp1!=NULL)delete IdHttp1;
                        return;
                        goto EXIT;
                }
#endif
//////////////////////////////////double check mac end/////////////////////////////////////////////

/////////////////////////////////PASS/////////////////////////////////////////
                 //Compare_log();
                 Save_log("Success.");     // 祘禲硂娩硄筁┮Τ喷靡
                 show_result(0);

//////////////////////////////////////////////////////////////////////////////
EXIT:
    Timer1->Enabled = False;
    //StartCmd->Enabled = True;
    RadioCOM1->Enabled = True;
    RadioCOM2->Enabled = True;
    RadioButton1->Enabled = True;
    RadioButton2->Enabled = True;
    RadioButton3->Enabled = True;
    RadioButton4->Enabled = True;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::QuitCmdClick(TObject *Sender)
{
    Timer1->Enabled = False;
    StartCmd->Enabled = True;
    RadioCOM1->Enabled = True;
    RadioCOM2->Enabled = True;
    RadioButton1->Enabled = True;
    RadioButton2->Enabled = True;
    RadioButton3->Enabled = True;
    RadioButton4->Enabled = True;
    exit(0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    timeout = 0;
}
//---------------------------------------------------------------------------

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

    if (Form1->RadioCOM1->Checked)
      {  PortID = "Com1";  }
    else if(Form1->RadioCOM2->Checked)
      {  PortID = "Com2";  }
    else if(Form1->RadioButton1->Checked)
      {  PortID = "Com3";  }
    else if(Form1->RadioButton2->Checked)
      {  PortID = "Com4";  }
    else if(Form1->RadioButton3->Checked)
      {  PortID = "Com5";  }
    else
      {  PortID = "Com6";  }

    if (!BuildCommDCB("115200, n, 8, 1", &dcb)) {
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

    if (!SetCommState(COM1, &dcb)) {
      strcat(TxdBuffer, "Unable to initial serial Port\n");
      w_result = false;
    }

    if (!SetupComm(COM1, 512, 512)) {
      strcat(TxdBuffer, "Unable to Setup serial port Buffer\n");
      w_result = false;
    }

    if (!SetCommTimeouts(COM1, &TimeOut)) {
      strcat(TxdBuffer, "Unable to Setup serial Port Timeouts\n");
      w_result = false;
    }
    memset(TxdBuffer, NULL, sizeof(TxdBuffer));//琵debug癟ぃ璶仓!!

    return (w_result);
}
//---------------------------------------------------------------------------

void show_result(int flag)
{
    switch(flag) {
      case 0:
        Form1->Label7->Caption = "Pass"   ;
        Form1->Label7->Font->Size = 48;
        Form1->Label7->Font->Color = clGreen ;
        text_i = 0;
        text_flag = 1 ;
        CloseHandle(COM1);
        break;
      case 1:
        Form1->Label7->Caption = "Fail"   ;
        Form1->Label7->Font->Size = 48;
        Form1->Label7->Font->Color = clRed ;
        CloseHandle(COM1);
        break;
      case 2:
        Form1->Label7->Caption = "Wait"   ;
        Form1->Label7->Font->Size = 48;
        Form1->Label7->Font->Color = clYellow ;
        Form1->Label7->ParentColor =  clRed ;
        Form1->Label2->Caption = "";
        Form1->Label12->Caption = "";
        Form1->Label8->Caption = "";
        break;
      case 3:
        Form1->Label7->Caption = "Ready"   ;
        Form1->Label7->Font->Size = 48;
        Form1->Label7->Font->Color = clBlue ;
        break;
      case 4:
        Form1->Label7->Caption = "NG"   ;
        Form1->Label7->Font->Size = 48;
        Form1->Label7->Font->Color = clRed ;
	Form1->Label2->Font->Color = clRed;
        Form1->Label2->Caption = "FW different!";
        CloseHandle(COM1);
        break;
      case 5:
        Form1->Label12->Caption = "FW match"   ;
        Form1->Label12->Font->Size = 12;
        Form1->Label12->Font->Color = clGreen ;
        //Form1->Label12->ParentColor =  clRed ;
        break;
      case 6:
        Form1->Label12->Caption = "FW Different"   ;
        Form1->Label12->Font->Size = 12;
        Form1->Label12->Font->Color = clRed ;
        CloseHandle(COM1);
        break;

      case 20:
        Form1->Label12->Caption = "Check MAC"   ;
        Form1->Label12->Font->Size = 12;
        Form1->Label12->Font->Color = clRed ;
        CloseHandle(COM1);
        break;

      case 22:
        Form1->Label12->Caption = "Check MAC Range"   ;
        Form1->Label12->Font->Size = 12;
        Form1->Label12->Font->Color = clRed ;
        CloseHandle(COM1);
        break;
    }
}

int check_version(char *p,int check_com)
{
    int res_version ;

    char *str_comp;


        memset(&TxdBuffer, 0, sizeof(&TxdBuffer)) ;

        //check different command line.
        if(check_com)
           sprintf(TxdBuffer, "printenv %s\n",p);
        else
           sprintf(TxdBuffer, "printsys dualfname0\r");

           //sprintf(TxdBuffer, "printsys %s\r",p);

        WriteFile(COM1, TxdBuffer, 20, &dw_Write, 0);
      //WriteFile(COM1, TxdBuffer, strlen(TxdBuffer), &dw_Write, 0);
        ReadFile(COM1, RxdBuffer, sizeof(RxdBuffer), &dw_Read, NULL);   // get the message form rs232.
        //Compare_log();

         str_comp = strcat(p,"=");     // combine string p and "="

             #if 0   // 0 △1 is enable this function.   //debug !!
                  char msg_03[64];
                  wsprintf(msg_03,"RxdBuffer version is %s",RxdBuffer);
                  Application->MessageBox(msg_03, "new mac", MB_OKCANCEL);
              #endif

        if (dw_Read) {

            Form1->Memo1->Lines->Add(RxdBuffer);
            ::Sleep(2000);
            sys_version = strstr(RxdBuffer ,str_comp);

            if (NULL != sys_version ) {
                  sys_version = sys_version + strlen(str_comp)  ;  //+13 jump  "boardversion="
                  sys_version = strtok(sys_version,"\r");
                   #if 0   // 0 △1 is enable this function.   //debug !!
                       char msg_03[64];
                       wsprintf(msg_03,"SYS version is %s",sys_version);
                       Application->MessageBox(msg_03, "new mac", MB_OKCANCEL);
                   #endif
                  res_version = 1 ;
            }
            else{
                res_version = 0 ;
            }
        } // end of if (dw_Read)


        //Application->ProcessMessages();

    return res_version ;
}

int upgrade_codes()
{
    char *ptr;
    char length[10];

    Form1->Timer1->Enabled = False;
    memset(RxdBuffer, NULL, sizeof(RxdBuffer));

    //Send command line. 2013-03-22 Hearn modified.

     //--- list -------//
    sprintf(TX_Command, "setsys dualfname0 %s",fw_version);
    sprintf(TxdBuffer, "%s\r",TX_Command);
    WriteFile(COM1, TxdBuffer, strlen(TxdBuffer), &dw_Write, 0);
              #if 0   // 0 △1 is enable this function.   //debug !!
                  char msg_001[64];
                  wsprintf(msg_001,"set default is %s",TxdBuffer);
                  Application->MessageBox(msg_001, "new mac", MB_OKCANCEL);
              #endif
    ::Sleep(2000);

    //----- end -----

    //--- Burn Ethaddr MAC address -------//
    wsprintf(TX_START_MAC,"%c%c:%c%c:%c%c:%c%c:%c%c:%c%c",currentmac_start[0],currentmac_start[1],currentmac_start[2],currentmac_start[3],currentmac_start[4],currentmac_start[5],currentmac_start[6],currentmac_start[7],currentmac_start[8],currentmac_start[9],currentmac_start[10],currentmac_start[11]);
    sprintf(TX_Command, "setenv ethaddr %s",TX_START_MAC);
    sprintf(TxdBuffer, "%s\r",TX_Command);
    WriteFile(COM1, TxdBuffer, strlen(TxdBuffer), &dw_Write, 0);
              #if 0   // 0 △1 is enable this function.   //debug !!
                  char msg_002[64];
                  wsprintf(msg_002,"start mac is %s",TxdBuffer);
                  Application->MessageBox(msg_002, "new mac", MB_OKCANCEL);
              #endif
    ::Sleep(1000);

    //--- Burn End MAC address -------//
    wsprintf(TX_END_MAC,"%c%c:%c%c:%c%c:%c%c:%c%c:%c%c",currentmac_end[0],currentmac_end[1],currentmac_end[2],currentmac_end[3],currentmac_end[4],currentmac_end[5],currentmac_end[6],currentmac_end[7],currentmac_end[8],currentmac_end[9],currentmac_end[10],currentmac_end[11]);
    sprintf(TX_Command, "setsys mac_end %s",TX_END_MAC);
    sprintf(TxdBuffer, "%s\r",TX_Command);
    WriteFile(COM1, TxdBuffer, strlen(TxdBuffer), &dw_Write, 0);
              #if 0   // 0 △1 is enable this function.   //debug !!
                  char msg_003[64];
                  wsprintf(msg_003,"End mac is %s",TxdBuffer);
                  Application->MessageBox(msg_003, "new mac", MB_OKCANCEL);
              #endif
    ::Sleep(1000);
    //----- end -----

    //--- Burn Start MAC address -------//
    sprintf(TX_Command, "setsys mac_start %s",TX_START_MAC);
    sprintf(TxdBuffer, "%s\r",TX_Command);
    WriteFile(COM1, TxdBuffer, strlen(TxdBuffer), &dw_Write, 0);
              #if 0   // 0 △1 is enable this function.   //debug !!
                  char msg_004[64];
                  wsprintf(msg_004,"sys start mac is %s",TxdBuffer);
                  Application->MessageBox(msg_004, "new mac", MB_OKCANCEL);
              #endif
    ::Sleep(1000);
    //----- end -----

#if 1       // Save config into the bootloader.
    WriteFile(COM1, "savesys\n", 8, &dw_Write, 0);
    ::Sleep(3000);

    //--- list -------//
    WriteFile(COM1, "saveenv\n", 8, &dw_Write, 0);
    ::Sleep(2000);

 #endif

    //Form1->Timer1->Enabled = False;
    return 1;
}

int get_login_prompt(int flag, char *pattern)
{
//    char sz_cmd[] = {0x1B, '\r'};
    char sz_cmd[] = {0x20, '\r'};    // Send virtual key like space button.

    Form1->Timer1->Enabled = True;
    while (timeout) {
      if (flag == 1)
        WriteFile(COM1, sz_cmd, 2, &dw_Write, 0);          // send command line.
      ReadFile(COM1, &RxdBuffer, 1024, &dw_Read, NULL);    // get the message form rs232.
      if (dw_Read) {
        Form1->Memo1->Lines->Add(RxdBuffer);
        if (NULL != strstr(RxdBuffer, pattern)) {
          break;
        }
      } // end of if (dw_Read)
      memset(RxdBuffer, NULL, strlen(RxdBuffer));
      Application->ProcessMessages();
    }   // end of while{}

    return (timeout);
}


//ReadMAC function

void Open_File()
{
  String filepath;
  TCHAR   currentpath[200];

  //---------Check Mac Address range---------- Add by Hearn 2013-03-22
  GetCurrentDirectory(255,currentpath);
  filepath=String(currentpath);
  filepath +="\\MACADDR.ini";

  memset(readstart,0,13);
  GetPrivateProfileString("GM103-MACDATA","START-MAC"," ",readstart,13,filepath.c_str());  memset(currentmac_start,0,13);
  GetPrivateProfileString("GM103-MACDATA","CURRENT-MAC_START"," ",currentmac_start,13,filepath.c_str());  memset(currentmac_end,0,13);  GetPrivateProfileString("GM103-MACDATA","CURRENT-MAC_END"," ",currentmac_end,13,filepath.c_str());  memset(readend,0,13);  GetPrivateProfileString("GM103-MACDATA","END_MAC"," ",readend,13,filepath.c_str());  memset(PCBA_SN_Length,0,3);  GetPrivateProfileString("GM103-MACDATA","PCBA_SN_Length"," ",PCBA_SN_Length,3,filepath.c_str());  memset(Serveradder,0,24);
  GetPrivateProfileString("GM103-MACDATA","Serveradder"," ",Serveradder,24,filepath.c_str());
  memset(Station,0,8);
  GetPrivateProfileString("GM103-MACDATA","Station"," ",Station,8,filepath.c_str());
  memset(EMP,0,8);
  GetPrivateProfileString("GM103-MACDATA","EMP"," ",EMP,8,filepath.c_str());
  memset(passread,0,7);  GetPrivateProfileString("GM103-MACDATA","PASS_COUNT"," ",passread,13,filepath.c_str()); //Calon add 2011-03-07  passcount = atoi(passread);

}

int mac_check( char *lpmac , char *lpstart ,char *lpend)
{
        for(int i=0; i<12;i++)
        {
                if(lpmac[i]>='0' && lpmac[i]<='9')
                {
                }
                else if(lpmac[i]>='A' &&  lpmac[i]<='F')
                {
                }
                else
                {
                        return -1;
                }
        }

        for(int j=0;j<12;j++)
        {
                if(lpstart[j]>='0' && lpstart[j]<='9')
                {
                }
                else if(lpstart[j]>='A' && lpstart[j]<='F')
                {
                }
                else
                {
                        return -1;
                }
        }
        for(int k=0;k<12;k++)
        {
                if(lpend[k]>='0' && lpend[k]<='9')
                {
                }
                else if(lpend[k]>='A' && lpend[k]<='F')
                {
                }
                else
                {
                        return -1;
                }
        }
        if( ( mac_equal(lpmac, lpstart) || mac_more_than(lpmac, lpstart) ) && ( mac_equal(lpend, lpmac) || mac_more_than(lpend, lpmac) ) )
        {
        
        }
        else
        {
                return -1;
        }
        return 1;

}


int mac_more_than(char *lp_addr, char *lp_max)
{
  int i=11;
  int Carry=0;
  int res;

  if (!lp_max || !lp_addr)
    return (FALSE);

  while (i>=0) {
    res=(((int) lp_max[i]) - Carry - ((int) lp_addr[i]));
    Carry=(res<0);
    i--;
  }
  return (Carry);
}



int mac_equal(char *lpsz_addr_A, char *lpsz_addr_B)
{
  // 1) verify the parameters
  if (!lpsz_addr_A || !lpsz_addr_B)
    return (FALSE);

  return( ((lpsz_addr_A[0] == lpsz_addr_B[0]) &&
           (lpsz_addr_A[1] == lpsz_addr_B[1]) &&
           (lpsz_addr_A[2] == lpsz_addr_B[2]) &&
           (lpsz_addr_A[3] == lpsz_addr_B[3]) &&
           (lpsz_addr_A[4] == lpsz_addr_B[4]) &&
           (lpsz_addr_A[5] == lpsz_addr_B[5]) &&
           (lpsz_addr_A[6] == lpsz_addr_B[6]) &&
           (lpsz_addr_A[7] == lpsz_addr_B[7]) &&
           (lpsz_addr_A[8] == lpsz_addr_B[8]) &&
           (lpsz_addr_A[9] == lpsz_addr_B[9]) &&
           (lpsz_addr_A[10] == lpsz_addr_B[10]) &&
           (lpsz_addr_A[11] == lpsz_addr_B[11])) ? TRUE : FALSE);
}


void Open_File_Start_End()
{
  String filepath;
  TCHAR   currentpath[200];

  //---------Check Mac Address range---------- Add by Hearn 2013-03-22
  GetCurrentDirectory(255,currentpath);
  filepath=String(currentpath);
  filepath +="\\MACADDR.ini";

  memset(fw_version,0,16);
  GetPrivateProfileString("GM103-MACDATA","FW_VERSION"," ",fw_version,16,filepath.c_str());
  memset(readstart,0,13);
  GetPrivateProfileString("GM103-MACDATA","START-MAC"," ",readstart,13,filepath.c_str());
  memset(readend,0,13);
  GetPrivateProfileString("GM103-MACDATA","END_MAC"," ",readend,13,filepath.c_str());
  memset(PCBA_SN_Length,0,7);
  GetPrivateProfileString("GM103-MACDATA","PASS_COUNT"," ",passread,13,filepath.c_str()); //Calon add 2011-03-07
  passcount = atoi(passread);

}



String MacAdd(String lbl, int a)
 {

    //lbl = "0x" +  lbl;
    //int iMac=StrToInt(lbl);
    int iMac = 0x001122334466;
    String Mac_End_str;

    Mac_End_str = Mac_End_str.sprintf("%0X",iMac+a);

    #if 1   // 0 △1 is enable this function.
    char msg_02[64];
    wsprintf(msg_02,"Mac_i is %s",Mac_End_str);
    Application->MessageBox(msg_02, "new mac", MB_OKCANCEL);
    #endif

    Mac_End_str =  Mac_End_str.SubString(2,14);

    return Mac_End_str;
}

void Save_log(char *p)
{
        FILE *fp ;

        if ((fp = fopen("log.txt", "a")) == NULL)
        {
        Application->MessageBox("Fail to open the log.txt file .", "Error");
        fclose(fp);
        return;
        }

        char date[9];
        char time[9];

        fprintf(fp,"%s ", _strdate(date));
        fprintf(fp,"%s \n", _strtime(time));
        fprintf(fp, "CURRENT-MAC_START=%s\n", currentmac_start);
        fprintf(fp, "CURRENT-MAC_END=%s\n-> %s\n", currentmac_end,p);

        fclose(fp);
}

void Compare_log()
{
        FILE *fp ;

        if ((fp = fopen("log_console.txt", "a")) == NULL)
        {
        Application->MessageBox("Fail to open the log_console.txt file .", "Error");
        fclose(fp);
        return;
        }

        char date[9];
        char time[9];

        fprintf(fp,"%s ", _strdate(date));
        fprintf(fp,"%s \n", _strtime(time));

        fprintf(fp, "%s\n", RxdBuffer);

        fclose(fp);
}

void double_check(char *str_p)
{
      char *compare_tmp;

      #if 0
      WriteFile(COM1, "reset", 5, &dw_Write, 0);
      ::Sleep(5000);
      #endif

      memset(TxdBuffer_ver, NULL, sizeof(TxdBuffer_ver));
      memset(RxdBuffer_ver, NULL, sizeof(RxdBuffer_ver));
      memset(&dw_Read, NULL, sizeof(&dw_Read));
      memset(&dw_Write, NULL, sizeof(&dw_Write));

      if (get_login_prompt(1, "RTL838x#"))
      {

           ::Sleep(2000);
           sprintf(TxdBuffer_ver, "%s\r",str_p);
           WriteFile(COM1, TxdBuffer_ver, sizeof(TxdBuffer_ver), &dw_Write, 0);
           ReadFile(COM1, RxdBuffer_ver, sizeof(RxdBuffer_ver), &dw_Read, NULL);   // get the message form rs232.
  #if 0  //20160409
             #if 0   // 0 △1 is enable this function.   //debug !!
                  char msg_005[128];
                  wsprintf(msg_005,"The result is:%s",RxdBuffer_ver);
                  Application->MessageBox(msg_005, "check version", MB_OKCANCEL);
             #endif

           // command line :printsys mac_start;

                compare_tmp = strstr(RxdBuffer_ver,"dualfname0=");
             #if 0   // 0 △1 is enable this function.   //debug !!
                  char msg_004[256];
                  wsprintf(msg_004,"1.The result is:%s",compare_tmp);
                  Application->MessageBox(msg_004, "new mac", MB_OKCANCEL);
             #endif

                compare_tmp = strtok(compare_tmp,"\r");

             #if 0   // 0 △1 is enable this function.   //debug !!
                  char msg_006[256];
                  wsprintf(msg_006,"2.The result is:%s",compare_tmp);
                  Application->MessageBox(msg_006, "new mac", MB_OKCANCEL);
             #endif

                if( strstr(compare_tmp,fw_version) ){
                        double_check_fw=1;      //comapre dualfname0 version pass
                        //system("PAUSE");
             #if 0   // 0 △1 is enable this function.   //debug !!
                  char msg_007[32];
                  wsprintf(msg_007,"Pass");
                  Application->MessageBox(msg_007, "new mac", MB_OKCANCEL);
             #endif
                }
                else{
                        double_check_fw=0 ;     //compare daulfname0 version fail
             #if 0   // 0 △1 is enable this function.   //debug !!
                  char msg_008[32];
                  wsprintf(msg_008,"Fail");
                  Application->MessageBox(msg_008, "new mac", MB_OKCANCEL);
             #endif

                }
  #endif     //20160409
      }


}
 
void __fastcall TForm1::Button1Click(TObject *Sender)
{
        MAC->Text = "" ;
        END_MAC->Text = "" ;
        PCBASN->Text = "" ;

        StartCmd->Enabled = True;
        RadioCOM1->Enabled = True;
        RadioCOM2->Enabled = True;
        RadioButton1->Enabled = True;
        RadioButton2->Enabled = True;
        RadioButton3->Enabled = True;
        RadioButton4->Enabled = True;
}
//---------------------------------------------------------------------------
String MAC_ADD_A(String MAC_ADD_A , int A)
 {
     int mac0 = 0x3, mac1 = 0x3;
     mac0 = StrToInt("0x" + MAC_ADD_A.SubString(1,6));
     mac1 = StrToInt("0x" + MAC_ADD_A.SubString(7,6));

     mac1 += A;

     if(mac1 >= 0x1000000) {
         mac0++;
         mac1 -= 0x1000000;
     }
     String str = IntToHex(mac0,6) + IntToHex(mac1,6);
     return str;
}

//------------------------------------------------------------------------------




