#ifndef PEPS_IMAG_INFOMULTIMONDE_HPP
#define PEPS_IMAG_INFOMULTIMONDE_HPP

// Spot of each index
#define SPOT_FTSE 6061.61
#define SPOT_P500 1919.65
#define SPOT_HANGSENG 9551.52
#define SPOT_NIKKEI 17479.97
#define SPOT_SPASX200 5021.97
#define SPOT_EUROSTOCK50 3190.39

// Volatility
#define VOL_FTSE 0.191
#define VOL_P500 0.184
#define VOL_HANGSENG 0.532
#define VOL_NIKKEI 0.248
#define VOL_SPASX200 0.186
#define VOL_EUROSTOCK50 0.152

// TODO Trend
#define TREND_FTSE 0
#define TREND_P500 0
#define TREND_HANGSENG 0
#define TREND_NIKKEI 0
#define TREND_SPASX200 0
#define TREND_EUROSTOCK50 0

// Matrice de correlation
#define COR_FTSE_P500 0.856
#define COR_FTSE_HANGSENG 0.505
#define COR_FTSE_NIKKEI 0.841
#define COR_FTSE_SPASX200 0.922
#define COR_FTSE_EUROSTOCK50 0.934
#define COR_P500_HANGSENG 0.542
#define COR_P500_NIKKEI 0.781
#define COR_P500_SPASX200 0.809
#define COR_P500_EUROSTOCK50 0.909
#define COR_HANGSENG_NIKKEI 0.306
#define COR_HANGSENG_SPASX200 0.518
#define COR_HANGSENG_EUROSTOCK50 0.521
#define COR_NIKKEI_SPASX200 0.741
#define COR_NIKKEI_EUROSTOCK50 0.793
#define COR_SPASX_EUROSTOCK50 0.897

// Number of days from 01/10/2015 to each date of constatation
#define NB_DAYS_TO_CONSTATATION_1 373 // 01/10/2015 to 07/10/2016
#define NB_DAYS_TO_CONSTATATION_2 744 // 01/10/2015 to 13/10/2017
#define NB_DAYS_TO_CONSTATATION_3 1115 // 01/10/2015 to 19/10/2018
#define NB_DAYS_TO_CONSTATATION_4 1486 // 01/10/2015 to 25/10/2019
#define NB_DAYS_TO_CONSTATATION_5 1857 // 01/10/2015 to 30/10/2020
#define NB_DAYS_TO_CONSTATATION_6 2228 // 01/10/2015 to 05/11/2021

#define NB_DAYS_TO_MATURITY 2235 // 01/10/2015 to 12/11/2021
#define BASE 360

// Cap and Floor
#define FLOOR -0.15
#define CAP 0.15

// Nominal
#define NOMINAL 100

#endif //PEPS_IMAG_INFOMULTIMONDE_HPP
