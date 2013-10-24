#pragma once

#pragma pack(1)
typedef struct
{
    WORD dwSize;
    wchar_t wszAddress[0x100];
}NOKIAPHONETOOLSMSG;
#pragma pack()


typedef HRESULT (*TEXT_SEND)(LPVOID smsmcCookie,
                             const BYTE* pbData,
                             DWORD dwDataSize,
                             const BYTE* pbProviderSpecificData,
                             DWORD dwProviderSpecificDataSize,
                             LPVOID smsdeDesiredDataEncoding,
                             LPVOID prilmTemplate,
                             LPVOID smsmsmSendMessageFunction);

TEXT_SEND textSend = NULL;

#define RIL_MSGCLASS_OUTGOING                       (0x00020000)   
#define RIL_MSGTYPE_OUT_SUBMIT                      (0x00000001 | RIL_MSGCLASS_OUTGOING)  

#define MAXLENGTH_ADDRESS                           (256)   
#define MAXLENGTH_HDR                               (256)     
#define MAXLENGTH_MSG                               (512)     

typedef struct {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwType;
    DWORD dwNumPlan;
    WCHAR wszAddress[MAXLENGTH_ADDRESS];
} RILADDRESSFAKE; // 256 * 2 + 4 * 4 = 0x210

typedef struct {
    DWORD cbSize;
    DWORD dwParams;
    DWORD dwType;
    DWORD dwFlags;
    DWORD dwMsgClass;
    DWORD dwAlphabet; 
    DWORD dwIndication;
    DWORD dwLanguage;
} RILMSGDCSFAKE; // 4 * 8 = 32       = 0x20

typedef struct _RILMESSAGEFAKE
{
    DWORD cbSize;
    DWORD dwParams;
    RILADDRESSFAKE raSvcCtrAddress;
    DWORD dwType;
    DWORD dwFlags;
    RILADDRESSFAKE raDestAddress;
    DWORD dwProtocolID;
    RILMSGDCSFAKE rmdDataCoding;
    DWORD dwVPFormat;
    SYSTEMTIME stVP; //16
    DWORD cbHdrLength;
    DWORD cchMsgLength;
    BYTE rgbHdr[MAXLENGTH_HDR];
    BYTE rgbMsg[MAXLENGTH_MSG];
}RILMESSAGEFAKE;
