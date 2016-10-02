//#include	<All_Header.h>
//#include	<All_Extern_Variables.h> 
#include "sci_bc.h"
#include "main_def.h"

void Read_Data_Registers(int Par_index)
{
	switch(Par_index)
	{
		case 200 :	Device_Info=				Data_Registers[Par_index];	break;
		case 201 :	Software_Number=			Data_Registers[Par_index];	break;
		case 202 :	Software_Version=			Data_Registers[Par_index];	break; 

		case 280 :	Run_Stop_Src=				Data_Registers[Par_index];	break;
		case 281 :	Ref_method=					Data_Registers[Par_index];	break;

		// Digital Input
		case 810:	input_function_option[1]=	Data_Registers[Par_index];	break;	// P8.0		DI1, DI2
		case 811:	input_function_option[2]=	Data_Registers[Par_index];	break;	// P8.1		DI3
		case 812:	input_function_option[3]=	Data_Registers[Par_index];	break;	// P8.2		DI4
		case 813:	input_function_option[4]= 	Data_Registers[Par_index];	break;	// P8.3		DI5
		case 814:	input_function_option[5]= 	Data_Registers[Par_index];	break;	// P8.4		DI6
		case 815:	input_function_option[6]=	Data_Registers[Par_index];	break;	// P8.5		DI7
		case 816:	input_function_option[7]= 	Data_Registers[Par_index];	break;	// P8.6		DI8
		case 826:	Ref_UP_DOWN_TIME		= 	Data_Registers[Par_index];	break;	// P8.16
		case 828:	RUN_DELAY_TIME 			= 	Data_Registers[Par_index];	break;	// P8.18
		// Analog Output
		case 940:	AO1.P00_Output_selection= 	Data_Registers[Par_index];	break;	// P11.0
		case 941:	AO1.P01_Type= 				Data_Registers[Par_index];	break;	// P11.1
		case 942:	AO1.P02_Adjustment_0mA= 	Data_Registers[Par_index];	break;	// P11.2
		case 943:	AO1.P03_Adjustment_4mA= 	Data_Registers[Par_index];	break;	// P11.3
		case 944:	AO1.P04_Adjustment_20mA= 	Data_Registers[Par_index];	break;	// P11.4
		case 945:	AO1.P05_Max_output_x1=		Data_Registers[Par_index];	break;	// P11.5
		case 946:	AO1.P06_Inversion= 			Data_Registers[Par_index];	break;	// P11.6
		case 947:	AO2.P00_Output_selection= 	Data_Registers[Par_index];	break;	// P11.7
		case 948:	AO2.P01_Type= 				Data_Registers[Par_index];	break;	// P11.8
		case 949:	AO2.P02_Adjustment_0mA= 	Data_Registers[Par_index];	break;	// P11.9
		case 950:	AO2.P03_Adjustment_4mA= 	Data_Registers[Par_index];	break;	// P11.10
		case 951:	AO2.P04_Adjustment_20mA=	Data_Registers[Par_index];	break;	// P11.11
		case 952:	AO2.P05_Max_output_x1=		Data_Registers[Par_index];	break;	// P11.12
		case 953:	AO2.P06_Inversion= 			Data_Registers[Par_index];	break;	// P11.13
		// Digital Output
		case 960:	digital_out_funtion[0]= 	Data_Registers[Par_index];	break;	// P12.0
		case 961:	digital_out_funtion[1]= 	Data_Registers[Par_index];	break;	// P12.1
		case 962:	digital_out_funtion[2]= 	Data_Registers[Par_index];	break;	// P12.2
		case 963:	digital_out_funtion[3]= 	Data_Registers[Par_index];	break;	// P12.3
		case 964:	digital_out_funtion[4]= 	Data_Registers[Par_index];	break;	// P12.4
		case 965:	digital_out_funtion[5]=		Data_Registers[Par_index];	break;	// P12.5
		case 966:	digital_out_funtion[6]= 	Data_Registers[Par_index];	break;	// P12.6
		case 967:	digital_out_funtion[7]=		Data_Registers[Par_index];	break;	// P12.7

		case 1870:	Fsw= 			1e+2*(float)(Data_Registers[Par_index]);break;	// P29.0
		case 2301:	Vdc_set_user=		(float)(Data_Registers[Par_index]);	break;	// P29.1
		case 1872:	V_rate= 					Data_Registers[Par_index];	break;	// P29.2
		case 1873:	P_rate= 					Data_Registers[Par_index];	break;	// P29.3
		case 1874:	R_L=			1e-4*(float)(Data_Registers[Par_index]);break;	// P29.4
		case 1875:	La=				1e-4*(float)(Data_Registers[Par_index]);break;	// P29.5
		case 1876:	Sens_time_Vin=	1e-1*		Data_Registers[Par_index];	break;	// P29.6
		case 1877:	Kp_Vdc_factor= 	1e-1*(float)(Data_Registers[Par_index]);break;	// P29.7
		case 1878:	Ki_Vdc_factor=	1e-1*(float)(Data_Registers[Par_index]);break;	// P29.8
		case 1879:	Kp_Idc_factor= 	1e-1*(float)(Data_Registers[Par_index]);break;	// P29.9
		case 1880:	Ki_Idc_factor=	1e-1*(float)(Data_Registers[Par_index]);break; 	// P29.10
		case 1881:	vc_cnt_set=					Data_Registers[Par_index];	break;	// P29.11
		case 1882:	Cin=			1e-6*(float)(Data_Registers[Par_index]);break;	// P29.12
		case 1883:	Cout=			1e-6*(float)(Data_Registers[Par_index]);break;	// P29.12
		case 1884:	Fnv=			1e-1*(float)(Data_Registers[Par_index]);break;	// P29.14
		case 1885:	Fnc=			1e-1*(float)(Data_Registers[Par_index]);break;	// P29.15
		case 1886:	OV_set= 					Data_Registers[Par_index];	break;	// P29.16
		case 1887:	UV_set= 					Data_Registers[Par_index];	break;	// P29.17
		case 1888:	OVin_set=					Data_Registers[Par_index];	break;	// P29.18
		case 1889:	UVin_set=					Data_Registers[Par_index];	break;	// P29.19
		case 1890:	I_rate=						Data_Registers[Par_index];	break;	// P29.20
		case 1891:	OC_Trip=		1e-1*		Data_Registers[Par_index];	break;	// P29.21
		case 1892:	Max_Con_cur=	1e-1*		Data_Registers[Par_index];	break;	// P29.22
		case 1893:	Over_Load=		1e-1*		Data_Registers[Par_index];	break;	// P29.23
		case 1894:	Over_Load_Time=	1e-1*		Data_Registers[Par_index];	break;	// P29.24
		case 1895:	OV_Time=		1e-1*		Data_Registers[Par_index];	break;	// P29.25
		case 1896:	OV_Temp=		1e-1*		Data_Registers[Par_index];	break;	// P29.26
		
		case 2300:	Local_Remote=				Data_Registers[Par_index];	break;
		case 2306:	Run_Stop=					Data_Registers[Par_index];	break;
		case 2355:	Drive_Voltage=	1e-1*		Data_Registers[Par_index];	break;	// P29.4
		case 2484:	FAULT_RESET=				Data_Registers[Par_index];	break;
	}
}

void Write_Data_Registers_Online()
{
	Data_Registers[2270]=		Run_Stop_Status;

	Data_Registers[2300]=		Local_Remote;
	Data_Registers[2301]= 		(int)Vdc_set_user;
	Data_Registers[2306]=		Run_Stop;

	Data_Registers[2310]=		(int)Vdc_input_LPF;					// M1.0.0
	Data_Registers[2311]=		Under_Limit((int)Iinput_LPF);		// M1.0.1
	Data_Registers[2312]=					(int)Vdc_out_LPF;		// M1.0.2
	Data_Registers[2313]=		Under_Limit((int)Ias_LPF);			// M1.0.3
	Data_Registers[2314]=		Under_Limit((int)Ibs_LPF);			// M1.0.4
	Data_Registers[2315]= 		Under_Limit((int)Ics_LPF);			// M1.0.5
	Data_Registers[2316]=		Under_Limit((int)Idc_ref_LPF);		// M1.0.6
	Data_Registers[2317]=					(int)Vdc_Error;			// M1.0.7
	Data_Registers[2318]=		Under_Limit((int)(1e-2*Power_in));	// M1.0.8
	Data_Registers[2319]=		Under_Limit((int)(1e-2*Power_out));	// M1.0.9
	Data_Registers[2320]=		(int)Idc_Error_a;					// M1.0.10
	Data_Registers[2321]=		(int)Idc_Error_b;					// M1.0.11
	Data_Registers[2322]=		(int)Idc_Error_c;					// M1.0.12
	Data_Registers[2323]=		(int)(10.*Temperature);				// M1.0.13

	Data_Registers[2330]=		State_Index;
	Data_Registers[2340]=		DI_STATUS;							// M1.1.0
//	SCI_Registers[2340] = 		Data_Registers[2340];
	Data_Registers[2341]=		DO_STATUS;							// M1.1.1
	Data_Registers[2342]=		255;								// M1.1.2
	Data_Registers[2343]=		255;								// M1.1.3
	Data_Registers[2344]=		Anaolg_Output_mA_x1;				// M1.1.4

	Data_Registers[2352]=		Run_Stop_Src;	// M1.2.2
	Data_Registers[2353]=		Ref_method;		// M1.2.3
	Data_Registers[2354]=		P_rate;			// M1.2.4
	Data_Registers[2355]=		10 * Drive_Voltage;	// M1.2.5

	Data_Registers[1874]=		(int)(10000. * R_L);
	
	Data_Registers[2376]=		point.Fault1.all;
	Data_Registers[2377]=		point.Fault2.all;
	Data_Registers[2378]=		point.Fault3.all;
	Data_Registers[2379]= 		Fault_count; 
	Data_Registers[2484]=		FAULT_RESET;
	Data_Registers[2485]=		FAULT_RESET_COMPLETE;
	Data_Registers[1871]=		(int)(Vdc_set_user);

	// Analog Output ฐüทร Parameter back monitoring
	Data_Registers[940]=		AO1.P00_Output_selection;		// P11.0
	Data_Registers[941]= 		AO1.P01_Type;					// P11.1
	Data_Registers[942]= 		AO1.P02_Adjustment_0mA;		// P11.2
	Data_Registers[943]= 		AO1.P03_Adjustment_4mA;		// P11.3
	Data_Registers[944]= 		AO1.P04_Adjustment_20mA;		// P11.4
	Data_Registers[945]= 		AO1.P05_Max_output_x1;			// P11.5
	Data_Registers[946]= 		AO1.P06_Inversion;				// P11.6
}

void Write_Data_Registers_Offline(int Par_index)
{
	switch(Par_index)
	{
		case 200 :	Data_Registers[Par_index]=Device_Info;				break;
		case 201 :	Data_Registers[Par_index]=Software_Number;			break;
		case 202 :	Data_Registers[Par_index]=Software_Version;			break; 
		case 280 :	Data_Registers[Par_index]=Run_Stop_Src;				break;
		case 281 :	Data_Registers[Par_index]=Ref_method;				break;
		// Digital Input
				// Digital Input
		case 810:	Data_Registers[Par_index]=input_function_option[1];	break;	// P8.0		DI1, DI2
		case 811:	Data_Registers[Par_index]=input_function_option[2];	break;	// P8.1		DI3
		case 812:	Data_Registers[Par_index]=input_function_option[3];	break;	// P8.2		DI4
		case 813:	Data_Registers[Par_index]=input_function_option[4];	break;	// P8.3		DI5
		case 814:	Data_Registers[Par_index]=input_function_option[5];	break;	// P8.4		DI6
		case 815:	Data_Registers[Par_index]=input_function_option[6];	break;	// P8.5		DI7
		case 816:	Data_Registers[Par_index]=input_function_option[7];	break;	// P8.6		DI8
		case 826:	Data_Registers[Par_index]=Ref_UP_DOWN_TIME;			break;	// P8.16
		case 828:	Data_Registers[Par_index]=RUN_DELAY_TIME;			break;	// P8.18	

		// Analog Output
		case 940:	Data_Registers[Par_index]=AO1.P00_Output_selection; break;	// P11.0
		case 941:	Data_Registers[Par_index]=AO1.P01_Type; 			break;	// P11.1
		case 942:	Data_Registers[Par_index]=AO1.P02_Adjustment_0mA; 	break;	// P11.2
		case 943:	Data_Registers[Par_index]=AO1.P03_Adjustment_4mA; 	break;	// P11.3
		case 944:	Data_Registers[Par_index]=AO1.P04_Adjustment_20mA; 	break;	// P11.4
		case 945:	Data_Registers[Par_index]=AO1.P05_Max_output_x1;	break;	// P11.5
		case 946:	Data_Registers[Par_index]=AO1.P06_Inversion; 		break;	// P11.6
		case 947:	Data_Registers[Par_index]=AO2.P00_Output_selection; break;	// P11.7
		case 948:	Data_Registers[Par_index]=AO2.P01_Type; 			break;	// P11.8
		case 949:	Data_Registers[Par_index]=AO2.P02_Adjustment_0mA; 	break;	// P11.9
		case 950:	Data_Registers[Par_index]=AO2.P03_Adjustment_4mA; 	break;	// P11.10
		case 951:	Data_Registers[Par_index]=AO2.P04_Adjustment_20mA;	break;	// P11.11
		case 952:	Data_Registers[Par_index]=AO2.P05_Max_output_x1;	break;	// P11.12
		case 953:	Data_Registers[Par_index]=AO2.P06_Inversion; 		break;	// P11.13
		// Digital Output
		case 960:	Data_Registers[Par_index]=digital_out_funtion[0];	break;	// P12.0
		case 961:	Data_Registers[Par_index]=digital_out_funtion[1];	break;	// P12.1
		case 962:	Data_Registers[Par_index]=digital_out_funtion[2];	break;	// P12.2
		case 963:	Data_Registers[Par_index]=digital_out_funtion[3];	break;	// P12.3
		case 964:	Data_Registers[Par_index]=digital_out_funtion[4];	break;	// P12.4
		case 965:	Data_Registers[Par_index]=digital_out_funtion[5];	break;	// P12.5
		case 966:	Data_Registers[Par_index]=digital_out_funtion[6];	break;	// P12.6
		case 967:	Data_Registers[Par_index]=digital_out_funtion[7];	break;	// P12.7 

		case 2351:	Data_Registers[Par_index]=Control_method;			break;
		case 2355:	Data_Registers[Par_index]=10*Drive_Voltage;			break;

		case 1870:	Data_Registers[Par_index]=(int)(1e-2*Fsw);			break;	// P29.0	// kHz
		case 1871:	Data_Registers[Par_index]=(int)(Vdc_set_user);		break;	// P29.1	// kHz
		case 1872:	Data_Registers[Par_index]=V_rate;					break;	// P29.2	// V
		case 1873:	Data_Registers[Par_index]=P_rate;					break;	// P29.3	// kW
		case 1874:	Data_Registers[Par_index]=(int)(10000.*R_L);			break;	// P29.4	// mOhm
		case 1875:	Data_Registers[Par_index]=(int)(1e+4*La);			break;	// P29.5	// mH
		case 1876:	Data_Registers[Par_index]=10*Sens_time_Vin;			break;	// P29.6	// s
		case 1877:	Data_Registers[Par_index]=(int)(10.*Kp_Vdc_factor);	break;	// P29.7	// %
		case 1878:	Data_Registers[Par_index]=(int)(10.*Ki_Vdc_factor);	break;	// P29.8	// %
		case 1879:	Data_Registers[Par_index]=(int)(10.*Kp_Idc_factor);	break;	// P29.9	// %
		case 1880:	Data_Registers[Par_index]=(int)(10.*Ki_Idc_factor);	break;	// P29.10	// %
		case 1881:	Data_Registers[Par_index]=vc_cnt_set;				break;	// P29.11	// 
		case 1882:	Data_Registers[Par_index]=(int)(1e+6*Cin);			break;	// P29.12	// uF
		case 1883:	Data_Registers[Par_index]=(int)(1e+6*Cout);			break;	// P29.13	// uF
		case 1884:	Data_Registers[Par_index]=(int)(10.*Fnv);			break;	// P29.14	// Hz
		case 1885:	Data_Registers[Par_index]=(int)(10.*Fnc);			break;	// P29.15	// Hz
		case 1886:	Data_Registers[Par_index]= OV_set; 					break;	// P29.16	// V
		case 1887:	Data_Registers[Par_index]= UV_set; 					break;	// P29.17	// V
		case 1888:	Data_Registers[Par_index]= OVin_set;				break;	// P29.18	// V
		case 1889:	Data_Registers[Par_index]= UVin_set;				break;	// P29.19	// V
		case 1890:	Data_Registers[Par_index]= I_rate;					break;	// P29.20	// A
		case 1891:	Data_Registers[Par_index]= 10 * OC_Trip;			break;	// P29.21	// %
		case 1892:	Data_Registers[Par_index]= 10 * Max_Con_cur;		break;	// P29.22	// %
		case 1893:	Data_Registers[Par_index]= 10 * Over_Load;			break;	// P29.23	// %
		case 1894:	Data_Registers[Par_index]= 10 * Over_Load_Time;		break;	// P29.24	// s
		case 1895:	Data_Registers[Par_index]= 10 * OV_Time;			break;	// P29.25	// s
		case 1896:	Data_Registers[Par_index]= 10 * OV_Temp;			break;	// P29.26	// C

		case 2301:	Data_Registers[Par_index]=(int)Vdc_set_user;		break;	// M0.1		// V

		default:	Data_Registers[Par_index]=0;
	}
}

