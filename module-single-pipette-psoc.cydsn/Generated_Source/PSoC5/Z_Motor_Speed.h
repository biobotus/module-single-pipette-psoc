/*******************************************************************************
* File Name: Z_Motor_Speed.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_Z_Motor_Speed_H)
#define CY_PWM_Z_Motor_Speed_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Z_Motor_Speed_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Z_Motor_Speed_Resolution                     (16u)
#define Z_Motor_Speed_UsingFixedFunction             (0u)
#define Z_Motor_Speed_DeadBandMode                   (0u)
#define Z_Motor_Speed_KillModeMinTime                (0u)
#define Z_Motor_Speed_KillMode                       (0u)
#define Z_Motor_Speed_PWMMode                        (0u)
#define Z_Motor_Speed_PWMModeIsCenterAligned         (0u)
#define Z_Motor_Speed_DeadBandUsed                   (0u)
#define Z_Motor_Speed_DeadBand2_4                    (0u)

#if !defined(Z_Motor_Speed_PWMUDB_genblk8_stsreg__REMOVED)
    #define Z_Motor_Speed_UseStatus                  (0u)
#else
    #define Z_Motor_Speed_UseStatus                  (0u)
#endif /* !defined(Z_Motor_Speed_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Z_Motor_Speed_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Z_Motor_Speed_UseControl                 (1u)
#else
    #define Z_Motor_Speed_UseControl                 (0u)
#endif /* !defined(Z_Motor_Speed_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Z_Motor_Speed_UseOneCompareMode              (1u)
#define Z_Motor_Speed_MinimumKillTime                (1u)
#define Z_Motor_Speed_EnableMode                     (0u)

#define Z_Motor_Speed_CompareMode1SW                 (1u)
#define Z_Motor_Speed_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Z_Motor_Speed__B_PWM__DISABLED 0
#define Z_Motor_Speed__B_PWM__ASYNCHRONOUS 1
#define Z_Motor_Speed__B_PWM__SINGLECYCLE 2
#define Z_Motor_Speed__B_PWM__LATCHED 3
#define Z_Motor_Speed__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Z_Motor_Speed__B_PWM__DBMDISABLED 0
#define Z_Motor_Speed__B_PWM__DBM_2_4_CLOCKS 1
#define Z_Motor_Speed__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Z_Motor_Speed__B_PWM__ONE_OUTPUT 0
#define Z_Motor_Speed__B_PWM__TWO_OUTPUTS 1
#define Z_Motor_Speed__B_PWM__DUAL_EDGE 2
#define Z_Motor_Speed__B_PWM__CENTER_ALIGN 3
#define Z_Motor_Speed__B_PWM__DITHER 5
#define Z_Motor_Speed__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Z_Motor_Speed__B_PWM__LESS_THAN 1
#define Z_Motor_Speed__B_PWM__LESS_THAN_OR_EQUAL 2
#define Z_Motor_Speed__B_PWM__GREATER_THAN 3
#define Z_Motor_Speed__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Z_Motor_Speed__B_PWM__EQUAL 0
#define Z_Motor_Speed__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Z_Motor_Speed_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!Z_Motor_Speed_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!Z_Motor_Speed_PWMModeIsCenterAligned) */
        #if (Z_Motor_Speed_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Z_Motor_Speed_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Z_Motor_Speed_DeadBandMode == Z_Motor_Speed__B_PWM__DBM_256_CLOCKS || \
            Z_Motor_Speed_DeadBandMode == Z_Motor_Speed__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Z_Motor_Speed_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Z_Motor_Speed_KillModeMinTime) */

        /* Backup control register */
        #if(Z_Motor_Speed_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Z_Motor_Speed_UseControl) */

    #endif /* (!Z_Motor_Speed_UsingFixedFunction) */

}Z_Motor_Speed_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Z_Motor_Speed_Start(void) ;
void    Z_Motor_Speed_Stop(void) ;

#if (Z_Motor_Speed_UseStatus || Z_Motor_Speed_UsingFixedFunction)
    void  Z_Motor_Speed_SetInterruptMode(uint8 interruptMode) ;
    uint8 Z_Motor_Speed_ReadStatusRegister(void) ;
#endif /* (Z_Motor_Speed_UseStatus || Z_Motor_Speed_UsingFixedFunction) */

#define Z_Motor_Speed_GetInterruptSource() Z_Motor_Speed_ReadStatusRegister()

#if (Z_Motor_Speed_UseControl)
    uint8 Z_Motor_Speed_ReadControlRegister(void) ;
    void  Z_Motor_Speed_WriteControlRegister(uint8 control)
          ;
#endif /* (Z_Motor_Speed_UseControl) */

#if (Z_Motor_Speed_UseOneCompareMode)
   #if (Z_Motor_Speed_CompareMode1SW)
       void    Z_Motor_Speed_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Z_Motor_Speed_CompareMode1SW) */
#else
    #if (Z_Motor_Speed_CompareMode1SW)
        void    Z_Motor_Speed_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Z_Motor_Speed_CompareMode1SW) */
    #if (Z_Motor_Speed_CompareMode2SW)
        void    Z_Motor_Speed_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Z_Motor_Speed_CompareMode2SW) */
#endif /* (Z_Motor_Speed_UseOneCompareMode) */

#if (!Z_Motor_Speed_UsingFixedFunction)
    uint16   Z_Motor_Speed_ReadCounter(void) ;
    uint16 Z_Motor_Speed_ReadCapture(void) ;

    #if (Z_Motor_Speed_UseStatus)
            void Z_Motor_Speed_ClearFIFO(void) ;
    #endif /* (Z_Motor_Speed_UseStatus) */

    void    Z_Motor_Speed_WriteCounter(uint16 counter)
            ;
#endif /* (!Z_Motor_Speed_UsingFixedFunction) */

void    Z_Motor_Speed_WritePeriod(uint16 period)
        ;
uint16 Z_Motor_Speed_ReadPeriod(void) ;

#if (Z_Motor_Speed_UseOneCompareMode)
    void    Z_Motor_Speed_WriteCompare(uint16 compare)
            ;
    uint16 Z_Motor_Speed_ReadCompare(void) ;
#else
    void    Z_Motor_Speed_WriteCompare1(uint16 compare)
            ;
    uint16 Z_Motor_Speed_ReadCompare1(void) ;
    void    Z_Motor_Speed_WriteCompare2(uint16 compare)
            ;
    uint16 Z_Motor_Speed_ReadCompare2(void) ;
#endif /* (Z_Motor_Speed_UseOneCompareMode) */


#if (Z_Motor_Speed_DeadBandUsed)
    void    Z_Motor_Speed_WriteDeadTime(uint8 deadtime) ;
    uint8   Z_Motor_Speed_ReadDeadTime(void) ;
#endif /* (Z_Motor_Speed_DeadBandUsed) */

#if ( Z_Motor_Speed_KillModeMinTime)
    void Z_Motor_Speed_WriteKillTime(uint8 killtime) ;
    uint8 Z_Motor_Speed_ReadKillTime(void) ;
#endif /* ( Z_Motor_Speed_KillModeMinTime) */

void Z_Motor_Speed_Init(void) ;
void Z_Motor_Speed_Enable(void) ;
void Z_Motor_Speed_Sleep(void) ;
void Z_Motor_Speed_Wakeup(void) ;
void Z_Motor_Speed_SaveConfig(void) ;
void Z_Motor_Speed_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Z_Motor_Speed_INIT_PERIOD_VALUE          (1500u)
#define Z_Motor_Speed_INIT_COMPARE_VALUE1        (750u)
#define Z_Motor_Speed_INIT_COMPARE_VALUE2        (51u)
#define Z_Motor_Speed_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Z_Motor_Speed_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Z_Motor_Speed_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Z_Motor_Speed_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Z_Motor_Speed_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Z_Motor_Speed_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Z_Motor_Speed_CTRL_CMPMODE2_SHIFT)
#define Z_Motor_Speed_DEFAULT_COMPARE1_MODE      (uint8)((uint8)5u <<  Z_Motor_Speed_CTRL_CMPMODE1_SHIFT)
#define Z_Motor_Speed_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Z_Motor_Speed_UsingFixedFunction)
   #define Z_Motor_Speed_PERIOD_LSB              (*(reg16 *) Z_Motor_Speed_PWMHW__PER0)
   #define Z_Motor_Speed_PERIOD_LSB_PTR          ( (reg16 *) Z_Motor_Speed_PWMHW__PER0)
   #define Z_Motor_Speed_COMPARE1_LSB            (*(reg16 *) Z_Motor_Speed_PWMHW__CNT_CMP0)
   #define Z_Motor_Speed_COMPARE1_LSB_PTR        ( (reg16 *) Z_Motor_Speed_PWMHW__CNT_CMP0)
   #define Z_Motor_Speed_COMPARE2_LSB            (0x00u)
   #define Z_Motor_Speed_COMPARE2_LSB_PTR        (0x00u)
   #define Z_Motor_Speed_COUNTER_LSB             (*(reg16 *) Z_Motor_Speed_PWMHW__CNT_CMP0)
   #define Z_Motor_Speed_COUNTER_LSB_PTR         ( (reg16 *) Z_Motor_Speed_PWMHW__CNT_CMP0)
   #define Z_Motor_Speed_CAPTURE_LSB             (*(reg16 *) Z_Motor_Speed_PWMHW__CAP0)
   #define Z_Motor_Speed_CAPTURE_LSB_PTR         ( (reg16 *) Z_Motor_Speed_PWMHW__CAP0)
   #define Z_Motor_Speed_RT1                     (*(reg8 *)  Z_Motor_Speed_PWMHW__RT1)
   #define Z_Motor_Speed_RT1_PTR                 ( (reg8 *)  Z_Motor_Speed_PWMHW__RT1)

#else
   #if (Z_Motor_Speed_Resolution == 8u) /* 8bit - PWM */

       #if(Z_Motor_Speed_PWMModeIsCenterAligned)
           #define Z_Motor_Speed_PERIOD_LSB      (*(reg8 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define Z_Motor_Speed_PERIOD_LSB_PTR  ((reg8 *)   Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define Z_Motor_Speed_PERIOD_LSB      (*(reg8 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define Z_Motor_Speed_PERIOD_LSB_PTR  ((reg8 *)   Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (Z_Motor_Speed_PWMModeIsCenterAligned) */

       #define Z_Motor_Speed_COMPARE1_LSB        (*(reg8 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Z_Motor_Speed_COMPARE1_LSB_PTR    ((reg8 *)   Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Z_Motor_Speed_COMPARE2_LSB        (*(reg8 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Z_Motor_Speed_COMPARE2_LSB_PTR    ((reg8 *)   Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Z_Motor_Speed_COUNTERCAP_LSB      (*(reg8 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Z_Motor_Speed_COUNTERCAP_LSB_PTR  ((reg8 *)   Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Z_Motor_Speed_COUNTER_LSB         (*(reg8 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Z_Motor_Speed_COUNTER_LSB_PTR     ((reg8 *)   Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Z_Motor_Speed_CAPTURE_LSB         (*(reg8 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define Z_Motor_Speed_CAPTURE_LSB_PTR     ((reg8 *)   Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Z_Motor_Speed_PWMModeIsCenterAligned)
               #define Z_Motor_Speed_PERIOD_LSB      (*(reg16 *) Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define Z_Motor_Speed_PERIOD_LSB_PTR  ((reg16 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define Z_Motor_Speed_PERIOD_LSB      (*(reg16 *) Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define Z_Motor_Speed_PERIOD_LSB_PTR  ((reg16 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (Z_Motor_Speed_PWMModeIsCenterAligned) */

            #define Z_Motor_Speed_COMPARE1_LSB       (*(reg16 *) Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Z_Motor_Speed_COMPARE1_LSB_PTR   ((reg16 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Z_Motor_Speed_COMPARE2_LSB       (*(reg16 *) Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Z_Motor_Speed_COMPARE2_LSB_PTR   ((reg16 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Z_Motor_Speed_COUNTERCAP_LSB     (*(reg16 *) Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Z_Motor_Speed_COUNTERCAP_LSB_PTR ((reg16 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Z_Motor_Speed_COUNTER_LSB        (*(reg16 *) Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Z_Motor_Speed_COUNTER_LSB_PTR    ((reg16 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Z_Motor_Speed_CAPTURE_LSB        (*(reg16 *) Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define Z_Motor_Speed_CAPTURE_LSB_PTR    ((reg16 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(Z_Motor_Speed_PWMModeIsCenterAligned)
               #define Z_Motor_Speed_PERIOD_LSB      (*(reg16 *) Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define Z_Motor_Speed_PERIOD_LSB_PTR  ((reg16 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Z_Motor_Speed_PERIOD_LSB      (*(reg16 *) Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define Z_Motor_Speed_PERIOD_LSB_PTR  ((reg16 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Z_Motor_Speed_PWMModeIsCenterAligned) */

            #define Z_Motor_Speed_COMPARE1_LSB       (*(reg16 *) Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Z_Motor_Speed_COMPARE1_LSB_PTR   ((reg16 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Z_Motor_Speed_COMPARE2_LSB       (*(reg16 *) Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Z_Motor_Speed_COMPARE2_LSB_PTR   ((reg16 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Z_Motor_Speed_COUNTERCAP_LSB     (*(reg16 *) Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Z_Motor_Speed_COUNTERCAP_LSB_PTR ((reg16 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Z_Motor_Speed_COUNTER_LSB        (*(reg16 *) Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Z_Motor_Speed_COUNTER_LSB_PTR    ((reg16 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Z_Motor_Speed_CAPTURE_LSB        (*(reg16 *) Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define Z_Motor_Speed_CAPTURE_LSB_PTR    ((reg16 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Z_Motor_Speed_AUX_CONTROLDP1          (*(reg8 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Z_Motor_Speed_AUX_CONTROLDP1_PTR      ((reg8 *)   Z_Motor_Speed_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Z_Motor_Speed_Resolution == 8) */

   #define Z_Motor_Speed_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define Z_Motor_Speed_AUX_CONTROLDP0          (*(reg8 *)  Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Z_Motor_Speed_AUX_CONTROLDP0_PTR      ((reg8 *)   Z_Motor_Speed_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Z_Motor_Speed_UsingFixedFunction) */

#if(Z_Motor_Speed_KillModeMinTime )
    #define Z_Motor_Speed_KILLMODEMINTIME        (*(reg8 *)  Z_Motor_Speed_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Z_Motor_Speed_KILLMODEMINTIME_PTR    ((reg8 *)   Z_Motor_Speed_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Z_Motor_Speed_KillModeMinTime ) */

#if(Z_Motor_Speed_DeadBandMode == Z_Motor_Speed__B_PWM__DBM_256_CLOCKS)
    #define Z_Motor_Speed_DEADBAND_COUNT         (*(reg8 *)  Z_Motor_Speed_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Z_Motor_Speed_DEADBAND_COUNT_PTR     ((reg8 *)   Z_Motor_Speed_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Z_Motor_Speed_DEADBAND_LSB_PTR       ((reg8 *)   Z_Motor_Speed_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Z_Motor_Speed_DEADBAND_LSB           (*(reg8 *)  Z_Motor_Speed_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Z_Motor_Speed_DeadBandMode == Z_Motor_Speed__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Z_Motor_Speed_UsingFixedFunction)
        #define Z_Motor_Speed_DEADBAND_COUNT         (*(reg8 *)  Z_Motor_Speed_PWMHW__CFG0)
        #define Z_Motor_Speed_DEADBAND_COUNT_PTR     ((reg8 *)   Z_Motor_Speed_PWMHW__CFG0)
        #define Z_Motor_Speed_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Z_Motor_Speed_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Z_Motor_Speed_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Z_Motor_Speed_DEADBAND_COUNT         (*(reg8 *)  Z_Motor_Speed_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Z_Motor_Speed_DEADBAND_COUNT_PTR     ((reg8 *)   Z_Motor_Speed_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Z_Motor_Speed_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Z_Motor_Speed_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Z_Motor_Speed_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Z_Motor_Speed_UsingFixedFunction) */
#endif /* (Z_Motor_Speed_DeadBandMode == Z_Motor_Speed__B_PWM__DBM_256_CLOCKS) */



#if (Z_Motor_Speed_UsingFixedFunction)
    #define Z_Motor_Speed_STATUS                 (*(reg8 *) Z_Motor_Speed_PWMHW__SR0)
    #define Z_Motor_Speed_STATUS_PTR             ((reg8 *) Z_Motor_Speed_PWMHW__SR0)
    #define Z_Motor_Speed_STATUS_MASK            (*(reg8 *) Z_Motor_Speed_PWMHW__SR0)
    #define Z_Motor_Speed_STATUS_MASK_PTR        ((reg8 *) Z_Motor_Speed_PWMHW__SR0)
    #define Z_Motor_Speed_CONTROL                (*(reg8 *) Z_Motor_Speed_PWMHW__CFG0)
    #define Z_Motor_Speed_CONTROL_PTR            ((reg8 *) Z_Motor_Speed_PWMHW__CFG0)
    #define Z_Motor_Speed_CONTROL2               (*(reg8 *) Z_Motor_Speed_PWMHW__CFG1)
    #define Z_Motor_Speed_CONTROL3               (*(reg8 *) Z_Motor_Speed_PWMHW__CFG2)
    #define Z_Motor_Speed_GLOBAL_ENABLE          (*(reg8 *) Z_Motor_Speed_PWMHW__PM_ACT_CFG)
    #define Z_Motor_Speed_GLOBAL_ENABLE_PTR      ( (reg8 *) Z_Motor_Speed_PWMHW__PM_ACT_CFG)
    #define Z_Motor_Speed_GLOBAL_STBY_ENABLE     (*(reg8 *) Z_Motor_Speed_PWMHW__PM_STBY_CFG)
    #define Z_Motor_Speed_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Z_Motor_Speed_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Z_Motor_Speed_BLOCK_EN_MASK          (Z_Motor_Speed_PWMHW__PM_ACT_MSK)
    #define Z_Motor_Speed_BLOCK_STBY_EN_MASK     (Z_Motor_Speed_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Z_Motor_Speed_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Z_Motor_Speed_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Z_Motor_Speed_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Z_Motor_Speed_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Z_Motor_Speed_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Z_Motor_Speed_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Z_Motor_Speed_CTRL_ENABLE            (uint8)((uint8)0x01u << Z_Motor_Speed_CTRL_ENABLE_SHIFT)
    #define Z_Motor_Speed_CTRL_RESET             (uint8)((uint8)0x01u << Z_Motor_Speed_CTRL_RESET_SHIFT)
    #define Z_Motor_Speed_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Z_Motor_Speed_CTRL_CMPMODE2_SHIFT)
    #define Z_Motor_Speed_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Z_Motor_Speed_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Z_Motor_Speed_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Z_Motor_Speed_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Z_Motor_Speed_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Z_Motor_Speed_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Z_Motor_Speed_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Z_Motor_Speed_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Z_Motor_Speed_STATUS_TC_INT_EN_MASK_SHIFT            (Z_Motor_Speed_STATUS_TC_SHIFT - 4u)
    #define Z_Motor_Speed_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Z_Motor_Speed_STATUS_CMP1_INT_EN_MASK_SHIFT          (Z_Motor_Speed_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Z_Motor_Speed_STATUS_TC              (uint8)((uint8)0x01u << Z_Motor_Speed_STATUS_TC_SHIFT)
    #define Z_Motor_Speed_STATUS_CMP1            (uint8)((uint8)0x01u << Z_Motor_Speed_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Z_Motor_Speed_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Z_Motor_Speed_STATUS_TC >> 4u)
    #define Z_Motor_Speed_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Z_Motor_Speed_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Z_Motor_Speed_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Z_Motor_Speed_RT1_MASK              (uint8)((uint8)0x03u << Z_Motor_Speed_RT1_SHIFT)
    #define Z_Motor_Speed_SYNC                  (uint8)((uint8)0x03u << Z_Motor_Speed_RT1_SHIFT)
    #define Z_Motor_Speed_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Z_Motor_Speed_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Z_Motor_Speed_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Z_Motor_Speed_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Z_Motor_Speed_SYNCDSI_SHIFT)


#else
    #define Z_Motor_Speed_STATUS                (*(reg8 *)   Z_Motor_Speed_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Z_Motor_Speed_STATUS_PTR            ((reg8 *)    Z_Motor_Speed_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Z_Motor_Speed_STATUS_MASK           (*(reg8 *)   Z_Motor_Speed_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Z_Motor_Speed_STATUS_MASK_PTR       ((reg8 *)    Z_Motor_Speed_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Z_Motor_Speed_STATUS_AUX_CTRL       (*(reg8 *)   Z_Motor_Speed_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Z_Motor_Speed_CONTROL               (*(reg8 *)   Z_Motor_Speed_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Z_Motor_Speed_CONTROL_PTR           ((reg8 *)    Z_Motor_Speed_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Z_Motor_Speed_CTRL_ENABLE_SHIFT      (0x07u)
    #define Z_Motor_Speed_CTRL_RESET_SHIFT       (0x06u)
    #define Z_Motor_Speed_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Z_Motor_Speed_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Z_Motor_Speed_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Z_Motor_Speed_CTRL_ENABLE            (uint8)((uint8)0x01u << Z_Motor_Speed_CTRL_ENABLE_SHIFT)
    #define Z_Motor_Speed_CTRL_RESET             (uint8)((uint8)0x01u << Z_Motor_Speed_CTRL_RESET_SHIFT)
    #define Z_Motor_Speed_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Z_Motor_Speed_CTRL_CMPMODE2_SHIFT)
    #define Z_Motor_Speed_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Z_Motor_Speed_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Z_Motor_Speed_STATUS_KILL_SHIFT          (0x05u)
    #define Z_Motor_Speed_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Z_Motor_Speed_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Z_Motor_Speed_STATUS_TC_SHIFT            (0x02u)
    #define Z_Motor_Speed_STATUS_CMP2_SHIFT          (0x01u)
    #define Z_Motor_Speed_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Z_Motor_Speed_STATUS_KILL_INT_EN_MASK_SHIFT          (Z_Motor_Speed_STATUS_KILL_SHIFT)
    #define Z_Motor_Speed_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Z_Motor_Speed_STATUS_FIFONEMPTY_SHIFT)
    #define Z_Motor_Speed_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Z_Motor_Speed_STATUS_FIFOFULL_SHIFT)
    #define Z_Motor_Speed_STATUS_TC_INT_EN_MASK_SHIFT            (Z_Motor_Speed_STATUS_TC_SHIFT)
    #define Z_Motor_Speed_STATUS_CMP2_INT_EN_MASK_SHIFT          (Z_Motor_Speed_STATUS_CMP2_SHIFT)
    #define Z_Motor_Speed_STATUS_CMP1_INT_EN_MASK_SHIFT          (Z_Motor_Speed_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Z_Motor_Speed_STATUS_KILL            (uint8)((uint8)0x00u << Z_Motor_Speed_STATUS_KILL_SHIFT )
    #define Z_Motor_Speed_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Z_Motor_Speed_STATUS_FIFOFULL_SHIFT)
    #define Z_Motor_Speed_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Z_Motor_Speed_STATUS_FIFONEMPTY_SHIFT)
    #define Z_Motor_Speed_STATUS_TC              (uint8)((uint8)0x01u << Z_Motor_Speed_STATUS_TC_SHIFT)
    #define Z_Motor_Speed_STATUS_CMP2            (uint8)((uint8)0x01u << Z_Motor_Speed_STATUS_CMP2_SHIFT)
    #define Z_Motor_Speed_STATUS_CMP1            (uint8)((uint8)0x01u << Z_Motor_Speed_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Z_Motor_Speed_STATUS_KILL_INT_EN_MASK            (Z_Motor_Speed_STATUS_KILL)
    #define Z_Motor_Speed_STATUS_FIFOFULL_INT_EN_MASK        (Z_Motor_Speed_STATUS_FIFOFULL)
    #define Z_Motor_Speed_STATUS_FIFONEMPTY_INT_EN_MASK      (Z_Motor_Speed_STATUS_FIFONEMPTY)
    #define Z_Motor_Speed_STATUS_TC_INT_EN_MASK              (Z_Motor_Speed_STATUS_TC)
    #define Z_Motor_Speed_STATUS_CMP2_INT_EN_MASK            (Z_Motor_Speed_STATUS_CMP2)
    #define Z_Motor_Speed_STATUS_CMP1_INT_EN_MASK            (Z_Motor_Speed_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Z_Motor_Speed_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Z_Motor_Speed_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Z_Motor_Speed_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Z_Motor_Speed_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Z_Motor_Speed_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Z_Motor_Speed_UsingFixedFunction */

#endif  /* CY_PWM_Z_Motor_Speed_H */


/* [] END OF FILE */
