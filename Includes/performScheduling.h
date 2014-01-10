
#ifndef PERFORMSCHEDULING_H_
#define PERFORMSCHEDULING_H_

void performUserScheduling(systemConfig_t *sysConfig,downlinkConfig_t *dlConfig);
void performRoundRobinScheduling(systemConfig_t *sysConfig,downlinkConfig_t *dlConfig);
void performSuccessiveProjections(systemConfig_t *sysConfig,downlinkConfig_t *dlConfig);

#endif /* PERFORMSCHEDULING_H_ */
