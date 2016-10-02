// EwInv File $Revision: /main/2 $
// Checkin $Date: May 13, 2008   21:50:** $
//###########################################################################
//
// FILE:	io_define.h
//
// Project:	EwInv F28335  _080413
// TITLE:	s.

//#ifndef		__DIGITAL_INOUT_H_
//#define		__DIGITAL_INOUT_H_
     // Set Output High

#define test_led1_on		(GpioDataRegs.GPASET.bit.GPIO11 	= 1)	// D01
#define test_led1_off		(GpioDataRegs.GPACLEAR.bit.GPIO11 	= 1)	// D01
#define test_led1_toggle	(GpioDataRegs.GPATOGGLE.bit.GPIO11 	= 1)	// D01

#define test_led2_on		(GpioDataRegs.GPBSET.bit.GPIO37 	= 1)	// D01
#define test_led2_off		(GpioDataRegs.GPBCLEAR.bit.GPIO37 	= 1)	// D01
#define test_led2_toggle	(GpioDataRegs.GPBTOGGLE.bit.GPIO37 	= 1)	// D01

#define digital_out0_on()	(GpioDataRegs.GPBSET.bit.GPIO58 = 1)	// D01
#define digital_out0_off()	(GpioDataRegs.GPBCLEAR.bit.GPIO58 = 1)	// D01

#define digital_out1_on()	(GpioDataRegs.GPBSET.bit.GPIO59 = 1)	// D02
#define digital_out1_off()	(GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1)	// D02

#define digital_out2_on()	(GpioDataRegs.GPBSET.bit.GPIO60 = 1)	// D03
#define digital_out2_off()	(GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1)	// D03

#define digital_out3_on()	(GpioDataRegs.GPBSET.bit.GPIO48 = 1)	// GPIO.1
#define digital_out3_off()	(GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1)	// GPIO.1

#define digital_out4_on()	(GpioDataRegs.GPBSET.bit.GPIO49 = 1)	// GPIO.2
#define digital_out4_off()	(GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1)	// GPIO.2

#define digital_out5_on()	(GpioDataRegs.GPBSET.bit.GPIO50 = 1)	// GPIO.3
#define digital_out5_off()	(GpioDataRegs.GPBCLEAR.bit.GPIO50 = 1)	// GPIO.3

#define digital_out6_on()	(GpioDataRegs.GPBSET.bit.GPIO51 = 1)	// GPIO.4
#define digital_out6_off()	(GpioDataRegs.GPBCLEAR.bit.GPIO51 = 1)	// GPIO.4

#define digital_out7_on()	(GpioDataRegs.GPBSET.bit.GPIO52 = 1)	// GPIO.5
#define digital_out7_off()	(GpioDataRegs.GPBCLEAR.bit.GPIO52 = 1)	// GPIO.5

#define DI_NONE					0
#define DI_DRIVE_ENABLE			1 
#define DI_MULTI_STEP_BIT0		2
#define DI_MULTI_STEP_BIT1		3
#define DI_MULTI_STEP_BIT2		4
#define DI_MULTI_STEP_BIT3		5
#define DI_FAULT_RESET			6
#define DI_JOG					7
#define DI_AI_REF_ACTIVE		8
#define DI_AI_LOCAL_REMOTE		9
#define DI_EXT_FAULT_A			10
#define DI_EXT_FAULT_B			11
#define DI_MOTOR_SELECT			12
#define DI_MB_BRAKE_STATE		13
#define DI_ACCEL_DECEL_SWITCH	14
#define DI_REF_TUNING_INC		15
#define DI_REF_TUNING_DEC		16
#define DI_ACC_DEC_BYP			17
#define DI_PID_CNTL_ENABLE		18
#define DI_AUTO_PID_MODE		19
#define DI_PID_GAIN_SEL			20
#define DI_PID_I_RESET			21
#define DI_TRQ_REF_OPT_BYP		22
#define DI_TRQ_SIGN				23
#define DI_DI_TRQ_OUT_ZERO		24
#define DI_TIMER_RUN_ENABLE		25
#define DI_SLAVE_RUN_STATUS		26
#define DI_SYNC_CTRL_OPT_BPY	27
#define DI_FLYING_START			28
#define DI_DISABLE_PROFIBUS		29

#define DI_1FWD_2REV			0
#define	DI_1RUN_2DIR			1

#define DO_DISABLED_Aux_SW_Ctrl	0
#define DO_DRIVE_READY			1
#define DO_FAULT_OUT_A			2
#define DO_FAULT_OUT_B			3
#define DO_MOTOR_BRAKE			4
#define DO_RUN_STOP_STATUS		5
#define DO_WARNING_STATUS		6
#define DO_DIRECTION			7
#define DO_JOG_INPUT_STATE		8
#define DO_OV_OC_UV_LIMITING_FUNC	9
#define DO_FREE_FUNCTION		10

struct DIGIT_FUNCTION_BITS {      
	Uint16 DRIVE_ENABLE:1;      // 
	Uint16 MULTI_STEP_BIT0:1;	// 
	Uint16 MULTI_STEP_BIT1:1;	// 
	Uint16 MULTI_STEP_BIT2:1;	// 
	Uint16 MULTI_STEP_BIT3:1;	// 
	Uint16 FAULT_RESET:1;		// 
	Uint16 JOG:1;				//
	Uint16 AI_REF_ACTIVE:1;		//
	Uint16 AI_LOCAL_REMOTE:1;	//
	Uint16 EXT_FAULT_A:1;		//
	Uint16 EXT_FAULT_B:1;		//
	Uint16 MOTOR_SELECT:1;		//
	Uint16 MB_BRAKE_STATE:1;	//
	Uint16 ACCEL_DECEL_SWITCH:1;	//
	Uint16 REF_TUNING_INC:1;	//
	Uint16 REF_TUNING_DEC:1;	//
	Uint16 ACC_DEC_BYP:1;		//
	Uint16 PID_CNTL_ENABLE:1;	//
	Uint16 AUTO_PID_MODE:1;		//
	Uint16 PID_GAIN_SEL:1;		//
	Uint16 PID_I_RESET:1;		//
	Uint16 TRQ_REF_OPT_BYP:1;	//
	Uint16 TRQ_SIGN:1;			//
	Uint16 TRQ_OUT_ZERO:1;		//
	Uint16 TIMER_RUN_ENABLE:1;	//
	Uint16 SLAVE_RUN_STATUS:1;	//
	Uint16 SYNC_CTRL_OPT_BPY:1;	//
	Uint16 FLYING_START:1;		//
	Uint16 DISABLE_PROFIBUS:1;	//
	Uint16 INVERT_DIR:1;		//
	Uint16 INVERT_RUN:1;		//
};

struct DIGITAL_OUT_BITS{
	Uint16 DRIVE_READY:1;	// driver ready
	Uint16 FAULT_OUT_A:1;
	Uint16 FAULT_OUT_B:1;
	Uint16 MOTOR_BRAKE:1;
	Uint16 RUN_STOP:1;
	Uint16 WARNING:1;
	Uint16 DIRECTION:1;
	Uint16 JOG_INPUT:1;
	Uint16 VC_LIMIT:1;
	Uint16 FREE:1;
};

union DIGITAL_OUT_FUNC{
	Uint16	all;
	struct DIGITAL_OUT_BITS bit;
};

union DIGITAL_FUNCTION
{
   Uint32               	  all;
   struct DIGIT_FUNCTION_BITS  bit;
} ;


//----------------------------------------
//Input Define
//----------------------------------------

/*
#define FORWARD_RUN			GpioDataRegs.GPCDAT.bit.GPIO72 	
#define REVERSE_RUN			GpioDataRegs.GPCDAT.bit.GPIO73 		 	
#define SPEED2_DIN			GpioDataRegs.GPCDAT.bit.GPIO74 	
#define SPEED3_DIN			GpioDataRegs.GPCDAT.bit.GPIO75 	
#define FORWARD_SLOW		GpioDataRegs.GPCDAT.bit.GPIO76 		 	
#define FORWARD_STOP		GpioDataRegs.GPCDAT.bit.GPIO77 	
#define REVERSE_SLOW		GpioDataRegs.GPCDAT.bit.GPIO78 		 	
#define REVERSE_STOP		GpioDataRegs.GPCDAT.bit.GPIO79 		 	

#define OVER_HEAT			GpioDataRegs.GPBDAT.bit.GPIO35 		 
#define EXT_RESET			GpioDataRegs.GPBDAT.bit.GPIO36 		 
#define EXT_TRIP			GpioDataRegs.GPBDAT.bit.GPIO38 		 

#define PORT_TRIP_U_PLUS	GpioDataRegs.GPBDAT.bit.GPIO45 		 
#define PORT_TRIP_U_MINUS	GpioDataRegs.GPBDAT.bit.GPIO46 		 
#define PORT_TRIP_V_PLUS	GpioDataRegs.GPBDAT.bit.GPIO47 		 

#define PORT_TRIP_V_MINUS	GpioDataRegs.GPCDAT.bit.GPIO80 		 
#define PORT_TRIP_W_PLUS	GpioDataRegs.GPCDAT.bit.GPIO81 		 
#define PORT_TRIP_W_MINUS	GpioDataRegs.GPCDAT.bit.GPIO82 		 
#define PORT_TRIP_DB		GpioDataRegs.GPCDAT.bit.GPIO83 		 
*/

//----------------------------------------
// Output Define
//----------------------------------------
#define nRESET_DRIVER_SET	(GpioDataRegs.GPASET.bit.GPIO7 	= 1)  
#define nRESET_DRIVER_CLEAR	(GpioDataRegs.GPACLEAR.bit.GPIO7= 1)  

#define nDC_CONTACT_CLEAR	(GpioDataRegs.GPACLEAR.bit.GPIO10 = 1)
#define nDC_CONTACT_SET		(GpioDataRegs.GPASET.bit.GPIO10   = 1)

#define nPWM_ENABLE_CLEAR	(GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1)
#define nPWM_ENABLE_SET		(GpioDataRegs.GPBSET.bit.GPIO34   = 1)

#define nBOOT_MODE_CLEAR	(GpioDataRegs.GPBCLEAR.bit.GPIO35 = 1)
#define nBOOT_MODE_SET		(GpioDataRegs.GPBSET.bit.GPIO35   = 1)

#define nBACKUP_ENABLE_CLEAR (GpioDataRegs.GPBCLEAR.bit.GPIO39 = 1)
#define nBACKUP_ENABLE_SET	 (GpioDataRegs.GPBSET.bit.GPIO39   = 1)

#ifdef	__DIGITAL_INOUT_H_
	void digital_input_proc ();
	void digital_out_proc ();
	#pragma DATA_SECTION(ZONE0_BUF,"ZONE0DATA");
	volatile unsigned int ZONE0_BUF[2048];
	int input_function_option[12];
	int digital_out_funtion[8];
	union DIGITAL_FUNCTION DI_Func;
	union DIGITAL_OUT_FUNC DO_Func;
	Uint16 DI_STATUS = 0, DO_STATUS = 0;
#else
	extern void digital_input_proc ();
	extern void digital_out_proc ();
	extern volatile unsigned int ZONE0_BUF[2048];
	extern int input_function_option[12];
	extern int digital_out_funtion[8];
	extern union DIGITAL_FUNCTION DI_Func;	// 디지털 입력의 기능� 설정한다.
	extern union DIGITAL_OUT_FUNC DO_Func; 
	extern Uint16 DI_STATUS, DO_STATUS;
#endif 

//===================================================================
// No more.
//===================================================================

