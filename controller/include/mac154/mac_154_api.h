/*************************************************************************************************/
/*!
 *  \file
 *
 *  \brief      802.15.4 MAC interface file.
 *
 *  Copyright (c) 2013-2018 Arm Ltd.
 *
 *  Copyright (c) 2019 Packetcraft, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
/*************************************************************************************************/

#ifndef MAC_154_API_H
#define MAC_154_API_H

#include "wsf_types.h"
#include "mac_154_defs.h"
#include "mac_154_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief  Version number. */
#define MAC_154_VER_NUM        0x1302      /* Default value. Auto-generated by builder. */

/*! \brief      Message header length. */
#define MAC_154_MSG_HDR_LEN    3

/*! brief       Command CHCI host to controller */
#define MAC_154_CMD_MLME_ASSOC_REQ            0x01
#define MAC_154_CMD_MLME_ASSOC_RSP            0x02
#define MAC_154_CMD_MLME_DISASSOC_REQ         0x03
#define MAC_154_CMD_MLME_GET_REQ              0x04
#define MAC_154_CMD_MLME_ORPHAN_RSP           0x05
#define MAC_154_CMD_MLME_RESET_REQ            0x06
#define MAC_154_CMD_MLME_RX_ENABLE_REQ        0x07
#define MAC_154_CMD_MLME_SCAN_REQ             0x08
#define MAC_154_CMD_MLME_SET_REQ              0x09
#define MAC_154_CMD_MLME_START_REQ            0x0A
#define MAC_154_CMD_MLME_POLL_REQ             0x0B
#define MAC_154_CMD_MCPS_PURGE_REQ            0x0C

/*! brief       Event CHCI controller to host */
#define MAC_154_EVT_MLME_ASSOC_CFM            0x81
#define MAC_154_EVT_MLME_ASSOC_IND            0x82
#define MAC_154_EVT_MLME_DISASSOC_CFM         0x83
#define MAC_154_EVT_MLME_DISASSOC_IND         0x84
#define MAC_154_EVT_MLME_BEACON_NOTIFY_IND    0x85
#define MAC_154_EVT_MLME_GET_CFM              0x86
#define MAC_154_EVT_MLME_ORPHAN_IND           0x87
#define MAC_154_EVT_MLME_RESET_CFM            0x88
#define MAC_154_EVT_MLME_RX_ENABLE_CFM        0x89
#define MAC_154_EVT_MLME_SCAN_CFM             0x8A
#define MAC_154_EVT_MLME_COMM_STATUS_IND      0x8B
#define MAC_154_EVT_MLME_SET_CFM              0x8C
#define MAC_154_EVT_MLME_START_CFM            0x8D
#define MAC_154_EVT_MLME_POLL_CFM             0x8E
#define MAC_154_EVT_MCPS_PURGE_CFM            0x8F
#define MAC_154_EVT_MCPS_DATA_CFM             0x90
#define MAC_154_EVT_MLME_POLL_IND             0x91

/*! brief       Data CHCI host to controller */
#define MAC_154_DATA_MCPS_DATA_REQ            0x01

/*! brief       Data CHCI controller to host */
#define MAC_154_DATA_MCPS_DATA_IND            0x81

/*! \brief  Receive start flag. */
#define MAC_154_RX_START                      0x01

/*! \brief  Receive stop flag. */
#define MAC_154_RX_STOP                       0x02

/**************************************************************************************************
  Data Types
**************************************************************************************************/
/*! \brief  HCI header */
typedef struct
{
  uint8_t  code;  /*!< Code field. */
  uint16_t len;   /*!< Parameter length. */
} Mac154Hdr_t;

/*! \brief  Callback for a raw frame message. */
typedef void (*Mac154RawFrameFn_t)(uint8_t mpduLen, uint8_t *pMpdu, uint8_t linkQuality, uint32_t timestamp);

/*! \brief  Callbacks which can be used to intercept NHLE messages. */
typedef bool_t (*Mac154DataFn_t)(uint8_t *pBuf);

/*! \brief  Callbacks which can be used to intercept NHLE messages. */
typedef bool_t (*Mac154EvtFn_t)(uint8_t *pBuf);

/*! \brief      Pending operation function. */
typedef uint8_t (*Mac154PendingOpFn_t)(void *);

/*! \brief  MAC PIB. */
typedef struct
{
  uint64_t extAddr; /* Vendor-specific PIB attribute */
  uint64_t coordExtAddr;
  uint32_t responseWaitTime;
  uint16_t vsCRCOverride; /* Vendor-specific PIB attribute */
  uint16_t vsFctlOverride; /* Vendor-specific PIB attribute */
  uint16_t coordShortAddr;
  uint16_t panId;
  uint16_t shortAddr;
  uint16_t transactionPersistenceTime;
  uint16_t maxFrameTotalWaitTime;
  uint8_t  vsRawRx;  /* Vendor-specific PIB attribute */
  uint8_t  deviceType; /* Vendor-specific PIB attribute */
  uint8_t  disableCCA; /* Vendor-specific PIB attribute */
  uint8_t  ackWaitDuration;
  uint8_t  associatedPanCoord;
  uint8_t  associationPermit;
  uint8_t  autoRequest;
  uint8_t  minBE;
  uint8_t  maxBE;
  uint8_t  maxCSMABackoffs;
  uint8_t  maxFrameRetries;
  uint8_t  promiscuousMode;
  uint8_t  rxOnWhenIdle;
  uint8_t  securityEnabled;
  uint8_t  bsn;
  uint8_t  dsn;
  uint8_t  beaconPayloadLength;
  uint8_t  beaconPayload[MAC_154_aMaxBeaconPayloadLength];
} Mac154Pib_t;

/*! \brief  MAC PHY PIB. */
typedef struct
{
  uint8_t  chan;
  uint8_t  txPower;
} Mac154PhyPib_t;

/**************************************************************************************************
  Function Declarations
**************************************************************************************************/

/*************************************************************************************************/
/*!
 *  \brief      Register raw frame callback
 *
 *  \param      rawFrameCback   Raw frame callback handler
 *
 *  \return     None.
 *
 *  \note       Called at a low level, so passed frame must be dealt with expediently
 */
/*************************************************************************************************/
void Mac154RegisterRawFrameCback(Mac154RawFrameFn_t rawFrameCback);

/*************************************************************************************************/
/*!
 *  \brief      Invoke a command handler.
 *
 *  \param      pHdr  Command header.
 *  \param      pBuf  Command buffer.
 *
 *  \return     None.
 */
/*************************************************************************************************/
bool_t Mac154InvokeCmdHandler(Mac154Hdr_t *pHdr, uint8_t *pBuf);

/*************************************************************************************************/
/*!
 *  \brief      Register Event callback.
 *
 *  \param      evtCback    Event callback handler
 *
 *  \return     None.
 */
/*************************************************************************************************/
void Mac154RegisterEvtCback(Mac154EvtFn_t evtCback);

/*************************************************************************************************/
/*!
 *  \brief      Invoke data handler.
 *
 *  \param      pHdr  Data header.
 *  \param      pBuf  Data buffer.
 *
 *  \return     None.
 */
/*************************************************************************************************/
bool_t Mac154InvokeDataHandler(Mac154Hdr_t *pHdr, uint8_t *pBuf);

/*************************************************************************************************/
/*!
 *  \brief      Register Data callback
 *
 *  \param      dataCback   Data callback handler
 *
 *  \return     None.
 */
/*************************************************************************************************/
void Mac154RegisterDataCback(Mac154DataFn_t dataCback);

/*************************************************************************************************/
/*!
 *  \brief      Initialize 802.15.4.
 *
 *  \param      initHandler   Initialize handler if TRUE
 *
 *  \return     TRUE if 802.15.4 initialized.
 */
/*************************************************************************************************/
bool_t Mac154Init(bool_t initHandler);

/*************************************************************************************************/
/*!
 *  \brief      De-initialize 802.15.4.
 *
 *  \return     None.
 */
/*************************************************************************************************/
void Mac154DeInit(void);

/*************************************************************************************************/
/*!
 *  \brief      802.15.4 MAC set extended address.
 *
 *  \param      extAddr   Extended address.
 *
 *  \return     None.
 */
/*************************************************************************************************/
void Mac154SetExtAddr(uint64_t extAddr);

/*************************************************************************************************/
/*!
 *  \brief      Start 15.4 receive, if enabled
 *
 *  \return     None.
 */
/*************************************************************************************************/
void Mac154StartRx(void);

/*************************************************************************************************/
/*!
 *  \brief      802.15.4 MAC get PIB.
 *
 *  \return     Pointer to PIB.
 */
/*************************************************************************************************/
Mac154Pib_t *Mac154GetPIB(void);

/*************************************************************************************************/
/*!
 *  \brief      802.15.4 MAC get PHY PIB.
 *
 *  \return     Pointer to PHY PIB.
 */
/*************************************************************************************************/
Mac154PhyPib_t *Mac154GetPhyPIB(void);

/*************************************************************************************************/
/*!
 *  \brief      Determine whether rx is enabled
 *
 *  \param      None.
 *
 *  \return     TRUE if rx is enabled, FALSE otherwise
 *
 *  \note       Based on the two values: PIB rx on when idle and rx enable flag set through
 *              MLME-RX-ENABLE.req. Note PIB rx on when idle is considered a "conflicting
 *              responsibility" ([109,10-13])
 */
/*************************************************************************************************/
bool_t Mac154IsRxEnabled(void);

#ifdef __cplusplus
};
#endif

#endif /* MAC_154_API_H */
