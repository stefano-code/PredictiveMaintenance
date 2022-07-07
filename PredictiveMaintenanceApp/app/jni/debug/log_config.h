#ifndef LOG_CONFIG_H
#define LOG_CONFIG_H

#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>


#define ANDROID_LOG_NAME	"PCA"

#define ANDROID_LOG(level, fmt, args...)	__android_log_print(level, ANDROID_LOG_NAME, fmt, ##args)

#include "android/log.h"

#define LOGI(fmt, args...) ANDROID_LOG(ANDROID_LOG_INFO, fmt, ##args);
#define LOGD(fmt, args...) ANDROID_LOG(ANDROID_LOG_DEBUG, fmt, ##args);
#define LOGE(fmt, args...) ANDROID_LOG(ANDROID_LOG_ERROR, fmt, ##args);

#include <syslog.h>

#endif	/* LOG_CONFIG_H */
