#include "RD_LED_Ctr.h"



RD_Touch_Data    RD_Touch_data1;

unsigned char UART3_Buffer_send[64];
bool vruc_TOUCH1_Stt     = FALSE;
bool vruc_TOUCH2_Stt     = FALSE;
bool vruc_TOUCH3_Stt     = FALSE;
bool vruc_TOUCH4_Stt     = FALSE;
bool vruc_TBAR_Stt       = FALSE;
bool vruc_OnOff_Stt      = FALSE;
volatile char vrsc_Timer4_Flag;
volatile unsigned int  vrui_Timer4_Count;
volatile unsigned int  vrui_Timer3_CountRST;
char vrsc_BAR_Start;

unsigned int vruc_TBAR_Value_old;
unsigned int vruc_TBAR_Value_new;

bool vruc_MODE_Stt = FALSE;
bool vruc_HCL_Stt = FALSE;
bool vruc_Tomato  = FALSE;
unsigned char vruc_OnOff   = FALSE;

volatile uint16_t vruc_DIM;
volatile uint16_t vruc_CCT;

//unsigned int vruc_DIM_PWM = 0;
//unsigned int vruc_CCT_PWM = 0;
unsigned int vrui_PWM_Calculator;
unsigned int vrui_PWM_CCT;
unsigned int vrui_RealWhite;
unsigned int vrui_RealYellow;
unsigned int vrui_RealWhite_old;
unsigned int vrui_RealYellow_old; 

unsigned int Dim_New, Dim_Old;
unsigned int Ctt_New, Ctt_Old;


void RangDong_System_Proc (void){
  Rangdong_Send_datatouch();
  //RangDong_ButtonProcess();
}


void RangDong_LED_OnOff_Control(void){
  TIM2_SetCompare1(0);
  TIM2_SetCompare3(0);
}


void Rangdong_Send_datatouch(void){
  if(UART1_Done){
      UART1_Done = 0;
      RD_Touch_data1.BID = UART1_Buffer[0] - 1;
      RD_Touch_data1.Val = UART1_Buffer[1] - 1;
      RD_Touch_data1.Future[0] = UART1_Buffer[2] - 1;
      RD_Touch_data1.Future[1] = UART1_Buffer[3] - 1;
      RD_Touch_data1.Future[2] = UART1_Buffer[4] - 1;
      RD_Touch_data1.Future[3] = UART1_Buffer[5] - 1;
      RangDong_Data_touch();
    }
}
void RangDong_Data_touch(void){
  int BID = RD_Touch_data1.BID;
  switch(BID){
    case RD_BID_ON_OFF:
      vruc_TOUCH1_Stt = TRUE;
      Fn_UART1_Pustf("B:On/Off\n");
      break;
    case RD_BID_MODE:
      vruc_TOUCH2_Stt = TRUE;
      Fn_UART1_Pustf("B:Mode\n");
      break;
    case RD_BID_HCL:
      vruc_TOUCH3_Stt = TRUE;
      break;
    case RD_BID_TOMATO:
      vruc_TOUCH4_Stt = TRUE;
      break;
    case RD_BID_BAR:
      vruc_TBAR_Stt = TRUE;
      Fn_UART1_Pustf("B:Bar\n");
      vruc_TBAR_Value_new = RD_Touch_data1.Val;
      break;
  }
  RangDong_Stt();
}
void Trans_PWM(){
  if( vruc_OnOff == TRUE){
    
    if(vrui_Timer4_Count >=4)
    {
      vrui_Timer4_Count =0;
      if(Dim_Old != Dim_New)
      {
        if(Dim_Old <Dim_New)
        {
          Dim_Old += 1;
        }   
        
        // DIm giam
        if(Dim_Old > Dim_New)
        {
          Dim_Old -= 1;
        } 
      }
      
      if(Ctt_Old != Ctt_New)
      {
        if(Ctt_Old < Ctt_New)
        {
          Ctt_Old += 1;
        }   
        
        // Ctt giam
        if(Ctt_Old > Ctt_New)
        {
          Ctt_Old -= 1;
        }
      }
    }
    vrui_RealWhite = (unsigned int)(((unsigned long)Dim_Old * (unsigned long)Ctt_Old)/(unsigned long)1000);
    vrui_RealYellow = (unsigned int)(Dim_Old - vrui_RealWhite);
    TIM2_SetCompare1(vrui_RealWhite);
    TIM2_SetCompare3(vrui_RealYellow);
  }

}


void RangDong_PWM_LED(unsigned int _vrui_Dim, unsigned int _vrui_Cct ){
  Fn_UART1_Pustf("Update\n");
  Dim_New = _vrui_Dim;
  Ctt_New = _vrui_Cct;  
  
}
void RangDong_Config(void){
  vruc_OnOff = FALSE;
  vruc_HCL_Stt = FALSE;
  vruc_Tomato  = FALSE;
  vruc_OnOff   = FALSE;
  vruc_TBAR_Value_old = vruc_TBAR_Value_new = 0;
  RangDong_LedBar(0);
  GPIO_WriteHigh(LED_ON_OFF_PORT, LED_ON_OFF_PIN);
  GPIO_WriteHigh(LED_MODE_PORT, LED_MODE_PIN);
  GPIO_WriteHigh(LED_HCL_PORT, LED_HCL_PIN);
  GPIO_WriteHigh (LED_TOMATO_PORT, LED_TOMATO_PIN);
  GPIO_WriteHigh(LED_BAR_1_7_PORT, LED_BAR_1_PIN | LED_BAR_2_PIN | LED_BAR_3_PIN | LED_BAR_4_PIN
          | LED_BAR_5_PIN | LED_BAR_6_PIN | LED_BAR_7_PIN);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
  GPIO_WriteHigh(LED_BAR_8_9_PORT, LED_BAR_8_PIN | LED_BAR_9_PIN);
  GPIO_WriteHigh(LED_BAR_10_PORT, LED_BAR_10_PIN);
  vruc_DIM = 500;
  vruc_CCT = 500;
}

void RangDong_Stt(void){
  if(vruc_TOUCH1_Stt == TRUE){
    vruc_TOUCH1_Stt = FALSE;
    vruc_OnOff = !vruc_OnOff;
    vruc_OnOff_Stt = TRUE;
    RD_Touch_data1.BID = 0;
    mcu_dp_bool_update(DPID_SWITCH_LED,vruc_OnOff);
  }
  
  if(vruc_OnOff == TRUE){
    GPIO_WriteLow(LED_ON_OFF_PORT,LED_ON_OFF_PIN);
    Button_Onoff();
    if(vruc_TOUCH2_Stt == TRUE){
       vruc_TOUCH2_Stt = FALSE;
       vruc_MODE_Stt = !vruc_MODE_Stt;
       RD_Touch_data1.BID = 0;
       Button_Mode();
    }
    if(vruc_TOUCH3_Stt == TRUE){
      vruc_TOUCH3_Stt = FALSE;
      vruc_HCL_Stt = !vruc_HCL_Stt;
      RD_Touch_data1.BID = 0;
    }
    if(vruc_TOUCH4_Stt == TRUE){
      vruc_TOUCH4_Stt = FALSE;
      vruc_Tomato = !vruc_Tomato;
      RD_Touch_data1.BID = 0;
    }
    if(vruc_TBAR_Stt == TRUE){
      vruc_TBAR_Stt = FALSE;
      RD_Touch_data1.BID = 0;
      RangDong_touch_PWM();
    }
  }
  else {
    vruc_TOUCH2_Stt = FALSE;
    vruc_TOUCH3_Stt = FALSE;
    vruc_TOUCH4_Stt = FALSE;
    vruc_TBAR_Stt = FALSE;
    vruc_OnOff_Stt = FALSE;
    GPIO_WriteHigh(LED_ON_OFF_PORT,LED_ON_OFF_PIN);
    GPIO_WriteHigh(LED_MODE_PORT,LED_MODE_PIN);
    GPIO_WriteHigh(LED_HCL_PORT, LED_HCL_PIN);
    GPIO_WriteHigh(LED_TOMATO_PORT, LED_TOMATO_PIN);
    RangDong_LedBar(0);
//    RangDong_PWM_LED(0,0);
//    Dim_Old = 1;
//    Ctt_Old = 1;
    RangDong_LED_OnOff_Control();
  }
  
}

void RangDong_LedBar(unsigned int _LedBar){
  _LedBar = _LedBar/10;
  if( _LedBar < 1){
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_1_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_2_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_3_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_4_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_5_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_6_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_7_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_8_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_9_PIN);
    GPIO_WriteHigh(LED_BAR_10_PORT,LED_BAR_10_PIN);
  }
  else if(1<=_LedBar && _LedBar <=10){
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_1_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_2_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_3_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_4_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_5_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_6_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_7_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_8_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_9_PIN);
    GPIO_WriteHigh(LED_BAR_10_PORT,LED_BAR_10_PIN);
  }
  else if( _LedBar <=20 ){
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_1_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_2_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_3_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_4_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_5_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_6_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_7_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_8_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_9_PIN);
    GPIO_WriteHigh(LED_BAR_10_PORT,LED_BAR_10_PIN);
  }
    else if( _LedBar <=30 ){
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_1_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_2_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_3_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_4_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_5_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_6_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_7_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_8_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_9_PIN);
    GPIO_WriteHigh(LED_BAR_10_PORT,LED_BAR_10_PIN);
  }
    else if( _LedBar <=40 ){
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_1_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_2_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_3_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_4_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_5_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_6_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_7_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_8_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_9_PIN);
    GPIO_WriteHigh(LED_BAR_10_PORT,LED_BAR_10_PIN);
  }
    else if( _LedBar <=50 ){
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_1_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_2_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_3_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_4_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_5_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_6_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_7_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_8_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_9_PIN);
    GPIO_WriteHigh(LED_BAR_10_PORT,LED_BAR_10_PIN);
  }
    else if( _LedBar <=60 ){
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_1_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_2_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_3_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_4_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_5_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_6_PIN);
    GPIO_WriteHigh(LED_BAR_1_7_PORT,LED_BAR_7_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_8_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_9_PIN);
    GPIO_WriteHigh(LED_BAR_10_PORT,LED_BAR_10_PIN);
  }
    else if( _LedBar <=70 ){
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_1_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_2_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_3_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_4_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_5_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_6_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_7_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_8_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_9_PIN);
    GPIO_WriteHigh(LED_BAR_10_PORT,LED_BAR_10_PIN);
  }
    else if( _LedBar <=80 ){
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_1_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_2_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_3_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_4_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_5_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_6_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_7_PIN);
    GPIO_WriteLow(LED_BAR_8_9_PORT,LED_BAR_8_PIN);
    GPIO_WriteHigh(LED_BAR_8_9_PORT,LED_BAR_9_PIN);
    GPIO_WriteHigh(LED_BAR_10_PORT,LED_BAR_10_PIN);
  }
    else if( _LedBar <=90 ){
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_1_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_2_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_3_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_4_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_5_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_6_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_7_PIN);
    GPIO_WriteLow(LED_BAR_8_9_PORT,LED_BAR_8_PIN);
    GPIO_WriteLow(LED_BAR_8_9_PORT,LED_BAR_9_PIN);
    GPIO_WriteHigh(LED_BAR_10_PORT,LED_BAR_10_PIN);
  }
    else if( _LedBar <=100 ){
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_1_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_2_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_3_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_4_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_5_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_6_PIN);
    GPIO_WriteLow(LED_BAR_1_7_PORT,LED_BAR_7_PIN);
    GPIO_WriteLow(LED_BAR_8_9_PORT,LED_BAR_8_PIN);
    GPIO_WriteLow(LED_BAR_8_9_PORT,LED_BAR_9_PIN);
    GPIO_WriteLow(LED_BAR_10_PORT,LED_BAR_10_PIN);
  }  
}





