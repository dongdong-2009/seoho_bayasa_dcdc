#include "main_def.h"

/*
********************************************************************************
* GLOBAL VARIABLE
******************************************************************************** 
*/
DAC	deg_Dac [ 4 ];
/*
********************************************************************************
* LOCAL VARIABLE
******************************************************************************** 
*/
S16 deg_sDacTmp;


/*
********************************************************************************
* PROTOTYPES
******************************************************************************** 
*/
void dev_SendDAC ( DAC *pDac, unsigned char );
int AC_DC_TYPE[4];
void dev_DacSetup ( void )
{
	EALLOW;
	// nDAC1_CS pin setup
	GpioCtrlRegs.GPBMUX2.bit.GPIO55  = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO55   = 1;

	// nDAC2_CS pin setup
	GpioCtrlRegs.GPBMUX2.bit.GPIO57  = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO57   = 1;

	GpioCtrlRegs.GPBPUD.bit.GPIO54   = 0;     // Enable pull-up on GPIO24 (SPISIMOB)                                                  
	GpioCtrlRegs.GPBPUD.bit.GPIO56   = 0;     // Enable pull-up on GPIO26 (SPICLKB) 
	GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = 3;     // Asynch input GPIO24 (SPISIMOB)
	GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 3;     // Asynch input GPIO26 (SPICLKB) 
	GpioCtrlRegs.GPBMUX2.bit.GPIO54  = 1;     // Configure GPIO24 as SPISIMOB
	GpioCtrlRegs.GPBMUX2.bit.GPIO56  = 1;     // Configure GPIO26 as SPICLKB         

	SpiaRegs.SPICCR.bit.SPISWRESET   = 0;	   // SPI SW RESET = 0
	SpiaRegs.SPICCR.all              = 0x004F; // Reset on, falling edge, 16-bit char bits  
	SpiaRegs.SPICTL.all              = 0x0006; // Enable master mode, normal phase,
	SpiaRegs.SPICTL.bit.CLK_PHASE    = 1;
	SpiaRegs.SPICCR.bit.CLKPOLARITY  = 1;
	SpiaRegs.SPIBRR                  = 0;														
	SpiaRegs.SPIPRI.bit.FREE         = 1;      // Set so breakpoints don't disturb xmission
	SpiaRegs.SPICTL.bit.SPIINTENA    = 1;
	SpiaRegs.SPICCR.bit.SPISWRESET   = 1;      // SPI SW RESET = 1
	EDIS;
}

void dev_InitDACVariable ( void )
{
	char i;

	DAC	*deg_pDac;
	deg_pDac = &deg_Dac [ 0 ]; 

	for ( i = 0; i < 4; i++ )
	{
		deg_pDac->ucCh   = i + 1;
		deg_pDac->ucType = FLOAT_TYPE;
 		deg_pDac->fValue = 0;
		deg_pDac->fScale = 1;
		deg_pDac++;
	}
}

unsigned short sTemp = 0;

void dev_SendDAC ( DAC *pDac, unsigned char AC_DC_Sel )
{


static	S16 sTemp;

	switch( AC_DC_Sel  )
	{
		case AC_TYPE :
		{
			sTemp = ( int )( (float)( ( pDac->fValue * 2047.5 ) + 2047.5 ) );
			sTemp = ( sTemp > 4095) ? 4095 : ( sTemp <= 0 ) ? 0 : sTemp;
			break;
		}
		case DC_TYPE : 
		{
			sTemp = ( int )( (float)( pDac->fValue * 4095 ) );
			sTemp = ( sTemp > 4095) ? 4095 : ( sTemp <= 0 ) ? 0 : sTemp;
			break;
		}
		default :
			break;
	}

	switch ( pDac->ucCh )
	{
		case DAC_CH1 :
		{
			DAC1_CS = 0;
			SpiaRegs.SPITXBUF = 0xC000 | sTemp & 0xfff;
			while ( !SpiaRegs.SPISTS.bit.INT_FLAG );
			deg_sDacTmp = SpiaRegs.SPIRXBUF;			// empty RX buffer data
			DAC1_CS = 1;
			break;
		}
		case DAC_CH2 : 
		{
			DAC1_CS = 0;
			SpiaRegs.SPITXBUF = 0x4000 | sTemp & 0xfff;
			while ( !SpiaRegs.SPISTS.bit.INT_FLAG );
			deg_sDacTmp = SpiaRegs.SPIRXBUF;
			DAC1_CS = 1;
			break;
		}
		case DAC_CH3 : 
		{
			DAC2_CS = 0;
			SpiaRegs.SPITXBUF = 0xC000 | sTemp  & 0xfff;
			while ( !SpiaRegs.SPISTS.bit.INT_FLAG );
			deg_sDacTmp = SpiaRegs.SPIRXBUF;
			DAC2_CS = 1;
			break;
		}
		case DAC_CH4 : 
		{
			DAC2_CS = 0;
			SpiaRegs.SPITXBUF = 0x4000 | sTemp  & 0xfff;
			while ( !SpiaRegs.SPISTS.bit.INT_FLAG );
			deg_sDacTmp = SpiaRegs.SPIRXBUF;
			DAC2_CS = 1;
			break;
		}
		default :
			break;
	}
}

void dev_BackgroundDAC ( void )
{
	U8 i;
	DAC *deg_pDac;
	
	deg_Dac[0].piChData=&Ias;
	deg_Dac[0].fScale = 50.;
	deg_Dac[0].ucType = 2;
	AC_DC_TYPE[0] = DC_TYPE;

	deg_Dac[1].piChData=&Ibs;
	deg_Dac[1].fScale = 50.;
	deg_Dac[1].ucType = 2;
	AC_DC_TYPE[1] = DC_TYPE;

	deg_Dac[2].piChData=&Ics;
	deg_Dac[2].fScale = 50.;
	deg_Dac[2].ucType = 2;
	AC_DC_TYPE[2]= DC_TYPE;

	deg_Dac[3].piChData=&Idc_ref;
	deg_Dac[3].fScale = 50.;
	deg_Dac[3].ucType = 2;
	AC_DC_TYPE[3] = DC_TYPE;

	deg_pDac = &deg_Dac [ 0 ];


	for ( i = 0; i < 4; i++ )
	{
		switch ( deg_pDac->ucType )
		{
			case INT_TYPE	: deg_pDac->fValue= *( int *)   deg_pDac->piChData / ( int )   deg_pDac->fScale;    break;
			case FLOAT_TYPE	: deg_pDac->fValue= *( float *) deg_pDac->piChData / ( float ) deg_pDac->fScale;	break;
			default 		: 																					break;
		}
//	deg_pDac->fValue=300;
		dev_SendDAC ( deg_pDac, AC_DC_TYPE[i] );
		deg_pDac++;
	}
}

