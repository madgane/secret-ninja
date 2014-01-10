
#include "lteSystem.h"
#include "performScheduling.h"

void performUserScheduling(systemConfig_t *sysConfig,downlinkConfig_t *dlConfig)
{
	switch (sysConfig->schedType)
	{
		case (ROUNDROBIN) :
		{
			performRoundRobinScheduling(sysConfig,dlConfig);
			break;
		}
		case (GREEDY) :
		{
			performGreedyScheduling(sysConfig,dlConfig);
			break;
		}
		case (SUCCPROJ) :
		{
			performSuccessiveProjections(sysConfig,dlConfig);
			break;
		}
		case (PIPD) :
		{
			performPIPDScheduling(sysConfig,dlConfig);
			break;
		}
		default :
		{
			printf("Unknown Scheduler Algorithm ! \n");
			exit(false);
		}
	}
}
