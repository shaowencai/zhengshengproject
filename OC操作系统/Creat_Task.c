   
   
   INT8U OSTaskCreate(void(*task)(void *p_arg), void *p_arg, OS_STK *ptos, INT8U prio)
	{
		OS_STK *psp;
		INT8U err;
		
		#if OS_ARG_CHK_EN>0u
			if(prio>OS_LOWEST_PRIO)
				return (OS_ERR_PRIO_INVALID)
		#endif
		OS_ENTER_CRITICAL();//进入临界区
		if(OSIntNesting>0u)
		{
			OS_EXIT_CRITICAL();
			return (OS_ERR_TASK_CREATE_ISR);
		}
		if(OSTCBPrioTbl[prio]==(OS_TCB *)0)
		{
			OSTCBPrioTbl[prio]=OS_TCB_RESERVED;//define OS_TCB_RESERVED ((OS_TCB *)1)是宏定义 
		
			OS_EXIT_CRITICAL();//退出临界区
		
			psp=OSTaskStkInit(task,p_arg,ptos,0u);//对栈进行初始化
			err=OS_TCBInit(prio,psp,(OS_STK *)0,0u,0u,(void *)0,0u);
			if(err==OS_ERR_NONE)
			{
				if(OSRuning==OS_TRUE)
				{
					OS_Sched();
				}
			}
			else
			{
				OS_ENTER_CRITICAL();
				OSTCBPrioTbl[prio]=(OS_TCB *)0;
				OS_EXIT_CRITICAL();
			}
			return (err);
		}
		OS_EXIT_CRITICAL();//退出临界区
		
		return (OS_ERR_PRIO_EXIST);		
	}
	
	OSTaskStkInit(void(*task)(void *pd),void *pdata,OS_STK *ptos,INT16U opt)
	{

	}
	OS_TCBInit(INT8U prio,OS_STK ptos);
	{
		OS_TCB *ptcb
		OS_ENTER_CRITICAL();
		ptcb=OSTCBFreeList;
		if(ptcb !=(OS_TCB *)0)
		{
			OSTCBFreeList=ptcb->OSTCBNext;
			OS_EXIT_CRITICAL();
			ptcb->OSTCBStkPtr=ptos;
			ptcb->OSTCBPrio=prio;
			ptcb->OSTCBStat=OS_STAT_RDY;
			ptcb->OSTCBStatPend=OS_STAT_PEND_OK;
			ptcb->OSTCBDly=0u;
			ptcb->
		}
	}

		
	