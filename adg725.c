/*
 * adg725.c
 *
 * Created: 18.01.2021 10:48:42
 *  Author: gfcwfzkm
 */ 

#include "adg725.h"

void adg_initStruct(adg725_t *adg, void *ioComs, uint8_t (*startTransaction)(void*),
				uint8_t (*sendBytes)(void*,uint8_t,uint8_t*,uint16_t),
				uint8_t (*endTransaction)(void*))
{
	adg->ioInterface = ioComs;
	adg->startTransaction = startTransaction;
	adg->sendBytes = sendBytes;
	adg->endTransaction = endTransaction;
}

void adg_init(adg725_t *adg)
{
	adg_setMux(adg, ADG_MUXOFF);
}

void adg_setMux(adg725_t *adg, enum ADG_MUXPOS _muxpos)
{
	adg->adg_switch = _muxpos;
	uint8_t dataBuf = _muxpos;
	
	adg->startTransaction(adg->ioInterface);
	adg->sendBytes(adg->ioInterface, 0, &dataBuf, 1);
	adg->endTransaction(adg->ioInterface);
}

enum ADG_MUXPOS adg_getMux(adg725_t *adg)
{
	return adg->adg_switch;
}