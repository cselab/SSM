#!/bin/sh

MethodsList="SSA AdaptiveSLeaping AdaptiveTauLeaping SLeaping RLeapingJana TauLeaping TauLeaping-NN"
EpsList="0.05 0.03 0.01"

for method in $MethodsList; do
mkdir ${method}

for eps in $EpsList; do

outputFolder=${method}/eps_${eps}/
mkdir ${outputFolder}

scriptName=Dimerization-${method}-${eps}.xml


cat > ${scriptName} << EOF
<?xml version="1.0" encoding="UTF-8"?>
<sbml xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
 xsi:schemaLocation="http://www.sbml.org/sbml/level1 http://www.sbml.org/sbml/level1"
 xmlns="http://www.sbml.org/sbml/level1"
 level="1"
 version="2">

    <model name="Dimerization-${method}">

                <annotation xmlns:stochSim="AnnotationField">
                        <stochSim:TimeStart>            0.0        </stochSim:TimeStart>
                        <stochSim:TimeEnd>              10.0       </stochSim:TimeEnd>
                        <stochSim:Method>               ${method}  </stochSim:Method>
                        <stochSim:NumberOfSamples>      5000      </stochSim:NumberOfSamples>
                        <stochSim:numberOfNoiseLevels>  51         </stochSim:numberOfNoiseLevels>
                        <stochSim:Epsilon>              ${eps}     </stochSim:Epsilon>
                        <stochSim:Theta>                0.0        </stochSim:Theta>
                        <stochSim:Delta>                0.05        </stochSim:Delta>
		        <stochSim:StoreInterval>        25         </stochSim:StoreInterval>
                        <stochSim:SortInterval>         100000     </stochSim:SortInterval>
                </annotation>



--------------------------------------------------------------------------------------
                <listOfCompartments>
                        <compartment volume="1.0" name="comp1" />
                        </listOfCompartments>

--------------------------------------------------------------------------------------
                <listOfSpecies>

                        <species compartment="comp1" initialAmount="4150" name="S1"  units="mole">
                                </species>

                        <species compartment="comp1" initialAmount="39565" name="S2"  units="mole">
                                </species>

                        <species compartment="comp1" initialAmount="3445" name="S3"  units="mole">
                                </species>

                </listOfSpecies>

--------------------------------------------------------------------------------------


                <listOfReactions>
                        <reaction name="R1">
                                <listOfReactants>
                                        <speciesReference species="S1" />
                                </listOfReactants>
                                <kineticLaw formula="">
                                        <listOfParameters>
                                                <parameter value="1.00" name="c1" />
                                                </listOfParameters>
                                        </kineticLaw>
                                </reaction>

                        <reaction name="R2">
                                <listOfReactants>
                                        <speciesReference species="S1" stoichiometry="2"/>
                                </listOfReactants>
                                <listOfProducts>
                                        <speciesReference species="S2" />
                                        </listOfProducts>
                                <kineticLaw formula="">
                                        <listOfParameters>
                                                <parameter value="10" name="c2" />
                                        </listOfParameters>
                                        </kineticLaw>
                                </reaction>

                        <reaction name="R3">
                                <listOfReactants>
                                        <speciesReference species="S2" />
                                        </listOfReactants>
                                <listOfProducts>
                                        <speciesReference species="S1" stoichiometry="2"/>
                                </listOfProducts>
                                <kineticLaw formula="">
                                        <listOfParameters>
                                                <parameter value="1000" name="c3" />
                                                </listOfParameters>
                                        </kineticLaw>
                                </reaction>

                        <reaction name="R4">
                                <listOfReactants>
                                        <speciesReference species="S2" />
                                        </listOfReactants>
                                <listOfProducts>
                                        <speciesReference species="S3" />
                                        </listOfProducts>
                                <kineticLaw formula="">
                                        <listOfParameters>
                                                <parameter value="0.1" name="c4" />
                                                </listOfParameters>
                                        </kineticLaw>
                                </reaction>


                </listOfReactions>

        </model>
</sbml>

EOF

mv ${scriptName}  ${outputFolder}

done
done
