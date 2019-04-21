#ifndef SIMULATOR_CONFIG_H
#define SIMULATOR_CONFIG_H

//#define USE_SIMULATOR

#if defined(Q_OS_WIN32) || defined(USE_SIMULATOR)
#define SIMULATOR
#endif


#endif // SIMULATOR_CONFIG_H
