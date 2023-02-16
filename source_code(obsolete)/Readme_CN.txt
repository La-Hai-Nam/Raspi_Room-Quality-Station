/*****************************************************************************
* | File      	:   Readme_CN.txt
* | Author      :   Waveshare team
* | Function    :   Help with use
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-08-28
* | Info        :   �������ṩһ�����İ汾��ʹ���ĵ����Ա���Ŀ���ʹ��
******************************************************************************/
����ļ��ǰ�����ʹ�ñ����̡�
����oled�oled��Խ��Խ�࣬������oled�ά������˰����е�oled��������һ�����̡�
��������Ե����������̵�ʹ�ã�

1.������Ϣ��
�����̻�����ݮ��4B+�����ģ��ں˰汾
	Linux raspberrypi 5.4.51-v7l+ #1333 SMP Mon Aug 10 16:51:40 BST 2020 armv7l GNU/Linux
�����̿����ڹ��̵�examples\�в鿴��Ӧ�Ĳ�������;

2.�ܽ����ӣ�
�ܽ���������Դ�/lib/Config/DEV_Config.h�鿴������Ҳ������һ�Σ�
SPI:
	oled   =>    RPI(BCM)
	VCC    ->    3.3
	GND    ->    GND
	DIN    ->    10(MOSI)
	CLK    ->    11(SCLK)
	CS     ->    8
	DC     ->    25
	RST    ->    27

IIC:
	oled   =>    RPI(BCM)
	VCC    ->    3.3
	GND    ->    GND
	DIN    ->    2(SDA)
	CLK    ->    3(SCL)
	CS     ->    8
	DC     ->    25
	RST    ->    27

3.����ʹ�ã�
���ڱ�������һ���ۺϹ��̣�����ʹ�ö��ԣ��������Ҫ�Ķ��������ݣ�
��ע���㹺��oled�һ���oled��
����1��
    ����㹺��oledinch oled Module (C)����ô����Ŀ¼���룺
		sudo make clean
		sudo make
		sudo ./main 1.3c

����2��
    ����㹺���olednch RGB oled Module����ô����Ŀ¼���룺
		sudo make clean
		sudo make
		sudo ./main 1.5rgb
		
����3��
    ����㹺��oled1inch oled Module��ע�����ڸ�ģ��ֻ��IIC�ӿڣ�������Ĭ����SPI����ҪȥConfig.h���޸ģ�����
		#define USE_SPI_4W 	1
		#define USE_IIC 	0
	�޸ĳɣ�
		#define USE_SPI_4W 	0
		#define USE_IIC 	1
	������Ŀ¼���룺
		sudo make clean
		sudo make
		sudo ./main 0.91
	

4.Ŀ¼�ṹ��ѡ������
����㾭��ʹ�����ǵĲ�Ʒ�������ǵĳ���Ŀ¼�ṹ��ʮ����Ϥ�����ھ���ĺ�����������һ��
������API�ֲᣬ����������ǵ�WIKI�����ػ����ۺ�ͷ���ȡ������򵥽���һ�Σ�
Config\:��Ŀ¼ΪӲ���ӿڲ��ļ�����DEV_Config.c(.h)���Կ����ܶඨ�壬������
    �������ͣ�
        #define UBYTE   uint8_t
        #define UWORD   uint16_t
        #define UDOUBLE uint32_t
	SPI��IIC��ѡ��
		#define USE_SPI_4W 	1
		#define USE_IIC 	0
	IIC��ַ��
		#define IIC_CMD        0X00
		#define IIC_RAM        0X40
    GPIO��д��
		#define oled_CS_0		HAL_GPIO_WritePin(oled_CS_GPIO_Port, oled_CS_Pin, GPIO_PIN_RESET)
		#define oled_CS_1		HAL_GPIO_WritePin(oled_CS_GPIO_Port, oled_CS_Pin, GPIO_PIN_SET)
		#define oled_DC_0		HAL_GPIO_WritePin(oled_DC_GPIO_Port, oled_DC_Pin, GPIO_PIN_RESET)
		#define oled_DC_1		HAL_GPIO_WritePin(oled_DC_GPIO_Port, oled_DC_Pin, GPIO_PIN_SET)
		#define oled_RST_0		HAL_GPIO_WritePin(oled_RST_GPIO_Port, oled_RST_Pin, GPIO_PIN_RESET)
		#define oled_RST_1		HAL_GPIO_WritePin(oled_RST_GPIO_Port, oled_RST_Pin, GPIO_PIN_SET)
    SPI�������ݣ�
        void SPI4W_Write_Byte(UBYTE value);
    IIC�������ݣ�
        void I2C_Write_Byte(UBYTE value, UBYTE Cmd);
    ��ʱ��
        #define DEV_Delay_ms(__xms) HAL_Delay(__xms);
        ע�⣺����ʱ������δʹ��ʾ��������������ֵ
    ģ���ʼ�����˳��Ĵ�����
        UBYTE	System_Init(void);
        void	System_Exit(void);
        ע�⣺1.����oled�ʹ��oledǰ��ʹ����֮��һЩGPIO�Ĵ�����
              
GUI\:��Ŀ¼ΪһЩ������ͼ������������GUI_Paint.c(.h)�У�
    ����ͼ����������ͼ�Ρ���תͼ�Ρ�����ͼ�Ρ��������ص㡢������;
    ���û�ͼ���������㡢�ߡ���Բ�������ַ���Ӣ���ַ������ֵ�;
    ����ʱ����ʾ���ṩһ�����õ���ʾʱ�亯��;
    ������ʾͼƬ���ṩһ����ʾλͼ�ĺ���;
    
Fonts\:ΪһЩ���õ����壺
    Ascii:
        font8: 5*8 
        font12: 7*12
        font16: 11*16 
        font20: 14*20 
        font24: 17*24
    ���ģ�
        font12CN: 16*21 
        font24CN: 32*41
        
oled\:��Ŀ¼oledLED��������;
Examples\:��Ŀ¼oledLED�Ĳ��Գ�����������п��������ʹ�÷���;