#include "profiler.h"
#define TEN 10

const size_t transfer_lengths[4]={10,100,1000,5000};
size_t start_count=0,end_count=0,profile_result_length;
uint8_t	profile_result[24][10];


#define KL25Z

//#define PROFILERESULT

#ifdef KL25Z
/**
@brief Configures the Ssystick for performing the profiling operations
@param ticks value to initialise the systick down counter
@return  none
*/
	void SysTick_Init(uint32_t ticks)
	{
		SysTick->LOAD  = (uint32_t)(ticks - 1UL);
		SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
						   //SysTick_CTRL_TICKINT_Msk  |
						   SysTick_CTRL_ENABLE_Msk;
		SysTick->VAL   = 0UL;
	}

/**
@brief Does profiling for memmove using DMA
@param uint8_t * src_addr source pointer
@param uint8_t * dst_addr destination pointer
@return  none
*/
	
	void profiling_memmove_dma(uint8_t * src_addr,uint8_t * dst_addr)
	{
		#ifdef PROFILERESULT
		LOG_RAW_STRING("\n\n\rMemMove DMA\r\n\n");
		#endif
		
		for(int i=0;i<4;i++)
		{
			systickzero();
			start_count=getcount();
			my_memmove_dma(src_addr,dst_addr,transfer_lengths[i]);
			end_count=getcount();

			profile_result_length=my_itoa(disp_val,profile_result[0+i],TEN);
			LOG_ITEM(createLog(INFO,10,"MemmoveDMA"),Logger_q);
			LOG_ITEM(createLog(PROFILING_RESULT,profile_result_length,profile_result[0+i]),Logger_q);
			
			#ifdef PROFILERESULT
			LOG_RAW_INT(transfer_lengths[i]);LOG_RAW_STRING("Bytes\n\r");
			LOG_RAW_STRING("Start Count: ");LOG_RAW_INT(start_count);LOG_RAW_STRING("\n\r");
			LOG_RAW_STRING("End Count: ");LOG_RAW_INT(end_count);LOG_RAW_STRING("\n\r");
			LOG_RAW_STRING("Count Diff: ");LOG_RAW_INT(disp_val); LOG_RAW_STRING(time_unit);
			#endif
		}

	}

/**
@brief Does profiling for memset using DMA
@param uint8_t * src_addr source pointer
@return  none
*/

	void profiling_memset_dma(uint8_t * src_addr)
	{
		#ifdef PROFILERESULT
		LOG_RAW_STRING("\n\rMemset DMA\r\n\n");
		#endif

		for(int i=0;i<4;i++)
			{
				systickzero();
				start_count=getcount();
				my_memset_dma(src_addr,transfer_lengths[i],65);
				end_count=getcount();
				
				profile_result_length=my_itoa(disp_val,profile_result[4+i],TEN);
				LOG_ITEM(createLog(INFO,9,"MemsetDMA"),Logger_q);
				LOG_ITEM(createLog(PROFILING_RESULT,profile_result_length,profile_result[4+i]),Logger_q);

				#ifdef PROFILERESULT
				LOG_RAW_INT(transfer_lengths[i]);LOG_RAW_STRING("Bytes\n\r");
				LOG_RAW_STRING("Start Count: ");LOG_RAW_INT(start_count);LOG_RAW_STRING("\n\r");
				LOG_RAW_STRING("End Count: ");LOG_RAW_INT(end_count);LOG_RAW_STRING("\n\r");
				LOG_RAW_STRING("Count Diff: ");LOG_RAW_INT(disp_val); LOG_RAW_STRING(time_unit);
				#endif
			}
	}

#else
/**
@brief gets time from sys/time.h for BBB
@param   none
@return  none
*/
	
	size_t getcount(void)
	{
		gettimeofday(&time_value,NULL);
		return time_value.tv_usec;
	}
	
#endif

/**
@brief Does profiling for memset 
@param uint8_t * src_addr source pointer
@return  none
*/


void profiling_my_memset(uint8_t * src_addr)
{	
	#ifdef PROFILERESULT
	LOG_RAW_STRING("\n\rMy Memset\r\n\n");
	#endif
	
	for(int i=0;i<4;i++)
		{
			systickzero();
			start_count=getcount();
			my_memset(src_addr,transfer_lengths[i],65);
			end_count=getcount();
			
			profile_result_length=my_itoa(disp_val,profile_result[8+i],TEN);
			LOG_ITEM(createLog(INFO,8,"MyMemset"),Logger_q);
			LOG_ITEM(createLog(PROFILING_RESULT,profile_result_length,profile_result[8+i]),Logger_q);

			#ifdef PROFILERESULT
			LOG_RAW_INT(transfer_lengths[i]);LOG_RAW_STRING("Bytes\n\r");
			LOG_RAW_STRING("Start Count: ");LOG_RAW_INT(start_count);LOG_RAW_STRING("\n\r");
			LOG_RAW_STRING("End Count: ");LOG_RAW_INT(end_count);LOG_RAW_STRING("\n\r");
			LOG_RAW_STRING("Count Diff: ");LOG_RAW_INT(disp_val); LOG_RAW_STRING(time_unit);
			#endif
		}

}
/**
@brief Does profiling for memset included from c library 
@param uint8_t * src_addr source pointer
@return  none
*/

void profiling_memset(uint8_t * src_addr)
{
	#ifdef PROFILERESULT
	LOG_RAW_STRING("\n\rMemset\r\n\n");
	#endif
	
	for(int i=0;i<4;i++)
		{
			systickzero();
			start_count=getcount();
			memset(src_addr,65,transfer_lengths[i]);
			end_count=getcount();
			
			profile_result_length=my_itoa(disp_val,profile_result[12+i],TEN);
			LOG_ITEM(createLog(INFO,6,"Memset"),Logger_q);
			LOG_ITEM(createLog(PROFILING_RESULT,profile_result_length,profile_result[12+i]),Logger_q);

			#ifdef PROFILERESULT
			LOG_RAW_INT(transfer_lengths[i]);LOG_RAW_STRING("Bytes\n\r");
			LOG_RAW_STRING("Start Count: ");LOG_RAW_INT(start_count);LOG_RAW_STRING("\n\r");
			LOG_RAW_STRING("End Count: ");LOG_RAW_INT(end_count);LOG_RAW_STRING("\n\r");
			LOG_RAW_STRING("Count Diff: ");LOG_RAW_INT(disp_val); LOG_RAW_STRING(time_unit);
			#endif
		}


}



/**
@brief Does profiling for memmove 
@param uint8_t * src_addr source pointer
@param uint8_t * dst_addr destination pointer
@return  none
*/
void profiling_my_memmove(uint8_t * src_addr,uint8_t * dst_addr)
{
	#ifdef PROFILERESULT
	LOG_RAW_STRING("\n\n\rMy MemMove\r\n\n");
	#endif
	
	for(int i=0;i<4;i++)
		{
			systickzero();
			start_count=getcount();
			my_memmove(src_addr,dst_addr,transfer_lengths[i]);
			end_count=getcount();
			
			profile_result_length=my_itoa(disp_val,profile_result[16+i],TEN);
			LOG_ITEM(createLog(INFO,9,"MyMemmove"),Logger_q);
			LOG_ITEM(createLog(PROFILING_RESULT,profile_result_length,profile_result[16+i]),Logger_q);

			#ifdef PROFILERESULT
			LOG_RAW_INT(transfer_lengths[i]);LOG_RAW_STRING("Bytes\n\r");
			LOG_RAW_STRING("Start Count: ");LOG_RAW_INT(start_count);LOG_RAW_STRING("\n\r");
			LOG_RAW_STRING("End Count: ");LOG_RAW_INT(end_count);LOG_RAW_STRING("\n\r");
			LOG_RAW_STRING("Count Diff: ");LOG_RAW_INT(disp_val); LOG_RAW_STRING(time_unit);
			#endif
		}

}
/**
@brief Does profiling for memmove using c-library memmove
@param uint8_t * src_addr source pointer
@param uint8_t * dst_addr destination pointer
@return  none
*/
void profiling_memmove(uint8_t * src_addr,uint8_t * dst_addr)
{
	#ifdef PROFILERESULT
	LOG_RAW_STRING("\n\n\rMemMove\r\n\n");
	#endif
	
	for(int i=0;i<4;i++)
		{
			systickzero();
			start_count=getcount();
			memmove((uint8_t*)src_addr,(uint8_t *)dst_addr,transfer_lengths[i]);
			end_count=getcount();
			
			profile_result_length=my_itoa(disp_val,profile_result[20+i],TEN);
			LOG_ITEM(createLog(INFO,7,"Memmove"),Logger_q);
			LOG_ITEM(createLog(PROFILING_RESULT,profile_result_length,profile_result[20+i]),Logger_q);

			#ifdef PROFILERESULT
			LOG_RAW_INT(transfer_lengths[i]);LOG_RAW_STRING("Bytes\n\r");
			LOG_RAW_STRING("Start Count: ");LOG_RAW_INT(start_count);LOG_RAW_STRING("\n\r");
			LOG_RAW_STRING("End Count: ");LOG_RAW_INT(end_count);LOG_RAW_STRING("\n\r");
			LOG_RAW_STRING("Count Diff: ");LOG_RAW_INT(disp_val); LOG_RAW_STRING(time_unit);
			#endif
		}

}
/**
@brief Does profiling for all memory functions, 
		ie calls all the individual profiling functions
@param uint8_t * src_addr source pointer
@param uint8_t * dst_addr destination pointer
@return  none
*/
void profiling_memory_functions(uint8_t * src_addr,uint8_t * dst_addr)
{
	LOG_ITEM(createLog(PROFILING_STARTED,0,NULL),Logger_q);
	#ifdef KL25Z
	profiling_memset_dma(src_addr);
	profiling_memmove_dma(src_addr,dst_addr);
	#endif

	profiling_memset(src_addr);
	profiling_my_memset(src_addr);
	
	profiling_memmove(src_addr,dst_addr);
	profiling_my_memmove(src_addr,dst_addr);
	LOG_ITEM(createLog(PROFILING_COMPLETED,0,NULL),Logger_q);

}
