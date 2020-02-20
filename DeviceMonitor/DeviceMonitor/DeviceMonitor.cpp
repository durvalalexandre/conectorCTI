// DeviceMonitor.cpp: DeviceMonitor é um aplicativo Windows baseado em console projetado
// para demonstrar o uso de algumas das funcionalidades comuns da API de serviços de telefonia
// operação básica. Este aplicativo demonstra processo de inicialização comum
// necessário para cada aplicativo TSAPI Client. Após a inicialização, este aplicativo
// demonstra a funcionalidade de serviços de monitoramento ao configurar um monitor em
// um dispositivo (extensão). Outras aplicações podem ser projetadas para usar outros serviços
// fornecido pela TSAPI.
//
// Nota: assegure os arquivos da biblioteca (CSTA32.lib e ATTPRV32.lib)
// estão incluídos na opção "include" do Linker na configuração do projeto.
// A seguir estão as principais APIs TSAPI demonstradas neste aplicativo:
// 1: Adquira uma lista de nome de serviço anunciado usando o método acsEnumServerNames ().
// 2: Abra um fluxo de Serviços de Controle de API (ACS) usando o método acsOpenStream ().
// 3: Defina um método para receber notificação de evento do TSAPI Service
// usando o método acsSetESR ().
// 4: Recupere eventos da fila de eventos da biblioteca do Cliente usando acsGetEventBlock ()
// e o método acsGetEventPoll ().
// 5: monitore um dispositivo (extensão) usando o método cstaMonitorDevice ().
// 6: Pare de monitorar o dispositivo monitorado usando o método cstaMonitorStop ().
// 7: Aborta o fluxo ACS aberto usando o método acsAbortStream ().
// 8: Feche o fluxo ACS aberto usando o método acsCloseStream ().

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <tchar.h>
#include <map>
#include <windows.h>
#include <string>
using namespace std;
char* UCID = "";
char UUI[50];
char str[150];
char usuario[5];
char senha[9];
char url[100];
char navegador[100];
char ramal[10];
char debug[10];
char endereco[100];

// TSAPI required header files
// Contains event structure and macros definition
// CSTA Events Defines	
// ATT Private Defines


#include <stdio.h>
#include <conio.h>
#include "acs.h"
#include "csta.h"	
#include "attpriv.h"
#include "ATT_private_identifiers.h"

// Gloabal variables declaration - Starts Here
// This demo application stores monitor cross reference ID
// and InvokeIDs returned from APIs in global variables for
// simplicity, other applications should be designed to store
// these values in a map or any other data structure.

// Store the Monitor Cross reference ID returned by the Monitor Service
CSTAMonitorCrossRefID_t g_lMonitorCrossRefID;

// To store InvokeID for open stream request
int g_nOpenStreamInvokeID = 0;
// To store InvokeID for close stream request
int g_nCloseStreamInvokeID = 0;
// To store InvokeID for start monitor device request
int g_nStartMonitorInvokeID = 0;
// To store InvokeID for stop monitor device request
int g_nStopMonitorInvokeID = 0;
// Handle object used to wait for acsOpenStreamConf Event
HANDLE g_hOpenStreamConfEvent;	
// Handle object used to wait for acsCloseStreamConf Event
HANDLE g_hCloseStreamConfEvent;	
// Handle object used to wait for MonitorDeviceConf Event
HANDLE g_hMonitorDeviceConfEvent;	
// Handle object used to wait for MonitorStopConf Event
HANDLE g_hMonitorStopConfEvent;	
// Contain private data version that is requested by user
// for negotiation. 

Version_t g_szPrivateDataVersion;
// Count for the available service names

static int nServicesCount = 0;
// Data structure to store service name

map<int, char*> serviceNameMap;
typedef pair <int, char*> serviceNamePair;
// Gloabal variables declaration - Ends Here
// Method Declaration - Starts Here
// Method to open an ACS stream

bool OpenACSStream(ACSHandle_t* a_pAcsHandle);

// Method to monitor a device
void MonitorDevice(ACSHandle_t* a_pAcsHandle);
// Method to stop monitoring

void StopMonitor(ACSHandle_t* a_pAcsHandle);
// Method to Close an ACS stream

void CloseStream(ACSHandle_t* a_pAcsHandle);

// Method to Abort an ACS Stream
void AbortStream(ACSHandle_t* a_pAcsHandle);
// Callback function that will be called when an event
// is available in Client library event queue

void __stdcall ESRCallback (unsigned long esrParam);
// Method to that retrieve the events from Client library event queue
// and process each event.

void Notify(ACSHandle_t* a_pAcsHandle); 
// Initializes application variables

bool InitApplication();
// Print error messages and exit the application

void PrintErrorAndExit(ACSHandle_t* a_pAcsHandle);
// Enumerate service names registered with TSAPI Service.

void EnumerateServiceNames();
// Method Declaration - Ends Here
// This is starting point where the application will begin from


int _tmain(int argc, _TCHAR* argv[]){

	FILE *arq;
	char linha[100];
	char *result;
	int i;
	// Abre um arquivo TEXTO para LEITURA
	arq = fopen("Config.ini", "rt");


  if (arq == NULL)  // Se houve erro na abertura
  {
     printf("Problemas na abertura do arquivo\n");

  }
  i = 1;
  while (!feof(arq))
  {
      result = fgets(linha, 100, arq);  
	  if (result){
		  switch(i){
			case 1:
				{
				int tamanho = strlen(linha) - 1;
				strncpy(usuario,&linha[0],tamanho);
				break;
				}
			case 2:
				{
				int tamanho = strlen(linha) - 1;
				strncpy(senha,&linha[0],tamanho);
				break;
				}
			case 3:
				{
				int tamanho = strlen(linha) - 1;
				strncpy(url,&linha[0],tamanho);
				break;
				}
			case 4:
				{
				int tamanho = strlen(linha) - 1;
				strncpy(navegador,&linha[0],tamanho);
				break;
				}
			case 5:
				{
				int tamanho = strlen(linha) - 1;
				strncpy(ramal,&linha[0],tamanho);
				break;
				}
				
			case 6:
				{
				int tamanho = strlen(linha) - 1;
				strncpy(debug,&linha[0],tamanho);
				break;
				}
			default:
				{
				cout << "terminou";
				break;
				}
			}
		  i++;
		}
	}
	fclose(arq);
	strcpy(endereco, navegador);
	strcat(endereco, url);



	// Maximum wait time interval for receiving an event
	const int APP_DEF_WAIT_TIMEOUT = 5000; // Five seconds
	// For variable initialization defined at application scope
	InitApplication();
	cout<<"*********** TSAPI SAMPLE CLIENT *********** "<<endl;
	EnumerateServiceNames();

	if(strcmp (debug, "debugfalse") == 0){
		HWND window;
		AllocConsole();
		window = FindWindowA("ConsoleWindowClass", NULL);
		ShowWindow(window,0);
	}
	
	// Open an ACS stream to access features supported by a service
	// that is advertised by AE Services server.

	cout << endl << endl << " Trying to Open an ACS Stream...."<<endl<<endl;
	// Store handle of the ACS stream
	ACSHandle_t* pAcsHandle = new ACSHandle_t;
	if (OpenACSStream(pAcsHandle)){
		// Wait until we receive a confirmation event for 
		// acsOpenStream() request
		if(WaitForSingleObject(g_hOpenStreamConfEvent, APP_DEF_WAIT_TIMEOUT) == WAIT_OBJECT_0) {	
			// Start monitoring a device
			cout<<" Trying to Monitor a device..." << endl;
			MonitorDevice(pAcsHandle);
			// Wait until we receive a confirmation event for 
			if(WaitForSingleObject(g_hMonitorDeviceConfEvent, APP_DEF_WAIT_TIMEOUT) == WAIT_OBJECT_0)
			{
				do{
					// This loop run until user press X or x on console, till that  
					// time we will continue receiving monitor event.
					char chInputChar = _getche();
					if(chInputChar == 'X' || chInputChar == 'x'){
						break;
					}
					else{
						// Continue with loop
					}
				}while(true);// loop ends when user press X or 
				// Stop the Monitor request
				cout << endl << " Trying to Stop the Monitor...." << endl << endl;
				StopMonitor(pAcsHandle);
				// Wait until we receive a confirmation event for 
				if(WaitForSingleObject(g_hMonitorStopConfEvent, APP_DEF_WAIT_TIMEOUT)== WAIT_OBJECT_0){
					cout << " Application has received monitor closed confirmation event." << endl;
				}// end of if
				else
				{
					cout << " Error: MonitorStopConfEvent event not received in set time limit." << endl;
					PrintErrorAndExit(pAcsHandle);
				}
			}// end of if
			else{
				cout << " Error: MonitorDeviceConfEvent event not received in set time limit." << endl;
				PrintErrorAndExit(pAcsHandle);
			}

		}// end of if 
		else{
			cout << " Error: OpenStreamConfEvent event not received in set time limit." << endl;
			PrintErrorAndExit(pAcsHandle);
		}
		
		// Close the ACS stream
		cout<<" Trying to close the stream...." <<endl <<endl;

		// Close the opened stream
		CloseStream(pAcsHandle);

		if(WaitForSingleObject(g_hCloseStreamConfEvent, APP_DEF_WAIT_TIMEOUT) == WAIT_OBJECT_0){
			cout << " Application has received close stream confirmation event." << endl;
		}// end of if
		else
		{
			cout << " Error: CloseStreamConfEvent event not received in set time limit." << endl;
			PrintErrorAndExit(pAcsHandle);
		}
	}
	else{
		// when the application reaches here then that means s
		// the application is not able to send request for Opening the Stream
		cout << " Error: Failed to open stream.... ";
	}

	delete pAcsHandle;
	return 0;
}// end of main

void PrintErrorAndExit(ACSHandle_t* a_pAcsHandle)
{
	cout << " Due to the error occured, the application will close now, please retry after some time." << endl;
	// As we are closing the application in an error condition
	// we should abort the ACS stream using acsAbortStream method
	// which will free the resource immediately.
	// Abort the opened stream

	AbortStream(a_pAcsHandle); 
	exit(-1);
}
bool InitApplication(){
	// The CreateEvent function creates or opens a named or unnamed 
	// event object.
	g_hOpenStreamConfEvent =    CreateEvent(0,TRUE,FALSE,0); 
	g_hCloseStreamConfEvent =    CreateEvent(0,TRUE,FALSE,0); 
	g_hMonitorDeviceConfEvent = CreateEvent(0,TRUE,FALSE,0);
	g_hMonitorStopConfEvent =   CreateEvent(0,TRUE,FALSE,0);
	return true;
}
// This is the call back method that will be called when 
// an incoming event is available in the Client library queue.
// @param esrParam: acsHandle passed in this parameter.
void __stdcall ESRCallback (unsigned long esrParam){
	ACSHandle_t* acsHandle = (ACSHandle_t*) esrParam;
	Notify(acsHandle);
}
// OpenACSStream() method: This method demonstrates the use of acsOpenStream()
// method which is used to establish a communication channel between the 
// application and the TSAPI Service to access the advertised services.
bool OpenACSStream(ACSHandle_t* a_pAcsHandle){
	// constants will be used in acsOpenStream method.
	const int SEND_QUEUE_SIZE = 0;
	const int RECEIVE_QUEUE_SIZE = 0;
	const int SEND_EXTRA_BUF_SIZE = 5;
	const int RECEIVE_EXTRA_BUF_SIZE = 5;
	const int MINIMUM_LENGTH = 3;

	// Store the Return code of the method
	RetCode_t nRetCode;		
	// To hold the advertised service name
	ServerID_t szServiceName; 
	// To hold CTI user login ID
	LoginID_t szLoginID;	
	// To hold CTI user password
	Passwd_t szPassword;
	// To hold authentication information
	ACSAuthInfo_t authInfo;

	// This demo application request user to enter advertised service Name,
	// login ID and password. Other application can read this information
	// from configuration file or any other data source as appropriate.

	// Request application user to provide advertised service name
	
	strcpy_s(szServiceName, "AVAYA#EASRVAES#CSTA#AES1-EUROP");

	// Use acsQueryAuthInfo( ) to determine the login and password requirements
	// when opening an ACS stream to a particular advertised CSTA service.
	nRetCode = acsQueryAuthInfo((ServerID_t*) szServiceName, &authInfo);
	if(nRetCode != ACSPOSITIVE_ACK){
		cout << " Error: acsQueryAuthInfo method failed. ";
	}
	switch(authInfo.authType){
	case needLoginIdAndPasswd: {
			
			char* usuario2 = (char*) usuario;
			strcpy(szLoginID, usuario2);

			char* senha2 = (char*) senha;
			strcpy(szPassword, senha2);

			break;
		}
	case authLoginIdOnly:
		{
			// We should request user to enter only login ID.
			cout << endl << " Please enter login ID: ";
			// To hold login
			cin >> szLoginID;

			break;
		}
	default:
		{
			// Default login ID for this application
			strcpy_s(szLoginID, "meeta");
			// Default password for this application
			strcpy_s(szPassword, "Meet@2014");
		}
	}

	// Assuming login ID and Password minimum length is 
	// greater than three char. Using default if user do not enter
	// correct credentials.
	if(strlen(szLoginID) < MINIMUM_LENGTH){
		cout << endl << " An incorrect LoginID is supplied, using default LoginID.";
		// Default login ID for this application
		strcpy_s(szLoginID, "meeta");
	}
	if(strlen(szPassword) < MINIMUM_LENGTH)
	{
		cout << endl << " An incorrect Password is supplied using default Password.";
		// Default password for this application
		strcpy_s(szPassword, "Meet@2014");
	}
	// To hold the Application Name, the system uses the application
	// name on certain administration and maintenance status displays.
	
	AppName_t szAppName = "DeviceMonitor";

	// Can be empty string
	// This parameter contains an ASCII string that is formatted with no spaces, 
	// as follows: TSn-n:5
	// where:
	// TS is a fixed constant (use uppercase characters).
	// n is a number indicating the TSAPI version
	// - (hyphen) character indicates a range of versions.
	// : (colon) character indicates a list of versions.
	// Example
	// The following example depicts how an application specifies that it can use 
	// TSAPI versions 1 through 3 (1,2, and 3) and version 5.
	// TS1-3:5
	
	Version_t szApiVersion = "TS1-2";

	// Set a unique value in this parameter in case Application generated
	// invokeID is used.
	// As in this example we are using Library generated invokeID, this
	// parameter value is set to zero.
	
	InvokeID_t lInvokeID = 0; 

	// Below code demonstrate the process to send private data version 
	// negotiation information in the acsOpenStream() method. 

	// ATT service request private data buffer
	ATTPrivateData_t privateData;

	// Set the vendor field to 'VERSION'
	strcpy_s(privateData.vendor, "VERSION");		

	// Set the data field to a one byte discriminator 
	// PRIVATE_DATA_ENCODING followed by an ASCII string identifying 
	// the version of the private data. Setting the first byte to 
	// PRIVATE_DATA_ENCODING

	privateData.data[0] = PRIVATE_DATA_ENCODING;
	// A special function is used to convert version string into the format 
	// required by the acsOpenStream function.
	//cout << endl << " Please enter private data version: ";
	//cin >> g_szPrivateDataVersion;

	strcpy_s(g_szPrivateDataVersion, "8");

	// Setting the formatted PDV version starting from second byte in the data 
	// field.
	if((attMakeVersionString(g_szPrivateDataVersion, &(privateData.data[1]))) > 0 )
	{
		// Setting the privateData length, adding 2 extra bytes here, one byte for 
		// element at zero location (i.e. data[0] as it is one byte long)
		// and one byte for trailing null (as the ASCII string will be 
		// null terminated).
		privateData.length = (unsigned short) strlen(&privateData.data[1]) + 2; 
	}
	else
	{
		// attMakeVersionString failed due to incorrect version passed.
		cout << endl << "attMakeVersionString() method failed...";
		cout << endl << "If you want to continue, a default Private Data Version string (3-8) will be used. Press y/Y to continue or any other key to exit the application... ";
		char cContinue = _getche();
		if(cContinue == 'Y' || cContinue == 'y'){
			// If the attMakeVersionString fails, to continue without private data 
			// set the privateData.length to 0.
			// Note that in this case private data will not be available to the 
			// application. ACSOpenStreamConfEvent event will receive 0 length PD.
			// privateData.length = 0;
			// As this application make use of private data, setting PDV to a 
			// default value "3-8" in this case.

			strcpy_s(g_szPrivateDataVersion, "12");
			// Calling attMakeVersionString again with default PDV
			if((attMakeVersionString(g_szPrivateDataVersion, &(privateData.data[1]))) > 0 )
			{
				privateData.length =(unsigned short)strlen(&privateData.data[1]) + 2;
			}
			else{
				// Probably using TSAPI client library from the older version
				exit(-1);
			}
		}
		else{
			// Exit as user do not want to continue.
			exit(-1);
		}
	}
	bool bIsSuccess = false;
	while(!bIsSuccess){
		// Open a stream with Private Data negotiation & with library 
		// generated InvokeID. This method will returns invokeID on success
		// as LIB_GEN_ID is used. The invokeID will be stored in nRetCode.
		// If the application does not wish to receive Private Data, it should
		// pass 0 in privateData parameter.
		nRetCode = acsOpenStream(a_pAcsHandle,
			LIB_GEN_ID,	// Library takes the control for generating InvokeID.
			lInvokeID,	// This param is ignored when the 2nd parameter is LIB_GEN_ID
			ST_CSTA,		// requesting CSTA stream type.
			&szServiceName,	// CTI Link name "AVAYA#SWITCH1#CSTA#SERVERNAME1" 
			&szLoginID,	    // CTI user login ID
			&szPassword,	// CTI user password
			&szAppName,	    // name of the application
			ACS_LEVEL1,	    // LIB Version, will be ignored 
			&szApiVersion,	// API Version
			SEND_QUEUE_SIZE,// send queue size using default 0
			SEND_EXTRA_BUF_SIZE, // send extra buf size
			RECEIVE_QUEUE_SIZE, // receive queue size using default 0
			RECEIVE_EXTRA_BUF_SIZE,	// receive extra bufs
			(PrivateData_t *)&privateData // buffer for Private Data
			);

		// If nRetCode is returned as positive value then this suggests 
		// that TSAPI Client Library has accepted the method and
		// has placed the request in the queue for sending the 
		// request to TSAPI Service.
		// If negative value is returned then TSAPI CLient library
		// has rejected the request and has provided the error code.

		if(nRetCode > 0) // acsOpenStream returned successfully
		{
			// storing invoke ID for future use
			g_nOpenStreamInvokeID = (int) nRetCode;
			bIsSuccess = true; // Stop the loop
		}
		else if(nRetCode < 0) // acsOpenStream failed
		{
			// Other applications should do the error handling as per need  
			// like logging error in a log file or event viewer. For some of these  
			// error you can take corrective action and retry e.g. if you receive 
			// ACSERR_APIVERDENIED, you can try with another version.
			switch(nRetCode){
			case ACSPOSITIVE_ACK:
				{
					// The function is successful
					bIsSuccess = true; // Stop the loop
					break;
				}
			case ACSERR_APIVERDENIED:
				{	// This return value indicates that the API Version requested is
					// invalid and not supported by the existing API Client Library.
					cout << " Error: acsOpenStream method failed to open stream.." << endl;
					// Requesting user to enter TSAPI version again.
					cout << " Error: API Version is incorrect. Trying again." << endl;
					bIsSuccess = false; // Continue the loop
					break;
				}
			case ACSERR_BADPARAMETER:
				{	// One or more parameters invalid.
					// Validate supplied parameter with the help of 
					// TSAPI Exerciser tool.
					break;
				}
			default:
				{
					// Some unhandled error occured
					const int SLEEP_TIME = 3000;
					cout << endl << " Error: acsOpenStream method failed to open stream..";
					cout << endl << " Error code: " << nRetCode;
					Sleep(SLEEP_TIME);
					return false;
				}
			}
		}
		else // case when nRetCode == 0
		{
			// Not possible as LIB_GEN_ID is used in this example.
		}
	}
	// acsSetESR(): This method is used to register a callback method with 
	//  Client library to receive a notification when an event is available
	//	in the Client library’s event queue.
	//	If the method is successful, the Client library will call ESRCallback
	//	method whenever there is an event is available in its event queue.
	//  @a_pAcsHandle: Handle returned by the acsOpenStream() method
	//  @ESRCallback: Call back routine invoked when there is an incoming event.
	//	@a_pAcsHandle: An open ACS stream handle is passed in this parameter
	//		whick will be passed in ESRCallback method as parameter.
	//  @notifyAll: TRUE indicates that the ESRCallback will be called 
	//		for each new event that arrives in Client library's event queue. 
	//		A FALSE value will indicate that the ESRCallback will
	//		only be called each time the Client library's event queue becomes 
	//		non-empty.

	nRetCode = acsSetESR(*a_pAcsHandle, ESRCallback, (unsigned long)a_pAcsHandle, TRUE);
	// Verification for the positive response
	if(nRetCode != ACSPOSITIVE_ACK){
		cout<<" ERROR: acsSetESR() method return with an error.";
		if(nRetCode == ACSERR_BADHDL){
			cout<<" ulAcsHandle being used is not a valid handle"<<endl;
		}
		else{
			cout << " acsSetESR() failed with unknown error. " << endl;
			cout << " Error code: " << nRetCode;
		}
	}
	return true;
}
// MonitorDevice() : This method demonstrates the use of cstaMonitorDevice() 
// method which is used to monitor the device (Extension) and to receive the 
// events that arrive at the device after monitor request acknowledged.
void MonitorDevice(ACSHandle_t* a_pAcsHandle){
	// Set the DeviceID of the Deivce to be monitored
	char* ramal2 = (char*) ramal;
	DeviceID_t szDeviceID;
	strcpy(szDeviceID, ramal2);
	
	// Default device ID	
	//cout << " Por favor, digite o ramal a ser monitorado: \a";
	//cin >> szDeviceID;
	// Store the return code of the method
	RetCode_t nRetCode = 0;
	CSTAMonitorFilter_t filter;	// Store the Montor Filter setting	

	// Pass 0 for a specific filter category or pass NULL for the filter parameter.
	// Call filters are supported for station device.
	filter.call = cfQueued; // Settting filter for Call Queued event.

	// The Agent Filter is supported only for ACD Split devices.
	filter.agent = 0; 
	
	// We are using a extension device in this example
	// The Feature Filter and Maintenance Filter are not supported.
	filter.feature = 0; 
	filter.maintenance = 0;

	// A zero Private Filter means that the application wants to receive
	// the private events. If Private Filter is non-zero, private events 
	// will be filtered out.
	filter.privateFilter = 0;

	// cstaMonitorDevice(): Sending a request to monitor a device.
	// @a_pAcsHandle : Handle returned from the acsOpenStream() method
	// @szDeviceID : Specifies the DeviceID of the device to be monitored
	// @filter : Filter to be set for receiving the events. if NULL is passed 
	//			then No filter will be set and application will receive event 
	//			reports for all events.
	// @privateData: Not passing private data with this request.

	nRetCode = cstaMonitorDevice( *a_pAcsHandle, // ACS Stream handle
		0, // Invoke ID is ignored, as it is library generated
		&szDeviceID, // ID of the device to be monitored
		&filter, // Filter setting that will apply on monitor
		NULL // Private data not passed with this request
		);

	if(nRetCode < 0)
	{
		cout<<" Failed to monitor device ID: "<< szDeviceID <<endl;
		cout<<" Error code: " << nRetCode;
	}
	else
	{
		// cstaMonitorDevice returned successfully
		g_nStartMonitorInvokeID = nRetCode;
	}
}
// StopMonitor() : This method demonstrates the use of cstaMonitorStop() method
// which is used to stop the monitor request for a perticular device.
// After invoking this method application will not receive any
// event for the device on which monitor service was activated.
void StopMonitor(ACSHandle_t* a_pAcsHandle)
{
	// cstaMonitorStop(): Request to stop the monitor on device.
	// @a_pAcsHandle: Handle returned from the acsOpenStream() method
	// @invokeID: Setting it to zero as Library generated ID is used in this
	//		example.
	// @g_lMonitorCrossRefID: Specifies the Monitor cross reference ID received 
	//		in the cstaMonitorDeiviceConf event.
	// @privateData: - Presently this parameter is ignored so please pass NULL
	//					in this parameter for cstaMonitorStop() method

	// Store the Return code of the method
	RetCode_t nRetCode;
	nRetCode = cstaMonitorStop (*a_pAcsHandle,
		0,
		g_lMonitorCrossRefID,
		0);
	// Checking for the negative response	
	if ( nRetCode < 0)
	{
		cout<<" Failed to stop monitor" <<endl;
		cout<<" Error Code :" <<nRetCode;
		return;
	}
	else
	{
		// Request is successful.	
		g_nStopMonitorInvokeID = nRetCode;
	}
}
// AbortStream() : This method demonstrates the use of acsAbortStream() method.
void AbortStream(ACSHandle_t* a_pAcsHandle){
	// acsAbortStream(): Request to abort an ACS stream. No confirmation event
	//		will be provided for this method.
	// @a_pAcsHandle: Handle returned from the acsOpenStream() method
	// @privateData: - Presently this parameter is ignored so please pass NULL
	//					in this parameter for acsAbortStream() method

	RetCode_t nRetCode = acsAbortStream(*a_pAcsHandle, NULL);
	// Checking for the negative response
	if(nRetCode<0){
		if(nRetCode==ACSERR_BADHDL){
			cout<<" The ACS Handle is invalid "<<endl<<endl;
		}
		else{
			cout<< " acsAbortStream() failed with unknown error. " << endl;
			cout << " Error code: " << nRetCode;
		}	
	}
	else{
		cout<<" ACS Stream aborted successfully... "<<endl<<endl;
	}
}

// CloseStream(): This function demonstrates the use of acsCloseStream() method
// which is used to close an ACS stream. The application will be unable to
// request services from the AE Services server after the success of this method.
void CloseStream(ACSHandle_t* a_pAcsHandle){
	// acsCloseStream(): Request to close an ACS stream. A confirmation event
	//		will be provided for this method.
	// @a_pAcsHandle: Handle returned from the acsOpenStream() method
	// @invokeID: Setting it to zero as Library generated ID is used in this
	//		example.
	// @privateData: - Presently this parameter is ignored so please pass NULL
	//					in this parameter for acsCloseStream() method
	RetCode_t nRetCode = acsCloseStream(*a_pAcsHandle, 0, NULL);

	// Checking for the negative response
	if ( nRetCode < 0){
		// Vrifying for the ACS handle
		if(nRetCode == ACSERR_BADHDL){
			// This error indicates the ACS handle passed in acsCloseStream method
			// is invalid. Please check valid handle value passed to acsCloseSream
			// method. The handle could be invalid because the stream associated 
			// with it, is already closed or the TSAPI Client library could not find 
			// the associated stream. In this case the application will not receive
			// an ACSCloseStreamConfEvent. 
			cout << " The ACS Handle is invalid" << endl;
		}
		else{
			cout<< " acsCloseStream() failed with unknown error. " << endl;
			cout << " Error code: " << nRetCode;
		}
	}
	else{
		cout << " ACS Stream close request sent successfully... " << endl;
		g_nCloseStreamInvokeID = nRetCode;
	}
}
// Notify() method will be called by ESRCallback method whenever it
// receive a event notification. This method retrive event from event  
// queue using acsGetEventBlock() or acsGetEventPoll() methods. The
// event information is extracted from event object and processed as
// per this application design. Other application should be designed to 
// include event processing logic as per their needs.
void Notify(ACSHandle_t* a_pAcsHandle){
	// A boolean variable which will be true if event is successfully
	// retrieved otherwise false.
	bool isEventRetrived = false;
	// This hold the size the application will allocate initially to 
	// the event buffer. Keeping the size of event buffer will reduce
	// applications memory footprint. If this size is set to  
	// a smaller value than the size of any event (say 64), then 
	// application receive an error (i.e. ACSERR_UBUFSMALL). In this
	// case application should try to retrieve event with a larger 
	// event buffer. Below code demonstrate the implementation for this
	// scenario.
	const int APP_DEF_DEFAULT_BUFFER_SIZE = 512;

	// CSTA event buffer size
	unsigned short usEventBufSize = APP_DEF_DEFAULT_BUFFER_SIZE;
	// A pointer to CSTAEvent_t structure, a pointer is being used 
	// instead of a non-pointer variable as non-pointer variable will
	// reserve fixed memory space on stack 
	CSTAEvent_t *cstaEvent = NULL;


	// Number of events in the Client library queue
	// Default value assumed 1, we will receive exact value after
	// acsGetEventBlock() method return.
	unsigned short usNumEvents = 1; 

	// We are running a loop here which will run until we successfully 
	// retrieved the event or count of events in the Client library 
	// queue has become zero and size of event buffer has become zero.
	while(!isEventRetrived || ( usNumEvents > 0 && usEventBufSize > 0)){
		// To hold the error cause
		int nError;
		// ATT service request private data buffer that store
		// private data coming with event.
		ATTPrivateData_t privateData;
		
		// Setting the private data length same as the size of
		// data field of ATTPrivateData_t structure.
		privateData.length = sizeof(privateData.data);

		// For the next iterations need to free the memory
		// before reallocating new memory.
		if(NULL != cstaEvent){
			//Free the buffer memory
			free(cstaEvent);
		}

		// Reallocate buffer in case any failure detected in 
		// retrieving event earlier.
		cstaEvent = (CSTAEvent_t*) malloc((SIZE_T) usEventBufSize);

		// To store method return value
		RetCode_t nRetCode;

		// BLOCKING_MODE can be defined in the project settings > C/C++ >
		// Preprocessor to use acsGetEventBlock() method. If application
		// wants to use acsGetEventPoll method instead, exclude BLOCKING_MODE
		// from project setting.

		#ifdef BLOCKING_MODE{
			// Receiving the events in Blocking mode: 
			// GetEventBlock() method is used to extract the events in the 
			// Blocking mode. In the Blocking mode, the application's calling thread 
			// will be blocked until there is an event from the ACS stream.
			// @a_pAsHandle: Handle returned from the acsOpenStream() method.
			// @cstaEvent: Pointer to an area in the application address 
			//					  space large enough to hold event that 
			//					  will be copied by Client library.	
			// @usEventBufSize: Specifies the size of event buffer.
			// @privateData: Points to a buffer which will receive any private 
			//	data that accompanies this event. If the application does not wish
			//	to receive private data, then privateData should be set to 0.
			// @usNumEvents: Specifies the count of events still pending in Client 
			//	library queue to be retrieved on this ACS stream. 

			nRetCode = acsGetEventBlock(*a_pAcsHandle, (void *)cstaEvent, &usEventBufSize, (PrivateData_t *)&privateData, &usNumEvents );
		}
		#else
		{
			// Receiving events in Non-Blocking mode
			// In the Non-Blocking mode the oldest outstanding event from ACS 	
			// stream (whose handle is passed in method call) will be copied into
			// the applications data space and control will be returned immedietly	
			// to the application. 
			// If no events are currently queued for the application, the function
			// will return control immediately to the application with an error code
			// indicating that no events were available.
			//Parameter description same as acsGetEventBlock.

			nRetCode = acsGetEventPoll(*a_pAcsHandle,(void *)cstaEvent,&usEventBufSize,(PrivateData_t *)&privateData,&usNumEvents);
		}
		#endif
		if(nRetCode != ACSPOSITIVE_ACK)
		{
			if(nRetCode == ACSERR_BADHDL){
				cout << " The ACS Handle is invalid" <<endl <<endl;
			} // end of if 
			else if (nRetCode == ACSERR_UBUFSMALL){
				cout << " Passed event buffer size is smaller than the size of the next available event for this ACS Stream." << endl << endl;
				// The usEventBufSize variable has been reset by the TSAPI Client 
				// Library to the size of the next message on the ACS              
				// stream. The application should call acsGetEventBlock( ) 
				// again with a larger buffer. The ACS event still present 
				// on the Client Library queue.
				continue;
			}// end of else if	
			else if (nRetCode == ACSERR_NOMESSAGE){
				// The acsGetEventPoll()method return this value to indicate
				// there were no events available in the Client library queue.
				cout << " No events available at this time."; 
			}
			else
			{
				cout << " acsGetEventBlock()/acsGetEventPoll() failed with unknown error. " << endl;
				cout << " Error code: " << nRetCode;
				break;
			}
		}// end of if 
		else{
			// Setting true as we have successfully retrieved event
			isEventRetrived = true;

			// Checking for Confirmation event for the Open Stream request
			switch(cstaEvent->eventHeader.eventClass)
			{
			case ACSCONFIRMATION:
				{
					switch(cstaEvent->eventHeader.eventType)
					{
					case ACS_OPEN_STREAM_CONF:
						{
							if(g_nOpenStreamInvokeID == cstaEvent->event.acsConfirmation.invokeID){
								cout << " acsOpenStremConfEvent received - Stream opened successfully." << endl;	
								cout << " API Version: " << cstaEvent->event.acsConfirmation.u.acsopen.apiVer << endl;
								cout << " Library Version: " << cstaEvent->event.acsConfirmation.u.acsopen.libVer << endl << endl;

								// verify that Private Data is correctly negotiated.
								// 1st check the length of the Private Data received
								if (privateData.length <= 0){
									// handle error condtion ( abort the Stream )
									// return error
									
									cout << endl << " Private Data length is zero in acsOpenStreamConf event. Private data is not sent as a part of this event.";
									
									// As this application is making use of private 
									// data features, in this condition it is 
									// appropriate to close the application as the
									// private data is not negotiated successfully.
									// This could happen if you send a PDV which is
									// not in range of PDV that AE Services server
									// supports e.g. "10-25", "0-5", "0", "10" etc

									PrintErrorAndExit(a_pAcsHandle);

									// If we do not close application and use PD
									// feature, the request in which we are using
									// PD feature will fail. In this example, 
									// cstaMonitorDevice method will fail if
									// we do not close the application at this moment.
								}
								// 2nd Check the vendor String
								if(strcmp(privateData.vendor,ECS_VENDOR_STRING) != 0 ){
									// hanlde error condtion ( abort the Stream )
									// return error
								}	
								// 3rd check the One byte descriminator
								if(privateData.data[0] != PRIVATE_DATA_ENCODING ){
									// handle error condtion ( abort the Stream )
									// return error
								}
								else{
									// Retrieving the Private Data 
									// Checking private data version, whether
									// it is same as requested or not.
									char cPDVReturned = privateData.data[1];

									// To hold returned PDV as number
									int nReturnedPDV = atoi(&cPDVReturned);
									if(strchr(g_szPrivateDataVersion, '-') == NULL)
									{
										// Requested version is specific i.e. does not contain '-'
										int nRequestedPDV = atoi(g_szPrivateDataVersion);
										if(nRequestedPDV == nReturnedPDV){
											cout << " Negotiated private data version is: " << cPDVReturned << endl;
										}
										else
										{
											cout <<" Private data version negotiation is failed.";
											// This is an error condition where AE Server does
											// not support the PDV requested.
										}
									}
									else
									{
										// A range of PDV is requested
										// Make a copy of requested PDV value, this
										// variable will also store first part of requested PDV
										// after call to strtok_s.
										char* szFirst = _strdup(g_szPrivateDataVersion);
									
										// To store second part of requested PDV
										char* szSecond;

										// strtok_s method is used to split string 
										// which is of format "m-n". This method
										// will copy m in szFirst and n in szSecond.

										strtok_s(szFirst, "-", &szSecond);
										int nMinVersion = atoi(szFirst);
										int nMaxVersion = atoi(szSecond);
										
										// compare value of m and n with
										// PDV returned.
										if(nReturnedPDV >= nMinVersion && nReturnedPDV <= nMaxVersion){
											cout << " Private data version negotiation is successful.";
											cout << " Negotiated private data version is: " << cPDVReturned << endl;
										}
										else{
											cout << " Private data version negotiation is failed.";
											// This is an error condition where AE Server does
											// not support the PDV requested.
										}
									}							
								}
								// Sets event object to signaled state.
								SetEvent(g_hOpenStreamConfEvent);
							}
							else{
								// Confirmation event received for some other open 
								// stream request.
								cout << " A confirmation event received for an unknown open stream request.";
							}
							break;
						}
					case ACS_CLOSE_STREAM_CONF:
						{
							if(g_nCloseStreamInvokeID == cstaEvent->event.acsConfirmation.invokeID){
								// Checking for confirmation event for the Close 
								// Stream request
								// Sets event object to signaled state.
								SetEvent(g_hCloseStreamConfEvent);
							}
							else{
								// Confirmation event received for some other close 
								// stream request.
								cout << " A confirmation event received for an unknown close stream request.";
							}
							break;
						}
					case ACS_UNIVERSAL_FAILURE_CONF:
						{
							// Checking for the Failure of Open Stream request
							nError = cstaEvent->event.acsConfirmation.u.failureEvent.error;
							cout << " ACS_UNIVERSAL_FAILURE_CONF event received" << endl;
							// Verifying error is for open stream that this
							// application has opened 
							if(g_nOpenStreamInvokeID ==	cstaEvent->event.acsConfirmation.invokeID){
								// Checking for the password of the loginID
								switch(nError)
								{
								case tserverBadPasswordOrLogin:{
										cout<<" CTI login password is incorrect "<<endl;
										break;
								}
								case tserverNoUserRecord:{	
										cout << " No user object was found in the security database for the login specified in the ACSOpenStream request."<<endl;
										break;
								}
								default:
								{
										cout << " ACS_UNIVERSAL_FAILURE_CONF event received with unknown error";
										cout << " Error Code: " << nError;
								}
							}
						}
						else if(g_nStartMonitorInvokeID == cstaEvent->event.cstaConfirmation.invokeID){
							// Checking for the password of the loginID
							switch(nError){
							case tserverDeviceNotSupported:{
								cout << " Error: Device not supported." << endl;
								break;
						}
							default:{
										cout << " ACS_UNIVERSAL_FAILURE_CONF event received with unknown error";
										cout << " Error Code: "<<nError;
									}
								}
							}
							else
							{
								cout << " An ACS_UNIVERSAL_FAILURE_CONF event received for an unknown request." << endl; 
								cout << " Error Code: "<<nError;
							}
							break;
						}
					default:
						{
							// Other application should add more cases as per need. 
							cout << " ACS Confirmation event received with unknown event type." << endl;
							cout << " Event Type: " << cstaEvent->eventHeader.eventType;
						}
					} // End of switch
					break;
				} // End of ACSCONFIRMATION case
			case CSTACONFIRMATION:
				{
					switch(cstaEvent->eventHeader.eventType)
					{
					case CSTA_MONITOR_CONF:
						{
							// Matching the invokeID received in this event with invokeId
							// received from invoked cstaMonitorDevice method.
							if(g_nStartMonitorInvokeID == cstaEvent->event.cstaConfirmation.invokeID){
								// Sets event object to signaled state.
								SetEvent(g_hMonitorDeviceConfEvent); 
								g_lMonitorCrossRefID = cstaEvent->event.cstaConfirmation.u.monitorStart.monitorCrossRefID;
								cout << endl << " csatMonitorDeviceConfEvent received - Monitoring started..." << endl << endl;
							}
							else
							{
								// Confirmation event received for some other monitor 
								// device request.
								cout << " A confirmation event received for an unknown monitor device request.";
							}
							break;
						}
					case CSTA_UNIVERSAL_FAILURE_CONF:{
							// Checking for the Failure of Monitor Request
							nError = cstaEvent->event.cstaConfirmation.u.universalFailure.error;
							cout << " CSTA_UNIVERSAL_FAILURE_CONF event received." << endl;
							// Verifying error is for monitor start or stop request

							if(g_nStartMonitorInvokeID == cstaEvent->event.cstaConfirmation.invokeID || g_nStopMonitorInvokeID == cstaEvent->event.cstaConfirmation.invokeID){
								// Checking the cause of the error received 
								// for the monitor request
								switch(nError){
								case invalidCstaDeviceIdentifier:{		
										cout << " Error: Invalid Devie Identifier." << endl;
										break;
									}
								case resourceBusy :						
									{
										cout << " Error: Resource is busy." << endl;
										break;
									}
								case genericOperationRejection :						
									{
										cout << " Error: GENERIC_OPERATION_REJECTION" << endl;
										break;
									}
								default:
									{
										cout << " Error: CSTA_UNIVERSAL_FAILURE_CONF event received with unknown error code." << endl;
										cout << " Error Code: " << nError;
									}
								}// end of inner switch
							}
							else
							{
								cout << " Error: CSTA_UNIVERSAL_FAILURE_CONF event received with unknown error code." << endl;
								cout << " Error Code: "<< nError;
							}
							break;
						}// end of case
					case CSTA_MONITOR_STOP_CONF:
						{
							// Matching the invokeID received in this event with invokeId
							// received from invoked cstaMonitorDevice method.
							if(g_nStopMonitorInvokeID == cstaEvent->event.cstaConfirmation.invokeID){	
								// Sets event object to signaled state.
								SetEvent(g_hMonitorStopConfEvent);
								cout << endl << " Monitor deactivated successfully... " << endl;
							}
							else
							{
								// Confirmation event received for some other stop monitor 
								// device request.
								cout << " A confirmation event received for an unknown stop monitor device request.";
							}
							break;
						}
					default:
						{
							// Other application should add more cases as per need. 
							cout << " CSTA Confirmation event received with unknown event type." << endl;
							cout << " Event Type: " << cstaEvent->eventHeader.eventType;
						}
					}// end of CSTA Confirmation event type switch
					break;
				}// end of CSTACONFIRMATION case
			case CSTAUNSOLICITED:{
					switch(cstaEvent->eventHeader.eventType){
						case CSTA_SERVICE_INITIATED:{
								cout << " A Service Initiated event is received. ";
								break;
							}
						case CSTA_DELIVERED:{	
							// Delivered event received
							// To store the connection state
							LocalConnectionState_t connectionState = cstaEvent->event.cstaUnsolicited.u.delivered.localConnectionInfo;
							CSTAEventCause_t eventCause = cstaEvent->event.cstaUnsolicited.u.delivered.cause;
							// check the connection state and cause for the event
							if( connectionState == csAlerting && eventCause == ecNewCall){
								// Retrieving the information associated with this event
								long lcallID = cstaEvent->event.cstaUnsolicited.u.delivered.connection.callID;
								char* szCallingDeviceID = cstaEvent->event.cstaUnsolicited.u.delivered.callingDevice.deviceID;
								char* alertingDevice = cstaEvent->event.cstaUnsolicited.u.delivered.alertingDevice.deviceID;
								cout << "Ligacao entrante do com ID " << lcallID << " Recebendo de " << szCallingDeviceID << " para " << alertingDevice << endl;
								// check the privateData length
								if ( privateData.length > 0 ){
									// Event buffer that will contain the decoded private data 
									// information.
									ATTEvent_t attEvent;
									// Check to ensure that private data is successfully decoded.
									if(attPrivateData(&privateData, &attEvent)==ACSPOSITIVE_ACK ){
										// check the event type					
										if (attEvent.eventType == ATT_DELIVERED){
											// This sample code snippet shows how to
											// extract UCID information from private data,
											// other application can choose to extract other private 
											// data information as required.
											// extract the Universal Call Identifier (UCID)
											UCID = attEvent.u.deliveredEvent.ucid;
											cout << " The UCID is: " << UCID;
											strcpy (str, endereco);
											strcpy (UUI, (char*) attEvent.u.deliveredEvent.userInfo.data.value);
											strcat (str, UUI);
										} // End of if
									} // End of if
									else
									{
										//Decoding Error.
										cout << " An error occured while decoding private data." << endl;
									}
								}// End of outer if
								else
								{
									// The event does not contain any private Data.
								}
							} // End of if
							break;
						} // End of Case
						case CSTA_ESTABLISHED:
							{	
							// Extract information included in this event here
							cout << "Ligacao recebida." << endl;
						
							if (strlen(UUI) > 1){
								cout << "UUI da lagacao eh: " << str << endl;
								system(str);
							}

							break;
							} // End of Case
						case CSTA_CONNECTION_CLEARED:
							{	
								// Extract information included in this event here
								cout << endl << " A Connection Cleared event is received. "<< endl;
								break;
							} // End of Case
						default:{
								cout << " tipo do evento: "<< cstaEvent->eventHeader.eventType;
							}
						} // End of switch
						break;
				}// end of CSTACONFIRMATION case
			default:
				{
					cout << " An event received with unknown event class." << endl;
					cout << " Event Class: "<< cstaEvent->eventHeader.eventClass;
				}
			}// End of event class switch
		}// end of else
	}// end of while loop
	if(NULL != cstaEvent)
	{
		//Free the buffer memory
		free(cstaEvent);
	}
} // end of Notify() method
// This is the callback method that will be called for each advertised 
// service name. serverName method parameter points to an array 
// of char which is a null-terminated string representing an  
// advertised service name or Tlink.
// This method returns a boolean value which allow application to
// request to stop receiving more service names at any point of time
// i.e. if this method returns false, it will not be called further
// with other service names.
Boolean DisplayServerNames(char* szServiceName, unsigned long lParam)
{
	Boolean bReturnValue = FALSE;
	if(strcmp(szServiceName, "") != 0){
		// Service name is printed on console here with a number
		// assigned to each service name. This application store 
		// service name into map for demonstration. User will be
		// asked to choose any of the service name later. 
		cout << endl << ++ nServicesCount << " . Service Name: " << szServiceName;
		
		// Making a copy of szServiceName in this application
		// address space.
		char *szServiceNameTemp = new char[sizeof(ServerID_t)];
		strcpy_s(szServiceNameTemp, sizeof(ServerID_t), szServiceName);
		
		// Make an entry in the service name map for later use.
		serviceNameMap.insert(serviceNamePair(nServicesCount, szServiceNameTemp));

		// Return TRUE so that the callback is called
		// again with the name of the next advertised
		// service found.
		bReturnValue = TRUE;
	}
	else
	{
		// Method received an empty buffer for service name,
		// returning false in this scenario will cause stop
		// receiving any more Service name i.e. this method
		// will not be called again.
		// bReturnValue = FALSE; 
		// Not required as default to FALSE
	}
	return bReturnValue;
}
// This method uses acsEnumServerNames() TSAPI method to specify 
// a callback method that will be called for each service name.
void EnumerateServiceNames(){

	// acsEnumServices(): This TSAPI method is used to enumerate 
	// the names of all servers of a specified stream type.
	// ST_CSTA: Indicates that CSTA services are to be enumerated.
	// DisplayServerNames: Call back fuction invoked for each service name.

	RetCode_t nRetCode = acsEnumServerNames(ST_CSTA, DisplayServerNames, NULL);
		
		// user defined variable, value of this
		// variable will be passed to the
		// callback method as lParam parameter. 
		// Passed as NULL here.
		
	if ( nRetCode != ACSPOSITIVE_ACK ){
		// some error occurred while sending request.
		cout<<" Error Code: "<<nRetCode;
		// handle error.
	}
}