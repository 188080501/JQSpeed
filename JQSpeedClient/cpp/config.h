#ifndef CONFIG_H_
#define CONFIG_H_

inline constexpr int defaultHttpPort      = 51888;
inline constexpr int defaultWebSocketPort = 51889;

inline constexpr int downloadTestBlockSize  = 1 * 1024 * 1024;
inline constexpr int downloadTestBlockCount = 50;

inline constexpr int uploadTestBlockSize  = 1 * 1024 * 1024;
inline constexpr int uploadTestBlockCount = 25;

#endif//CONFIG_H_
