#! /bin/bash -f

# writes corresponding xml file with given eps $1, method $2 and stores it at given location $3
eps=$1
method=$2
outputFolder=$3

scriptName=BSubtilis-${method}-${eps}.xml

#---------------------- xml content ---------
cat > ${scriptName} << EOF
<?xml version="1.0" encoding="UTF-8"?>
<sbml xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
 xsi:schemaLocation="http://www.sbml.org/sbml/level1 http://www.sbml.org/sbml/level1"
 xmlns="http://www.sbml.org/sbml/level1"
 level="1"
 version="2">

    <model name="BSubtilis_${method}">

                <annotation xmlns:stochSim="AnnotationField">
                        <stochSim:TimeStart>            0.0        </stochSim:TimeStart>
                        <stochSim:TimeEnd>              10.0       </stochSim:TimeEnd>
                        <stochSim:Method>               ${method}  </stochSim:Method>
                        <stochSim:NumberOfSamples>      10000      </stochSim:NumberOfSamples>
                        <stochSim:numberOfNoiseLevels>  51         </stochSim:numberOfNoiseLevels>
                        <stochSim:Epsilon>              ${eps}     </stochSim:Epsilon>
                        <stochSim:Theta>                0.0        </stochSim:Theta>
                        <stochSim:Delta>                0.05       </stochSim:Delta>
                        <stochSim:StoreInterval>        25         </stochSim:StoreInterval>
                        <stochSim:SortInterval>         100000     </stochSim:SortInterval>
                </annotation>



--------------------------------------------------------------------------------------
		<listOfCompartments>
			<compartment volume="1.0" name="comp1" />
			</listOfCompartments>
			
--------------------------------------------------------------------------------------
		<listOfSpecies>
			<species compartment="comp1" initialAmount="300" name="S1"  units="mole"></species>
			<species compartment="comp1" initialAmount="150" name="S2"  units="mole"></species>
            		<species compartment="comp1" initialAmount="200" name="S3"  units="mole"></species>
		</listOfSpecies>
			
--------------------------------------------------------------------------------------
		
		<listOfReactions>

			<reaction name="R1">
		                <listOfProducts>
					<speciesReference species="S2" stoichiometry="1"/>
					<speciesReference species="S3" stoichiometry="3"/>
				</listOfProducts>
				<kineticLaw formula="">
					<listOfParameters>
						<parameter value="0.151" name="c1" />
						</listOfParameters>
					</kineticLaw>
				</reaction>
			
			<reaction name="R2">
				<listOfReactants>
					<speciesReference species="S1" stoichiometry="1"/>
                		        <speciesReference species="S2" stoichiometry="1"/>
				</listOfReactants>
				<listOfProducts>
					<speciesReference species="S3" stoichiometry="4" />
				</listOfProducts>
				<kineticLaw formula="">
					<listOfParameters>
						<parameter value="0.00031" name="c2" />
					</listOfParameters>
					</kineticLaw>
				</reaction>
			
			<reaction name="R3">
				<listOfReactants>
                    			<speciesReference species="S2" stoichiometry="1"/>
				</listOfReactants>
				<listOfProducts>
					<speciesReference species="S3" stoichiometry="4"/>
				</listOfProducts>
				<kineticLaw formula="">
					<listOfParameters>
						<parameter value="0.0034" name="c3" />
					</listOfParameters>
					</kineticLaw>
				</reaction>
			
            
			<reaction name="R4">
				<listOfReactants>
					<speciesReference species="S3" stoichiometry="1"/>
				</listOfReactants>
				<listOfProducts>
					<speciesReference species="S1" />
					<speciesReference species="S2" />
				</listOfProducts>
				<kineticLaw formula="">
					<listOfParameters>
						<parameter value="0.02" name="c4" />
					</listOfParameters>
					</kineticLaw>
				</reaction>
                
                
			<reaction name="R5">
				<listOfReactants>
					<speciesReference species="S1" stoichiometry="1"/>
                    			<speciesReference species="S2" stoichiometry="2"/>
				</listOfReactants>
				<kineticLaw formula="">
					<listOfParameters>
						<parameter value="0.000062" name="c5" />
					</listOfParameters>
					</kineticLaw>
				</reaction>
                
                
			<reaction name="R6">
				<listOfReactants>
					<speciesReference species="S1" stoichiometry="2"/>
				</listOfReactants>
				<listOfProducts>
					<speciesReference species="S1" />
					<speciesReference species="S2" />
				</listOfProducts>
				<kineticLaw formula="">
					<listOfParameters>
						<parameter value="0.00049" name="c6" />
					</listOfParameters>
					</kineticLaw>
				</reaction>
            
            
			
		</listOfReactions>
		
	</model>	
</sbml>

EOF
#---------------------- end of xml content -----

mv ${scriptName}  ${outputFolder}
