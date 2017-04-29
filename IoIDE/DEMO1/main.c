#include "stm32f10x.h"


//*****************************************************************************

static u8  fac_us=0;
static u16 fac_ms=0;

void LED_Init(void)   // LED初始化
{

 GPIO_InitTypeDef  GPIO_InitStructure;

 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);	 //

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PB.5
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //
 GPIO_SetBits(GPIOA,GPIO_Pin_8);						 //PB.5

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2
 GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //
 GPIO_SetBits(GPIOD,GPIO_Pin_2); 						 //
}


void delay_init() //延时初始化
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	fac_us=SystemCoreClock/8000000;
	fac_ms=(u16)fac_us*1000;

}

void delay_ms(u16 nms) // 延时毫秒
{
	u32 temp;
	SysTick->LOAD=(u32)nms*fac_ms;
	SysTick->VAL =0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL =0X00;
}

int main(void)
{
	delay_init();       //初始化延时函数
	LED_Init();		  	//初始化LED函数
		while(1)
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_8);	 // PA.8 --> LED0
			GPIO_SetBits(GPIOD,GPIO_Pin_2);  	//  PD.2 --> LED1
			delay_ms(300);
			GPIO_SetBits(GPIOA,GPIO_Pin_8);		//LED0Êä³ö¸ß
			GPIO_ResetBits(GPIOD,GPIO_Pin_2);	//LED1Êä³öµÍ
			delay_ms(300);
		}
}

