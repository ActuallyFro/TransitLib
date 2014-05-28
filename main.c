#define TL_HELP_MESSAGE                                                                         \
"\nTransitLib (v.01 ALPHA)\
\n======================\
\nUsage: %s [--Num1 <int>] [--sink <float>] [--string <\"String\">] [--string2 <\"String\">] [--ip ###.###.###.###] [-F] [-E] [-D]\
\n\t--Num1:\t\tThis argument requires a following integer\
\n\t--sink:\t\tThis argument requires a following float\
\n\t--string:\tThis argument accepts a string; if you want spaces ensure to wrap string in QUOTES!\
\n\t--string2:\tThis argument accepts a string; if you want spaces ensure to wrap string in QUOTES!\
\n\t--ip:\t\tThis argument takes in a string form of an IPv4 Address for the TCP/UDP examples...\
\n\t-F:\t\tThis is a flag example\
\n\t-E:\t\tThis flag will set the piped stdin examples to ENCODE the passed string\
\n\t-D:\t\tThis flag will set the piped stdin examples to DECODE the passed string\
\n\n\
\nAbout:\
\n------\
\nTL;DR: Code once, run everywhere with the speed of C and without the suck of Run Time Enivronments/VM's/Intrepreters/etc\
\n\nThis 'Library' is supposed to allow rapid, cross-platform application development for network based software. \
It is the result of a gentlemens' duel, which was started with the proverbial gauntlet dropped with the statement: \"Pfft...you can't do that...\" \
The ultimate goal is to allow a single C library to be the 'go to' library I will use, and I will additionally be using this library to teach others C. \
The code is intended to be very simple and make sense. Function calls, when read right to left, should be fully descriptive of their purpose/use. \
If you can make sense of the code/examples, AND can use this code I highly encoruage your involvement! \
I would appreciate reporting of any and all bugs found, or reccomendations to make this code NOT suck. \
\n\n\
\nExamples:\
\n---------\
\n1) All normal flags in a single example:\
\n\t%s --ip 192.168.30.129 -E --string \"Hello There.\" --sink 2304.2342 -F --string2 \"Yup, second string...\" --Num1 237\
\n\
\n2) Encode a passed string:\
\n\techo \"Hello There how are you?\" | %s -E\
\n\
\n2) Decode a passed string:\
\n\techo \"SGVsbG8gVGhlcmUgaG93IGFyZSB5b3U/Cg==\" | %s -D\
\n\n\
\nCredits:\
\n========\
\nLong story short: I took a TON of code from the interwebz, but no worries it's all free! However, if you ever see/meet the other authors please shake their hand for me!\
\n\n\
\nLicense:\
\n--------\
\nThe bits of code I have added are copyleft, but please note that the following sections indicate further restrictions on the code...Thus, the overall copyright/license is under the MOST restrictive of the following segments.\
\n\tCheers!\
\n\t -ActuallyFro\
\n\n\
\nBase 64 Encoder and Decoder Code\
\n--------------------------------\
\nBase 64 Code Source: http://www.rtner.de/software/base64.c\
\nCopyright/License from the original source:\
\n* Copyright (c) 2002 Matthias Gaertner 29.06.2002\
\n*\
\n* This program is free software; you can redistribute it and/or modify\
\n* it under the terms of the GNU General Public License as published by\
\n* the Free Software Foundation; either version 2 of the License, or\
\n* (at your option) any later version.\
\n*\
\n* This program is distributed in the hope that it will be useful,\
\n* but WITHOUT ANY WARRANTY; without even the implied warranty of\
\n* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\
\n* GNU General Public License for more details.\
\n*\
\n* You should have received a copy of the GNU General Public License\
\n* along with this program; if not, write to the Free Software\
\n* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA\
\n*\
\n\n\
\nUDP and TCP Network Code\
\n------------------------\
\nDr. Ken Christensen's Tools page: http://www.csee.usf.edu/~christen/tools/toolpage.html#tcpip\
\nCopyright/License from the original source: NONE FOUND\
\nOther information from the Source Code:\
\n//=  Author: Ken Christensen                                                  =\
\n//=          University of South Florida                                      =\
\n//=          WWW: http://www.csee.usf.edu/~christen                           =\
\n//=          Email: christen@csee.usf.edu                                     =\
\n\n\
\nP.S. I use stderr, so I'll leave this here: %s --help 2>&1 | less\
\n\n",TL_ProgName,TL_ProgName,TL_ProgName,TL_ProgName,TL_ProgName

#include "TL_0_03.h" // FYI: It includes stdio/stdlib/string

//P.S. Skip to the "cases" below to really see the code in action.

int main(int argc, char **argv){
	int Tests=15;
	int CurrentTest=0;
	char MenuSelection[21]; // (2^64) --> "18446744073709551616" + '\0'

	TL_2D_Array_Create(char,TestNames,Tests,100);
        strcpy(TestNames[0],"Debugging API Example");
        strcpy(TestNames[1],"STDIN Piped Value Checking");
        strcpy(TestNames[2],"Operating System IFDEF Macros");
        strcpy(TestNames[3],"Infinite Switched Loop Allowing Keyboard Entry");
        strcpy(TestNames[4],"Piped Data parsing");
        strcpy(TestNames[5],"Command Line Options Parsing");
        strcpy(TestNames[6],"Dynamically Created 2D Integer Array");
        strcpy(TestNames[7],"Dynamically Created 2D Character Array");
        strcpy(TestNames[8],"Base64 Encoding");
        strcpy(TestNames[9],"Base64 Decoding");
        strcpy(TestNames[10],"Internet Creation UDP - Sender");
        strcpy(TestNames[11],"Internet Creation UDP - Listener");
        strcpy(TestNames[12],"Internet Creation TCP - Client");
        strcpy(TestNames[13],"Internet Creation TCP - Server");
        strcpy(TestNames[14],"ISO Time Strings");

    //Randoms for examples
	char buffer[100];
	int counter=0;
	int counter2=0;
	int RunMenu=1;

	//Parsing Vars
	int AlreadyParsed = 0;
	int Flag1=0;
	char *String1 = NULL;
	char *String2 = NULL;
	int Number1=0;
	float Float1=1.0;
    char *IP_Input_Dest = NULL; //[]="255.255.255.255";
    int DECODE_PIPED=-1;
    int InStrLen=0;

	//IPv4 Vars Sender Example
	char	IP_Dest[16]="127.0.0.1";
	int	IP_Port=1337;
	int	current2=1;
	int	counter3=4;
	int 	MESS_SIZE=1300;
	int 	LoopNum=100000;
	char    out_buf[1301]; // Buffer for output data
	char    in_buf[1301]; // Buffer for output data
	char    out_buf2[3500]; // Buffer for output data

    TL_IPv4_INIT();	//Case 11 and 12
    
	TL_IPv4_SOCKET_INIT(server_s); //Case 12
	TL_IPv4_SOCKET_INIT(client); //Case 12
    TL_IPv4_SOCKET_INIT(client_s); //Case 11

	//TCP Example Var's
    TL_IPv4_SOCKET_INIT(TCPClientEx); //Case 13
    TL_IPv4_SOCKET_INIT(TCPServerListener); //Case 14
    TL_IPv4_SOCKET_INIT(TCPClientResponder); //Case 14
    
	struct timeb         start, stop;        // Start and stop times structures
	double               elapsed;            // Elapsed time in seconds
	double               data_rate;          // Computed data rate in Mb/s
	unsigned int         i;                  // Loop counter

    //BASE 64 Var's
	TL_B64_INIT_Global();
	TL_B64_INIT();

	TL_TIME_INIT();

    //Add argument parsing functions and take values; NOTE: There's a LACK OF SEMICOLONS!!!
	TL_PARSEARGS_INSTALL();
	TL_PARSEARGS_START(argc, argv,TL_ENFORCEPARSING_OFF)
		TL_PARSEARGS_ADD_INT("--Num1",Number1)
		TL_PARSEARGS_ADD_STR("--string",String1)
		TL_PARSEARGS_ADD_STR("--ip",IP_Input_Dest)
		TL_PARSEARGS_ADD_STR("--string2",String2)
        TL_PARSEARGS_ADD_FLAG("-F", Flag1, 1)
        TL_PARSEARGS_ADD_FLAG("-E",DECODE_PIPED,FALSE)
        TL_PARSEARGS_ADD_FLAG("-D",DECODE_PIPED,TRUE)
		TL_PARSEARGS_ADD_FLOAT("--sink",Float1)
	TL_PARSEARGS_STOP
    
    if(IP_Input_Dest!=NULL && strlen(IP_Input_Dest)<17) {
        strcpy(IP_Dest,IP_Input_Dest);
    }
    
    //Stdin Checking for Piped data
	STDIN_CHECK();
    if(TL_STDIN_PIPED==1){
		char buffer[100];
		int counter = 0;
		#if WINDOWS
			system("cls");
		#elif NOTWINDOWS
			system("clear");
		#endif
		printf("\nTransitLib Example Program");
		printf("\n=========================");
		printf("\nThe program DID receive piped data...\nCannot Continue due to stdin messing  with read functions...\n\nYou gave the program the following:\n");

        #ifdef USE_CRLF
            TL_B64_fUseCRLF = TRUE;
        #endif
        TL_B64_DECODE_FLAG = FALSE;
        TL_B64_FILE_IN_FD = stdin;
        TL_B64_FILE_OUT_FD = stdout;

		RunMenu=0;

		//[Test 5] Pipe / File redirect Parsing Example
		//START PARSE ARGS
		printf("\nParse Args Information");
			printf("\n\tNumber1 = %i", Number1);
			printf("\n\tFlag1 = %i", Flag1);
			printf("\n\tString1 = %s", String1);
            printf("\n\tFloat1 = %f", Float1);
            printf("\n\tString2 = %s", String2);
            if(IP_Input_Dest!=NULL){
                 InStrLen=strlen(IP_Input_Dest);
                 if(InStrLen!=0){
                     printf("\n\tThe IP string is NOT empty!");
                 }
                 else{
                     printf("\n\tThe IP string IS empty!");
                 }
            }
            printf("\n\tIP Address = %s",IP_Dest);

         if(DECODE_PIPED>=0){
            #if WINDOWS
                _setmode(fileno(stdin), _O_BINARY);
                setmode(fileno(stdout), O_BINARY);
            #endif
            char *pbBufferIn = (char*) malloc( TL_B64_EN_TCP_SIZE_IN );
            char *pbBufferOut = (char*) malloc( TL_B64_EN_TCP_SIZE_OUT );

            if(DECODE_PIPED==0){
                printf("\n\tDECODE_PIPED = FALSE");
                printf("\n\nThis is the Base64 Encoded String: \n");
                while(!feof(stdin) && !isatty(fileno(stdin))){
                    TL_B64_ENCODE_FROM_FD(pbBufferIn,pbBufferOut,TL_B64_EN_TCP_SIZE_IN,TL_B64_FILE_IN_FD);
                }
             }
             else if(DECODE_PIPED==1){
                 printf("\n\tDECODE_PIPED = TRUE");
                 printf("\n\nThis is the Base64 Decoded String: \n");
                 while(!feof(stdin) && !isatty(fileno(stdin))){
                     TL_B64_DECODE_FROM_FD(TL_B64_FILE_IN_FD,TL_B64_FILE_OUT_FD);
                 }
             }
             if( pbBufferIn != NULL ){
                 free( pbBufferIn );
             }
             if( pbBufferOut != NULL ){
                 free( pbBufferOut );
             }

         }
         else{
             printf("\n\tDECODE_PIPED = (null)");
         }
         // END PARSE ARGS

	}

    //Enter the main loop for the coded examples:
	while(RunMenu==1){ //RE-code to TL_LOOP When string buffer is added :D
		switch(CurrentTest){
				case 1:
					//////////////////////////////////////////////////////////////////////////////////////////
					// 1. DEBUGGING API
					// ================
					// WHAT: Enable messages that output to stdout IFF TL_DEBUGGING==1

					// WHY: The debugging call of "TL_DEBUGF(stdout,)" is a glorified wrapper of printf.
					// The wrapper is an if statement comparing int TL_DEBUGGING to 1;
					// Debugging mode can be set with TL_DEBUGGING_ENABLE (TL_DEBUGGING=1).
					// Debugging mode can be unset with TL_DEBUGGING_DISABLE (TL_DEBUGGING=0).

					// Example Use:
					printf("\n\nTest[%i/%i]: %s",CurrentTest,Tests,TestNames[CurrentTest-1]);
					TL_DEBUGF(stdout,"\n\tThis Debugging message is NOT going to work.");
					TL_DEBUGGING_ENABLE;
					TL_DEBUGF(stdout,"\n\tThis Debugging message IS going to work.");
					TL_DEBUGGING_DISABLE;
					TL_DEBUGF(stdout,"\n\tThis Debugging message is NOT going to work.");

					printf("\n\nPress Enter to Continue...");
					getchar();
					CurrentTest=0;
					break;
				case 2:
					//////////////////////////////////////////////////////////////////////////////////////////
					// 2. STDIN Checking API
					// =====================
					// WHAT: Set a flag for stdin's state 0 for terminal/commandline OR 1 for piped data

					// WHY: These calls will check for the status of the file descriptor of stdin.
					// int TL_STD_PIPED is set to 1 if piped data is sent to this running program.
					// This can allow for the creation of "chaining" tools (e.g. ls -hatlr | grep *.c OR dir /OD | findstr .c)
					// Additionally, this can allow for parsing of data for further flags/settings/etc.

					// Example Use:
                    printf("\n\nTest[%i/%i]: %s",CurrentTest,Tests,TestNames[CurrentTest-1]);
					
                    /* Feel free to use this in your code:
                        STDIN_CHECK();
                        if(TL_STDIN_PIPED==1){
                                printf("\n\tThe program DID receive piped data...");
                        }
                        else{
                            printf("\n\tThe program DID NOT receive piped data...");
                        }
					*/
					printf("\n\tThere was no Piped Data Received!\n\tTo see what it looks like try starting the program like this:\n\t\techo \"Hello World\" | Example.exe \n\n\tPress Enter to Continue...");
					getchar();
					CurrentTest=0;

					break;
				case 3:
					//////////////////////////////////////////////////////////////////////////////////////////
					// 3. IFDEF MACROS
					// ===============
					// WHAT: Quickly set cross-platform defines for Windows vs Linux/Apple/Android

					// WHY: ifdef macros are needed when the same source code is pushed across platforms.
					//      I am lazy, so _WIN32/64 (WINDOWS) is defined against __linux__, __APPLE__, and __ANDROID__ (NOTWINDOWS).
					//      If finer grain ifdefs are needed it is left to the programmer to add specific OS dependencies.

					// Example Use:
                    printf("\n\nTest[%i/%i]: %s",CurrentTest,Tests,TestNames[CurrentTest-1]);
					#if WINDOWS
						printf("\n\tYAY I AM ON WINDOWS!!!! ... -_-");
					#elif NOTWINDOWS
						printf("\n\tHello! you are NOT WINDOWS OS :)");
					#endif

					printf("\n\nPress Enter to Continue...");
					getchar();
					CurrentTest=0;
					break;
				case 4:
					//////////////////////////////////////////////////////////////////////////////////////////
					// 4. Run While Keyboard key NOT hit
					// =================================
					// WHAT: Create an infinite loop that is only escapable by a defined keyboard key input

					// WHY: Many times you would like to have a program continuously AND have keyboard input.
					// This code allows you to define a loop that will run forever, and have defined keyboard
					// character switch cases with a given switch including "TL_KBHIT_CASE_QUIT;" to stop the loop.

					// TODO: To be most useful this would need to have kbhit() buffer the characters in a String.
					//       Upon a specific Key, let's say ENTER, the string can be processed (strcmp, atoi, etc).
					//       The current implementation only allows for SINGLE KEY interaction, which limits... everything.

					// Example Use:
                    printf("\n\nTest[%i/%i]: %s",CurrentTest,Tests,TestNames[CurrentTest-1]);
                    printf("\t... press ESC to exit!");

					TL_KBHIT_LOOP_INSTALL(Example);

					TL_KBHIT_LOOP_START(Example)
						TL_CHECK_KEY_SWITCH_START(Example)
								case TL_ENTER: //This is sometimes platform dependent
									printf("\n\tYOU HIT ENTER...");
									break;
								case '\t': //TL_TAB exists!
									printf("\n\tYOU HIT Tab FTW");
									break;
								case TL_BACKSPACE: //This is sometimes platform dependent
									printf("\n\tYOU HIT BACKSPACE .... ha.");
									break;
								case ' ': //TL_SPACE exists!
									printf("\n\tYOU HIT the Spacebar");
									break;
								case 'n': //direct characters work!
									printf("\n\tYOU HIT the n KEY!");
									break;
								case '~': //direct characters work!
									printf("\n\tYOU HIT the Tilda KEY!");
									break;
								case TL_ESCAPE: //This is sometimes platform dependent
									printf("\n\tYOU HIT ESCAPE...NOW QUITTING!!!\n");
									TL_KBHIT_CASE_QUIT(Example); //IMPORANT!!!
									break;
								default:
									printf("\n\tYou Pressed: %X",TL_GET_KEY_Example);
									break;
						TL_CHECK_KEY_SWITCH_STOP
					TL_KBHIT_LOOP_STOP

					printf("\n\nPress Enter to Continue...");
					getchar();
					CurrentTest=0;
					break;
				case 5:
					//////////////////////////////////////////////////////////////////////////////////////////
					// TODO: 5. Piped Data parsing
                    // WHAT: Show how "unix" like tools can be created by allowing the acceptance of piped data
                
                    // WHY: MOST Operating Systems have build in tools that can be strung together. Having this
                    //      functionality allows "drop in" tools that could expand total OS functionality dramatically.
                
                    // "Example Use": (this CANNOT be run from within the program's loop)
                    printf("\n\nTest[%i/%i]: %s",CurrentTest,Tests,TestNames[CurrentTest-1]);
                    printf("\nThis test MUST be run during the program's invocation!");
					printf("\n\nAn example execution is: \n echo SUP | %s --Num1 123412 -F --sink 3322.212 --string \"Hello how are you!?\" --string2 \"See I told you this crazy thing would work :D\"\n",TL_ProgName);

					printf("\n\nPress Enter to Continue...");
					getchar();
					CurrentTest=0;
					break;
				case 6:
					//////////////////////////////////////////////////////////////////////////////////////////
					// TODO: 6. Command Line Options Parsing
                    // WHAT: Allow a simple API/framework to enable argc/argv command parsing from command line values.
                
                    // WHY: Many times with a program you would like dynamic behavior, versus hardcoded, to occur.
                    //      Passing arguments allows you to "read in" input from the user with out having to
                    //      rebuild/recreate a binary.
                
                    // Example Use:
                    printf("\n\nTest[%i/%i]: %s",CurrentTest,Tests,TestNames[CurrentTest-1]);
                    printf("\n\tTry invoking this program with \"flags\"; To determine current flags type: %s --help",TL_ProgName);

                    printf("\n\tThese are the original Values:");
					printf("\n\t\tNumber1 = %i", 0);
					printf("\n\t\tFlag1 = %i", 0);
					printf("\n\t\tString1 = %s", "(null)");
					printf("\n\t\tFloat1 = %f", 1.0);
					printf("\n\t\tString2 = %s", "(null)");
                    printf("\n\t\tDECODE_PIPED = (null)");

                    // END PARSE ARGS
					printf("\n\n\tThis is what was parsed:");
					printf("\n\t\tNumber1 = %i", Number1);
					printf("\n\t\tFlag1 = %i", Flag1);
					printf("\n\t\tString1 = %s", String1);
					printf("\n\t\tFloat1 = %f", Float1);
					printf("\n\t\tString2 = %s ", String2);
                    if(DECODE_PIPED>=0){
                        if(DECODE_PIPED==0){
                            printf("\n\t\tDECODE_PIPED = FALSE");
                        }
                        else if(DECODE_PIPED==1){
                            printf("\n\t\tDECODE_PIPED = TRUE");
                        }
                    }
                    else{
                        printf("\n\t\tDECODE_PIPED = (null)");
                    }
                    printf("\n\t\tIP Address = %s",IP_Input_Dest);

					printf("\n\nPress Enter to Continue...");
					getchar();
					CurrentTest=0;
					break;
				case 7:
					//////////////////////////////////////////////////////////////////////////////////////////
					// TODO: 7. Dynamic 2D char Arrays
					// WHAT: Create a dynamically defined, 2D Character Array

					// WHY: Creating Static Arrays in a Pain, and Dynamic Arrays are WORSE.
                
					// This Macro allows you defined a simple 2D array with a Type, name, and rows/columns.
					// The macro will define, create, and allow you to access per the normal array conventions,
					// provided you define the array as a POINTER to the NAME.
					// (e.g. if(strcmp(*Array,"This String")==0)... or Array[x][y]="s";).
					// Also, the Variables rows_<ARRAY NAME> and cols_<ARRAY NAME> are created for convenience.
					// Please note that if strings are the intended storage/functions you still need a NULL
					// terminator.

					// Example Use:
                    printf("\n\nTest[%i/%i]: %s",CurrentTest,Tests,TestNames[CurrentTest-1]);
                    printf("\n\tCreating a 5 Row, 100 Column Array (+1 Null Terminator space)",CurrentTest,Tests);
					int i=0;
					int j=0;

					TL_2D_Array_Create(char,ThisArray,5,100+1);

					TL_2D_Array_Set_Default(ThisArray,'x');
					for(i=0;i<rows_ThisArray;i++){
						ThisArray[i][cols_ThisArray-1]='\0'; //You need a NULL terminator to use with string.h functions!
					}
					//printf("\n\t The 2D Array is %i Chars Long!", strlen(*ThisArray));
					printf("\n\n\tThis is the String (%i chars): %s",(int)strlen(ThisArray[0]), ThisArray[0]);
					printf("\n\n\tThis is the String (%i chars): %s",(int)strlen(ThisArray[1]), ThisArray[1]);
					printf("\n\n\tThis is the String (%i chars): %s",(int)strlen(ThisArray[2]), ThisArray[2]);
					printf("\n\n\tThis is the String (%i chars): %s",(int)strlen(ThisArray[3]), ThisArray[3]);
					printf("\n\n\tThis is the String (%i chars): %s",(int)strlen(ThisArray[4]), ThisArray[4]);

					strcpy(*ThisArray,"Hey,I made this dynamic Array! And I am Trying to make it Really Long!");
					printf("\n\tThis is the String: %s", *ThisArray);

					char * pch;

					printf("\n\tReplacing the word \"this\"...");
					pch = strstr(ThisArray[0],"this");
					if(pch!=NULL){
						strncpy(pch,"that",4);
					}
					else{
						printf("\n\tSubstring NOT found!");
					}

					printf("\n\n\tThis is the String: %s", ThisArray[0]);
					printf("\n\n\tThis is the String: %s", ThisArray[1]);
					printf("\n\n\tThis is the String: %s", ThisArray[2]);
					printf("\n\n\tThis is the String: %s", ThisArray[3]);
					printf("\n\n\tThis is the String: %s", ThisArray[4]);

					/*
					printf ("\n\tSplitting string \"%s\" into tokens:",*ThisArray);
					pch = strtok(*ThisArray," ,.-");
					while (pch != NULL){
						printf ("\n\t\t%s",pch);
						pch = strtok (NULL, " ,.-");
					}
					*/
					/*
					strcpy(ThisArray[2],"This is Line 3\0");
					printf("\n\tThis is the new String: %s", ThisArray[2]);
					for(i = 0; i < rows_ThisArray; i++){
						for(j = 0; j < cols_ThisArray; j++){
							printf("\n\t Array[%i][%i]: %c",i,j,ThisArray[i][j]);
						}
					}
					*/

					//printf("\n\tPause for memory check!\n\t\tPress Enter to continue...");
					//getchar();

					TL_2D_Char_Array_FREE(ThisArray);

					printf("\n\nPress Enter to Continue...");
					getchar();
					CurrentTest=0;
					break;
				case 8:
					//////////////////////////////////////////////////////////////////////////////////////////
					// TODO: 8. Dynamic 2D int Arrays
					// WHAT: Create a dynamically defined, 2D Integer Array

					// WHY: Creating Static Arrays in a Pain, and Dynamic Arrays are WORSE.
					// This Macro allows you defined a simple 2D array with a Type, name, and rows/columns.
					// The macro will define, create, and allow you to access per the normal array conventions
					// (e.g. if(Array[x][y]=="1")... or Array[x][y]=12312;). Also, the Variables rows_<ARRAY NAME>
					// and cols_<ARRAY NAME> are created for convenience.

					// Example Use:
                    printf("\n\nTest[%i/%i]: %s",CurrentTest,Tests,TestNames[CurrentTest-1]);

					int i2=0;
					int j2=0;
					TL_2D_Array_Create(int,ThisArrayInts,5,5);

					for(i2 = 0; i2 < rows_ThisArrayInts; i2++){
						for(j2 = 0; j2 < cols_ThisArrayInts; j2++){
							printf("\n\t Newly created ThisArrayInts[%i][%i]: %i",i2,j2,ThisArrayInts[i2][j2]);
						}
					}

					TL_2D_Array_Set_Default(ThisArrayInts,21342);

					for(i2 = 0; i2 < rows_ThisArrayInts; i2++){
						for(j2 = 0; j2 < cols_ThisArrayInts; j2++){
							printf("\n\t Set_Default Function applied: 	ThisArrayInts[%i][%i]: %i",i2,j2,ThisArrayInts[i2][j2]);
						}
					}
					TL_2D_Char_Array_FREE(ThisArrayInts);

					printf("\n\nPress Enter to Continue...");
					getchar();
					CurrentTest=0;
					break;
				case 9:
					//////////////////////////////////////////////////////////////////////////////////////////
					// TODO: 9. Base64 Encoding
                    // WHAT: Allow both piped and buffered data to be converted from binary or ASCII to Base 64
                    
                    // WHY: Passing strings may cause different Operating Systems to have a blown aneurysm. This
                    //      is COMPLETELY true with binary files, since most of the UDP/TCP stack wants null
                    //      terminated strings. Base64 gives a common codec to speak cross-platform.
                    
                    // Example Use:
                    printf("\n\nTest[%i/%i]: %s",CurrentTest,Tests,TestNames[CurrentTest-1]);
                    sprintf(in_buf,"This is my string YOLOYOYOYOYOYOY123");
					printf("\nThis is what I read in (%i): %s",(int)strlen(in_buf),in_buf);

					TL_2D_Array_Create(char,b64Out,1,(int)strlen(in_buf)*3+1);
					TL_2D_Array_Set_Default(b64Out,'\0');

					TL_B64_ENCODE_FROM_BUFFER(in_buf,b64Out[0],(int)strlen(in_buf));

					printf("\n\n\tThis is what the Base 64 Encoding is:\n%s\n", b64Out[0]);
				
					printf("\n\nPress Enter to Continue...");
					getchar();
					CurrentTest=0;
					TL_2D_Char_Array_FREE(b64Out);
					break;
				case 10:
					//////////////////////////////////////////////////////////////////////////////////////////
					// TODO: 10. Base64 Decoding
                    // WHAT: Allow a Base 64 string to be converted piped or buffered data.
                    
                    // WHY: Passing strings may cause different Operating Systems to have a blown aneurysm. This
                    //      is COMPLETELY true with binary files, since most of the UDP/TCP stack wants null
                    //      terminated strings. Base64 gives a common codec to speak cross-platform.
                    
                    // Example Use:
                    printf("\n\nTest[%i/%i]: %s",CurrentTest,Tests,TestNames[CurrentTest-1]);

                    sprintf(in_buf,"VGhpcyBpcyBteSBzdHJpbmcgWU9MT1lPWU9ZT1lPWU9ZMTIz");
                    printf("\nThis is what I read in (%i): %s",(int)strlen(in_buf),in_buf);
                    
                    TL_2D_Array_Create(char,b64Out2,1,(int)strlen(in_buf)+1);
                    TL_2D_Array_Set_Default(b64Out2,'\0');
                    
                    TL_B64_DECODE_WITH_BUFFER(in_buf,b64Out2[0],(int)strlen(in_buf));
                    
                    printf("\n\n\tThis is what the Base 64 Decoding is (%i):%s\n", (int)strlen(b64Out2[0]),b64Out2[0]);
                    TL_2D_Char_Array_FREE(b64Out2);
                
					printf("\n\nPress Enter to Continue...");
					getchar();
					CurrentTest=0;
					break;
				case 11:
					//////////////////////////////////////////////////////////////////////////////////////////
					// 11. Internet Creation UDP - Sender
					// WHAT: Simple IPv4 UDP Sender implementation.

					// WHY: Because Internet.

					// Example Use:
					printf("\n\nTest[%i/%i]: %s",CurrentTest,Tests,TestNames[CurrentTest-1]);
					printf("\n\tWould you like to run 1) UDP Blaster, 2) Client (for the Client-Server) or 3) Message Sender? (1-3): ");
					fgets(in_buf,10,stdin);

                    TL_IPv4_SOCKET_UDP_INIT(client_s);
                    TL_IPv4_SOCKET_SETIP(client_s,IP_Dest);
                
                    if(strcmp(in_buf,"1\n")==0){ //Remember that fgets will store the \n !!!

                        printf("\n\n\tRunning UDP Blaster...");

                        for (i=0; i<MESS_SIZE; i++) //Set message to ALL B's
                            out_buf[i] = 'B';

                        // Output start banner
                        printf("\n\n\tBlasting %d messages of size %d bytes to %s:%i...",LoopNum, MESS_SIZE,IP_Dest,1337);

                        // Start timing
                        ftime(&start);

                        // Blast out the test message in the output buffer LoopNum times
                        for (i=0; i<LoopNum; i++){
                            TL_IPv4_SOCKET_UDP_SENDTO(client_s,out_buf,MESS_SIZE);
                        }

                        // Stop timing and compute elapsed time
                        ftime(&stop);
                        elapsed=((double) stop.time + ((double) stop.millitm * 0.001)) -
                        ((double) start.time + ((double) start.millitm * 0.001));

                        // Compute data rate
                        data_rate = ((8.0 * (double)LoopNum * (double)MESS_SIZE) / elapsed) / 1048576.0;

                        // Output data rate
                        printf("\n\tDone.  Measured data rate = %f Mb/s", data_rate);

					}
					else if(strcmp(in_buf,"2\n")==0){ //Remember that fgets will store the \n !!!

						printf("\n\n\tSending messages to %s:%i...\n",IP_Dest,1337);
						printf("\n\t[%i/%i] Client started. Performing 1st SENDTO for a message to the server...",current2,counter3);
						strcpy(out_buf, "Test RECVFROM Message from the Client");
						printf("\n\t\tThe SENDTO Message: %s",out_buf);
						TL_IPv4_SOCKET_UDP_SENDTO(client_s,out_buf,sizeof(out_buf));
						current2++;

						printf("\n\t[%i/%i] Client started. Performing 2nd SENDTO for a message to the server...",current2,counter3);
						strcpy(out_buf, "Test RECVFROM #2 Message from the Client");
						printf("\n\t\tThe SENDTO Message: %s",out_buf);
						TL_IPv4_SOCKET_UDP_SENDTO(client_s,out_buf,sizeof(out_buf));
						current2++;

						printf("\n\t[%i/%i] Awaiting Message back from the Server...",current2,counter3);
						TL_IPv4_SOCKET_UDP_RECVFROM(client_s,in_buf);
						printf("\n\tReceived from server: %s \n", in_buf);
						current2++;

						printf("\n\t[%i/%i] Cleaning up used sockets...\nDone!\n\n",current2,counter3);
					}
					else{

						printf("\n\n\tSending 2 messages to %s:%i...",IP_Dest,1337);
						printf("\n\n\tRunning Message Sender...");
						printf("\n\tPlease enter your message (1300 char's max):\n");
						fgets(out_buf,1300,stdin);
						printf("\n\tSending Message...");

						TL_2D_Array_Create(char,b64Out,1,(int)strlen(out_buf)*3+1);
						TL_2D_Array_Set_Default(b64Out,'\0');
						TL_B64_ENCODE_FROM_BUFFER(out_buf,b64Out[0],(int)strlen(out_buf));

						printf("\n\t\tGiven String: %s",out_buf);
						TL_IPv4_SOCKET_UDP_SENDTO(client_s,out_buf,(int)strlen(out_buf));
						printf("\n\t\tB64 Encoded String: %s",b64Out[0]);
						TL_IPv4_SOCKET_UDP_SENDTO(client_s,b64Out[0],(int)strlen(b64Out[0]));

						TL_2D_Char_Array_FREE(b64Out);
					}
					TL_IPv4_SOCKET_CLOSE(client_s);

					printf("\n\nPress Enter to Continue...");
					getchar();
					CurrentTest=0;
					break;
				case 12:
					//////////////////////////////////////////////////////////////////////////////////////////
					// TODO: 12. Internet Creation UDP - Receiver
					// WHAT: Simple IPv4 UDP Listener implementation.

					// WHY: Because Internet.

					// Example Use:
					//NO IP SETTINGS NEEDED; Defaults are for listen to ALL Inet Interfaces on port 1337
					printf("\n\nTest[%i/%i]: %s",CurrentTest,Tests,TestNames[CurrentTest-1]);
					printf("\n\tWould you like to run 1) Server (for the Client-Server) or 2) N Message Listener? (1-2): ");
					fgets(in_buf,10,stdin);

				    TL_IPv4_SOCKET_UDP_INIT(server_s);
					//TL_IPv4_SOCKET_SETIP(server_s,IP_Dest);
					TL_IPv4_SOCKET_BIND(server_s);

					if(strcmp(in_buf,"1\n")==0){ //Remember that fgets will store the \n !!!
					    printf("\n\t[%i/%i] Awaiting Client's 2nd SENDTO",current2,counter3);
				        TL_TPv4_SOCKET_UDP_RECVFROM_2RESPOND(server_s,in_buf,client);
						printf("\n\t\tThe RECVFROM_2RESPOND Message: %s",in_buf);
						printf("\n\tIP address of client = %s  port = %d)", inet_ntoa(client_ip_addr),ntohs(client_addr.sin_port));
						current2++;

					    printf("\n\t[%i/%i] Awaiting Client's 2nd SENDTO",current2,counter3);
                		TL_TPv4_SOCKET_UDP_RECVFROM_2RESPOND(server_s,in_buf,client);
						printf("\n\t\tThe RECVFROM_2RESPOND Message: %s",in_buf);
						printf("\n\tIP address of client = %s  port = %d)", inet_ntoa(client_ip_addr),ntohs(client_addr.sin_port));
						current2++;

						printf("\n\t[%i/%i] Sending Message back to Client..",current2,counter3);
				        strcpy(out_buf, "This is a reply message from SERVER to CLIENT");
                        TL_IPv4_SOCKET_UDP_SENDTO_2RESPOND(client,out_buf,strlen(out_buf),server_s);
						current2++;

						printf("\n\t[%i/%i] Cleaning up used sockets...\nDone!\n\n",current2,counter3);
					}
					else if(strcmp(in_buf,"2\n")==0){ //Remember that fgets will store the \n !!!
						printf("\n\tHow many packets would you like to listen for (0-1000000): ");
						fgets(in_buf,8,stdin);
						counter=atoi(in_buf)%1000001;

						printf("\n\tAwaiting for message...");
						counter2=0;
						//printf("\n\tListening on Port %i for %i packets...\n",IP_Port,counter);

                        ///TL_2D_Array_Create(char,b64Out3,1,(int)strlen(in_buf)+1);
                        ///TL_2D_Array_Set_Default(b64Out3,'\0');
                        
						while(counter2<counter){
							TL_IPv4_SOCKET_UDP_RECVFROM(server_s,in_buf);
							in_buf[server_s_retcode]='\0';
							printf("\n\t[%i/%i] Received from client: \t%s ", counter2+1,counter,in_buf);
                          ///  TL_B64_DECODE_WITH_BUFFER(in_buf,b64Out3[0],(int)strlen(in_buf));
                          ///  printf("\n\tThis is what the Base 64 Decoding is (%i):%s\n", (int)strlen(b64Out3[0]),b64Out3[0]);

                            counter2++;
						}
                        ///TL_2D_Char_Array_FREE(b64Out3);
					}

					TL_IPv4_SOCKET_CLOSE(server_s);

					printf("\n\nPress Enter to Continue...");
					getchar();
					CurrentTest=0;
					break;
				case 13:
					//////////////////////////////////////////////////////////////////////////////////////////
					// TODO: 13. Internet Creation TCP - Client
                    // WHAT: Simple IPv4 UDP Listener implementation.
                    
                    // WHY: Because Internet.
                    
                    // Example Use:
                    printf("\n\nTest[%i/%i]: %s",CurrentTest,Tests,TestNames[CurrentTest-1]);
                    TL_IPv4_SOCKET_TCP_INIT(TCPClientEx);
					//TL_IPv4_SOCKET_SETPORT(TCPClientEx,PORT_NUM);
                    TL_IPv4_SOCKET_SETIP(TCPClientEx,IP_Dest);

					printf("\n\n\tConnecting to %s:%i...",IP_Dest,1337);

					TL_IPv4_SOCKET_TCP_CONNECT(TCPClientEx);

					printf("\n\n\tSuccessfully connected, and waiting to receive the message...");
					TL_IPv4_SOCKET_TCP_RECEIVE(TCPClientEx, in_buf, sizeof(in_buf));
					printf("\nReceived from server:\n%s", in_buf);

					printf("\n\n\tPreparing a response message..");
					strcpy(out_buf, "This is a reply message from CLIENT to SERVER");
					TL_IPv4_SOCKET_TCP_SEND(TCPClientEx,out_buf,(strlen(out_buf) + 1));

					printf("\n\n\tMessage sent! Closing down connection!");
                    TL_IPv4_SOCKET_CLOSE(TCPClientEx);

					printf("\n\nPress Enter to Continue...");
					getchar();
					CurrentTest=0;
					break;
				case 14:
					//////////////////////////////////////////////////////////////////////////////////////////
					// TODO: 14. Internet Creation TCP - Server
                    // WHAT: Simple IPv4  TCP Server implementation.
                
                    // WHY: Because Internet.
                
                    // Example Use:
                    printf("\n\nTest[%i/%i]: %s",CurrentTest,Tests,TestNames[CurrentTest-1]);
                    TL_IPv4_SOCKET_TCP_INIT(TCPServerListener);
                    TL_IPv4_SOCKET_TCP_BIND_and_LISTEN_INIT(TCPServerListener,1);
                    
                    printf("Waiting for accept() to complete... \n");
                    TL_IPv4_SOCKET_TCP_ACCEPT(TCPServerListener,TCPClientResponder);
                    
                    memcpy(&TCPClientResponder_ip_addr, &TCPClientResponder_addr.sin_addr.s_addr, 4);
                    
                    printf("Accept completed (IP address of client = %s  port = %d) \n",inet_ntoa(TCPClientResponder_ip_addr), ntohs(TCPClientResponder_addr.sin_port));
                    strcpy(out_buf, "This is a message from SERVER to CLIENT");
                    TL_IPv4_SOCKET_TCP_SEND(TCPClientResponder,out_buf,(strlen(out_buf) + 1));
                    
                    TL_IPv4_SOCKET_TCP_RECEIVE(TCPClientResponder,in_buf, sizeof(in_buf));
                    printf("Received from client: %s \n", in_buf);
                    
                    TL_IPv4_SOCKET_CLOSE(TCPServerListener);
                    TL_IPv4_SOCKET_CLOSE(TCPClientResponder);
                
					printf("\n\nPress Enter to Continue...");
					getchar();
					CurrentTest=0;
					break;
				case 15:
					//////////////////////////////////////////////////////////////////////////////////////////
					// 15. Iso Time Strings
					// WHAT: Simple functions to grab the system time and place it into a time struct, then it 
					//		 parses the time into  a string
					
                    // WHY: Grabbing the time is NOT trivial, this makes it so. Useful for output file names.

					// TODO: Determine UTC Offset; %z or %Z should return the values --- Win8 gives Time Zone
					
                    // Example Use:
                    printf("\n\nTest[%i/%i]: %s",CurrentTest,Tests,TestNames[CurrentTest-1]);
					TL_TIME_GET();
	
					printf("\n\tThis is the full time string:  %s",TL_TIME_STRING_FULL);
					printf("\n\tThis is the date time string:  %s",TL_TIME_STRING_DATE);
					printf("\n\tThis is the clock time string: %s",TL_TIME_STRING_TIME);

					printf("\n\nPress Enter to Continue...");
					getchar();
					CurrentTest=0;
					break;
				case 99:
					RunMenu=0;
					printf("\nThanks for Running the Program!");
					break;
				default:
					#if WINDOWS
						system("cls");
					#elif NOTWINDOWS
						system("clear");
					#endif
					printf("\nTransitLib Example Program");
					printf("\n=========================");

					for(CurrentTest=0;CurrentTest<Tests;CurrentTest++){
						printf("\n%02i. %s",CurrentTest+1, TestNames[CurrentTest]);
					}
					printf("\n99. Quit");
					printf("\n\n\tPlease Enter an Example selection (1/%i): ",Tests);
					CurrentTest=atoi(fgets(MenuSelection,21,stdin))%100;
					break;
		}
	}

	//Various Cleanup
	TL_2D_Char_Array_FREE(TestNames);
	TL_IPv4_Cleanup();

	printf("\n");

	return EXIT_SUCCESS;
}
