/*
 *  SLeapingNonNegative.cpp
 *  SSM_Xcode
 *
 *  Created by Lipkova on 8/19/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#include "SLeapingNonNegative.h"


SLeapingNonNegative::SLeapingNonNegative(Simulation * simulation):
LeapMethod(simulation)
{
}

SLeapingNonNegative::~SLeapingNonNegative()
{
}

vector<int> SLeapingNonNegative::listOfCriticalReactions()
{	
	vector<int> critical_reactions;
	int Ncrit = 10;  
	
	for (int ir = 0; ir < sbmlModel->getNumReactions(); ++ir)
	{
		long int lj = 2147483647; // MAXIMUM INTEGER
		SSMReaction * ssmReaction = simulation->ssmReactionList[ir];
		if (propensitiesVector(ir) > 0.0)
		{
			const vector<int> & changes		= ssmReaction->getChanges();
			const vector<int> & nuChanges	= ssmReaction->getNuChanges();
			
			for (int is = 0; is < changes.size() ; ++is)
			{
				if (nuChanges[is] > 0) break;
				lj = min(lj, -simulation->speciesValues(changes[is])/ nuChanges[is] );
			}
		}
		
		if (lj < Ncrit)
			critical_reactions.push_back(ir);
	}
	
	return critical_reactions;
}


double SLeapingNonNegative::computeTimeStep(vector<int> criticalReactions)
{	
	vector<int>    non_critical;    // list of non critical reactions used to compute muHat, signaHat2 
	
	double epsilon	        = simulation->Epsilon;	
	int numberOfSpecies		= sbmlModel->getNumSpecies();
	int numberOfReactions	= sbmlModel->getNumReactions(); 
	Array<int, 1> hor			(numberOfSpecies);
	Array<int, 1> nuHor			(numberOfSpecies);
	Array<double, 1> muHat		(numberOfSpecies);
	Array<double, 1> sigmaHat2	(numberOfSpecies);
	Array<double, 1> varHat		(numberOfSpecies);
	
	hor = 0; nuHor = 0; muHat = 0.0; sigmaHat2 = 0.0;
	computeHor(hor, nuHor);
	
	//computeMuHatSigmaHat2
	if (criticalReactions.empty())
		LeapMethod::computeMuHatSigmaHat2(muHat, sigmaHat2);
	else  // exclude critical reactions 
	{
	    int j = 0;
		for (int ir = 0; ir < numberOfReactions; ++ir)
		{
			if (ir != criticalReactions[j] )   // non critical reactions
				non_critical.push_back(ir);
			else 
				j++; 
		}
		computeMuHatSigmaHat2(muHat, sigmaHat2,non_critical);	
	}
	
	double tau, taup,  epsi, epsixi, epsixisq;
	double xi;
	
    tau = HUGE_VAL;
	
	double a0 = (double)blitz::sum(propensitiesVector);
	for (int is = 0; is < numberOfSpecies; is++)
		varHat(is) = sigmaHat2(is) - (1.0/a0) * muHat(is) * muHat(is);
	
	
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
};


double SLeapingNonNegative::computeTimeOfCritical(vector<int> criticalReactions, double& ac0) 
{
	double tau2;
	
	if (criticalReactions.empty()) 
	{
		tau2 = HUGE_VAL;
		ac0 = 0.0;
	}
	else
	{
		ac0 = 0.0;
		
		for (vector<int>::iterator it = criticalReactions.begin(); it!=criticalReactions.end() ; ++it)
			ac0 += propensitiesVector(*it);
		
		tau2 = (1.0/ac0) * sgamma( (double)1.0 );		
	}
	
	return tau2;
};

// this method is overloaded from the LeapMethod class, since in adaptive tau leaping we exclude
// critical reactions from computation of explicit tau and additionaly we exclude reactions in PEC
// in computation of implicit tau
void SLeapingNonNegative::computeMuHatSigmaHat2(Array<double, 1> & muHat, Array<double, 1> & sigmaHat2, vector<int> non_critical)
{
	int is, ir, ns, indx, nr;
	double tmpfloat;
	nr = sbmlModel->getNumReactions();
	
	for (int numbS = 0; numbS < sbmlModel->getNumSpecies(); ++numbS)
	{
		muHat(numbS) = 0.0;
		sigmaHat2(numbS) = 0.0;
	}
	
	// consider only non-critical reactions
	for (vector<int>::iterator ir = non_critical.begin(); ir!=non_critical.end(); ++ir)	
	{
		SSMReaction* ri = simulation->ssmReactionList[*ir];
		double  riPropensity = propensitiesVector(*ir);
		
		const vector<int> & changes = ri->getChanges();
		const vector<int> & nuChanges = ri->getNuChanges();
		
		ns = changes.size();
		for (is = 0; is < ns; is++ )
		{
			indx = changes[is];
			tmpfloat = nuChanges[is] * riPropensity;
			muHat(indx) += tmpfloat;
			sigmaHat2(indx) += nuChanges[is] * tmpfloat;
		}
	}
}


long int SLeapingNonNegative::computeLeapLength(double dt, double a0, double ac0, vector<int> criticalReactions)
{	
	if ( criticalReactions.empty() ) 
		return (long int)max( (long int)ignpoi(a0*dt), (long int)1) ; 
	else
		return (long int)max( (long int)ignpoi( (a0 - ac0) * dt), (long int)1) ; 
}





void SLeapingNonNegative::sampling(long int Llocal, double a0, double ac0, vector<int> criticalReactions, short int crit)
{
	long int numberOfReactions = sbmlModel->getNumReactions(); 
	
	// sample non critical reactions
	
	if (criticalReactions.empty())
	{
		if ( Llocal > numberOfReactions )
		{
			double p = 0.0;
			double cummulative	= a0;
			long int k			= 0;
			
			for (int j = 0; j < numberOfReactions ; ++j)
			{	
				if( (j == numberOfReactions - 1 ) && (Llocal != 0) )
				{
					fireReactionProposed( j , Llocal);	
					break;
				}
				
				cummulative		-= p;
				p				 = propensitiesVector(j);
				if (p!=0)
				{
					k				 = ignbin(Llocal, min(p/cummulative, 1.0) );
					Llocal			-= k;
					
					fireReactionProposed( j , k);	
					if (Llocal == 0){ break; }
				}
			}
		}
		else 
		{
			for (int s = 0; s<Llocal; s++)
			{
				double r1 = ranf();
				int j = 0;
				double suma = propensitiesVector(j)/a0;
				
				while (r1 > suma)
				{
					j++;
					suma += propensitiesVector(j)/a0;
				}
				
				fireReactionProposed(j,1);
			}
		}
	}
	else  // some critical reactions, thus we sample just from non critical
	{
		double p			= 0.0;
		double cummulative	= a0;
		long int k			= 0;
		long int m			= 0;
		
		for (int j = 0; j < numberOfReactions ; ++j)
		{	
			if (j!=criticalReactions[m])
			{
				cummulative		-= p;
				p				 = propensitiesVector(j);
				if (p!=0)
				{
					k				 = ignbin(Llocal, min(p/cummulative, 1.0) );
					Llocal			-= k;
					
					fireReactionProposed( j , k);	
					if (Llocal == 0){ break; }
				}
			}
			else 
				m++;
			
		}
	}
	
	if (crit == 1)
	{
		double r1 = ranf();
		int reactionIndex = 0;
		vector<int>::iterator it = criticalReactions.begin();
		double cummulative = propensitiesVector(*it);
		
		while (cummulative < r1 * ac0)
		{
			++it;
			cummulative += propensitiesVector(*it);
		}
		
		fireReactionProposed( *it , 1 );
	}
}


void SLeapingNonNegative::_executeSSA(double& t, int SSAsteps)
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
			if (t > tEnd) 
				break;
		}
		else 
		{ 
			t = HUGE_VAL;
			break;
		}
	}
	
}


void SLeapingNonNegative::	_writeDiagnostic(FILE* myfile, long int L, int steps, long int L_sum, double dt_sum)
{
	double aver_dt = dt_sum/ (double) steps;
	double aver_L = L_sum/ (double) steps;
	
	// time, dt, aver_dt, L,averL, #iterations
	if (myfile!=NULL)
	{
		fprintf(myfile, "%f  %e  %e  %i  %f  %i \n", t, dt, aver_dt, L, aver_L, steps  );
	}
}


void SLeapingNonNegative::solve()
{
#ifndef NDEBUG
	cout << "SLeaping and LC..." << endl;
	openAuxiliaryStream( (simulation->ModelName) + "_histogram.txt");
	FILE* rejectionsfile = fopen("Rejections_ST.txt", "w");
#endif
	
	double a0						= 0.0;
	double ac0						= 0.0;
	double dt2						= 0.; 
	long int L						= 1;
	short int crit					= 0;
	bool isNegative					= false;
	double averNumberOfRealizations = 0.0;
	double numberOfRejections;
	
#ifdef SSASTEP
	const int SSAfactor = 10;
	const int SSAsteps = 100;
#endif
	
	for (int samples = 0; samples < numberOfSamples; ++samples)
	{
		t = simulation->StartTime;
		numberOfIterations = 0;
		numberOfRejections = 0.0;
		timePoint = 0;
		zeroData();
		simulation->loadInitialConditions();
		isNegative = false;
		
		
#ifndef NDIAGNOSTIC  //diagnostic
		FILE* myfile = fopen("Diag_ST.txt", "w");
		double whenToWriteOffset = tEnd / numberOfFrames;
		double whenToWrite = whenToWriteOffset;
		
		int iterSteps = 0;
		double dt_sum = 0.;
		long int L_sum = 0;
		long int SSA_L = 0;
		double LAverage = 0.0;
#endif
		
		while (t < tEnd) 
		{
			
#ifndef NDEBUG
			saveData();
#endif
			computePropensities(propensitiesVector, 0);
			a0 = blitz::sum(propensitiesVector);
			
			vector<int> criticalReactions = listOfCriticalReactions();
			crit						  = 0 ;   // reset number of critical reactions to be executed;
			
			if (isNegative == false)
			{
				dt = computeTimeStep(criticalReactions);
				if ( (t+dt) > tEnd) 
					dt = tEnd - t;
			}
			
#ifdef SSASTEP
			if (dt <= SSAfactor * (1.0/a0) ) // * sgamma( (double)1.0 ) ) 
			{
				_executeSSA(t, SSAsteps);
#ifndef NDEBUG
			SSA_L += SSAsteps;
#endif
			}
			else
#endif
			{
				
				/* 3) compute time of critical reaction*/
				dt2 = computeTimeOfCritical(criticalReactions, ac0);
				
				if (dt2 < dt) 
				{
					dt	 =	dt2;
					crit = 1;
				}
				
				L =  computeLeapLength(dt,a0,  ac0, criticalReactions);	
				sampling(L, a0, ac0, criticalReactions, crit);
				
				if (isProposedNegative() == false)
				{
					acceptNewSpeciesValues();
					++numberOfIterations;
					t += dt;
					isNegative = false;
					
					
#ifndef NDIAGNOSTIC
					LAverage += (double)L;
					iterSteps = iterSteps + 1;
					L_sum  += L;
					dt_sum +=dt;
					
					//if ( t >= ((double) (whenToWrite)))
					{
						_writeDiagnostic(myfile, L, iterSteps, L_sum, dt_sum);
						whenToWrite = whenToWrite + whenToWriteOffset;
						
						// reset counters
						iterSteps = 0;
						L_sum = 0.;
						dt_sum = 0.;
					}
#endif
				}
				else
				{
#ifndef NDEBUG
					cout << "Negative species at time: " << t << endl;
					++numberOfRejections;
#endif
					dt = dt *0.5;
					reloadProposedSpeciesValues();
					isNegative = true;
				}
			}
		}  // end of: while(t < tEnd)
		
		
#ifndef NDEBUG
		saveData();
		
		cout << "Sample: " << samples << endl;
		
#ifndef NDIAGNOSTIC
		cout << "Average L: " << LAverage/((double)numberOfIterations) << endl;
		fclose(myfile);
#endif
		
#ifdef SSASTEP
		cout<< "Number of SSA steps: "<< SSA_L / SSAsteps << endl;
#endif
		
		writeToAuxiliaryStream( simulation->speciesValues );
		//writeData(localOutputFileName,samples);
		averNumberOfRealizations += numberOfIterations;
		
		// report on negative population
		if (rejectionsfile!=NULL)
			fprintf(rejectionsfile, "%i %f %i \n", samples, numberOfRejections ,numberOfIterations);
#endif
		
	}   // end of: for(samples...)
	
#ifndef NDEBUG
	writeData(outputFileName);
	closeAuxiliaryStream();
	cout << " Average number of Realizations in S-leaping:" << endl;
	cout << averNumberOfRealizations/numberOfSamples << endl;
	
	fclose(rejectionsfile);
#endif
	
}  // end of: solve()

