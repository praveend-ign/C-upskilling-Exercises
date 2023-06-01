#include "cmsis_os.h"

void SystemInit(void)
{
/*! Reset the RCC clock configuration to the default reset state ----
 * Set MSION bit 
 */
  RCC->CR |= RCC_CR_MSION;

  /*! Reset CFGR register */
  RCC->CFGR = 0x00000000U;

  /*! Reset HSEON, CSSON , HSION, and PLLON bits 
   *  assuming all the above bits are adjacent and
   *  starts from bit 0
   */
  RCC->CR &= 0x0F;

  /*! Reset PLLCFGR register 
   *  assuming bit 0 
   */
  RCC->PLLCFGR = 0x1;

  /*! Reset HSEBYP bit 
   * assuming bit 0 as HSEBYP
   */
  RCC->CR &= 0xFFFFFFFE;

  /*! Disable all interrupts */
  RCC->CIER = 0x00000000U;

  /*! Vector Table Relocation in Internal FLASH */
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; 
}

int main(void)
{
/*! Reset all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /*! Configure the system clock */
  SystemClock_Config();

  /*! Initialize gpio to configured peripherals */
  HAL_GPIO_Init();

  while(1) {
	/*! main application code starts from here
 	 */
  }
}
