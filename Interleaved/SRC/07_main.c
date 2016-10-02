
#define _MAIN_

#include "main_def.h"
#include "math.h"

void scib_init(void);
void scic_init(void);
extern void Write_Data_Registers_Online();
extern void State_Management();
extern void SCIC_Process(void); 
extern void Init_I2C_eeprom();
extern void Update_state();
int main_loop_cnt = 0;
unsigned int AO_Count = 0;

void GetAnaMonitCount(unsigned int * piChA, unsigned * piChB);

int flag_relay = 0;
Uint16 data1=0;
Uint16 EEPROM_WRITE_CHECK = 0;
Uint16 addr_ch = 0;
Uint16 chng_index=0;
int EEPROM_WRITE_CHECK_VAL; 

void main(void)
{
	unsigned int i;
	InitSysCtrl();
	InitXintf();
	InitGpio();
	dev_DacSetup ();
	dev_InitDACVariable();
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	// Call Flash Initialization to setup flash waitstates
	// This function must reside in RAM
	InitFlash();

    EEPROM_WRITE_CHECK_VAL = 15;

	DINT;
	IER = 0x0000;
	IFR = 0x0000;

	InitPieCtrl();

	Relay_setup();
	pwm_buffer_setup();

	InitPieVectTable();

	for(i=0;i<Buf_MAX;i++)
	{
		Data_Registers[i]=0x0000;
		CAN_Registers[i]=0x0000;
		SCI_Registers[i]=0x0000;
	}
//	scib_init();

//	init_can();
//	Parameter_Initialization();

	Init_I2C_eeprom();
	delay_ms(10);

//	Word_Write_data(81, 0);

	Word_Read_data (81, &EEPROM_WRITE_CHECK);

	Word_Write_data(2306, 0);	// Run_Stop 초기 값  
	Word_Write_data(2300, 0);	// Local/Remote 초기 값: 1/0 

	nDC_CONTACT_CLEAR;

	if(EEPROM_WRITE_CHECK != EEPROM_WRITE_CHECK_VAL)
	{
		Parameter_Initialization();
		for(i=0; i<Buf_MAX;i++)
		{
			Write_Data_Registers_Offline(i);
			SCI_Registers[i] = Data_Registers[i];
			Word_Write_data(i, Data_Registers[i]);

			Word_Read_data(i, &Data_Registers[i]);
			SCI_Registers[i] = Data_Registers[i];
			Read_Data_Registers(i);	 
		}
		Data_Registers[1] = 1;
		Word_Write_data(81, EEPROM_WRITE_CHECK_VAL);
	}
	else
	{
		for(i=0; i<Buf_MAX;i++)
		{
			Word_Read_data(i, &Data_Registers[i]);
			SCI_Registers[i] = Data_Registers[i];
			Read_Data_Registers(i);
		}
	}
	Fault_count= Data_Registers[2379];
	point.Fault1.all = 0x0000;
	point.Fault2.all = 0x0000;
	FAULT_RESET_COMPLETE= 1;
	FAULT_RESET = 0;

	Init_dsc();
	nRESET_DRIVER_SET;	//316J PWM on
	// Initialize SCI-A for data monitoring
	sci_debug_init();
//	scib_init();
	scic_init();

	DI_Func.all = 0;

	Init_var();
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM

	DC_Build_Up_delay_cnt = 0;
	DC_Build_Up_delay_set = 2;	// 2초
//	Set_InitialTime();	// 시간 설정 시 실행 
	Read_Time(&time);

	while(1)
	{
		digital_input_proc();
		digital_out_proc ();
		Update_state();
		Update_var();

		if (EEPROM_WRITE_ENABLE_Rx)
		{
			Word_Write_data(Rx_index, Data_Registers[Rx_index]);
//			Write_Data_Registers_Offline(Tx_index);
			EEPROM_WRITE_ENABLE_Rx= 0;
		}

		Write_Data_Registers_Online(); 		// 2011_02_17 dbsgln
		SCIC_Process();

		// dbsgln
		if (EEPROM_WRITE_ENABLE_Tx)
		{
			if(!chng_index) chng_index = Tx_index;
	 		Word_Write_data(Tx_index, Data_Registers[Tx_index]);
			EEPROM_WRITE_ENABLE_Tx= 0;
		}
//		Analog_Output_Monitoring();
		EPwm5Regs.CMPA.half.CMPA = count;

		Read_Time(&time);	// 2011_03_27 dbsgln
		NOP;
	}
}

void Update_var()
{
	// system control
	if(FaultInfo)	// 아무거나 펄트 발생 시
	{
//		if ( (point.Fault1.all & (~Flag.Fault_Neglect1.all)) != 0x0000 )	State_Index= STATE_FAULT;
//		if ( (point.Fault2.all & (~Flag.Fault_Neglect2.all)) != 0x0000 )	State_Index= STATE_FAULT;
//		if ( point.Fault1.all )	State_Index= STATE_FAULT;
//		if ( point.Fault2.all )	State_Index= STATE_FAULT;
/*
		State_Index = STATE_FAULT;
		Machine_state = STOP;
		Run_Stop_Status = 0;
		Run_Stop = 0;
		FAULT_RESET_COMPLETE = 0;
		DO_Func.bit.DRIVE_READY=0;
		if(Fault_State == 0)
		{
			FAULT_RESET_COMPLETE= 0;
			Fault_count++;
			Word_Write_data(2379, Fault_count);
			// Fault 횟수를 EEPROM에 저장 해야 한다.
			Fault_State = 1;
		}

*/
		if((DI_Func.bit.FAULT_RESET == 1) || (FAULT_RESET ==1))
		{
			FaultInfo = 0;
			OL_TimeOver_Count = 0;
			MaxCon_Curr_Count = 0;
			OverVoltCount = 0;
			UnderVoltCount = 0;
			OverVoltinCount = 0;
			UnderVoltinCount = 0;
			OverHeatCount = 0;
			point.Fault1.all = 0x0000;
			point.Fault2.all = 0x0000;
			FAULT_RESET_COMPLETE = 1;
			FAULT_RESET = 0;
			Run_Stop_Status = 0;
			DC_Build_Up_delay_cnt = 0;
			UV_Check_Enable = 0;
		}
	}
	else 
	{
		Fault_State = 0;
		if(Machine_state == RUNN)
		{
			flag.GT1_ENA = 1;
			flag.control = 1;
			State_Index = STATE_RUNNING;
			Run_Stop_Status = 1;
			nBOOT_MODE_CLEAR;
			nPWM_ENABLE_CLEAR;
		}
		else
		{
			flag.GT1_ENA = 0;			// 정지 시 게이트 즉시 차단
			flag.control = 0;			// 정지 시 전압 제어기 멈춤
			Run_Stop_Status = 0;
			State_Index = STATE_READY;
			DO_Func.bit.DRIVE_READY=1;
			nBOOT_MODE_SET;
			nPWM_ENABLE_SET;
		}
	}
}

void Update_state()
{
	if(Local_Remote)	// Local
	{
		Run_Stop_Src = 1;
		if((Run_Stop)&&(!FaultInfo)) DRIVE_ENABLE = RUNN;
		else						 DRIVE_ENABLE = STOP;
	}
	else				// Remote
	{
		Run_Stop = 0;	// Local --> Remote 시 Key-Pad의 의한 Run 신호 가 clear 되어야 함
		switch(Run_Stop_meth)
		{
			case 0	:	// Terminal
				Run_Stop_Src = 0;
				if(((DI_Func.bit.DRIVE_ENABLE == 1) && (DI_Func.bit.MULTI_STEP_BIT0 == 0)&&(!FaultInfo)))	DRIVE_ENABLE = RUNN;
				else if(((DI_Func.bit.DRIVE_ENABLE==0)||(DI_Func.bit.MULTI_STEP_BIT0 == 1)||(FaultInfo)))	DRIVE_ENABLE = STOP;
			break;
			case 1  :	
			break;
			case 2	:		// Synchronous_Ctrl
			break;
			case 3	:		// Fieldbus ( Profibus, Modbus, CAN bus)
			break;
			case 4	:		// Free Function
			break;
		}
	}
}

