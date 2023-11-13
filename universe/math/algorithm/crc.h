#pragma once
#ifndef XHQM_ALGOR_CRC
#define XHQM_ALGOR_CRC
#include "../../../head.h"
namespace xhqm
{
    namespace crc
    {
        /**
        **************************************************************************************************
        * @Brief    Single byte data inversion
        * @Param
        *            @DesBuf: destination buffer
        *            @SrcBuf: source buffer
        * @RetVal    None
        * @Note      (MSB)0101_0101 ---> 1010_1010(LSB)
        **************************************************************************************************
        */
        void xhqmclass InvertUint8(unsigned char* DesBuf, unsigned char* SrcBuf);

        /**
        **************************************************************************************************
        * @Brief    double byte data inversion
        * @Param
        *            @DesBuf: destination buffer
        *            @SrcBuf: source buffer
        * @RetVal    None
        * @Note      (MSB)0101_0101_1010_1010 ---> 0101_0101_1010_1010(LSB)
        **************************************************************************************************
        */
        void xhqmclass InvertUint16(unsigned short* DesBuf, unsigned short* SrcBuf);

        unsigned short xhqmclass CRC16_CCITT(unsigned char* puchMsg, unsigned int usDataLen);

        unsigned short xhqmclass CRC16_CCITT_FALSE(unsigned char* puchMsg, unsigned int usDataLen);

        unsigned short xhqmclass CRC16_XMODEM(unsigned char* puchMsg, unsigned int usDataLen);

        unsigned short xhqmclass CRC16_X25(unsigned char* puchMsg, unsigned int usDataLen);

        unsigned short xhqmclass CRC16_MODBUS(unsigned char* puchMsg, unsigned int usDataLen);

        unsigned short xhqmclass CRC16_IBM(unsigned char* puchMsg, unsigned int usDataLen);

        unsigned short xhqmclass CRC16_MAXIM(unsigned char* puchMsg, unsigned int usDataLen);

        unsigned short xhqmclass CRC16_USB(unsigned char* puchMsg, unsigned int usDataLen);

    };
}
#endif
