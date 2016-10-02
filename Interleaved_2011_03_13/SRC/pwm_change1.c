#define _PWM_
#include "main_def.h"

extern Uint16 Tx_count_25ms;		// RYU
extern Uint16 Tx_count_1s;			// RYU

void GetAnaMonitCount(unsigned int * piChA, unsigned * piChB);
interrupt void epwm1_timer_isr(void);
interrupt void epwm2_timer_isr(void);
interrupt void epwm3_timer_isr(void);

void pwm_buffer_setup()
{
    EALLOW;
	nBOOT_MODE_SET; 
	nPWM_ENABLE_SET;
	EDIS;
}

void pwm_g1_setup( double sys_clk, double dead_time)
{
	EALLOW;

	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;    // Enable pull-down on GPIO0 (EPWM1A)
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;    // Enable pull-down on GPIO1 (EPWM1B)   
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;    // Enable pull-down on GPIO2 (EPWM2A)
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;    // Enable pull-down on GPIO3 (EPWM2B)   
	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;    // Enable pull-down on GPIO4 (EPWM3A)
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;    // Enable pull-down on GPIO5 (EPWM3B)   
	
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM2B

	EDIS;

    DINT;

    InitPieCtrl();
    InitPieVectTable();


    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
    EDIS;

	EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm1Regs.TBPRD = (unsigned int)(Tsamp/(2*(1/sys_clk)));
	EPwm1Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
	
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;		// Load registers every ZERO
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;	//CC_CTR_ZERO;
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;	//CC_CTR_ZERO;
	
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;   
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_LOC;			

	EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;            
	EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR; 

//	EPwm1Regs.DBRED = (unsigned int)(dead_time*sys_clk);
//	EPwm1Regs.DBFED = (unsigned int)(dead_time*sys_clk);

	EPwm1Regs.DBRED = 0;
    EPwm1Regs.DBFED = 0;

//	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;     // Select INT on Zero event
    EPwm1Regs.ETSEL.bit.INTSEL =  ET_CTR_ZERO;
    EPwm1Regs.ETSEL.bit.INTEN = 1;  // Enable INT
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event


	//EPWM2 configuration
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm2Regs.TBPRD = (unsigned int)(Tsamp/(2*(1/sys_clk)));
//	EPwm2Regs.TBPHS.half.TBPHS = (unsigned int)(Tsamp/(2*(1/sys_clk))*(240/360));
	EPwm2Regs.TBPHS.half.TBPHS = (unsigned int)(TBPHS_delay);
//	EPwm2Regs.TBPHS.half.TBPHS = 14285;   // Fpwm is 3.5kHz
//	EPwm2Regs.TBPHS.half.TBPHS = 10000;   // Fpwm is 5.0kHz
//	EPwm2Regs.TBPHS.half.TBPHS = 5000;    // Fpwm is 10.0kHz

	EPwm2Regs.TBCTL.bit.PHSDIR =  TB_DOWN;
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;
	EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;

    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;  // Pass through 
	EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;	//CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;	//CC_CTR_ZERO;   

    //EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;	
    EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_LOC;		
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;            
    EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR; 

    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;
//	EPwm2Regs.DBRED = (unsigned int)(dead_time*sys_clk);
//	EPwm2Regs.DBFED = (unsigned int)(dead_time*sys_clk);
	EPwm2Regs.DBRED = 0;
    EPwm2Regs.DBFED = 0;

//	EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;     // Select INT on Zero event
	EPwm2Regs.ETSEL.bit.INTSEL =  ET_CTR_ZERO;                           
    EPwm2Regs.ETSEL.bit.INTEN = 1;  // Enable INT
    EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;

//EPWM3 configuration
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm3Regs.TBPRD = (unsigned int)(Tsamp/(2*(1/sys_clk)));
//	EPwm3Regs.TBPHS.half.TBPHS = (unsigned int)(Tsamp/(2*(1/sys_clk))*(240/360));
	EPwm3Regs.TBPHS.half.TBPHS = (unsigned int)(TBPHS_delay);
//	EPwm3Regs.TBPHS.half.TBPHS = 14285;       // Fpwm is 3.5kHz
//	EPwm3Regs.TBPHS.half.TBPHS = 10000;       // Fpwm is 5.0kHz
//	EPwm3Regs.TBPHS.half.TBPHS = 5000;        // Fpwm is 10.0kHz

	EPwm3Regs.TBCTL.bit.PHSDIR =  TB_UP;
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;
	EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;  // Pass through 

    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;	//CC_CTR_ZERO;
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;	//CC_CTR_ZERO;   

//	EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_LOC;			
	EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;            
	EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR; 
 
    EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;
//	EPwm3Regs.DBRED = (unsigned int)(dead_time*sys_clk);
//	EPwm3Regs.DBFED = (unsigned int)(dead_time*sys_clk);

    EPwm3Regs.DBRED = 0;
    EPwm3Regs.DBFED = 0;

    EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event 
//	EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;
    EPwm3Regs.ETSEL.bit.INTEN = 1;  // Enable INT
    EPwm3Regs.ETPS.bit.INTPRD = ET_1ST; 

	//------------------------------
	//InitEPwm5
	//------------------------------

   EPwm5Regs.TBPRD 				= (unsigned int)(Tsamp/(2*(1/sys_clk)));   // Set timer period
   EPwm5Regs.TBCTL.bit.CTRMODE 	= TB_COUNT_UPDOWN; 		// Count up
   EPwm5Regs.TBCTL.bit.PHSEN 	= TB_DISABLE;        // 

   EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;      // 
   EPwm5Regs.TBCTL.bit.CLKDIV 	= TB_DIV1;         // Slow so we can observe on the scope

   // Setup compare 
   EPwm5Regs.CMPA.half.CMPA 	= (unsigned int)(Tsamp/(2*(1/sys_clk))); 
   EPwm5Regs.CMPB				= (unsigned int)(Tsamp/(2*(1/sys_clk))); 

   // Set actions
   EPwm5Regs.AQCTLA.bit.CAU 		= AQ_SET;            
   EPwm5Regs.AQCTLA.bit.CAD 		= AQ_CLEAR;

   EPwm5Regs.AQCTLB.bit.CBU 		= AQ_SET;            
   EPwm5Regs.AQCTLB.bit.CBD 		= AQ_CLEAR;
   
   EPwm5Regs.DBCTL.bit.OUT_MODE 	= DB_DISABLE;
   EPwm5Regs.ETSEL.bit.INTEN 		= 0;                  // Enable INT


    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
    EDIS;
 
	EALLOW;
	PieVectTable.EPWM1_INT = &epwm1_timer_isr;
	PieVectTable.EPWM2_INT = &epwm2_timer_isr;
	PieVectTable.EPWM3_INT = &epwm3_timer_isr;

    EDIS;

	// Enable CPU INT3 which is connected to EPWM1/2/3/4 INT

	IER |= M_INT3;

	// Enable EPWM INTn in the PIE: Group 3 interrupt 1/2/3/4

	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
	PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
	PieCtrlRegs.PIEIER3.bit.INTx3 = 1;
}

interrupt void epwm1_timer_isr(void)
{

	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;
	Tx_count_25ms++;		// RYU
	Tx_count_1s++;			// RYU 
	current_controller_1();

	DUTY_A =  Idc_Err_PI_a / Vdc_out ;

	if(DUTY_A > Duty_L_MAX) DUTY_A = Duty_L_MAX;
	if(DUTY_A < Duty_L_MIN) DUTY_A = Duty_L_MIN;

//    if( PWM_start == 1)
/*    if(Machine_state == RUNN)
      {OPEN_DUTY_A += 0.15 *0.0001;
     	 if (OPEN_DUTY_A > 0.15) {OPEN_DUTY_A = 0.15;}	
     	cmpa_A = (Tsamp/(2*(1/SYS_CLK)))*(OPEN_DUTY_A);   //Active Low
		}
*/
	if(Machine_state == RUNN)	cmpa_A = (Tsamp/(2*(1/SYS_CLK)))*(DUTY_A);   //Active Low
	else 						cmpa_A = 0; 

//	if( PWM_start == 1)	cmpa1 = (Tsamp/(2*(1/SYS_CLK)))*(1-DUTY_OPEN); //Active high
//	else 				cmpa1 = (Tsamp/(2*(1/SYS_CLK)));

	EPwm1Regs.CMPA.half.CMPA = cmpa_A;
	EPwm1Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

interrupt void epwm2_timer_isr(void)
{
	EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;

	current_controller_2();

	DUTY_B =  Idc_Err_PI_b / Vdc_out ;

	if(DUTY_B > Duty_L_MAX) DUTY_B = Duty_L_MAX;
	if(DUTY_B < Duty_L_MIN) DUTY_B = Duty_L_MIN;

//    if( PWM_start == 1)
//    if(Machine_state == RUNN)
/*      { OPEN_DUTY_B += 0.15 *0.0001;
        if (OPEN_DUTY_B > 0.15) {OPEN_DUTY_B = 0.15;}	
            cmpa_B = (Tsamp/(2*(1/SYS_CLK)))*(OPEN_DUTY_B);   //Active Low
	  }
*/
	if(Machine_state == RUNN)	cmpa_B = (Tsamp/(2*(1/SYS_CLK)))*(DUTY_B);   //Active Low
	else						cmpa_B = 0; 

//	if( PWM_start == 1) cmpa1 = (Tsamp/(2*(1/SYS_CLK)))*(1-DUTY_OPEN); //active High
//	else				cmpa1 = (Tsamp/(2*(1/SYS_CLK)));
    
	EPwm2Regs.CMPA.half.CMPA = cmpa_B;
	EPwm2Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

interrupt void epwm3_timer_isr(void)
{
	EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;
	test_led1_on;
	current_controller_3();

	DUTY_C =  Idc_Err_PI_c / Vdc_out;

	if(DUTY_C > Duty_L_MAX) DUTY_C = Duty_L_MAX;
	if(DUTY_C < Duty_L_MIN) DUTY_C = Duty_L_MIN;
	 
//    if( PWM_start == 1)
//    if(Machine_state == RUNN)	cmpa_C = (Tsamp/(2*(1/SYS_CLK)))*(DUTY_C);   //Active Low
/*    if(Machine_state == RUNN)	
     { OPEN_DUTY_C += 0.15 *0.0001;
        if (OPEN_DUTY_C > 0.15) {OPEN_DUTY_C = 0.15;}	
            cmpa_C = (Tsamp/(2*(1/SYS_CLK)))*(OPEN_DUTY_C);   //Active Low
	  }
*/
	if(Machine_state == RUNN)	cmpa_C = (Tsamp/(2*(1/SYS_CLK)))*(DUTY_C);   //Active Low
	else 						cmpa_C = 0; 
	test_led1_off;

//	if( PWM_start == 1)	cmpa1 = (Tsamp/(2*(1/SYS_CLK)))*(1-DUTY_OPEN);
//	else				cmpa1 = (Tsamp/(2*(1/SYS_CLK)));
	
	EPwm3Regs.CMPA.half.CMPA =  cmpa_C ; 
	EPwm3Regs.ETCLR.bit.INT = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}
