#ifndef PEPS_IMAG_INFOMULTIMONDE_HPP
#define PEPS_IMAG_INFOMULTIMONDE_HPP

// Cap and Floor
#define FLOOR -0.15
#define CAP 0.15

// Nominal
#define NOMINAL 100

// Spot of each index at t = 01/10/2015
#define SPOT_EUROSTOCK50 3190.39
#define SPOT_FTSE 6061.61
#define SPOT_P500 1919.65
#define SPOT_HANGSENG 9551.52
#define SPOT_NIKKEI 17479.97
#define SPOT_SPASX200 5021.97

// Spot of each change at t = 01/10/2015
#define SPOT_GBP 1.3533
#define SPOT_USD 0.8946
#define SPOT_HKD 0.1154
#define SPOT_JPY 0.0075
#define SPOT_AUD 0.6278

// Spot of each index at eur economy at t = 01/10/2015
#define SPOT_XEUROSTOCK50 SPOT_EUROSTOCK50
#define SPOT_XFTSE SPOT_FTSE * SPOT_GBP
#define SPOT_XP500 SPOT_P500 * SPOT_USD
#define SPOT_XHANGSENG SPOT_HANGSENG * SPOT_HKD
#define SPOT_XNIKKEI SPOT_NIKKEI * SPOT_JPY
#define SPOT_XSPASX200 SPOT_SPASX200 * SPOT_AUD

// Number of days from 01/10/2015 to each date of constatation
#define NB_DAYS_TO_CONSTATATION_1 373 // 01/10/2015 to 07/10/2016
#define NB_DAYS_TO_CONSTATATION_2 744 // 01/10/2015 to 13/10/2017
#define NB_DAYS_TO_CONSTATATION_3 1115 // 01/10/2015 to 19/10/2018
#define NB_DAYS_TO_CONSTATATION_4 1486 // 01/10/2015 to 25/10/2019
#define NB_DAYS_TO_CONSTATATION_5 1857 // 01/10/2015 to 30/10/2020
#define NB_DAYS_TO_CONSTATATION_6 2228 // 01/10/2015 to 05/11/2021
// Number of working days from 01/10/2015 to each date of constatation
#define NB_DAYSWRK_TO_CONSTATATION_1 267 // 01/10/2015 to 07/10/2016
#define NB_DAYSWRK_TO_CONSTATATION_2 532 // 01/10/2015 to 13/10/2017
#define NB_DAYSWRK_TO_CONSTATATION_3 797 // 01/10/2015 to 19/10/2018
#define NB_DAYSWRK_TO_CONSTATATION_4 1062 // 01/10/2015 to 25/10/2019
#define NB_DAYSWRK_TO_CONSTATATION_5 1327 // 01/10/2015 to 30/10/2020
#define NB_DAYSWRK_TO_CONSTATATION_6 1592 // 01/10/2015 to 05/11/2021

#define NB_DAYS_TO_MATURITY 2235 // 01/10/2015 to 12/11/2021
#define NB_DAYSWRK_TO_MATURITY 1597 // 01/10/2015 to 12/11/2021

#define BASE 360

//Risk Free Rate for all countries in 2015
#define RFF_FRANCE 0.036
#define RFF_UK 0.021
#define RFF_US 0.024
#define RFF_CHINA 0.045
#define RFF_JAPAN 0.007
#define RFF_AUSTRALIA 0.031

#endif //PEPS_IMAG_INFOMULTIMONDE_HPP
