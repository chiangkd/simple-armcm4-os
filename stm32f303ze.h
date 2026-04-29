#ifndef _STM32F303ZE_H_
#define _STM32F303ZE_H_
#include <stdint.h>
#include <stddef.h>

#define __WEAK __attribute__((weak))

#define REG_TYPE    volatile uint32_t

/**
 * Arm Cortex Mx Processor Specific Register
 */

// NVIC
#define NVIC_ISER0          (volatile uint32_t *) 0xE000E100
#define NVIC_ISER1          (volatile uint32_t *) 0xE000E104
#define NVIC_ISER2          (volatile uint32_t *) 0xE000E108
#define NVIC_ISER3          (volatile uint32_t *) 0xE000E10C
#define NVIC_ISER4          (volatile uint32_t *) 0xE000E110
#define NVIC_ISER5          (volatile uint32_t *) 0xE000E104
#define NVIC_ISER6          (volatile uint32_t *) 0xE000E108
#define NVIC_ISER7          (volatile uint32_t *) 0xE000E11C

#define NVIC_ICER0          (volatile uint32_t *) 0xE000E180
#define NVIC_ICER1          (volatile uint32_t *) 0xE000E184
#define NVIC_ICER2          (volatile uint32_t *) 0xE000E188
#define NVIC_ICER3          (volatile uint32_t *) 0xE000E18C
#define NVIC_ICER4          (volatile uint32_t *) 0xE000E190
#define NVIC_ICER5          (volatile uint32_t *) 0xE000E194
#define NVIC_ICER6          (volatile uint32_t *) 0xE000E198
#define NVIC_ICER7          (volatile uint32_t *) 0xE000E19C

#define NVIC_IPR_BASE_ADDR    (volatile uint32_t *) 0xE000E400  // Interrupt priority register
#define NO_PRIOR_BITS_IMPLEMETED    4
/**
 * AHBx and APBx Bus Peripheral base address
 */
#define PERIPHERAL_BASE     0x40000000U
#define APB1BUS_BASEADDR    0x40000000U
#define APB2BUS_BASEADDR    0x40010000U
#define AHB1BUS_BASEADDR    0x40020000U
#define AHB2BUS_BASEADDR    0x48000000U
#define AHB3BUS_BASEADDR    0x50000000U
#define AHB4BUS_BASEADDR    0x60000000U

/**
 * Peripherals
 */

// AHB1
#define DMA1_BASEADDR       (AHB1BUS_BASEADDR + 0x0000)
#define DMA2_BASEADDR       (AHB1BUS_BASEADDR + 0x0400)
#define RCC_BASEADDR        (AHB1BUS_BASEADDR + 0x1000)
#define FLASHIF_BASEADDR    (AHB1BUS_BASEADDR + 0x2000)
#define CRC_BASEADDR        (AHB1BUS_BASEADDR + 0x3000)
#define TSC_BASEADDR        (AHB1BUS_BASEADDR + 0x4000)

// AHB2
#define GPIOA_BASEADDR      (AHB2BUS_BASEADDR + 0x0000)
#define GPIOB_BASEADDR      (AHB2BUS_BASEADDR + 0x0400)
#define GPIOC_BASEADDR      (AHB2BUS_BASEADDR + 0x0800)
#define GPIOD_BASEADDR      (AHB2BUS_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR      (AHB2BUS_BASEADDR + 0x1000)
#define GPIOF_BASEADDR      (AHB2BUS_BASEADDR + 0x1400)
#define GPIOG_BASEADDR      (AHB2BUS_BASEADDR + 0x1800)
#define GPIOH_BASEADDR      (AHB2BUS_BASEADDR + 0x1C00)

typedef enum {
    GPIOA = 0x1,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    GPIOF,
    GPIOG,
    GPIOH,
} GPIO_ID;

// AHB3
#define ADC_1_2_BASEADDR    (AHB3BUS_BASEADDR + 0x0000)     
#define ADC_3_4_BASEADDR    (AHB3BUS_BASEADDR + 0x0400)

// AHB4
#define FMCBANK_1_2_BASEADDR    (AHB4BUS_BASEADDR + 0x0000)
#define FMCBANK_3_4_BASEADDR    (AHB4BUS_BASEADDR + 0x20000400)
#define FMCCTL_BASEADDR         (AHB4BUS_BASEADDR + 0x40000400)

// APB1
#define TIM2_BASEADDR       (APB1BUS_BASEADDR + 0x0000)
#define TIM3_BASEADDR       (APB1BUS_BASEADDR + 0x0400)
#define TIM4_BASEADDR       (APB1BUS_BASEADDR + 0x0800)
#define TIM6_BASEADDR       (APB1BUS_BASEADDR + 0x1000)
#define TIM7_BASEADDR       (APB1BUS_BASEADDR + 0x1400)
#define RTC_BASEADDR        (APB1BUS_BASEADDR + 0x2800)
#define WWDG_BASEADDR       (APB1BUS_BASEADDR + 0x2C00)
#define IWDG_BASEADDR       (APB1BUS_BASEADDR + 0x3000)
#define I2S2EXT_BASEADDR    (APB1BUS_BASEADDR + 0x4000)
#define SPI2_I2S2_BASEADDR  (APB1BUS_BASEADDR + 0x3800)
#define SPI3_I2S3_BASEADDR  (APB1BUS_BASEADDR + 0x3C00)
#define I2S3EXT_BASEADDR    (APB1BUS_BASEADDR + 0x4000)
#define USART2_BASEADDR     (APB1BUS_BASEADDR + 0x4400)
#define USART3_BASEADDR     (APB1BUS_BASEADDR + 0x4800)
#define UART4_BASEADDR      (APB1BUS_BASEADDR + 0x4C00)
#define UART5_BASEADDR      (APB1BUS_BASEADDR + 0x5000)
#define I2C1_BASEADDR       (APB1BUS_BASEADDR + 0x5400)
#define I2C2_BASEADDR       (APB1BUS_BASEADDR + 0x5800)
#define USB_DEV_FS_BASEADDR (APB1BUS_BASEADDR + 0x5C00)
#define USB_CAN_SRAM_BASEADDR (APB1BUS_BASEADDR + 0x6000)
#define BXCAB_BASEADDR      (APB1BUS_BASEADDR + 0x6400)
#define PWR_BASEADDR        (APB1BUS_BASEADDR + 0x7000)
#define DAC1_BASEADDR       (APB1BUS_BASEADDR + 0x7400)
#define I2C3_BASEADDR       (APB1BUS_BASEADDR + 0x7800)

// APB2
#define SYSCFG_COMP_OPAMP_BASEADDR  (APB2BUS_BASEADDR + 0x0000)
#define EXTI_BASEADDR               (APB2BUS_BASEADDR + 0x0400)
#define TIM1_BASEADDR               (APB2BUS_BASEADDR + 0x2C00)
#define SPI1_BASEADDR               (APB2BUS_BASEADDR + 0x3000)
#define TIM8_BASEADDR               (APB2BUS_BASEADDR + 0x3400)
#define USART1_BASEADDR             (APB2BUS_BASEADDR + 0x3800)
#define SPI4_BASEADDR               (APB2BUS_BASEADDR + 0x3C00)
#define TIM15_BASEADDR              (APB2BUS_BASEADDR + 0x4000)
#define TIM16_BASEADDR              (APB2BUS_BASEADDR + 0x4400)
#define TIM17_BASEADDR              (APB2BUS_BASEADDR + 0x4800)
#define TIM20_BASEADDR              (APB2BUS_BASEADDR + 0x5000)

// IRQ vector list for STM32F303ZE (Peripheral IRQ only)
#define IRQ_VECTOR          \
    _(WWDG,                0)   \
    _(PVD,                 1)   \
    _(TAMPER_STAMP,        2)   \
    _(RTC_WKUP,            3)   \
    _(FLASH,               4)   \
    _(RCC,                 5)   \
    _(EXTI0,               6)   \
    _(EXTI1,               7)   \
    _(EXTI2_TSC,           8)   \
    _(EXTI3,               9)   \
    _(EXTI4,               10)  \
    _(DMA1_Stream0,        11)  \
    _(DMA1_Stream1,        12)  \
    _(DMA1_Stream2,        13)  \
    _(DMA1_Stream3,        14)  \
    _(DMA1_Stream4,        15)  \
    _(DMA1_Stream5,        16)  \
    _(DMA1_Stream6,        17)  \
    _(ADC,                 18)  \
    _(FDCAN1_IT0,          19)  \
    _(FDCAN1_IT1,          20)  \
    _(EXTI9_5,             23)  \
    _(TIM1_BRK_TIM15,      24)  \
    _(TIM1_UP_TIM16,       25)  \
    _(TIM1_TRG_COM,        26)  \
    _(TIM1_CC,             27)  \
    _(TIM2,                28)  \
    _(TIM3,                29)  \
    _(TIM4,                30)  \
    _(I2C1_EV,             31)  \
    _(I2C1_ER,             32)  \
    _(I2C2_EV,             33)  \
    _(I2C2_ER,             34)  \
    _(SPI1,                35)  \
    _(SPI2,                36)  \
    _(USART1,              37)  \
    _(USART2,              38)  \
    _(USART3,              39)  \
    _(EXTI15_10,           40)  \
    _(RTC_Alarm,           41)  \
    _(OTG_FS,              42)  \
    _(DMA2_Stream0,        47)  \
    _(DMA2_Stream1,        48)  \
    _(DMA2_Stream2,        49)  \
    _(DMA2_Stream3,        50)  \
    _(DMA2_Stream4,        51)  \
    _(USART4_5,            52)  \
    _(I2C3_EV,             53)  \
    _(I2C3_ER,             54)  \
    _(SPI3,                55)  \
    _(USART6,              56)  \
    _(SPI4,                57)  \
    _(OCTOSPI1,            58)  \
    _(OCTOSPI2,            59)  \
    _(RNG,                 60)  \
    _(FPU,                 61)

typedef enum {
#define _(name, num) IRQ_NO_##name = (num),
    IRQ_VECTOR
#undef _
} IRQ_NO_T;



// RCC registers
typedef struct {
    volatile uint32_t cr;        /** Clock control register */
    volatile uint32_t cfgr;      /** Clock configuration register */
    volatile uint32_t cir;       /** Clock interrupt register */
    volatile uint32_t apb2rstr;  /** APB2 peripheral reset register */
    volatile uint32_t apb1rstr;  /** APB1 peripheral reset register */
    volatile uint32_t ahbenr;    /** AHB peripheral clock enable register */
    volatile uint32_t apb2enr;   /** APB2 peripheral clock enable register */
    volatile uint32_t apb1enr;   /** APB1 peripheral clock enable register */
    volatile uint32_t bdcr;      /** RTC domain control register */
    volatile uint32_t csr;       /** Control/status register */
    volatile uint32_t ahbrstr;   /** AHB peripheral reset register */
    volatile uint32_t cfg2r;     /** Clock configuration register 2 */
    volatile uint32_t cfgrs;     /** Clock configuration register 3 */
} RCC_REG_T;

#define RCC ((RCC_REG_T *)RCC_BASEADDR)

#define RCC_AHBENR_CTL          \
    _(ahbenr, DMA1, 0)          \
    _(ahbenr, DMA2, 1)          \
    _(ahbenr, SRAM, 2)          \
    _(ahbenr, FLITF, 4)         \
    _(ahbenr, FMC, 5)           \
    _(ahbenr, CRC, 6)           \
    _(ahbenr, GPIOH, 16)        \
    _(ahbenr, GPIOA, 17)        \
    _(ahbenr, GPIOB, 18)        \
    _(ahbenr, GPIOC, 19)        \
    _(ahbenr, GPIOD, 20)        \
    _(ahbenr, GPIOE, 21)        \
    _(ahbenr, GPIOF, 22)        \
    _(ahbenr, GPIOG, 23)        \
    _(ahbenr, TSCEN, 24)        \
    _(ahbenr, ADC12, 28)        \
    _(ahbenr, ADC34, 29)        

#define RCC_APB1ENR_CTL         \
    _(apb1enr, TIM2, 0)         \
    _(apb1enr, TIM3, 1)         \
    _(apb1enr, TIM4, 2)         \
    _(apb1enr, TIM6, 4)         \
    _(apb1enr, TIM7, 5)         \
    _(apb1enr, WWDG, 11)        \
    _(apb1enr, SPI2, 14)        \
    _(apb1enr, SPI3, 15)        \
    _(apb1enr, USART2, 17)      \
    _(apb1enr, USART3, 18)      \
    _(apb1enr, UART4, 19)       \
    _(apb1enr, UART5, 20)       \
    _(apb1enr, I2C1, 21)        \
    _(apb1enr, I2C2, 22)        \
    _(apb1enr, USB, 23)         \
    _(apb1enr, CAN, 25)         \
    _(apb1enr, DAC2, 26)        \
    _(apb1enr, PWR, 28)         \
    _(apb1enr, DAC1, 29)        \
    _(apb1enr, I2C3, 30)         

#define RCC_APB2ENR_CTL         \
    _(apb2enr, SYSCFG, 0)       \
    _(apb2enr, TIM1, 11)        \
    _(apb2enr, SPI1, 12)        \
    _(apb2enr, TIM8, 13)        \
    _(apb2enr, USART1, 14)      \
    _(apb2enr, SPI4, 15)        \
    _(apb2enr, TIM15, 16)       \
    _(apb2enr, TIM16, 17)       \
    _(apb2enr, TIM17, 18)       \
    _(apb2enr, TIM20, 20)

/** Define PCLOCK enable / disable macro */
#define _(reg, name, bit)                                                   \
    static inline void name##_PCLK_EN(void) { RCC->reg |= (1 << bit); }     \
    static inline void name##_PCLK_DIS(void) { RCC->reg &= ~(1 << bit); }

RCC_AHBENR_CTL
RCC_APB1ENR_CTL
RCC_APB2ENR_CTL
#undef _

#define RCC_AHBRSTR_CTL         \
    _(ahbrstr, FMCR, 5)         \
    _(ahbrstr, GPIOH, 16)       \
    _(ahbrstr, GPIOA, 17)       \
    _(ahbrstr, GPIOB, 18)       \
    _(ahbrstr, GPIOC, 19)       \
    _(ahbrstr, GPIOD, 20)       \
    _(ahbrstr, GPIOE, 21)       \
    _(ahbrstr, GPIOF, 22)       \
    _(ahbrstr, GPIOG, 23)       \
    _(ahbrstr, TSC, 24)         \
    _(ahbrstr, ADC12, 28)       \
    _(ahbrstr, ADC34, 29)

#define RCC_APB1RSTR_CTL        \
    _(apb1rstr, TIM2, 0)        \
    _(apb1rstr, TIM3, 1)        \
    _(apb1rstr, TIM4, 2)        \
    _(apb1rstr, TIM6, 4)        \
    _(apb1rstr, TIM7, 5)        \
    _(apb1rstr, WWDG, 11)       \
    _(apb1rstr, SPI2, 14)       \
    _(apb1rstr, SPI3, 15)       \
    _(apb1rstr, USART2, 17)     \
    _(apb1rstr, USART3, 18)     \
    _(apb1rstr, UART4, 19)      \
    _(apb1rstr, UART5, 20)      \
    _(apb1rstr, I2C1, 21)       \
    _(apb1rstr, I2C2, 22)       \
    _(apb1rstr, USB, 23)        \
    _(apb1rstr, CAN, 25)        \
    _(apb1rstr, DAC2, 26)       \
    _(apb1rstr, PWR, 28)        \
    _(apb1rstr, DAC1, 29)       \
    _(apb1rstr, I2C3, 30)         

#define RCC_APB2RSTR_CTL        \
    _(apb2rstr, SYSCFG, 0)      \
    _(apb2rstr, TIM1, 11)       \
    _(apb2rstr, SPI1, 12)       \
    _(apb2rstr, TIM8, 13)       \
    _(apb2rstr, USART1, 14)     \
    _(apb2rstr, SPI4, 15)       \
    _(apb2rstr, TIM15, 16)      \
    _(apb2rstr, TIM16, 17)      \
    _(apb2rstr, TIM17, 18)      \
    _(apb2rstr, TIM20, 20)

#define _(reg, name, bit)   \
    static inline void name##_REG_RST(void) {RCC->reg |= (1 << bit); RCC->reg &= ~(1 << bit);}
RCC_AHBRSTR_CTL
RCC_APB1RSTR_CTL
RCC_APB2RSTR_CTL
#undef _



#endif