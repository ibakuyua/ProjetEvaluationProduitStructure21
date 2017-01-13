#include <time.h>
#include "ModelGen.hpp"


ModelGen::ModelGen(int assetNb, Asset **assets, RateModelGen **rateModel)
        :assetNb(assetNb),rateModels(rateModel)
{
    spot = pnl_vect_create(assetNb);
    trend = pnl_vect_create(assetNb);
    volatility = pnl_vect_create(assetNb);
    for (int d = 0; d < assetNb; ++d) {
        LET(spot,d) = assets[d]->spot;
        LET(trend,d) = assets[d]->trend;
        LET(volatility,d) = assets[d]->volatility;
    }
    rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, time(NULL));
}


ModelGen::~ModelGen() {
    pnl_vect_free(&spot);
    pnl_vect_free(&trend);
    pnl_vect_free(&volatility);
    pnl_rng_free(&rng);
}
