/*
 * adg725.h
 *
 * Created: 18.01.2021 10:48:34
 *  Author: gfcwfzkm
 */ 


#ifndef ADG725_H_
#define ADG725_H_

#include <inttypes.h>

/* Input Shift Register Contents:
 * DB7 (MSB)                                      DB0 (LSB)
 * .-----.------.------.------.------.------.------.------.
 * | !EN | !CSA | !CSB |   X  |  A3  |  A2  |  A1  |  A0  |
 * '-----'------'------'------'------'------'------'------'
 *
 * CSA & CSB have to be zero. If EN is set, the MUX is off,
 * if CSA & CSB are set, it retains the previous condition.
 * A0..3 controls the switch position of the diff-analog MUX
 */

#define ADG725_R_EN_BIT		0x80
#define ADG725_R_CSA_BIT	0x40
#define ADG725_R_CSB_BIT	0x20

enum ADG_MUXPOS{
	ADG_NOCHANGES	= ADG725_R_CSA_BIT | ADG725_R_CSB_BIT,
	ADG_MUXOFF		= ADG725_R_EN_BIT,
	ADG_SWITCH_S1	= 0,
	ADG_SWITCH_S2	= 1,
	ADG_SWITCH_S3	= 2,
	ADG_SWITCH_S4	= 3,
	ADG_SWITCH_S5	= 4,
	ADG_SWITCH_S6	= 5,
	ADG_SWITCH_S7	= 6,
	ADG_SWITCH_S8	= 7,
	ADG_SWITCH_S9	= 8,
	ADG_SWITCH_S10	= 9,
	ADG_SWITCH_S11	= 10,
	ADG_SWITCH_S12	= 11,
	ADG_SWITCH_S13	= 12,
	ADG_SWITCH_S14	= 13,
	ADG_SWITCH_S15	= 14,
	ADG_SWITCH_S16	= 15,
};

typedef struct
{
	enum ADG_MUXPOS adg_switch;
	void *ioInterface;					// Pointer to the IO/Peripheral Interface library
	// Any return value by the IO interface functions have to return zero when successful or
	// non-zero when not successful.
	uint8_t (*startTransaction)(void*);	// Prepare the IO/Peripheral Interface for a transaction
	uint8_t (*sendBytes)(void*,			// Send and receive Bytes from the buffer (SPI only)
						uint8_t,		// Address of the PortExpander (8-Bit Address Format!),
						uint8_t*,		// Pointer to send buffer,
						uint16_t);		// Amount of bytes to send
	uint8_t (*endTransaction)(void*);	// Finish the transaction / Release IO/Peripheral
} adg725_t;

void adg_initStruct(adg725_t *adg, void *ioComs, uint8_t (*startTransaction)(void*),
				uint8_t (*sendBytes)(void*,uint8_t,uint8_t*,uint16_t),
				uint8_t (*endTransaction)(void*));

void adg_init(adg725_t *adg);

void adg_setMux(adg725_t *adg, enum ADG_MUXPOS _muxpos);

/* No actual readback from the device */
enum ADG_MUXPOS adg_getMux(adg725_t *adg);

#endif /* ADG725_H_ */