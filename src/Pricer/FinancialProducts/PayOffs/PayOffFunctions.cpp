#include <map>
#include <math.h>
#include "PayOffFunctions.hpp"

#include "../../infoMultimonde.hpp"
// TODO Faire attention, vu qu'on fait du jour par jour dans la calibration, l'intégrale doit se faire en terme de jour ! pour le calcul des payoff

double payOffMultimonde21_simple(PnlMat *path, PnlVect *parameters, map<Change,RateModelGen*> &rateModels) {
    int nbTimeStep = path->m;
    bool isConstated[6] = {false, false, false, false,false,false};
    // TODO ici à changer
    int constatationIndexes[6] =
            {
                    (int)(nbTimeStep * NB_DAYS_TO_CONSTATATION_1/(double)NB_DAYS_TO_MATURITY),
                    (int)(nbTimeStep * NB_DAYS_TO_CONSTATATION_2/(double)NB_DAYS_TO_MATURITY),
                    (int)(nbTimeStep * NB_DAYS_TO_CONSTATATION_3/(double)NB_DAYS_TO_MATURITY),
                    (int)(nbTimeStep * NB_DAYS_TO_CONSTATATION_4/(double)NB_DAYS_TO_MATURITY),
                    (int)(nbTimeStep * NB_DAYS_TO_CONSTATATION_5/(double)NB_DAYS_TO_MATURITY),
                    (int)(nbTimeStep * NB_DAYS_TO_CONSTATATION_6/(double)NB_DAYS_TO_MATURITY)
            };

    double maxPerfCour, indexPerf, constatedPerf = 0.;
    int maxPerfCourIndex;

    // For each date of constatation
    for (int d = 0; d < 6; ++d) {
        maxPerfCour = -10000;
        // For each index performance
        for (int ind = 0; ind < 6; ++ind) {
            // Non constated index
            if (isConstated[ind])
                continue;
            // Compute the index performance
            indexPerf = (PNL_MGET(path,constatationIndexes[d],ind)-PNL_MGET(path,0,ind))/PNL_MGET(path,0,ind);
            // Search of the maximum
            if (maxPerfCour < indexPerf){
                maxPerfCour = indexPerf;
                maxPerfCourIndex = ind;
            }
        }
        // constated index is deleted of the index basket
        isConstated[maxPerfCourIndex] = true;
        // cap/floor the maxPerf
        maxPerfCour = (maxPerfCour < FLOOR) ? FLOOR : maxPerfCour;
        maxPerfCour = (maxPerfCour > CAP) ? CAP : maxPerfCour;
        // Add the performance to the final performance
        constatedPerf += maxPerfCour;
    }

    return NOMINAL * (1 + constatedPerf);
}


double payOffMultimonde21(PnlMat *path, PnlVect *parameters, map<Change, RateModelGen *> &rateModels) {
    int nbTimeStep = path->m;
    bool isConstated[6] = {false, false, false, false,false,false};
    // TODO ici à changer
    int constatationIndexes[6] =
            {
                    (int)(nbTimeStep * NB_DAYS_TO_CONSTATATION_1/(double)NB_DAYS_TO_MATURITY),
                    (int)(nbTimeStep * NB_DAYS_TO_CONSTATATION_2/(double)NB_DAYS_TO_MATURITY),
                    (int)(nbTimeStep * NB_DAYS_TO_CONSTATATION_3/(double)NB_DAYS_TO_MATURITY),
                    (int)(nbTimeStep * NB_DAYS_TO_CONSTATATION_4/(double)NB_DAYS_TO_MATURITY),
                    (int)(nbTimeStep * NB_DAYS_TO_CONSTATATION_5/(double)NB_DAYS_TO_MATURITY),
                    (int)(nbTimeStep * NB_DAYS_TO_CONSTATATION_6/(double)NB_DAYS_TO_MATURITY)
            };
    double constatationTime[6] =
            {
                    NB_DAYS_TO_CONSTATATION_1/(double)NB_DAYS_TO_MATURITY,
                    NB_DAYS_TO_CONSTATATION_2/(double)NB_DAYS_TO_MATURITY,
                    NB_DAYS_TO_CONSTATATION_3/(double)NB_DAYS_TO_MATURITY,
                    NB_DAYS_TO_CONSTATATION_4/(double)NB_DAYS_TO_MATURITY,
                    NB_DAYS_TO_CONSTATATION_5/(double)NB_DAYS_TO_MATURITY,
                    NB_DAYS_TO_CONSTATATION_6/(double)NB_DAYS_TO_MATURITY
            };
    Change changeByIndex[6] =
            {
                    Change::EUR,
                    Change::GBP,
                    Change::USD,
                    Change::HKD,
                    Change::JPY,
                    Change::AUD
            };

    double maxPerfCour, indexPerf, constatedPerf = 0.;
    int maxPerfCourIndex;

    double XtIt_outof_XtRt, X0I0_out_of_X0R0, Rt_outof_R0;

    // For each date of constatation
    for (int d = 0; d < 6; ++d) {
        maxPerfCour = -10000;
        // First indice performance (eurostock)
        if (!isConstated[0]) {
            maxPerfCour = (PNL_MGET(path, constatationIndexes[d], 0) - PNL_MGET(path, 0, 0)) / PNL_MGET(path, 0, 0);
            maxPerfCourIndex = 0;
        }
        // For each other index performance
        for (int ind = 1; ind < 6; ++ind) {
            // Non constated index
            if (isConstated[ind])
                continue;
            // Compute the index performance
            // TODO : affecte ici
            Rt_outof_R0 = exp(-rateModels[changeByIndex[ind]]->GetIntegralRate(0.,constatationIndexes[ind]));
            XtIt_outof_XtRt = PNL_MGET(path,constatationIndexes[d],ind)/PNL_MGET(path,constatationIndexes[d],ind+5);
            X0I0_out_of_X0R0 = PNL_MGET(path,0,ind)/PNL_MGET(path,0,ind+5);

            indexPerf = (XtIt_outof_XtRt * Rt_outof_R0 - X0I0_out_of_X0R0)/X0I0_out_of_X0R0;
            // Search of the maximum
            if (maxPerfCour < indexPerf){
                maxPerfCour = indexPerf;
                maxPerfCourIndex = ind;
            }
        }
        // constated index is deleted of the index basket
        isConstated[maxPerfCourIndex] = true;
        // cap/floor the maxPerf
        maxPerfCour = (maxPerfCour < FLOOR) ? FLOOR : maxPerfCour;
        maxPerfCour = (maxPerfCour > CAP) ? CAP : maxPerfCour;
        // Add the performance to the final performance
        constatedPerf += maxPerfCour;
    }

    return NOMINAL * (1 + constatedPerf);
}

double payOffCall(PnlMat *path, PnlVect *parameters, map<Change,RateModelGen*> &rateModels) {
    double S_TminusK = MGET(path,path->m-1,0)-GET(parameters,0);

    return (S_TminusK > 0.) ? S_TminusK : 0.;
}
