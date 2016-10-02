//#include	<All_Header.h>
//#include	<All_Extern_Variables.h> 
#include "sci_bc.h"
#include "main_def.h"

void Read_Data_Registers(int Parameter_index)
{
	switch(Parameter_index)
	{
		case 200 :	Device_Info=				Data_Registers[Parameter_index];	break;
		case 201 :	Software_Number=			Data_Registers[Parameter_index];	break;
		case 202 :	Software_Version=			Data_Registers[Parameter_index];	break; 

		case 280 :	Run_Stop_Src=				Data_Registers[Parameter_index];	break;
		case 281 :	Ref_method=					Data_Registers[Parameter_index];	break;

		case 940:	AO1.P00_Output_selection= 	Data_Registers[Parameter_index];	break;			
		case 941:	AO1.P01_Type= 				Data_Registers[Parameter_index];	break;
		case 942:	AO1.P02_Adjustment_0mA= 	Data_Registers[Parameter_index];	break;
		case 943:	AO1.P03_Adjustment_4mA= 	Data_Registers[Parameter_index];	break;
		case 944:	AO1.P04_Adjustment_20mA= 	Data_Registers[Parameter_index];	break;
		case 945:	AO1.P05_Max_output_x1000= 	Data_Registers[Parameter_index];	break;			
		case 946:	AO1.P06_Inversion= 			Data_Registers[Parameter_index];	break;				
		case 947:	AO2.P00_Output_selection= 	Data_Registers[Parameter_index];	break;			
		case 948:	AO2.P01_Type= 				Data_Registers[Parameter_index];	break;
		case 949:	AO2.P02_Adjustment_0mA= 	Data_Registers[Parameter_index];	break;
		case 950:	AO2.P03_Adjustment_4mA= 	Data_Registers[Parameter_index];	break;
		case 951:	AO2.P04_Adjustment_20mA=	Data_Registers[Parameter_index];	break;
		case 952:	AO2.P05_Max_output_x1000= 	Data_Registers[Parameter_index];	break;
		case 953:	AO2.P06_Inversion= 			Data_Registers[Parameter_index];	break;	

		case 1870:	Fsw= 			1e+2*(float)(Data_Registers[Parameter_index]);	break;
		case 2301:	Vdc_set_user=		(float)(Data_Registers[Parameter_index]);	break;
		case 1872:	V_rate= 					Data_Registers[Parameter_index];	break;
		case 1873:	P_rate= 					Data_Registers[Parameter_index];	break;
		case 1874:	R_L=			1e-4*(float)(Data_Registers[Parameter_index]);	break;
		case 1875:	La=				1e-4*(float)(Data_Registers[Parameter_index]);	break;
		case 1876:	Sens_time_Vin=	1e-1*		Data_Registers[Parameter_index];	break;
		case 1877:	Kp_Vdc_factor= 	1e-1*(float)(Data_Registers[Parameter_index]);	break;
		case 1878:	Ki_Vdc_factor=	1e-1*(float)(Data_Registers[Parameter_index]);	break;
		case 1879:	Kp_Idc_factor= 	1e-1*(float)(Data_Registers[Parameter_index]);	break;
		case 1880:	Ki_Idc_factor=	1e-1*(float)(Data_Registers[Parameter_index]);	break; 
		case 1881:	vc_cnt_set=					Data_Registers[Parameter_index];	break;

		case 1882:	Cin=			1e-6*(float)(Data_Registers[Parameter_index]);	break;
		case 1883:	Cout=			1e-6*(float)(Data_Registers[Parameter_index]);	break;

		case 1884:	Fnv=			1e-1*(float)(Data_Registers[Parameter_index]);	break;
		case 1885:	Fnc=			1e-1*(float)(Data_Registers[Parameter_index]);	break;

		case 1886:	OV_set= 					Data_Registers[Parameter_index];	break;
		case 1887:	UV_set= 					Data_Registers[Parameter_index];	break;
		case 1888:	OVin_set=					Data_Registers[Parameter_index];	break;
		case 1889:	UVin_set=					Data_Registers[Parameter_index];	break;
		case 1890:	I_rate=						Data_Registers[Parameter_index];	break;
		case 1891:	OC_Trip=		1e-1*		Data_Registers[Parameter_index];	break;
		case 1892:	Max_Con_cur=	1e-1*		Data_Registers[Parameter_index];	break;
		case 1893:	Over_Load=		1e-1*		Data_Registers[Parameter_index];	break;
		case 1894:	Over_Load_Time=	1e-1*		Data_Registers[Parameter_index];	break;
		case 1895:	OV_Time=		1e-1*		Data_Registers[Parameter_index];	break;

		case 1896:	OV_Temp=		1e-1*		Data_Registers[Parameter_index];	break;
		case 1897:	Fnv_max=		1e-1*		Data_Registers[Parameter_index];	break;
		case 1898:	Fnv_min=		1e-1*		Data_Registers[Parameter_index];	break;
		case 1899:	Fnc_max=		1e-1*		Data_Registers[Parameter_index];	break;
		case 1900:	Fnc_min=		1e-1*		Data_Registers[Parameter_index];	break;
		
		case 2300:	Local_Remote=				Data_Registers[Parameter_index];	break;
		case 2306:	Run_Stop=					Data_Registers[Parameter_index];	break;
		case 2484:	FAULT_RESET=				Data_Registers[Parameter_index];	break;
	}
}

void Write_Data_Registers_Online()
{
	Data_Registers[2270]=					Run_Stop_Status;

	Data_Registers[2300]=					Local_Remote;
	Data_Registers[2301]= 					(int)Vdc_set_user;
	Data_Registers[2306]=					Run_Stop;
	Data_Registers[2310]= 					(int)Vdc_input_LPF;

	Data_Registers[2311]=		Under_Limit((int)Iinput_LPF);

	Data_Registers[2312]=					(int)Vdc_out_LPF;

	Data_Registers[2313]=		Under_Limit((int)Ias_LPF);

	Data_Registers[2314]=		Under_Limit((int)Ibs_LPF);

	Data_Registers[2315]= 		Under_Limit((int)Ics_LPF);

	Data_Registers[2316]=		Under_Limit((int)Idc_ref_LPF);
	Data_Registers[2317]=					(int)Vdc_Error;
	Data_Registers[2318]=		Under_Limit((int)(1e-2*Power_in));
	Data_Registers[2319]=		Under_Limit((int)(1e-2*Power_out));

	Data_Registers[2320]=					(int)Idc_Error_a;
	Data_Registers[2321]=					(int)Idc_Error_b;
	Data_Registers[2322]=					(int)Idc_Error_c;
	Data_Registers[2323]=					(int)(10.*Temperature);
	Data_Registers[2330]=					State_Index;

	Data_Registers[2352]=					Run_Stop_Src;	// M1.2.2
	Data_Registers[2353]=					Ref_method;		// M1.2.3
	Data_Registers[2354]=					P_rate;			// M1.2.4
	Data_Registers[2355]=					Drive_Voltage;	// M1.2.5

	
	Data_Registers[2376]=					point.Fault1.all;
	Data_Registers[2377]=					point.Fault2.all;
	Data_Registers[2379]= 					Fault_count;
	Data_Registers[2484]=					FAULT_RESET;
	Data_Registers[2485]=					FAULT_RESET_COMPLETE;
	Data_Registers[1871]=					(int)(Vdc_set_user);
	Data_Registers[1870]=					(int)(1e-2*Fsw);	// kHz
}

void Write_Data_Registers_Offline(int Parameter_index)
{
	switch(Parameter_index)
	{
		case 200 :	Data_Registers[Parameter_index]=Device_Info;				break;
		case 201 :	Data_Registers[Parameter_index]=Software_Number;			break;
		case 202 :	Data_Registers[Parameter_index]=Software_Version;			break; 
		case 280 :	Data_Registers[Parameter_index]=Run_Stop_Src;				break;
		case 281 :	Data_Registers[Parameter_index]=Ref_method;					break;

		case 940:	Data_Registers[Parameter_index]=AO1.P00_Output_selection; 	break;			
		case 941:	Data_Registers[Parameter_index]=AO1.P01_Type; 				break;
		case 942:	Data_Registers[Parameter_index]=AO1.P02_Adjustment_0mA; 	break;
		case 943:	Data_Registers[Parameter_index]=AO1.P03_Adjustment_4mA; 	break;
		case 944:	Data_Registers[Parameter_index]=AO1.P04_Adjustment_20mA; 	break;
		case 945:	Data_Registers[Parameter_index]=AO1.P05_Max_output_x1000; 	break;			
		case 946:	Data_Registers[Parameter_index]=AO1.P06_Inversion; 			break;				
		case 947:	Data_Registers[Parameter_index]=AO2.P00_Output_selection; 	break;			
		case 948:	Data_Registers[Parameter_index]=AO2.P01_Type; 				break;
		case 949:	Data_Registers[Parameter_index]=AO2.P02_Adjustment_0mA; 	break;
		case 950:	Data_Registers[Parameter_index]=AO2.P03_Adjustment_4mA; 	break;
		case 951:	Data_Registers[Parameter_index]=AO2.P04_Adjustment_20mA;	break;
		case 952:	Data_Registers[Parameter_index]=AO2.P05_Max_output_x1000; 	break;
		case 953:	Data_Registers[Parameter_index]=AO2.P06_Inversion; 			break;	

		case 2351:	Data_Registers[Parameter_index]=Control_method;				break;
		case 2354:	Data_Registers[Parameter_index]=P_rate;						break;
		case 2355:	Data_Registers[Parameter_index]=Drive_Voltage;				break;

		case 1870:	Data_Registers[Parameter_index]=(int)(1e-2*Fsw);			break;	// kHz
		case 1871:	Data_Registers[Parameter_index]=(int)(Vdc_set_user);		break;	// kHz
		case 2301:	Data_Registers[Parameter_index]=(int)Vdc_set_user;			break;	// V
		case 1872:	Data_Registers[Parameter_index]=V_rate;						break;	// V
		case 1873:	Data_Registers[Parameter_index]=P_rate;						break;	// kW
		case 1874:	Data_Registers[Parameter_index]=(int)(1e+4*R_L);			break;	// mOhm
		case 1875:	Data_Registers[Parameter_index]=(int)(1e+4*La);				break;	// mH
		case 1876:	Data_Registers[Parameter_index]=10*Sens_time_Vin;			break;	// s
		case 1877:	Data_Registers[Parameter_index]=(int)(10.*Kp_Vdc_factor);	break;	// %
		case 1878:	Data_Registers[Parameter_index]=(int)(10.*Ki_Vdc_factor);	break;	// %
		case 1879:	Data_Registers[Parameter_index]=(int)(10.*Kp_Idc_factor);	break;	// %
		case 1880:	Data_Registers[Parameter_index]=(int)(10.*Ki_Idc_factor);	break; 	// %
		case 1881:	Data_Registers[Parameter_index]=vc_cnt_set;					break;	// 
		case 1882:	Data_Registers[Parameter_index]=(int)(1e+6*Cin);			break;	// uF
		case 1883:	Data_Registers[Parameter_index]=(int)(1e+6*Cout);			break;	// uF
		case 1884:	Data_Registers[Parameter_index]=(int)(10.*Fnv);				break;	// Hz
		case 1885:	Data_Registers[Parameter_index]=(int)(10.*Fnc);				break;	// Hz

		case 1886:	Data_Registers[Parameter_index]= OV_set; 					break;	// V
		case 1887:	Data_Registers[Parameter_index]= UV_set; 					break;	// V
		case 1888:	Data_Registers[Parameter_index]= OVin_set;					break;	// V
		case 1889:	Data_Registers[Parameter_index]= UVin_set;					break;	// V
		case 1890:	Data_Registers[Parameter_index]= I_rate;					break;	// A
		case 1891:	Data_Registers[Parameter_index]= 10 * OC_Trip;				break;	// %
		case 1892:	Data_Registers[Parameter_index]= 10 * Max_Con_cur;			break;	// %
		case 1893:	Data_Registers[Parameter_index]= 10 * Over_Load;			break;	// %
		case 1894:	Data_Registers[Parameter_index]= 10 * Over_Load_Time;		break;	// s
		case 1895:	Data_Registers[Parameter_index]= 10 * OV_Time;				break;	// s
		case 1896:	Data_Registers[Parameter_index]= 10 * OV_Temp;				break;	// C
		default:	Data_Registers[Parameter_index]=0;
	}
}

