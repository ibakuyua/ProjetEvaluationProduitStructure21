#include "MonteCarloPricer.hpp"


MonteCarloPricer::MonteCarloPricer(double maturity, PayOffFunction payOff, ModelGen *simuIndex, ModelGen *simuChange, int nbSample, int nbTimeStep)
        : PricerGen(maturity, payOff)
{
    this->nbSample = nbSample;
    this->simuChangeModel = simuChange;
    this->simuIndexModel = simuIndex;
    this->nbTimeStep = nbTimeStep;
    this->path = pnl_mat_create_from_zero(nbTimeStep+1,6);
}

void MonteCarloPricer::price(double t, PnlMat *past, double &price, double &ic) const {

    // TODO : question si r est stochastique ?
    double r_T = simuIndexModel->rateModel->GetRate(maturity);
    double discountFactor = exp(-simuIndexModel->rateModel->GetIntegralRate(t,maturity));

    double estimation, espEstimation = 0, varEstimation = 0;

    for (int m = 0; m < nbSample; ++m) {
        simuIndexModel->Simulate(t,maturity,path,past,nbTimeStep);
        estimation = payOff(path);
        espEstimation += estimation;
        varEstimation += estimation * estimation;
    }
    espEstimation /= (double)nbSample;
    varEstimation /= (double)nbSample;
    varEstimation = exp(-2 * r_T * maturity) * fabs(varEstimation - espEstimation * espEstimation);

    price = discountFactor * espEstimation;
    ic = 3.92 * sqrt(varEstimation / (double)nbSample);
}

void MonteCarloPricer::delta(double t, PnlMat *past, PnlVect *delta) const {
    // TODO
}

MonteCarloPricer::~MonteCarloPricer() {
    pnl_mat_free(&path);
}
