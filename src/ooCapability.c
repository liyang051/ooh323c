/*
 * Copyright (C) 2004-2009 by Objective Systems, Inc.
 *
 * This software is furnished under an open source license and may be
 * used and copied only in accordance with the terms of this license.
 * The text of the license may generally be found in the root
 * directory of this installation in the COPYING file.  It
 * can also be viewed online at the following URL:
 *
 *   http://www.obj-sys.com/open/license.html
 *
 * Any redistributions of this file including modified versions must
 * maintain this copyright notice.
 *
 *****************************************************************************/
#include "ooCapability.h"
#include "ootrace.h"
#include "ooCalls.h"
#include "ooh323ep.h"
#include "ooUtils.h"
/** Global endpoint structure */
extern OOH323EndPoint gH323ep;

static int giDynamicRTPPayloadType = 101;

int ooCapabilityEnableDTMFRFC2833
   (OOH323CallData *call, int dynamicRTPPayloadType)
{
   if(!call)
   {
      gH323ep.dtmfmode |= OO_CAP_DTMF_RFC2833;
      OOTRACEINFO1("Enabled RFC2833 DTMF capability for end-point\n");
   }
   else{
      call->dtmfmode |= OO_CAP_DTMF_RFC2833;
      OOTRACEINFO3("Enabled RFC2833 DTMF capability for (%s, %s) \n",
                   call->callType, call->callToken);
   }

   /*Dynamic RTP payload type range is from 96 - 127 */
   if(dynamicRTPPayloadType >= 96 && dynamicRTPPayloadType <= 127)
      giDynamicRTPPayloadType = dynamicRTPPayloadType;

   return OO_OK;
}



int ooCapabilityDisableDTMFRFC2833(OOH323CallData *call)
{
   if(!call){
      gH323ep.dtmfmode ^= OO_CAP_DTMF_RFC2833;
      OOTRACEINFO1("Disabled RFC2833 DTMF capability for end-point\n");
   }
   else{
      call->dtmfmode ^= OO_CAP_DTMF_RFC2833;
      OOTRACEINFO3("Disabled RFC2833 DTMF capability for (%s, %s)\n",
                    call->callType, call->callToken);
   }

   return OO_OK;
}

int ooCapabilityEnableDTMFH245Alphanumeric(OOH323CallData *call)
{
   if(!call){
      gH323ep.dtmfmode |= OO_CAP_DTMF_H245_alphanumeric;
      OOTRACEINFO1("Dtmf mode set to H.245(alphanumeric) for endpoint\n");
   }
   else {
      call->dtmfmode |= OO_CAP_DTMF_H245_alphanumeric;
      OOTRACEINFO3("Dtmf mode set to H.245(alphanumeric) for (%s, %s)\n",
                    call->callType, call->callToken);
   }
   return OO_OK;
}

int ooCapabilityDisableDTMFH245Alphanumeric(OOH323CallData *call)
{
   if(!call){
      gH323ep.dtmfmode ^= OO_CAP_DTMF_H245_alphanumeric;
      OOTRACEINFO1("Dtmf mode H.245(alphanumeric) disabled for endpoint\n");
   }
   else {
      call->dtmfmode ^= OO_CAP_DTMF_H245_alphanumeric;
      OOTRACEINFO3("Dtmf mode H.245(alphanumeric) disabled for (%s, %s)\n",
                    call->callType, call->callToken);
   }
   return OO_OK;
}

int ooCapabilityEnableDTMFH245Signal(OOH323CallData *call)
{
   if(!call){
      gH323ep.dtmfmode |= OO_CAP_DTMF_H245_signal;
      OOTRACEINFO1("Dtmf mode set to H.245(signal) for endpoint\n");
   }
   else {
      call->dtmfmode |= OO_CAP_DTMF_H245_signal;
      OOTRACEINFO3("Dtmf mode set to H.245(signal) for (%s, %s)\n",
                    call->callType, call->callToken);
   }
   return OO_OK;
}

int ooCapabilityDisableDTMFH245Signal(OOH323CallData *call)
{
   if(!call){
      gH323ep.dtmfmode ^= OO_CAP_DTMF_H245_signal;
      OOTRACEINFO1("Dtmf mode H.245(signal) disabled for endpoint\n");
   }
   else {
      call->dtmfmode ^= OO_CAP_DTMF_H245_signal;
      OOTRACEINFO3("Dtmf mode H.245(signal) disabled for (%s, %s)\n",
                    call->callType, call->callToken);
   }
   return OO_OK;
}

int ooCapabilityEnableDTMFQ931Keypad(struct OOH323CallData *call)
{
   if(!call){
      gH323ep.dtmfmode |= OO_CAP_DTMF_Q931;
      OOTRACEINFO1("Dtmf mode set to Q.931(keypad) for the endpoint\n");
   }
   else {
      call->dtmfmode |= OO_CAP_DTMF_Q931;
      OOTRACEINFO3("Dtmf mode set to Q.931(keypad) for the call (%s, %s)\n",
                    call->callType, call->callToken);
   }
   return OO_OK;
}

int ooCapabilityDisableDTMFQ931Keypad(struct OOH323CallData *call)
{
   if(!call){
      gH323ep.dtmfmode ^= OO_CAP_DTMF_Q931;
      OOTRACEINFO1("Dtmf mode Q.931(keypad) disabled for the endpoint\n");
   }
   else {
      call->dtmfmode ^= OO_CAP_DTMF_Q931;
      OOTRACEINFO3("Dtmf mode Q.931(keypad) disabled for the call (%s, %s)\n",
                    call->callType, call->callToken);
   }
   return OO_OK;
}

int ooCapabilityAddH263VideoCapability(ooCallData *call,
                              unsigned sqcifMPI, unsigned qcifMPI,
                              unsigned cifMPI, unsigned cif4MPI,
                              unsigned cif16MPI, unsigned maxBitRate, int dir,
                              cb_StartReceiveChannel startReceiveChannel,
                              cb_StartTransmitChannel startTransmitChannel,
                              cb_StopReceiveChannel stopReceiveChannel,
                              cb_StopTransmitChannel stopTransmitChannel,
                              OOBOOL remote)
{
   int ret = OO_OK;
   if(sqcifMPI>0)
   {
      ret = ooCapabilityAddH263VideoCapability_helper(call, sqcifMPI, 0,
                                 0, 0, 0, maxBitRate, dir, startReceiveChannel,
                                 startTransmitChannel, stopReceiveChannel,
                                 stopTransmitChannel, remote);
      if(ret != OO_OK)
      {
         OOTRACEERR1("Error: Failed to add H263 sqcifMPI capability\n");
         return OO_FAILED;
      }
   }
   if(qcifMPI>0)
   {
      ret = ooCapabilityAddH263VideoCapability_helper(call, 0, qcifMPI, 0,
                                 0, 0, maxBitRate, dir, startReceiveChannel,
                                 startTransmitChannel, stopReceiveChannel,
                                 stopTransmitChannel, remote);
      if(ret != OO_OK)
      {
         OOTRACEERR1("Error: Failed to add H263 qcifMPI capability\n");
         return OO_FAILED;
      }
   }
   if(cifMPI>0)
   {
      ret = ooCapabilityAddH263VideoCapability_helper(call, 0, 0, cifMPI,
                                 0, 0, maxBitRate, dir, startReceiveChannel,
                                 startTransmitChannel, stopReceiveChannel,
                                 stopTransmitChannel, remote);
      if(ret != OO_OK)
      {
         OOTRACEERR1("Error: Failed to add H263 cifMPI capability\n");
         return OO_FAILED;
      }
   }
   if(cif4MPI>0)
   {
      ret = ooCapabilityAddH263VideoCapability_helper(call, 0, 0, 0,
                                 cif4MPI, 0, maxBitRate, dir,
                                 startReceiveChannel,
                                 startTransmitChannel, stopReceiveChannel,
                                 stopTransmitChannel, remote);
      if(ret != OO_OK)
      {
         OOTRACEERR1("Error: Failed to add H263 cif4MPI capability\n");
         return OO_FAILED;
      }
   }
   if(cif16MPI>0)
   {
      ret = ooCapabilityAddH263VideoCapability_helper(call, dir, 0, 0, 0, 0,
                                 cif16MPI, maxBitRate, startReceiveChannel,
                                 startTransmitChannel, stopReceiveChannel,
                                 stopTransmitChannel, remote);
      if(ret != OO_OK)
      {
         OOTRACEERR1("Error: Failed to add H263 cif16MPI capability\n");
         return OO_FAILED;
      }
   }
   return OO_OK;

}

int ooCapabilityAddH263VideoCapability_helper(ooCallData *call,
                              unsigned sqcifMPI, unsigned qcifMPI,
                              unsigned cifMPI, unsigned cif4MPI,
                              unsigned cif16MPI, unsigned maxBitRate, int dir,
                              cb_StartReceiveChannel startReceiveChannel,
                              cb_StartTransmitChannel startTransmitChannel,
                              cb_StopReceiveChannel stopReceiveChannel,
                              cb_StopTransmitChannel stopTransmitChannel,
                              OOBOOL remote)
{

   ooH323EpCapability *epCap = NULL, *cur=NULL;
   OOH263CapParams *params=NULL;
   OOCTXT *pctxt=NULL;
   char *pictureType = NULL;
   int cap = OO_H263VIDEO;

   if(!call) pctxt = &gH323ep.ctxt;
   else pctxt = call->pctxt;

   epCap = (ooH323EpCapability*)memAllocZ(pctxt, sizeof(ooH323EpCapability));
   params = (OOH263CapParams*) memAllocZ(pctxt, sizeof(OOH263CapParams));
   if(!epCap || !params)
   {
      OOTRACEERR1("Error:Memory - ooCapabilityAddH263Capability - epCap/params"
                  ".\n");
      return OO_FAILED;
   }

   if(sqcifMPI>0)
   {
      params->MPI = sqcifMPI;
      params->picFormat = OO_PICFORMAT_SQCIF;
      pictureType = "SQCIF";
   }
   if(qcifMPI>0)
   {
      params->MPI = qcifMPI;
      params->picFormat =  OO_PICFORMAT_QCIF;
      pictureType = "QCIF";
   }
   if(cifMPI>0)
   {
      params->MPI = cifMPI;
      params->picFormat = OO_PICFORMAT_CIF;
      pictureType = "CIF";
   }
   if(cif4MPI>0)
   {
      params->MPI = cif4MPI;
      params->picFormat = OO_PICFORMAT_CIF4;
      pictureType = "CIF4";
   }
   if(cif16MPI>0)
   {
      params->MPI = cif16MPI;
      params->picFormat = OO_PICFORMAT_CIF16;
      pictureType = "CIF16";
   }

   params->maxBitRate = maxBitRate;


   if(dir & OORXANDTX)
   {
      epCap->dir = OORX;
      epCap->dir |= OOTX;
   }
   else
      epCap->dir = dir;

   epCap->cap = OO_H263VIDEO;
   epCap->capType = OO_CAP_TYPE_VIDEO;
   epCap->params = (void*)params;
   epCap->startReceiveChannel = startReceiveChannel;
   epCap->startTransmitChannel = startTransmitChannel;
   epCap->stopReceiveChannel = stopReceiveChannel;
   epCap->stopTransmitChannel = stopTransmitChannel;

   epCap->next = NULL;

   if (0 == call)
   {/*Add as local capability */
      OOTRACEDBGC2("Adding endpoint H263 video capability %s.\n", pictureType);
      ooAppendCapToCapList (&gH323ep.myCaps, epCap);
      ooAppendCapToCapPrefs (NULL, cap);
      gH323ep.noOfCaps++;
   }
   else if (remote) {
      /*Add as remote capability */
      ooAppendCapToCapList (&call->remoteCaps, epCap);
   }
   else {
      /*Add as our capability */
      OOTRACEDBGC4("Adding call specific H263 video capability %s. "
                   "(%s, %s)\n", pictureType, call->callType,
                   call->callToken);

      if (0 == call->ourCaps) {
         ooResetCapPrefs (call);
      }
      ooAppendCapToCapList (&call->ourCaps, epCap);
      ooAppendCapToCapPrefs (call, cap);
   }

   return OO_OK;
}

/* Used for g711 ulaw/alaw, g728, g729 and g7231 */
int ooCapabilityAddSimpleCapability
   (OOH323CallData *call, int cap, int txframes,
    int rxframes, OOBOOL silenceSuppression, int dir,
    cb_StartReceiveChannel startReceiveChannel,
    cb_StartTransmitChannel startTransmitChannel,
    cb_StopReceiveChannel stopReceiveChannel,
    cb_StopTransmitChannel stopTransmitChannel,
    OOBOOL remote)
{
   ooH323EpCapability *epCap = NULL, *cur=NULL;
   OOCapParams *params=NULL;
   OOCTXT *pctxt=NULL;
   if(!call) pctxt = &gH323ep.ctxt;
   else pctxt = call->pctxt;

   epCap = (ooH323EpCapability*)memAlloc(pctxt, sizeof(ooH323EpCapability));
   params = (OOCapParams*) memAlloc(pctxt, sizeof(OOCapParams));
   if(!epCap || !params)
   {
      OOTRACEERR1("ERROR: Memory - ooCapabilityAddSimpleCapability - "
                  "epCap/params\n");
      return OO_FAILED;
   }
   OOTRACEDBGA2 ("New H323EpCapability record allocated (%x)\n", epCap);

   params->txframes = txframes;
   params->rxframes = rxframes;
   /* Ignore silence suppression parameter unless cap is g7231 */
   if(cap == OO_G7231)
      params->silenceSuppression = silenceSuppression;
   else
      params->silenceSuppression = FALSE; /* Set to false for g711 and g729*/

   if(dir & OORXANDTX) {
      epCap->dir = OORX;
      epCap->dir |= OOTX;
   }
   else {
      epCap->dir = dir;
   }

   epCap->cap = cap;
   epCap->capType = OO_CAP_TYPE_AUDIO;
   epCap->params = (void*)params;
   epCap->startReceiveChannel = startReceiveChannel;
   epCap->startTransmitChannel = startTransmitChannel;
   epCap->stopReceiveChannel = stopReceiveChannel;
   epCap->stopTransmitChannel = stopTransmitChannel;
   epCap->next = NULL;

   if (0 == call)
   {
      /* Add as local capability */
      OOTRACEDBGC2 ("Adding endpoint capability %s. \n",
                    ooGetCapTypeText(epCap->cap));

      ooAppendCapToCapList (&gH323ep.myCaps, epCap);
      ooAppendCapToCapPrefs (NULL, cap);
      gH323ep.noOfCaps++;
   }
   else if (remote)
   {
      /* Add as remote capability */
      OOTRACEDBGC4 ("Adding remote call-specific capability %s. (%s, %s)\n",
                    ooGetCapTypeText(epCap->cap), call->callType,
                    call->callToken);

      ooAppendCapToCapList (&call->remoteCaps, epCap);
   }
   else {
      /* Add as our capability */
      OOTRACEDBGC4 ("Adding call-specific capability %s. (%s, %s)\n",
                    ooGetCapTypeText(epCap->cap), call->callType,
                    call->callToken);

      if(!call->ourCaps){
         ooResetCapPrefs (call);
      }
      ooAppendCapToCapList (&call->ourCaps, epCap);
      ooAppendCapToCapPrefs (call, cap);
   }

   return OO_OK;
}

int ooCapabilityAddH264VideoCapability(struct OOH323CallData *call,
                                                           unsigned maxBitRate, int dir,
                               cb_StartReceiveChannel startReceiveChannel,
                               cb_StartTransmitChannel startTransmitChannel,
                               cb_StopReceiveChannel stopReceiveChannel,
                               cb_StopTransmitChannel stopTransmitChannel,
                               OOBOOL remote){
   ooH323EpCapability *epCap = NULL, *cur=NULL;
   OOGenericCapParams *params=NULL;
   OOCTXT *pctxt=NULL;
   char *pictureType = NULL;
   int cap = OO_GENERICVIDEO;

   if(!call) pctxt = &gH323ep.ctxt;
   else pctxt = call->pctxt;

   epCap = (ooH323EpCapability*)memAllocZ(pctxt, sizeof(ooH323EpCapability));
   params = (OOGenericCapParams*) memAllocZ(pctxt, sizeof(OOGenericCapParams));
   if(!epCap || !params)
   {
      OOTRACEERR1("Error:Memory - ooCapabilityAddH263Capability - epCap/params"
                  ".\n");
      return OO_FAILED;
   }

   params->maxBitRate = maxBitRate;
   params->type = OO_GENERICVIDEO_H264;

   if(dir & OORXANDTX)
   {
      epCap->dir = OORX;
      epCap->dir |= OOTX;
   }
   else
      epCap->dir = dir;

   epCap->cap = OO_GENERICVIDEO;
   epCap->capType = OO_CAP_TYPE_VIDEO;
   epCap->params = (void*)params;
   epCap->startReceiveChannel = startReceiveChannel;
   epCap->startTransmitChannel = startTransmitChannel;
   epCap->stopReceiveChannel = stopReceiveChannel;
   epCap->stopTransmitChannel = stopTransmitChannel;

   epCap->next = NULL;

   if (0 == call)
   {/*Add as local capability */
      OOTRACEDBGC2("Adding endpoint H264 video capability %s.\n", pictureType);
      ooAppendCapToCapList (&gH323ep.myCaps, epCap);
      ooAppendCapToCapPrefs (NULL, cap);
      gH323ep.noOfCaps++;
   }
   else if (remote) {
      /*Add as remote capability */
      ooAppendCapToCapList (&call->remoteCaps, epCap);
   }
   else {
      /*Add as our capability */
      OOTRACEDBGC4("Adding call specific H264 video capability %s. "
                   "(%s, %s)\n", pictureType, call->callType,
                   call->callToken);

      if (0 == call->ourCaps) {
         ooResetCapPrefs (call);
      }
      ooAppendCapToCapList (&call->ourCaps, epCap);
      ooAppendCapToCapPrefs (call, cap);
   }

   return OO_OK;
}

int ooCapabilityAddGSMCapability(OOH323CallData *call, int cap,
                                unsigned framesPerPkt, OOBOOL comfortNoise,
                                OOBOOL scrambled, int dir,
                                cb_StartReceiveChannel startReceiveChannel,
                                cb_StartTransmitChannel startTransmitChannel,
                                cb_StopReceiveChannel stopReceiveChannel,
                                cb_StopTransmitChannel stopTransmitChannel,
                                OOBOOL remote)
{

   ooH323EpCapability *epCap = NULL, *cur=NULL;
   OOGSMCapParams *params=NULL;
   OOCTXT *pctxt = NULL;

   if(!call) pctxt = &gH323ep.ctxt;
   else pctxt = call->pctxt;

   epCap = (ooH323EpCapability*)memAlloc(pctxt, sizeof(ooH323EpCapability));
   params = (OOGSMCapParams*) memAlloc(pctxt, sizeof(OOGSMCapParams));
   if(!epCap || !params)
   {
      OOTRACEERR1("Error:Memory - ooCapabilityAddGSMCapability - "
                  "epCap/params\n");
      return OO_FAILED;
   }


   params->rxframes = framesPerPkt;
   params->txframes = framesPerPkt;
   params->comfortNoise = comfortNoise;
   params->scrambled = scrambled;
   if(dir & OORXANDTX)
   {
      epCap->dir = OORX;
      epCap->dir |= OOTX;
   }
   else
      epCap->dir = dir;

   epCap->cap = cap;
   epCap->capType = OO_CAP_TYPE_AUDIO;
   epCap->params = (void*)params;
   epCap->startReceiveChannel = startReceiveChannel;
   epCap->startTransmitChannel = startTransmitChannel;
   epCap->stopReceiveChannel = stopReceiveChannel;
   epCap->stopTransmitChannel = stopTransmitChannel;

   epCap->next = NULL;
   /* Add as local capability */
   if(!call)
   {
      if(!gH323ep.myCaps)
         gH323ep.myCaps = epCap;
      else{
         cur = gH323ep.myCaps;
         while(cur->next) cur = cur->next;
         cur->next = epCap;
      }
      ooAppendCapToCapPrefs(NULL, cap);
      gH323ep.noOfCaps++;
   }
   else{
      if(remote)
      {
         /*Add as remote capability */
         if(!call->remoteCaps)
            call->remoteCaps = epCap;
         else{
            cur = call->remoteCaps;
            while(cur->next) cur = cur->next;
            cur->next = epCap;
         }
      }
      else{
         OOTRACEDBGC4("Adding call specific capability %s. (%s, %s)\n",
                     ooGetCapTypeText(epCap->cap), call->callType,
                     call->callToken);
         /*Add as our capability */
         if(!call->ourCaps){
            call->ourCaps = epCap;
            ooResetCapPrefs(call);
         }
         else{
            cur = call->ourCaps;
            while(cur->next) cur = cur->next;
            cur->next = epCap;
         }
         ooAppendCapToCapPrefs(call, cap);
      }
   }

   return OO_OK;
}




struct H245VideoCapability* ooCapabilityCreateVideoCapability
      (ooH323EpCapability *epCap, OOCTXT *pctxt, int dir)
{

   if(!epCap)
   {
     OOTRACEERR1("Error:Invalid capability parameter passed to "
                 "ooCapabilityCreateVideoCapability.\n");
     return NULL;
   }

   if(!(epCap->dir & dir))
   {
      OOTRACEERR1("Error:Failed to create capability due to direction "
                  "mismatch.\n");
      return NULL;
   }

   switch(epCap->cap)
   {
   case OO_H263VIDEO:
     return ooCapabilityCreateH263VideoCapability(epCap, pctxt, dir);

   case OO_NONSTDVIDEO:
   case OO_H261VIDEO:
   case OO_H262VIDEO:
   case OO_IS11172VIDEO:
   case OO_GENERICVIDEO:
            return ooCapabilityCreateGenericVideoCapability(epCap, pctxt, dir);
   case OO_EXTELEMVIDEO:
   default:
      OOTRACEERR2("ERROR: Don't know how to create video capability %s\n",
                  ooGetCapTypeText(epCap->cap));
   }
   return NULL;
}



struct H245AudioCapability* ooCapabilityCreateAudioCapability
      (ooH323EpCapability *epCap, OOCTXT *pctxt, int dir)
{

   if(!epCap)
   {
     OOTRACEERR1("Error:Invalid capability parameter passed to "
                 "ooCapabilityCreateAudioCapability.\n");
     return NULL;
   }

   if(!(epCap->dir & dir))
   {
      OOTRACEERR1("Error:Failed to create capability due to direction "
                  "mismatch.\n");
      return NULL;
   }

   switch(epCap->cap)
   {
   case OO_G711ALAW64K:
   case OO_G711ALAW56K:
   case OO_G711ULAW64K:
   case OO_G711ULAW56K:
   /*case OO_G726:*/
   case OO_G728:
   case OO_G729:
   case OO_G729A:
   case OO_G7231:
     return ooCapabilityCreateSimpleCapability(epCap, pctxt, dir);
   case OO_GSMFULLRATE:
      return ooCapabilityCreateGSMFullRateCapability(epCap, pctxt, dir);
   default:
      OOTRACEERR2("ERROR: Don't know how to create audio capability %d\n",
                  epCap->cap);
   }
   return NULL;
}



void* ooCapabilityCreateDTMFCapability(int cap, OOCTXT *pctxt)
{
   H245AudioTelephonyEventCapability *pATECap=NULL;
   H245UserInputCapability *userInput = NULL;
   char *events=NULL;
   switch(cap)
   {
   case OO_CAP_DTMF_RFC2833:
      pATECap = memAllocTypeZ (pctxt, H245AudioTelephonyEventCapability);
      if(!pATECap)
      {
         OOTRACEERR1
            ("Error:Memory - ooCapabilityCreateDTMFCapability - pATECap\n");
         return NULL;
      }
      pATECap->dynamicRTPPayloadType = giDynamicRTPPayloadType;
      events = (char*)memAlloc(pctxt, 5 /*strlen("0-16")+1*/);
      if(!events)
      {
         OOTRACEERR1
            ("Error:Memory - ooCapabilityCreateDTMFCapability - events\n");
         memFreePtr(pctxt, pATECap);
         return NULL;
      }
      strcpy (events, "0-16");
      pATECap->audioTelephoneEvent = events;
      return pATECap;

   case OO_CAP_DTMF_H245_alphanumeric:
      userInput = memAllocTypeZ (pctxt, H245UserInputCapability);
      if(!userInput)
      {
         OOTRACEERR1("Error:Memory - ooCapabilityCreateDTMFCapability - "
                     "userInput\n");
         return NULL;
      }
      userInput->t = T_H245UserInputCapability_basicString;
      return userInput;

   case OO_CAP_DTMF_H245_signal:
      userInput = memAllocTypeZ (pctxt, H245UserInputCapability);
      if(!userInput)
      {
         OOTRACEERR1("Error:Memory - ooCapabilityCreateDTMFCapability - "
                     "userInput\n");
         return NULL;
      }
      userInput->t = T_H245UserInputCapability_dtmf;
      return userInput;

   default:
     OOTRACEERR1("Error:unknown dtmf capability type\n");
   }

   return NULL;
}



struct H245VideoCapability* ooCapabilityCreateH263VideoCapability
   (ooH323EpCapability *epCap, OOCTXT* pctxt, int dir)
{
   H245VideoCapability *pVideo=NULL;
   OOH263CapParams *params=NULL;
   H245H263VideoCapability *pH263Cap=NULL;

   if(!epCap || !epCap->params)
   {
     OOTRACEERR1("Error:Invalid capability parameters to "
                 "ooCapabilityCreateH263VideoCapability.\n");
     return NULL;
   }
   params =(OOH263CapParams*)epCap->params;

   pVideo = (H245VideoCapability*)memAllocZ(pctxt,
                                                  sizeof(H245VideoCapability));
   pH263Cap = (H245H263VideoCapability*) memAllocZ(pctxt,
                                             sizeof(H245H263VideoCapability));
   if(!pVideo || !pH263Cap)
   {
      OOTRACEERR1("ERROR:Memory - ooCapabilityCreateH263VideoCapability - "
                  "pVideo/pH263Cap\n");
      return NULL;
   }

   pVideo->t = T_H245VideoCapability_h263VideoCapability;
   pVideo->u.h263VideoCapability = pH263Cap;


   if(params->picFormat ==  OO_PICFORMAT_SQCIF) {
      pH263Cap->m.sqcifMPIPresent = TRUE;
      pH263Cap->sqcifMPI = params->MPI;
   }
   else if(params->picFormat == OO_PICFORMAT_QCIF) {
      pH263Cap->m.qcifMPIPresent = TRUE;
      pH263Cap->qcifMPI = params->MPI;
   }
   else if(params->picFormat == OO_PICFORMAT_CIF) {
      pH263Cap->m.cifMPIPresent = TRUE;
      pH263Cap->cifMPI = params->MPI;
   }
   else if(params->picFormat == OO_PICFORMAT_CIF4) {
      pH263Cap->m.cif4MPIPresent  = TRUE;
      pH263Cap->cif4MPI = params->MPI;
   }
   else if(params->picFormat == OO_PICFORMAT_CIF16) {
      pH263Cap->m.cif16MPIPresent = TRUE;
      pH263Cap->cif16MPI = params->MPI;
   }

   pH263Cap->m.errorCompensationPresent = TRUE;
   pH263Cap->maxBitRate = params->maxBitRate;
   pH263Cap->unrestrictedVector = FALSE;
   pH263Cap->arithmeticCoding = FALSE;
   pH263Cap->advancedPrediction = FALSE;
   pH263Cap->pbFrames = FALSE;
   pH263Cap->temporalSpatialTradeOffCapability = FALSE;
   pH263Cap->hrd_B = 0;
   pH263Cap->bppMaxKb = 0;
   pH263Cap->slowSqcifMPI = FALSE;
   pH263Cap->slowQcifMPI = FALSE;
   pH263Cap->slowCifMPI = FALSE;
   pH263Cap->slowCif4MPI = FALSE;
   pH263Cap->slowCif16MPI = FALSE;
   pH263Cap->errorCompensation = FALSE;
   return pVideo;
}


struct H245VideoCapability* ooCapabilityCreateGenericVideoCapability
   (ooH323EpCapability *epCap, OOCTXT* pctxt, int dir)
{
   H245VideoCapability *pVideo=NULL;
   OOGenericCapParams *params=NULL;
   H245GenericCapability *pGenericCap=NULL;

   if(!epCap || !epCap->params)
   {
     OOTRACEERR1("Error:Invalid capability parameters to "
                 "ooCapabilityCreateH263VideoCapability.\n");
     return NULL;
   }
   params =(OOGenericCapParams*)epCap->params;

   pVideo = (H245VideoCapability*)memAllocZ(pctxt,
                                                  sizeof(H245VideoCapability));
   pGenericCap = (H245GenericCapability*) memAllocZ(pctxt,
                                             sizeof(H245GenericCapability));
   if(!pVideo || !pGenericCap)
   {
      OOTRACEERR1("ERROR:Memory - ooCapabilityCreateGenericVideoCapability - "
                  "pVideo/pGenericCap\n");
      return NULL;
   }

   pVideo->t = T_H245VideoCapability_genericVideoCapability;
   pVideo->u.genericVideoCapability = pGenericCap;
   pGenericCap->maxBitRate = params->maxBitRate;
   pGenericCap->capabilityIdentifier.t = 1;
   pGenericCap->capabilityIdentifier.u.standard = memAllocTypeZ (pctxt, ASN1OBJID);
   pGenericCap->capabilityIdentifier.u.standard->numids = 6;
   pGenericCap->capabilityIdentifier.u.standard->subid[0] = 0;
   pGenericCap->capabilityIdentifier.u.standard->subid[1] = 0;
   pGenericCap->capabilityIdentifier.u.standard->subid[2] = 8;
   pGenericCap->capabilityIdentifier.u.standard->subid[3] = 245;
   pGenericCap->capabilityIdentifier.u.standard->subid[4] = 0;
   pGenericCap->capabilityIdentifier.u.standard->subid[5] = 13;
   return pVideo;
}

struct H245AudioCapability* ooCapabilityCreateGSMFullRateCapability
   (ooH323EpCapability *epCap, OOCTXT* pctxt, int dir)
{
   H245AudioCapability *pAudio=NULL;
   H245GSMAudioCapability *pGSMCap=NULL;
   if(!epCap || !epCap->params)
   {
     OOTRACEERR1("Error:Invalid capability parameters to "
                 "ooCapabilityCreateGSMFullRateCapability.\n");
     return NULL;
   }

   pAudio = (H245AudioCapability*)memAlloc(pctxt,
                                                sizeof(H245AudioCapability));
   pGSMCap = (H245GSMAudioCapability*)memAlloc(pctxt,
                                              sizeof(H245GSMAudioCapability));
   if(!pAudio || !pGSMCap)
   {
      OOTRACEERR1("ERROR:Memory - ooCapabilityCreateGSMFullRateCapability - "
                  "pAudio/pGSMCap\n");
      return NULL;
   }

   pAudio->t = T_H245AudioCapability_gsmFullRate;
   pAudio->u.gsmFullRate = pGSMCap;
   if(dir & OORX)
      pGSMCap->audioUnitSize = ((OOGSMCapParams*)epCap->params)->rxframes*OO_GSMFRAMESIZE;
   else
      pGSMCap->audioUnitSize = ((OOGSMCapParams*)epCap->params)->txframes*OO_GSMFRAMESIZE;

   pGSMCap->comfortNoise = ((OOGSMCapParams*)epCap->params)->comfortNoise;
   pGSMCap->scrambled = ((OOGSMCapParams*)epCap->params)->scrambled;

   return pAudio;
}

/* This is used for g711 ulaw/alaw, g728, g729, g729A, g7231*/
struct H245AudioCapability* ooCapabilityCreateSimpleCapability
   (ooH323EpCapability *epCap, OOCTXT* pctxt, int dir)
{
   H245AudioCapability *pAudio=NULL;
   OOCapParams *params;
   if(!epCap || !epCap->params)
   {
     OOTRACEERR1("Error:Invalid capability parameters to "
                 "ooCapabilityCreateSimpleCapability.\n");
     return NULL;
   }
   params =(OOCapParams*)epCap->params;
   pAudio = (H245AudioCapability*)memAlloc(pctxt,
                                                sizeof(H245AudioCapability));
   if(!pAudio)
   {
      OOTRACEERR1("ERROR:Memory - ooCapabilityCreateSimpleCapability - pAudio\n");
      return NULL;
   }


   switch(epCap->cap)
   {
   case OO_G711ALAW64K:
      pAudio->t = T_H245AudioCapability_g711Alaw64k;
      if(dir & OORX)
         pAudio->u.g711Alaw64k = params->rxframes;
      else
         pAudio->u.g711Alaw64k = params->txframes;
      return pAudio;
   case OO_G711ALAW56K:
      pAudio->t = T_H245AudioCapability_g711Alaw56k;
      if(dir & OORX)
         pAudio->u.g711Alaw56k = params->rxframes;
      else
         pAudio->u.g711Alaw56k = params->txframes;
      return pAudio;
   case OO_G711ULAW64K:
      pAudio->t = T_H245AudioCapability_g711Ulaw64k;
      if(dir & OORX)
         pAudio->u.g711Ulaw64k = params->rxframes;
      else
         pAudio->u.g711Ulaw64k = params->txframes;
      return pAudio;
   case OO_G711ULAW56K:
      pAudio->t = T_H245AudioCapability_g711Ulaw56k;
      if(dir & OORX)
         pAudio->u.g711Ulaw56k = params->rxframes;
      else
         pAudio->u.g711Ulaw64k = params->txframes;
      return pAudio;
   /*case OO_G726:
      pAudio->t = T_H245AudioCapability_g726;
      if(dir & OORX)
         pAudio->u.g726 = params->rxframes;
      else
         pAudio->u.g726 = params->txframes;
      return pAudio;*/
   case OO_G728:
      pAudio->t = T_H245AudioCapability_g728;
      if(dir & OORX)
         pAudio->u.g728 = params->rxframes;
      else
         pAudio->u.g728 = params->txframes;
      return pAudio;
   case OO_G729:
      pAudio->t = T_H245AudioCapability_g729;
      if(dir & OORX)
         pAudio->u.g729 = params->rxframes;
      else
         pAudio->u.g729 = params->txframes;
      return pAudio;
   case OO_G729A:
      pAudio->t = T_H245AudioCapability_g729AnnexA;
      if(dir & OORX)
         pAudio->u.g729AnnexA = params->rxframes;
      else
         pAudio->u.g729AnnexA = params->txframes;
      return pAudio;
   case OO_G7231:
      pAudio->t = T_H245AudioCapability_g7231;
      pAudio->u.g7231 = (H245AudioCapability_g7231*)memAlloc(pctxt,
                                           sizeof(H245AudioCapability_g7231));
      if(!pAudio->u.g7231)
      {
         OOTRACEERR1("Error:Memory - ooCapabilityCreateSimpleCapability - g7231\n");
         memFreePtr(pctxt, pAudio);
         return NULL;
      }
      pAudio->u.g7231->silenceSuppression = params->silenceSuppression;
      if(dir & OORX)
         pAudio->u.g7231->maxAl_sduAudioFrames = params->rxframes;
      else
         pAudio->u.g7231->maxAl_sduAudioFrames = params->txframes;
      return pAudio;

   default:
      OOTRACEERR2("ERROR: Don't know how to create audio capability %d\n",
                   epCap->cap);
   }
   return NULL;
}

/* Used for g711 ulaw/alaw, g728, g729, g729a, g7231 */
ASN1BOOL ooCapabilityCheckCompatibility_Simple
   (OOH323CallData *call, ooH323EpCapability* epCap,
    H245AudioCapability* audioCap, int dir)
{
   int noofframes=0, cap;

   OOTRACEDBGC2("Comparing channel with codec type: %d\n", audioCap->t);

   switch(audioCap->t)
   {
   case T_H245AudioCapability_g711Ulaw56k:
      cap = OO_G711ULAW56K;
      noofframes = audioCap->u.g711Ulaw56k;
      break;
   case T_H245AudioCapability_g711Ulaw64k:
      cap = OO_G711ULAW64K;
      noofframes = audioCap->u.g711Ulaw64k;
      break;
   case T_H245AudioCapability_g711Alaw64k:
      cap = OO_G711ALAW64K;
      noofframes = audioCap->u.g711Alaw64k;
      break;
   case T_H245AudioCapability_g711Alaw56k:
      cap = OO_G711ALAW56K;
      noofframes = audioCap->u.g711Alaw56k;
      break;
   /*case T_H245AudioCapability_g726:
      cap = OO_G726;
      noofframes = audioCap->u.g726;
      break;*/
   case T_H245AudioCapability_g728:
      cap = OO_G728;
      noofframes = audioCap->u.g728;
      break;
   case T_H245AudioCapability_g729:
      cap = OO_G729;
      noofframes = audioCap->u.g729;
      break;
   case T_H245AudioCapability_g729AnnexA:
      cap = OO_G729A;
      noofframes = audioCap->u.g729AnnexA;
      break;
   case T_H245AudioCapability_g7231:
     cap = OO_G7231;
     noofframes = audioCap->u.g7231->maxAl_sduAudioFrames;
     break;
   default:
      return FALSE;
   }

   OOTRACEDBGC3("Comparing codecs: current=%d, requested=%d\n",
      epCap->cap, cap);
   if(cap != epCap->cap) { return FALSE; }

   /* Can we receive this capability */
   if(dir & OORX)
   {
      OOTRACEDBGC3("Comparing RX frame rate: channel's=%d, requested=%d\n",
         ((OOCapParams*)epCap->params)->rxframes, noofframes);
      if(((OOCapParams*)epCap->params)->rxframes >= noofframes) {
         return TRUE;
      }
      //else {
      //  not supported, as already told other ep our max. receive rate
      //  our ep can't receive more rate than it
      //  return FALSE;
      //}
   }

   /* Can we transmit compatible stream */
   if(dir & OOTX)
   {
      OOTRACEDBGC3("Comparing TX frame rate: channel's=%d, requested=%d\n",
         ((OOCapParams*)epCap->params)->txframes, noofframes);
      if(((OOCapParams*)epCap->params)->txframes <= noofframes) {
         return TRUE;
      }
      //else {
      //   TODO: reduce our ep transmission rate, as peer EP has low receive
      //   cap, than return TRUE
      //}
   }
   return FALSE;

}


OOBOOL ooCapabilityCheckCompatibility_GSM
   (OOH323CallData *call, ooH323EpCapability* epCap,
    H245AudioCapability* audioCap, int dir)
{
   unsigned noofframes=0, cap;
   switch(audioCap->t)
   {
   case T_H245AudioCapability_gsmFullRate:
      cap = OO_GSMFULLRATE;
      noofframes = (audioCap->u.gsmFullRate->audioUnitSize)/OO_GSMFRAMESIZE;
      break;
   case T_H245AudioCapability_gsmHalfRate:
      cap = OO_GSMHALFRATE;
      noofframes = (audioCap->u.gsmHalfRate->audioUnitSize)/OO_GSMFRAMESIZE;
      break;
   case T_H245AudioCapability_gsmEnhancedFullRate:
      cap = OO_GSMENHANCEDFULLRATE;
      noofframes = (audioCap->u.gsmEnhancedFullRate->audioUnitSize)/OO_GSMFRAMESIZE;
      break;
   default:
      return FALSE;
   }

   /* can we receive this capability */
   if(dir & OORX)
   {
      if(((OOGSMCapParams*)epCap->params)->rxframes >= noofframes)
         return TRUE;
   }

   /* Make sure we transmit compatible stream */
   if(dir & OOTX)
   {
      if(((OOGSMCapParams*)epCap->params)->txframes > noofframes){
         OOTRACEDBGA5("Reducing txframes for GSM from %d to %d to match "
                      "receive capability of remote end.(%s, %s)\n",
                     ((OOGSMCapParams*)epCap->params)->txframes, noofframes,
                     call->callType, call->callToken);
         ((OOGSMCapParams*)epCap->params)->txframes = noofframes;
      }
      return TRUE;
   }
   return FALSE;

}


OOBOOL ooCapabilityCheckCompatibility_H263Video
   (struct OOH323CallData *call, ooH323EpCapability *epCap,
    H245VideoCapability *pVideoCap, int dir)
{
   H245H263VideoCapability *pH263Cap = NULL;

   OOH263CapParams *params = epCap->params;
   if(!pVideoCap->u.h263VideoCapability)
   {
      OOTRACEERR3("Error:No H263 video capability present in video capability"
                 "structure. (%s, %s)\n", call->callType, call->callToken);
      return FALSE;
   }
   pH263Cap = pVideoCap->u.h263VideoCapability;

   /* can we receive/transmit this capability */
   if(OORX & dir)
   {
      if(pH263Cap->m.sqcifMPIPresent)
      {
         if(params->picFormat != OO_PICFORMAT_SQCIF)
         {
            return FALSE;
         }
         else{
            if(pH263Cap->sqcifMPI >= params->MPI)
               return TRUE;
            else
               return FALSE;
         }
      }
      if(pH263Cap->m.qcifMPIPresent)
      {
         if(params->picFormat != OO_PICFORMAT_QCIF)
         {
            return FALSE;
         }
         else{
            if(pH263Cap->qcifMPI >= params->MPI)
               return TRUE;
            else
               return FALSE;
         }
      }
      if(pH263Cap->m.cifMPIPresent)
      {
         if(params->picFormat != OO_PICFORMAT_CIF)
         {
            return FALSE;
         }
         else{
            if(pH263Cap->cifMPI >= params->MPI)
               return TRUE;
            else
               return FALSE;
         }
      }
      if(pH263Cap->m.cif4MPIPresent)
      {
         if(params->picFormat != OO_PICFORMAT_CIF4)
         {
            return FALSE;
         }
         else{
            if(pH263Cap->cif4MPI >= params->MPI)
               return TRUE;
            else
               return FALSE;
         }
      }
      if(pH263Cap->m.cif16MPIPresent)
      {
         if(params->picFormat != OO_PICFORMAT_CIF16)
         {
            return FALSE;
         }
         else{
            if(pH263Cap->cif16MPI >= params->MPI)
               return TRUE;
            else
               return FALSE;
         }
      }
   }

   /* Can we transmit */
   if(OOTX & dir)
   {
       if(pH263Cap->m.sqcifMPIPresent)
      {
         if(params->picFormat != OO_PICFORMAT_SQCIF)
         {
            return FALSE;
         }
         else{
            if(pH263Cap->sqcifMPI <= params->MPI)
               return TRUE;
            else
               return FALSE;
         }
      }
      if(pH263Cap->m.qcifMPIPresent)
      {
         if(params->picFormat != OO_PICFORMAT_QCIF)
         {
            return FALSE;
         }
         else{
            if(pH263Cap->qcifMPI <= params->MPI)
               return TRUE;
            else
               return FALSE;
         }
      }
      if(pH263Cap->m.cifMPIPresent)
      {
         if(params->picFormat != OO_PICFORMAT_CIF)
         {
            return FALSE;
         }
         else{
            if(pH263Cap->cifMPI <= params->MPI)
               return TRUE;
            else
               return FALSE;
         }
      }
      if(pH263Cap->m.cif4MPIPresent)
      {
         if(params->picFormat != OO_PICFORMAT_CIF4)
         {
            return FALSE;
         }
         else{
            if(pH263Cap->cif4MPI <= params->MPI)
               return TRUE;
            else
               return FALSE;
         }
      }
      if(pH263Cap->m.cif16MPIPresent)
      {
         if(params->picFormat != OO_PICFORMAT_CIF16)
         {
            return FALSE;
         }
         else{
            if(pH263Cap->cif16MPI <= params->MPI)
               return TRUE;
            else
               return FALSE;
         }
      }
   }

   return FALSE;

}


OOBOOL ooCapabilityCheckCompatibility_Audio
   (OOH323CallData *call, ooH323EpCapability* epCap,
    H245AudioCapability* audioCap, int dir)
{

   switch(audioCap->t)
   {
   case T_H245AudioCapability_g711Ulaw56k:
   case T_H245AudioCapability_g711Ulaw64k:
   case T_H245AudioCapability_g711Alaw64k:
   case T_H245AudioCapability_g711Alaw56k:
   /*case T_H245AudioCapability_g726:*/
   case T_H245AudioCapability_g728:
   case T_H245AudioCapability_g729:
   case T_H245AudioCapability_g729AnnexA:
   case T_H245AudioCapability_g7231:
      return ooCapabilityCheckCompatibility_Simple(call, epCap, audioCap, dir);
   case T_H245AudioCapability_gsmFullRate:
      return ooCapabilityCheckCompatibility_GSM(call, epCap, audioCap, dir);
   default:
      return FALSE;
   }

   return FALSE;
}

OOBOOL ooCapabilityCheckCompatibility_Video
   (OOH323CallData *call, ooH323EpCapability* epCap,
    H245VideoCapability* videoCap, int dir)
{
   switch(videoCap->t)
   {
   case T_H245VideoCapability_h263VideoCapability:
      return ooCapabilityCheckCompatibility_H263Video(call, epCap,
                                                              videoCap, dir);
   default:
     OOTRACEDBGC3("ooCapabilityCheckCompatibility_Video - Unsupported video "
                  "capability. (%s, $s)\n", call->callType, call->callToken);
   }
   return FALSE;
}
/*
   Note: In faststart if we sent transmit rate (x>y) and remote
         can receive only y, then we can't reduce our transmit rate
*/
OOBOOL ooCapabilityCheckCompatibility
   (struct OOH323CallData *call, ooH323EpCapability* epCap,
    H245DataType* dataType, int dir)
{
   switch(dataType->t)
   {
   case T_H245DataType_audioData:
      if(epCap->capType == OO_CAP_TYPE_AUDIO)
         return ooCapabilityCheckCompatibility_Audio(call, epCap,
                                                   dataType->u.audioData, dir);
      break;
   case T_H245DataType_videoData:
      if(epCap->capType == OO_CAP_TYPE_VIDEO)
         return ooCapabilityCheckCompatibility_Video(call, epCap,
                                                   dataType->u.videoData, dir);
      break;
   case T_H245DataType_data:
   default:
      OOTRACEDBGC3("ooCapabilityCheckCompatibility - Unsupported  "
                  "capability. (%s, $s)\n", call->callType, call->callToken);
   }

   return FALSE;
}

#if 0
/**
  TODO: If txCap is local and number of txframes is greater than remote can
  receive, we should automatically decrease it. And logical channel cap should
  be the one where it should be decreased. The start logical channel will
  indicate the application that it is supposed to tx and a reduced rate.
 */
ASN1BOOL ooCheckCompatibility
   (OOH323CallData *call, ooH323EpCapability *txCap, ooH323EpCapability *rxCap)
{

   if(txCap->cap != rxCap->cap) return FALSE;

   if(!(txCap->dir & OOTX)) return FALSE;

   if(!(rxCap->dir & OORX)) return FALSE;

   switch(txCap->cap)
   {
   case OO_G711ALAW64K:
   case OO_G711ALAW56K:
   case OO_G711ULAW64K:
   case OO_G711ULAW56K:
   /*case OO_G726:*/
   case OO_G728:
   case OO_G729:
   case OO_G729A:
   case OO_G7231:
     if(((OOCapParams*)txCap->params)->txframes <=
                                ((OOCapParams*)rxCap->params)->rxframes)
       return TRUE;
     else{
       OOTRACEDBGA4("Simple caps %s are not compatible.(%s, %s)\n",
                    ooGetCapTypeText(txCap->cap), call->callType,
                    call->callToken);
       return FALSE;
     }
   case OO_GSMFULLRATE:
   case OO_GSMHALFRATE:
   case OO_GSMENHANCEDFULLRATE:
     if(((OOGSMCapParams*)txCap->params)->txframes <=
                                ((OOGSMCapParams*)rxCap->params)->rxframes)
       return TRUE;
     else{
       OOTRACEDBGA3("GSM caps are not compatible. (%s, %s)\n", call->callType,
                     call->callToken);
       return FALSE;
     }
   default:
     OOTRACEWARN3("WARN: Unsupported capabilities being compared. (%s, %s)\n",
                   call->callType, call->callToken);
   }
   return FALSE;

}

#endif

ooH323EpCapability* ooIsAudioDataTypeGSMSupported
   (OOH323CallData *call, H245AudioCapability* audioCap, int dir)
{
   unsigned framesPerPkt=0;
   int cap=0;
   ooH323EpCapability *cur = NULL, *epCap=NULL;
   OOGSMCapParams *params = NULL;

   switch(audioCap->t)
   {
   case T_H245AudioCapability_gsmFullRate:
      framesPerPkt = (audioCap->u.gsmFullRate->audioUnitSize)/OO_GSMFRAMESIZE;
      cap = OO_GSMFULLRATE;
      break;
   case T_H245AudioCapability_gsmHalfRate:
      framesPerPkt = (audioCap->u.gsmHalfRate->audioUnitSize)/OO_GSMFRAMESIZE;
      cap = OO_GSMHALFRATE;
      break;
   case T_H245AudioCapability_gsmEnhancedFullRate:
      framesPerPkt = (audioCap->u.gsmEnhancedFullRate->audioUnitSize)/OO_GSMFRAMESIZE;
      cap = OO_GSMENHANCEDFULLRATE;
      break;
   default:
      OOTRACEERR3("Error:Invalid GSM capability type.(%s, %s)\n",
                                           call->callType, call->callToken);
     return NULL;
   }

   OOTRACEDBGC4("Determined audio data type to be of type %d. Searching"
                " for matching capability.(%s, %s)\n", cap, call->callType,
                call->callToken);

   /* If we have call specific caps then we use them, otherwise we use
      general endpoint caps*/
   if(call->ourCaps)
      cur = call->ourCaps;
   else
      cur = gH323ep.myCaps;

   while(cur)
   {
      OOTRACEDBGC4("Local cap being compared %d. (%s, %s)\n", cur->cap,
                     call->callType, call->callToken);

      if(cur->cap == cap && (cur->dir & dir))
         break;
      cur = cur->next;
   }

   if(!cur) return NULL;

   OOTRACEDBGC4("Found matching audio capability type %d. Comparing"
                " other parameters. (%s, %s)\n", cap, call->callType,
                call->callToken);

   /* can we receive this capability */
   if(dir & OORX)
   {
      if(((OOGSMCapParams*)cur->params)->rxframes < framesPerPkt)
         return NULL;
      else{
         epCap = (ooH323EpCapability*)memAlloc(call->pctxt,
                                                 sizeof(ooH323EpCapability));
         params =(OOGSMCapParams*)memAlloc(call->pctxt,sizeof(OOGSMCapParams));
         if(!epCap || !params)
         {
            OOTRACEERR3("Error:Memory - ooIsAudioDataTypeGSMSupported - "
                        "epCap/params (%s, %s)\n", call->callType,
                        call->callToken);
            return NULL;
         }
         epCap->params = params;
         epCap->cap = cur->cap;
         epCap->dir = cur->dir;
         epCap->capType = cur->capType;
         epCap->startReceiveChannel = cur->startReceiveChannel;
         epCap->startTransmitChannel= cur->startTransmitChannel;
         epCap->stopReceiveChannel = cur->stopReceiveChannel;
         epCap->stopTransmitChannel = cur->stopTransmitChannel;
         epCap->next = NULL;
         memcpy(epCap->params, cur->params, sizeof(OOGSMCapParams));
         return epCap;
      }
   }

   /* Can we transmit compatible stream */
   if(dir & OOTX)
   {
      epCap = (ooH323EpCapability*)memAlloc(call->pctxt,
                                                sizeof(ooH323EpCapability));
      params =(OOGSMCapParams*)memAlloc(call->pctxt,sizeof(OOGSMCapParams));
      if(!epCap || !params)
      {
         OOTRACEERR3("Error:Memory - ooIsAudioDataTypeGSMSupported - "
                     "epCap/params (%s, %s)\n", call->callType,
                     call->callToken);
         return NULL;
      }
      epCap->params = params;
      epCap->cap = cur->cap;
      epCap->dir = cur->dir;
      epCap->capType = cur->capType;
      epCap->startReceiveChannel = cur->startReceiveChannel;
      epCap->startTransmitChannel= cur->startTransmitChannel;
      epCap->stopReceiveChannel = cur->stopReceiveChannel;
      epCap->stopTransmitChannel = cur->stopTransmitChannel;
      epCap->next = NULL;
      memcpy(epCap->params, cur->params, sizeof(OOGSMCapParams));
      if(params->txframes > framesPerPkt)
      {
         OOTRACEINFO5("Reducing framesPerPkt for transmission of GSM "
                      "capability from %d to %d to match receive capability of"
                      " remote endpoint.(%s, %s)\n", params->txframes,
                      framesPerPkt, call->callType, call->callToken);
         params->txframes = framesPerPkt;
      }

      return epCap;

   }
   return NULL;

}

/* used for g711 ulaw/alaw, g728, g729, g729a, g7231 */
ooH323EpCapability* ooIsAudioDataTypeSimpleSupported
   (OOH323CallData *call, H245AudioCapability* audioCap, int dir)
{
   int cap, framesPerPkt=0;
   ooH323EpCapability *cur=NULL, *epCap=NULL;
   OOCapParams * params= NULL;

   /* Find similar capability */
   switch(audioCap->t)
   {
      case T_H245AudioCapability_g711Alaw64k:
         framesPerPkt = audioCap->u.g711Alaw64k;
         cap = OO_G711ALAW64K;
         break;

      case T_H245AudioCapability_g711Alaw56k:
         framesPerPkt = audioCap->u.g711Alaw56k;
         cap = OO_G711ALAW56K;
         break;

      case T_H245AudioCapability_g711Ulaw56k:
         framesPerPkt = audioCap->u.g711Ulaw56k;
         cap = OO_G711ULAW56K;
         break;

      case T_H245AudioCapability_g711Ulaw64k:
         framesPerPkt = audioCap->u.g711Ulaw64k;
         cap = OO_G711ULAW64K;
         break;

/*      case T_H245AudioCapability_g726:
         framesPerPkt = audioCap->u.g726;
         cap = OO_G726;
         break;
*/
      case T_H245AudioCapability_g728:
         framesPerPkt = audioCap->u.g728;
         cap = OO_G728;
         break;

      case T_H245AudioCapability_g729:
         framesPerPkt = audioCap->u.g729;
         cap = OO_G729;
         break;

      case T_H245AudioCapability_g729AnnexA:
         framesPerPkt = audioCap->u.g729AnnexA;
         cap = OO_G729A;
         break;

      case T_H245AudioCapability_g7231:
         framesPerPkt = audioCap->u.g7231->maxAl_sduAudioFrames;
         cap = OO_G7231;
         break;

      default:
         return NULL;
   }

   OOTRACEDBGC4("Determined Simple audio data type to be of type %s. Searching"
                " for matching capability.(%s, %s)\n",
                ooGetCapTypeText(cap), call->callType, call->callToken);

   /* If we have call specific caps, we use them; otherwise use general
      endpoint caps
   */
   if(call->ourCaps)
     cur = call->ourCaps;
   else
     cur = gH323ep.myCaps;

   while(cur)
   {
      OOTRACEDBGC4("Local cap being compared %s. (%s, %s)\n",
         ooGetCapTypeText(cur->cap),call->callType, call->callToken);

      if(cur->cap == cap && (cur->dir & dir))
         break;
      cur = cur->next;
   }

   if(!cur) return NULL;

   OOTRACEDBGC4("Found matching simple audio capability type %s. Comparing"
                " other parameters. (%s, %s)\n", ooGetCapTypeText(cap),
                call->callType, call->callToken);

   /* can we receive this capability */
   if(dir & OORX)
   {
     if(((OOCapParams*)cur->params)->rxframes < framesPerPkt)
         return NULL;
     else{
        OOTRACEDBGC4("We can receive Simple capability %s. (%s, %s)\n",
                      ooGetCapTypeText(cur->cap), call->callType,
                      call->callToken);
        epCap = (ooH323EpCapability*)memAlloc(call->pctxt,
                                                 sizeof(ooH323EpCapability));
        params=(OOCapParams*)memAlloc(call->pctxt,sizeof(OOCapParams));
        if(!epCap || !params)
        {
           OOTRACEERR3("Error:Memory - ooIsAudioDataTypeSimpleSupported - "
                       "epCap/params (%s, %s)\n", call->callType,
                       call->callToken);
           return NULL;
        }
        epCap->params = params;
        epCap->cap = cur->cap;
        epCap->dir = cur->dir;
        epCap->capType = cur->capType;
        epCap->startReceiveChannel = cur->startReceiveChannel;
        epCap->startTransmitChannel= cur->startTransmitChannel;
        epCap->stopReceiveChannel = cur->stopReceiveChannel;
        epCap->stopTransmitChannel = cur->stopTransmitChannel;
        epCap->next = NULL;
        memcpy(epCap->params, cur->params, sizeof(OOCapParams));
        OOTRACEDBGC4("Returning copy of matched receive capability %s. "
                     "(%s, %s)\n",
                     ooGetCapTypeText(cur->cap), call->callType,
                     call->callToken);
        return epCap;
     }
   }

   /* Can we transmit compatible stream */
   if(dir & OOTX)
   {
      OOTRACEDBGC4("We can transmit Simple capability %s. (%s, %s)\n",
                   ooGetCapTypeText(cur->cap), call->callType,
                   call->callToken);
      epCap = (ooH323EpCapability*)memAlloc(call->pctxt,
                                                sizeof(ooH323EpCapability));
      params =(OOCapParams*)memAlloc(call->pctxt,sizeof(OOCapParams));
      if(!epCap || !params)
      {
         OOTRACEERR3("Error:Memory - ooIsAudioDataTypeSimpleSupported - "
                     "epCap/params (%s, %s)\n", call->callType,
                     call->callToken);
         return NULL;
      }
      epCap->params = params;
      epCap->cap = cur->cap;
      epCap->dir = cur->dir;
      epCap->capType = cur->capType;
      epCap->startReceiveChannel = cur->startReceiveChannel;
      epCap->startTransmitChannel= cur->startTransmitChannel;
      epCap->stopReceiveChannel = cur->stopReceiveChannel;
      epCap->stopTransmitChannel = cur->stopTransmitChannel;
      epCap->next = NULL;
      memcpy(epCap->params, cur->params, sizeof(OOCapParams));
      if(params->txframes > framesPerPkt)
      {
         OOTRACEINFO5("Reducing framesPerPkt for transmission of Simple "
                      "capability from %d to %d to match receive capability of"
                      " remote endpoint.(%s, %s)\n", params->txframes,
                      framesPerPkt, call->callType, call->callToken);
         params->txframes = framesPerPkt;
      }
      OOTRACEDBGC4("Returning copy of matched transmit capability %s."
                   "(%s, %s)\n",
                   ooGetCapTypeText(cur->cap), call->callType,
                   call->callToken);
      return epCap;
   }
   return NULL;
}



ooH323EpCapability* ooIsAudioDataTypeSupported
   (OOH323CallData *call, H245AudioCapability* audioCap, int dir)
{
   /* Find similar capability */
   switch(audioCap->t)
   {
      case T_H245AudioCapability_g711Alaw64k:
      case T_H245AudioCapability_g711Alaw56k:
      case T_H245AudioCapability_g711Ulaw56k:
      case T_H245AudioCapability_g711Ulaw64k:
      /*case T_H245AudioCapability_g726:*/
      case T_H245AudioCapability_g728:
      case T_H245AudioCapability_g729:
      case T_H245AudioCapability_g729AnnexA:
      case T_H245AudioCapability_g7231:
         return ooIsAudioDataTypeSimpleSupported(call, audioCap, dir);
      case T_H245AudioCapability_gsmFullRate:
      case T_H245AudioCapability_gsmHalfRate:
      case T_H245AudioCapability_gsmEnhancedFullRate:
         return ooIsAudioDataTypeGSMSupported(call, audioCap, dir);
      default:
         return NULL;
   }
}


ooH323EpCapability* ooIsVideoDataTypeH263Supported
   (OOH323CallData *call, H245H263VideoCapability* pH263Cap, int dir,
    OOPictureFormat picFormat)
{
   int cap;
   ooH323EpCapability *cur=NULL, *epCap=NULL;
   OOH263CapParams *params= NULL;
   char *pictureType=NULL;
   unsigned mpi=0;
   cap = OO_H263VIDEO;

   if(picFormat == OO_PICFORMAT_SQCIF && pH263Cap->m.sqcifMPIPresent)
   {
      pictureType = "SQCIF";
      mpi = pH263Cap->sqcifMPI;
   }
   if(picFormat == OO_PICFORMAT_QCIF && pH263Cap->m.qcifMPIPresent)
   {
      pictureType = "QCIF";
      mpi = pH263Cap->qcifMPI;
   }
   if(picFormat == OO_PICFORMAT_CIF && pH263Cap->m.cifMPIPresent)
   {
      pictureType = "CIF";
      mpi = pH263Cap->cifMPI;
   }
   if(picFormat == OO_PICFORMAT_CIF4 && pH263Cap->m.cif4MPIPresent)
   {
      pictureType = "CIF4";
      mpi = pH263Cap->cif4MPI;
   }
   if(picFormat == OO_PICFORMAT_CIF16 && pH263Cap->m.cif16MPIPresent)
   {
      pictureType = "CIF16";
      mpi = pH263Cap->cif16MPI;
   }


   OOTRACEDBGA4("Looking for H263 video capability(%s). (%s, %s)\n",
                 pictureType, call->callType, call->callToken);

  /* If we have call specific caps, we use them; otherwise use general
      endpoint caps
   */
   if(call->ourCaps)
     cur = call->ourCaps;
   else
     cur = gH323ep.myCaps;

   while(cur)
   {
      OOTRACEDBGC4("Local cap being compared %s. (%s, %s)\n",
              ooGetCapTypeText(cur->cap),call->callType, call->callToken);

      if(cur->cap == cap && (cur->dir & dir))
      {
         if(((OOH263CapParams*)cur->params)->picFormat == picFormat)
            break;
      }
      cur = cur->next;
   }

   if(!cur) return NULL;

   OOTRACEDBGC4("Found matching H.263 video capability type %s. Comparing"
                " other parameters. (%s, %s)\n", ooGetCapTypeText(cap),
                call->callType, call->callToken);
   if(dir & OORX)
   {
      if(mpi < ((OOH263CapParams*)cur->params)->MPI)
         return NULL;
      else{
         epCap = (ooH323EpCapability*)memAlloc(call->pctxt,
                                                   sizeof(ooH323EpCapability));
         params = (OOH263CapParams*) memAlloc(call->pctxt,
                                                      sizeof(OOH263CapParams));
         if(!epCap || !params)
         {
            OOTRACEERR3("Error:Memory - ooIsVideoDataTypeH263Supported - "
                       "epCap/params. (%s, %s)\n", call->callType,
                        call->callToken);
            return NULL;
         }
         epCap->params = params;
         epCap->cap = cur->cap;
         epCap->dir = cur->dir;
         epCap->capType = cur->capType;
         epCap->startReceiveChannel = cur->startReceiveChannel;
         epCap->startTransmitChannel= cur->startTransmitChannel;
         epCap->stopReceiveChannel = cur->stopReceiveChannel;
         epCap->stopTransmitChannel = cur->stopTransmitChannel;
         epCap->next = NULL;
         memcpy(epCap->params, cur->params, sizeof(OOH263CapParams));
         OOTRACEDBGC4("Returning copy of matched receive capability %s. "
                     "(%s, %s)\n", ooGetCapTypeText(cur->cap), call->callType,
                     call->callToken);
         return epCap;
      }
   }
   if(dir & OOTX)
   {
      epCap = (ooH323EpCapability*)memAlloc(call->pctxt,
                                                  sizeof(ooH323EpCapability));
      params = (OOH263CapParams*) memAlloc(call->pctxt,
                                                      sizeof(OOH263CapParams));
      if(!epCap || !params)
      {
         OOTRACEERR3("Error:Memory - ooIsVideoDataTypeH263Supported - "
                     "epCap/params. (%s, %s)\n", call->callType,
                     call->callToken);
         return NULL;
      }
      epCap->params = params;
      epCap->cap = cur->cap;
      epCap->dir = cur->dir;
      epCap->capType = cur->capType;
      epCap->startReceiveChannel = cur->startReceiveChannel;
      epCap->startTransmitChannel= cur->startTransmitChannel;
      epCap->stopReceiveChannel = cur->stopReceiveChannel;
      epCap->stopTransmitChannel = cur->stopTransmitChannel;
      epCap->next = NULL;
      memcpy(epCap->params, cur->params, sizeof(OOH263CapParams));
      if(params->MPI < mpi)
      {
         OOTRACEINFO5("Increasing minimum picture interval for transmission of"
                      " H263 video capability from %d to %d to match receive "
                      "capability of remote endpoint.(%s, %s)\n", params->MPI,
                      mpi, call->callType, call->callToken);
         params->MPI = mpi;
      }
      OOTRACEDBGC4("Returning copy of matched receive capability %s. "
                  "(%s, %s)\n", ooGetCapTypeText(cur->cap), call->callType,
                  call->callToken);
      return epCap;
   }
   return NULL;

}

ooH323EpCapability* ooIsVideoDataTypeSupported
   (OOH323CallData *call, H245VideoCapability* pVideoCap, int dir)
{
   switch(pVideoCap->t)
   {
   case T_H245VideoCapability_h263VideoCapability:
      if(pVideoCap->u.h263VideoCapability->m.sqcifMPIPresent)
         return ooIsVideoDataTypeH263Supported(call,
                    pVideoCap->u.h263VideoCapability, dir, OO_PICFORMAT_SQCIF);
      else if(pVideoCap->u.h263VideoCapability->m.qcifMPIPresent)
         return ooIsVideoDataTypeH263Supported(call,
                     pVideoCap->u.h263VideoCapability, dir, OO_PICFORMAT_QCIF);
      else if(pVideoCap->u.h263VideoCapability->m.cifMPIPresent)
        return ooIsVideoDataTypeH263Supported(call,
                      pVideoCap->u.h263VideoCapability, dir, OO_PICFORMAT_CIF);
      else if(pVideoCap->u.h263VideoCapability->m.cif4MPIPresent)
        return ooIsVideoDataTypeH263Supported(call,
                     pVideoCap->u.h263VideoCapability, dir, OO_PICFORMAT_CIF4);
      else if(pVideoCap->u.h263VideoCapability->m.cif16MPIPresent)
        return ooIsVideoDataTypeH263Supported(call,
                    pVideoCap->u.h263VideoCapability, dir, OO_PICFORMAT_CIF16);
      break;
   case T_H245VideoCapability_nonStandard:
   case T_H245VideoCapability_h261VideoCapability:
   case T_H245VideoCapability_h262VideoCapability:
   case T_H245VideoCapability_is11172VideoCapability:
   case T_H245VideoCapability_genericVideoCapability:
   case T_H245VideoCapability_extElem1:
   default:
     OOTRACEDBGA1("Unsupported video capability type in "
                  "ooIsVideoDataTypeSupported\n");
      return NULL;
   }
   return NULL;
}

ooH323EpCapability* ooIsDataTypeSupported
                   (OOH323CallData *call, H245DataType *data, int dir)
{
   OOTRACEDBGC3("Looking for data type support. (%s, %s)\n", call->callType,
                 call->callToken);

   switch(data->t)
   {
   case T_H245DataType_nonStandard:
      OOTRACEDBGC3("NonStandard data type not supported.(%s, %s)\n",
                   call->callType, call->callToken);
      return NULL;
   case T_H245DataType_nullData:
      OOTRACEDBGC3("Null data type not supported.(%s, %s)\n",
                   call->callType, call->callToken);
      return NULL;
   case T_H245DataType_videoData:
      OOTRACEDBGC3("Looking for video dataType support. (%s, %s)\n",
                    call->callType, call->callToken);
      return ooIsVideoDataTypeSupported(call, data->u.videoData, dir);
   case T_H245DataType_audioData:
      OOTRACEDBGC3("Looking for audio dataType support. (%s, %s)\n",
                    call->callType, call->callToken);
      return ooIsAudioDataTypeSupported(call, data->u.audioData, dir);
   case T_H245DataType_data:
     OOTRACEDBGC3("Data type not supported.(%s, %s)\n",
                   call->callType, call->callToken);
     return NULL;
   case T_H245DataType_encryptionData:
     OOTRACEDBGC3("Encryption data type not supported.(%s, %s)\n",
                   call->callType, call->callToken);
     return NULL;
   case T_H245DataType_h235Control:
     return NULL;
   case T_H245DataType_h235Media:
     return NULL;
   case T_H245DataType_multiplexedStream:
     return NULL;
   default:
      OOTRACEINFO3("Unknown data type (%s, %s)\n", call->callType,
                    call->callToken);
   }
   return NULL;
}

int ooResetCapPrefs (OOH323CallData *call)
{
   if (0 != call) {
      OOTRACEINFO3 ("Reset capabilities preferences. (%s, %s)\n",
                    call->callType, call->callToken);
      memset (&call->capPrefs, 0, sizeof(OOCapPrefs));
   }
   else {
      OOTRACEINFO1 ("Reset capabilities preferences in endpoint\n");
      memset (&gH323ep.capPrefs, 0, sizeof(OOCapPrefs));
   }

   return OO_OK;
}

int ooRemoveCapFromCapPrefs(OOH323CallData *call, int cap)
{
   int i=0, j=0;
   OOCapPrefs *capPrefs=NULL, oldPrefs;
   if(call)
      capPrefs = &call->capPrefs;
   else
      capPrefs = &gH323ep.capPrefs;

   memcpy(&oldPrefs, capPrefs, sizeof(OOCapPrefs));
   memset(capPrefs, 0, sizeof(OOCapPrefs));
   for(i=0; i<oldPrefs.index; i++)
   {
      if(oldPrefs.order[i] != cap)
         capPrefs->order[j++] = oldPrefs.order[i];
   }
   capPrefs->index = j;
   return OO_OK;
}

void ooAppendCapToCapList
(ooH323EpCapability** pphead, ooH323EpCapability* pcap)
{
   if (0 == *pphead) {
      *pphead = pcap;
   }
   else {
      ooH323EpCapability* p = *pphead;
      while (0 != p->next) p = p->next;
      p->next = pcap;
   }
}

int ooAppendCapToCapPrefs (OOH323CallData *call, int cap)
{
   OOCapPrefs* capPrefs = (0 != call) ? &call->capPrefs : &gH323ep.capPrefs;
   capPrefs->order[capPrefs->index++] = cap;

   OOTRACEINFO3 ("Appended %d to capPrefs, count = %d\n",
                 cap, capPrefs->index);

   return OO_OK;
}

int ooChangeCapPrefOrder(OOH323CallData *call, int cap, int pos)
{
   int i=0, j=0;
   OOCapPrefs *capPrefs = NULL;

   /* Whether to change prefs for call or for endpoint as a whole */
   if(call)
      capPrefs = &call->capPrefs;
   else
      capPrefs = &gH323ep.capPrefs;

   /* check whether cap exists, cap must exist */
   for(i=0; i<capPrefs->index; i++)
   {
      if(capPrefs->order[i] == cap)
         break;
   }
   if(i == capPrefs->index) return OO_FAILED;

   if(i==pos) return OO_OK; /* No need to change */

   /* Decrease Pref order */
   if(i < pos)
   {
      for( ; i<pos; i++)
         capPrefs->order[i] = capPrefs->order[i+1];
      capPrefs->order[i]=cap;
      return OO_OK;
   }
   /* Increase Pref order */
   if(i>pos)
   {
     for(j=i; j>pos; j--)
       capPrefs->order[j] = capPrefs->order[j-1];
     capPrefs->order[j] = cap;
     return OO_OK;
   }

   return OO_FAILED;

}

int ooPreppendCapToCapPrefs(OOH323CallData *call, int cap)
{
   int i=0, j=0;
   OOCapPrefs *capPrefs=NULL, oldPrefs;
   if(call)
      capPrefs = &call->capPrefs;
   else
      capPrefs = &gH323ep.capPrefs;

   memcpy(&oldPrefs, capPrefs, sizeof(OOCapPrefs));


   capPrefs->order[j++] = cap;

   for(i=0; i<oldPrefs.index; i++)
   {
      if(oldPrefs.order[i] != cap)
         capPrefs->order[j++] = oldPrefs.order[i];
   }
   capPrefs->index = j;
   return OO_OK;
}


int ooAddRemoteCapability(OOH323CallData *call, H245Capability *cap)
{
   switch(cap->t)
   {
   case T_H245Capability_receiveAudioCapability:
     return ooAddRemoteAudioCapability(call, cap->u.receiveAudioCapability,
                                       OORX);
   case T_H245Capability_transmitAudioCapability:
     return ooAddRemoteAudioCapability(call, cap->u.transmitAudioCapability,
                                       OOTX);
   case T_H245Capability_receiveAndTransmitAudioCapability:
     return ooAddRemoteAudioCapability(call,
                             cap->u.receiveAndTransmitAudioCapability, OORXTX);
   default:
     OOTRACEDBGA4("Unsupported cap type [%d] encountered. Ignoring. (%s, %s)\n",
                   cap->t, call->callType, call->callToken);
   }
   return OO_OK;
}

int ooAddRemoteAudioCapability(OOH323CallData *call,
                               H245AudioCapability *audioCap,
                               int dir)
{
   int rxframes=0, txframes=0;

   switch(audioCap->t)
   {
   case T_H245AudioCapability_g711Alaw64k:
      if(dir&OOTX) txframes = audioCap->u.g711Alaw64k;
      else if(dir&OORX) rxframes = audioCap->u.g711Alaw64k;
      else{
         txframes = audioCap->u.g711Alaw64k;
         rxframes = audioCap->u.g711Alaw64k;
      }
      return ooCapabilityAddSimpleCapability(call, OO_G711ALAW64K, txframes,
                            rxframes, FALSE, dir, NULL, NULL, NULL, NULL,TRUE);
   case T_H245AudioCapability_g711Alaw56k:
      if(dir&OOTX) txframes = audioCap->u.g711Alaw56k;
      else if(dir&OORX) rxframes = audioCap->u.g711Alaw56k;
      else{
         txframes = audioCap->u.g711Alaw56k;
         rxframes = audioCap->u.g711Alaw56k;
      }
      return ooCapabilityAddSimpleCapability(call, OO_G711ALAW56K, txframes,
                           rxframes, FALSE, dir, NULL, NULL, NULL, NULL, TRUE);
   case T_H245AudioCapability_g711Ulaw64k:
      if(dir&OOTX) txframes = audioCap->u.g711Ulaw64k;
      else if(dir&OORX) rxframes = audioCap->u.g711Ulaw64k;
      else{
         txframes = audioCap->u.g711Ulaw64k;
         rxframes = audioCap->u.g711Ulaw64k;
      }
      return ooCapabilityAddSimpleCapability(call, OO_G711ULAW64K, txframes,
                           rxframes, FALSE, dir, NULL, NULL, NULL, NULL, TRUE);
   case T_H245AudioCapability_g711Ulaw56k:
      if(dir&OOTX) txframes = audioCap->u.g711Ulaw56k;
      else if(dir&OORX) rxframes = audioCap->u.g711Ulaw56k;
      else{
         txframes = audioCap->u.g711Ulaw56k;
         rxframes = audioCap->u.g711Ulaw56k;
      }
      return ooCapabilityAddSimpleCapability(call, OO_G711ULAW56K, txframes,
                           rxframes, FALSE, dir, NULL, NULL, NULL, NULL, TRUE);

/*   case T_H245AudioCapability_g726:
      if(dir&OOTX) txframes = audioCap->u.g726;
      else if(dir&OORX) rxframes = audioCap->u.g726;
      else{
         txframes = audioCap->u.g726;
         rxframes = audioCap->u.g726;
      }
      return ooCapabilityAddSimpleCapability(call, OO_G726, txframes,
                           rxframes, FALSE, dir, NULL, NULL, NULL, NULL, TRUE);
*/
   case T_H245AudioCapability_g728:
      if(dir&OOTX) txframes = audioCap->u.g728;
      else if(dir&OORX) rxframes = audioCap->u.g728;
      else{
         txframes = audioCap->u.g728;
         rxframes = audioCap->u.g728;
      }
      return ooCapabilityAddSimpleCapability(call, OO_G728, txframes,
                           rxframes, FALSE, dir, NULL, NULL, NULL, NULL, TRUE);

   case T_H245AudioCapability_g729:
      if(dir&OOTX) txframes = audioCap->u.g729;
      else if(dir&OORX) rxframes = audioCap->u.g729;
      else{
         txframes = audioCap->u.g729;
         rxframes = audioCap->u.g729;
      }
      return ooCapabilityAddSimpleCapability(call, OO_G729, txframes,
                           rxframes, FALSE, dir, NULL, NULL, NULL, NULL, TRUE);

   case T_H245AudioCapability_g729AnnexA:
      if(dir&OOTX) txframes = audioCap->u.g729AnnexA;
      else if(dir&OORX) rxframes = audioCap->u.g729AnnexA;
      else{
         txframes = audioCap->u.g729AnnexA;
         rxframes = audioCap->u.g729AnnexA;
      }
      return ooCapabilityAddSimpleCapability(call, OO_G729A, txframes,
                           rxframes, FALSE, dir, NULL, NULL, NULL, NULL, TRUE);

   case T_H245AudioCapability_g7231:
      if(dir&OOTX) txframes = audioCap->u.g7231->maxAl_sduAudioFrames;
      else if(dir&OORX) rxframes = audioCap->u.g7231->maxAl_sduAudioFrames;
      else{
         txframes = audioCap->u.g7231->maxAl_sduAudioFrames;
         rxframes = audioCap->u.g7231->maxAl_sduAudioFrames;
      }
      return ooCapabilityAddSimpleCapability(call, OO_G7231, txframes,rxframes,
                                         audioCap->u.g7231->silenceSuppression,
                                         dir, NULL, NULL, NULL, NULL, TRUE);
   case T_H245AudioCapability_gsmFullRate:
      return ooCapabilityAddGSMCapability(call, OO_GSMFULLRATE,
            (unsigned)(audioCap->u.gsmFullRate->audioUnitSize/OO_GSMFRAMESIZE),
                                        audioCap->u.gsmFullRate->comfortNoise,
                                        audioCap->u.gsmFullRate->scrambled,
                                        dir, NULL, NULL, NULL, NULL, TRUE);
   case T_H245AudioCapability_gsmHalfRate:
      return ooCapabilityAddGSMCapability(call, OO_GSMHALFRATE,
            (unsigned)(audioCap->u.gsmHalfRate->audioUnitSize/OO_GSMFRAMESIZE),
                                        audioCap->u.gsmHalfRate->comfortNoise,
                                        audioCap->u.gsmHalfRate->scrambled,
                                        dir, NULL, NULL, NULL, NULL, TRUE);
   case T_H245AudioCapability_gsmEnhancedFullRate:
      return ooCapabilityAddGSMCapability(call, OO_GSMENHANCEDFULLRATE,
   (unsigned)(audioCap->u.gsmEnhancedFullRate->audioUnitSize/OO_GSMFRAMESIZE),
                                audioCap->u.gsmEnhancedFullRate->comfortNoise,
                                audioCap->u.gsmEnhancedFullRate->scrambled,
                                dir, NULL, NULL, NULL, NULL, TRUE);

   default:
     OOTRACEDBGA3("Unsupported audio capability type %d:%s\n",
                  audioCap->t, ooH245AudioCapText(audioCap->t));

   }

   return OO_OK;
}


int ooCapabilityUpdateJointCapabilities
   (OOH323CallData* call, H245Capability *cap)
{
   ooH323EpCapability * epCap = NULL, *cur = NULL;
   OOTRACEDBGC3("checking whether we need to add cap to joint capabilities"
                "(%s, %s)\n", call->callType, call->callToken);

   switch(cap->t)
   {
   case T_H245Capability_receiveAudioCapability:
      epCap= ooIsAudioDataTypeSupported
         (call, cap->u.receiveAudioCapability, OOTX);
      break;

   case T_H245Capability_transmitAudioCapability:
      epCap = ooIsAudioDataTypeSupported
         (call, cap->u.transmitAudioCapability, OORX);
      break;

   case T_H245Capability_receiveAndTransmitAudioCapability:
      epCap = ooIsAudioDataTypeSupported
         (call, cap->u.receiveAndTransmitAudioCapability, OORX | OOTX);
      break;

   case T_H245Capability_receiveVideoCapability:
      return ooCapabilityUpdateJointCapabilitiesVideo
         (call, cap->u.receiveVideoCapability, OOTX);

   case T_H245Capability_transmitVideoCapability:
      return ooCapabilityUpdateJointCapabilitiesVideo
         (call, cap->u.transmitVideoCapability, OORX);

   case T_H245Capability_receiveUserInputCapability:
      if((cap->u.receiveUserInputCapability->t ==
          T_H245UserInputCapability_basicString) &&
         (call->dtmfmode & OO_CAP_DTMF_H245_alphanumeric))
      {
         call->jointDtmfMode |= OO_CAP_DTMF_H245_alphanumeric;
         return OO_OK;
      }
      else if((cap->u.receiveUserInputCapability->t ==
               T_H245UserInputCapability_dtmf) &&
               (call->dtmfmode & OO_CAP_DTMF_H245_signal))
      {
         call->jointDtmfMode |= OO_CAP_DTMF_H245_signal;
         return OO_OK;
      }
      break;

   case T_H245Capability_receiveAndTransmitUserInputCapability:
      if((cap->u.receiveAndTransmitUserInputCapability->t ==
          T_H245UserInputCapability_basicString) &&
         (call->dtmfmode & OO_CAP_DTMF_H245_alphanumeric))
      {
         call->jointDtmfMode |= OO_CAP_DTMF_H245_alphanumeric;
         return OO_OK;
      }
      else if((cap->u.receiveAndTransmitUserInputCapability->t ==
               T_H245UserInputCapability_dtmf) &&
               (call->dtmfmode & OO_CAP_DTMF_H245_signal))
      {
         call->jointDtmfMode |= OO_CAP_DTMF_H245_signal;
         return OO_OK;
      }
      break;

   default:
     OOTRACEDBGA4("Unsupported cap type [%d] encountered. Ignoring. (%s, %s)\n",
                   cap->t, call->callType, call->callToken);
   }

   if(epCap)
   {
      OOTRACEDBGC3("Adding cap to joint capabilities(%s, %s)\n",call->callType,
                   call->callToken);
      /* Note:we add jointCaps in remote endpoints preference order.*/
      if(!call->jointCaps)
         call->jointCaps = epCap;
      else {
         cur = call->jointCaps;
         while(cur->next) cur = cur->next;
         cur->next = epCap;
      }

      return OO_OK;
   }

   OOTRACEDBGC3("Not adding to joint capabilities. (%s, %s)\n", call->callType,
                call->callToken);
   return OO_OK;
}



int ooCapabilityUpdateJointCapabilitiesVideo
   (OOH323CallData *call, H245VideoCapability *videoCap, int dir)
{
   switch(videoCap->t)
   {
   case T_H245VideoCapability_h263VideoCapability:
      return ooCapabilityUpdateJointCapabilitiesVideoH263(call,
                                        videoCap->u.h263VideoCapability, dir);
   default:
      OOTRACEDBGC3("ooCapabilityUpdateJointCapabilitiesVideo - Unsupported"
                   "capability type. (%s, %s)\n", call->callType,
                   call->callToken);
   }
   return OO_OK;
}


int ooCapabilityUpdateJointCapabilitiesVideoH263
   (OOH323CallData *call, H245H263VideoCapability *pH263Cap, int dir)
{
   ooH323EpCapability *epCap = NULL, *cur = NULL;
   if(pH263Cap->m.sqcifMPIPresent)
   {
      epCap =  ooIsVideoDataTypeH263Supported(call, pH263Cap, dir,
                                                          OO_PICFORMAT_SQCIF);
      if(epCap)
      {
         OOTRACEDBGC3("Adding H263-SQCIF to joint capabilities(%s, %s)\n",
                      call->callType, call->callToken);
         /* Note:we add jointCaps in remote endpoints preference order.*/
         if(!call->jointCaps)
            call->jointCaps = epCap;
         else {
            cur = call->jointCaps;
            while(cur->next) cur = cur->next;
            cur->next = epCap;
         }

      }
   }

   epCap = NULL;

   if(pH263Cap->m.qcifMPIPresent)
   {
      epCap =  ooIsVideoDataTypeH263Supported(call, pH263Cap, dir,
                                                          OO_PICFORMAT_QCIF);
      if(epCap)
      {
         OOTRACEDBGC3("Adding H263-QCIF to joint capabilities(%s, %s)\n",
                      call->callType, call->callToken);
         /* Note:we add jointCaps in remote endpoints preference order.*/
         if(!call->jointCaps)
            call->jointCaps = epCap;
         else {
            cur = call->jointCaps;
            while(cur->next) cur = cur->next;
            cur->next = epCap;
         }

      }
   }

   epCap = NULL;

   if(pH263Cap->m.cifMPIPresent)
   {
      epCap =  ooIsVideoDataTypeH263Supported(call, pH263Cap, dir,
                                                          OO_PICFORMAT_CIF);
      if(epCap)
      {
         OOTRACEDBGC3("Adding H263-CIF to joint capabilities(%s, %s)\n",
                      call->callType, call->callToken);
         /* Note:we add jointCaps in remote endpoints preference order.*/
         if(!call->jointCaps)
            call->jointCaps = epCap;
         else {
            cur = call->jointCaps;
            while(cur->next) cur = cur->next;
            cur->next = epCap;
         }

      }
   }

   epCap = NULL;

   if(pH263Cap->m.cif4MPIPresent)
   {
      epCap =  ooIsVideoDataTypeH263Supported(call, pH263Cap, dir,
                                                          OO_PICFORMAT_CIF4);
      if(epCap)
      {
         OOTRACEDBGC3("Adding H263-CIF4 to joint capabilities(%s, %s)\n",
                      call->callType, call->callToken);
         /* Note:we add jointCaps in remote endpoints preference order.*/
         if(!call->jointCaps)
            call->jointCaps = epCap;
         else {
            cur = call->jointCaps;
            while(cur->next) cur = cur->next;
            cur->next = epCap;
         }
      }
   }

   epCap = NULL;

   if(pH263Cap->m.cif16MPIPresent)
   {
      epCap =  ooIsVideoDataTypeH263Supported(call, pH263Cap, dir,
                                                          OO_PICFORMAT_CIF16);
      if(epCap)
      {
         OOTRACEDBGC3("Adding H263-CIF16 to joint capabilities(%s, %s)\n",
                      call->callType, call->callToken);
         /* Note:we add jointCaps in remote endpoints preference order.*/
         if(!call->jointCaps)
            call->jointCaps = epCap;
         else {
            cur = call->jointCaps;
            while(cur->next) cur = cur->next;
            cur->next = epCap;
         }

      }
   }

   return OO_OK;
}

const char* ooGetCapTypeText (OOCapabilities cap)
{
   static const char *capTypes[]={
      "unknown",
      "OO_NONSTANDARD",
      "OO_G711ALAW64K",
      "OO_G711ALAW56K",
      "OO_G711ULAW64K",
      "OO_G711ULAW56K",
      "OO_G72264K",
      "OO_G72256K",
      "OO_G72248K",
      "OO_G7231",
      "OO_G728",
      "OO_G729",
      "OO_G729ANNEXA",
      "OO_IS11172AUDIO",
      "OO_IS13818AUDIO",
      "OO_G729WANNEXB",
      "OO_G729ANNEXAWANNEXB",
      "OO_G7231ANNEXC",
      "OO_GSMFULLRATE",
      "OO_GSMHALFRATE",
      "OO_GSMENHANCEDFULLRATE",
      "OO_GENERICAUDIO",
      "OO_G729EXTENSIONS",
      "OO_VBD",
      "OO_AUDIOTELEPHONYEVENT",
      "OO_AUDIOTONE",
      "OO_EXTELEM1",
      "OO_VIDEO_BASE",
      "OO_NONSTDVIDEO",
      "OO_H261VIDEO",
      "OO_H262VIDEO",
      "OO_H263VIDEO",
      "OO_IS11172VIDEO",  /* mpeg */
      "OO_GENERICVIDEO",
      "OO_EXTELEMVIDEO"
   };
   return ooUtilsGetText (cap, capTypes, OONUMBEROF(capTypes));
}

void ooCapabilityDiagPrint (const ooH323EpCapability* pvalue)
{
   OOTRACEINFO2 ("Capability: %s\n", ooGetCapTypeText(pvalue->cap));

   OOTRACEINFO1 ("  direction:");
   if (pvalue->dir & OORX) { OOTRACEINFO1 (" receive"); }
   if (pvalue->dir & OOTX) { OOTRACEINFO1 (" transmit"); }
   OOTRACEINFO1 ("\n");

   OOTRACEINFO1 ("  type:");
   switch (pvalue->capType) {
   case OO_CAP_TYPE_AUDIO: OOTRACEINFO1 (" audio\n"); break;
   case OO_CAP_TYPE_VIDEO: OOTRACEINFO1 (" video\n"); break;
   case OO_CAP_TYPE_DATA:  OOTRACEINFO1 (" data\n"); break;
   default: OOTRACEINFO2 (" ? (%d)\n", pvalue->capType);
   }

   /* TODO: print params specific to each capability type */
}
