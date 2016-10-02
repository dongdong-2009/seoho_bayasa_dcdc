#define __DIGITAL_INOUT_H_

#include "math.h"
#include "main_def.h"

void set_digit_input_funtion( int input_state, int function_option, int di_port );

int input_state(int port)
{
	unsigned int xbus_in;
	int i,j;

	i = 1;

	j = port;

	while( j ){	i *= 2; j--; }
	asm ("      nop");

	xbus_in = ( ZONE0_BUF[0x0050] & i );
	if( xbus_in ) 	return 0;
	else 			return 1;
}


void set_digit_input_funtion( int input_state, int function_option, int di_port )
{
	if(di_port<=1)
	{
		if(!input_function_option[1])	// 1.FWD / 2.REV
		{
			if(di_port==0)	// DI 1
			{
				if		(!DI_Func.bit.INVERT_RUN )	DI_Func.bit.DRIVE_ENABLE = input_state;
				else								DI_Func.bit.DRIVE_ENABLE = 0;
			}
			else if (di_port==1)	// DI 2
			{
				if(!DI_Func.bit.DRIVE_ENABLE )		DI_Func.bit.INVERT_RUN = input_state;
				else								DI_Func.bit.INVERT_RUN = 0;
			}
		}
		else	// 1.RUN / 2.DIR
		{
			if		(di_port==0)	DI_Func.bit.DRIVE_ENABLE = input_state;	// DI 1
			else if (di_port == 1)	DI_Func.bit.INVERT_DIR = input_state;
		}
	}
	else
	{
		switch( function_option )
		{
			case DI_NONE:	
				break;
			case DI_DRIVE_ENABLE:		DI_Func.bit.DRIVE_ENABLE 		&= input_state;	break;
			case DI_MULTI_STEP_BIT0:	DI_Func.bit.MULTI_STEP_BIT0	 = input_state;	break;
			case DI_MULTI_STEP_BIT1:	DI_Func.bit.MULTI_STEP_BIT1	 = input_state;	break;
			case DI_MULTI_STEP_BIT2:	DI_Func.bit.MULTI_STEP_BIT2	 = input_state;	break;
			case DI_MULTI_STEP_BIT3:	DI_Func.bit.MULTI_STEP_BIT3	 = input_state;	break;
			case DI_FAULT_RESET:		DI_Func.bit.FAULT_RESET 	  	 = input_state;	break;
			case DI_JOG:				DI_Func.bit.JOG			 	 = input_state;	break;
			case DI_AI_REF_ACTIVE:		DI_Func.bit.AI_REF_ACTIVE		 = input_state;	break;
			case DI_AI_LOCAL_REMOTE:	DI_Func.bit.AI_LOCAL_REMOTE 	 = input_state;	break;
			case DI_EXT_FAULT_A:		DI_Func.bit.EXT_FAULT_A	  	 = input_state;	break;
			case DI_EXT_FAULT_B:		DI_Func.bit.EXT_FAULT_B	  	 = input_state;	break;
			case DI_MOTOR_SELECT:		DI_Func.bit.MOTOR_SELECT	 	 = input_state;	break;
			case DI_MB_BRAKE_STATE:		DI_Func.bit.MB_BRAKE_STATE 	 = input_state;	break;
			case DI_ACCEL_DECEL_SWITCH:	DI_Func.bit.ACCEL_DECEL_SWITCH = input_state;	break;
			case DI_REF_TUNING_INC:		DI_Func.bit.REF_TUNING_INC	 = input_state;	break;
			case DI_REF_TUNING_DEC:		DI_Func.bit.REF_TUNING_DEC	 = input_state;	break;
			case DI_ACC_DEC_BYP:		DI_Func.bit.ACC_DEC_BYP		 = input_state;	break;
			case DI_PID_CNTL_ENABLE:	DI_Func.bit.PID_CNTL_ENABLE	 = input_state;	break;
			case DI_AUTO_PID_MODE:		DI_Func.bit.AUTO_PID_MODE		 = input_state;	break;
			case DI_PID_GAIN_SEL:		DI_Func.bit.PID_GAIN_SEL		 = input_state;	break;
			case DI_PID_I_RESET:		DI_Func.bit.PID_I_RESET		 = input_state;	break;
			case DI_TRQ_REF_OPT_BYP:	DI_Func.bit.TRQ_REF_OPT_BYP	 = input_state;	break;
			case DI_TRQ_SIGN:			DI_Func.bit.TRQ_SIGN			 = input_state;	break;
			case DI_DI_TRQ_OUT_ZERO:	DI_Func.bit.TRQ_OUT_ZERO		 = input_state;	break;
			case DI_TIMER_RUN_ENABLE:	DI_Func.bit.TIMER_RUN_ENABLE	 = input_state;	break;
			case DI_SLAVE_RUN_STATUS:	DI_Func.bit.SLAVE_RUN_STATUS	 = input_state;	break;
			case DI_SYNC_CTRL_OPT_BPY:	DI_Func.bit.SYNC_CTRL_OPT_BPY	 = input_state;	break;
			case DI_FLYING_START:		DI_Func.bit.FLYING_START		 = input_state;	break;
			case DI_DISABLE_PROFIBUS:	DI_Func.bit.DISABLE_PROFIBUS	 = input_state;	break;
		}
	}
}

void digital_input_proc()
{
	int temp;
	int a;
	DI_Func.all = 0;
	for(a=-1;a<8;a++)
	{
		temp = input_state(a); set_digit_input_funtion( temp, input_function_option[a], a);
		switch (a)
		{
			case 0:	if( input_state(a))	DI_STATUS |= 0x0001; 
					else  				DI_STATUS &= 0x00FE;
					break;
			case 1:	if( input_state(a))	DI_STATUS |= 0x0002;
					else  				DI_STATUS &= 0x00FD;
					break;
			case 2:	if( input_state(a))	DI_STATUS |= 0x0004;
					else  				DI_STATUS &= 0x00FB;
					break;
			case 3:	if( input_state(a))	DI_STATUS |= 0x0008;
					else  				DI_STATUS &= 0x00F7;
					break;
			case 4:	if( input_state(a))	DI_STATUS |= 0x0010;
					else  				DI_STATUS &= 0x00EF;
					break;
			case 5:	if( input_state(a))	DI_STATUS |= 0x0020;
					else  				DI_STATUS &= 0x00DF;
					break;
			case 6:	if( input_state(a))	DI_STATUS |= 0x0040;
					else  				DI_STATUS &= 0x00BF;
					break;
			case 7:	if( input_state(a))	DI_STATUS |= 0x0080;
					else  				DI_STATUS &= 0x007F;
					break;
		}
	}
}

int digital_port_check( int out_function )
{
	int i;
	i = 0;
	switch (out_function)
	{
		case 0:		i= 0;						break;
		case 1:		i= DO_Func.bit.DRIVE_READY;	break;
		case 2:		i= DO_Func.bit.FAULT_OUT_A;	break;
		case 3:		i= DO_Func.bit.FAULT_OUT_B;	break;
		case 4:		i= DO_Func.bit.MOTOR_BRAKE;	break;
		case 5:		i= DO_Func.bit.RUN_STOP;	break;
		case 6:		i= DO_Func.bit.WARNING;		break;
		case 7:		i= DO_Func.bit.DIRECTION;	break;
		case 8:		i= DO_Func.bit.JOG_INPUT;	break;
		case 9:		i= DO_Func.bit.VC_LIMIT;	break;
		case 10:	i= DO_Func.bit.FREE;		break;
		default:	i= 0;						break;
	}
	return i;
}  	


void digital_out_proc ()
{
	int i;
	i = digital_port_check( digital_out_funtion[0] );
	if( i ) digital_out0_on(), 	DO_STATUS |= 0x0001;
	else 	digital_out0_off(), DO_STATUS &= 0x00FE;

	i = digital_port_check( digital_out_funtion[1] );
	if( i ) digital_out1_on(),	DO_STATUS |= 0x0002;
	else 	digital_out1_off(),	DO_STATUS &= 0x00FD;

	i = digital_port_check( digital_out_funtion[2] );
	if( i ) digital_out2_on(),	DO_STATUS |= 0x0004;
	else 	digital_out2_off(),	DO_STATUS &= 0x00FB;

	i = digital_port_check( digital_out_funtion[3] );
	if( i ) digital_out3_on(),	DO_STATUS |= 0x0008;
	else 	digital_out3_off(),	DO_STATUS &= 0x00F7;

	i = digital_port_check( digital_out_funtion[4] );
	if( i ) digital_out4_on(),	DO_STATUS |= 0x0010;
	else 	digital_out4_off(),	DO_STATUS &= 0x00EF;

	i = digital_port_check( digital_out_funtion[5] );
	if( i ) digital_out5_on(),	DO_STATUS |= 0x0020;
	else 	digital_out5_off(),	DO_STATUS &= 0x00DF;

	i = digital_port_check( digital_out_funtion[6] );
	if( i ) digital_out6_on(),	DO_STATUS |= 0x0040;
	else 	digital_out6_off(),	DO_STATUS &= 0x00BF;

	i = digital_port_check( digital_out_funtion[7] );
	if( i ) digital_out7_on(),	DO_STATUS |= 0x0080;
	else 	digital_out7_off(),	DO_STATUS &= 0x007F;
}

