/* 
SMS_Providers_Ultra
(C) ultrashot 2012-2013
*/
#include "stdafx.h"
#include "ril_my.h"

HRESULT Text_Send(LPVOID smsmcCookie,
                  const BYTE* pbData,
                  DWORD dwDataSize,
                  const BYTE* pbProviderSpecificData,
                  DWORD dwProviderSpecificDataSize,
                  LPVOID smsdeDesiredDataEncoding,
                  LPVOID prilmTemplate,
                  LPVOID smsmsmSendMessageFunction) 
{
    RETAILMSG(1, (L"[SMS_Providers_Ultra] Text_Send++\r\n"));
    HRESULT hr = E_FAIL;
    if (textSend == NULL)
    {
#ifdef FORHTC
        HMODULE hLibrary = LoadLibrary(L"SMS_Providers_OEM.dll");
#elif FORSAMSUNG
        HMODULE hLibrary = LoadLibrary(L"Mits_SMS_Providers.dll");
#endif
        textSend = (TEXT_SEND)GetProcAddressW(hLibrary, L"Text_Send");
    }
    if (textSend)
        hr = textSend(smsmcCookie, pbData, dwDataSize, pbProviderSpecificData, dwProviderSpecificDataSize, smsdeDesiredDataEncoding, prilmTemplate, smsmsmSendMessageFunction);

    if (prilmTemplate)
    {
        RILMESSAGEFAKE *ril = (RILMESSAGEFAKE*)prilmTemplate;
        if (ril->dwType == RIL_MSGTYPE_OUT_SUBMIT)
        {
            HANDLE hFile = CreateFile(L"PHT1:", 0, 0, NULL, 0, 3, NULL);
            if (hFile && hFile != INVALID_HANDLE_VALUE)
            {
                NOKIAPHONETOOLSMSG msg;
                memset(&msg, 0, sizeof(msg));
                msg.dwSize = 0x1;
                wcscpy_s(msg.wszAddress, 0x100, ril->raDestAddress.wszAddress);
                DeviceIoControl(hFile, 0x2000044, &msg, sizeof(NOKIAPHONETOOLSMSG), NULL, NULL, 0,0);
                CloseHandle(hFile);
            }
        }
    }
    RETAILMSG(1, (L"[SMS_Providers_Ultra] Text_Send-- hr = %X\r\n", hr));
    return hr;
}

void Text_RecognizeMessage() {} 
void Text_GetMessageInfo() {} 

void Text_GetSize() {} 
void Text_Read() {} 
void Text_CalculateFragments() {} 
void Notify_RecognizeMessage() {} 
void Notify_GetMessageInfo() {} 
void Notify_Send() {} 
void Notify_GetSize() {} 
void Notify_Read() {} 
void Notify_RecognizeMessageInSim() {} 
void Notify_GetMessageInfoInSim() {} 
void Notify_GetSizeInSim() {} 
void Notify_ReadInSim() {} 
void WDP_RecognizeMessage() {} 
void WDP_GetMessageInfo() {} 
void WDP_Send() {} 
void WDP_GetSize() {} 
void WDP_Read() {} 
void WCMP_RecognizeMessage() {} 
void WCMP_GetMessageInfo() {} 
void WCMP_Send() {} 
void WCMP_GetSize() {} 
void WCMP_Read() {} 
void Status_RecognizeMessage() {} 
void Status_GetMessageInfo() {} 
void Status_Send() {} 
void Status_GetSize() {} 
void Status_Read() {} 
void Status_IdentifyGroup() {} 
void Status_GetStatus() {} 
void Broadcast_RecognizeMessage() {} 
void Broadcast_GetMessageInfo() {} 
void Broadcast_Send() {} 
void Broadcast_GetSize() {} 
void Broadcast_Read() {} 
void Raw_RecognizeMessage() {} 
void Raw_GetMessageInfo() {} 
void Raw_Send() {} 
void Raw_GetSize() {} 
void Raw_Read() {} 
void Class2_RecognizeMessage() {} 
void Class2_GetMessageInfo() {} 
void Class2_Send() {} 
void Class2_GetSize() {} 
void Class2_Read() {} 
void Class2_RecognizeMessageInSim() {} 
void Class2_GetMessageInfoInSim() {} 
void Class2_GetSizeInSim() {} 
void Class2_ReadInSim() {} 
void Class2Data_RecognizeMessage() {} 
void Class2Data_GetMessageInfo() {} 
void Class2Data_Send() {} 
void Class2Data_GetSize() {} 
void Class2Data_Read() {} 
void Class2Data_RecognizeMessageInSim() {} 
void Class2Data_GetMessageInfoInSim() {} 
void Class2Data_GetSizeInSim() {} 
void Class2Data_ReadInSim() {} 


BOOL APIENTRY DllMain( HANDLE hModule, 
                      DWORD  ul_reason_for_call, 
                      LPVOID lpReserved
                      )
{
    return TRUE;
}

