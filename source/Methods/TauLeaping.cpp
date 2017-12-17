/*
 *  TauLeaping.cpp
 *  StochasticSimulationMethods
 *
 *  Created by Basil Bayati on 10/7/08.
 *  Copyright 2008 Basil Bayati. All rights reserved.
 *
 */

#include "TauLeaping.h"

TauLeaping::TauLeaping(Simulation * simulation):
LeapMethod(simulation)
{ }

TauLeaping::~TauLeaping()
{ }

double TauLeaping::computeTimeStep()
{
    double epsilon	= simulation->Epsilon;
    
    int numberOfSpecies		= sbmlModel->getNumSpecies();
    Array<int, 1> hor			(numberOfSpecies);
    Array<int, 1> nuHor			(numberOfSpecies);
    Array<double, 1> muHat		(numberOfSpecies);
    Array<double, 1> sigmaHat2	(numberOfSpecies);
    Array<double, 1> varHat		(numberOfSpecies);
    hor = 0; nuHor = 0; muHat = 0.0; sigmaHat2 = 0.0;
    
    computeHor(hor, nuHor);
    computeMuHatSigmaHat2(muHat, sigmaHat2);
    
    double tau, taup,  epsi, epsixi, epsixisq;
    double xi;
    
    tau = HUGE_VAL;
    
    double a0 = (double)blitz::sum(propensitiesVector);
    for (int is = 0; is < numberOfSpecies; is++)
    {
        varHat(is) = sigmaHat2(is) - (1.0/a0) * muHat(is) * muHat(is);
    }
    
    for (int is = 0; is < numberOfSpecies; ++is)
    {
        taup = (HUGE_VALF*0.5);
        xi = (double)simulation->speciesValues(is);
        switch (hor(is)) {
            case 0:
                break;
            case 1:
                epsi = epsilon;
                epsixi = epsi * xi;
                epsixi = max(epsixi,1.0);
                tau = min(tau,epsixi/fabsf(muHat(is)));
                epsixisq = epsixi*epsixi;
                tau = min(tau,epsixisq/varHat(is));
                break;
            case 2:
                if (nuHor(is) == 1)
                    epsi = 0.5*epsilon;
                else
                    epsi = epsilon*(xi-1.0)/(2.0*(xi-1.0)+1.0);
                epsixi = epsi * xi;
                epsixi = max(epsixi,1.0);
                tau = min(tau,epsixi/fabs(muHat(is)));
                epsixisq = epsixi*epsixi;
                tau = min(tau,epsixisq/varHat(is));
                break;
            case 3:
                if (nuHor(is)==1)
                    epsi = 0.3333333333*epsilon;
                else if (nuHor(is) == 2)
                    epsi = epsilon*(xi-1)/(3.0*(xi-1)+1.5);
                else
                    epsi = epsilon*(xi-1)*(xi-2)/(3.0*(xi-1)*(xi-2)+(xi-2)+2.0*(xi-1));
                epsixi = epsi * xi;
                epsixi = max(epsixi,1.0);
                tau = min(tau,epsixi/fabsf(muHat(is)));
                epsixisq = epsixi*epsixi;
                tau = min(tau,epsixisq/varHat(is));
                break;
            default:
                break;
        }
    }
    
    return tau;
}

// if proposed time step is too small,execute numberOfIterations steps of SSA
void TauLeaping::_executeSSA(double& t, int SSAsteps)
{
    int count = 0.;
    double a0 = 0.;
    double tau;
    double r1;
    int reactionIndex = 0;
    double cummulative = 0.0;
    
    while (count < SSAsteps)
    {
        count++;
        computePropensities(propensitiesVector, 0);
        a0 = blitz::sum(propensitiesVector);
        tau = (1.0/a0) * sgamma( (double)1.0 );
        
        r1 = ranf();
        reactionIndex = -1;
        cummulative = 0.0;
        for (int j = 0; j < propensitiesVector.extent(firstDim); ++j)
        {
            cummulative += propensitiesVector(j);
            if ( cummulative > a0*r1 )
            {
                reactionIndex = j;
                break;
            }
        }
        
        if (reactionIndex != -1)
        {
            fireReaction(reactionIndex, 1);
            t += tau;
        }
        else
        {
            t = HUGE_VAL;
            break;
        }
    }
}

void TauLeaping::_writeDiagnostic(FILE* myfile, long int L, int steps, long int L_sum, double dt_sum)
{
    double aver_dt = dt_sum/ (double) steps;
    double aver_L = L_sum/ (double) steps;
    
    if (myfile!=NULL)
        fprintf(myfile, "%f  %e  %e  %i  %f  %i \n", t, dt, aver_dt, L, aver_L, steps  );
    
}

void TauLeaping::solve()
{
    cout << "TauLeaping..." << endl;
    openAuxiliaryStream( (simulation->ModelName) + "_histogram.txt");
    FILE* rejectionsfile = fopen("Rejections_T.txt", "w");
    
    double aj;
    long int kj;
    double a0						= 0.0;
    bool isNegative					= false;
    double averNumberOfRealizations = 0.0;
    double numberOfRejections		= 0.0;
    
#ifdef SSASTEP
    const int SSAfactor = 10;
    const int SSAsteps = 1;
#endif
    
    for (int samples = 0; samples < numberOfSamples; ++samples)
    {
        t = simulation->StartTime;
        numberOfIterations = 0;
        numberOfRejections = 0.;
        timePoint = 0;
        zeroData();
        simulation->loadInitialConditions();
        isNegative = false;

        
        while (t < tEnd)
        {
            saveData();
            computePropensities(propensitiesVector, 0);
            a0 = blitz::sum(propensitiesVector);
            
            if (isNegative == false){
                dt = computeTimeStep();
                if (dt >= HUGE_VAL) {dt= tEnd*10; cout<<"stop"<<endl;	break;}
            }
            
#ifdef SSASTEP
            if (dt <= SSAfactor * (1.0/a0) * sgamma( (double)1.0 ) )
            {
                _executeSSA(t, SSAsteps);
                SSA_L += SSAsteps;
            }
            else
#endif
            {
                // sampling
                for (int j = 0; j < propensitiesVector.extent(firstDim); ++j)
                {
                    aj = propensitiesVector(j);
                    kj = (aj == 0) ? 0. : ignpoi( aj*dt );
                    fireReactionProposed( j , kj );
                }
                
                if (isProposedNegative() == false)
                {
                    acceptNewSpeciesValues();
                    ++numberOfIterations;
                    t += dt;
                    isNegative = false;
                }
                else
                {
                    cout << "Negative species at time: " << t << endl;
                    ++numberOfRejections;
                    dt = dt * 0.5;
                    reloadProposedSpeciesValues();
                    isNegative = true;
                }	
                
            }
        }
        
        saveData();
        cout << "Sample: " << samples << endl;
#ifdef SSASTEP
        cout<< "Number of SSA steps: "<< SSA_L / SSAsteps << endl;
#endif
        
        writeToAuxiliaryStream( simulation->speciesValues );
        averNumberOfRealizations += numberOfIterations;
        
        // report on negative population
        if (rejectionsfile!=NULL)
            fprintf(rejectionsfile, "%i %f %i \n", samples, numberOfRejections ,numberOfIterations);
        
    }
    
    writeData(outputFileName);
    closeAuxiliaryStream();
    fclose(rejectionsfile);
    
    cout << " Average number of Realizations in Tau-leaping:" << endl;
    cout << averNumberOfRealizations/numberOfSamples << endl;
    
}

