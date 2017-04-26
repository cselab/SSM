/*
 *  RLeaping_LacZLacY.cpp
 *  SSM_Xcode
 *
 *  Created by Lipkova on 9/4/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#include "RLeaping_LacZLacY.h"


RLeaping_LacZLacY::RLeaping_LacZLacY(Simulation * simulation):
LeapMethod(simulation)
{
}

RLeaping_LacZLacY::~RLeaping_LacZLacY()
{
}

long int RLeaping_LacZLacY::computeLeapLength()
{
	long int L				 = 2147483647;//2^{31}-1
	
	double theta	= simulation->Theta;
	double epsilon	= simulation->Epsilon;
	
	int numberOfSpecies		= sbmlModel->getNumSpecies();
	int numberOfReactions	= sbmlModel->getNumReactions(); 
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
				tau = min(tau,epsixi/fabs(muHat(is)));
				epsixisq = epsixi*epsixi;
				tau = min(tau,epsixisq/varHat(is));
				break;
			default:
				break;
				
		}
	}
	
	L = (long int)max((long int)(tau*a0), (long int)1);	
	
	//   used to speed up simulation for theta != 0
	for (int ir = 0; ir < numberOfReactions; ++ir)
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
			long int propsedL = (long int)((1.0-theta*(1.0-a0/propensitiesVector(ir)))*lj);
			if (propsedL < L && propsedL > 0)
				L = propsedL;
			
			//			L = min( (long int)L, (long int)((1.0-theta*(1.0-a0/propensitiesVector(ir)))*lj) );
		}
	}
	
	return L;
}

// this method is overloaded from the Methods class since R-Leaping needs to store both indices and 
// propensities (not just propensities).  These are located in the anonymous inner class called Event
void RLeaping_LacZLacY::computePropensitiesGrowingVolume(double genTime)
{
	
	double volume	= 1. + t/genTime;
	double ivolume	= 1./volume;
		
	int nu;
	ParticleType x;
	ParticleType num, denom;
	
	int ir;		// the reaction index
	
	propensitiesVector = 0.0;
	
	vector<SSMReaction* > ssmReactionList = simulation->ssmReactionList;
	
	Reaction * sbmlreaction; // added maagm
	
	for (int ev = 0; ev < eventVector.size(); ++ev) // event index
	{
		eventVector[ev]->propensity = 0.0;
		ir							= eventVector[ev]->index;
		
		//added maagm
		SSMReaction* reaction		= ssmReactionList[ir];
		
		sbmlreaction = sbmlModel->getReaction(ir);
		KineticLaw * kineticLaw = sbmlreaction->getKineticLaw();
		Parameter * parameter = kineticLaw->getParameter(0);
		double rate = parameter->getValue();
		
		if (kineticLaw->getNumParameters() == 5)
		{
			int dependentSpecies = getDependentSpecies(ir);
			double dependentValue = (double)simulation->speciesValues(dependentSpecies);
			double h =					kineticLaw->getParameter(2)->getValue();
			double defaultProduction =	kineticLaw->getParameter(3)->getValue();
			double cHill =				kineticLaw->getParameter(4)->getValue();
			//propensitiesVector(ir) = defaultProduction + rate*hillFunction(cHill, dependentValue, h);
			reaction->setPropensity(defaultProduction + rate*hillFunction(cHill, dependentValue, h));
		}
		else
		{
			//original bbayati
			SSMReaction* reaction		= ssmReactionList[ir];
			vector <int>  reactants		= reaction->getReactants();
			vector <int>  nu_reactants	= reaction->getNuReactants();
			int order					= reaction->getOrder();

			reaction->setPropensity(reaction->getRate());
			
			for (int s = 0; s < reactants.size(); ++s)
			{
				nu		= nu_reactants[s];
				x		= simulation->speciesValues( reactants[s] );
				num		= x;
				denom	= nu;
				while ((--nu)>0)
				{
					denom	*= nu;
					num		*= (x - nu);
				}
				reaction->setPropensity( reaction->getPropensity()*((double)num/(double)denom) );
			}
			
			if (order == 2)
				reaction->setPropensity( reaction->getPropensity() * ivolume );
			
			if (order == 3) 
				reaction->setPropensity( reaction->getPropensity() * ivolume *ivolume);
			
			if (order > 3) 
			{
				std::cout<<"Aborting: Growing volume of reaction enviroment do not support reaction of order higher than 3, if you want it implement it"<<std::endl;
				std::abort();
			}	
		}
		
		propensitiesVector(ir)		= reaction->getPropensity();
		eventVector[ev]->propensity	= reaction->getPropensity();
	}
}

//***********************************
//       Sampling 
// Binomial sampling from reordered propensities
// no critical reactions considered
//***********************************
void RLeaping_LacZLacY::sampling(long int L, double a0)
{
	
	if ( L > sbmlModel->getNumReactions() )
	{
		double p = 0.0;
		double cummulative	= a0;
		long int k			= 0;
		
		for (int j = 0; j < eventVector.size(); ++j)
		{	
			if( (j == eventVector.size() - 1 ) && (L != 0) )
			{
				fireReactionProposed( eventVector[j]->index , L);	
				break;
			}
			
			cummulative		-= p;
			p				 = eventVector[j]->propensity;
			
			if(p!=0)
			{
				k				 = ignbin(L, min(p/cummulative, 1.0) );
				L				-= k;
				
				fireReactionProposed( eventVector[j]->index , k);			
				if (L == 0){ break; }
			}
		}
	}
//	else
//	{
//		for (int s = 0; s<L; s++)
//		{
//			double r1 = ranf();
//			int j = 0;
//			double suma = (eventVector[j]->propensity);
//			
//			while (a0*r1 > suma)
//			{
//				j++;
//				suma += (eventVector[j]->propensity);
//			}
//			
//			fireReactionProposed(eventVector[j]->index,1);
//		}
//	}
}

void RLeaping_LacZLacY:: _writeDiagnostic(FILE* myfile, long int L, int steps, long int L_sum, double dt_sum)
{
	double aver_dt = dt_sum/ (double) steps;
	double aver_L = L_sum/ (double) steps;
	
	// time, dt, aver_dt, L,averL, #iterations
	if (myfile!=NULL)
	{
		fprintf(myfile, "%f  %e  %e  %i  %f  %i \n", t, dt, aver_dt, L, aver_L, steps  );
	}
}

void RLeaping_LacZLacY:: _writeTrajectories(FILE* myfile, vector<int> data)
{
	if (myfile!=NULL) 
	{
		for (int i=0; i < data.size() ; ++i) 
			fprintf(myfile, "%i ", data[i], " " );
		
		fprintf(myfile, "\n");
	}
}

void RLeaping_LacZLacY::solve()
{
#ifndef NDEBUG	
	cout << "RLeaping LacZ/LacY..." << endl;
	openAuxiliaryStream( (simulation->ModelName) + "_histogram.txt");
	FILE* rejectionsfile = fopen("Rejections_R.txt", "w");
#endif
	
#ifdef TRAJECTORIES
	FILE* file_RbsLacY   = fopen("R_RbsLacY.txt"  , "w");
	FILE* file_TrLacZ2   = fopen("R_TrLacZ2.txt"  , "w");
	FILE* file_TrRbsLacY = fopen("R_TrRbsLacY.txt", "w");
	FILE* file_TrRbsLacZ = fopen("R_TrRbsLacZ.txt", "w");
#endif
	
	double a0						= 0.0;
	long int Lcurrent				= 1;
	bool isNegative					= false;
	double averNumberOfRealizations = 0.0;
	double numberOfRejections = 0.0;
	
	double genTime = 2100.;   // generation time

	
	for (int i = 0; i < sbmlModel->getNumReactions(); ++i)
	{
		Event * e = new Event();
		e->index		= i;
		e->propensity	= 0.0;
		eventVector.push_back(e);
	}
	
	for (int samples = 0; samples < numberOfSamples; ++samples)
	{
		t = simulation->StartTime;
		whenToSave			= simulation->StartTime;
		numberOfIterations	= 0;
		numberOfRejections	= 0.;
		timePoint			= 0;
		zeroData();
		simulation->loadInitialConditions();
		Lcurrent			= 1;
		isNegative			= false;
		
#ifdef TRAJECTORIES
		vector<int> RbsLacY;
		vector<int> TrLacZ2;
		vector<int> TrRbsLacY;
		vector<int> TrRbsLacZ;
		
		double whenToWriteTrajectories		 = simulation->StartTime;
		double whenToWriteTrajectoriesOffset = 1.;
#endif
		
#ifndef NDIAGNOSTIC  //diagnostic
		FILE* myfile = fopen("Diag_R.txt", "w");
		double whenToWriteOffset = tEnd / numberOfFrames;
		double whenToWrite = whenToWriteOffset;
		int iterSteps = 0;
		double dt_sum = 0.;
		long int L_sum = 0;
		double LAverage = 0.0;
#endif
		
		while (t < tEnd)
		{
			
			#ifndef NDEBUG
			saveData();
			#endif
			
			// set random variables values
			// RNAP     = S(1) ~ N(35),3.5^2)
			// Ribosome = S(9) ~ N(350,35^2)
			// + mean values of these pools growth with cell volume so that the concentrations of these molecules remain constant
			simulation->speciesValues(1)  = gennor(35  * (1 + t/genTime),  3.5);
			simulation->speciesValues(9)  = gennor(350 * (1 + t/genTime),   35);

			computePropensitiesGrowingVolume(genTime);
			a0 = blitz::sum(propensitiesVector);
			
			// sort the list
			if (numberOfIterations % simulation->SortInterval == 0)
				sort(eventVector.begin(), eventVector.end(), EventSort());
			
			/* 1) compute L */
			if (isNegative == false)
				Lcurrent =  computeLeapLength(); 
			
			/* 2) ssampling */
			sampling(Lcurrent, a0);
			
			/* 3) State update */
			if (isProposedNegative() == false)
			{
				acceptNewSpeciesValues();
				++numberOfIterations;
				dt = (1.0/a0) * sgamma( (double)Lcurrent ); // Gamma ( L, 1.0 / a0 )
				t += dt;
				isNegative = false;
				
#ifndef NDIAGNOSTIC
				LAverage += (double)Lcurrent;
				iterSteps = iterSteps + 1;
				L_sum  += Lcurrent;
				dt_sum +=dt;
				
				//if ( t >= ((double) (whenToWrite)))
				{
					_writeDiagnostic(myfile, Lcurrent, iterSteps, L_sum, dt_sum);
					whenToWrite = whenToWrite + whenToWriteOffset;
					
					// reset counters
					iterSteps = 0;
					L_sum = 0.;
					dt_sum = 0.;
				}
#endif
				
#ifdef TRAJECTORIES
				// write trajectories of RbsLacY=S(7), TrLacZ2=S(5),TrRbsLacY=S(13),TrRbsLacZ=S(12)
				if (t >= whenToWriteTrajectories )
				{
					RbsLacY.push_back(simulation->speciesValues(7));
					TrLacZ2.push_back(simulation->speciesValues(5));
					TrRbsLacY.push_back(simulation->speciesValues(13));
					TrRbsLacZ.push_back(simulation->speciesValues(12));
					
					whenToWriteTrajectories += whenToWriteTrajectoriesOffset;
				}
#endif
			}
			else
			{					
#ifndef NDEBUG
				cout << "Negative species at time: " << t << endl;
				++numberOfRejections;
#endif
				Lcurrent = max( (int)(Lcurrent*0.5), 1);
				reloadProposedSpeciesValues();
				isNegative = true;
			}
		} // end of while
		
#ifdef TRAJECTORIES
		_writeTrajectories(file_RbsLacY,RbsLacY);
		_writeTrajectories(file_TrLacZ2,TrLacZ2);
		_writeTrajectories(file_TrRbsLacY,TrRbsLacY);
		_writeTrajectories(file_TrRbsLacZ,TrRbsLacZ);	
		
		cout << "Sample: " << samples << endl;
#endif
		
#ifndef NDEBUG 
		
		saveData();
				
#ifndef NDIAGNOSTIC
		cout << "Average L: " << LAverage/((double)numberOfIterations) << endl;
		fclose(myfile);
#endif
		
		writeToAuxiliaryStream( simulation->speciesValues );
		//writeData(localOutputFileName,samples);
		averNumberOfRealizations += numberOfIterations;
		
		// report on negative population
		if (rejectionsfile!=NULL)
			fprintf(rejectionsfile, "%i %f %i \n", samples, numberOfRejections ,numberOfIterations);
#endif
		
	}  // end of : for(samples, ...) 
	
#ifndef NDEBUG
	writeData(outputFileName);
	closeAuxiliaryStream();
	cout << " Average number of Realizations in R-leaping:" << endl;
	cout << averNumberOfRealizations/numberOfSamples << endl;
	
	fclose(rejectionsfile);
#endif
	
#ifdef TRAJECTORIES
	fclose(file_RbsLacY);
	fclose(file_TrLacZ2);
	fclose(file_TrRbsLacY);
	fclose(file_TrRbsLacZ);
#endif
	
	for (int i = 0; i < eventVector.size(); ++i) { delete eventVector[i]; }
	
}






